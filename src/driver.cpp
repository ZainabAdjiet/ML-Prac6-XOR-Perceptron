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

        if (load_training("and.txt", and_training)) {
            cout << "AND training data loaded: " << and_training.size() << " instances" << endl;

            perceptron and1 = perceptron(
                { 0, 0 }, { 0, 0 }, 1.5, 0.2
            );

            int it = 0;
            while (it < 5) {
                cout << "Iteration " << it+1 << endl;
                for (int i = 0; i < instances; ++i) {
                    and1.change_values(and_training[i].values);
                    and1.adjust_weights(and_training[i]);
                    cout << and1 << endl;
                }
                it++;
            }
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
