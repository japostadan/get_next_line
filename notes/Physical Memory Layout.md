# Physical Memory Layout

	- In physical memory (RAM), the layout will be similar to the virtual memory model, but
more direct controll by the operating system and harware.

``` vbnet

+--------------------------------------------------+
|        **Operating System** (Kernel Memory)      |
|   (System-level functions, drivers, etc.)         |
+--------------------------------------------------+
|        **User Space** (Program Memory)            |
|                                                  |
|   +--------------------------------------------+  |
|   |      **Text Segment** (Program Code)       |  | <- Contains the program's instructions. This area is typically read-only.
|   |  (Address Range: 0x00000000 - 0x10000000)   |  |
|   +--------------------------------------------+  |
|   |      **Data Segment** (Initialized Data)   |  | <- Holds initialized global and static variables.
|   |  (Address Range: 0x10000000 - 0x20000000)   |  | 
|   +--------------------------------------------+  |
|   |      **BSS Segment** (Uninitialized Data)  |  | <- Holds uninitialized global and static variables (set to 0).
|   |  (Address Range: 0x20000000 - 0x30000000)   |  | 
|   +--------------------------------------------+  |
|   |      **Heap** (Dynamic Memory)             |  | <- Used for dynamically allocated memory (e.g., malloc).
|   |  (Address Range: 0x30000000 - 0x40000000)   |  | 
|   |  (Grows upwards)                           |  | 
|   +--------------------------------------------+  |
|   |      **Stack** (Local Variables/Function)  |  | <- Stores local variables, function calls, etc.
|   |  (Address Range: 0x40000000 - 0x50000000)   |  | 
|   |  (Grows downwards)                         |  | 
|   +--------------------------------------------+  |
+--------------------------------------------------+


```

### Key Points

1. Operating System and Kernel Memory
	- Kernel space (operating system level) is separated from user space (where program runs). It contains the systems' instruction
and hardware management code. (e.g device, drivers, system calls).
	- User space is where the program runs, with its own sections for code, and dynamic memory.

2. Text Segment
	- Program Code are stored in this segment. In physical memory. the Text Segment contains the machine code instructions that the CPU
reads and executes.
	- The operating system loads the program's binary and executable into the Text Segment and ensures it is read-only for security reasons
(this is to make sure your program can't modify its own code.)

3. Data Segment
	- Initialized Variables are stored in this segment of the memory. Also program's global and static variables are stored in this segment
if they have an initial value.
	- The operating system loads these variables from the program's binary into the physical memory and allocates space for them.

4. BSS Segment
	- Unitialized Variables that are declared but not initialized(e.g static int var;) are loaded into this area.
	- The operating system initalizes them to zero when the program stars.

5. Heap Segment
	- The Heap is the section of the memory for dynamic allocation. It grows upward as memory is allocated using maloc() and calloc() or new().
	- In physical memory, the heap grows into the variable memory range as the program request more space.

6. Stack Segment
	- The Stack stores local variables, return addresses, and function call information.
	- It grows downward in physical memory asnew function calls are made, and it shrinks when function returns.
	- The operationg system and CPU manage this growth and shrinkage automatically.
