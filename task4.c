#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        printf("Usage: %s <program> <file>\n", argv[0]);
        return 1;
    }

    // Open the file for writing (create if it doesn't exist, truncate if it does)
    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) 
    {
        perror("open failed");
        return 1;
    }

    // Redirect standard output to the file
    if (dup2(fd, STDOUT_FILENO) < 0) 
    {
        perror("dup2 failed");
        close(fd);
        return 1;
    }

    // Close the original file descriptor (not needed anymore)
    close(fd);

    // Execute the specified program
    execl(argv[1], argv[1], NULL);

    // If exec fails, print an error and return
    perror("execl failed");
    return 1;
}
