#pragma once
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <print>
#include <windows.h>

using namespace std;

template<typename T>
T wczytaj(const std::string& komunikat) {
    T wartosc;
   
    std::print("{}",komunikat);

    while (!(std::cin >> wartosc)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::println("Wrong input type:");
        std::print("{}", komunikat);
    }
    std::print("\n");
    return wartosc;
}

int parameter(int mode,const int pointer, const vector<int>& intcode){

    switch(mode){
        default:
            throw runtime_error("Unknown mode");
            
        case 0:
            return intcode[pointer];

        case 1:
            return pointer;
    }

}

auto computer(vector<int>& intcode,int noun, int verb){
    int ptr = 0;
    int opcode, param1, param2, dest;
    int a,b,c,d,e;

    const size_t N = intcode.size();

    intcode[1]=noun;
    intcode[2]=verb;

    auto bad_access = [&](const string& reason) {
        ostringstream os;
        os << "Intcode error: " << reason << "\n";
        os << "ptr=" << ptr << " size=" << N << "\n";
        if (ptr < N) os << "opcode at ptr = " << intcode[ptr] << "\n";
        os<< "modes=(" << a << "," << b << "," << c << ")\n";
        throw runtime_error(os.str());
    };

    int full_opcode = intcode[ptr];
    opcode=full_opcode%100;
    while(opcode!=99){

        a=full_opcode/10000;
        b=(full_opcode/1000)%10;
        c=(full_opcode/100)%10;
        
        //print("DEBUG: Decoded opcode {} into {}, modes=({}, {}, {})\n", intcode[ptr], opcode, a, b, c);

        if ((opcode == 3) && c == 1){
            throw runtime_error("Destination parameter cannot be in immediate mode");
            //c=0; //tryb dla parametru input/output musi byc zawsze 0
            //print("ATTENTION\n Computer read opcode {} in immediate mode\n Changing to position mode\n\n",opcode);
        }
        param1 = parameter(c, ptr + 1, intcode);
        param2 = parameter(b, ptr + 2, intcode);
        if (a == 1)
            throw runtime_error("Destination parameter cannot be in immediate mode");
        dest = parameter(a, ptr + 3, intcode);

        //print("DEBUG: ptr={}, opcode={}, modes=({}, {}, {}), param1={}, param2={}, dest={}\n", ptr, opcode, a, b, c, param1, param2, dest);
  
        //wyjatki
        if (ptr >= N) bad_access("instruction pointer out of range (ptr >= size)");
        //if (c==0 && ((param1) >= static_cast<int>(N) || param1 < 0)) bad_access("param1 index out of range: " + to_string(param1));
        //if (b==0 && ((param2) >= static_cast<int>(N) || param2 < 0)) bad_access("param2 index out of range: " + to_string(param2));
        //if (a==0 && ((dest) >= static_cast<int>(N) || dest < 0)) bad_access("dest index out of range: " + to_string(dest));
        
        switch(opcode){

            default:
                throw std::runtime_error("Unknown opcode" + to_string(opcode));

            case 1:
                //print("DEBUG: Adding {} and {}, storing at {}\n", intcode[param1], intcode[param2], dest);
                intcode[dest] = intcode[param1] + intcode[param2];
                
                ptr += 4;
                break;
            case 2:
                //print("DEBUG: Multiplying {} and {}, storing at {}\n", intcode[param1], intcode[param2], dest);
                intcode[dest] = intcode[param1] * intcode[param2];
                
                ptr += 4;
                break;
            case 3:
                intcode[param1] = wczytaj<int>("Podaj input: "); 
                ptr += 2;
                break;
            case 4:
                //print("DEBUG: Outputting value at {}, value={}\n", param1, intcode[param1]);
                print("output: {}\n", intcode[param1]);
                ptr += 2;
                break;
            case 5:
                if(intcode[param1]) ptr = intcode[param2];
                else ptr +=3;
                break;
            case 6:
                if(!intcode[param1]) ptr = intcode[param2];
                else ptr +=3;
                break;
            case 7:
                intcode[dest] = (intcode[param1] < intcode[param2]) ? 1 : 0;
                ptr += 4;
                break;
            case 8:
                intcode[dest] = (intcode[param1] == intcode[param2]) ? 1 : 0;
                ptr += 4;
                break;
            
        }
        full_opcode = intcode[ptr];
        opcode=full_opcode%100;
    }

    //print("DEBUG: Halting program.\n");
    //Sleep(1);
    return intcode[0];


}

    
    
