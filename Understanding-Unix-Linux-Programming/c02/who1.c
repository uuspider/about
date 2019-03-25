/* P36, 2.5.3, 2.5.4, 2019.03.25
 * who1.c - v1 of the who program
 * open, read UTMP file, and show results
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
