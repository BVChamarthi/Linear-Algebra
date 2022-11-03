#include <iostream>

#include "matrix.h"

int main() {
    matrix2<double> i3 = matrix2<double>::generateIdentity(4);
    std::cout << "Test 1: i3 = generateIdentity(4)\n";
    i3.print();

    std::cout << "\nTest 2: i3.switchRows(0, 1)\n";
    i3.switchRows(0, 1);
    i3.print();

    std::cout << "\nTest 3: i3.multiplyToRow(1, 1.5)\n";
    i3.multiplyToRow(1, 1.5);
    i3.print();
    
    std::cout << "\nTest 4: i3.addMultipleToRow(0, 1, 2.0)\n";
    i3.addMultipleToRow(0, 1, 2.0);
    i3.print();

    std::cout << "\nTest 5: i3.swapWithFirstNonZeroElem(0, 2)\n";
    i3.swapWithFirstNonZeroElem(0, 2);
    i3.print();

    std::cout << "\nTest 6: i3.zeroOutCol(1, 0)\n";
    i3.zeroOutCol(1, 0);
    i3.print();

    std::cout << "\nTest 7: i4 = i3.join(matrix2<double>::generateIdentity(4))\n";
    matrix2<double> i4 = i3.join(matrix2<double>::generateIdentity(4));
    i4.print();

    std::cout << "\nTest 8: i5 = i3.inverse()\n";
    matrix2<double> i5 = i3.inverse();
    i5.print();

    std::cout << "\nTest 9: check i3 * i5\n";
    (i3 * i5).print();

    std::cout << "\nTest 10: check i5 * i3\n";
    (i5 * i3).print();

    std::cout << "\nTest 11: det(i3) = " << i3.det();
    std::cout << "\nTest 12: det(i5) = " << i5.det();

    return 0;
}