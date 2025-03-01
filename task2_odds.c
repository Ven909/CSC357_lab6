#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 0) 
    {
        printf("N must be a positive integer.\n");
        return 1;
    }

    for (int i = 1; i <= N; i += 2) 
    {
        printf("%d\n", i);
    }

    return 0;
}
