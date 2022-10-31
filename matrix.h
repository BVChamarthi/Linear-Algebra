#ifndef MATRIX_H
#define MATRIX_H


/*******************************************************************************************************
CLASS DEFINITION
*******************************************************************************************************/
template<class T>
class matrix2 {         //template class for 2d matrix

    private:
        int row, col;
        T* data;

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

};

// overload == operator
template <class T> bool operator== (const matrix2<T>&lhs, const matrix2<T>& rhs);

// overload addition operator
template <class T> matrix2<T> operator+ (const matrix2<T>& lhs, const matrix2<T>& rhs);
template <class T> matrix2<T> operator+ (const T& lhs, const matrix2<T>& rhs);
template <class T> matrix2<T> operator+ (const matrix2<T>& lhs, const T& rhs);

// overload subtraction operator
template <class T> matrix2<T> operator- (const matrix2<T>& lhs, const matrix2<T>& rhs);
template <class T> matrix2<T> operator- (const T& lhs, const matrix2<T>& rhs);
template <class T> matrix2<T> operator- (const matrix2<T>& lhs, const T& rhs);

// overload multiplication operator
template <class T> matrix2<T> operator* (const matrix2<T>& lhs, const matrix2<T>& rhs);
template <class T> matrix2<T> operator* (const T& lhs, const matrix2<T>& rhs);
template <class T> matrix2<T> operator* (const matrix2<T>& lhs, const T& rhs);


/*******************************************************************************************************
CONSTRUCTORS / DESTRUCTORS
*******************************************************************************************************/
// default constructor

#endif // !MATRIX_H