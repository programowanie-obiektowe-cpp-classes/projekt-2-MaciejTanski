#pragma once
#include <vector>
#include <stdexcept>
#include <sstream>


using namespace std;

auto computer(vector<int>& intcode){
    int ptr = 0;
    int opcode, param1, param2, dest;
    const size_t N = intcode.size();

    auto bad_access = [&](const string& reason) {
        ostringstream os;
        os << "Intcode error: " << reason << "\n";
        os << "ptr=" << ptr << " size=" << N << "\n";
        if (ptr < N) os << "opcode at ptr = " << intcode[ptr] << "\n";
        throw runtime_error(os.str());
    };

    while(true){
        opcode = intcode[ptr];
        param1 = intcode[ptr + 1];
        param2 = intcode[ptr + 2];
        dest = intcode[ptr + 3];

        if (opcode==99){
            return intcode;
        }

        if (ptr >= N) bad_access("instruction pointer out of range (ptr >= size)");
        if (param1 < 0 || param2 < 0 || dest < 0) bad_access("parameter index negative");
        if (static_cast<size_t>(param1) >= N) bad_access("param1 index out of range: " + to_string(param1));
        if (static_cast<size_t>(param2) >= N) bad_access("param2 index out of range: " + to_string(param2));
        if (static_cast<size_t>(dest) >= N) bad_access("dest index out of range: " + to_string(dest));

        switch(opcode){

            default:
                throw std::runtime_error("Unknown opcode");

            case 1:
                intcode[dest] = intcode[param1] + intcode[param2];
                break;
            case 2:
                intcode[dest] = intcode[param1] * intcode[param2];
                break;
        }
        ptr += 4;
    }

}
