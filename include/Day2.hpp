#pragma once
#include <vector>
#include <stdexcept>

#include "Computer.hpp"
using namespace std;


auto day2a(const string path){

    string fileContent = readFile(path);
    auto intcode = intcodeParser(fileContent);

    auto result = computer(intcode,12,2);
    return result;
}

auto day2b(const string path){
    string fileContent = readFile(path);
    auto intcode = intcodeParser(fileContent);

    int input1,input2;//inputy sa wstawiane do:
    //intcode[1]=input1; -noun
    //intcode[2]=input2; -verb
    int desired_output=19690720;// output=intcode[0]

    int upper_boundary = min(100,static_cast<int>(intcode.size())); //100 wynika z tresci zadania - argumenty moga byc od 0 do 99
    for(input1=0;input1<upper_boundary;input1++){
        for(input2=0;input2<upper_boundary;input2++){
            auto temp_intcode = intcode;
            auto result = computer(temp_intcode,input1,input2);
            if(result==desired_output){
                return 100*input1+input2;
            }
        }
    }
    //metoda bruteforce'owa, moze jeszcze poszukam optymalnej
    return -1;
}