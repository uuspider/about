/* P114, 4.5.2, 2019.03.31
 * spwd.c: a simplified version of pwd
 * starts in current directory and recursively
 * climbs up to root of filesystem, prints top part
 * then prints current part
 * 
 * uses readdir() to get info about each thing
 * 
 * bug: prints an empty string if run from "/"
 */
/* 
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t, char *, int);

int main()
{
    printpathto(get_inode("."));
    putchar('\n');
    return 0;
}

void printpathto(ino_t this_inode)
{
    ino_t my_inode;
    char its_name[BUFSIZ];
    if (get_inode(".") != this_inode)
    {
        chdir("..");
        inum_to_name(this_inode, its_name, BUFSIZ);
        my_inode = get_inode(".");
        printpathto(my_inode);
        printf("/%s", its_name);
    }
}

void inum_to_name(ino_t inode_to_find, char * namebuf, int buflen)
{
    DIR *dir_prt;
    struct dirent *direntp;
    dir_prt = opendir(".");
    if (dir_ptr == NULL) {
        perror(".");
        exit(1);
    }
