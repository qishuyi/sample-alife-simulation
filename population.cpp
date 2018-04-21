//
//  population.cpp
//  
//
//  Created by qi on 4/8/18.
//
//

#include "population.hpp"
#include "host.hpp"
#include <iostream>
#include <ctime>
#include <iterator>
#include <list>
#include <random>

#define INVALID_SYMBIONT -2

Population::Population() {}

/**
 * Constructs a list of hosts.
 */
void Population::initialize() {
    // Initialize a list of host classes.
    std::list<Host> list_of_hosts;
    
    // Set up for calculating normal distribution.
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(-1.0,1.0);
    
    for (int i = 0; i < 500; i++) {
        // Make a symbiont object with a random cooperation probability between -1 and 1 and 0 resources.
        double prob_symbiont = distribution(generator);
        Symbiont symb = Symbiont(prob_symbiont, 0);
        
        // Initialize each host object with a random cooperation probability between -1 and 1, 0 resources and a symbiont.
        double prob_host = distribution(generator);
        Host new_host = Host(prob_host, 0, symb);
        list_of_hosts.push_back(new_host);
    }
    
    population = list_of_hosts;
}

/**
 * Loops through all the organisms in the population and do the following:
 * 1. Updates each host.
 * 2. Checks for reproduction of the host.
 * 3. Checks for reproduction of its symbiont.
 */
void Population::update() {
    std::list<Host>::iterator iter;
    for (iter = population.begin(); iter != population.end(); iter++){
        iter->update();
        
        // If the host has 100 resources, it gets to reproduce.
        if (iter->getResource() >= 100) {
            Host hostOffspring = iter->reproduce();
            
            // Replace a random host in the population with the offspring
            int index = rand() % 500;
            std::list<Host>::iterator iter2 = population.begin();
            for (int j = 0; j < index; j++) {
                iter2++;
            }
            *iter2 = hostOffspring;
        }
        
        if (iter->symbiont.getResource() >= 50) {
            Symbiont symbiontOffspring = iter->symbiont.reproduce();

            // Inject the symbiont offspring into a random host
            // If the host already has a symbiont (it is already infected), then horizontal transmission fails.
            int index = rand() % 500;
            std::list<Host>::iterator iter2 = population.begin();
            for (int j = 0; j < index; j++) {
                iter2++;
            }
            
            // Pick a random host in the population, if that host already has a symbiont, do nothing; otherwise, inject the offspring symbiont into the host.
            if (iter2->symbiont.getCooperationProb() != -2) {
                iter2->symbiont = symbiontOffspring;
            }
        }
    }
}

/**
 * Calculates the average cooperation probability of the population and returns it.
 */
double Population::calculateCooperationMean() {
    double cooperationSum = 0.0;
    std::list<Host>::iterator iter;
    
    for (iter = population.begin(); iter != population.end(); iter++) {
        cooperationSum += iter->getCooperationProb();
    }
    
    return cooperationSum/500;
}
