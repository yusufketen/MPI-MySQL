#include "utility.h"

int spawn(char *program, char **arg_list)
{
    pid_t child_pid;

    // ALI-Wrapper fork
    child_pid = fork();
    if (child_pid != 0)
        return child_pid;
    else
    {
        execvp(program, arg_list);
        fprintf(stderr, "an error occurred in execvp\n");
        abort();
    }
}