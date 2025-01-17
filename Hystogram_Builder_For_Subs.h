#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <cassert>
#include "IDictionary_Sequence.h"
#include "Count_Subsequence.h"

class HistogramBuilder {
private:
    std::map<std::string, int> histogram;

public:
    void Build(const std::map<std::string, int>& counts) {
        histogram = counts;
    }

    void DrawHistogram(sf::RenderWindow& window) {
        const int barWidth = 50;
        const int barSpacing = 10;

        int x = 50; // Начальная позиция
        int yMax = 400; // Максимальная высота столбцов
        int maxCount = 0;

        // Найдем максимальное количество для масштаба
        for (const auto& pair : histogram) {
            if (pair.second > maxCount) maxCount = pair.second;
        }

        // Проверка на деление на ноль
        if (maxCount == 0) {
            std::cerr << "Ошибка: нет данных для построения гистограммы.\n";
            return;
        }

        // Рисуем гистограмму
        for (const auto& pair : histogram) {
            int barHeight = static_cast<int>(pair.second) * yMax / maxCount;

            sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
            bar.setFillColor(sf::Color::Blue);
            bar.setPosition(x, yMax - bar.getSize().y);  // Отрисовываем с учетом высоты окна
            window.draw(bar);

            // Сдвигаем позицию для следующего столбца
            x += barWidth + barSpacing;
        }
    }
};