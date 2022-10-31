#ifndef MATRIX_H
#define MATRIX_H


/*******************************************************************************************************
CLASS DEFINITION
*******************************************************************************************************/
template<class T>
class matrix2 {         //template class for 2d matrix

    private:
        int row, col, num_elems;
        T* data;

        int index(int r, int c);  // function to convert 2d coords to index in 1d array

    public:
        // constructors
        matrix2();
        matrix2(int r, int c);
        matrix2(int r, int c, const T* d);
        matrix2(const matrix2<T>& obj);

        // destructor
        ~matrix2()

        // overload access operators
        T& operator() (int r, int c);
        const T& operator() (int r, int c) const;

        // get rows and columns
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
template <class T> matrix2<T>::matrix2(): row(1), col(1), num_elems(1) {
    data = new T[1];
    data[0] = 0.0;
}

// parametrized constructor, no data
template <class T> matrix2<T>::matrix2(int r, int c): row(r), col(c), num_elems(r*c) {
    data = new T[num_elems];
    for(int i = 0; i < num_elems; i++) {
        data[i] = 0.0;
    }
}

// parametrized constructor with data
template <class T> matrix2<T>::matrix2(int r, int c, const T* d): row(r), col(c), num_elems(r*c) {
    data = new T[num_elems];
    for(int i = 0; i < num_elems; i++) {
        data[i] = d[i];
    }
}

// copy constructor
template <class T> matrix2<T>::matrix2(const matrix2<T>& obj): row(obj.row), col(obj.col), num_elems(obj.num_elems) {
    data = new T[num_elems];
    for(int i = 0; i < num_elems; i++) {
        data[i] = obj.data[i];
    }
}

// destructor
template <class T> matrix2<T>::~matrix2() {
    if(data != nullptr) delete data;
}

#endif // !MATRIX_H