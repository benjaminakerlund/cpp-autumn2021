#include <iostream>
#include <vector>
#include <math.h>
#include "matrix.hpp"

// Implement the functions here
// Remember to use auto and ranged for-loops when they can be used!
// typedef std::vector<std::vector<int>> Matrix;

// Function reads input from user to n x n matrix,
// n is the width and height of the matrix --> user must give n^2 inputs.
Matrix ReadMatrix(int n) { //DONE
    Matrix m;
    int element;
    std::cout << "Please enter element: " << std::endl;
    
    for (auto out = 0; out < n; out++) {
        std::vector<int> row;
        for (auto it = 0; it < n; it++) {
            std::cin >> element;
            row.push_back(element);
        }
        m.push_back(row);
    }
    return m;
}


// Function rotates n x n matrix 90 degrees clockwise
// and stores it to a new matrix that it returns
Matrix Rotate90Deg(const Matrix & m) {
    Matrix newM = m; //The problem was, that I wasn't initializing the new matrix correctly...
    int n = newM.size();

    for (auto out = 0; out < n/2; out++) {
        //std::vector<int> col;
        for (auto in = out; in < n - out - 1; in++) {

            int temp = m[out][in];

            newM[out][in] = m[n - 1 - in][out]; //OK
            newM[n - 1 - in][out] = newM[n - 1 - out][n - 1 - in]; //OK

            newM[n - 1 - out][n - 1 - in] = newM[in][n - 1 - out]; //OK
            newM[in][n - 1 - out] = temp;
        }
    }

    return newM;
}




/* Function prints n x n matrix to standard output:
 * e.g. when n = 3 and the matrix' rows are all 1,2,3:
Printing out a 3 x 3 matrix:\n
1 2 3 \n
1 2 3 \n
1 2 3 \n
 */
void Print(const Matrix & m) { //DONE
    int n = m.size();
    std::cout << "Printing out a " << n << " x " << n << " matrix:" << std::endl; //REPLACE N with corresponding matrix dimensions.

    for (auto out = 0; out < n; out++) {
        for (auto in = 0; in < n; in++) {
            std::cout << m.at(out).at(in) << " ";
        }
        std::cout << std::endl;
    }
}