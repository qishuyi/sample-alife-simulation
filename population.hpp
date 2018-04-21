//
//  population.hpp
//  
//
//  Created by qi on 4/21/18.
//
//

#include "host.hpp"
#include <list>

#ifndef population_h
#define population_h

class Population {
    std::list<Host> population;
    
public:
    Population();
    
    void initialize();
    
    void update();
    
    double calculateCooperationMean();
};

#endif /* population_h */
