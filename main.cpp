#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include "ArraySequence.h" 
#include "HeapSorter.h"    
#include "ShellSorter.h"   
#include "QuickSorter.h"   
#include "ISorter.h"       
#include "printer.h"
#include "comparator.h"
#include "tests.h"


int main() {
    char c = '1';
    std::cout << "Введите 1 для запуска тестов. Введите 2 для пользовательского ввода. 3 для тестирования структур. Любая другая клавиша завершает программу.\n";
    std::cin >> c;

    while (c == '1' || c == '2' || c == '3') {
        if (c == '1') {
            HeapSorter<int> heapSorter;
            ShellSorter<int> shellSorter;
            QuickSorter<int> quickSorter;

            HeapSorter<std::string> stringHeapSorter;
            ShellSorter<std::string> stringShellSorter;
            QuickSorter<std::string> stringQuickSorter;

            testSorting(heapSorter, "HeapSort");
            testSorting(shellSorter, "ShellSort");
            testSorting(quickSorter, "QuickSort");

            testSorting(stringHeapSorter, "HeapSort для строк");
            testSorting(stringShellSorter, "ShellSort для строк");
            testSorting(stringQuickSorter, "QuickSort для строк");

            std::cout << "Тесты завершены.\n";
        } else if (c == '2') {
            char cc = '1';
            std::cout << "Выберите тип данных: 1 - Числа, 2 - Строки. 3 - Person\n";
            std::cin >> cc;

            if (cc == '1') {
                std::cout << "Выберите алгоритм сортировки: 1 - HeapSort, 2 - ShellSort, иначе - QuickSort.\n";
                std::cin >> cc;

                if (cc == '1') {
                    HeapSorter<double> heapSorter;
                    testUserSorting(heapSorter);
                } else if (cc == '2') {
                    ShellSorter<double> shellSorter;
                    testUserSorting(shellSorter);
                } else {
                    QuickSorter<double> quickSorter;
                    testUserSorting(quickSorter);
                }
            } else if (cc == '2') {
                std::cout << "Выберите алгоритм сортировки: 1 - HeapSort, 2 - ShellSort, иначе - QuickSort.\n";
                std::cin >> cc;

                if (cc == '1') {
                    HeapSorter<std::string> stringHeapSorter;
                    testUserSortingString(stringHeapSorter);
                } else if (cc == '2') {
                    ShellSorter<std::string> stringShellSorter;
                    testUserSortingString(stringShellSorter);
                } else {
                    QuickSorter<std::string> stringQuickSorter;
                    testUserSortingString(stringQuickSorter);
                }
            }
            else if (cc == '3') {
                std::cout << "Выберите алгоритм сортировки: 1 - HeapSort, 2 - ShellSort, иначе - QuickSort.\n";
                std::cin >> cc;
                if (cc == '1') {
                    HeapSorter<Person> personHeapSorter;
                    testUserSortingPersons(personHeapSorter);
                    }
                else if (cc == '2') {
                    ShellSorter<Person> personShellSorter;
                    testUserSortingPersons(personShellSorter);
                    } 
                else {
                    QuickSorter<Person> personQuickSorter;
                    testUserSortingPersons(personQuickSorter);
                }
            }
            else {
                std::cout << "Неверный ввод. Возврат в главное меню.\n";
            }
        } else if (c == '3') {
            testPersonSorting();
        } else {
            break;
        }

        std::cout << "Введите 1 для запуска тестов. Введите 2 для пользовательского ввода. 3 для тестирования структур. Любая другая клавиша завершает программу.\n";
        std::cin >> c;
    }

    std::cout << "До свидания!\n";
    return 0;
}