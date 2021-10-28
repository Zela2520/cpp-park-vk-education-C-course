#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

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
		puts("The matrix does not exist");
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
				 puts("Data reading error");
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
		return NULL;
	}
}

void free_matrix(Matrix* matrix) {
	if (matrix == NULL) {
		puts("The matrix does not exist");
		return;
	} else {
		for (size_t row = 0; row < matrix->number_of_rows; ++row) {
			free(matrix->ptr_matrix[row]);
		}
		free(matrix->ptr_matrix);
		free(matrix);
	}
}

