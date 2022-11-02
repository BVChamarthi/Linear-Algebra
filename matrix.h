#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>     // for debug
#include <math.h>


/*******************************************************************************************************
CLASS DEFINITION
*******************************************************************************************************/
template<class T>
class matrix2 {         //template class for 2d matrix

    private:
        int rows, cols, num_elems;
        T* data;

        int index(int r, int c);  // function to convert 2d coords to index in 1d array

    public:
        // constructors
        matrix2();
        matrix2(int r, int c);
        matrix2(int r, int c, const T* d);
        matrix2(const matrix2<T>& obj);

        // destructor
        ~matrix2();

        // overload access operators
        T& operator() (int r, int c);
        const T& operator() (int r, int c) const;

        // get number of rows and columns
        int r();
        int c();

        // overload == operator
        bool operator== (const matrix2<T>& rhs);

        // compare with tolerance
        bool compare(const matrix2<T>& rhs, double tolerance);

        // overload addition operator
        template <class U> friend matrix2<U> operator+ (const matrix2<U>& lhs, const matrix2<U>& rhs);
        template <class U> friend matrix2<U> operator+ (const U& lhs, const matrix2<U>& rhs);
        template <class U> friend matrix2<U> operator+ (const matrix2<U>& lhs, const U& rhs);

        // overload subtraction operator
        template <class U> friend matrix2<U> operator- (const matrix2<U>& lhs, const matrix2<U>& rhs);
        template <class U> friend matrix2<U> operator- (const U& lhs, const matrix2<U>& rhs);
        template <class U> friend matrix2<U> operator- (const matrix2<U>& lhs, const U& rhs);

        // overload multiplication operator
        template <class U> friend matrix2<U> operator* (const matrix2<U>& lhs, const matrix2<U>& rhs);
        template <class U> friend matrix2<U> operator* (const U& lhs, const matrix2<U>& rhs);
        template <class U> friend matrix2<U> operator* (const matrix2<U>& lhs, const U& rhs);

        // print function
        void print();

        // functions for calculating the inverse
        static matrix2<T> generateIdentity(int size);               // generates identity matrix of given size
        void switchRows(int r1, int r2);                            // r1 <-> r2
        void multiplyToRow(int r, const T m);                       // r -> m*r
        void addMultipleToRow(int d, int s, const T m);             // d -> d + m*s

        int getNonZeroElem(int c, int sr);                          // gets row value of 1st non-zero elem in column c,
                                                                    // starts searching from row sr
};


/*******************************************************************************************************
CONSTRUCTORS / DESTRUCTORS
*******************************************************************************************************/
// default constructor
template <class T> matrix2<T>::matrix2(): rows(0), cols(0), num_elems(0) {
    data = nullptr;
}

// parametrized constructor, no data
template <class T> matrix2<T>::matrix2(int r, int c): rows(r), cols(c), num_elems(r*c) {
    data = new T[num_elems];
    for(int i = 0; i < num_elems; i++) {
        data[i] = 0.0;
    }
}

// parametrized constructor with data
template <class T> matrix2<T>::matrix2(int r, int c, const T* d): rows(r), cols(c), num_elems(r*c) {
    data = new T[num_elems];
    for(int i = 0; i < num_elems; i++) {
        data[i] = d[i];
    }
}

// copy constructor
template <class T> matrix2<T>::matrix2(const matrix2<T>& obj): rows(obj.rows), cols(obj.cols), num_elems(obj.num_elems) {
    data = new T[num_elems];
    for(int i = 0; i < num_elems; i++) {
        data[i] = obj.data[i];
    }
}

// destructor
template <class T> matrix2<T>::~matrix2() {
    if(data != nullptr) delete[] data;
}


/*******************************************************************************************************
MEMORY ACCESS OPERATORS
*******************************************************************************************************/
// indexing function
template <class T> int matrix2<T>::index(int r, int c) {
    if(r >= rows || c >= cols || r < 0 || c < 0) return -1;
    else return r * cols + c;
}

// setter
template <class T> T& matrix2<T>::operator() (int r, int c) { 
    int ind = index(r, c);
    if(ind < 0) return *(new T());
    else return data[ind];
}

// getter
template <class T> const T& matrix2<T>::operator() (int r, int c) const { 
    int ind = index(r, c);
    if(ind < 0) return 0.0;
    else return data[ind];
}


/*******************************************************************************************************
GETTERS FOR ROWS AND COLUMNS
*******************************************************************************************************/
//get rows
template <class T> int matrix2<T>::r() { return rows; }

//get columns
template <class T> int matrix2<T>::c() { return cols; }


/*******************************************************************************************************
COMPARE WITH TOLERANCE
*******************************************************************************************************/
template <class T> bool matrix2<T>::compare(const matrix2<T>& rhs, double tolerance) {
    if(num_elems == 0) return 0.0;
    if(rows != rhs.rows || cols != rhs.cols) return false;
    int sumOfSqDiff = 0;
    for(int i = 0; i < num_elems; i++) {
        sumOfSqDiff += (data[i] - rhs.data[i]) * (data[i] - rhs.data[i]);
    }
    int rms = sqrt(sumOfSqDiff / num_elems);    // get root mean square
    return (rms < tolerance);                   // return whether rms is less than tolerance
}

/*******************************************************************************************************
OPERATOR OVERLOADS
*******************************************************************************************************/

// the == operator
template <class T> bool matrix2<T>::operator== (const matrix2<T>& rhs) {
    if( (rows != rhs.rows) || (cols != rhs.cols) ) return false;

    for(int i = 0; i < num_elems; i++) {
        if(data[i] != rhs.data[i]) return false;
    }
    return true;
}

// matrix + matrix
template <class U> matrix2<U> operator+ (const matrix2<U>& lhs, const matrix2<U>& rhs) {
    if(lhs.rows != rhs.rows || lhs.cols != rhs.cols) return *(new matrix2<U>());
    matrix2<U> ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] + rhs.data[i];
    }
    return ans;
}

// scalar + matrix
template <class U> matrix2<U> operator+ (const U& lhs, const matrix2<U>& rhs) {
    matrix2<U> ans(rhs.rows, rhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs + rhs.data[i];
    }
    return ans;
}

// matrix + scalar
template <class U> matrix2<U> operator+ (const matrix2<U>& lhs, const U& rhs) {
    matrix2<U> ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] + rhs;
    }
    return ans;
}

// matrix - matrix
template <class U> matrix2<U> operator- (const matrix2<U>& lhs, const matrix2<U>& rhs) {
    if(lhs.rows != rhs.rows || lhs.cols != rhs.cols) return *(new matrix2<U>());
    matrix2<U> ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] - rhs.data[i];
    }
    return ans;
}

// scalar - matrix
template <class U> matrix2<U> operator- (const U& lhs, const matrix2<U>& rhs) {
    matrix2<U> ans(rhs.rows, rhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs - rhs.data[i];
    }
    return ans;
}

// matrix - scalar
template <class U> matrix2<U> operator- (const matrix2<U>& lhs, const U& rhs) {
    matrix2<U> ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] - rhs;
    }
    return ans;
}

// matrix * matrix
template <class U> matrix2<U> operator* (const matrix2<U>& lhs, const matrix2<U>& rhs) {
    if(lhs.cols != rhs.rows) return *(new matrix2<U>());
    matrix2<U> ans(lhs.rows, rhs.cols);
    for(int i = 0; i < ans.rows; i++) {
        for(int j = 0; j < ans.cols; j++) {
            for(int k = 0; k < lhs.cols; k++) {
                ans.data[i*ans.cols + j] += lhs.data[i*lhs.cols + k] * rhs.data[k*rhs.cols + j];
            }
        }
    }
    return ans;
}

// scalar * matrix
template <class U> matrix2<U> operator* (const U& lhs, const matrix2<U>& rhs) {
    matrix2<U> ans(rhs.rows, rhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs * rhs.data[i];
    }
    return ans;
}

// matrix * scalar
template <class U> matrix2<U> operator* (const matrix2<U>& lhs, const U& rhs) {
    matrix2<U> ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] * rhs;
    }
    return ans;
}


/*******************************************************************************************************
PRINT FUNCTION
*******************************************************************************************************/
template <class T> void matrix2<T>::print() {
    if(rows == 0 || cols == 0) {
        std::cout << "empty matrix\n";
        return;
    }
    int k = 0; 
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            std::cout << data[k++] << '\t';
        }
        std::cout << '\n';
    }
}


/*******************************************************************************************************
FUNCTIONS FOR CALCULATING THE INVERSE
*******************************************************************************************************/
// generate identity
template <class T> matrix2<T> matrix2<T>::generateIdentity(int size) {
    if(size <=0) return *(new matrix2<T>());
    matrix2<T> ans(size, size);
    for(int i = 0; i < size; i++) {
        ans.data[i * size + i] = 1.0;
    }
    return ans;
}

// r1 <-> r2
template <class T> void matrix2<T>::switchRows(int r1, int r2) {
    if(r1 < 0 || r2 < 0 || r1 >= rows || r2 >= rows) return;
    T temp;
    for(int i = 0; i < cols; i++){
        temp = data[r1 * cols + i];
        data[r1 * cols + i] = data[r2 * cols + i];
        data[r2 * cols + i] = temp;
    }
}

// r -> m*r
template <class T> void matrix2<T>::multiplyToRow(int r, const T m) {
    if(r < 0 || r >= rows) return;
    for(int i = 0; i < cols; i++) {
        data[r * cols + i] *= m;
    }
}

// d -> d + m*s
template <class T> void matrix2<T>::addMultipleToRow(int d, int s, const T m) {
    if(d < 0 || s < 0 || d >= rows || s >= rows) return;
    for(int i = 0; i < cols; i++) {
        data[d * cols + i] += data[s * cols + i] * m;
    }
}

#endif // !MATRIX_H