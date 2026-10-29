#pragma once
#include <vector>

class Calculator {
public:
    Calculator() = default;
    
    float average(const std::vector<float>& values);
};
