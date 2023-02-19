#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

int execute_command(char *command)
{
  char *args[100];
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
    perror("fork");
    return 1;
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

    fprintf(stderr, "%s: %s\n", args[0], strerror(errno));
    exit(1);
  } 
  else 
  {
    
    wait(&pid);

    
  }
}

int main(int argc, char *argv[])
{
  char *cmd = NULL;
  size_t size = 0;
  char *args[1024];
  int i = 0 ;

  while (1)
  {

    write (STDOUT_FILENO,"#cisfun$ ",9);
    if (getline(&cmd, &size, stdin) == -1) 
    {
      break;
    }

    char *command = strtok(cmd, ";");

    
    while (command != NULL )
      {
      args[i++] = command;
       
      command = strtok(NULL, ";");
    }
   if (args[0] != NULL)
   {
      execute_command(args[0]);
      
   }
   if (args[1] != NULL)
   {
     execute_command(args[1]);
     
   }
    i = 0;
  }

  free(cmd);
  return 0;
}
