# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <stddef.h>
# include <sys/types.h>
# include <stddef.h>
# include <sys/stat.h>


int main (int argc, char **arg, char **envp)
{
    (void)(argc);

    char *const  argv[] = {arg[1], arg[2], NULL};
    execve(arg[1], argv, envp);
    return 0;
}