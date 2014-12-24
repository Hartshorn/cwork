#include <stdio.h>
#include <stdlib.h>

/*if compiling on windows, compile these functions*/
#ifdef _WIN32
#include <string.h>


static char input[2048];

/*fake readline function*/
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

/*fake add_history function*/
void add_history(char* unused) {}

/*Otherwise include the editline headers*/
#else
//need to install this library - libedit-dev
//and link in the compilation -ledit flag
//Like this: gcc -std=c99 -Wall repl.c -ledit -o repl

#include <editline/readline.h>
#include <editline/history.h>
#endif


int main(int argc, char** argv) {
    
    /*print version and exit info*/
    puts("Lispy Version 0.0.0.0.1");
    puts("Press Ctrl-c to exit\n");
    
    /*never ending loop*/
    while (1) {
        
        /* print the propmt*/
        char* input = readline("lispy> ");
        
        /*get the user input*/
        add_history(input);
        
        /*echo it back*/
        printf("ECHO: %s\n", input);
        
        /*let it go free!*/
        free(input);
    }
    return 0;
}