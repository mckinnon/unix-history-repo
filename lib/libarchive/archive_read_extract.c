/*-
 * Copyright (c) 2003-2007 Tim Kientzle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "archive_platform.h"
__FBSDID("$FreeBSD$");

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "archive.h"
#include "archive_private.h"
#include "archive_read_private.h"
#include "archive_write_disk_private.h"

struct extract {
	struct archive *ad; /* archive_write_disk object */

	/* Progress function invoked during extract. */
	void			(*extract_progress)(void *);
	void			 *extract_progress_user_data;
};

static int	archive_read_extract_cleanup(struct archive_read *);
static int	copy_data(struct archive *ar, struct archive *aw);
static struct extract *get_extract(struct archive_read *);

static struct extract *
get_extract(struct archive_read *a)
{
	/* If we haven't initialized, do it now. */
	/* This also sets up a lot of global state. */
	if (a->extract == NULL) {
		a->extract = (struct extract *)malloc(sizeof(*a->extract));
		if (a->extract == NULL) {
			archive_set_error(&a->archive, ENOMEM, "Can't extract");
			return (NULL);
		}
		a->extract->ad = archive_write_disk_new();
		if (a->extract->ad == NULL) {
			archive_set_error(&a->archive, ENOMEM, "Can't extract");
			return (NULL);
		}
		archive_write_disk_set_standard_lookup(a->extract->ad);
		a->cleanup_archive_extract = archive_read_extract_cleanup;
	}
	return (a->extract);
}

int
archive_read_extract(struct archive *_a, struct archive_entry *entry, int flags)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct extract *extract;
	int r, r2;

	extract = get_extract(a);
	if (extract == NULL)
		return (ARCHIVE_FATAL);

	/* Set up for this particular entry. */
	extract = a->extract;
	archive_write_disk_set_options(a->extract->ad, flags);
	archive_write_disk_set_skip_file(a->extract->ad,
	    a->skip_file_dev, a->skip_file_ino);
	r = archive_write_header(a->extract->ad, entry);
	if (r == ARCHIVE_OK)
		/* If there's an FD, pour data into it. */
		r = copy_data(_a, a->extract->ad);
	r2 = archive_write_finish_entry(a->extract->ad);
	/* Use the first message. */
	if (r2 != ARCHIVE_OK || r != ARCHIVE_OK)
		archive_set_error(&a->archive,
		    archive_errno(extract->ad),
		    "%s", archive_error_string(extract->ad));
	/* Use the worst error return. */
	if (r2 < r)
		r = r2;
	return (r);
}

void
archive_read_extract_set_progress_callback(struct archive *_a,
    void (*progress_func)(void *), void *user_data)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct extract *extract = get_extract(a);
	if (extract != NULL) {
		extract->extract_progress = progress_func;
		extract->extract_progress_user_data = user_data;
	}
}

static int
copy_data(struct archive *ar, struct archive *aw)
{
	int r;
	const void *buff;
	size_t size;
	off_t offset;

	for (;;) {
		r = archive_read_data_block(ar, &buff, &size, &offset);
		if (r == ARCHIVE_EOF)
			return (ARCHIVE_OK);
		if (r != ARCHIVE_OK)
			return (r);
		r = archive_write_data_block(aw, buff, size, offset);
		if (r != ARCHIVE_OK) {
			archive_set_error(ar, archive_errno(aw),
			    "%s", archive_error_string(aw));
			return (r);
		}
	}
}

/*
 * Cleanup function for archive_extract.
 */
static int
archive_read_extract_cleanup(struct archive_read *a)
{
	int ret = ARCHIVE_OK;

#if ARCHIVE_API_VERSION > 1
	ret =
#endif
	    archive_write_finish(a->extract->ad);
	free(a->extract);
	a->extract = NULL;
	return (ret);
}
