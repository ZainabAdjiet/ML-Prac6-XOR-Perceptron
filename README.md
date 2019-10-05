# ML Lab 6: XOR Perceptron Training

## How it works:

* An XOR perceptron is achieved by training individual 2-input, threshold activation perceptrons and linking them to form a Multi-Layered Perceptron
* The first layer is made up of a NAND and an OR perceptron into which both input values are fed
* The second layer is a single AND perceptron into which the outputs of the NAND and OR perceptrons are fed
* The program trains these perceptrons using training data in the 'training' folder and tests the XOR on given test data

## How to run:

1. Run 'make' to compile
2. Running 'make run' will run the following command:
    './perceptron test_data.txt output.txt'
3. But the program can be called like:
    ./perceptron [test_data_file] [output_file]

## Input file format

* (Line 1) [n - number of test instances]
* (Line 2 - n) [value1] [value2] [target output]