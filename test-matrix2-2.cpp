#include <iostream>

#include "matrix.h"

int main() {
    matrix2<double> i3 = matrix2<double>::generateIdentity(4);
    i3.print();
    std::cout << '\n';

    i3.switchRows(0, 1);
    i3.print();
    std::cout << '\n';

    i3.multiplyToRow(1, 1.5);
    i3.print();
    std::cout << '\n';

    i3.addMultipleToRow(0, 1, 2.0);
    i3.print();
    std::cout << '\n';

    return 0;
}