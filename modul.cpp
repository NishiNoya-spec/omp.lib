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

// ������� 1

void task1() {
    const int size1 = 20;
    const int size2 = 100;
    const int size3 = 1000;
    const int size4 = 50000;
    const int size5 = 100000;

    int using_size = size3;

    double start_time_a, end_time_a, start_time_b, end_time_b;
    int a[using_size], b[using_size];

    // ���������� ������� a � ������� ����
    start_time_a = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < using_size; ++i) {
        a[i] = 0.5 * i * i - 8.5 * i + 0.3;
    }
    end_time_a = omp_get_wtime();

    // ���������� ������� b � ������������ ������� ��� ���� �������
    start_time_b = omp_get_wtime();
    #pragma omp parallel for num_threads(2)
    for (int i = 0; i < using_size; ++i) {
        b[i] = 0.5 * i * i - 8.5 * i + 0.3;
    }
    end_time_b = omp_get_wtime();

    // ����� �����������
    cout << "����� ��� ������� a: " << end_time_a - start_time_a << " ������" << endl;
    cout << "����� ��� ������� b: " << end_time_b - start_time_b << " ������" << endl;

    // ����� �������, ������� ���������� �������
    if (end_time_a - start_time_a < end_time_b - start_time_b) {
        cout << "������ a �������:" << endl;
        for (int i = 0; i < using_size; ++i) {
            cout << a[i] << " ";
        }
    } else {
        cout << "������ b �������:" << endl;
        for (int i = 0; i < using_size; ++i) {
            cout << b[i] << " ";
        }
    }
}

// ������� 2

int f(int a)
{
    return a * a - 10 * a - 50;
}

void task2() {

    const int n = 100;
    int a[n], t;

    // �������� ����� ���������� �����������
    int num_procs = omp_get_num_procs();

    // ������������� ����� ������� ������ ������ ����� �����������
    omp_set_num_threads(num_procs);

    #pragma omp parallel
    {
    #pragma omp for private(t)
        for (int i = 0; i < n; i++)
        {
            t = f(i);
            a[i] = t;

            // ����� ���������, ����������� ������� �������
            if (omp_get_thread_num() == 0)
            {
                cout << "����� " << omp_get_thread_num() << " �������� ������� a[" << i << "] = " << a[i] << endl;
            }
        }
    }

    // ����� ������ ���������� ���������, ����������� ������� �������
    if (omp_get_thread_num() == 0)
    {
        cout << "����� ���-�� ���������, ����������� ������� �������: " << n << endl;
    }

    cout << "���-�� ��������� �����������: " << num_procs << endl;

}

// ������� 3

void task3() {
    const int n = 40;
    vector<int> a(n);

    // ������������� ���������� ��������� �����
    srand(static_cast<unsigned>(time(nullptr)));

    // ������ �������� ������� ����������� ���������� �������
    #pragma omp parallel for
    for (int i = 0; i < n / 2; ++i) {
        a[i] = rand() % 100;
    }

    // ������������ ������� ��� �������� ��������� ����� �������
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        vector<int> local_copy(a.begin(), a.end());

    // ������ �������� ������� ������������������� ������� ������
    #pragma omp for
        for (int i = n / 2; i < n; ++i) {
            local_copy[i] = thread_id;
        }

    // ����� ������� � ������ ������ ��� ������ ��������� �����
    #pragma omp critical
        {
            cout << "����� " << thread_id << ": ";
            for (int i : local_copy) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
}

// ������� 4

// ������� ��� ���������� ������������ ������
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

    // ������������� ������ a � b
    vector<vector<int>> a(size, vector<int>(size, 0));
    vector<vector<int>> b(size, vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = b[i][j] = i * j;
        }
    }

    // ��������� ������� ����������
    double start_time = omp_get_wtime();

    // ���������� ������������ ������
    vector<vector<int>> result = multiplyMatrices(a, b);

    double end_time = omp_get_wtime();
    double duration = end_time - start_time;

    // ����� ������� ����������
    cout << "����� ���������� ���������: " << duration << " ������" << endl;

    // ����� ���������� (������ ������ ������ 5x5 ���������)
    cout << "������������ ������� (������ 10x10 ���������):" << endl;
    for (int i = 0; i < min(size, 5); ++i) {
        for (int j = 0; j < min(size, 5); ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}

