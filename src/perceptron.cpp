/****************************************************************/
/* Includes
/****************************************************************/

#include "perceptron.h"

using namespace ADJZAI001_perceptron;

/****************************************************************/
/* Functions
/****************************************************************/

training_instance::training_instance(f_vect v, int t) :
    values(v), target(t) {}

perceptron::perceptron(f_vect w, f_vect v, float th, float e) :
    weights(w), values(v), threshold(th), eta(e) {}

void perceptron::change_values(f_vect v) {
    values = v;
}

void perceptron::adjust_weights(training_instance t) {
    float w_sum = 0;
    for (int i = 0; i < values.size(); ++i) {
        w_sum += values[i]*weights[i];
    }
    if (w_sum > threshold)
        output = 1;
    else
        output = 0;

    for (int i = 0; i < values.size(); ++i) {
        float delta_w = eta * (t.target - output) * values[i];
        
        if (weights[i] == weights[i] + delta_w)
            convergence++;
        weights[i] = weights[i] + delta_w;
    }
}