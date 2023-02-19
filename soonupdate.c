#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

extern char **environ;

int execute_command(char *command)
{
  char *args[1024];
  char *token = strtok(command, " \n");
  int i = 0;

  while (token != NULL)
  {
    args[i++] = token;
    token = strtok(NULL, " \n");
  }

  args[i] = NULL;

  pid_t pid = fork();

  if (pid < 0)
  {
    perror("");
  }
  else if (pid == 0)
  {
    char *env = getenv("PATH");
    char *path = strtok(env, ":");

    while (path != NULL)
    {
      char buffer[100];
      snprintf(buffer, sizeof(buffer), "%s/%s", path, args[0]);
      execve(buffer, args, environ);
      path = strtok(NULL, ":");
    }
    exit(1);
  }
  else
    wait(NULL);
}

int main(int argc, char *argv[])
{
  char *cmd = NULL;
  size_t size = 0;
  char *args[1024];
  int i = 0;

  while (1)
  {

    write(STDOUT_FILENO, "#cisfun$ ", 9);
    if (getline(&cmd, &size, stdin) == -1)
    {
      break;
    }

    char *command = strtok(cmd, ";");

    while (command != NULL)
    {
      args[i++] = command;
      command = strtok(NULL, ";");
    }
    
    int num_commands = i;
    
    for (i = 0; i < num_commands; i++)
    {
      if (args[i] != NULL)
      {
        execute_command(args[i]);
      }
    }
    
    i = 0;
  }

  free(cmd);
  return 0;
}
