#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <print>
#include <ranges>
#include <filesystem>

#include "FileReader.hpp"
#include "IntcodeParser.hpp"
#include "Day2.hpp"
#include "Day5.hpp"
#include "Day9.hpp"

using namespace std;

int main() {
     // Day 2a
    string path = "../data/inp_d2.txt";
    auto result = day2a(path);
    print("Result day 2a: {}\n", result);//odp 3101878

    // Day 2b
    print("Result day 2b: {}\n", day2b(path));//odp 8444

    // Day 5a
    auto path5 = "../data/inp_d5.txt";
    day5a(path5);//odp 13787043

    day5b(path5); //odp 3892695

    // Day 9a
    //day9tests();

    day9a();// odp 3638931938

    // day 9b
    day9b();// odp 86025
    return 0;
}
