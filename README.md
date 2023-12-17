# Project Guidelines

Your goal is to implement a solution for the dining philosophers problem using C. Here are some key requirements and guidelines:

- Your project must adhere to the Norm, including bonus files/functions.
- Functions should not quit unexpectedly (segmentation fault, bus error, double free, etc.), apart from undefined behaviors.
- Properly free all heap-allocated memory space when necessary. No memory leaks will be tolerated.
- If required, submit a Makefile that compiles your source files to the required output with the flags `-Wall`, `-Wextra`, and `-Werror`. Use `cc`, and the Makefile must not relink.
- Include at least the rules `$(NAME)`, `all`, `clean`, `fclean`, and `re` in your Makefile.
- For bonuses, include a rule `bonus` in your Makefile, adding headers, libraries, or functions that are forbidden in the main part of the project.
- If using libft, copy its sources and Makefile to a `libft` folder. Your project’s Makefile must compile the library by using its Makefile, then compile the project.

## Evaluation

- Mandatory and bonus parts will be evaluated separately.
- If your project allows using libft, ensure that it is included as specified.
- Create test programs for your project. While not graded, these tests are useful for testing your work and peer evaluations during defense.


# Processes and Threads

## Processes 🔄

A **process** is an independent, self-contained unit of execution in a computer program. In the dining philosophers problem, each philosopher's behavior can be considered as an individual process. Each process has its memory space, code, and system resources. Processes run independently and do not directly share memory with each other.

In the dining philosophers problem, a process might represent the train of thought and actions of a philosopher. Processes communicate through inter-process communication (IPC) mechanisms, which might be required to coordinate the actions of philosophers.

## Threads 🧵

A **thread** is a lightweight unit of execution within a process. Threads within the same process share the same memory space and resources. In the context of the Philosopher project, you might consider implementing each philosopher as a thread within a single process.

Threads share data and resources, making communication between them more straightforward. However, in a multithreaded environment, proper synchronization mechanisms (like mutexes) are necessary to avoid race conditions and ensure that threads do not interfere with each other's execution.

## Philosopher Project Implementation 🍽️💻

In the Philosopher project, you have the flexibility to choose whether to represent each philosopher as a separate process or a thread within a process. The decision might depend on factors such as ease of communication, resource sharing, and the overall design of your solution.

Happy coding! 🚀
