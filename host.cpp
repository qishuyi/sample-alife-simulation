//
//  host.cpp
//
//
//  Created by qi on 4/6/18.
//
//

#include "host.hpp"
#include <iostream>
#include <random>

#define INVALID_SYMBIONT -2

Symbiont::Symbiont(double prob, double resource) : cooperationProb(prob), resource(resource) {}

/**
 * Returns the cooperation probability of the symbiont.
 */
double Symbiont::getCooperationProb() {
    return cooperationProb;
}

/**
 * Returns the resoruce of the symbiont.
 */
double Symbiont::getResource() {
    return resource;
}

/**
 * Updates the symbiont by:
 * 1. Donate back five times the received resource multiplied by cooperation probability to the host.
 * 2. The symbiont gets the rest resources.
 *
 * @param   res_in, the resources the symbiont receives from its host.
 * @returns the number of resources the symbiont donates back to its host.
 */
double Symbiont::update(double res_in) {
    // Donates Y * res_in multiplied by 5 back.
    double donate_back = res_in * cooperationProb;
    resource += (res_in - donate_back);
    return (donate_back * 5); // Think about 5 as the nutrition value. The host gives resource to the symbiont for this benefit.
}

/**
 * Adds some resource to the symbiont.
 *
 * @param res_in, the resources the symbiont receives to keep for itself
 */
void Symbiont::addResource(double res_in) {
    resource += res_in;
}

/**
 * Makes an offspring of the symbiont object.
 * The offspring will inherit the resources from the parent symbiont, with a chance of mutation changing their cooperation probability by Normaldistribution(0, 0.01)
 *
 * @returns the offspring symbiont
 */
Symbiont Symbiont::reproduce() {
    // Set up for calculating normal distribution
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> distribution(0, 0.01);
    
    // Add Normaldistribution(0, 0.01) to the symbiont's cooperation probability
    double prob = cooperationProb + distribution(generator);
    
    return Symbiont(prob, resource);
}

Host::Host(double prob, double resource, Symbiont symb) : cooperationProb(prob), resource(resource), symbiont(symb) {}

/**
 * Returns the cooperation probability of the host.
 */
double Host::getCooperationProb() {
    return cooperationProb;
}

/**
 * Returns the resoruce of the host.
 */
double Host::getResource() {
    return resource;
}

/**
 * Updates the host by:
 * 1. Gains 10 resources during an update.
 * 2. Host interacts with its symbiont with the 10 gained resources.
 * 3. Host gets whatever remains.
 */
void Host::update() {
    if (symbiont.getCooperationProb() != INVALID_SYMBIONT) {
        // Gains ten resource during each update
        int res_in = 10;
        if (cooperationProb > 0 && symbiont.getCooperationProb() > 0) {
            // Host donates proportion host_cooperationProb to symbiont
            double donate = res_in * cooperationProb;
            resource -= donate;
            // Symbiont returns five times proportion symbiont_cooperationProb back
            double res_return = symbiont.update(donate);
            res_in += res_return;
        }else if (cooperationProb < 0 && symbiont.getCooperationProb() > 0) {
            // Host invests in defense and doesn't interact with its symbiont
            double defense = res_in * cooperationProb;
            res_in -= defense;
        }else if (cooperationProb < 0 && symbiont.getCooperationProb() < 0) {
            // Host invests in defense
            double defense = res_in * cooperationProb;
            res_in -= defense;
            // Symbiont steals proportion (host_cooperationProb - symbiont_cooperationProb). Host gets the rest.
            double stolen = res_in * (cooperationProb - symbiont.getCooperationProb());
            res_in -= stolen;
            symbiont.addResource(stolen);
        }else if (cooperationProb > 0 && symbiont.getCooperationProb() < 0) {
            // Host donates proportion host_cooperationProb to symbiont.
            double donate = res_in * cooperationProb;
            res_in -= donate;
            // Symbiont steals an additional proportion symbiont_cooperationProb.
            double stolen = res_in * (- symbiont.getCooperationProb());
            res_in -= stolen;
            symbiont.addResource(donate + stolen);
        }
        // Host gets the remaining
        resource += res_in;
    }
}

/**
 * Makes an offspring of the host
 * The offspring will inherit the number of resources from its parent, with a chance of mutation changing their cooperation probability by Normaldistribution(0, 0.01).
 * There is a 20% chance that the host's symbiont reproduces and gets copied into the host's offspring as well.
 * If the symbiont doesn't get the chance to reproduce, we mark the offspring host's symbiont's cooperation probability as -2 to distinguish.
 *
 * @returns the offspring host
 */
Host Host::reproduce() {
    // Set up for calculating normal distribution
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> distribution(0, 0.01);
    
    Symbiont symbiontOffspring = Symbiont(INVALID_SYMBIONT, 0);
    // When the host reproduces, there is a 20% chance that the symbiont also reproduces and is copied into the host's offspring.
    // If the symbiont doesn't get to reproduce, the offspring host will have a symbiont with a cooperation probability at -2 to be marked as invalid.
    int transmissionProb = rand() % 10;
    if (transmissionProb < 2) {
        symbiontOffspring = symbiont.reproduce();
    }
    
    // The host uses 100 resoruces for reproduction
    resource -= 100;
    
    double prob = cooperationProb + + distribution(generator);
    return Host(prob, resource, symbiontOffspring);
}
