#include "main.h"

int main(int argc, char *argv[])
{
    char *token;
    char *why;
    char *token1 = NULL;
    char *token0 = NULL;
    char *s = malloc (80 * sizeof(char));
    int i = 0;
    char *u = getcwd(s, 80 * sizeof(char)) ;
    while (1)
    {
        printf("#cisfun$ ");
        why = _getline();

        if (feof(stdin))
        {
            free(why);
            exit(1);
        }

        token = _strtok(why, " ");

        if (_strcmp(token, "exit") == 0)
        {
            free(why);
            break;
        }

        i = 0;
        while (token != NULL && i < 2)
        {
           if (i == 0)
            {
            token0 = token;
            }
          if (i == 1)
            {
                token1 = token;
            }
            i++;
            token = _strtok(NULL, " ");
        } 
         if (_strcmp(token0,"rm") == 0)
         {
           pid_t pid4 = fork();
           
           if (pid4 == 0)
            {
           char *f[100] = {"/bin/rmdir",token1,NULL};
           execve (f[0],f,NULL);
           perror ("rm");
             exit (1);
             }
           else
             wait (NULL);
           continue;
         }
  
     char *cg = getcwd(s, 80 * sizeof(char)) ;
      
         
        if (_strcmp(token0, "cd") == 0)
        {
     

             chdir(token1);
            if (token1 == NULL)
            {
             chdir("/home");
            }
            if (strcmp(token1, "-") == 0)
            {
              getenv("OLDPWD");
            }
       
            continue;
        }
        if (_strcmp(token0,"pwd") == 0)
        {
      
           if (getcwd(s, 80 * sizeof(char)) != NULL)
           {
           printf("%s\n", s);
           }
           else
           {
           perror("getcwd() error");
           }
          continue;
         }

         if (_strcmp(token0,"mkdir") == 0)
         {
           pid_t pid3 = fork();
           
           if (pid3 == 0)
            {
           char *e[100] = {"/bin/mkdir",token1,NULL};
           execve (e[0],e,NULL);
           perror ("mkdir");
             exit (1);
             }
           else
             wait (NULL);
           continue;
         }
         if (_strcmp(token0,"ls") == 0)
         {
           pid_t pid2 = fork();
           
           if (pid2 == 0)
            {
           char *n[100] = {"/bin/ls",token1,NULL};
           execve (n[0],n,environ);
           perror ("ls");
             exit (1);
             }
           else
             wait (NULL);
           continue;
         }
        {
            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                free(why);
                continue;
            }
            else if (pid == 0)
            {
                char *arg[] = {token0,NULL};

                execve(arg[0],arg,environ),
            perror("execve");
                free(why);
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }

        free(why);
    }

    return 0;
}
