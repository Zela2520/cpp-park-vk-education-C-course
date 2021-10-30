#include <stdio.h>
#include "matrix.h"

int main(void) {
    Matrix *first_matrix = create_matrix_from_file("../../test.txt");
    if (first_matrix != NULL) {
	    show_the_matrix(first_matrix);
    } else {
	    puts("The first matrix doesn't exist");
    }

    // инициализируем переменные для хранения количества строк и столбцов второй матрицы
    size_t rows = 0;
    size_t cols = 0;

    // создаём вторую матрицу из первой
    // используем методы get_rows, get_cols, get_elem, set_elem, create_matrix
    Matrix* second_matrix = NULL;
    if (get_rows(first_matrix, &rows) == 0 && get_cols(first_matrix, &cols) == 0) {
    	second_matrix = create_matrix(rows, cols);
	if (second_matrix != NULL) {
		for (size_t i = 0; i < rows; ++i) {
	    		for (size_t j = 0; j < cols; ++j) {
				double temp;
				if (get_elem(first_matrix, i, j, &temp) == 0) {
		    			if (set_elem(second_matrix, i, j, temp) != 0) {
						puts("Memory allocation erroe");
					}
				} else {
					puts("Memory allocation error");
				}
	    		}
		}
	} else {
		puts("The second matrix doesn't exist");
    	}
    } else {
	    puts("The first matrix doesn't exist");
    }

    // Арифметические операции
    double multiplier = 5;
    Matrix* mul_scalar_matrix = mul_scalar(first_matrix, multiplier);
    if (mul_scalar_matrix != NULL) {
	    show_the_matrix(mul_scalar_matrix);
    } else {
	    puts("Memory allocation error");
    }

    Matrix* transp_matrix = transp(first_matrix);
    if (transp_matrix != NULL) {
	    show_the_matrix(transp_matrix);
    } else {
	    puts("Memory allocation error");
    }

    Matrix* sum_matrix = sum(first_matrix, second_matrix);
    if (sum_matrix != NULL) {
	    show_the_matrix(sum_matrix);
    } else {
	    puts("Memory allocation error");
    }

    Matrix* sub_matrix = sub(first_matrix, second_matrix);
    if (sub_matrix != NULL) {
	    show_the_matrix(sub_matrix);
    } else {
	    puts("Memory allocation error");
    }

    Matrix* mul_matrix = mul(first_matrix, second_matrix);
    if (mul_matrix != NULL) {
	    show_the_matrix(mul_matrix);
    } else {
	    puts("Memory allocation error");
    }

    // Освобождаем память
    if (first_matrix != NULL) {
    	free_matrix(first_matrix);
    }
    if (second_matrix != NULL) {
    	free_matrix(second_matrix);
    }
    if (mul_scalar_matrix != NULL) {
    	free_matrix(mul_scalar_matrix);
    }
    if (transp_matrix != NULL) {
    	free_matrix(transp_matrix);
    }
    if (sum_matrix != NULL) {
    	free_matrix(sum_matrix);
    }
    if (sub_matrix != NULL) {
    	free_matrix(sub_matrix);
    }
    if (mul_matrix != NULL) {
    	free_matrix(mul_matrix);
    }

    det(NULL, NULL);
    adj(NULL);
    inv(NULL);

    return 0;
}
