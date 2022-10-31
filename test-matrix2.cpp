#include <iostream>

#include "matrix.h"

template <class T> 
void printMatrix(matrix2<T> m) {
    if(m.r() == 0 || m.c() == 0) {
        std::cout << "empty matrix\n";
        return;
    }
    int rows = m.r();
    int cols = m.c();
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            std::cout << m(i, j) << '\t';
        }
        std::cout << '\n';
    }
}

int main() {
    std::cout << "test matrix2.h\n\n";

    // test 1: create and print a matrix
    double data[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    matrix2<double> m1(3,4,data);
    printMatrix(m1);

    // test 2: element retrieval
    std::cout << '\n';
    std::cout << m1(0,0) << '\n';
    std::cout << m1(1,0) << '\n';
    std::cout << m1(2,0) << '\n';
    std::cout << m1(0,1) << '\n';
    std::cout << m1(1,1) << '\n';
    std::cout << m1(2,1) << '\n';
    std::cout << m1(5,5) << '\n';

    // test 2: matrix multiplication
    std::cout << '\n';
    double data2[] = {1,2,3,1,2,3,1,2,3,1,2,3};
    matrix2<double> m2(4,3,data2);
    printMatrix(m2);
    std::cout << '\n';
    matrix2<double> m3 = m1 * m2;
    printMatrix(m3);

    // test 3: matrix vector multiplication
    std::cout << '\n';
    double data3[] = {1.5, 2.5, 3.5};
    matrix2<double> v1(3,1,data3);

    double data4[] = {1,0,0,0,1,0,0,0,1};
    matrix2<double> m4(3,3,data4);

    printMatrix(v1);
    std::cout << '\n';
    printMatrix(m4);
    std::cout << '\n';
    printMatrix(v1 * m4);
    std::cout << '\n';
    printMatrix(m4 * v1);
    std::cout << '\n';
    matrix2<double> m5 = m4 + 1.0;
    printMatrix(m5);
    std::cout << '\n';
    printMatrix(m5 * v1);

    // test 4: test == operator
    std::cout << "m1 == m2 : " << (m1 == m2) << '\n';
    matrix2<double> m6 = m1;
    std::cout << "m1 == m6 : " << (m1 == m6) << '\n';

    return 0;
}