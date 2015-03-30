#include <stdio.h>

#define MAXLINE 1000

int my_strlen(char s[]);

int main()
{
    int i, c;
    char input[MAXLINE];
    
    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && i != '\n'; ++i)
        input[i] = c;
    if (c == '\n') {
        input[i] = c;
        ++i;
    }
    input[i] = '\0';
    
    printf("%d\n", strlen(input));
    printf("%s\n", input); 
    return 0;
}

int my_strlen(char s[])
{
    int i;
    
    i = 0;
    while (s[i] != '\0')
        ++i;
    return i;
}