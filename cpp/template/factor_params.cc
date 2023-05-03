#include <iostream>

// Please refer to "Effective C++" item 44
// It puts data in derived class, and puts operations in base class

template <typename T>
class SquareMatrixBase {
    T* data;
    int size;
protected:
    SquareMatrixBase(int n) : size(n), data(new T[n * n]) {
        for (int i = 0; i < n * n; i++) {
            data[i] = i;
        }
    }

    ~SquareMatrixBase() {
        delete[] data;
    }

    void transpose() {
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; ++j) {
                std::swap(data[i * size + j], data[j * size + i]);
            }
        }
    }

    void print() {
        for (int i = 0; i < size * size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T, int size>
class SquareMatrix : private SquareMatrixBase<T> {
public:
    SquareMatrix() : SquareMatrixBase<T>(size) {
    }

    ~SquareMatrix() {
    }

    void transpose() {
        SquareMatrixBase<T>::transpose();
    }

    void print() {
        SquareMatrixBase<T>::print();
    }
};

int main() {
    SquareMatrix<int, 5> matrix;
    matrix.transpose();
    matrix.print();
    return 0;
}