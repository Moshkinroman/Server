#include "Calculator.h"
#include <numeric>

float Calculator::average(const std::vector<float>& values) {
    if (values.empty()) {
        return 0.0f;
    }
    
    float sum = std::accumulate(values.begin(), values.end(), 0.0f);
    return sum / values.size();
}
