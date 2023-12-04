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

//    string value;

//    cout << "Введите значение: ";
//    getline(cin, value);
//    cout << "Ваше введенное значение: " << value << endl;

//    _getch();

//    srand(time(nullptr));
//    int rand_num = rand();
//    cout << "Вы получаете рандомное значение: " << rand_num << endl;

//    int x = 10;
//    int y = 20;

//    cout << x << y << endl;

//    swap(x, y);

//    cout << x << y << endl;

//    _getch();

//    print();

//    _getch();

//    int arr[5] = {1, 2, 3, 4, 5};

//    MyClass *obj1 = new MyClass();
//    obj1 -> var1 = 10;
//    obj1 -> var2 = 20;
//    MyClass *obj2 = new MyClass();
//    obj2 -> var1 = 30;
//    obj2 -> var2 = 40;

//    cout << obj1->var1 << " " << obj1->var2 << " " << obj2->var1 << " " << obj2->var2 << endl;

//    cout << obj1->arr[0] << " " << obj2->arr[0] << endl;

//    _getch();


    task1();
//    task2();

//    task3();

//    task4();

    cout << "\n Нажмите любую клавишу для завершения программы." << endl;

    _getch();

    return 0;
    //return a.exec();
}


