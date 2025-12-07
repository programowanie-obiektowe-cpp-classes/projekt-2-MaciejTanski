#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include <ranges>

auto intcodeParser(const std::string& input)
{
    return input | 
        std::views::split(',') | 
        std::views::transform([](auto&& str){
            return std::stoll(std::string{str.data(), str.size()});
        }) | 
        std::ranges::to< std::vector >();
}