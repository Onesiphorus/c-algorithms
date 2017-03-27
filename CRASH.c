/* Paul Bagley
 * CSCI 4100
 * Programming Assignment 3
 * The Command Resolution and Activation SHell (aka CRASH)
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 256
#define MAX_ARGS 64

int is_blank(const char *cmd);
void parse_args(const char *cmd, char *argv[]);
void read_line(char *line);

/* main function for the CRASH shell program. */
int main()
{
  char input[MAX_LINE];
  char **args;
  pid_t pid;//process id
  printf("$ ");
  read_line(input);//reads input from keyboard
  args = malloc(MAX_ARGS*(sizeof(char)));//dynamically allocates the array
  while(strcmp("exit",input) != 0){
	  if(is_blank(input)){//checks to see if input is empty
		  printf("Please input a command or type exit to quit.\n");
	  }
	  else {
		  parse_args(input, args);
		  pid = fork();//checks the id
		  if (pid < 0){
			//printf(stderr, "Error!");  
		  }
		  else if (pid > 0){//pauses the parent process
			  wait(NULL);
		  }
		  else if (pid == 0){//executes the child process
			  execvp(args[0], args);
			  printf("error, command %s not found.\n", input);
			  exit(EXIT_FAILURE);
		  }
	  }
	  printf("$ ");
	  read_line(input);
  }
  //deallocates args
  printf("[exiting crash shell]\n");
  return 0;
}

/* determines if a command line is empty or made up of only whitespace.
 * cmd: the command line string
 * returns 1 (true) if cmd is blank and 0 (false) otherwise. 
 */
int is_blank(const char *cmd)
{
  int i = 0;
  while(cmd[i] != '\0') {
    if(!isspace(cmd[i++]))
      return 0;
  }
  return 1;
}

/* reads a line frome the terminal into a buffer
 * line: a pre-allocated array of characters of size MAX_LINE
 */
void read_line(char *line)
{
  char c;
  int chars_read = 0;
  while((c = getchar()) != '\n' && chars_read < MAX_LINE)
    line[chars_read++] = c;
  line[chars_read] = '\0';
}

/* breaks up a command line into a command and its arguments
 * cmd: the string containing the command line
 * argv: a pre-allocated array of strings of size MAX_ARGS
 * note that the array argv must be allocated, but the individual strings
 * are dynamically allocated by parse_args
 */
void parse_args(const char *cmd, char *argv[])
{ 
  int argc = 0;
  while(*cmd != '\0' && argc < MAX_ARGS) {
    int i = 0;
    while(!isspace(cmd[i]) && cmd[i] != '\0') i++;
    argv[argc] = (char *) malloc(i + 1);
    strncpy(argv[argc], cmd, i);
    while(isspace(cmd[i])) i++;
    cmd += i;
    argc++;
  }
  if(argc < MAX_ARGS)
    argv[argc] = NULL;
  else
    argv[MAX_ARGS - 1] = NULL;
}
