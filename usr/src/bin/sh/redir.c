/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "@(#)redir.c	5.4 (Berkeley) %G%";
#endif /* not lint */

/*
 * Code for dealing with input/output redirection.
 */

#include "shell.h"
#include "nodes.h"
#include "jobs.h"
#include "expand.h"
#include "redir.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


#define EMPTY -2		/* marks an unused slot in redirtab */
#define PIPESIZE 4096		/* amount of buffering in a pipe */


MKINIT
struct redirtab {
	struct redirtab *next;
	short renamed[10];
};


MKINIT struct redirtab *redirlist;

/* 
 * We keep track of whether or not fd0 has been redirected.  This is for
 * background commands, where we want to redirect fd0 to /dev/null only
 * if it hasn't already been redirected.  
*/
int fd0_redirected = 0;

#ifdef __STDC__
STATIC void openredirect(union node *, char *);
STATIC int openhere(union node *);
#else
STATIC void openredirect();
STATIC int openhere();
#endif



/*
 * Process a list of redirection commands.  If the REDIR_PUSH flag is set,
 * old file descriptors are stashed away so that the redirection can be
 * undone by calling popredir.  If the REDIR_BACKQ flag is set, then the
 * standard output, and the standard error if it becomes a duplicate of
 * stdout, is saved in memory.
 */

void
redirect(redir, flags)
	union node *redir;
	int flags;
	{
	union node *n;
	struct redirtab *sv;
	int i;
	int fd;
	char memory[10];		/* file descriptors to write to memory */

	for (i = 10 ; --i >= 0 ; )
		memory[i] = 0;
	memory[1] = flags & REDIR_BACKQ;
	if (flags & REDIR_PUSH) {
		sv = ckmalloc(sizeof (struct redirtab));
		for (i = 0 ; i < 10 ; i++)
			sv->renamed[i] = EMPTY;
		sv->next = redirlist;
		redirlist = sv;
	}
	for (n = redir ; n ; n = n->nfile.next) {
		fd = n->nfile.fd;
		if ((flags & REDIR_PUSH) && sv->renamed[fd] == EMPTY) {
			INTOFF;
			if ((i = copyfd(fd, 10)) != EMPTY) {
				sv->renamed[fd] = i;
				close(fd);
			}
			INTON;
			if (i == EMPTY)
				error("Out of file descriptors");
		} else {
			close(fd);
		}
                if (fd == 0)
                        fd0_redirected++;
		openredirect(n, memory);
	}
	if (memory[1])
		out1 = &memout;
	if (memory[2])
		out2 = &memout;
}


STATIC void
openredirect(redir, memory)
	union node *redir;
	char memory[10];
	{
	int fd = redir->nfile.fd;
	char *fname;
	int f;

	/*
	 * We suppress interrupts so that we won't leave open file
	 * descriptors around.  This may not be such a good idea because
	 * an open of a device or a fifo can block indefinitely.
	 */
	INTOFF;
	memory[fd] = 0;
	switch (redir->nfile.type) {
	case NFROM:
		fname = redir->nfile.expfname;
		if ((f = open(fname, O_RDONLY)) < 0)
			error("cannot open %s: %s", fname, errmsg(errno, E_OPEN));
movefd:
		if (f != fd) {
			copyfd(f, fd);
			close(f);
		}
		break;
	case NTO:
		fname = redir->nfile.expfname;
#ifdef O_CREAT
		if ((f = open(fname, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
			error("cannot create %s: %s", fname, errmsg(errno, E_CREAT));
#else
		if ((f = creat(fname, 0666)) < 0)
			error("cannot create %s: %s", fname, errmsg(errno, E_CREAT));
#endif
		goto movefd;
	case NAPPEND:
		fname = redir->nfile.expfname;
#ifdef O_APPEND
		if ((f = open(fname, O_WRONLY|O_CREAT|O_APPEND, 0666)) < 0)
			error("cannot create %s: %s", fname, errmsg(errno, E_CREAT));
#else
		if ((f = open(fname, O_WRONLY)) < 0
		 && (f = creat(fname, 0666)) < 0)
			error("cannot create %s: %s", fname, errmsg(errno, E_CREAT));
		lseek(f, (off_t)0, 2);
#endif
		goto movefd;
	case NTOFD:
	case NFROMFD:
		if (redir->ndup.dupfd >= 0) {	/* if not ">&-" */
			if (memory[redir->ndup.dupfd])
				memory[fd] = 1;
			else
				copyfd(redir->ndup.dupfd, fd);
		}
		break;
	case NHERE:
	case NXHERE:
		f = openhere(redir);
		goto movefd;
	default:
		abort();
	}
	INTON;
}


/*
 * Handle here documents.  Normally we fork off a process to write the
 * data to a pipe.  If the document is short, we can stuff the data in
 * the pipe without forking.
 */

STATIC int
openhere(redir)
	union node *redir;
	{
	int pip[2];
	int len;

	if (pipe(pip) < 0)
		error("Pipe call failed");
	if (redir->type == NHERE) {
		len = strlen(redir->nhere.doc->narg.text);
		if (len <= PIPESIZE) {
			xwrite(pip[1], redir->nhere.doc->narg.text, len);
			goto out;
		}
	}
	if (forkshell((struct job *)NULL, (union node *)NULL, FORK_NOJOB) == 0) {
		close(pip[0]);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
#ifdef SIGTSTP
		signal(SIGTSTP, SIG_IGN);
#endif
		signal(SIGPIPE, SIG_DFL);
		if (redir->type == NHERE)
			xwrite(pip[1], redir->nhere.doc->narg.text, len);
		else
			expandhere(redir->nhere.doc, pip[1]);
		_exit(0);
	}
out:
	close(pip[1]);
	return pip[0];
}



/*
 * Undo the effects of the last redirection.
 */

void
popredir() {
	register struct redirtab *rp = redirlist;
	int i;

	for (i = 0 ; i < 10 ; i++) {
		if (rp->renamed[i] != EMPTY) {
                        if (i == 0)
                                fd0_redirected--;
			close(i);
			if (rp->renamed[i] >= 0) {
				copyfd(rp->renamed[i], i);
				close(rp->renamed[i]);
			}
		}
	}
	INTOFF;
	redirlist = rp->next;
	ckfree(rp);
	INTON;
}

/*
 * Undo all redirections.  Called on error or interrupt.
 */

#ifdef mkinit

INCLUDE "redir.h"

RESET {
	while (redirlist)
		popredir();
}

SHELLPROC {
	clearredir();
}

#endif

/* Return true if fd 0 has already been redirected at least once.  */
int
fd0_redirected_p () {
        return fd0_redirected != 0;
}

/*
 * Discard all saved file descriptors.
 */

void
clearredir() {
	register struct redirtab *rp;
	int i;

	for (rp = redirlist ; rp ; rp = rp->next) {
		for (i = 0 ; i < 10 ; i++) {
			if (rp->renamed[i] >= 0) {
				close(rp->renamed[i]);
			}
			rp->renamed[i] = EMPTY;
		}
	}
}



/*
 * Copy a file descriptor to be >= to.  Returns -1
 * if the source file descriptor is closed, EMPTY if there are no unused
 * file descriptors left.
 */

int
copyfd(from, to) {
	int newfd;

	newfd = fcntl(from, F_DUPFD, to);
	if (newfd < 0 && errno == EMFILE)
		return EMPTY;
	return newfd;
}
