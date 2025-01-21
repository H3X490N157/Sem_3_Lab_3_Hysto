#ifndef HISTOGRAM_BUILDER_H
#define HISTOGRAM_BUILDER_H

#include "IDictionary.h"
#include "person.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <iostream> 

class HistogramBuilder {
private:
    IDictionary<std::string, int> histogram;

public:
    void Build(const std::vector<Person>& persons, const std::string& attribute, double minRange, double maxRange, double step) {
        histogram = IDictionary<std::string, int>();

        // Инициализация диапазонов
        for (double rangeStart = minRange; rangeStart < maxRange; rangeStart += step) {
            std::string bin = "[" + std::to_string(rangeStart) + "-" + std::to_string(rangeStart + step) + ")";
            histogram.Add(bin, 0);
        }

        // Заполнение гистограммы
        for (const auto& person : persons) {
            double value = 0.0;

            if (attribute == "height")
                value = person.GetHeight();
            else if (attribute == "weight")
                value = person.GetWeight();
            else
                throw std::runtime_error("Ошибка");

            if (value >= minRange && value < maxRange) {
                double rangeStart = minRange + std::floor((value - minRange) / step) * step;
                std::string bin = "[" + std::to_string(rangeStart) + "-" + std::to_string(rangeStart + step) + ")";
                histogram.Add(bin, histogram.Get(bin) + 1);
            }
        }
    }

    void DrawHistogram(sf::RenderWindow& window) {
        const int barWidth = 30;       // Уменьшаем ширину столбцов
        const int barSpacing = 10;     // Уменьшаем промежуток между столбцами
        const int yMax = 600;          // Уменьшаем максимальную высоту столбцов
        int x = 50;                    // Начальная позиция по оси X
        int yOffset = 50;              // Смещение столбцов от нижней границы (вместо 0)

        int maxCount = 0;

        // Найдем максимальное количество для масштабирования
        for (int i = 0; i < histogram.GetLength(); ++i) {
            auto bin = histogram.Get(i);
            if (bin.second > maxCount)
                maxCount = bin.second;
        }

        // Проверка на деление на ноль
        if (maxCount == 0) {
            std::cerr << "Ошибка: нет данных для построения гистограммы.\n";
            return;
        }

        // Шрифт для подписей
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Ошибка загрузки шрифта.\n";
            return;
        }

        // Рисуем гистограмму
        for (int i = 0; i < histogram.GetLength(); ++i) {
            auto bin = histogram.Get(i);

            // Масштабирование высоты столбца
            int barHeight = static_cast<int>(bin.second) * (yMax - yOffset) / maxCount;

            sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
            bar.setFillColor(sf::Color(100 + i * 40, 100 + i * 30, 200)); // Разные цвета для каждого столбца
            bar.setPosition(x, yMax - bar.getSize().y - yOffset);  // Отрисовываем с учетом высоты окна (сдвигаем столбцы немного выше)
            window.draw(bar);

            // Добавляем текст с диапазоном (названием столбца)
            sf::Text label(bin.first, font, 10);  // Уменьшаем размер шрифта
            label.setFillColor(sf::Color::White);
            label.setPosition(x, yMax + 5); // Расположить подпись под столбцом
            window.draw(label);

            // Добавляем текст с количеством элементов (число над столбцом)
            sf::Text valueLabel(std::to_string(bin.second), font, 10);  // Уменьшаем размер шрифта
            valueLabel.setFillColor(sf::Color::White);
            valueLabel.setPosition(x + barWidth / 4, yMax - barHeight - 20); // Расположить подпись над столбцом
            window.draw(valueLabel);

            // Сдвигаем позицию для следующего столбца
            x += barWidth + barSpacing;
        }
    }

    void SaveToCSV(const std::string& filename) {
        std::ofstream file(filename);
        file << "Range,Count\n";
        for (int i = 0; i < histogram.GetLength(); ++i) {
            auto bin = histogram.Get(i);
            file << bin.first << "," << bin.second << "\n";
        }
    }
};

#endif // HISTOGRAM_BUILDER_H
