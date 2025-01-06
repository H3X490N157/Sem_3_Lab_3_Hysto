#pragma once
#include <ncurses.h>
#include "sequence.h"
#include "creator.h"

template <typename T>
void printSequence(const Sequence<T>* seq) {
    for (int i = 0; i < seq->GetLength(); ++i) {
        std::cout << seq->Get(i) << " ";
    }
    std::cout << "\n";
}

void PrintHistogram(const Histogram& hist) {
    initscr();  // Инициализация ncurses
    noecho();   // Отключаем вывод символов на экран
    curs_set(0); // Скрываем курсор

    int y = 0;  // Стартовая позиция для вывода текста

    for (const auto& entry : hist.GetHistogram()) {
        mvprintw(y++, 0, "%s: %d", entry.first.c_str(), entry.second);
    }

    refresh();  // Обновить экран
    getch();    // Ожидание нажатия клавиши

    endwin();  // Завершаем работу с ncurses
}
