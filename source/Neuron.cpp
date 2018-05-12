#include <iostream>
#include <cmath>
#include "Neuron.h"

Neuron::Neuron() {
    //Give it the list of the input of the layer before
    leftLayers = std::vector<Neuron*>(0);
    weights = std::vector<double>(leftLayers.size(), 0);
}

Neuron::Neuron(const std::vector<Neuron*> &leftLayers) : leftLayers(leftLayers) {
    weights = std::vector<double>(leftLayers.size(), 0);
}


void Neuron::setValue(double value) {
    Neuron::inputValue = value;
}

double Neuron::getValue() const {

    if(leftLayers.empty()) {
        //It is an input neuron so return the given value
        return inputValue;
    }

    //It is not an input neuron
    //totalValue = (w1 * a1 + w2 * a2 + .... + wn * an)
    double totalValue = 0;
    for(int i = 0; i < leftLayers.size(); i++) {
        double newVal = (leftLayers)[i]->getValue();
        totalValue += weights[i] * newVal;
    }

    //Add the bias to the total value
    totalValue += bias;

    //Squish the totalValue in a sigmoid function
    if(!useReLU) {
        return 1.0 / (1.0 + exp(-totalValue));
    }
    //Or in a ReLU function
    if(useReLU) {
        return totalValue > 0 ? totalValue : 0;
    }

}

void Neuron::mutate(unsigned int mutationRate, unsigned int changeRate) {

    for(int i = 0; i < weights.size(); i++) {
        double rand1 = (double) rand() / RAND_MAX;

        // rand1 * 100 = [ 0 ; 100 [
        if(rand1 * 100 <= mutationRate) {

            double rand2 = (double) rand() / RAND_MAX;

            //(change the weight within a number between - (changeRate% / 2) and (changeRate% / 2))
            weights[i] += (rand2 * (changeRate / 100.0)) - ((changeRate / 100) / 2.0);
        }
    }

}


Neuron::~Neuron() {

}

