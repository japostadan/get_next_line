# get_next_line

    # Mandatory part

This project is about programming a function that returns a line read from a file descriptor.


• Repeated calls (e.g., using a loop) to your get_next_line() function should let
    you read the text file pointed to by the file descriptor, one line at a time.

• Your function should return the line that was read.
    If there is nothing else to read or if an error occurred, it should return NULL.

• The returned line should include the terminating \n character,
    except if the end of file was reached and does not end with a \n character.

    # Bonus part

• Develop get_next_line() using only one static variable.

• get_next_line() should be able to manage multiple file descriptors at the same time.
    For example, if you can read from the file descriptors 3, 4 and 5, you should be
    able to read from a different fd per call without losing the reading thread of each
    file descriptor or returning a line from another fd.
    It means that you should be able to call get_next_line() to read from fd 3, then
    fd 4, then 5, then once again 3, once again 4, and so forth.