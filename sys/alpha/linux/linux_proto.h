/*
 * System call prototypes.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 * created from FreeBSD: src/sys/alpha/linux/syscalls.master,v 1.45 2001/02/20 03:47:59 gallatin Exp 
 */

#ifndef _LINUX_SYSPROTO_H_
#define	_LINUX_SYSPROTO_H_

#include <sys/signal.h>

#include <sys/acl.h>

struct proc;

#define	PAD_(t)	(sizeof(register_t) <= sizeof(t) ? \
		0 : sizeof(register_t) - sizeof(t))

struct	linux_fork_args {
	register_t dummy;
};
struct	osf1_wait4_args {
	int	pid;	char pid_[PAD_(int)];
	int *	status;	char status_[PAD_(int *)];
	int	options;	char options_[PAD_(int)];
	struct osf1_rusage *	rusage;	char rusage_[PAD_(struct osf1_rusage *)];
};
struct	linux_link_args {
	char *	path;	char path_[PAD_(char *)];
	char *	to;	char to_[PAD_(char *)];
};
struct	linux_unlink_args {
	char *	path;	char path_[PAD_(char *)];
};
struct	linux_chdir_args {
	char *	path;	char path_[PAD_(char *)];
};
struct	linux_mknod_args {
	char *	path;	char path_[PAD_(char *)];
	int	mode;	char mode_[PAD_(int)];
	int	dev;	char dev_[PAD_(int)];
};
struct	linux_chmod_args {
	char *	path;	char path_[PAD_(char *)];
	int	mode;	char mode_[PAD_(int)];
};
struct	linux_chown_args {
	char *	path;	char path_[PAD_(char *)];
	int	uid;	char uid_[PAD_(int)];
	int	gid;	char gid_[PAD_(int)];
};
struct	linux_brk_args {
	char *	dsend;	char dsend_[PAD_(char *)];
};
struct	linux_lseek_args {
	int	fdes;	char fdes_[PAD_(int)];
	long	off;	char off_[PAD_(long)];
	int	whence;	char whence_[PAD_(int)];
};
struct	linux_umount2_args {
	char *	path;	char path_[PAD_(char *)];
	int	flags;	char flags_[PAD_(int)];
};
struct	linux_ptrace_args {
	register_t dummy;
};
struct	linux_access_args {
	char *	path;	char path_[PAD_(char *)];
	int	flags;	char flags_[PAD_(int)];
};
struct	linux_kill_args {
	int	pid;	char pid_[PAD_(int)];
	int	signum;	char signum_[PAD_(int)];
};
struct	linux_open_args {
	char *	path;	char path_[PAD_(char *)];
	int	flags;	char flags_[PAD_(int)];
	int	mode;	char mode_[PAD_(int)];
};
struct	osf1_sigprocmask_args {
	int	how;	char how_[PAD_(int)];
	u_long	mask;	char mask_[PAD_(u_long)];
};
struct	linux_ioctl_args {
	int	fd;	char fd_[PAD_(int)];
	u_long	cmd;	char cmd_[PAD_(u_long)];
	u_long	arg;	char arg_[PAD_(u_long)];
};
struct	linux_symlink_args {
	char *	path;	char path_[PAD_(char *)];
	char *	to;	char to_[PAD_(char *)];
};
struct	linux_readlink_args {
	char *	name;	char name_[PAD_(char *)];
	char *	buf;	char buf_[PAD_(char *)];
	int	count;	char count_[PAD_(int)];
};
struct	linux_execve_args {
	char *	path;	char path_[PAD_(char *)];
	char **	argp;	char argp_[PAD_(char **)];
	char **	envp;	char envp_[PAD_(char **)];
};
struct	linux_vfork_args {
	register_t dummy;
};
struct	linux_newstat_args {
	char *	path;	char path_[PAD_(char *)];
	struct linux_newstat *	buf;	char buf_[PAD_(struct linux_newstat *)];
};
struct	linux_newlstat_args {
	char *	path;	char path_[PAD_(char *)];
	struct linux_newstat *	buf;	char buf_[PAD_(struct linux_newstat *)];
};
struct	linux_mmap_args {
	caddr_t	addr;	char addr_[PAD_(caddr_t)];
	size_t	len;	char len_[PAD_(size_t)];
	int	prot;	char prot_[PAD_(int)];
	int	flags;	char flags_[PAD_(int)];
	int	fd;	char fd_[PAD_(int)];
	off_t	pos;	char pos_[PAD_(off_t)];
};
struct	linux_munmap_args {
	caddr_t	addr;	char addr_[PAD_(caddr_t)];
	u_long	len;	char len_[PAD_(u_long)];
};
struct	linux_mprotect_args {
	caddr_t	addr;	char addr_[PAD_(caddr_t)];
	size_t	len;	char len_[PAD_(size_t)];
	int	prot;	char prot_[PAD_(int)];
};
struct	linux_vhangup_args {
	register_t dummy;
};
struct	linux_setgroups_args {
	u_int	gidsetsize;	char gidsetsize_[PAD_(u_int)];
	linux_gid_t *	gidset;	char gidset_[PAD_(linux_gid_t *)];
};
struct	linux_getgroups_args {
	u_int	gidsetsize;	char gidsetsize_[PAD_(u_int)];
	linux_gid_t *	gidset;	char gidset_[PAD_(linux_gid_t *)];
};
struct	linux_setpgid_args {
	int	pid;	char pid_[PAD_(int)];
	int	pgid;	char pgid_[PAD_(int)];
};
struct	osf1_setitimer_args {
	u_int	which;	char which_[PAD_(u_int)];
	struct itimerval *	itv;	char itv_[PAD_(struct itimerval *)];
	struct itimerval *	oitv;	char oitv_[PAD_(struct itimerval *)];
};
struct	linux_newfstat_args {
	int	fd;	char fd_[PAD_(int)];
	struct linux_newstat *	buf;	char buf_[PAD_(struct linux_newstat *)];
};
struct	linux_fcntl_args {
	int	fd;	char fd_[PAD_(int)];
	int	cmd;	char cmd_[PAD_(int)];
	u_long	arg;	char arg_[PAD_(u_long)];
};
struct	osf1_select_args {
	u_int	nd;	char nd_[PAD_(u_int)];
	fd_set *	in;	char in_[PAD_(fd_set *)];
	fd_set *	ou;	char ou_[PAD_(fd_set *)];
	fd_set *	ex;	char ex_[PAD_(fd_set *)];
	struct timeval *	tv;	char tv_[PAD_(struct timeval *)];
};
struct	osf1_socket_args {
	int	domain;	char domain_[PAD_(int)];
	int	type;	char type_[PAD_(int)];
	int	protocol;	char protocol_[PAD_(int)];
};
struct	linux_connect_args {
	int	s;	char s_[PAD_(int)];
	caddr_t	name;	char name_[PAD_(caddr_t)];
	int	namelen;	char namelen_[PAD_(int)];
};
struct	osf1_sigreturn_args {
	struct osigcontext *	sigcntxp;	char sigcntxp_[PAD_(struct osigcontext *)];
};
struct	osf1_sigsuspend_args {
	unsigned long	ss;	char ss_[PAD_(unsigned long)];
};
struct	osf1_gettimeofday_args {
	struct timeval *	tp;	char tp_[PAD_(struct timeval *)];
	struct timezone *	tzp;	char tzp_[PAD_(struct timezone *)];
};
struct	osf1_getrusage_args {
	long	who;	char who_[PAD_(long)];
	void *	rusage;	char rusage_[PAD_(void *)];
};
struct	linux_rename_args {
	char *	from;	char from_[PAD_(char *)];
	char *	to;	char to_[PAD_(char *)];
};
struct	linux_truncate_args {
	char *	path;	char path_[PAD_(char *)];
	long	length;	char length_[PAD_(long)];
};
struct	osf1_sendto_args {
	int	s;	char s_[PAD_(int)];
	caddr_t	buf;	char buf_[PAD_(caddr_t)];
	size_t	len;	char len_[PAD_(size_t)];
	int	flags;	char flags_[PAD_(int)];
	struct sockaddr *	to;	char to_[PAD_(struct sockaddr *)];
	int	tolen;	char tolen_[PAD_(int)];
};
struct	linux_mkdir_args {
	char *	path;	char path_[PAD_(char *)];
	int	mode;	char mode_[PAD_(int)];
};
struct	linux_rmdir_args {
	char *	path;	char path_[PAD_(char *)];
};
struct	linux_getrlimit_args {
	u_int	resource;	char resource_[PAD_(u_int)];
	struct rlimit *	rlim;	char rlim_[PAD_(struct rlimit *)];
};
struct	linux_setrlimit_args {
	u_int	resource;	char resource_[PAD_(u_int)];
	struct rlimit *	rlim;	char rlim_[PAD_(struct rlimit *)];
};
struct	linux_quotactl_args {
	register_t dummy;
};
struct	osf1_sigaction_args {
	int	sig;	char sig_[PAD_(int)];
	struct osf1_sigaction *	nsa;	char nsa_[PAD_(struct osf1_sigaction *)];
	struct osf1_sigaction *	osa;	char osa_[PAD_(struct osf1_sigaction *)];
};
struct	linux_msgctl_args {
	int	arg1;	char arg1_[PAD_(int)];
	int	arg2;	char arg2_[PAD_(int)];
	caddr_t	ptr;	char ptr_[PAD_(caddr_t)];
};
struct	linux_msgget_args {
	int	arg1;	char arg1_[PAD_(int)];
	int	arg2;	char arg2_[PAD_(int)];
};
struct	linux_msgrcv_args {
	int	arg1;	char arg1_[PAD_(int)];
	caddr_t	ptr;	char ptr_[PAD_(caddr_t)];
	size_t	arg2;	char arg2_[PAD_(size_t)];
	long	arg3;	char arg3_[PAD_(long)];
	int	arg4;	char arg4_[PAD_(int)];
};
struct	linux_msgsnd_args {
	int	arg1;	char arg1_[PAD_(int)];
	caddr_t	ptr;	char ptr_[PAD_(caddr_t)];
	size_t	arg2;	char arg2_[PAD_(size_t)];
	long	arg3;	char arg3_[PAD_(long)];
	int	arg4;	char arg4_[PAD_(int)];
};
struct	linux_semctl_args {
	int	arg1;	char arg1_[PAD_(int)];
	int	arg2;	char arg2_[PAD_(int)];
	int	arg3;	char arg3_[PAD_(int)];
	caddr_t	ptr;	char ptr_[PAD_(caddr_t)];
};
struct	linux_semget_args {
	int	arg1;	char arg1_[PAD_(int)];
	int	arg2;	char arg2_[PAD_(int)];
	int	arg3;	char arg3_[PAD_(int)];
};
struct	linux_semop_args {
	int	arg1;	char arg1_[PAD_(int)];
	caddr_t	ptr;	char ptr_[PAD_(caddr_t)];
	int	arg2;	char arg2_[PAD_(int)];
};
struct	linux_lchown_args {
	char *	path;	char path_[PAD_(char *)];
	int	uid;	char uid_[PAD_(int)];
	int	gid;	char gid_[PAD_(int)];
};
struct	linux_shmat_args {
	int	arg1;	char arg1_[PAD_(int)];
	caddr_t	ptr;	char ptr_[PAD_(caddr_t)];
	int	arg2;	char arg2_[PAD_(int)];
	caddr_t	arg3;	char arg3_[PAD_(caddr_t)];
};
struct	linux_shmctl_args {
	int	arg1;	char arg1_[PAD_(int)];
	int	arg2;	char arg2_[PAD_(int)];
	caddr_t	ptr;	char ptr_[PAD_(caddr_t)];
};
struct	linux_shmdt_args {
	caddr_t	ptr;	char ptr_[PAD_(caddr_t)];
};
struct	linux_shmget_args {
	int	arg1;	char arg1_[PAD_(int)];
	size_t	arg2;	char arg2_[PAD_(size_t)];
	int	arg3;	char arg3_[PAD_(int)];
};
struct	linux_msync_args {
	caddr_t	addr;	char addr_[PAD_(caddr_t)];
	int	len;	char len_[PAD_(int)];
	int	fl;	char fl_[PAD_(int)];
};
struct	linux_getpgid_args {
	int	pid;	char pid_[PAD_(int)];
};
struct	linux_getsid_args {
	linux_pid_t	pid;	char pid_[PAD_(linux_pid_t)];
};
struct	osf1_sysinfo_args {
	int	cmd;	char cmd_[PAD_(int)];
	char *	buf;	char buf_[PAD_(char *)];
	long	count;	char count_[PAD_(long)];
};
struct	linux_sysfs_args {
	int	option;	char option_[PAD_(int)];
	u_long	arg1;	char arg1_[PAD_(u_long)];
	u_long	arg2;	char arg2_[PAD_(u_long)];
};
struct	osf1_getsysinfo_args {
	u_long	op;	char op_[PAD_(u_long)];
	caddr_t	buffer;	char buffer_[PAD_(caddr_t)];
	u_long	nbytes;	char nbytes_[PAD_(u_long)];
	caddr_t	arg;	char arg_[PAD_(caddr_t)];
	u_long	flag;	char flag_[PAD_(u_long)];
};
struct	osf1_setsysinfo_args {
	u_long	op;	char op_[PAD_(u_long)];
	caddr_t	buffer;	char buffer_[PAD_(caddr_t)];
	u_long	nbytes;	char nbytes_[PAD_(u_long)];
	caddr_t	arg;	char arg_[PAD_(caddr_t)];
	u_long	flag;	char flag_[PAD_(u_long)];
};
struct	linux_afs_syscall_args {
	register_t dummy;
};
struct	linux_bdflush_args {
	register_t dummy;
};
struct	linux_mount_args {
	char *	specialfile;	char specialfile_[PAD_(char *)];
	char *	dir;	char dir_[PAD_(char *)];
	char *	filesystemtype;	char filesystemtype_[PAD_(char *)];
	u_long	rwflag;	char rwflag_[PAD_(u_long)];
	void *	data;	char data_[PAD_(void *)];
};
struct	linux_swapoff_args {
	register_t dummy;
};
struct	linux_getdents_args {
	int	fd;	char fd_[PAD_(int)];
	void *	dent;	char dent_[PAD_(void *)];
	unsigned	count;	char count_[PAD_(unsigned)];
};
struct	linux_create_module_args {
	register_t dummy;
};
struct	linux_init_module_args {
	register_t dummy;
};
struct	linux_delete_module_args {
	register_t dummy;
};
struct	linux_get_kernel_syms_args {
	register_t dummy;
};
struct	linux_ksyslog_args {
	int	what;	char what_[PAD_(int)];
};
struct	linux_reboot_args {
	int	magic1;	char magic1_[PAD_(int)];
	int	magic2;	char magic2_[PAD_(int)];
	int	opt;	char opt_[PAD_(int)];
};
struct	linux_clone_args {
	int	flags;	char flags_[PAD_(int)];
	void *	stack;	char stack_[PAD_(void *)];
};
struct	linux_uselib_args {
	char *	library;	char library_[PAD_(char *)];
};
struct	linux_sysinfo_args {
	register_t dummy;
};
struct	linux_sysctl_args {
	register_t dummy;
};
struct	linux_idle_args {
	register_t dummy;
};
struct	linux_umount_args {
	char *	path;	char path_[PAD_(char *)];
};
struct	linux_times_args {
	struct linux_times_argv *	buf;	char buf_[PAD_(struct linux_times_argv *)];
};
struct	linux_personality_args {
	int	per;	char per_[PAD_(int)];
};
struct	linux_setfsuid_args {
	linux_uid_t	uid;	char uid_[PAD_(linux_uid_t)];
};
struct	linux_setfsgid_args {
	linux_gid_t	gid;	char gid_[PAD_(linux_gid_t)];
};
struct	linux_ustat_args {
	linux_dev_t	dev;	char dev_[PAD_(linux_dev_t)];
	struct linux_ustat *	ubuf;	char ubuf_[PAD_(struct linux_ustat *)];
};
struct	linux_statfs_args {
	char *	path;	char path_[PAD_(char *)];
	struct linux_statfs_buf *	buf;	char buf_[PAD_(struct linux_statfs_buf *)];
};
struct	linux_fstatfs_args {
	int	fd;	char fd_[PAD_(int)];
	struct linux_statfs_buf *	buf;	char buf_[PAD_(struct linux_statfs_buf *)];
};
struct	linux_sched_setscheduler_args {
	pid_t	pid;	char pid_[PAD_(pid_t)];
	int	policy;	char policy_[PAD_(int)];
	const struct sched_param *	param;	char param_[PAD_(const struct sched_param *)];
};
struct	linux_sched_getscheduler_args {
	pid_t	pid;	char pid_[PAD_(pid_t)];
};
struct	linux_sched_get_priority_max_args {
	int	policy;	char policy_[PAD_(int)];
};
struct	linux_sched_get_priority_min_args {
	int	policy;	char policy_[PAD_(int)];
};
struct	linux_newuname_args {
	struct linux_newuname_t *	buf;	char buf_[PAD_(struct linux_newuname_t *)];
};
struct	linux_mremap_args {
	caddr_t	addr;	char addr_[PAD_(caddr_t)];
	u_long	old_len;	char old_len_[PAD_(u_long)];
	u_long	new_len;	char new_len_[PAD_(u_long)];
	u_long	flags;	char flags_[PAD_(u_long)];
};
struct	linux_nfsservctl_args {
	register_t dummy;
};
struct	linux_getresgid_args {
	linux_gid_t *	rgid;	char rgid_[PAD_(linux_gid_t *)];
	linux_gid_t *	egid;	char egid_[PAD_(linux_gid_t *)];
	linux_gid_t *	sgid;	char sgid_[PAD_(linux_gid_t *)];
};
struct	linux_query_module_args {
	register_t dummy;
};
struct	linux_prctl_args {
	register_t dummy;
};
struct	linux_pread_args {
	int	fd;	char fd_[PAD_(int)];
	char *	buf;	char buf_[PAD_(char *)];
	size_t	nbyte;	char nbyte_[PAD_(size_t)];
	off_t	offset;	char offset_[PAD_(off_t)];
};
struct	linux_pwrite_args {
	int	fd;	char fd_[PAD_(int)];
	const char *	buf;	char buf_[PAD_(const char *)];
	size_t	nbyte;	char nbyte_[PAD_(size_t)];
	off_t	offset;	char offset_[PAD_(off_t)];
};
struct	linux_rt_sigreturn_args {
	register_t dummy;
};
struct	linux_rt_sigaction_args {
	int	sig;	char sig_[PAD_(int)];
	linux_sigaction_t *	act;	char act_[PAD_(linux_sigaction_t *)];
	linux_sigaction_t *	oact;	char oact_[PAD_(linux_sigaction_t *)];
	size_t	sigsetsize;	char sigsetsize_[PAD_(size_t)];
};
struct	linux_rt_sigprocmask_args {
	int	how;	char how_[PAD_(int)];
	linux_sigset_t *	mask;	char mask_[PAD_(linux_sigset_t *)];
	linux_sigset_t *	omask;	char omask_[PAD_(linux_sigset_t *)];
	size_t	sigsetsize;	char sigsetsize_[PAD_(size_t)];
};
struct	linux_rt_sigpending_args {
	register_t dummy;
};
struct	linux_rt_sigtimedwait_args {
	register_t dummy;
};
struct	linux_rt_sigqueueinfo_args {
	register_t dummy;
};
struct	linux_rt_sigsuspend_args {
	linux_sigset_t *	newset;	char newset_[PAD_(linux_sigset_t *)];
	size_t	sigsetsize;	char sigsetsize_[PAD_(size_t)];
};
struct	linux_newselect_args {
	int	nfds;	char nfds_[PAD_(int)];
	fd_set *	readfds;	char readfds_[PAD_(fd_set *)];
	fd_set *	writefds;	char writefds_[PAD_(fd_set *)];
	fd_set *	exceptfds;	char exceptfds_[PAD_(fd_set *)];
	struct timeval *	timeout;	char timeout_[PAD_(struct timeval *)];
};
struct	linux_getitimer_args {
	u_int	which;	char which_[PAD_(u_int)];
	struct itimerval *	itv;	char itv_[PAD_(struct itimerval *)];
};
struct	linux_setitimer_args {
	u_int	which;	char which_[PAD_(u_int)];
	struct itimerval *	itv;	char itv_[PAD_(struct itimerval *)];
	struct itimerval *	oitv;	char oitv_[PAD_(struct itimerval *)];
};
struct	linux_utime_args {
	char *	fname;	char fname_[PAD_(char *)];
	struct linux_utimbuf *	times;	char times_[PAD_(struct linux_utimbuf *)];
};
struct	linux_wait4_args {
	int	pid;	char pid_[PAD_(int)];
	int *	status;	char status_[PAD_(int *)];
	int	options;	char options_[PAD_(int)];
	struct rusage *	rusage;	char rusage_[PAD_(struct rusage *)];
};
struct	linux_adjtimex_args {
	register_t dummy;
};
struct	linux_getcwd_args {
	char *	buf;	char buf_[PAD_(char *)];
	unsigned long	bufsize;	char bufsize_[PAD_(unsigned long)];
};
struct	linux_capget_args {
	register_t dummy;
};
struct	linux_capset_args {
	register_t dummy;
};
struct	linux_sendfile_args {
	register_t dummy;
};
int	linux_fork __P((struct proc *, struct linux_fork_args *));
int	osf1_wait4 __P((struct proc *, struct osf1_wait4_args *));
int	linux_link __P((struct proc *, struct linux_link_args *));
int	linux_unlink __P((struct proc *, struct linux_unlink_args *));
int	linux_chdir __P((struct proc *, struct linux_chdir_args *));
int	linux_mknod __P((struct proc *, struct linux_mknod_args *));
int	linux_chmod __P((struct proc *, struct linux_chmod_args *));
int	linux_chown __P((struct proc *, struct linux_chown_args *));
int	linux_brk __P((struct proc *, struct linux_brk_args *));
int	linux_lseek __P((struct proc *, struct linux_lseek_args *));
int	linux_umount2 __P((struct proc *, struct linux_umount2_args *));
int	linux_ptrace __P((struct proc *, struct linux_ptrace_args *));
int	linux_access __P((struct proc *, struct linux_access_args *));
int	linux_kill __P((struct proc *, struct linux_kill_args *));
int	linux_open __P((struct proc *, struct linux_open_args *));
int	osf1_sigprocmask __P((struct proc *, struct osf1_sigprocmask_args *));
int	linux_ioctl __P((struct proc *, struct linux_ioctl_args *));
int	linux_symlink __P((struct proc *, struct linux_symlink_args *));
int	linux_readlink __P((struct proc *, struct linux_readlink_args *));
int	linux_execve __P((struct proc *, struct linux_execve_args *));
int	linux_vfork __P((struct proc *, struct linux_vfork_args *));
int	linux_newstat __P((struct proc *, struct linux_newstat_args *));
int	linux_newlstat __P((struct proc *, struct linux_newlstat_args *));
int	linux_mmap __P((struct proc *, struct linux_mmap_args *));
int	linux_munmap __P((struct proc *, struct linux_munmap_args *));
int	linux_mprotect __P((struct proc *, struct linux_mprotect_args *));
int	linux_vhangup __P((struct proc *, struct linux_vhangup_args *));
int	linux_setgroups __P((struct proc *, struct linux_setgroups_args *));
int	linux_getgroups __P((struct proc *, struct linux_getgroups_args *));
int	linux_setpgid __P((struct proc *, struct linux_setpgid_args *));
int	osf1_setitimer __P((struct proc *, struct osf1_setitimer_args *));
int	linux_newfstat __P((struct proc *, struct linux_newfstat_args *));
int	linux_fcntl __P((struct proc *, struct linux_fcntl_args *));
int	osf1_select __P((struct proc *, struct osf1_select_args *));
int	osf1_socket __P((struct proc *, struct osf1_socket_args *));
int	linux_connect __P((struct proc *, struct linux_connect_args *));
int	osf1_sigreturn __P((struct proc *, struct osf1_sigreturn_args *));
int	osf1_sigsuspend __P((struct proc *, struct osf1_sigsuspend_args *));
int	osf1_gettimeofday __P((struct proc *, struct osf1_gettimeofday_args *));
int	osf1_getrusage __P((struct proc *, struct osf1_getrusage_args *));
int	linux_rename __P((struct proc *, struct linux_rename_args *));
int	linux_truncate __P((struct proc *, struct linux_truncate_args *));
int	osf1_sendto __P((struct proc *, struct osf1_sendto_args *));
int	linux_mkdir __P((struct proc *, struct linux_mkdir_args *));
int	linux_rmdir __P((struct proc *, struct linux_rmdir_args *));
int	linux_getrlimit __P((struct proc *, struct linux_getrlimit_args *));
int	linux_setrlimit __P((struct proc *, struct linux_setrlimit_args *));
int	linux_quotactl __P((struct proc *, struct linux_quotactl_args *));
int	osf1_sigaction __P((struct proc *, struct osf1_sigaction_args *));
int	linux_msgctl __P((struct proc *, struct linux_msgctl_args *));
int	linux_msgget __P((struct proc *, struct linux_msgget_args *));
int	linux_msgrcv __P((struct proc *, struct linux_msgrcv_args *));
int	linux_msgsnd __P((struct proc *, struct linux_msgsnd_args *));
int	linux_semctl __P((struct proc *, struct linux_semctl_args *));
int	linux_semget __P((struct proc *, struct linux_semget_args *));
int	linux_semop __P((struct proc *, struct linux_semop_args *));
int	linux_lchown __P((struct proc *, struct linux_lchown_args *));
int	linux_shmat __P((struct proc *, struct linux_shmat_args *));
int	linux_shmctl __P((struct proc *, struct linux_shmctl_args *));
int	linux_shmdt __P((struct proc *, struct linux_shmdt_args *));
int	linux_shmget __P((struct proc *, struct linux_shmget_args *));
int	linux_msync __P((struct proc *, struct linux_msync_args *));
int	linux_getpgid __P((struct proc *, struct linux_getpgid_args *));
int	linux_getsid __P((struct proc *, struct linux_getsid_args *));
int	osf1_sysinfo __P((struct proc *, struct osf1_sysinfo_args *));
int	linux_sysfs __P((struct proc *, struct linux_sysfs_args *));
int	osf1_getsysinfo __P((struct proc *, struct osf1_getsysinfo_args *));
int	osf1_setsysinfo __P((struct proc *, struct osf1_setsysinfo_args *));
int	linux_afs_syscall __P((struct proc *, struct linux_afs_syscall_args *));
int	linux_bdflush __P((struct proc *, struct linux_bdflush_args *));
int	linux_mount __P((struct proc *, struct linux_mount_args *));
int	linux_swapoff __P((struct proc *, struct linux_swapoff_args *));
int	linux_getdents __P((struct proc *, struct linux_getdents_args *));
int	linux_create_module __P((struct proc *, struct linux_create_module_args *));
int	linux_init_module __P((struct proc *, struct linux_init_module_args *));
int	linux_delete_module __P((struct proc *, struct linux_delete_module_args *));
int	linux_get_kernel_syms __P((struct proc *, struct linux_get_kernel_syms_args *));
int	linux_ksyslog __P((struct proc *, struct linux_ksyslog_args *));
int	linux_reboot __P((struct proc *, struct linux_reboot_args *));
int	linux_clone __P((struct proc *, struct linux_clone_args *));
int	linux_uselib __P((struct proc *, struct linux_uselib_args *));
int	linux_sysinfo __P((struct proc *, struct linux_sysinfo_args *));
int	linux_sysctl __P((struct proc *, struct linux_sysctl_args *));
int	linux_idle __P((struct proc *, struct linux_idle_args *));
int	linux_umount __P((struct proc *, struct linux_umount_args *));
int	linux_times __P((struct proc *, struct linux_times_args *));
int	linux_personality __P((struct proc *, struct linux_personality_args *));
int	linux_setfsuid __P((struct proc *, struct linux_setfsuid_args *));
int	linux_setfsgid __P((struct proc *, struct linux_setfsgid_args *));
int	linux_ustat __P((struct proc *, struct linux_ustat_args *));
int	linux_statfs __P((struct proc *, struct linux_statfs_args *));
int	linux_fstatfs __P((struct proc *, struct linux_fstatfs_args *));
int	linux_sched_setscheduler __P((struct proc *, struct linux_sched_setscheduler_args *));
int	linux_sched_getscheduler __P((struct proc *, struct linux_sched_getscheduler_args *));
int	linux_sched_get_priority_max __P((struct proc *, struct linux_sched_get_priority_max_args *));
int	linux_sched_get_priority_min __P((struct proc *, struct linux_sched_get_priority_min_args *));
int	linux_newuname __P((struct proc *, struct linux_newuname_args *));
int	linux_mremap __P((struct proc *, struct linux_mremap_args *));
int	linux_nfsservctl __P((struct proc *, struct linux_nfsservctl_args *));
int	linux_getresgid __P((struct proc *, struct linux_getresgid_args *));
int	linux_query_module __P((struct proc *, struct linux_query_module_args *));
int	linux_prctl __P((struct proc *, struct linux_prctl_args *));
int	linux_pread __P((struct proc *, struct linux_pread_args *));
int	linux_pwrite __P((struct proc *, struct linux_pwrite_args *));
int	linux_rt_sigreturn __P((struct proc *, struct linux_rt_sigreturn_args *));
int	linux_rt_sigaction __P((struct proc *, struct linux_rt_sigaction_args *));
int	linux_rt_sigprocmask __P((struct proc *, struct linux_rt_sigprocmask_args *));
int	linux_rt_sigpending __P((struct proc *, struct linux_rt_sigpending_args *));
int	linux_rt_sigtimedwait __P((struct proc *, struct linux_rt_sigtimedwait_args *));
int	linux_rt_sigqueueinfo __P((struct proc *, struct linux_rt_sigqueueinfo_args *));
int	linux_rt_sigsuspend __P((struct proc *, struct linux_rt_sigsuspend_args *));
int	linux_newselect __P((struct proc *, struct linux_newselect_args *));
int	linux_getitimer __P((struct proc *, struct linux_getitimer_args *));
int	linux_setitimer __P((struct proc *, struct linux_setitimer_args *));
int	linux_utime __P((struct proc *, struct linux_utime_args *));
int	linux_wait4 __P((struct proc *, struct linux_wait4_args *));
int	linux_adjtimex __P((struct proc *, struct linux_adjtimex_args *));
int	linux_getcwd __P((struct proc *, struct linux_getcwd_args *));
int	linux_capget __P((struct proc *, struct linux_capget_args *));
int	linux_capset __P((struct proc *, struct linux_capset_args *));
int	linux_sendfile __P((struct proc *, struct linux_sendfile_args *));

#ifdef COMPAT_43


#endif /* COMPAT_43 */

#undef PAD_

#endif /* !_LINUX_SYSPROTO_H_ */
