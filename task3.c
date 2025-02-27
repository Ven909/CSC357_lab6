#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
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

    pid_t pid1, pid2;

    // Fork first child to execute "odds"
    if ((pid1 = fork()) < 0) 
    {
        perror("fork failed for odds");
        return 1;
    } 
    else if (pid1 == 0) 
    {
        execl("./odds", "odds", argv[1], NULL);
        perror("execl failed for odds");
        exit(1);
    }

    // Fork second child to execute "evens"
    if ((pid2 = fork()) < 0) 
    {
        perror("fork failed for evens");
        return 1;
    } 
    else if (pid2 == 0) 
    {
        execl("./evens", "evens", argv[1], NULL);
        perror("execl failed for evens");
        exit(1);
    }

    // Parent waits for both children to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
