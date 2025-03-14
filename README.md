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


### Static Variables

	This project can easily be solved by using static variables.
	Unlike local variables, which are destroyed once the function exits,
	Static variables are persistent meaning the data they hold persist across function calls,
	even when a function ends and another begins.
	The persistence allows to manage data that needs to survive throughout the program's execution.


### Psuedo Code
	Initialize a buffer to which will hold the value of the line read from a file.
	Check the file if readable.
	Search the line if '\n' in present.
	Store the data that are found before the '\n' to the static variable.
	Free used memory.
	Return the location of the found '\n'.

### Code Overview


- How it works
	- Initial call: 
		When get_next_line is called with a valid file descriptor, it will call set_content to read data into content.
    - Reading line by line:
		It keeps reading data from the file until it finds a newline or reaches the end. The data is stored in the static content variable, 
which persists across multiple calls to get_next_line.
    - Extracting the line:
		Once a newline is found, extract_line extracts the portion of content up to the newline and returns it.
    - Cleaning up:
		After a line is returned, refresh_content updates content to remove the part that was extracted, ensuring that the next call to get_next_line
continues reading from where the last line ended.
    - End of file:
		If the end of the file is reached, get_next_line will return NULL.

- Summary of Key Functions

    - get_next_line:
		Main function that coordinates the reading, extracting, and cleaning of lines.
    - set_content:
		Reads from the file and accumulates content in the content variable until a newline is found.
    - extract_line:
		Extracts the line from the content.
     - fefresh_content:
		Updates content by removing the extracted line.

- Memory Management

    - Dynamic memory allocation (malloc) to handle the buffer and content string.
    - Frees memory when appropriate to avoid memory leaks.
