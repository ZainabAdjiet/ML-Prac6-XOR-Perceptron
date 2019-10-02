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

/****************************************************************/
/* Functions
/****************************************************************/

namespace ADJZAI001_perceptron {

    typedef std::vector<float> f_vect;

    struct perceptron {
        f_vect weights;
        f_vect values;
        float output;

        perceptron(f_vect w, f_vect v);
        void update_tick();
    };

    struct training_instance {
        f_vect values;
        int target;

        training_instance(f_vect v, int t);
    };

    bool load_training(std::string filename);
}

#endif
