#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main() {
  char command[MAX_COMMAND_LENGTH];
  char *args[MAX_ARGUMENTS];
  int status;

  while (1) {
    printf("$ ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    if (strcmp(command, "exit\n") == 0) {
      // exit command without arguments
      exit(0);
    }

    // split command into arguments
    int i = 0;
    args[i] = strtok(command, " \n");
    while (args[i] != NULL && i < MAX_ARGUMENTS - 1) {
      i++;
      args[i] = strtok(NULL, " \n");
    }
    args[i] = NULL;

    if (strcmp(args[0], "exit") == 0) {
      // exit command with argument
      status = atoi(args[1]);
      exit(status);
    }

    // execute command
    pid_t pid = fork();
    if (pid == 0) {
      // child process
      execvp(args[0], args);
      printf("Command not found\n");
      exit(1);
    } else if (pid > 0) {
      // parent process
      waitpid(pid, &status, 0);
    } else {
      // error
      printf("Fork failed\n");
    }
  }

  return 0;
}
