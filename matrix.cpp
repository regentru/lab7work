#include <cmath>
#include <iostream>

class Matrix {
protected:
	int rows;
	int cols;
	double** elements;

public:
	Matrix(int rows = 5, int cols = 5);
	Matrix(const Matrix& other);
	~Matrix();

	Matrix& operator=(const Matrix& other);

	void set(int rows, int cols, double element);
	int getRows() const;
	int getCols() const;
	double getElement(int rows, int cols) const;

	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(double num) const;
	Matrix operator*(const Matrix& other) const;

	Matrix transpose() const;

	friend std::istream& operator>>(std::istream& in, Matrix& matrix);
	friend std::ostream& operator<<(std::ostream& out, Matrix& matrix);
};

//square 
class QMatrix : public Matrix {
public:
	QMatrix(int size);
	QMatrix(const Matrix& other);
	QMatrix inverse() const;
	double determinant() const;
	QMatrix submatrix(int row, int col) const;
	QMatrix adjoint() const;
};

//construct
Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;

    elements = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        elements[i] = new double[cols];
    }
}

//copy construct 
Matrix::Matrix(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;

    elements = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        elements[i] = new double[cols];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            elements[i][j] = other.elements[i][j];
        }
    }
}

//destructor
Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] elements[i];
    }
    delete[] elements;
}

// get protected fields
int Matrix::getCols() const {
    return this->cols;
}
int Matrix::getRows() const {
    return this->rows;
}
double Matrix::getElement(int rows, int cols) const {
    return elements[rows][cols];
}
void Matrix::set(int rows, int cols, double element) {
    this->elements[rows][cols] = element;
}

// assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    this->~Matrix();
    rows = other.rows;
    cols = other.cols;

    elements = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        elements[i] = new double[cols];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            elements[i][j] = other.elements[i][j];
        }
    }
    return *this;
}

//matrix addition
Matrix Matrix::operator+(const Matrix& other) const {
    //size matrix check
    if (rows != other.rows || cols != other.cols) {
        throw "Matrixes sizes are not equal!!!";
    }

    Matrix result(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.elements[i][j] = elements[i][j] + other.elements[i][j];
        }
    }

    return result;
}

// matrix substraction
Matrix Matrix::operator-(const Matrix& other) const {
    //size matrix check
    if (rows != other.rows || cols != other.cols) {
        throw "Matrixes sizes are not equal!!!";
    }

    Matrix result(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.elements[i][j] = elements[i][j] - other.elements[i][j];
        }
    }

    return result;
}

// multiplication by a number
Matrix Matrix::operator*(double num) const {
    Matrix result(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.set(i, j, elements[i][j] * num);
        }
    }

    return result;
}

// multiplication by another matrix
Matrix Matrix::operator*(const Matrix& other) const {

    if (cols != other.rows) {
        throw "Sizes of the matrixes are incompatible";
    }

    Matrix result(rows, other.cols);

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            double sum = 0;
            for (int k = 0; k < cols; k++) {
                sum += elements[i][k] * other.elements[k][j];
            }
            result.elements[i][j] = sum;
        }
    }

    return result;
}

// matrix transposition
Matrix Matrix::transpose() const {
    Matrix result(cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.elements[j][i] = elements[i][j];
        }
    }

    return result;
}

std::istream& operator>>(std::istream& in, Matrix& matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            in >> matrix.elements[i][j];
        }
    }

    return in;
}
std::ostream& operator<<(std::ostream& out, Matrix& matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            out << matrix.elements[i][j] << " ";
        }
        out << std::endl;
    }

    return out;
}

// QMatrix construct
QMatrix::QMatrix(int size) : Matrix(size, size) { }
//QMatrix construct for Matrix
QMatrix::QMatrix(const Matrix& other) { 
    if (other.getCols() > other.getRows()) {
        rows = other.getRows();
        cols = other.getRows();
    }
    else {
        rows = other.getCols();
        cols = other.getCols();
    }
    this->elements = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        this->elements[i] = new double[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            this->elements[i][j] = other.getElement(i, j);
        }
    }
}

double QMatrix::determinant() const {

    //matrix HAS to be square
    if (rows != cols) {
        throw "Matrix has to be square!!";
    }

    double det = 0;
	
	//determinant of 1x1 matrix
    if (rows == 1) {
        det = elements[0][0];
    }
    else if (rows == 2) {
        //determinant of 2x2 matrix
        det = elements[0][0] * elements[1][1] -
            elements[0][1] * elements[1][0];
    }
    else {
        // determinant of mxm matrix
        for (int i = 0; i < rows; i++) {
            det += pow(-1, i) * elements[0][i] * submatrix(0, i).determinant();
        }
    }

    return det;
}

QMatrix QMatrix::submatrix(int row, int col) const {

    //submatrix sizes
    int subRow = rows - 1;
    int subCol = cols - 1;

    //create submatrix
    Matrix subMat(subRow, subCol);

    for (int i = 0; i < subRow; i++) {
        for (int j = 0; j < subCol; j++) {
            int indexI = i < row ? i : i + 1;
            int indexJ = j < col ? j : j + 1;

            subMat.set(i, j, elements[indexI][indexJ]);
        }
    }

    return subMat;
}

QMatrix QMatrix::inverse() const {
    double det = this->determinant();
	
    QMatrix adj = adjoint();

    QMatrix inverse(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            inverse.elements[i][j] = adj.elements[i][j] / det;
        }
    }

    return inverse;
}

QMatrix QMatrix::adjoint() const {
    QMatrix adj(rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            QMatrix sub = submatrix(i, j);

            double det = sub.determinant();

            adj.elements[j][i] = pow(-1, i + j) * det;
        }
    }

    return adj;
}
