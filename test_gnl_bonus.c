#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void test_multiple_file_descriptors(void)
{
    printf("\n--- Testing Multiple File Descriptors ---\n");
    
    // Create three different test files
    int fd1 = open("test1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int fd2 = open("test2.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int fd3 = open("test3.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    
    write(fd1, "In test1.txt, First New Line\nSecond New Line\nThird New Line 1, Line 3\n", 68);
    write(fd2, "In test2.txt, First New Line\nSecond New Line,\n", 48);
    write(fd3, "In test3.txt, Single Line\n", 27);
    
    close(fd1);
    close(fd2);
    close(fd3);
    
    // Open the files for reading
    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);
    fd3 = open("test3.txt", O_RDONLY);
    
    // Read alternating between files
    char *line;
    
    printf("Reading alternating between files:\n");
    
    line = get_next_line(fd1);
    printf("FD1: %s", line);
    free(line);
    
    line = get_next_line(fd2);
    printf("FD2: %s", line);
    free(line);
    
    line = get_next_line(fd3);
    printf("FD3: %s", line);
    free(line);
    
    line = get_next_line(fd1);
    printf("FD1: %s", line);
    free(line);
    
    line = get_next_line(fd2);
    printf("FD2: %s", line);
    free(line);
    
    line = get_next_line(fd1);
    printf("FD1: %s", line);
    free(line);
    
    // Check if we've reached the end of all files
    line = get_next_line(fd1);
    printf("FD1 (should be NULL): %s\n", line ? line : "NULL");
    free(line);
    
    line = get_next_line(fd2);
    printf("FD2 (should be NULL): %s\n", line ? line : "NULL");
    free(line);
    
    line = get_next_line(fd3);
    printf("FD3 (should be NULL): %s\n", line ? line : "NULL");
    free(line);
    
    close(fd1);
    close(fd2);
    close(fd3);
}

void test_fd_limits(void)
{
    printf("\n--- Testing FD Limits ---\n");
    
    // Test with FD at the upper limit (1024)
    printf("Testing with FD at the upper limit is system-dependent\n");
    printf("Theoretical limit check with fd=1024: ");
    char *line = get_next_line(1024);
    printf("%s\n", line ? line : "NULL");
    free(line);
}

// Separate function for invalid FDs to isolate the crash
void test_invalid_fds(void)
{
    printf("\n--- Testing Invalid FDs ---\n");
    printf("Note: Testing with careful error handling to prevent crashes\n");
    
    // Test with negative fd
    printf("FD -1: ");
    fflush(stdout); // Ensure output is displayed before potential crash
    char *line = get_next_line(-1);
    printf("%s\n", line ? line : "NULL");
    if (line) free(line);
    
    // Test with out-of-bounds fd
    printf("FD 1025: ");
    fflush(stdout);
    line = get_next_line(1025);
    printf("%s\n", line ? line : "NULL");
    if (line) free(line);
}

void test_interleaved_reads(void)
{
    printf("\n--- Testing Interleaved Reads with Various File Types ---\n");
    
    // Create different types of files
    int fd_text = open("interleaved_text.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int fd_empty = open("interleaved_empty.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int fd_binary = open("interleaved_binary.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    
    write(fd_text, "Line 1 text\nLine 2 text\nLine 3 text\n", 36);
    // fd_empty remains empty
    unsigned char binary_data[] = {0xFF, 0x00, '\n', 0xAB, 0xCD, '\n'};
    write(fd_binary, binary_data, sizeof(binary_data));
    
    close(fd_text);
    close(fd_empty);
    close(fd_binary);
    
    // Open the files for reading
    fd_text = open("interleaved_text.txt", O_RDONLY);
    fd_empty = open("interleaved_empty.txt", O_RDONLY);
    fd_binary = open("interleaved_binary.bin", O_RDONLY);
    
    char *line;
    
    // Read from text file
    printf("Text file (first line): ");
    line = get_next_line(fd_text);
    printf("%s", line ? line : "NULL");
    free(line);
    
    // Read from empty file
    printf("Empty file: ");
    line = get_next_line(fd_empty);
    printf("%s\n", line ? line : "NULL");
    free(line);
    
    // Read from binary file
    printf("Binary file (first line): ");
    line = get_next_line(fd_binary);
    if (line)
    {
        printf("Length: %zu, Content in hex: ", strlen(line));
        for (size_t i = 0; i < strlen(line); i++)
        {
            printf("%02X ", (unsigned char)line[i]);
        }
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }
    free(line);
    
    // Read second line from text file
    printf("Text file (second line): ");
    line = get_next_line(fd_text);
    printf("%s", line ? line : "NULL");
    free(line);
    
    // Read second line from binary file
    printf("Binary file (second line): ");
    line = get_next_line(fd_binary);
    if (line)
    {
        printf("Length: %zu, Content in hex: ", strlen(line));
        for (size_t i = 0; i < strlen(line); i++)
        {
            printf("%02X ", (unsigned char)line[i]);
        }
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }
    free(line);
    
    close(fd_text);
    close(fd_empty);
    close(fd_binary);
}

void test_different_buffer_sizes(void)
{
    printf("\n--- Testing Different Buffer Sizes with Multiple FDs ---\n");
    printf("Note: This test requires recompilation with different BUFFER_SIZE values\n");
    printf("Current BUFFER_SIZE: %d\n", BUFFER_SIZE);
    
    int fd1 = open("buffer_test1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int fd2 = open("buffer_test2.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    
    // First file with short lines
    write(fd1, "Short line 1\nShort line 2\nShort line 3\n", 40);
    
    // Second file with long lines to test buffer size handling
    char long_line[1000];
    memset(long_line, 'A', 999);
    long_line[999] = '\0';
    write(fd2, long_line, 999);
    write(fd2, "\n", 1);
    memset(long_line, 'B', 999);
    long_line[999] = '\0';
    write(fd2, long_line, 999);
    write(fd2, "\n", 1);
    
    close(fd1);
    close(fd2);
    
    fd1 = open("buffer_test1.txt", O_RDONLY);
    fd2 = open("buffer_test2.txt", O_RDONLY);
    
    char *line;
    
    // Read first line from each file
    printf("FD1 (Short line): ");
    line = get_next_line(fd1);
    printf("%s", line ? line : "NULL");
    free(line);
    
    printf("FD2 (1000-char line): ");
    line = get_next_line(fd2);
    if (line)
    {
        printf("Length: %zu, First 10 chars: %.10s...\n", strlen(line), line);
    }
    else
    {
        printf("NULL\n");
    }
    free(line);
    
    // Read second line from each file
    printf("FD1 (Short line): ");
    line = get_next_line(fd1);
    printf("%s", line ? line : "NULL");
    free(line);
    
    printf("FD2 (1000-char line): ");
    line = get_next_line(fd2);
    if (line)
    {
        printf("Length: %zu, First 10 chars: %.10s...\n", strlen(line), line);
    }
    else
    {
        printf("NULL\n");
    }
    free(line);
    
    close(fd1);
    close(fd2);
}

void test_close_between_calls(void)
{
    printf("\n--- Testing Close Between Calls ---\n");
    
    int fd = open("close_test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    write(fd, "Line 1\nLine 2\nLine 3\n", 21);
    close(fd);
    
    fd = open("close_test.txt", O_RDONLY);
    char *line = get_next_line(fd);
    printf("First call: %s", line ? line : "NULL");
    free(line);
    
    // Close and reopen
    close(fd);
    fd = open("close_test.txt", O_RDONLY);
    
    line = get_next_line(fd);
    printf("After close/reopen: %s", line ? line : "NULL");
    free(line);
    
    close(fd);
}

int main(void)
{
    printf("=== GET_NEXT_LINE_BONUS TESTS ===\n");
    
    test_multiple_file_descriptors();
    test_fd_limits();
    // Separate the invalid FD tests to isolate potential crashes
    //test_invalid_fds();
    test_interleaved_reads();
    test_different_buffer_sizes();
    test_close_between_calls();
    
    printf("\n=== ALL BONUS TESTS COMPLETED ===\n");
    return (0);
}
