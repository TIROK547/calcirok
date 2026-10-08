#include <iostream>
#include "util.h"
#include <climits>
int main() {
    int array[4] = {10, 20, 30, 40};
    for(int val : array){
        std::cout << val << ' ';
    }
    std::cout << '\n';
    float anint = INT_MAX;
    std::cout << anint << '\n';
    std::cout << add(4, 3) << '\n';
    std::cout << subtract(4, 3) << '\n';
    std::cout << multiply(4, 3) << '\n';
    std::cout << divide(4, 3) << '\n';
}

