#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// Init/release operations
void free_matrix(Matrix* matrix) {
	if (matrix == NULL) {
		puts("The matrix doesn't exist");
	} else {
		for (size_t row = 0; row < matrix->number_of_rows; ++row) {
			free(matrix->ptr_matrix[row]);
		}
		if (matrix->ptr_matrix != NULL) {
			free(matrix->ptr_matrix);
		}
		free(matrix);
	}
}

Matrix* create_matrix_from_file(const char* path_file) {
	FILE *off_fptr = fopen(path_file, "r");
	if (off_fptr == NULL) {
		puts("There is no access to the file");
		return NULL;
	}
	// выделяем память для хранения матрицы
	Matrix *newmatrix = calloc(1, sizeof(Matrix));
	if (newmatrix == NULL) {
		puts("Memory allocation error");
		fclose(off_fptr);
		return NULL;
	}
	// читаем указан ли размер матрицы в файле, проверяем на корректность данные
	if (fscanf(off_fptr, "%zu%zu", &newmatrix->number_of_rows, &newmatrix->number_of_cols) != 2) {
		puts("The matrix is incorrect");
		free(newmatrix);
		fclose(off_fptr);
		return NULL;
	}
	// выделяем память для массива указателей количеством number_of_rows
	newmatrix->ptr_matrix = calloc(newmatrix->number_of_rows, sizeof(double*));
	if (newmatrix->ptr_matrix == NULL) {
		puts("Memory allocation error");
		free(newmatrix);
		fclose(off_fptr);
		return NULL;
	}
	for (size_t row = 0; row < newmatrix->number_of_rows; ++row) {
		// выделяем память для переменных, хранящихся в каждом из массивов
		newmatrix->ptr_matrix[row] = calloc(newmatrix->number_of_cols, sizeof(double));
		if (newmatrix->ptr_matrix[row] == NULL) {
			puts("Memory allocation error");
			free_matrix(newmatrix);
			fclose(off_fptr);
			return NULL;
		}
	}
	// выполним инициализацию полей массива
	for (size_t row = 0; row < newmatrix->number_of_rows; ++row) {
		for (size_t col = 0; col < newmatrix->number_of_cols; ++col) {
			if (fscanf(off_fptr, "%lf", &newmatrix->ptr_matrix[row][col]) != 1) {
				 puts("The matrix is incorrect");
				 free_matrix(newmatrix);
				 fclose(off_fptr);
				 return NULL;
			}
		}
	}
	fclose(off_fptr);
	return newmatrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
	if (rows > 0 && cols > 0) {
		Matrix *newmatrix = calloc(1, sizeof(Matrix));
		if (newmatrix == NULL) {
			puts("Memory allocation error");
			return NULL;
		}
		newmatrix->number_of_rows = rows;
		newmatrix->number_of_cols = cols;
		newmatrix->ptr_matrix = calloc(newmatrix->number_of_rows, sizeof(double*));
		if (newmatrix->ptr_matrix == NULL) {
			puts("Memory allocation error");
			free(newmatrix);
			return NULL;
		}
		for (size_t row = 0; row < newmatrix->number_of_rows; ++row) {
			newmatrix->ptr_matrix[row] = calloc(newmatrix->number_of_cols, sizeof(double));
			if (newmatrix->ptr_matrix[row] == NULL) {
				puts("Memory allocation error");
				free_matrix(newmatrix);
				return NULL;
			}
		}
		return newmatrix;
	} else {
		puts("The matrix is incorrect");
		return NULL;
	}
}

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows) {
	if (matrix != NULL && rows != NULL) {
		*rows = matrix->number_of_rows;
		return 0;
	} else {
		puts("Memory allocation error");
		return 1;
	}
}

int get_cols(const Matrix* matrix, size_t* cols) {
	if (matrix != NULL && cols != NULL) {
		*cols = matrix->number_of_cols;
		return 0;
	} else {
		puts("Memory allocation error");
		return 1;
	}
}

int get_elem(const Matrix* matrix, size_t rows, size_t cols, double* val) {
	if (matrix != NULL && matrix->ptr_matrix != NULL
			&& matrix->number_of_rows > rows
			&& matrix->number_of_cols > cols
			&& val != NULL) {
		for (size_t row = 0; row < matrix->number_of_rows; ++row) {
			if (matrix->ptr_matrix[row] == NULL) {
				puts("Memory allocation error");
				return 1;
			}
		}
		*val = matrix->ptr_matrix[rows][cols];
		return 0;
	} else {
		return 1;
	}
}

int set_elem(Matrix* matrix, size_t rows, size_t cols, double val) {
	if (matrix != NULL && matrix->ptr_matrix != NULL
			&& matrix->number_of_rows > rows
			&& matrix->number_of_cols > cols) {
		for (size_t row = 0; row < matrix->number_of_rows; ++row) {
			if (matrix->ptr_matrix[row] == NULL) {
				puts("Memory allocation error");
				return 1;
			}
		}
		matrix->ptr_matrix[rows][cols] = val;
		return 0;
	} else {
		return 1;
	}
}

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
	if (matrix != NULL && matrix->ptr_matrix != NULL) {
		for (size_t row = 0; row < matrix->number_of_rows; ++row) {
			if (matrix->ptr_matrix[row] == NULL) {
				puts("Error in the matrix entry");
				return NULL;
			}
		}
		Matrix* newmatrix = create_matrix(matrix->number_of_rows, matrix->number_of_cols);
		if (newmatrix != NULL) {
			for (size_t row = 0; row < matrix->number_of_rows; ++row) {
				for (size_t col = 0; col < matrix->number_of_cols; ++col) {
					newmatrix->ptr_matrix[row][col] = matrix->ptr_matrix[row][col] * val;
				}
			}
			return newmatrix;
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}

Matrix* transp(const Matrix* matrix) {
	if (matrix != NULL && matrix->ptr_matrix != NULL) {
		for (size_t row = 0; row < matrix->number_of_rows; ++row) {
			if (matrix->ptr_matrix[row] == NULL) {
				puts("Error in the matrix entry");
				return NULL;
			}
		}
		Matrix* newmatrix = create_matrix(matrix->number_of_cols, matrix->number_of_rows);
		if (newmatrix != NULL) {
			for (size_t row = 0; row < matrix->number_of_rows; ++row) {
				for (size_t col = 0; col < matrix->number_of_cols; ++col) {
					newmatrix->ptr_matrix[col][row] = matrix->ptr_matrix[row][col];
				}
			}
			return newmatrix;
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}

Matrix* sum(const Matrix* l, const Matrix* r) {
	if (l != NULL && l->ptr_matrix != NULL
			&& r != NULL && r->ptr_matrix != NULL
			&& l->number_of_rows == r->number_of_rows
			&& l->number_of_cols == r->number_of_cols) {
		for (size_t row = 0; row < l->number_of_rows; ++row) {
			if (l->ptr_matrix[row] == NULL) {
				puts("Error in the matrix entry");
				return NULL;
			}
		}
		for (size_t row = 0; row < r->number_of_rows; ++row) {
			if (r->ptr_matrix[row] == NULL) {
				puts("Error in the matrix entry");
				return NULL;
			}
		}
		Matrix *newmatrix = create_matrix(l->number_of_rows, l->number_of_cols);
		if (newmatrix != NULL) {
			for (size_t row = 0; row < newmatrix->number_of_rows; ++row) {
				for (size_t col = 0; col < newmatrix->number_of_cols; ++col) {
					newmatrix->ptr_matrix[row][col] = l->ptr_matrix[row][col] + r->ptr_matrix[row][col];
				}
			}
			return newmatrix;
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}

Matrix* sub(const Matrix* l, const Matrix* r) {
	if (l != NULL && l->ptr_matrix != NULL
			&& r != NULL && r->ptr_matrix != NULL
			&& l->number_of_rows == r->number_of_rows
			&& l->number_of_cols == r->number_of_cols) {
		for (size_t row = 0; row < l->number_of_rows; ++row) {
			if (l->ptr_matrix[row] == NULL) {
				puts("Error in the matrix entry");
				return NULL;
			}
		}
		for (size_t row = 0; row < r->number_of_rows; ++row) {
			if (r->ptr_matrix[row] == NULL) {
				puts("Error in the matrix entry");
				return NULL;
			}
		}
		Matrix *newmatrix = create_matrix(l->number_of_rows, l->number_of_cols);
		if (newmatrix != NULL) {
			for (size_t row = 0; row < newmatrix->number_of_rows; ++row) {
				for (size_t col = 0; col < newmatrix->number_of_cols; ++col) {
					newmatrix->ptr_matrix[row][col] = l->ptr_matrix[row][col] - r->ptr_matrix[row][col];
				}
			}
			return newmatrix;
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}

Matrix* mul(const Matrix* l, const Matrix* r) {
	if (l != NULL && l->ptr_matrix != NULL
			&& r != NULL && r->ptr_matrix != NULL
			&& l->number_of_cols == r->number_of_rows) {
		for (size_t row = 0; row < l->number_of_rows; ++row) {
			if (l->ptr_matrix[row] == NULL) {
				puts("Error in the matrix entry");
				return NULL;
			}
		}
		for (size_t row = 0; row < r->number_of_rows; ++row) {
			if (r->ptr_matrix[row] == NULL) {
				puts("Error in the matrix entry");
				return NULL;
			}
		}
		Matrix *newmatrix = create_matrix(l->number_of_rows, r->number_of_cols);
		if (newmatrix != NULL) {
			for (size_t row = 0; row < newmatrix->number_of_rows; ++row) {
				for (size_t col = 0; col < newmatrix->number_of_cols; ++col) {
					for (size_t i = 0; i < l->number_of_cols; ++i) {
						newmatrix->ptr_matrix[row][col] += l->ptr_matrix[row][i] * r->ptr_matrix[i][col];
					}
				}
			}
			return newmatrix;
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}

//  Extra operations

void reduce_matrix(const Matrix* matrix, size_t del_row, size_t del_col, Matrix* newmatrix) {
	size_t miss_rows = 0;
	for (size_t i = 0; i < matrix->number_of_rows; ++i) {
		if (i != del_row) {
			size_t miss_cols = 0;
			for (size_t j = 0; j < matrix->number_of_cols; ++j) {
				if (del_col != j) {
					newmatrix->ptr_matrix[i - miss_rows][j - miss_cols] = matrix->ptr_matrix[i][j];
				} else {
					++miss_cols;
				}
			}
		} else {
			++miss_rows;
		}
	}
}


int det(const Matrix* matrix, double* val) {
	if (matrix != NULL && matrix->ptr_matrix != NULL && val != NULL
			&& matrix->number_of_rows == matrix->number_of_cols) {
		if (matrix->number_of_rows == 1) {
			*val = matrix->ptr_matrix[0][0];
			return 0;
	    	} else if (matrix->number_of_rows == 2) {
			*val = ((matrix->ptr_matrix[0][0] * matrix->ptr_matrix[1][1])
				       	- (matrix->ptr_matrix[0][1] * matrix->ptr_matrix[1][0]));
			return 0;
		} else {
			Matrix* newmatrix = create_matrix(matrix->number_of_rows - 1, matrix->number_of_cols - 1);
			double sum_res = 0;
			int sig_n = 1;
			for (size_t col = 0; col < matrix->number_of_cols; ++col) {
				reduce_matrix(matrix, 0, col, newmatrix);
				if (det(newmatrix, val) == 0) {
		    			double temp_res = *val * matrix->ptr_matrix[0][col];
					sum_res += sig_n * temp_res;
					sig_n *= -1;
				}
			}
			*val = sum_res;
			free_matrix(newmatrix);
			return 0;
		}
	} else {
		if (matrix != NULL && matrix->ptr_matrix != NULL && val != NULL) {
			puts("Memory allocation error");
		} else {
			puts("The matrix is incorrect");
		}
		return 1;
	}
}

Matrix* make_minor(const Matrix* matrix, size_t del_row, size_t del_col, Matrix* newmatrix) {
	size_t miss_rows = 0;
	for (size_t i = 0; i < matrix->number_of_rows; ++i) {
		if (i != del_row) {
			size_t miss_cols = 0;
			for (size_t j = 0; j < matrix->number_of_cols; ++j) {
				if (del_col != j) {
					newmatrix->ptr_matrix[i - miss_rows][j - miss_cols] = matrix->ptr_matrix[i][j];
				} else {
					++miss_cols;
				}
			}
		} else {
			++miss_rows;
		}
	}
	return newmatrix;
}


Matrix* adj(const Matrix* matrix) {
	if (matrix != NULL && matrix->ptr_matrix != NULL
			&& matrix->number_of_rows == matrix->number_of_cols) {
		for (size_t row = 0; row < matrix->number_of_rows; ++row) {
			if (matrix->ptr_matrix[row] == NULL) {
				puts("Error in the matrix entry");
				return NULL;
			}
		}
		Matrix* transpon_matrix = transp(matrix);
		Matrix* newmatrix = create_matrix(matrix->number_of_rows, matrix->number_of_cols);
		Matrix* minor_matrix = create_matrix(matrix->number_of_rows - 1, matrix->number_of_cols - 1);
		double minor_res = 0;
		for (size_t i = 0; i < transpon_matrix->number_of_rows; ++i) {
			for (size_t j = 0; j < transpon_matrix->number_of_cols; ++j) {
				if(det(make_minor(transpon_matrix, i, j, minor_matrix), &minor_res) == 0) {
					int sig_n = 1;
					if ((i + j) % 2 == 1) {
						sig_n = -1;
					}
					newmatrix->ptr_matrix[i][j] = minor_res * sig_n;
				} else {
					puts("The descriminant does not exist");
					return NULL;
				}
			}
		}
		free_matrix(transpon_matrix);
		free_matrix(minor_matrix);
		return newmatrix;
	} else {
		if (matrix != NULL && matrix->ptr_matrix != NULL) {
			puts("Memory allocation error");
		} else {
			puts("The matrix is incorrect");
		}
		return NULL;
	}
}

Matrix* inv(const Matrix* matrix) {
	if ((matrix != NULL) && (matrix->ptr_matrix != NULL)) {
		Matrix* bum = create_matrix(matrix->number_of_rows, matrix->number_of_cols);
		return bum;
	} else {
		return NULL;
	}
}


void show_the_matrix(const Matrix* matrix) {
	if (matrix != NULL && matrix->ptr_matrix != NULL) {
		for (size_t row = 0; row < matrix->number_of_rows; ++row) {
	    		for (size_t col = 0; col < matrix->number_of_cols; ++col) {
		    		printf("%lf ", matrix->ptr_matrix[row][col]);
	    		}
	    		puts("\n");
    		}
	} else {
		puts("Memory allocation error");
	}
}
