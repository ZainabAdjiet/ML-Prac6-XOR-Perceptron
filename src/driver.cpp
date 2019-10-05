/****************************************************************/
/* Includes
/****************************************************************/

#include "perceptron.h"

using namespace ADJZAI001_perceptron;
using namespace std;

/****************************************************************/
/* Perceptron training functions
/****************************************************************/

/*
* loads training/test data from a file into a given vector
*/
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

/*
* trains a given threshold activation perceptron using the training data to adjust weights
* outputs number of iterations needed to train perceptron
*/
int ADJZAI001_perceptron::train_perceptron(perceptron & perc, vector<training_instance> & training) {
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
    return it;
}

/****************************************************************/
/* Main function
/****************************************************************/

int main(int argc, char const *argv[]) {
    
    if (argc > 2) {
        string out = string(argv[2]);
        ofstream outfile(out);

        if (outfile.is_open()) {
            vector<training_instance> and_training;
            vector<training_instance> or_training;
            vector<training_instance> nand_training;

            /*
            * initialises perceptrons needed for XOR perceptron with
            * initial weights and values of zero and
            * learning rate of 0.2
            */

            // initialise AND perceptron bias to 1.5
            perceptron and_p = perceptron(
                    { 0, 0 }, { 0, 0 }, 1.5, 0.2
                );

            // initialise OR perceptron to 0.5
            perceptron or_p = perceptron(
                    { 0, 0 }, { 0, 0 }, 0.5, 0.2
                );

            // initialise NAND perceptron to -1.5
            perceptron nand_p = perceptron(
                    { 0, 0 }, { 0, 0 }, -1.5, 0.2
                );

            // train each perceptron with their respective training examples
            int it = 0;
            if (load_data("training/and.txt", and_training)) {
                outfile << "AND training data loaded: " << and_training.size() << " instances" << endl;
                it = train_perceptron(and_p, and_training);

                outfile << and_p;
                outfile << "Converged after " << it << " iterations" << endl << endl;
            }

            if (load_data("training/or.txt", or_training)) {
                outfile << "OR training data loaded: " << or_training.size() << " instances" << endl;
                it = train_perceptron(or_p, or_training);

                outfile << or_p;
                outfile << "Converged after " << it << " iterations" << endl << endl;
            }

            if (load_data("training/nand.txt", nand_training)) {
                outfile << "NAND training data loaded: " << nand_training.size() << " instances" << endl;
                it = train_perceptron(nand_p, nand_training);

                outfile << nand_p;
                outfile << "Converged after " << it << " iterations" << endl << endl;
            }

            /*
            * load test data and link AND, OR and NAND perceptrons to build XOR perceptron
            * also compare XOR outputs to expected outputs for test data instances
            */

            string test = string(argv[1]);
            vector<training_instance> test_data;

            if (load_data(test, test_data)) {
                outfile << "XOR test data loaded: " << test_data.size() << " instances" << endl;

                for (int i = 0; i < test_data.size(); ++i) {

                    outfile << test_data[i];

                    // pass both values through NAND
                    nand_p.change_values(test_data[i].values);
                    nand_p.weighted_sum();

                    // pass both values through OR
                    or_p.change_values(test_data[i].values);
                    or_p.weighted_sum();

                    // pass outputs of OR and NAND through AND to get final output
                    f_vect outputs = { (float) nand_p.output, (float) or_p.output };
                    and_p.change_values(outputs);
                    and_p.weighted_sum();
                    
                    outfile << "MLP XOR Output: " << and_p.output << endl << endl;
                }
            }
        }
        else {
            cout << "could not write to " << out << endl;
        }
    }
    else {
        cout << "Program call: ./perceptron [test_data_file] [output_file]" << endl;
    }
    return 0;
}

// Prints perceptron information
ostream & ADJZAI001_perceptron::operator<<(ostream & os, perceptron & p) {
    os << "Threshold: " << p.threshold << endl;
    os << "Learning rate: " << p.eta << endl;
    os << "Weights:" << endl;
    for (int n = 0; n < p.weights.size(); ++n) {
        os << n+1 << " " << p.weights[n] << endl;
    }
    return os;
}

// Prints training instance
ostream & ADJZAI001_perceptron::operator<<(ostream & os, training_instance & t) {
    os << "Values:" << endl;
    for (int n = 0; n < t.values.size(); ++n) {
        os << n+1 << " " << t.values[n] << endl;
    }
    os << "Target: " << t.target << endl;
    return os;
}