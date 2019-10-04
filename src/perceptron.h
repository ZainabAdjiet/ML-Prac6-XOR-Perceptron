#ifndef PERCEPTRON_H
#define PERCEPTRON_H

/****************************************************************/
/* Includes
/****************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

/****************************************************************/
/* Functions
/****************************************************************/

namespace ADJZAI001_perceptron {

    typedef std::vector<float> f_vect;

    struct training_instance {
        f_vect values;
        int target;

        training_instance(f_vect v, int t);
    };

    struct perceptron {
        float threshold;
        float eta;
        f_vect weights;
        f_vect values;
        int output;

        int convergence;

        perceptron(f_vect w, f_vect v, float th, float e);
        void change_values(f_vect & v);
        void weighted_sum();
        void adjust_weights(int target);
    };

    bool load_data(std::string filename, std::vector<training_instance> & training);
    void train_perceptron(perceptron & perc, std::vector<training_instance> & training);
    std::ostream & operator<<(std::ostream & os, perceptron & p);
    std::ostream & operator<<(std::ostream & os, training_instance & t);
}

#endif
