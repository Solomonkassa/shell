#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

int main() {
    char cmd[MAX_CMD_LEN];
    char* args[MAX_CMD_LEN];
    char* cmd_ptr;
    int status;

    while (1) {
        printf("Enter command: ");
        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL) {
            break;
        }

        // Replace newline character with null terminator
        cmd[strcspn(cmd, "\n")] = '\0';

        // Parse the command and its arguments
        int arg_count = 0;
        cmd_ptr = strtok(cmd, " ");
        while (cmd_ptr != NULL) {
            args[arg_count++] = cmd_ptr;
            cmd_ptr = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        // Execute each command separated by ";"
        cmd_ptr = strtok(cmd, ";");
        while (cmd_ptr != NULL) {
            // Execute the command
            if (fork() == 0) {
                execvp(args[0], args);
                perror(args[0]);
                exit(1);
            }
            // Wait for the child process to finish
            wait(&status);

            cmd_ptr = strtok(NULL, ";");
        }
    }

    return 0;
}
