#include <stdio.h>

#define MAXLINE 1000

int getaline(char line[], int max)
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

main()
{
    char line[MAXLINE];
    int found = 0;
    
    while (getaline(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    return found;
}

int getaline(char string[], int limit)
{
    int chr, itr;
    
    itr = 0;
    while (--limit > 0 && (chr = getchar()) != EOF && chr != '\n')
        string[iter++] = c;
    if (c == '\n')
        string[iter++] = c;
    string[i] = '\0';
    return i;
}