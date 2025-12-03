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
using namespace std;

int main() {
    // Day 2a
    string path = "../data/inp_d2.txt";
    auto result = day2a(path);
    print("Result day 2a: {}\n", result);

    // Day 2b
    print("Result day 2b: {}\n", day2b(path));
    return 0;
}
