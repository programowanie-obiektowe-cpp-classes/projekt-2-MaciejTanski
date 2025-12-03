#pragma once
#include <vector>
#include <stdexcept>

#include "Computer.hpp"
using namespace std;


auto day2a(const string path){

    string fileContent = readFile(path);
    auto intcode = intcodeParser(fileContent);

    intcode[1]=12;
    intcode[2]=2;

    auto result = computer(intcode);
    return result[0];
}