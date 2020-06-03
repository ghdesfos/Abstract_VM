# Abstract-VM
## Project from the C++ branch at school 42
Abstract-VM is a virtual machine that can interpret and execute commands written in a basic assembly language.

## Special features
For this project, I implemented a lexer-tokenizer-parser.

## How to use the virtual machine
Compile with:
```sh
make
```

Run with:
```sh
./abstract_vm files/[file_name]
```

## Assemply language
Simple assembler language that our virtual machine can understand. If there is an error in the set of instructions, the program will throw an exception.
| Instruction  |  Details |
|---|---|
| **push _value_**  | Pushes the value at the top of the stack. The _value_ must have one of the following form: <ul><li>int8(n) : Creates an 8-bit integer with value n.</li><li>int16(n) : Creates a 16-bit integer with value n.</li><li>int32(n) : Creates a 32-bit integer with value n.</li><li>float(z) : Creates a float with value z.</li><li>double(z) : Creates a double with value z.</li></ul>|
| **pop**  | Unstacks the value from the top of the stack. |
|  **dump**  |  Displays each value of the stack, from the most recent one to the oldest one. |
| **assert _value_** |  Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction. |
| **more _value_** |  Asserts that the value at the top of the stack is less to the one passed as parameter for this instruction. |
| **less _value_** |  Asserts that the value at the top of the stack is more to the one passed as parameter for this instruction. |
| **add**  |  Unstacks the first two values on the stack, adds them together and stacks the result. |
| **sub** |  Unstacks the first two values on the stack, subtracts them, then stacks the result. |
| **mul** |  Unstacks the first two values on the stack, multiplies them, then stacks the result. |
| **div** |  Unstacks the first two values on the stack, divides them, then stacks the result. |
| **mod** | Unstacks the first two values on the stack, calculates the modulus, then stacks the result. |
| **print** | Asserts that the value at the top of the stack is an 8-bit integer. (If not, exception will be thrown), then interprets it as an ASCII value and displays the corresponding character on the standard output. |
| **b_min** | Bonus: prints the minimum of the values on the stack. |
| **b_max** | Bonus: prints the maximum of the values on the stack. |
| **b_avg** | Bonus: prints the average of the values on the stack. |
| **b_tokens** | Bonus: prints all tokens obtained by the lexer. |
| **b_stack** | Bonus: prints the value of all elements on the stack. |
