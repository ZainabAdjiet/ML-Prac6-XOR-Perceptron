/****************************************************************/
/* Includes
/****************************************************************/

#include "perceptron.h"

using namespace ADJZAI001_perceptron;

/****************************************************************/
/* Struct Functions
/****************************************************************/

/*
* creates training instance using vector of values and a target value
*/
training_instance::training_instance(f_vect v, int t) :
    values(v), target(t) {}

/*
* creates perceptron using:
* w - vector of weights
* v - vector of values
* th - theta/threshold
* e - eta/learning rate
*/
perceptron::perceptron(f_vect w, f_vect v, float th, float e) :
    weights(w), values(v), threshold(th), eta(e) {}

/*
* changes input values of perceptron
*/
void perceptron::change_values(f_vect & v) {
    values = v;
}

/*
* calculates the weighted sum of input values using
* threshold activation function and stores in output
*/
void perceptron::weighted_sum() {
    float w_sum = 0;
    for (int i = 0; i < values.size(); ++i) {
        w_sum += values[i]*weights[i];
    }
    if (w_sum > threshold)
        output = 1;
    else
        output = 0;
}

/*
* adjusts the input weights based on perceptron learning rule, using training instance target
*/
void perceptron::adjust_weights(int target) {
    convergence = 0;
    for (int i = 0; i < values.size(); ++i) {
        float delta_w = eta * (target - output) * values[i];
        
        if (weights[i] == weights[i] + delta_w)
            convergence++;
        weights[i] = weights[i] + delta_w;
    }
}