# RISC-V to Machine Code Converter

## Overview
This program converts RISC-V assembly code into machine code. It takes a RISC-V assembly file `input.asm` as input and generates the corresponding machine code in a text file `output.mc`.

## Installation
- Clone this repository to your local machine:
git clone https://github.com/jyoti7777/RISC-V_Assembler

## Usage
1. Ensure you have a valid RISC-V assembly file `input.asm` in the same directory as `main.cpp`.
2. Place your assembly code in `input.asm`.
3. Compile and run the program.
    Use the following instructions in the terminal of directory:
        $ gcc main.cpp
        $ ./a.out
4. If all the code is correct, check the generated machine code in the `output.mc` file located in the project directory to find the equivalent machine code for the given input.
5. In case of an error, you will find the error in the `output.mc`.
6. In the `output.mc` file, you will find 4 segments, DATA, TEXT, STACK, HEAP each containing corresponding data or instructions.

## Supported Instructions
R format:
- `add`
- `and`
- `or`
- `sll`
- `slt`
- `sra`
- `srl`
- `div`
- `sub`
- `xor`
- `mul`
- `rem`

I format:
- `addi`
- `andi`
- `ori`
- `lb`
- `ld`
- `lh`
- `lw`
- `jalr`

S format:
- `sb`
- `sw`
- `sd`
- `sh`

SB format:
- `beq`
- `bne`
- `bge`
- `blt`

U format:
- `auipc`
- `lui`

UJ format:
- `jal`

Also support for data segment and following directives:
- `.text`
- `.data`
- `.byte`
- `.half`
- `.word`
- `.dword`
- `.asciz`

These directives can be used to define and allocate data in the data segment and specify the type of data being declared.

## Features
- Converts RISC-V assembly instructions to corresponding machine code.
- Supports various instruction formats including R-type, I-type, S-type, SB-type, U-type, and UJ-type instructions.
- Checks for syntax errors and invalid instructions.
- Handles labels and branch instructions.
- Handles data and memory storage in multiple formats.

## Sample Input
A sample RISC-V assembly file (`input.asm`) might look like this:
.data

arr: .word 0x12 -2 24 0xcde

n: .byte 4


.text

main:

add x1, x2, x3

addi x3, x4, 0x30

beq x4, x5, exit

or x7, x8, x9

exit:


## Sample Output
The generated machine code for the sample input will be written to the `output.mc` file as follow:
0x10000000 0x00000012

0x10000004 0xfffffffe

0x10000008 0x00000018

0x1000000c 0x00000cde

0x10000010 0x04

0x10000011 0x68656c6c6f20776f726c6400



0x00000000 0x003100b3

0x00000004 0x03020193

0x00000008 0x00520463

0x0000000c 0x009463b3


## Limitations
- Currently supports a limited set of RISC-V instructions.
- May not handle all edge cases or optimizations.

## Warnings
- The directive `.word` is used for word, `.dword` for double word, `.half` for half word, `.byte` for byte, and `.asciz` for ASCII strings specified within double quotation marks.

- Labels in RISC-V follow the same format as identifiers in programming languages like C/C++. They must start with a letter (lowercase or uppercase) or underscore, followed by a combination of letters, underscores, or digits of any length, and end with a colon `:`.
- Pseudo instructions are not supported.

- Immediate and offset values in instructions can be specified in hexadecimal format (beginning with 0x) or decimal format.
  
- Operands in instructions can be separated by commas or spaces.
  
- The `.asciz` directive does not directly support the creation of arrays of strings. Instead, only individual strings can be stored one at a time using `.asciz`.

## Contributors
- Jyoti (https://github.com/jyoti7777)
- Ojas Jain (https://github.com/Ojas251)
- Siddharth Verma (https://github.com/Sid-3904)
