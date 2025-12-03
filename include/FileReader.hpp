#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>



std::string readFile(const std::string& path) {
    const std::size_t MAX_FILE_SIZE = 10'000'000; // 10 MB

    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) throw std::runtime_error("Nie mozna otworzyc pliku");

    std::ifstream::pos_type pos = file.tellg();
    if (pos == std::ifstream::pos_type(-1)) throw std::runtime_error("Nie mozna odczytac rozmiaru pliku");

    std::size_t size = static_cast<std::size_t>(pos);
    if (size > MAX_FILE_SIZE) throw std::runtime_error("Plik zbyt duzy");

    std::string buffer(size, '\0');
    file.seekg(0, std::ios::beg);
    file.read(&buffer[0], static_cast<std::streamsize>(size));

    if (file.gcount() != static_cast<std::streamsize>(size)) {
        throw std::runtime_error("Blad podczas czytania pliku");
    }

    return buffer;
}


    
    
