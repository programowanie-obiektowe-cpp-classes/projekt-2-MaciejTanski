#pragma once
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <print>
#include <windows.h>
#include <ranges>

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


int parameter(const int mode,const int pointer, vector<long long>& intcode,const int relative_base){

    int param;

    switch(mode){
        default:
            throw runtime_error("Unknown mode");
            
        case 0:
            param = (int)intcode[pointer];
            break;
        case 1:
            param = pointer;
            break;
        case 2:
            param = relative_base + (int)intcode[pointer];
            break;
    }

    if(param<0){
        throw runtime_error("Negative parameter index: " + to_string(param));
    }
    if((param) >= static_cast<int>(intcode.size())){
        //rozszerzenie pamieci
        //print("DEBUG: Extending memory from size {} to {}\n", intcode.size(), param + 1);
        intcode.resize(param+1, 0);
    }
    return param;
}

auto computer(vector<long long>& intcode,long long noun, long long verb){
    //auto intcode = intcode_int | std::views::transform([](int& x){ return static_cast<int64_t>(x); }) | std::ranges::to<std::vector<int64_t>>();
    //zmiana typu dla obsługi wiekszych liczb, takie podejscie zapewnia kompatybilność wsteczną
    //możliwe, że ze wzgledów optymalizacyjnych warto by pozmieniać to już wcześniej - nie znam kosztów rzutowania typów w C++
    //ale teraz chciałem osiągnąć zgodnosć wersji przy jak najmniejszym nakładzie pracy - wystarczyło zmienić 5 linijek w computer

    //hehe nie dziala przy czytaniu i tak wiec trzeba jednak przerabiac
    int ptr = 0; int relative_base = 0;
    int opcode; 
    long long param1, param2, dest;
    int a,b,c,d,e;

    intcode[1]=noun;
    intcode[2]=verb;

    auto bad_access = [&](const string& reason) {
        ostringstream os;
        os << "Intcode error: " << reason << "\n";
        os << "ptr=" << ptr << " size=" << intcode.size() << "\n";
        if (ptr < intcode.size()) os << "opcode at ptr = " << intcode[ptr] << "\n";
        os<< "modes=(" << a << "," << b << "," << c << ")\n";
        throw runtime_error(os.str());
    };

    int full_opcode = (int)intcode[ptr];
    opcode=full_opcode%100;
    while(opcode!=99){

        a=full_opcode/10000;
        b=(full_opcode/1000)%10;
        c=(full_opcode/100)%10;
        
        //print("DEBUG: Decoded opcode {} into {}, modes=({}, {}, {})\n", intcode[ptr], opcode, a, b, c);

        //wersja z bezpiecznym czytaniem
        //to tak jak bysmy psowiecali trochew mocy obliczneiowej procesora na rzecz braku dostępu do niektórych miejsc w pamieci
        //mozna zostac przy poprzednim podejsciu ale to mi sie bardziej podoba i latwiej w nim rzucac wyjatki przy wyjsciu z zakresu
        //ale znowu - kosztem wydajnosci

        if ((opcode == 3) && c == 1)
                    throw runtime_error("Destination parameter cannot be in immediate mode");
        switch(opcode){
            case 1: case 2: case 7: case 8:
                //three-parameter instructions
                param1 = parameter(c, ptr + 1, intcode,relative_base);
                param2 = parameter(b, ptr + 2, intcode,relative_base);
                if (a == 1)
                    throw runtime_error("Destination parameter cannot be in immediate mode");
                dest = parameter(a, ptr + 3, intcode,relative_base);
                break;
            case 3: case 4: case 9:
                //one-parameter instructions
                param1 = parameter(c, ptr + 1, intcode,relative_base);
                param2=0;dest=0;
                break;
            case 5: case 6:
                //two-parameter instructions
                param1 = parameter(c, ptr + 1, intcode,relative_base);
                param2 = parameter(b, ptr + 2, intcode,relative_base);
                dest=0;
                break;
            default:
                throw runtime_error("Unknown opcode: " + to_string(opcode));
        }
        print("DEBUG: ptr={}, opcode={}, modes=({}, {}, {}), param1={}, param2={}, dest={}\n", ptr, opcode, a, b, c, param1, param2, dest);
  
        //wyjatki
        if (ptr >= intcode.size()) bad_access("instruction pointer out of range (ptr >= size)");
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
            case 4:{
                //print("DEBUG: Outputting value at {}, value={}\n", param1, intcode[param1]);
                //long long output_value = intcode[param1];
                long long val = intcode[param1];
                println("output: {}", val);

                ptr += 2;}
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
            case 9:
                relative_base += intcode[param1];
                //print("DEBUG: Adjusting relative base by {}, new relative base={}\n", intcode[param1], relative_base);
                ptr +=2;
                break;
                
        }
        full_opcode = static_cast<int>(intcode[ptr]);
        opcode=full_opcode%100;
    }

    //print("DEBUG: Halting program.\n");
    //Sleep(1);
    return intcode[0];


}

