#include <main.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

void print() {
    SetConsoleOutputCP(1251);
    cout << "1251" << endl;
}

// Задание 1

void task1() {
    const int size1 = 20;
    const int size2 = 100;
    const int size3 = 1000;
    const int size4 = 50000;
    const int size5 = 100000;

    int using_size = size3;

    double start_time_a, end_time_a, start_time_b, end_time_b;
    int a[using_size], b[using_size];

    // Заполнение массива a в главной нити
    start_time_a = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < using_size; ++i) {
        a[i] = 0.5 * i * i - 8.5 * i + 0.3;
    }
    end_time_a = omp_get_wtime();

    // Заполнение массива b в параллельной области для двух потоков
    start_time_b = omp_get_wtime();
    #pragma omp parallel for num_threads(2)
    for (int i = 0; i < using_size; ++i) {
        b[i] = 0.5 * i * i - 8.5 * i + 0.3;
    }
    end_time_b = omp_get_wtime();

    // Вывод результатов
    cout << "Время для массива a: " << end_time_a - start_time_a << " секунд" << endl;
    cout << "Время для массива b: " << end_time_b - start_time_b << " секунд" << endl;

    // Вывод массива, который заполнился быстрее
    if (end_time_a - start_time_a < end_time_b - start_time_b) {
        cout << "Массив a быстрее:" << endl;
        for (int i = 0; i < using_size; ++i) {
            cout << a[i] << " ";
        }
    } else {
        cout << "Массив b быстрее:" << endl;
        for (int i = 0; i < using_size; ++i) {
            cout << b[i] << " ";
        }
    }
}

// Задание 2

int f(int a)
{
    return a * a - 10 * a - 50;
}

void task2() {

    const int n = 100;
    int a[n], t;

    // Получаем общее количество процессоров
    int num_procs = omp_get_num_procs();

    // Устанавливаем число потоков равным общему числу процессоров
    omp_set_num_threads(num_procs);

    #pragma omp parallel
    {
    #pragma omp for private(t)
        for (int i = 0; i < n; i++)
        {
            t = f(i);
            a[i] = t;

            // Вывод элементов, заполненных главным потоком
            if (omp_get_thread_num() == 0)
            {
                cout << "Поток " << omp_get_thread_num() << " заполнил элемент a[" << i << "] = " << a[i] << endl;
            }
        }
    }

    // Вывод общего количества элементов, заполненных главным потоком
    if (omp_get_thread_num() == 0)
    {
        cout << "Общее кол-во элементов, заполненное главным потоком: " << n << endl;
    }

    cout << "Кол-во доступных процессоров: " << num_procs << endl;

}

// Задание 3

void task3() {
    const int n = 40;
    vector<int> a(n);

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned>(time(nullptr)));

    // Первая половина вектора заполняется случайными числами
    #pragma omp parallel for
    for (int i = 0; i < n / 2; ++i) {
        a[i] = rand() % 100;
    }

    // Параллельная область для создания локальных копий вектора
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        vector<int> local_copy(a.begin(), a.end());

    // Вторая половина вектора проинициализирована номером потока
    #pragma omp for
        for (int i = n / 2; i < n; ++i) {
            local_copy[i] = thread_id;
        }

    // Вывод вектора и номера потока для каждой локальной копии
    #pragma omp critical
        {
            cout << "Поток " << thread_id << ": ";
            for (int i : local_copy) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
}

// Задание 4

// Функция для вычисления произведения матриц
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    int m = a[0].size();
    int p = b[0].size();

    vector<vector<int>> result(n, vector<int>(p, 0));

#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < m; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

void task4() {
    const int size = 100;

    // Инициализация матриц a и b
    vector<vector<int>> a(size, vector<int>(size, 0));
    vector<vector<int>> b(size, vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = b[i][j] = i * j;
        }
    }

    // Измерение времени выполнения
    double start_time = omp_get_wtime();

    // Вычисление произведения матриц
    vector<vector<int>> result = multiplyMatrices(a, b);

    double end_time = omp_get_wtime();
    double duration = end_time - start_time;

    // Вывод времени выполнения
    cout << "Время выполнения программы: " << duration << " секунд" << endl;

    // Вывод результата (пример вывода первых 5x5 элементов)
    cout << "Рассчитанная матрица (первые 10x10 элементов):" << endl;
    for (int i = 0; i < min(size, 5); ++i) {
        for (int j = 0; j < min(size, 5); ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}

