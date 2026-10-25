# C Pointers Analysis Report

**GitHub Repository:** https://github.com/armentamrazyan84/pointers-assignment

## Assignment 1: Basics of Pointers
* **Code Explanation:** An integer `num` is allocated in memory. The address-of operator (`&num`) extracts its physical memory location, which is assigned to pointer `ptr_num`. Using the dereference operator (`*ptr_num`), we access and overwrite the value stored at that address.
* **Pointer Behavior & Observations:** Both `&num` and `ptr_num` yield identical hexadecimal addresses (e.g., `0x7fff...`). Direct variable assignment (`num = 99`) and pointer dereferencing (`*ptr_num = 99`) target the exact same memory location, demonstrating that pointers act as direct aliases for memory slots.

## Assignment 2: Pointer Arithmetic
* **Code Explanation:** The array name `arr` acts as a constant pointer to its first element `&arr[0]`. Incrementing `ptr_arr + i` calculates the offset to element i, allowing element traversal and value modification without array indexing `[]`.
* **Pointer Behavior & Observations:** Adding 1 to an `int*` pointer does not increase the raw memory address by 1 byte; instead, it scales by `sizeof(int)` (typically 4 bytes). The memory address sequence printed during traversal confirms contiguous 4-byte steps (e.g., ending in `...00`, `...04`, `...08`).

## Assignment 3: Pointers and Functions
* **Code Explanation:** The `swap` function accepts two integer pointers (`int *a, int *b`). Passing `&x` and `&y` from `main()` provides the function direct access to the callers' stack frames (pass-by-reference simulation in C).
* **Pointer Behavior & Observations:** Standard pass-by-value only modifies local copies within the called function. By passing memory addresses, dereferencing `*a` and `*b` inside `swap()` directly updates the values stored in the stack addresses of `x` and `y`.

## Assignment 4: Pointers to Pointers
* **Code Explanation:** A single pointer `ptr_val` stores the address of `val`. A double pointer `dbl_ptr` (`int**`) is declared to store the memory address of `ptr_val`.
* **Pointer Behavior & Observations:** 
  * `dbl_ptr` evaluates to the address of `ptr_val`.
  * `*dbl_ptr` dereferences once to retrieve the address stored in `ptr_val` (`&val`).
  * `**dbl_ptr` dereferences twice to retrieve the integer value (`250`).

## Assignment 5: Strings and Character Pointers
* **Code Explanation:** A string in C is a null-terminated (`'\0'`) array of `char`. A character pointer `char_ptr` iterates through the contiguous bytes until reaching `'\0'`. String length is calculated via pointer subtraction `(end_ptr - start_ptr)`.
* **Pointer Behavior & Observations:** Unlike `int*`, incrementing a `char*` by 1 increases the raw memory address by exactly 1 byte (`sizeof(char) = 1`). Subtracting two pointers of the same type returns the count of elements between them rather than the raw byte difference.
