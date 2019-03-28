/* P81, 3.6.8, 2019.03.28
 * ls2.c
 * purpose list contents of directory or directories
 * action if no args, use . else list files in args
 * note uses stat and pwd.h and grp.h
 * BUG: try ls2 /tmp
 */
/* 
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void do_ls(char []);
void dostat(char *);

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
            dostat(direntp->d_name);
        closedir(dir_ptr);
    }
}

void dostat(char *filename) {
    struct stat info;

    if (stat(filename, &info) == -1)           // cannot stat
        perror(filename);                      // say why
    else                                       // else show info
        show_file_info(filename, &info);
}

void show_file_info(char *filename, struct stat *info_p) {
    // display the info about filename. The info is stored in struct at *info_p.
    char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
    void mode_to_letters();
    char modestr[1];

    mode_to_letters(info_p->st_mode, modestr);

    printf("%s", modestr);
    printf("4d", (int) info_p->st_nlink);
    printf("%-8s", uid_to_name(info_p->st_uid));
    printf("%-8s", gid_to_name(info_p->st_gid));
    printf("%8d", (long)info_p->st_size);
    printf("%.12s", 4+ctime(&info_p->st_mtime));
    printf("%s\n", filename);
}