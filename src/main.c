/**
 * @file main.c
 * @brief Программа для поиска чисел, являющихся степенями пяти, в массиве
 * 
 * Программа принимает размерность массива через аргумент командной строки,
 * генерирует случайные натуральные числа и выводит те из них,
 * которые являются степенями пяти.
 * 
 * @author Egor Gerdiy
 * @version 1.0
 * @date 27.02.2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

/* Константы */
#define MAX_ARRAY_SIZE    1000    /**< Максимальный размер массива */
#define MIN_ARRAY_SIZE    1       /**< Минимальный размер массива */
#define RANDOM_MAX_VALUE  1000    /**< Максимальное значение случайного числа */
#define BASE_FIVE         5       /**< Основание для проверки степени */
#define EXIT_SUCCESS       0
#define EXIT_FAILURE       1
#define EXIT_INVALID_ARGS  2

/**
 * @brief Проверяет, является ли число степенью пяти
 * 
 * Функция последовательно делит число на 5 до тех пор,
 * пока это возможно. Если в результате получается 1,
 * значит исходное число было степенью пяти.
 * 
 * @param number Проверяемое число (должно быть натуральным)
 * @return true если число является степенью пяти, false в противном случае
 * 
 * @note Для числа 1 (5^0) функция вернёт true
 * @warning Число должно быть положительным
 */
static bool is_power_of_five(int number)
{
		/* Проверка на натуральное число */
		if (number <= 0) {
				return false;
		}

		/* Последовательное деление на 5 */
		while (number % BASE_FIVE == 0) {
				number /= BASE_FIVE;
		}

		/* Если после деления осталась единица - число было степенью пяти */
		return (number == 1);
}

/**
 * @brief Безопасное преобразование строки в целое число
 * 
 * @param str Строка для преобразования
 * @param result Указатель для сохранения результата
 * @return true если преобразование успешно, false в противном случае
 */
static bool safe_str_to_int(const char *str, int *result)
{
		char *endptr;
		long value;

		if (str == NULL || result == NULL) {
				return false;
		}

		errno = 0;
		value = strtol(str, &endptr, 10);

		/* Проверка ошибок преобразования */
		if (errno != 0 || *endptr != '\0' || str == endptr) {
				return false;
		}

		/* Проверка на переполнение */
		if (value < INT_MIN || value > INT_MAX) {
				return false;
		}

		*result = (int)value;
		return true;
}

/**
 * @brief Выводит справку по использованию программы
 * 
 * @param program_name Имя исполняемого файла
 */
static void print_usage(const char *program_name)
{
		fprintf(stderr, 
						"Использование: %s <размерность_массива>\n"
						"  размерность_массива: целое число от %d до %d\n"
						"Пример: %s 20\n",
						program_name, MIN_ARRAY_SIZE, MAX_ARRAY_SIZE, program_name);
}

/**
 * @brief Заполняет массив случайными натуральными числами
 * 
 * @param array Указатель на массив
 * @param size Размер массива
 * @param max_value Максимальное значение элемента
 */
static void fill_array_with_random(int *array, size_t size, int max_value)
{
		if (array == NULL || size == 0) {
				return;
		}

		for (size_t i = 0; i < size; ++i) {
				/* Генерация числа от 1 до max_value включительно */
				array[i] = rand() % max_value + 1;
		}
}

/**
 * @brief Выводит массив на экран
 * 
 * @param array Указатель на массив
 * @param size Размер массива
 * @param message Сообщение перед выводом
 */
static void print_array(const int *array, size_t size, const char *message)
{
		if (array == NULL || size == 0 || message == NULL) {
				return;
		}

		printf("%s", message);
		for (size_t i = 0; i < size; ++i) {
				printf("%d ", array[i]);

				/* Форматирование вывода: перенос строки после каждых 20 чисел */
				if ((i + 1) % 20 == 0) {
						printf("\n");
				}
		}

		/* Добавляем перевод строки, если последняя строка не закончена */
		if (size % 20 != 0) {
				printf("\n");
		}
}

/**
 * @brief Находит и выводит элементы массива, являющиеся степенями пяти
 * 
 * @param array Указатель на массив
 * @param size Размер массива
 * @return Количество найденных элементов
 */
static size_t print_powers_of_five(const int *array, size_t size)
{
		size_t count = 0;

		if (array == NULL || size == 0) {
				return 0;
		}

		printf("Числа, являющиеся степенями пяти:\n");

		for (size_t i = 0; i < size; ++i) {
				if (is_power_of_five(array[i])) {
						printf("%d ", array[i]);
						++count;
				}
		}

		if (count == 0) {
				printf("(не найдено)");
		}
		printf("\n");

		return count;
}

/**
 * @brief Точка входа в программу
 * 
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return Код завершения программы
 */
int main(int argc, char *argv[])
{
		int array_size = 0;
		int *array = NULL;

		/* Проверка количества аргументов */
		if (argc != 2) {
				fprintf(stderr, "Ошибка: неверное количество аргументов\n");
				print_usage(argv[0]);
				return EXIT_INVALID_ARGS;
		}

		/* Преобразование аргумента в число */
		if (!safe_str_to_int(argv[1], &array_size)) {
				fprintf(stderr, "Ошибка: аргумент должен быть целым числом\n");
				print_usage(argv[0]);
				return EXIT_INVALID_ARGS;
		}

		/* Проверка допустимости размера массива */
		if (array_size < MIN_ARRAY_SIZE || array_size > MAX_ARRAY_SIZE) {
				fprintf(stderr, 
								"Ошибка: размер массива должен быть от %d до %d\n",
								MIN_ARRAY_SIZE, MAX_ARRAY_SIZE);
				print_usage(argv[0]);
				return EXIT_INVALID_ARGS;
		}

		/* Выделение памяти под массив */
		array = (int *)malloc((size_t)array_size * sizeof(int));
		if (array == NULL) {
				fprintf(stderr, "Ошибка: не удалось выделить память для массива\n");
				return EXIT_FAILURE;
		}

		/* Инициализация генератора случайных чисел */
		srand((unsigned int)time(NULL));

		/* Заполнение массива случайными числами */
		fill_array_with_random(array, (size_t)array_size, RANDOM_MAX_VALUE);

		/* Вывод исходного массива */
		printf("\n");
		print_array(array, (size_t)array_size, "Исходный массив:\n");
		printf("\n");

		/* Поиск и вывод степеней пяти */
		print_powers_of_five(array, (size_t)array_size);
		printf("\n");

		/* Освобождение памяти */
		free(array);
		array = NULL;

		return EXIT_SUCCESS;
}