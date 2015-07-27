#include<stdio.h>
#include<stdlib.h>
#include "mpc.h"

//for windows platform
#ifdef _WIN32
#include  <string.h>

//add fake readline function
char* readline(char* prompt)
{
	fputs(prompt,stdout);
	fgets(buffer,2048,stdin);
	char* cpy = malloc(strelen(buffer)+1);
	strcpy(cpy,buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy;
}
//windows already has history support
void add_histoy(char* unused);
#else
#include<editline/readline.h>
#include<editline/history.h>
#endif
static char input[2048];

int main(int argc, char **argv)
{
	/*Create some parsers*/
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator =  mpc_new("operator");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");
	
	mpca_lang(MPCA_LANG_DEFAULT,
	"								\
									\
	number		: /-?[0-9]+/ ;					\
	operator 	: '+' | '-' | '*' | '/' ;			\
	expr		: <number> | '(' <operator> <expr>+ ')' ;	\
	lispy		: /^/ <operator> <expr>+ /$/ ;			\
	",
Number,Operator,Expr,Lispy);
	

	puts("Lispy version 0.0.0.1");
	puts("Press ctrl+c to Exit\n");
	while(1)
	{
		char *input=readline("xlisp> ");
		add_history(input);
		mpc_result_t r;
		if(mpc_parse("<stdin>",input,Lispy,&r))
		{
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);			
		}else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		//printf("%s\n",input);
		free(input);
	}

mpc_cleanup(4,Number,Operator,Expr,Lispy);
return 0;

}
