#include "neural_network.h"

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
    
    network->layers = layer;
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
    printf("✅ Réseau créé\n");
    
    printf("\nInitialisation des poids...\n");
    init_network(nn);
    printf("✅ Poids initialisés\n");
    
    // Affichage de quelques poids pour vérification
    printf("\nÉchantillon de poids (couche 1):\n");
    for (int i = 0; i < 4; i++) {
        printf("  Neurone %d: w0=%.3f, w1=%.3f, bias=%.3f\n",
               i,
               nn->layers[0].weights[i][0],
               nn->layers[0].weights[i][1],
               nn->layers[0].biases[i]);
    }
    
    free_network(nn);
    printf("\n✅ Mémoire libérée\n");
    
    return 0;
}

