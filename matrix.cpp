#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

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

void initialize_square_matrix(int** & matrix, int matrixSize);

void println(std::string toPrint);

void print_square_matrix(int** & matrixToPrint, int matrixSize);

void populate_square_matrix(int** & matrixToFill, std::vector<std::string>& fillWith, int vectorOffset, int matrixSize);

void read_matrices_from_file(int** & matrixA, int** & matrixB, int& matrixSize, std::string& filePath);

void get_matrix_sum(int** & dest, int** & matrixA, int** & matrixB, int matrixSize);

void get_matrix_product(int** & dest, int** & matrixA, int** & matrixB, int matrixSize);

void get_matrix_difference(int** & dest, int** & matrixA, int** & matrixB, int matrixSize);

int main(int argc, char** argv) {

    if (argc != 2) {
        println("Please enter an input file to read!");
        println("ie) program.app ./input.txt");

        return 1;
    }

    std::string filePath(argv[1]);
    int **matrixA, **matrixB, **matrixSum, **matrixProduct, **matrixDifference;
    int matrixSize;

    read_matrices_from_file(matrixA, matrixB, matrixSize, filePath);

    println("\nWilliam Morris, 3057236");
    println("Lab #6: Matrix Multiplication\n");
    
    println("Matrix A: ");
    print_square_matrix(matrixA, matrixSize);

    println("Matrix B: ");
    print_square_matrix(matrixB, matrixSize);

    get_matrix_sum(matrixSum, matrixA, matrixB, matrixSize);
    println("Matrix Sum (A + B): ");
    print_square_matrix(matrixSum, matrixSize);

    get_matrix_product(matrixProduct, matrixA, matrixB, matrixSize);
    println("Matrix Product (A * B): ");
    print_square_matrix(matrixProduct, matrixSize);

    get_matrix_difference(matrixDifference, matrixA, matrixB, matrixSize);
    println("Matrix Difference (A - B): ");
    print_square_matrix(matrixDifference, matrixSize);

    return 0;
}

void println(std::string toPrint) {
    std::cout << toPrint << std::endl;
}

void print_square_matrix(int** & matrixToPrint, int matrixSize) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) 
            std::cout << matrixToPrint[i][j] << ' ';
        std::cout << std::endl;
    } 
    std::cout << std::endl;
}

void populate_square_matrix(int** & matrixToFill, std::vector<std::string>& fillWith, int vectorOffset, int matrixSize) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixToFill[i][j] = std::stoi(fillWith[vectorOffset + ((matrixSize*i) + j)]);
        }
    }
}

void read_matrices_from_file(int** & matrixA, int** & matrixB, int& matrixSize, std::string& filePath) {

    std::ifstream inputFile(filePath, std::ios::in);

    if (!inputFile.is_open()) {
        throw std::runtime_error("File needs to be open");
    }

    std::string buffer;
    std::vector<std::string> vec;

    std::getline(inputFile, buffer);

    matrixSize = stoi(buffer);

    initialize_square_matrix(matrixA, matrixSize);
    
    initialize_square_matrix(matrixB, matrixSize);

    while (inputFile) {

        while (std::getline(inputFile, buffer, '\n')) {
           
            std::stringstream s(buffer);
            while (std::getline(s, buffer, ' ')) {
                vec.push_back(buffer);
            }
        }       

    }

    inputFile.close();

    populate_square_matrix(matrixA, vec, 0, matrixSize);
    populate_square_matrix(matrixB, vec, (matrixSize*matrixSize), matrixSize);
}

void get_matrix_sum(int** & dest, int** & matrixA, int** & matrixB, int matrixSize) {
    initialize_square_matrix(dest, matrixSize);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            dest[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

void get_matrix_product(int** & dest, int** & matrixA, int** & matrixB, int matrixSize) {
    initialize_square_matrix(dest, matrixSize);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            for (int k = 0; k < matrixSize; k++) {
                dest[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void get_matrix_difference(int** & dest, int** & matrixA, int** & matrixB, int matrixSize) {
    initialize_square_matrix(dest, matrixSize);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            dest[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
}

void initialize_square_matrix(int** & matrix, int matrixSize) {
    matrix = (int**) malloc(sizeof(int*) * matrixSize);

    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * matrixSize);
    }
}
