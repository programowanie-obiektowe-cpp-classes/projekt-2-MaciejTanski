#pragma once
#include <vector>
#include <stdexcept>

#include "Computer.hpp"
using namespace std;

void day5a(const string path){

    string fileContent = readFile(path);
    auto intcode = intcodeParser(fileContent);

    intcode[10]=04;
    //print("{}",intcode);
    print("!!!!!Dzien 5a - Podaj input 1!!!!!\n");
    auto result = computer(intcode,intcode[1],intcode[2]);
}

auto day5b(const string path){

    string fileContent = readFile(path);
    auto intcode = intcodeParser(fileContent);

    print("!!!!!Dzien 5b - Podaj input 5!!!!!\n");
    auto result = computer(intcode,intcode[1],intcode[2]);

}