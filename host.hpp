//
//  host.hpp
//  
//
//  Created by qi on 4/6/18.
//
//

#ifndef host_hpp
#define host_hpp

#include <stdio.h>
#include <random>

class Symbiont {
    double cooperationProb;
    double resource;
    
public:
    Symbiont(double prob, double resource);
    
    double getCooperationProb();
    
    double getResource();
    
    double update(double res_in);
    
    void addResource(double res_in);
    
    Symbiont reproduce();
};

class Host {
    double cooperationProb;
    double resource;
    
public:
    Symbiont symbiont;
    
    Host(double prob, double resource, Symbiont symbt);
    
    double getCooperationProb();
    
    double getResource();
    
    void update();
    
    Host reproduce();
};
#endif /* host_hpp */
