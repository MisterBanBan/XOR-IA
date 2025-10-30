#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "neural_network.h"

NeuralNetwork *create_network(int *topology, int num_layers) {
    int i = 0;
    int j = 0;

    NeuralNetwork *network = (NeuralNetwork *)calloc(1, sizeof(NeuralNetwork));
    if (!network) {
        fprintf(stderr, "Failed to allocate memory for NeuralNetwork\n");
        return NULL;
    }
    
    NeuralLayer *layer = (NeuralLayer *)calloc(num_layers, sizeof(NeuralLayer));
    if(!layer) {
        fprintf(stderr, "Failed to allocate memory for NeuralLayer\n");
        free(network);
        return NULL;
    }
    
    network->layers = layer;  // ← CORRECTION ICI !
    network->num_layers = num_layers;
    
    while (i < num_layers) {
        layer[i].input_size = topology[i];
        layer[i].output_size = topology[i + 1];
        
        layer[i].weights = (float **)calloc(layer[i].output_size, sizeof(float *));
        if (!layer[i].weights) {
            fprintf(stderr, "Failed to allocate memory for weights\n");
            free_network(network);
            return NULL;
        }
        
        while (j < layer[i].output_size) {
            layer[i].weights[j] = (float *)calloc(layer[i].input_size, sizeof(float));
            if (!layer[i].weights[j]) {
                fprintf(stderr, "failed to allocate memory for weights row\n");
                free_network(network);
                return NULL;
            }
            j++;
        }
        j = 0;
        
        layer[i].biases = (float *)calloc(layer[i].output_size, sizeof(float));
        if(!layer[i].biases) {
            fprintf(stderr, "Failed to allocate memory for biases\n");
            free_network(network);
            return NULL;
        }
        
        layer[i].outputs = (float *)calloc(layer[i].output_size, sizeof(float));
        if (!layer[i].outputs) {
            fprintf(stderr, "failed to allocate memory for outputs\n");
            free_network(network);
            return NULL;
        }
        
        layer[i].inputs = (float *)calloc(layer[i].input_size, sizeof(float));
        if (!layer[i].inputs) {
            fprintf(stderr, "failed to allocate memory for inputs\n");
            free_network(network);
            return NULL;
        }
        
        i++;
    }
    return network;
}

void free_network(NeuralNetwork *network) {
    if(!network)
        return;
    
    if(network->layers) {
        for (int i = 0; i < network->num_layers; i++) {
            if(network->layers[i].weights) {
                for(int j = 0; j < network->layers[i].output_size; j++) {
                    free(network->layers[i].weights[j]);
                }
                free(network->layers[i].weights);
            }
            free(network->layers[i].biases);
            free(network->layers[i].outputs);
            free(network->layers[i].inputs);
        }
        free(network->layers);
    }
    free(network);
}

int main() {
    printf("=== Test du réseau de neurones ===\n\n");
    
    int topology[] = {2, 4, 1};
    int num_layers = 2;
    
    printf("Création du réseau [2 -> 4 -> 1]...\n");
    NeuralNetwork *nn = create_network(topology, num_layers);
    
    if (nn == NULL) {
        printf("❌ Erreur: allocation échouée\n");
        return 1;
    }
    
    printf("✅ Réseau créé avec succès!\n\n");
    
    printf("Vérification des couches:\n");
    for (int i = 0; i < num_layers; i++) {
        printf("Couche %d: %d entrées -> %d neurones\n",
               i+1, 
               nn->layers[i].input_size,
               nn->layers[i].output_size);
    }
    
    printf("\nTest d'accès mémoire...\n");
    nn->layers[0].weights[0][0] = 0.5;
    nn->layers[0].biases[0] = 0.1;
    printf("✅ Accès mémoire OK\n");
    
    printf("\nLibération de la mémoire...\n");
    free_network(nn);
    printf("✅ Mémoire libérée\n");
    
    return 0;
}
