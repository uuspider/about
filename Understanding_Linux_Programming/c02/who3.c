/* P52, 2.7.4, 2019.03.27
 * who3.c - v3 of the who program
 * - with buffered reads
 * - formats time nicely
 * - buffers input (using utmplib)
 */
/*
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>    // man utmp.h; man -k utmp
#include <fcntl.h>   // int fd = open(char *name, int how)
#include <unistd.h>  // ssize_t numread = read(int fd, void *buf, size_t qty)
#include <time.h>    // char *ctime(const time_t *timep);
#include <sys/types.h>

#define SHOWHOST     // include remote machine on output

void showtime(time_t);
void show_info(struct utmp *);

/* start: utmplib */
/* utmplib - functions to buffer reads utmp file
 * - reads NRECS per read and then doles them out from the buffer
 */

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

static char  utmpbuf[NRECS * UTSIZE];  // storage
static int   num_recs;                 // num stored
static int   cur_rec;                  // next to go
static int   fd_utmp = -1;             // read from

int utmp_reload();

int utmp_open(char *filename) {     // open file, returns -1 on error
    fd_utmp = open(filename, O_RDONLY);  // open it
    cur_rec = num_recs = 0;              // no recs yet
    return fd_utmp;                      // report
}

struct utmp *utmp_next() {     // return pointer to next struct, returns NULL on eof
    struct utmp *recp;
    if (fd_utmp == -1)         // error?
        return NULLUT;
    if (cur_rec == num_recs && utmp_reload() == 0)
        return NULLUT;         // any more?
    // get address of next record
    recp = (struct utmp *) &utmpbuf[cur_rec * UTSIZE];
    cur_rec++;
    return recp;
}

int utmp_reload() {    // read next bunch of records into buffer
    int amt_read;      // read them in
    amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);  // how many did we get?
    num_recs = amt_read/UTSIZE;    // reset pointer
    cur_rec = 0;
        return num_recs;
}

int utmp_close() {     // close file
    if (fd_utmp != -1)     // don't close if not open
        close(fd_utmp);
}


/* end: utmplib */

int main() {
    struct utmp  *utbufp,            // holds pointer to next rec
                 *utmp_next();       // return pointer to next

    if ( utmp_open(UTMP_FILE) == -1) {
        perror(UTMP_FILE);         // UTMP_FILE is in utmp.h
        // void perror(const char *s)
        // similar as: fprintf(stderr, "%s: %s\n", s, "error message")
        exit(1);
    }

    while ((utbufp = utmp_next()) != ((struct utmp *)NULL))
        show_info(utbufp);
    utmp_close();
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
