#include <iostream>
#include <limits>
#include <iomanip>
#include "matrix.h"
#include "exceptions.h"
#include "math.h"

#define EPS (std::numeric_limits<double>::epsilon()*1e-07)
#define eps 1e7
#define TRUE 1

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols) :
    rows(rows),
    cols(cols) {
        this->matrix.assign(this->rows, std::vector<double>(this->cols, 0));
        this->adj_matrix.assign(this->rows, std::vector<double>(this->cols, 0));
    }

    Matrix::Matrix(std::istream &input_stream) :
    rows(0),
    cols(0) {
        if (input_stream.fail()) {
            throw InvalidMatrixStream();
        }

        if (!(input_stream >> this->rows >> this->cols)) {
            throw InvalidMatrixStream();
        }

        this->matrix.assign(this->rows, std::vector<double>(this->cols, 0));
        this->adj_matrix.assign(this->rows, std::vector<double>(this->cols, 0));

        for (auto& row : this->matrix) {
            for (auto& element : row) {
                if (!(input_stream >> element)) {
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

    double Matrix::operator()(size_t row, size_t col) const {
        if (this->getRows() <= row || this->getCols() <= col) {
            throw(OutOfRange(row, col, *this));
        }
        return this->matrix[row][col];
    }

    double& Matrix::operator()(size_t row, size_t col) {
        if (this->getRows() <= row || this->getCols() <= col) {
            throw(OutOfRange(row, col, *this));
        }
        return this->matrix[row][col];
    }

    bool Matrix::operator==(const Matrix& rhs) const {
        bool is_equal = true;

        if (this->getRows() != rhs.rows || this->getCols() != rhs.cols) {
            return false;
        }

        for (size_t i = 0; i < this->getRows(); ++i) {
            if (is_equal == false) {
                break;
            }

            for (size_t j = 0; j < this->getCols(); ++j) {
                if (std::abs((this->matrix[i][j] - rhs.matrix[i][j])) > EPS) {
                    is_equal = false;
                    break;
                }
            }
        }
        return is_equal;
    }

    bool Matrix::operator!=(const Matrix& rhs) const {
        bool is_equal = false;

        if (this->getRows() != rhs.getRows() || this->getCols() != rhs.getCols()) {
            return true;
        }

        for (size_t i = 0; i < this->getRows(); ++i) {
            if (is_equal == true) {
                break;
            }

            for (size_t j = 0; j < this->getCols(); ++j) {
                if (std::abs((this->matrix[i][j] - rhs.matrix[i][j])) < EPS) {
                    is_equal = true;
                    break;
                }
            }
        }
        return is_equal;
    }

    std::ostream& operator<<(std::ostream& output_stream, const Matrix& matrix) {
        output_stream << matrix.rows << " " << matrix.cols << std::endl;

        for (const auto& row : matrix.matrix) {
            output_stream << std::endl;
            for (const auto& element : row) {
                output_stream << std::setprecision(std::numeric_limits<double>::max_digits10) <<
                element << " ";
            }
        }
        return output_stream;
    }

    Matrix Matrix::operator+(const Matrix& rhs) const {
        if (this->getRows() != rhs.getRows() || this->getCols() != rhs.getCols()) {
            throw(DimensionMismatch(*this, rhs));
        }

        Matrix sum_matrix(this->rows, this->cols);

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                sum_matrix.matrix[i][j] = this->matrix[i][j] + rhs.matrix[i][j];
            }
        }
        return sum_matrix;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const {
        if (this->getRows() != rhs.getRows() || this->getCols() != rhs.getCols()) {
            throw(DimensionMismatch(*this, rhs));
        }

        Matrix difference_matrix(rhs.rows, rhs.cols);

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                difference_matrix.matrix[i][j] = this->matrix[i][j] - rhs.matrix[i][j];
            }
        }
        return difference_matrix;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (this->getCols() != rhs.getRows()) {
            throw(DimensionMismatch(*this, rhs));
        }

        Matrix multiplication_matrix(this->rows, rhs.cols);

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < rhs.cols; ++j) {
                for (size_t k = 0; k < this->cols; ++k) {
                    multiplication_matrix.matrix[i][j] += this->matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }
        return multiplication_matrix;
    }

    Matrix Matrix::transp() const {
        Matrix transp_matrix(this->cols, this->rows);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                transp_matrix.matrix[j][i] = this->matrix[i][j];
            }
        }
        return transp_matrix;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix multiplication_matrix(this->rows, this->cols);

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
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

    void fill_minor(const Matrix& matrix, size_t del_row, size_t del_col, Matrix* new_matrix) {
	    size_t miss_rows = 0;

	    for (size_t i = 0; i < matrix.rows; ++i) {
		    if (i != del_row) {
			    size_t miss_cols = 0;

			    for (size_t j = 0; j < matrix.cols; ++j) {
				    if (del_col != j) {
					    new_matrix->matrix[i - miss_rows][j - miss_cols] = matrix.matrix[i][j];
				    } else {
					    ++miss_cols;
				    }
			    }
		    } else {
			    ++miss_rows;
		    }
	    }
    }

    double prep::Matrix::det() const {
        if (this->rows != this->cols) {
            throw(DimensionMismatch(*this));
        }

        if (this->rows == 1) {
            return this->matrix[0][0];
        } else if (this->rows == 2) {
            return ((this->matrix[0][0] * this->matrix[1][1])
            - (this->matrix[0][1] * this->matrix[1][0]));
        }

        Matrix minor_matrix(this->rows - 1, this->cols - 1);
        double sum_res = 0;
        int sig_n = 1;

        for (size_t col = 0; col < this->cols; ++col) {
			fill_minor(*this, 0, col, &minor_matrix);
		    double temp_res = minor_matrix.det() * this->matrix[0][col];
			sum_res += sig_n * temp_res;
			sig_n *= -1;
		}
        return sum_res;
    }

    Matrix return_filled_minor(const Matrix& matrix, size_t del_row, size_t del_col, Matrix* new_matrix) {
	    size_t miss_rows = 0;

	    for (size_t i = 0; i < matrix.rows; ++i) {
		    if (i != del_row) {
			    size_t miss_cols = 0;

			    for (size_t j = 0; j < matrix.cols; ++j) {
				    if (del_col != j) {
					    new_matrix->matrix[i - miss_rows][j - miss_cols] = matrix.matrix[i][j];
				    } else {
					    ++miss_cols;
				    }
			    }
		    }   else {
			    ++miss_rows;
		    }
	    }
	    return *new_matrix;
    }

    Matrix prep::Matrix::adj() const {
        if (this->getRows() != this->getCols()) {
            throw(DimensionMismatch(*this));
        }

		const Matrix& transpon_matrix = transp();
		Matrix new_matrix(this->rows, this->cols);
		Matrix minor_matrix(this->rows - 1, this->cols - 1);

		for (size_t i = 0; i < transpon_matrix.rows; ++i) {
			for (size_t j = 0; j < transpon_matrix.cols; ++j) {
                double minor_res = 0.0;
                return_filled_minor(transpon_matrix, i, j, &minor_matrix);
				minor_res = minor_matrix.det();
				int minor_sign = 1;

				if ((i + j) % 2 == TRUE) {
					minor_sign = -1;
				}

                new_matrix.adj_matrix[i][j] = minor_res * minor_sign;
				new_matrix.matrix[i][j] = std::trunc((minor_res * minor_sign) * eps) / eps;
			}
		}
        return new_matrix;
    }

    Matrix prep::Matrix::inv() const {
        if (this->getRows() != this->getCols()) {
            throw(DimensionMismatch(*this));
        }

		double det_matrix = det();

		if (det_matrix == 0) {
            throw(SingularMatrix());
        }

		if (this->rows == 1) {
            Matrix newmatrix(1, 1);
            newmatrix.matrix[0][0] = 1 / this->matrix[0][0];
			return newmatrix;
		}

        const Matrix& adj_matrix = adj();
		Matrix newmatrix(this->rows, this->cols);

        for (size_t i = 0; i < newmatrix.rows; ++i) {
            for (size_t j = 0; j < newmatrix.cols; ++j) {
                newmatrix.matrix[i][j] =  std::trunc((adj_matrix.adj_matrix[i][j] / det_matrix) * eps) / eps;
            }
        }
	    return newmatrix;
    }
}  // namespace prep
