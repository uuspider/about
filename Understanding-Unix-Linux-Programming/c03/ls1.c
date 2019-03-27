/* P69, 3.5, 2019.03.27
 * ls1.c
 * purpose list contents of directory or directories
 * action if no args, use . else list files in args
 */
/* $ man -k 'read directory'
 * readdir (2)          - read directory entry
 * $ man 2 readdir
 * ...Look at readdir(3) for the POSIX conforming C library interface....
 * $ man 3 readdir
 * ...
 * SEE ALSO
 *      getdents(2),read(2),closedir(3),dirfd(3),ftw(3),offsetof(3),opendir(3),rewinddir(3),scandir(3),seekdir(3),telldir(3)
 *...
 * $ man 3 closedir
 * $ man 3 opendir
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char []);

main(int ac, char *av[]) {
    if (ac == 1)
        do_ls(".");
    else
        while (--ac) {
            printf("%s:\n", *++av);
            do_ls(*av);
        }
}

void do_ls(char dirname[]) { // list files in directory called dirname
    DIR *dir_ptr;      // the directory
    struct dirent *direntp;  // each entry

    if ((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls1: cannot open %s\n", dirname);
    else {
        while((direntp = readdir(dir_ptr)) != NULL)
            printf("%s\n", direntp->d_name);
        closedir(dir_ptr);
    }
}
