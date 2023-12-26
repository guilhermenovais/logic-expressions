# Logic Expressions Evaluator

## About
This project implements two algorithms: the first is an algorithm to evaluate the value that a logical expression takes based on a set of values assigned to its variables, while the second is an algorithm designed to evaluate the satisfiability of a logical expression, taking into account quantifiers that specify the scope of variables and a set of values assigned to these variables.

## Implementation
To solve the evaluation problem, I chose to represent logical expressions using binary trees, with each node constituting an element of the expression (operand, operator or opening/closing parentheses). The elements are organized in the tree in such a way that the operations that will be executed first, that is, that have greater precedence, are further from the root, while the operations that will be executed last are closer to the root. This allows, by evaluating the operations using the post-order path, the result to converge to the root.
To solve the satisfiability problem, I simply used the evaluation algorithm, replacing the values of the variables with possible values, and observed whether any combination satisfies the applied restrictions.

## Instructions to compile and execute
To compile the program, simply run the `make all` command.

To run the program, simply execute the command `./bin/tp1.out`, passing the appropriate arguments.

To clean the ‘.o’ files and the executable, simply run the `make clean` command.

To run tests with Valgrind and gdb, simply run the `make test` command.
