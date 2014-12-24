#include "mpc.h"

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
#include <editline/readline.h>
#include <histedit.h>
#endif


/*use operator string to see which operation to perform*/
long eval_op(long x, char* op, long y) {
	if (strcmp(op, "+") == 0) { return x + y; }
	if (strcmp(op, "-") == 0) { return x - y; }
	if (strcmp(op, "*") == 0) { return x * y; }
	if (strcmp(op, "/") == 0) { return x / y; }
	return 0;
}


long eval(mpc_ast_t* t) {
	
	/*if tagged as a number return it directly*/
	if (strstr(t->tag, "number")) {
		return atoi(t->contents);
	}
	
	/*the operator is always second child*/
	char* op = t->children[1]->contents;
	
	/*we store the third child in 'x' */
	long x = eval(t->children[2]);
	
	/*iterate the remaining children and combining*/
	int i = 3;
	while (strstr(t->children[i]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[i]));
		i++;
	}
	return x;
}


int main(int argc, char** argv) {
    
    /*Create some parsers*/
    mpc_parser_t* Number    = mpc_new("number");
    mpc_parser_t* Operator  = mpc_new("operator");
    mpc_parser_t* Expr      = mpc_new("expr");
    mpc_parser_t* Lispy     = mpc_new("lispy");

    /*Define them with the following language*/
    mpca_lang(MPCA_LANG_DEFAULT,                    
      "                                                     \
        number   : /-?[0-9]+/ ;                             \
        operator : '+' | '-' | '*' | '/' ;                  \
        expr     : <number> | '(' <operator> <expr>+ ')' ;  \
        lispy    : /^/ <operator> <expr>+ /$/ ;             \
      ",
      Number, Operator, Expr, Lispy);


    /*print version and exit info*/
    puts("Lispy Version 0.0.0.0.3");
    puts("Press Ctrl-c to exit\n");
    
    /*never ending loop*/
    while (1) {
        
        char* input = readline("lispy> ");
        add_history(input);
        
        /*Attempt to parse user input*/
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            
            long result = eval(r.output);
            printf("%li\n", result);
            mpc_ast_delete(r.output);
            
        } else {
            /*otherwise print the error*/
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        
        free(input);
    }

    /*Undefine and Delete our Parsers*/
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}
