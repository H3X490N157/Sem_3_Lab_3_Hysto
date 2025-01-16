#include "Histogram_Builder.h"
#include "csv_writer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main() {
    // Считываем данные из CSV
    auto persons = read_persons_from_csv("persons.csv");

    // Проверим данные, чтобы удостовериться, что они корректно загружены
    std::cout << "Считанные данные:\n";
    for (const auto& person : persons) {
        std::cout << "Name: " << person.GetName() 
                  << ", Height: " << person.GetHeight() 
                  << ", Weight: " << person.GetWeight() << "\n";
    }

    // Выбор параметров для гистограммы
    std::string attribute;
    double minRange, maxRange, step;

    std::cout << "Введите атрибут для анализа (height/weight): ";
    std::cin >> attribute;
    if (attribute != "height" && attribute != "weight") {
        std::cerr << "Ошибка: атрибут должен быть 'height' или 'weight'.\n";
        return 1;
    }

    std::cout << "Введите минимальное значение диапазона: ";
    std::cin >> minRange;

    std::cout << "Введите максимальное значение диапазона: ";
    std::cin >> maxRange;
    if (minRange >= maxRange) {
        std::cerr << "Ошибка: минимальное значение должно быть меньше максимального.\n";
        return 1;
    }

    std::cout << "Введите шаг диапазона: ";
    std::cin >> step;
    if (step <= 0) {
        std::cerr << "Ошибка: шаг должен быть положительным числом.\n";
        return 1;
    }

    // Создаем гистограмму
    HistogramBuilder builder;
    try {
        builder.Build(persons, attribute, minRange, maxRange, step);
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << "\n";
        return 1;
    }

    // Открываем окно для визуализации
    sf::RenderWindow window(sf::VideoMode(2000, 1500), "Гистограмма");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        builder.DrawHistogram(window);
        window.display();
    }

    // Сохраняем результат в CSV
    builder.SaveToCSV("result.csv");
    std::cout << "Гистограмма сохранена в 'result.csv'.\n";

    return 0;
}
