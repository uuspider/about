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

