#include "Count_Subsequence.h"
#include "IDictionary_Sequence.h"
#include "sequence.h"
#include <iostream>
#include <string>
#include <ncurses.h>
#include <cassert>

// Простой класс Sequence для строки
class StringSequence : public Sequence<char> {
private:
    std::string data;

public:
    StringSequence(const std::string& str) : data(str) {}

    char& GetFirst() override { return data.front(); }
    char& GetLast() override { return data.back(); }
    char& Get(int index) const override {
        if (index < 0 || index >= data.size()) throw std::out_of_range("Index out of range");
        return const_cast<char&>(data[index]);
    }
    char& operator[](int index) override { return Get(index); }
    int GetLength() const override { return data.size(); }
    void Append(char item) override { data += item; }
    void Prepend(char item) override { data = item + data; }
    void InsertAt(char item, int index) override {
        if (index < 0 || index > data.size()) throw std::out_of_range("Index out of range");
        data.insert(data.begin() + index, item);
    }
};

// Функция для визуализации диаграммы
void DisplayDiagram(const IDictionary<std::string, int>& counts) {
    initscr();
    noecho();
    cbreak();

    int row = 0, col = 0;
    int max_count = 0;

    // Найти максимальное количество для нормализации диаграммы
    for (int i = 0; i < counts.GetLength(); ++i) {
        auto temp = counts.Get(i); // Используем метод Get() для доступа
        max_count = std::max(max_count, temp.second);
    }

    for (int i = 0; i < counts.GetLength(); ++i) {
        auto temp = counts.Get(i); // Используем метод Get() для доступа
        int normalized_length = (temp.second * 50) / max_count; // Нормализация длины диаграммы
        mvprintw(row++, col, "%s: %d [%s]", temp.first.c_str(), temp.second,
                 std::string(normalized_length, '*').c_str());
        if (row >= LINES - 1) {
            mvprintw(row, 0, "Press any key to continue...");
            getch();
            clear();
            row = 0;
        }
    }

    mvprintw(row, 0, "Press any key to exit...");
    getch();
    endwin();
}

// Функция автотестов
void RunTests() {
    {
        // Тест 1
        StringSequence sequence("ababc");
        int lmin = 2, lmax = 3;
        auto result = CountSubsequences(sequence, lmin, lmax);

        assert(result.Get("ab") == 2);
        assert(result.Get("ba") == 1);
        assert(result.Get("bc") == 1);
        assert(result.Get("abc") == 1);

        DisplayDiagram(result);
    }

    {
        // Тест 2
        StringSequence sequence("aaaa");
        int lmin = 1, lmax = 2;
        auto result = CountSubsequences(sequence, lmin, lmax);

        assert(result.Get("a") == 4);
        assert(result.Get("aa") == 3);

        DisplayDiagram(result);
    }

    {
        // Тест 3
        StringSequence sequence("abcde");
        int lmin = 2, lmax = 3;
        auto result = CountSubsequences(sequence, lmin, lmax);

        assert(result.Get("ab") == 1);
        assert(result.Get("bc") == 1);
        assert(result.Get("cd") == 1);
        assert(result.Get("de") == 1);
        assert(result.Get("abc") == 1);
        assert(result.Get("bcd") == 1);

        DisplayDiagram(result);
    }

    std::cout << "All tests passed successfully!" << std::endl;
}

// Функция для выполнения пользовательского ввода
void ManualInput() {
    std::string input;
    int lmin, lmax;

    std::cout << "Enter input string: ";
    std::cin >> input;
    std::cout << "Enter minimum length (lmin): ";
    std::cin >> lmin;
    std::cout << "Enter maximum length (lmax): ";
    std::cin >> lmax;

    try {
        StringSequence sequence(input);
        auto result = CountSubsequences(sequence, lmin, lmax);

        DisplayDiagram(result);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

// Главное меню программы
int main() {
    std::cout << "Choose mode:\n";
    std::cout << "1. Run tests\n";
    std::cout << "2. Manual input\n";
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        RunTests();
        break;
    case 2:
        ManualInput();
        break;
    default:
        std::cerr << "Invalid choice. Exiting..." << std::endl;
        return 1;
    }

    return 0;
}