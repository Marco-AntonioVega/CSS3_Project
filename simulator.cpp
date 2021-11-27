/*
Created by Marco-Antonio Vega and Gerardo Lopez
CSS - 9406
December 15, 2021
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
    
    reg_map["000"] = 0;                     //r1 holds number of loops                
    reg_map["001"] = 0;                     //r2 holds sum total
    reg_map["010"] = 0;                     //r3 holds current num to add to sum

    while(fin >> instruction)               // read in the entire line of instruction (13 bits)
    {         
        memory.push_back(instruction);      // place it into our memory vector
    }

    fin.close();                            // program is loaded.

    for(unsigned i = 0; i < memory.size(); i++)     // for loop to iterate through vector of instructions
    {             
        instruction = memory.at(i);                 // retrieve the current instruction
        opcode = instruction.substr(0,4);           // take the first 4 bits of the instruction

        if(opcode == "0000") { //CLEAR
            for(const auto& key : reg_map)
                reg_map[key.first] = 0;
        }
        else if(opcode == "1000") //INPUT
        {
            int num;
            cout << "Enter the number: ";
            cin >> num;
            reg_map[instruction.substr(10, 3)] = num;
        }
        else if(opcode == "1010") { //JUMP
            if(instruction.substr(8, 1) == "0")
                i += bin_to_dec(instruction.substr(9, 4));
            else
                i -= bin_to_dec(instruction.substr(9, 4));
        }
        else if(opcode == "1110") { //SKIPCOND
            if(instruction.substr(10, 3) == "100") {
                if(reg_map[instruction.substr(7, 3)] == 0)
                    i++;
            }
            else if(instruction.substr(10, 3) == "000") {
                if(reg_map[instruction.substr(7, 3)] < 0)
                    i++;
            }
            else if(instruction.substr(10, 3) == "101") {
                if(reg_map[instruction.substr(7, 3)] > 0)
                    i++;
            }
        }
        else if(opcode == "0101") //SUM
        {   
            reg_map[instruction.substr(10, 3)] += reg_map[instruction.substr(7, 3)];
        }
        else if(opcode == "0111") { // SUBT
            reg_map[instruction.substr(10, 3)] -= bin_to_dec(instruction.substr(7, 3));
        }
        else if(opcode == "1111") //OUT                 // print to screen
        {
            string regis = instruction.substr(10,3);     // find which register to print
            cout << reg_map[regis] << endl;             // use those 3 bits with map to find value.
        }
        else if(opcode == "0001")                       // Stops the program
        {
            cout << "Program has finished running.\n";
            break;
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