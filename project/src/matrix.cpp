#include <iostream>
#include <limits>
#include <iomanip>
#include "matrix.h"
#include "exceptions.h"
#include "math.h"

#define EPS (std::numeric_limits<double>::epsilon()*1e-07)

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        this->matrix.assign(this->rows, std::vector<double>(this->cols, 0));
    }

    Matrix::Matrix(std::istream &is): rows(0), cols(0) {
        if (is.fail()) {
            throw InvalidMatrixStream();
        }
        if (!(is >> this->rows >> this->cols)) {
            throw InvalidMatrixStream();
        }
        this->matrix.assign(this->rows, std::vector<double>(this->cols, 0));
        for (size_t i = 0; i < this-> rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                if (!(is >> matrix[i][j])) {
                    throw InvalidMatrixStream();
                }
            }
        }
    }

    size_t Matrix::getRows() const {
        return this->rows;
    }

    size_t Matrix::getCols() const {
        return this->cols;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (this->rows <= i || this->cols <= j) {
            throw(OutOfRange(i, j, *this));
        }
        return this->matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (this->rows <= i || this->cols <= j) {
            throw(OutOfRange(i, j, *this));
        }
        return this->matrix[i][j];
    }

    bool Matrix::operator==(const Matrix& rhs) const {
        bool equal = true;
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            return false;
        }
        for (size_t i = 0; i < this->rows; i++) {
            if (equal == false) {
                break;
            }
            for (size_t j = 0; j < this->cols; j++) {
                if (std::abs((this->matrix[i][j] - rhs.matrix[i][j])) > EPS) {
                    equal = false;
                    break;
                }
            }
        }
        return equal;
    }

    bool Matrix::operator!=(const Matrix& rhs) const {
        bool equal = false;
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            return true;
        }
        for (size_t i = 0; i < this->rows; i++) {
            if (equal == true) {
                break;
            }
            for (size_t j = 0; j < this->rows; j++) {
                if (std::abs((this->matrix[i][j] - rhs.matrix[i][j])) < EPS) {
                    equal = true;
                    break;
                }
            }
        }
        return equal;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << matrix.rows << " " << matrix.cols << std::endl;
        for (size_t i = 0; i < matrix.rows; i++) {
            os << std::endl;
            for (size_t j = 0; j < matrix.cols; j++) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10) <<
                matrix.matrix[i][j] << " ";
            }
        }
        return os;
    }

    Matrix Matrix::operator+(const Matrix& rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            throw(DimensionMismatch(*this, rhs));
        }
        Matrix sum_matrix(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                sum_matrix.matrix[i][j] = this->matrix[i][j] + rhs.matrix[i][j];
            }
        }
        return sum_matrix;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            throw(DimensionMismatch(*this, rhs));
        }
        Matrix difference_matrix(rhs.rows, rhs.cols);
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                difference_matrix.matrix[i][j] = this->matrix[i][j] - rhs.matrix[i][j];
            }
        }
        return difference_matrix;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (this->cols != rhs.rows) {
            throw(DimensionMismatch(*this, rhs));
        }
        Matrix multiplication_matrix(this->rows, rhs.cols);
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < rhs.cols; j++) {
                for (size_t k = 0; k < this->cols; k++) {
                    multiplication_matrix.matrix[i][j] += this->matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }
        return multiplication_matrix;
    }

    Matrix Matrix::transp() const {
        Matrix transp_matrix(this->cols, this->rows);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                transp_matrix.matrix[j][i] = this->matrix[i][j];
            }
        }
        return transp_matrix;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix multiplication_matrix(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                multiplication_matrix.matrix[i][j] =  this->matrix[i][j] * val;
            }
        }
        return multiplication_matrix;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix multiplication_matrix(matrix.rows, matrix.cols);
        for (size_t i = 0; i < matrix.rows; i++) {
            for (size_t j = 0; j < matrix.cols; j++) {
                multiplication_matrix.matrix[i][j] =  matrix.matrix[i][j] * val;
            }
        }
        return multiplication_matrix;
    }

    double prep::Matrix::det() const {
        return 0;
    }

    Matrix prep::Matrix::adj() const {
        return Matrix{};
    }

    Matrix prep::Matrix::inv() const {
        return Matrix{};
    }

}  // namespace prep
