#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-12

static void swap_rows(double *a, int cols, int r1, int r2) {
	if (r1 == r2) {
		return;
	}

	for (int j = 0; j < cols; j++) {
		double temp = a[r1 * cols + j];
		a[r1 * cols + j] = a[r2 * cols + j];
		a[r2 * cols + j] = temp;
	}
}

static void print_matrix(const double *a, int rows, int cols, const char *title) {
	printf("\n%s\n", title);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (j == cols - 1) {
				printf("| %10.4lf ", a[i * cols + j]);
			} else {
				printf("%10.4lf ", a[i * cols + j]);
			}
		}
		printf("\n");
	}
}

int main(void) {
	int n;

	printf("Enter number of equations (n): ");
	if (scanf("%d", &n) != 1 || n <= 0) {
		printf("Invalid value of n.\n");
		return 1;
	}

	int cols = n + 1;
	double *aug = (double *)malloc((size_t)n * (size_t)cols * sizeof(double));
	double *x = (double *)malloc((size_t)n * sizeof(double));

	if (aug == NULL || x == NULL) {
		printf("Memory allocation failed.\n");
		free(aug);
		free(x);
		return 1;
	}

	printf("Enter coefficients and constants for each equation:\n");
	printf("Format per row: a1 a2 ... an b\n\n");

	for (int i = 0; i < n; i++) {
		printf("Equation %d: ", i + 1);
		for (int j = 0; j < cols; j++) {
			if (scanf("%lf", &aug[i * cols + j]) != 1) {
				printf("Invalid input encountered.\n");
				free(aug);
				free(x);
				return 1;
			}
		}
	}

	print_matrix(aug, n, cols, "Initial Augmented Matrix [A|B]:");

	for (int k = 0; k < n - 1; k++) {
		int pivot_row = k;
		double max_value = fabs(aug[k * cols + k]);

		for (int i = k + 1; i < n; i++) {
			double value = fabs(aug[i * cols + k]);
			if (value > max_value) {
				max_value = value;
				pivot_row = i;
			}
		}

		if (max_value < EPS) {
			printf("No unique solution exists (zero pivot found).\n");
			free(aug);
			free(x);
			return 1;
		}

		swap_rows(aug, cols, k, pivot_row);

		for (int i = k + 1; i < n; i++) {
			double factor = aug[i * cols + k] / aug[k * cols + k];

			for (int j = k; j < cols; j++) {
				aug[i * cols + j] -= factor * aug[k * cols + j];
			}
		}

		char title[80];
		snprintf(title, sizeof(title), "Upper Triangular Matrix after step %d:", k + 1);
		print_matrix(aug, n, cols, title);
	}

	print_matrix(aug, n, cols, "Final Upper Triangular Matrix:");

	if (fabs(aug[(n - 1) * cols + (n - 1)]) < EPS) {
		printf("No unique solution exists (singular system).\n");
		free(aug);
		free(x);
		return 1;
	}

	for (int i = n - 1; i >= 0; i--) {
		double sum = aug[i * cols + n];
		for (int j = i + 1; j < n; j++) {
			sum -= aug[i * cols + j] * x[j];
		}

		if (fabs(aug[i * cols + i]) < EPS) {
			printf("No unique solution exists (division by zero pivot).\n");
			free(aug);
			free(x);
			return 1;
		}

		x[i] = sum / aug[i * cols + i];
	}

	printf("\nSolution:\n");
	for (int i = 0; i < n; i++) {
		printf("x%d = %.6lf\n", i + 1, x[i]);
	}

	free(aug);
	free(x);
	return 0;
}

/*
Format per row: a1 a2 ... an b

Equation 1: 10 3 1 14
Equation 2: 2 -10 3 -5
Equation 3: 1 3 10 14

Solution:
x1 = 1.000000
x2 = 1.000000
x3 = 1.000000
*/
