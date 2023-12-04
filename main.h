#ifndef MAIN_H
#define MAIN_H

void swap(int &x, int &y);
void print();

void task1();

int f(int a);
void task2();

void task3();

#include <vector>

// Декларация функции для вычисления произведения матриц
std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b);
void task4();


class MyClass {
public:
    int var1;
    int var2;
    int arr[2] = {0, 0};
    MyClass() {
        var1 = 0;
        var2 = 0;
    }
};

#endif // MAIN_H
