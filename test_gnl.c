#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

void test_empty_file(void)
{
    printf("\n--- Testing Empty File ---\n");
    int fd = open("empty.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    close(fd);
    
    fd = open("empty.txt", O_RDONLY);
    char *line = get_next_line(fd);
    printf("Result: %s\n", line ? line : "NULL");
    free(line);
    close(fd);
}

void test_one_line_without_newline(void)
{
    printf("\n--- Testing One Line Without Newline ---\n");
    int fd = open("one_line_no_nl.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    write(fd, "This is a single line without a newline", 39);
    close(fd);
    
    fd = open("one_line_no_nl.txt", O_RDONLY);
    char *line = get_next_line(fd);
    printf("Result: %s\n", line ? line : "NULL");
    free(line);
    
    line = get_next_line(fd);
    printf("Second call: %s\n", line ? line : "NULL");
    free(line);
    close(fd);
}

void test_one_line_with_newline(void)
{
    printf("\n--- Testing One Line With Newline ---\n");
    int fd = open("one_line_nl.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    write(fd, "This is a single line with a \nnewline", 37);
    close(fd);
    
    fd = open("one_line_nl.txt", O_RDONLY);
    char *line = get_next_line(fd);
    printf("Result: %s", line ? line : "NULL");
    free(line);
    
    line = get_next_line(fd);
    printf("Second call: %s\n", line ? line : "NULL");
    free(line);
    close(fd);
}

void test_multiple_lines(void)
{
    printf("\n--- Testing Multiple Lines ---\n");
    int fd = open("multiple_lines.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    write(fd, "First line\nSecond line\nThird line\n", 34);
    close(fd);
    
    fd = open("multiple_lines.txt", O_RDONLY);
    char *line;
    int i = 1;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", i++, line);
        free(line);
    }
    close(fd);
}

void test_large_file(void)
{
    printf("\n--- Testing Large File ---\n");
    int fd = open("large_file.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    // Create a file with many lines that exceed BUFFER_SIZE
    for (int i = 0; i < 1000; i++)
    {
        char buffer[50];
        sprintf(buffer, "This is line %d in the large file test\n", i);
        write(fd, buffer, strlen(buffer));
    }
    close(fd);
    
    fd = open("large_file.txt", O_RDONLY);
    char *line;
    int count = 0;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        count++;
        free(line);
        // Print only a few lines to avoid flooding the console
        if (count <= 5 || count >= 995)
            printf("Line %d read\n", count);
        else if (count == 6)
            printf("...\n");
    }
    printf("Total lines read: %d\n", count);
    close(fd);
}

void test_invalid_fd(void)
{
    printf("\n--- Testing Invalid File Descriptor ---\n");
    char *line = get_next_line(-1);
    printf("Result with fd=-1: %s\n", line ? line : "NULL");
    free(line);
    
    line = get_next_line(42);
    printf("Result with fd=42: %s\n", line ? line : "NULL");
    free(line);
}

void test_binary_file(void)
{
    printf("\n--- Testing Binary File ---\n");
    int fd = open("binary.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    unsigned char binary_data[] = {0xFF, 0x00, 0xAB, 0xCD, 0x12, 0x34, 0x56, 0x78, '\n', 0xFF, 0xAA};
    write(fd, binary_data, sizeof(binary_data));
    close(fd);
    
    fd = open("binary.bin", O_RDONLY);
    char *line = get_next_line(fd);
    printf("Binary data line length: %zu\n", line ? strlen(line) : 0);
    if (line)
    {
        printf("Contains newline: %s\n", ft_strchr(line, '\n') ? "Yes" : "No");
        for (size_t i = 0; i < strlen(line); i++)
        {
            printf("%02X ", (unsigned char)line[i]);
        }
        printf("\n");
    }
    free(line);
    
    line = get_next_line(fd);
    printf("Second call result: %s\n", line ? "Not NULL" : "NULL");
    if (line)
    {
        for (size_t i = 0; i < strlen(line); i++)
        {
            printf("%02X ", (unsigned char)line[i]);
        }
        printf("\n");
    }
    free(line);
    close(fd);
}

void test_different_buffer_sizes(void)
{
    printf("\n--- Testing Different Buffer Sizes ---\n");
    printf("Note: This test requires recompilation with different BUFFER_SIZE values\n");
    printf("Current BUFFER_SIZE: %d\n", BUFFER_SIZE);
    
    int fd = open("buffer_test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    write(fd, "This is a test for different buffer sizes.\nLet's see how it handles various lengths.\n", 86);
    close(fd);
    
    fd = open("buffer_test.txt", O_RDONLY);
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}

int main(void)
{
    printf("=== GET_NEXT_LINE TESTS ===\n");
    
    test_empty_file();
    test_one_line_without_newline();
    test_one_line_with_newline();
    test_multiple_lines();
    test_large_file();
    test_invalid_fd();
    test_binary_file();
    test_different_buffer_sizes();
    
    printf("\n=== ALL TESTS COMPLETED ===\n");
    return (0);
}
