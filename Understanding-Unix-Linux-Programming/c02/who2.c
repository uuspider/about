/* P41, 2.5.5, 2019.03.26
 * who2.c - v2 of the who program
 * - read /etc/utmp and list info therein
 * - suppresses empty records
 * - formats time nicely
 */
/*
 * $ man 5 utmp
 * ...
 *           // Values for ut_type field, below 
 * ...
 *           #define USER_PROCESS  7 // Normal process 
 * ...
 * $ man -k time | grep transform
 * asctime (3)          - transform date and time to broken-down time or ASCII
 * asctime_r (3)        - transform date and time to broken-down time or ASCII
 * ctime (3)            - transform date and time to broken-down time or ASCII
 * ctime_r (3)          - transform date and time to broken-down time or ASCII
 * ...
 * $ man 3 asctime
 * ...
 *            #include <time.h>
 * ...
 *            The ctime(), gmtime() and localtime() functions all take an argument of data type time_t,  which  represents  calendar  time.
 *            When  interpreted as an absolute time value, it represents the number of seconds elapsed since the Epoch, 1970-01-01 00:00:00
 *            +0000 (UTC).
 * ...
 *            The  call  ctime(t) is equivalent to asctime(localtime(t)).  It converts the calendar time t into a null-terminated string of
 *            the form
 *                 "Wed Jun 30 21:49:08 1993\n"
 * ...
 * $ man 3 ctime
 * ...
 *            char *ctime(const time_t *timep);
 * ...
 */
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>    // man utmp.h; man -k utmp
#include <fcntl.h>   // int fd = open(char *name, int how)
#include <unistd.h>  // ssize_t numread = read(int fd, void *buf, size_t qty)
#include <time.h>    // char *ctime(const time_t *timep);

// #define SHOWHOST     // include remote machine on output

void showtime(long);
void show_info(struct utmp *);

int main() {
    struct utmp  utbuf;            // read info into here
    int          utmpfd;           // read from this descriptor

    if (( utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);         // UTMP_FILE is in utmp.h
        // void perror(const char *s)
        // similar as: fprintf(stderr, "%s: %s\n", s, "error message")
        exit(1);
    }

    while (read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
        show_info(&utbuf);
    close(utmpfd);
    return 0;                      // went ok
}

void show_info(struct utmp *utbufp) {
/* displays contents of the utmp struct in human readable form
 * displays nothing if record has no user name
 * * note * these sizes should not be hardwired
 */
    if (utbufp->ut_type != USER_PROCESS)
        return;
    printf("%-8.8s", utbufp->ut_name);   // the logname
    printf(" ");                         // a space
    printf("%-8.8s", utbufp->ut_line);   // the tty
    printf(" ");                         // a space
    showtime(utbufp->ut_time);           // display time
   #ifdef SHOWHOST
   if (utbufp->ut_host[0] != '\0')
        printf("(%s)", utbufp->ut_host); // the host
   #endif
    printf("\n");                        // newline
}

void showtime(long timeval) {
/* displays time in a format fit for human consumption
 * uses ctime to build a string then picks parts out of it 
 * NOTE: %12.12s prints a string 12 chars wide and LIMITS it to 12 chars.
 */
    char *cp;                            // to hold address of time
    cp = ctime(&timeval);                // convert time to string
    printf("%12.12s", cp+4);             // pick 12 chars from pos 4
}
