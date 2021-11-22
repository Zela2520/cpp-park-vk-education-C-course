#pragma once // NOLINT

#include <vector>
#include <istream>

namespace prep {
class Matrix {
  size_t rows;
  size_t cols;
  std::vector<std::vector<double>> matrix;
  std::vector<std::vector<double>> adj_matrix;

 public:
  explicit Matrix(size_t rows = 0, size_t cols = 0);
  explicit Matrix(std::istream& input_stream);
  Matrix(const Matrix& rhs) = default;
  Matrix& operator=(const Matrix& rhs) = default;
  ~Matrix() = default;

  size_t getRows() const;
  size_t getCols() const;

  double operator()(size_t row, size_t col) const;
  double& operator()(size_t row, size_t col);

  bool operator==(const Matrix& rhs) const;
  bool operator!=(const Matrix& rhs) const;

  Matrix operator+(const Matrix& rhs) const;
  Matrix operator-(const Matrix& rhs) const;
  Matrix operator*(const Matrix& rhs) const;

  Matrix operator*(double val) const;

  friend
  Matrix operator*(double val, const Matrix& matrix);
  friend
  std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
  friend
  void fill_minor(const Matrix& matrix, size_t del_row, size_t del_col, Matrix* new_matrix);
  friend
  Matrix return_filled_minor(const Matrix& matrix, size_t del_row, size_t del_col, Matrix* new_matrix);

  Matrix transp() const;
  double det() const;
  Matrix adj() const;
  Matrix inv() const;
};

Matrix operator*(double val, const Matrix& matrix);
std::ostream& operator<<(std::ostream& output_stream, const Matrix& matrix);
void fill_minor(const Matrix& matrix, size_t del_row, size_t del_col, Matrix* new_matrix);
Matrix return_filled_minor(const Matrix& matrix, size_t del_row, size_t del_col, Matrix* new_matrix);
}  // namespace prep
