CSS3_Project  
Created by Marco-Antonio Vega and Gerardo Lopez  
CSS 3 - 9406  
December 15, 2021  

This program reads in binary instructions and loops through  
each instruction line. First, the user inputs a number. Let us call  
this number X. Then, the program asks for a number X amount of times.  
Each iteration, the input number is added to a sum variable,  
which is outputted at the end of the program.  

Opcode bits:  

CLEAR: 0000  
INPUT: 1000  
JUMP: 1010  
SKIPCOND: 1110  
SUM: 0101  
SUBT: 0111  
OUT: 1111  
HALT: 0001

For each instruction, the first four bits are for the opcode,  
the next six bits are for the value that is being passed in,  
and the last three bits are for the register address.  

One exception is the "JUMP" opcode,  
which has the bits "1010". It checks the value of the 9th bit. If it  
is equal to 0, then it adds the decimal value of the last  
four bits to the current iteration of the loop.  
If it is equal to 1, then it subtracts the decimal value of the last  
four bits from the current iteration of the loop. This simulates  
jumping to different addresses in C++.  

Another exception is the "SKIPCOND" opcode, which  
has the bits "1110". It reads the last three bits as a skip condition and  
the bits from 7 - 9 (inclusive) as the register address, which holds the value that is being  
checked. If the skip condition is equal to "000" and the middle  
value is less than 0, then the next instruction is skipped.  
If the skip condition is equal to "100" and the middle  
value is equal to 0, then the next instruction is skipped.  
If the skip condition is equal to "101" and the middle  
value is greater than 0, then the next instruction is skipped.    
This allows us to break the loop when the number of iterations  
is fulfilled.  

The "CLEAR" clears all registers.  

The "INPUT" opcode takes in a user input and stores it  
in the corresponding register address in the last three  
bits of the instruction.  

The "SUM" opcode checks the value of bits 7 - 9 (inclusive)  
and finds the corresponding register address value. Then, it adds  
this value to the register address represented by the last three bits.  

THE "SUBT" opcode subtracts the decimal value of bits 7 - 9 (inclusive)  
from the registe address represented by the last three bits.  

The "OUT" opcode outputs the value of the register address that  
corresponds with the last three bits.  

THE "HALT" opcode terminates the program.  

General Purpose Register Architecture:  
Number of Registers: 3  
Word size: 4  
Size of Memory: 10  
Addressing: Mostly Direct & Some Immediate  
Types of Operands: Registers  
Bits for Opcode: 4  
Bits for Operand: 3  
Instruction Format: Big Endian, Register-Memory  
Fixed Instruction Width: 13 bits  
Fixed Data Width: 4 bits  
Fixed Register Width: 4 bits  
