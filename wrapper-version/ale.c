#include "utility.h"

int main()
{
    printf("ALE has started\n");

    char *args[] = {"./ali-wrapper", NULL};
    int pid = spawn(args[0], args);
    waitpid(pid, NULL, 0);
    printf("ALE has finished\n");
    return 0;
}