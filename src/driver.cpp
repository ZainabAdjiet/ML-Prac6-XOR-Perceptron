/****************************************************************/
/* Includes
/****************************************************************/

#include "perceptron.h"

using namespace ADJZAI001_perceptron;
using namespace std;

/****************************************************************/
/* Functions
/****************************************************************/

bool ADJZAI001_perceptron::load_data(string filename, vector<training_instance> & training) {
    ifstream file(filename);
    string line;    // hold line in file
    float val;
    float target;
    int instances;

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

void ADJZAI001_perceptron::train_perceptron(perceptron & perc, vector<training_instance> & training) {
    int it = 0, converge = 0, instances = training.size();
    while (converge < instances) {
        converge = 0;
        ++it;
        for (int i = 0; i < instances; ++i) {
            perc.change_values(training[i].values);
            perc.weighted_sum();
            perc.adjust_weights(training[i].target);

            if (perc.convergence == 2) converge++;
        }
    }
    cout << "After " << it << " iterations:" << endl;
    cout << perc << endl;
}

int main(int argc, char const *argv[]) {
    
    if (argc > 1) {
        string test = string(argv[1]);

        vector<training_instance> and_training;
        vector<training_instance> or_training;
        vector<training_instance> nand_training;

        vector<training_instance> test_data;

        perceptron and_p = perceptron(
                { 0, 0 }, { 0, 0 }, 1.5, 0.2
            );

        perceptron or_p = perceptron(
                { 0, 0 }, { 0, 0 }, 0.5, 0.2
            );

        perceptron nand_p = perceptron(
                { 0, 0 }, { 0, 0 }, -1.5, 0.2
            );

        if (load_data("training/and.txt", and_training)) {
            cout << "AND training data loaded: " << and_training.size() << " instances" << endl;
            train_perceptron(and_p, and_training);
        }

        if (load_data("training/or.txt", or_training)) {
            cout << "OR training data loaded: " << or_training.size() << " instances" << endl;
            train_perceptron(or_p, or_training);
        }

        if (load_data("training/nand.txt", nand_training)) {
            cout << "NAND training data loaded: " << nand_training.size() << " instances" << endl;
            train_perceptron(nand_p, nand_training);
        }

        if (load_data(test, test_data)) {

            for (int i = 0; i < test_data.size(); ++i) {

                cout << test_data[i];

                nand_p.change_values(test_data[i].values);
                nand_p.weighted_sum();

                or_p.change_values(test_data[i].values);
                or_p.weighted_sum();

                f_vect outputs = { (float) nand_p.output, (float) or_p.output };
                and_p.change_values(outputs);
                and_p.weighted_sum();

                cout << endl;
                cout << "NAND: " << nand_p.output << " OR: " << or_p.output << " AND: " << and_p.output << endl;
                cout << "MLP Output: " << and_p.output << endl << endl;
            }
        }
    }
    else {
        cout << "test data file missing" << endl;
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

ostream & ADJZAI001_perceptron::operator<<(ostream & os, training_instance & t) {
    os << "Values:" << endl;
    for (int n = 0; n < t.values.size(); ++n) {
        os << n+1 << " " << t.values[n] << endl;
    }
    os << "Target: " << t.target << endl;
    return os;
}