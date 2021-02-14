#include "utility.h"

int main()
{
    printf("ALI-Wrapper has started\n");

    // ALI call
    char *coreNumber = "6";
    char *fileLocation = "./ali.o";
    char *args[] = {"mpirun", "-n", coreNumber, fileLocation, NULL};

    // There are two versions of creating mpirun processes
    // First is done with spawn(fork), with this way we can reach end of this file(printf ali wrapper has finished)
    //int pid = spawn(args[0], args);
    //waitpid(pid, NULL, 0);

    // The other way is done with execvp
    // Process goes through mpirun process and terminated codes which after this line
    execvp(args[0], args);

    printf("ALI-Wrapper has finished\n");
    return 0;
}