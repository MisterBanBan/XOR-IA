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

