/****************************************************************/
/* Includes
/****************************************************************/

#include "perceptron.h"

using namespace ADJZAI001_perceptron;
using namespace std;

int instances;
vector<training_instance> and_training;
vector<training_instance> or_training;
vector<training_instance> nand_training;

/****************************************************************/
/* Functions
/****************************************************************/

bool ADJZAI001_perceptron::load_training(string filename, vector<training_instance> & training) {
    ifstream file(filename);
    string line;    // hold line in file
    float val;
    float target;

    if (file.is_open()) {

        getline(file, line);
        istringstream inst(line);
        inst >> instances;

        for (int i = 0; i < instances; ++i) {
            getline(file, line);
            istringstream temp(line);

            f_vect values;
            for (int j = 0; j < 2; ++j) {
                temp >> val;
                values.push_back(val);
            }
            temp >> target;
            training.push_back(training_instance(values, target));
        }

        file.close();
        return true;
    }
    else {
        cout << "could not open " << filename << endl; 
        return false;
    }  
}

int main(int argc, char const *argv[]) {
    
    if (argc > 1) {
        string test = string(argv[1]);

        if (load_training("training/and.txt", and_training)) {
            cout << "AND training data loaded: " << and_training.size() << " instances" << endl;

            perceptron and_p = perceptron(
                { 0, 0 }, { 0, 0 }, 1.5, 0.2
            );

            int it = 0, converge = 0;
            while (converge < instances) {
                converge = 0;
                cout << "Iteration " << it+1 << endl;
                for (int i = 0; i < instances; ++i) {
                    and_p.change_values(and_training[i].values);
                    and_p.adjust_weights(and_training[i]);

                    if (and_p.convergence == 2) converge++;
                }
                it++;
            }

            cout << and_p << endl;
        }

        if (load_training("training/or.txt", or_training)) {
            cout << "OR training data loaded: " << or_training.size() << " instances" << endl;

            perceptron or_p = perceptron(
                { 0, 0 }, { 0, 0 }, 0.5, 0.2
            );

            int it = 0, converge = 0;
            while (converge < instances) {
                converge = 0;
                cout << "Iteration " << it+1 << endl;
                for (int i = 0; i < instances; ++i) {
                    or_p.change_values(or_training[i].values);
                    or_p.adjust_weights(or_training[i]);

                    if (or_p.convergence == 2) converge++;
                }
                it++;
            }

            cout << or_p << endl;
        }

        if (load_training("training/nand.txt", nand_training)) {
            cout << "NAND training data loaded: " << nand_training.size() << " instances" << endl;

            perceptron nand_p = perceptron(
                { 0, 0 }, { 0, 0 }, -1.5, 0.2
            );

            int it = 0, converge = 0;
            while (converge < instances) {
                converge = 0;
                cout << "Iteration " << it+1 << endl;
                for (int i = 0; i < instances; ++i) {
                    nand_p.change_values(nand_training[i].values);
                    nand_p.adjust_weights(nand_training[i]);

                    if (nand_p.convergence == 2) converge++;
                }
                it++;
            }

            cout << nand_p << endl;
        }
    }
    else {
        cout << "input file missing" << endl;
    }
    return 0;
}

ostream & ADJZAI001_perceptron::operator<<(ostream & os, perceptron & p) {
    os << "Weights:" << endl;
    for (int n = 0; n < p.weights.size(); ++n) {
        os << n+1 << " " << p.weights[n] << endl;
    }
    return os;
}
