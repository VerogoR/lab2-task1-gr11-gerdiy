/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int isPowerOfFive(int n) {
		if (n <= 0) return 0;

		while (n % 5 == 0) {
				n /= 5;
		}

		return (n == 1);
}

int main(int argc, char *argv[]) {
		if (argc != 2) {
				printf("Использование: %s <размерность массива>\n", argv[0]);
				return 1;
		}

		int n = atoi(argv[1]);

		if (n <= 0) {
				printf("Размерность массива должна быть положительным числом\n");
				return 1;
		}

		srand(time(NULL));

		int *arr = (int*)malloc(n * sizeof(int));
		if (arr == NULL) {
				printf("Ошибка выделения памяти\n");
				return 1;
		}

		printf("Исходный массив:\n");
		for (int i = 0; i < n; i++) {
				arr[i] = rand() % 1000 + 1;
				printf("%d ", arr[i]);
		}
		printf("\n\n");

		printf("Числа, являющиеся степенями пяти:\n");
		int count = 0;

		for (int i = 0; i < n; i++) {
				if (isPowerOfFive(arr[i])) {
						printf("%d ", arr[i]);
						count++;
				}
		}

		if (count == 0) {
				printf("Таких чисел не найдено");
		}
		printf("\n");

		free(arr);

		return 0;
}
