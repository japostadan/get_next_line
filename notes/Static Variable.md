# Static Variable Properties: The Building Blocks of Persistent Data

	- Static variables in C are essential for managing data that needs to persist throughout the entire program
execution. 

### Scope: Local and Global

	- Local Static Variables : These are confined to the function they are declared in and cannot be accessed
outside of it.
	- Global Static Variables : These are limited to the file where they are declared, preventing access from the other
files, and ensuring encapsulation within the program.

### Initialization

	- Static Variables are automatically initialized to zero (for basic data types) when program begins.
	- They are allocated in the data segment of the program's memory, ensuring that they retain their 
values across function calls, in contratry of local variables which are allocated in the stack. These
properties of static variables make them so powerfull for managing data persistence and ensuring that
program operates efficiently across mutiple function calls.

### Declaration

	``` C
	# static data_type variable_name

	#include <stdio.h>
	
	void incrementCounter()
	{
		static int counter = 0;  // Static variable
    	counter++;
    	printf("Counter: %d\n", counter);
	}

	int main()
	{
		incrementCounter();
    	incrementCounter();
    	incrementCounter();
    	return 0;
	}
	```

### Risk

	- Source of thread safety issues
	- Can obstuct testability and maintenance
	- Persist even if unused, wasting memory


[[Memory Layout]]
