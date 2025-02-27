#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void limit_fork(rlim_t max_procs)
{
    struct rlimit rl;
    if (getrlimit(RLIMIT_NPROC, &rl))
    {
        perror("getrlimit");
        exit(-1);
    }
    rl.rlim_cur = max_procs;
    if (setrlimit(RLIMIT_NPROC, &rl))
    {
        perror("setrlimit");
        exit(-1);
    }
}

int main(int argc, char *argv[]) 
{
    limit_fork(50);

    if (argc != 2) 
    {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        printf("N must be a positive integer.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) 
    {
        perror("fork failed");
        return 1;
    }
    if (pid == 0) // Child process
    {  
        for (int i = 1; i <= N; i += 2) 
        {
            printf("%d\n", i);
        }
        exit(0);
    } 
    else // Parent process
    {  
        wait(NULL);  // Wait for child to complete
        for (int i = 2; i <= N; i += 2) 
        {
            printf("\t%d\n", i);
        }
    }

    return 0;
}

