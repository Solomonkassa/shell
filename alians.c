#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIAS 100
#define MAX_CMD_LEN 100

typedef struct {
    char* name;
    char* value;
} Alias;

Alias aliases[MAX_ALIAS];
int num_aliases = 0;

void print_aliases() {
    for (int i = 0; i < num_aliases; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void print_alias(char* name) {
    for (int i = 0; i < num_aliases; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
    fprintf(stderr, "alias: %s: not found\n", name);
}

void set_alias(char* name, char* value) {
    for (int i = 0; i < num_aliases; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            free(aliases[i].value);
            aliases[i].value = strdup(value);
            return;
        }
    }
    if (num_aliases >= MAX_ALIAS) {
        fprintf(stderr, "alias: too many aliases defined\n");
        return;
    }
    aliases[num_aliases].name = strdup(name);
    aliases[num_aliases].value = strdup(value);
    num_aliases++;
}

void unset_alias(char* name) {
    int found = 0;
    for (int i = 0; i < num_aliases; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            free(aliases[i].name);
            free(aliases[i].value);
            num_aliases--;
            found = 1;
        }
        if (found && i < num_aliases) {
            aliases[i] = aliases[i+1];
        }
    }
    if (!found) {
        fprintf(stderr, "alias: %s: not found\n", name);
    }
}

void handle_alias(int argc, char** argv) {
    if (argc == 1) {
        print_aliases();
        return;
    }
    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];
        char* equals = strchr(arg, '=');
        if (equals == NULL) {
            print_alias(arg);
        } else {
            *equals = '\0';
            set_alias(arg, equals+1);
        }
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "alias: not enough arguments\n");
        return 1;
    }
    handle_alias(argc, argv);
    return 0;
}
