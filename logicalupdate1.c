#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

int execute_command(char **args) {
  char *env = getenv("PATH");
  char *path = strtok(env, ":");

  while (path != NULL) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s/%s", path, args[0]);
    execve(buffer, args, environ);
    path = strtok(NULL, ":");
  }

  perror(args[0]);
  exit(1);
}

int main(int argc, char *argv[]) {
  char *args[100];
  char *token;
  char *cmd = NULL;
  char *oldpwd;
  size_t size = 0;
  int i = 0;
  char s[100];
  int status;

  while (1) {
    write(STDOUT_FILENO, "#cisfun$ ", 9);
    getline(&cmd, &size, stdin);

    if (feof(stdin)) {
      break;
    }

    token = strtok(cmd, " \n");

    while (token != NULL) {
      args[i++] = token;
      token = strtok(NULL, " \n");
    }

    args[i] = NULL;

    int is_background = 0;

    for (int j = 0; args[j] != NULL; j++) {
      if (strcmp(args[j], "&&") == 0) {
        args[j] = NULL;
        execute_command(args);

        int pid = fork();
        if (pid < 0) {
          perror("fork");
          exit(1);
        } else if (pid == 0) {
          args = args + j + 1;
          execute_command(args);
        } else {
          waitpid(pid, &status, 0);
          if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            exit(1);
          }
          break;
        }
      } else if (strcmp(args[j], "||") == 0) {
        args[j] = NULL;
        execute_command(args);

        int pid = fork();
        if (pid < 0) {
          perror("fork");
          exit(1);
        } else if (pid == 0) {
          args = args + j + 1;
          execute_command(args);
        } else {
          waitpid(pid, &status, 0);
          if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            exit(0);
          }
          break;
        }
      }
    }

    if (args[0] != NULL) {
      int pid = fork();

      if (pid < 0) {
        perror("fork");
        exit(1);
      } else if (pid == 0) {
        execute_command(args);
      } else {
        if (!is_background) {
          waitpid(pid, &status, 0);
        }
      }
    }

    i = 0;
  }

  free(cmd);
  return (0);
}
