#pragma once
#include <vector>
#include <stdexcept>

#include "Computer.hpp"
using namespace std;

auto day5a(const string path){

    string fileContent = readFile(path);
    auto intcode = intcodeParser(fileContent);

    //print("{}",intcode);
    auto result = computer(intcode,intcode[1],intcode[2]);

    return result;
}
