#include<stdio.h>
#include<stdlib.h>
#include<editline/readline.h>
#include<editline/history.h>

static char input[2048];

int main(int argc, char **argv)
{
	puts("Lispy version 0.0.0.1");
	puts("Press ctrl+c to Exit\n");
	while(1)
	{
		char *input=readline("lispy> ");
add_history(input);
printf("%s Welcome to Lisp Interpreter Version 0.0.0.1.\nType help for List of commands.\n",input);
free(input);

	}
return 0;
}
