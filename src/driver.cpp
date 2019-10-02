/****************************************************************/
/* Includes
/****************************************************************/

#include "perceptron.h"

using namespace ADJZAI001_perceptron;
using namespace std;

int instances;
vector<training_instance> training;

/****************************************************************/
/* Functions
/****************************************************************/

bool ADJZAI001_perceptron::load_training(std::string filename) {
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
        string input = string(argv[1]);

        if (load_training(input)) {
            cout << "training data loaded: " << training.size() << " instances" << endl;  
        }
    }
    else {
        cout << "input file missing" << endl;
    }
    return 0;
}
