#pragma once
#include <vector>
#include <stdexcept>

#include "Computer.hpp"
using namespace std;

void day9tests(){

    string fileContent = readFile("../data/test_d9a.txt");
    auto intcode = intcodeParser(fileContent);

    print("{}\n",intcode);
    auto result = computer(intcode,intcode[1],intcode[2]);
    print("{}\n",intcode);

    fileContent = readFile("../data/test_9a_mnozenie.txt");
    intcode = intcodeParser(fileContent);

    println("mnozenie 16digit test");
    print("{}\n",intcode);
    result = computer(intcode,intcode[1],intcode[2]);
 

    fileContent = readFile("../data/test_9a_longint.txt");
    intcode = intcodeParser(fileContent);

    println("longint printing test");
    print("{}\n",intcode);
    result = computer(intcode,intcode[1],intcode[2]); 

}

void day9a(){

    string fileContent = readFile("../data/inp_d9a.txt");
    auto intcode = intcodeParser(fileContent);

    print("!!!!!Dzien 9a - Podaj input 1!!!!!\n");
    auto result = computer(intcode,intcode[1],intcode[2]);
}
