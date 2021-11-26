/*
Created by Marco-Antonio Vega and Gerardo Lopez
*/

// simulator.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

int bin_to_dec(string bin);

int main()
{   
    ifstream fin("sum.binary");             // the file with binary code (0s and 1s)

    if(fin.fail())                          // make sure file opened okay
    {
        cout << "File open failed\n";
        exit(0);
    }

    string instruction;                     // hold the entire binary instruction
    string opcode;                          // hold the binary opcode (4 bits)
    
    map<string, int> reg_map;               // a map from strings to ints used for registers
    map<string, vector<int>> ary_map;       // a map from strings to vector<int> used for arrays
    vector<string> memory;                 // load instructions in vector to represent memory
    
    reg_map["000"] = 0;                     //r1 register set to zero                
    reg_map["001"] = 0;                     //r2 register set to zero
    reg_map["010"] = 0;                     //r3 register set to zero
    reg_map["011"] = 0;                     //r4 register set to zero
    reg_map["100"] = 0;                     //r5 register set to zero
    reg_map["101"] = 0;                     //r6 register set to zero
    reg_map["110"] = 0;                     //r7 register set to zero
    reg_map["111"] = 0;                     //r8 register set to zero

    while(fin >> instruction)               // read in the entire line of instruction (13 bits)
    {         
        memory.push_back(instruction);      // place it into our memory vector
    }

    fin.close();                            // program is loaded.

    for(unsigned i = 0; i < memory.size(); i++)     // for loop to iterate through vector of instructions
    {             
        instruction = memory.at(i);                 // retrieve the current instruction
        opcode = instruction.substr(0,4);           // take the first 4 bits of the instruction

        if(opcode == "0011") //PUT                  // if the first 4 bits are opcode for PUT
        {
            string n = instruction.substr(4,6);     // read the 6 bits related to numerical value
            int val = bin_to_dec(n);                // convert binary to decimal

            string regis = instruction.substr(10,3);    // find the 3 bits related to the register
            reg_map[regis] = val;                       // use those 3 bits as location to store value
        }
        else if(opcode == "0101") //SUM                 // SUM instruction is followed by three registers
        {   
            string regisA = instruction.substr(4,3);    // bits 4-6 are the first register
            string regisB = instruction.substr(7,3);    // bits 7-9 are the second register
            string regisC = instruction.substr(10,3);   // bits 10-12 are the last register
            
            int sum_result = reg_map[regisA] + reg_map[regisB]; // add the first two registers
            reg_map[regisC] = sum_result;                       // place the result in the third register

        }
        else if(opcode == "1111") //OUT                 // print to screen
        {
            string regis = instruction.substr(4,3);     // find which register to print
            cout << reg_map[regis] << endl;             // use those 3 bits with map to find value.
        }
        else if(opcode == "1010") //MAKE THE ARRAY
        {
            string n = instruction.substr(4,6);         // read the 6 bits related to size of array
            int val = bin_to_dec(n);                    // convert binary to decimal
            string regis = instruction.substr(10,3);    // find the 3 bits related to the array
            ary_map[regis] = vector<int>(val);             
        }
        else if(opcode == "0000")                       // Stops the program
        {
            cout << "Program has finished running.\n";           
        }
        else
        {
            cout << "ERROR. OPCODE NOT FOUND. PROGRAM WILL TERMINATE.\n";
            exit(2);
        }
    }

    return 0;
}

int bin_to_dec(string bin) 
{
    int num = 0;
    for (int i = 0; i < bin.length(); i++) 
        if (bin[i] == '1')
            num += pow(2, bin.length() - 1 - i);
    
    return num;
}