#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#define MAX_NxN_MATRIX_SIZE 100

/*
    Dev:            William A. Morris
    Created:        2023-10-19
    Last Modified:  2023-10-19

    KUID:           3057236
    Email:          morris.william@ku.edu
    Class:          EECS 348 
    Lab Section:    Thursdays @11am

    Description:    
        A simple (and probably unsafe) C Program to preform several basic matrix operations
*/

/**
 * function to initialize a block of memory to store a NxN MATRIX of specified size N
*/
void initialize_square_matrix(int** & matrix, int matrixSize);

/**
 * function to print a string to next available console line
*/
void println(std::string toPrint);

/**
 * function to print out an NxN matrix of known N
*/
void print_square_matrix(int** & matrixToPrint, int matrixSize);

/** 
 * function to initialize and populate an NxN matrix of known N
 *  with vector containing matrix data in left->right top->bottom order 
*/
void populate_square_matrix(int** & matrixToFill, std::vector<std::string>& fillWith, int vectorOffset, int matrixSize);

/**
 * function to initialize and populate two NxN matrices 
 *  from the provided file (given as path)
 *  and return N
*/
int read_matrices_from_file(int** & matrixA, int** & matrixB, const std::string& filePath);

/**
 * function to create a new NxN matrix with the SUM of two NxN matrices
*/
void get_matrix_sum(int** & dest, int** & matrixA, int** & matrixB, int matrixSize);

/**
 * function to create a new NxN matrix with the PRODUCT of two NxN matrices
*/
void get_matrix_product(int** & dest, int** & matrixA, int** & matrixB, int matrixSize);

/**
 * function to create a new NxN matrix with the DIFFERENCE of two NxN matrices
*/
void get_matrix_difference(int** & dest, int** & matrixA, int** & matrixB, int matrixSize);


int main(int argc, char** argv) {
    // bring macro into main scope for program use
    static const int MAX_MATRIX_SIZE = (int) MAX_NxN_MATRIX_SIZE;

    // user must pass in a file containing matrix size and two matrices of specified size
    if (argc != 2) {
        // if incorrect num of args provided, print appropriate error
        println("Please enter an input file to read!\nie) program.app ./input.txt");
        // and return with error status
        return 1;
    }

    // store file path in string variable
    const std::string filePath(argv[1]);
    // initialize all necessary arrays  
    int **matrixA, **matrixB, **matrixSum, **matrixProduct, **matrixDifference;
    // read two matrices from file and store determined size
    const int matrixSize = read_matrices_from_file(matrixA, matrixB, filePath);

    // if determined matrix size is LARGER than program max
    if (matrixSize > MAX_MATRIX_SIZE) {
        // report error to user
        std::cout<< "NxN matrix may not have N larger than " << MAX_MATRIX_SIZE << "...";
        // and return with error status
        return 1;
    }

    // begin main program output
    // print required name/title
    println("\nWilliam Morris, 3057236");
    println("Lab #6: Matrix Multiplication\n");
    
    // output matrix A (given)
    println("Matrix A: ");
    print_square_matrix(matrixA, matrixSize);

    // output matrix B (given)
    println("Matrix B: ");
    print_square_matrix(matrixB, matrixSize);

    // preform matrix sum operation on matrix A and B
    // save to SUM matrix
    get_matrix_sum(matrixSum, matrixA, matrixB, matrixSize);
    // output SUM matrix
    println("Matrix Sum (A + B): ");
    print_square_matrix(matrixSum, matrixSize);

    // perform matrix product operation on matrix A and B
    // save to PRODUCT matrix
    get_matrix_product(matrixProduct, matrixA, matrixB, matrixSize);
    // output PRODUCT matrix
    println("Matrix Product (A * B): ");
    print_square_matrix(matrixProduct, matrixSize);

    // perform matrix difference operation on matrix A and B
    // save to DIFFERENCE matrix
    get_matrix_difference(matrixDifference, matrixA, matrixB, matrixSize);
    // output DIFFERENCE matrix
    println("Matrix Difference (A - B): ");
    print_square_matrix(matrixDifference, matrixSize);

    // return without errors :)
    return 0;
}

void println(std::string toPrint) {
    // bring std into current namespace
    using namespace std;
    // use cout to output string to console
    // use endl to create a new line after outputting the desired string
    cout << toPrint << endl;
}

void print_square_matrix(int** & matrixToPrint, int matrixSize) {
    // bring std into current namespace
    using namespace std;
    
    // for every entry in the matrix
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) 
            // output current value with space between for readability
            cout << matrixToPrint[i][j] << ' ';
        // for every row in the matrix, output on new line
        cout << endl;
    } 
    // create blank line after matrix output
    cout << endl;
}

void populate_square_matrix(int** & matrixToFill, std::vector<std::string>& fillWith, int vectorOffset, int matrixSize) {
    // initialize memory for matrix
    initialize_square_matrix(matrixToFill, matrixSize);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            // and fill matrix with values read from file
            matrixToFill[i][j] = std::stoi(fillWith[vectorOffset + ((matrixSize*i) + j)]);
        }
    }
}

int read_matrices_from_file(int** & matrixA, int** & matrixB, const std::string& filePath) {
    // open desired file
    std::ifstream inputFile(filePath, std::ios::in);

    // and throw error if file could not be opened
    if (!inputFile.is_open()) 
        throw std::runtime_error("File needs to be open");

    // declare string buffer
    std::string buffer;
    // and vector to store all read matrix data
    std::vector<std::string> rawMatrixData;
    // get first line from the file, corresponding to size N for NxN matrix
    std::getline(inputFile, buffer);
    // and save as constant int after string->int conversion
    const int matrixSize = stoi(buffer);

    // while the file can be read
    while (inputFile) {
        // read every line into buffer 
        while (std::getline(inputFile, buffer, '\n')) {
            // create stream from current line in file
            std::stringstream s(buffer);
            // and save each number in the line separated by whitespace
            while (std::getline(s, buffer, ' ')) rawMatrixData.push_back(buffer);
        }       
    }

    // close the file after all data has been extracted
    inputFile.close();

    // populate first matrix A with data from file
    // start at beginning of data vector
    populate_square_matrix(matrixA, rawMatrixData, 0, matrixSize);
    // populate second matrix B with data from file
    // start reading from N^2 position in the vector
    // so that no data from Matrix A overlaps into B
    populate_square_matrix(matrixB, rawMatrixData, (matrixSize*matrixSize), matrixSize);
    // return derived matrix size
    return matrixSize;
}

void get_matrix_sum(int** & dest, int** & matrixA, int** & matrixB, int matrixSize) {
    // init matrix to store summation
    initialize_square_matrix(dest, matrixSize);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            // for every entry in A and B, add together and store in new matrix
            dest[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

void get_matrix_product(int** & dest, int** & matrixA, int** & matrixB, int matrixSize) {
    // init matrix to store product
    initialize_square_matrix(dest, matrixSize);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            // for every entry in every row in matrix A, 
            // multiply by every entry in every column in matrix B
            for (int k = 0; k < matrixSize; k++)
                // and save the sum of these products to appropriate location in new matrix
                dest[i][j] += matrixA[i][k] * matrixB[k][j];
        }
    }
}

void get_matrix_difference(int** & dest, int** & matrixA, int** & matrixB, int matrixSize) {
    // init matrix to store difference
    initialize_square_matrix(dest, matrixSize);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            // for every entry in A and B, subtract val B from A and save to new matrix
            dest[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
}

void initialize_square_matrix(int** & matrix, int matrixSize) {
    // allocate memory for an array of N size populated with int* 
    matrix = (int**) malloc(sizeof(int*) * matrixSize);

    for (int i = 0; i < matrixSize; i++) 
        // every entry in allocated array will contain an array of size N
        matrix[i] = (int*) malloc(sizeof(int) * matrixSize);
}
