#include <stdlib.h>
#include <time.h>

#include "neural_network.h"

float random_float(float float_min, float float_max) {
    float scale = rand() / (float) RAND_MAX; // [0, 1.0]
    return float_min + scale * (float_max - float_min); // if a = 2 and b = 5 => [2, 5] this nb is 2 + scale * (5 - 2)
}

void init_layer(NeuralLayer *layer) {
    float limit = 0;
    limit = sqrt(6.0f / layer->input_size);
    for (int i = 0; i < layer->output_size; i++) {
        for (int j = 0; j < layer->input_size; j++) {
            layer->weights[i][j] = random_float(-limit, limit);
        }
        layer->biases[i] = 0.0f;
    }
}

void init_network(NeuralNetwork *network) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < network->num_layers; i++) {
        init_layer(&network->layers[i]);
    }
}