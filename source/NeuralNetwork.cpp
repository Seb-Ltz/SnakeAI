#include <iostream>
#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(unsigned int inputSize, unsigned int outputSize, unsigned int hiddenLayers,
                             unsigned int hiddenLayersSize) : inputSize(inputSize), outputSize(outputSize),
                                                              hiddenLayersNb(hiddenLayers),
                                                              hiddenLayersSize(hiddenLayersSize) {
    init();
}

void NeuralNetwork::setInput(std::vector<double> &input) {

    //Replace the values of the input layer
    for(int i = 0; i < input.size(); i++) {
        neuralNetwork[0][i]->setValue(input[i]);
    }

}

void NeuralNetwork::init() {
    //Init the layers with Neurons

    //Init the input layer
    std::vector<Neuron*> inputLayer;
    for(unsigned int i = 0; i < inputSize; i++) {
        inputLayer.emplace_back(new Neuron());
    }
    neuralNetwork.push_back(inputLayer);

    //Init the hidden layers
    for(unsigned int i = 0; i < hiddenLayersNb; i++) {
        std::vector<Neuron*> hiddenLayer;
        for(unsigned j = 0; j < hiddenLayersSize; j++) {
            hiddenLayer.emplace_back(new Neuron(neuralNetwork[i]));
        }
        neuralNetwork.push_back(hiddenLayer);
    }

    //Init the output layer
    std::vector<Neuron*> outputLayer;
    for(int i = 0; i < outputSize; i++) {
        outputLayer.emplace_back(new Neuron(neuralNetwork[hiddenLayersNb]));
    }
    neuralNetwork.push_back(outputLayer);

}

const std::vector<double> NeuralNetwork::getOutput() {
    std::vector<Neuron*> outputLayer = neuralNetwork[hiddenLayersNb + 1];
    std::vector<double> outputValues;

    for (auto &outputNeuron : outputLayer) {
        outputValues.push_back(outputNeuron->getValue());
    }

    return outputValues;
}

void NeuralNetwork::mutate(unsigned int mutationRate, unsigned int rateChange) {

    for(int i = 1; i <= hiddenLayersNb + 1; i++) {
        for(int j = 0; j < neuralNetwork[i].size(); j++) {
            //Mutate the neuron's weights
            neuralNetwork[i][j]->mutate(mutationRate, rateChange);
        }
    }
}

NeuralNetwork::~NeuralNetwork() {
    //TODO: DELETE ALL VALUES

}
