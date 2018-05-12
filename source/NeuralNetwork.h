
#pragma once


#include <vector>
#include "Neuron.h"

class NeuralNetwork {
public:
    NeuralNetwork(unsigned int inputSize, unsigned int outputSize, unsigned int hiddenLayers,
                  unsigned int hiddenLayersSize);

    void setInput(std::vector<double> &input);

    const std::vector<double> getOutput();

    void mutate(unsigned int mutationRate, unsigned int rateChange);

    virtual ~NeuralNetwork();

private:
    void init();
    std::vector<std::vector<Neuron*>> neuralNetwork;

    unsigned int inputSize;
    unsigned int outputSize;
    unsigned int hiddenLayersNb;
    unsigned int hiddenLayersSize;
};



