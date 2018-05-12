
#pragma once


#include <vector>

class Neuron {
public:
    Neuron();
    explicit Neuron(const std::vector<Neuron*> &leftLayers);
    virtual ~Neuron();

    void setValue(double value);
    double getValue() const;

    void mutate(unsigned int mutationRate, unsigned int changeRate);

private:
    double inputValue = 0;

    bool useReLU = false;

    std::vector<Neuron*> leftLayers;
    std::vector<double> weights;
    double bias = 0;
};



