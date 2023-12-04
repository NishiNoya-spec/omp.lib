#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <main.h>
#include <omp.h>

using namespace std;

int main(/*int argc, char *argv[]*/)
{
//    QCoreApplication a(argc, argv);

   // setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251); // установка кодовой страницы windows-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы windows-cp 1251 в поток вывода

//    task1();

//    task2();

//    task3();

    task4();

    cout << "\n Нажмите любую клавишу для завершения программы." << endl;

    _getch();

    return 0;
    //return a.exec();
}


