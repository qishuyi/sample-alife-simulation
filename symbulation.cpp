//
//  symbulation.cpp
//  
//
//  Created by qi on 4/21/18.
//
//

#include "population.hpp"
#include "host.hpp"
#include <iostream>

int main(void) {
    Population population = Population();
    population.initialize();
    
    double initialCooperationMean = population.calculateCooperationMean();
    std::cout << "The initial population mean is: " << initialCooperationMean << std::endl;
    
    int iterations = 10;
    for (int i = 0; i < iterations; i++) {
        population.update();
    }
    
    double afterCooperationMean = population.calculateCooperationMean();
    std::cout << "The population mean after " << iterations << " iterations is: " << afterCooperationMean << std::endl;
    
    int iterations2 = 90;
    for (int i = 0; i < iterations2; i++) {
        population.update();
    }
    double afterCooperationMean2 = population.calculateCooperationMean();
    std::cout << "The population mean after 90 iterations is: " << afterCooperationMean2 << std::endl;
    
    return 0;
}
