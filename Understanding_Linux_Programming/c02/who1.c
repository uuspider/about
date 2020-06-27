/* P36, 2.5.3, 2.5.4, 2019.03.25
 * who1.c - v1 of the who program
 * open, read UTMP file, and show results
 */
/*
 * $ who
 * uuspider tty7         2019-03-23 22:49 (:0)
 * uuspider pts/20       2019-03-23 22:49 (Edge)
 * uuspider pts/6        2019-03-23 22:50 (Edge)
 * uuspider pts/2        2019-03-24 21:38 (Edge)
 * uuspider pts/21       2019-03-24 22:13 (Edge)
 * $ man who
 * ...
 *        If FILE is not specified, use /var/run/utmp.  /var/log/wtmp as FILE
 *        is common.  If ARG1 ARG2 given, -m presumed:  'am  i'  or
 *        'mom likes' are usual.
 * ...
 * $ man -k utmp
 * ...
 * utmp (5)             - login records
 * ...
 * $ man 5 utmp
 * ...
 * struct utmp {
 *               short   ut_type;              // Type of record
 *               pid_t   ut_pid;               // PID of login process 
 *               char    ut_line[UT_LINESIZE]; // Device name of tty - "/dev/" 
 *               char    ut_id[4];             // Terminal name suffix, or inittab(5) ID
 *               char    ut_user[UT_NAMESIZE]; // Username 
 *               char    ut_host[UT_HOSTSIZE]; // Hostname for remote login, or
 *                                                kernel version for run-level
 *                                                messages 
 * ...
 * $ man -k file | grep read
 * ...
 * read (2)             - read from a file descriptor
 * ...
 * $ man 2 read
 * ...
 *     #include <unistd.h>
 * 
 *     ssize_t read(int fd, void *buf, size_t count);
 * ...
 * SEE ALSO
 *     close(2), fcntl(2), ioctl(2), lseek(2), open(2), pread(2), readdir(2), readlink(2), readv(2), select(2), write(2), fread(3)
 * ...
 * $ man 2 open
 * ...
 *     #include <fcntl.h>
 * ...
 *     int open(const char *pathname, int flags, mode_t mode);
 * ...
 * $ cat /usr/include/fcntl.h
 * ...
 * extern int open (const char *__file, int __oflag, ...) __nonnull ((1));
 * ...
 * $ man 2 close
 * ...
 *     #include <unistd.h>
 * 
 *     int close(int fd);
 * ...
 */
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>    // man utmp.h; man -k utmp
#include <fcntl.h>   // int fd = open(char *name, int how)
#include <unistd.h>  // ssize_t numread = read(int fd, void *buf, size_t qty)

#define SHOWHOST     // include remote machine on output

int show_info(struct utmp *utbufp);

int main() {
    struct utmp  current_record;   // read info into here
    int          utmpfd;           // read from this descriptor
    int          reclen = sizeof(current_record);

    if (( utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);         // UTMP_FILE is in utmp.h
        // void perror(const char *s)
        // similar as: fprintf(stderr, "%s: %s\n", s, "error message")
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen)
        show_info(&current_record);
    close(utmpfd);
    return 0;                      // went ok
}

int show_info(struct utmp *utbufp) {
/* displays contents of the utmp struct in human readable form
 * * note * these sizes should not be hardwired
 */
    printf("%-8.8s", utbufp->ut_name);   // the logname
    printf(" ");                         // a space
    printf("%-8.8s", utbufp->ut_line);   // the tty
    printf(" ");                         // a space
    printf("%10d", utbufp->ut_time);     // login time: x86 10ld; x64 10d
    printf(" ");                         // a space
   #ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);     // the host
   #endif
    printf("\n");                        // newline
}
