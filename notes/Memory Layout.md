### Memory Layout in Programs

	- The memory layout of a program refers to how's the data is stored in the computer
	computer memory during execution.

``` vbnet
+-----------------------------+
|     Text Segment            |  
|   (Program Code/Instructions)| <- The program's instructions (read-only) reside here.  
+-----------------------------+
|     Data Segment            |  
|  (Initialized Global & Static)|
|    Variables                | <- Holds variables that are initialized, like global_var = 10.  
+-----------------------------+
|     BSS Segment             |  
|   (Uninitialized Variables) |
|  static int b;              | <- Holds uninitialized variables (automatically set to zero).  
+-----------------------------+
|     Heap Segment            |  
|   (Dynamic Memory)          |  
|   malloc/calloc memory      | <- Memory for things you ask the program to create during runtime.  
|   (Grows upwards)           |  
+-----------------------------+
|     Stack Segment           |  
|  (Local Variables & Function)|
|   Calls (Grows Downwards)   | <- Temporary space for function calls and local variables.  
+-----------------------------+

```	

### Text Segment
	- This is where program code lives, It's like the instruction for what the compuer should do
(think of recipe). It's read-only, meaning it can't be changed by the program itself.

### Data Segment
	- This part holds initialized global and static variables. -things like variables that are
given value.

### Heap Segment
	- The Heap is where the memory is allocated dynamically during the program's execution.
Using malloc() or calloc(), the computer grabs a chunk of memory from the heap to store data.

### Stack Segment
	- The Stack is for local variables and function calls. It grows downward from higher memory
addresses.
	- Every time a funcntion is called, it gets a "stack frame" where the function's local
variable, return address, and other information are stored.
	- When the function ends, the stack frame is removed..


- The Growth Directions:
	- The heap grows upwards, and stack grows downwards. This is like two sections of the memory
trying to expand in opposite directions. Eventually, if you use up too much space in either the stack
or the heap, these two will meet- this is where memory problems like stack overflow or heap overflow 
happens.
