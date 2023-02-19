#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

int execute(char **args, int should_wait) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("");
        return -1;
    }

    if (pid == 0) {
        char *env = getenv("PATH");
        char *path = strtok(env, ":");

        while (path != NULL) {
            char buffer[100];
            snprintf(buffer, sizeof(buffer), "%s/%s", path, args[0]);
            execve(buffer, args, environ);
            path = strtok(NULL, ":");
        }

        perror("");
        exit(1);
    }

    if (should_wait) {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    char *args[100];
    char *token;
    char *cmd = NULL;
    size_t size = 0;
    int i = 0;
    char s[100];
    int should_wait = 1;
    int result = 0;

    while (1) {
        write(STDOUT_FILENO, "#cisfun$ ", 9);
        getline(&cmd, &size, stdin);

        if (feof(stdin)) {
            break;
        }

        token = strtok(cmd, " \n");

        while (token != NULL) {
            if (strcmp(token, "&&") == 0) {
                should_wait = result == 0 ? 1 : 0;
                token = strtok(NULL, " \n");
                continue;
            } else if (strcmp(token, "||") == 0) {
                should_wait = result != 0 ? 1 : 0;
                token = strtok(NULL, " \n");
                continue;
            }

            args[i++] = token;
            token = strtok(NULL, " \n");
        }

        args[i] = NULL;

        result = execute(args, should_wait);
        should_wait = 1;
        i = 0;
    }

    free(cmd);
    return 0;
}
