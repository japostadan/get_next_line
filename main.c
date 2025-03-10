#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("File does not exist. Creating it...\n");
        fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd == -1) {
            perror("Failed to create file");
            return 1;
        }
        // Write some content to the file
        const char *content = "This is a test file. '\t' It '\n'contains multiple lines.\n";
        if (write(fd, content, strlen(content)) == -1) {
            perror("Failed to write to file");
            return 1;
        }
        close(fd);
        printf("File created successfully.\n");
        // Reopen the file for reading
        fd = open(filename, O_RDONLY);
    }
    
    if (fd != -1)
    {
        char *line;
        line = (char *)1; // Initializing line to a non-NULL value
        while (line != NULL)
        {
            line = get_next_line(fd); // Reading from file descriptor
            if (line != NULL)
            {
                printf("%s\n", line);
                free(line);
            }
        }
        close(fd);
    }
    else
    {
        printf("Failed to open file.\n");
    }

    return 0;
}
/*
int main(void)
{
    char    *line;

    // Test reading from standard input (stdin)
    printf("Testing reading from standard input:\n");
    printf("Enter some lines of text (Ctrl+D to end):\n");
    line = (char *)1; // Initializing line to a non-NULL value
    while (line != NULL)
    {
        line = get_next_line(0); // Reading from standard input (stdin)
        if (line != NULL)
        {
            printf("%s\n", line);
            free(line);
        }
    }
	printf("Good Job!!\n");

    return 0;
}
*/
