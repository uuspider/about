/* P46, 2.6.3, 2019.03.27
 * cp1.c - v1 of cp
 * - uses read and write with tunable buffer size
 * usage: cp1 src dest
 */
/*
 *     open sourcefile for reading
 *     open copyfile for writing
 *  +->read from source to buffer   -- EOF?  -+
 *  |__write from buffer to copy              |
 *     close sourcefile  <--------------------|
 *     close copyfile
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   // int fd = creat(char *filename, mode_t mode)
#include <unistd.h>  // ssize_t result = write(int fd, void *buf, size_t amt)

#define BUFFERSIZE 4096
#define COPYMODE   0644

void oops(char *, char *);

main(int ac, char *av[]) {
    int   in_fd, out_fd, n_chars;
    char  buf[BUFFERSIZE];
    // check args
    if(ac!=3) {
        fprintf(stderr, "usage: %s source destination\n", *av);
        exit(1);
    }
    // open files
    if((in_fd=open(av[1],O_RDONLY))==-1)
        oops("Cannot open", av[1]);
    
    if((out_fd=creat(av[2],COPYMODE))==-1)
        oops("Cannot creat", av[2]);
    // copy files
    while((n_chars=read(in_fd, buf, BUFFERSIZE))>0)
        if(write(out_fd,buf,n_chars)!=n_chars)
            oops("Write error to", av[2]);
    if(n_chars == -1)
        oops("Read error from", av[1]);
    // close files
    if(close(in_fd)==-1 || close(out_fd)==-1)
        oops("Error closing files", "");
}

void oops(char *s1, char *s2) {
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(1);
}
