#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float **weights;
    float *biases;
    float *outputs;
    float *inputs;
    int input_size;
    int output_size;
} NeuralLayer;

typedef struct {
    NeuralLayer *layers;
    int num_layers;
} NeuralNetwork;

// Déclarations des fonctions
NeuralNetwork* create_network(int *topology, int num_layers);
void free_network(NeuralNetwork *network);
void init_network(NeuralNetwork *network);
void init_layer(NeuralLayer *layer);
float random_float(float min, float max);

#endif // NEURAL_NETWORK_H
