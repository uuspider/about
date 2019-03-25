/* P20, 1.6, 2019.03.25
 * more02.c - v0.2 of more
 * read and print 24 lines then pause for a few special commands
 * feature of v0.2: read from /dev/tty for commands
 */
#include <stdio.h> // man stdio
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE *);
int see_more(FILE *);
int main(int ac, char *av[]) {
    FILE *fp;
    if (ac == 1)          // ac: num of arguments, test: printf("%d\n", ac)
        do_more(stdin);   // read stdin
    else
        while(--ac)
        if ((fp = fopen(* ++av, "r")) != NULL) {
            // FILE *fopen(const char *filename, const char *mode)
            do_more(fp);
            fclose(fp);
        }
        else
            exit(1);
    return 0;
}

void do_more(FILE *fp) {
/* read PAGELEN lines, then call see_more() for further instructions */
    char line[LINELEN];
    int num_of_lines = 0;
    int see_more(), reply;
    FILE *fp_tty;
    fp_tty = fopen("/dev/tty","r");    // NEW: cmd stream
    if (fp_tty == NULL)                // if open fails
        exit(1);                       // no use in running
    while (fgets(line, LINELEN, fp)) { // more input
            // char *fgets(char *s, int n, FILE *stream)
        if (num_of_lines == PAGELEN) { // full screen
            reply = see_more(fp_tty);  // NEW: pass FILE 
            if (reply == 0)            // n: done
                break;
            num_of_lines -= reply;     // reset count
        }
        if (fputs(line,stdout) == EOF) // show line
            // int fputs(const char *s, FILE *stream)
            exit(1);                   // or die
        num_of_lines++;                // count it
    }
}

int see_more(FILE *cmd) {              // NEW: accepts arg
/* print message, wait for response, return # of lines to advance
 * q means no, space means yes, CR means one_line */
    int c;
    printf("\033[7m more? \33[m");     // reverse on a vt100
    while((c = getc(cmd)) != EOF) { // NEW: read from tty
            // int getc(FILE *steam)
        if (c == 'q')                  // q -> N
            return 0;
        if (c == ' ')                  // ' ' => next page
            return PAGELEN;            // how many to show
        if (c == '\n')                 // Enter key => 1 line
            return 1;
    }
    return 0;
}
