#ifndef MATRIX_H
#define MATRIX_H


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
        int rows();
        int cols();

        // overload == operator
        bool operator== (const matrix2<T>& rhs);

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

};


/*******************************************************************************************************
CONSTRUCTORS / DESTRUCTORS
*******************************************************************************************************/
// default constructor
template <class T> matrix2<T>::matrix2(): rows(1), cols(1), num_elems(1) {
    data = new T[1];
    data[0] = 0.0;
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
template <class T> matrix2<T>::matrix2(const matrix2<T>& obj): rows(obj.row), cols(obj.col), num_elems(obj.num_elems) {
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
    if(r >= row || c >= col || r < 0 || c < 0) return -1;
    else return r * col + c;
}

// setter
template <class T> T& matrix2<T>::operator() (int r, int c) { 
    int ind = index(r, c);
    if(ind < 0) return nullptr;
    else return data[ind];
}

// getter
template <class T> const T& matrix2<T>::operator() (int r, int c) const { 
    int ind = index(r, c);
    if(ind < 0) return 0;
    else return data[ind];
}

/*******************************************************************************************************
GETTERS FOR ROWS AND COLUMNS
*******************************************************************************************************/
//get rows
template <class T> int matrix2<T>::rows() { return rows; }

//get columns
template <class T> int matrix2<T>::cols() { return cols; }

/*******************************************************************************************************
OPERATOR OVERLOADS
*******************************************************************************************************/

// the == operator
template <class T> bool matrix2<T>::operator== (const matrix2<T>& rhs) {
    if( (row != rhs.rows) || (col != rhs.cols) ) return false;

    for(int i = 0; i < num_elems; i++) {
        if(data[i] != rhs.data[i]) return false;
    }
    return true;
}

// matrix + matrix
template <class U> matrix2<U> operator+ (const matrix2<U>& lhs, const matrix2<U>& rhs) {
    if(lhs.rows != rhs.rows || lhs.cols != rhs.cols) return nullptr;
    matrix2 ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] + rhs.data[i];
    }
    return ans;
}

// scalar + matrix
template <class U> matrix2<U> operator+ (const U& lhs, const matrix2<U>& rhs) {
    matrix2 ans(rhs.rows, rhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs + rhs.data[i];
    }
    return ans;
}

// matrix + scalar
template <class U> matrix2<U> operator+ (const matrix2<U>& lhs, const U& rhs) {
    matrix2 ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] + rhs;
    }
    return ans;
}

// matrix - matrix
template <class U> matrix2<U> operator- (const matrix2<U>& lhs, const matrix2<U>& rhs) {
    if(lhs.rows != rhs.rows || lhs.cols != rhs.cols) return nullptr;
    matrix2 ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] - rhs.data[i];
    }
    return ans;
}

// scalar - matrix
template <class U> matrix2<U> operator- (const U& lhs, const matrix2<U>& rhs) {
    matrix2 ans(lrhs.rows, rhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs - rhs.data[i];
    }
    return ans;
}

// matrix - scalar
template <class U> matrix2<U> operator- (const matrix2<U>& lhs, const U& rhs) {
    matrix2 ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] - rhs;
    }
    return ans;
}

// matrix * matrix
template <class U> matrix2<U> operator* (const matrix2<U>& lhs, const matrix2<U>& rhs) {
    if(lhs.cols != rhs.rows) return nullptr;
    matrix2 ans(lhs.rows, rhs.cols);
    for(int i = 0; i < ans.rows; i++) {
        for(int j = 0; j < ans.cols; j++) {
            for(int k = 0; k < lhs.cols; k++) {
                ans(i,j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
    return ans;
}

// scalar * matrix
template <class U> matrix2<U> operator* (const U& lhs, const matrix2<U>& rhs) {
    matrix2 ans(rhs.rows, rhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs * rhs.data[i];
    }
    return ans;
}

// matrix * scalar
template <class U> matrix2<U> operator* (const matrix2<U>& lhs, const U& rhs) {
    matrix2 ans(lhs.rows, lhs.cols);
    for(int i = 0; i < ans.num_elems; i++) {
        ans.data[i] = lhs.data[i] * rhs;
    }
    return ans;
}


#endif // !MATRIX_H