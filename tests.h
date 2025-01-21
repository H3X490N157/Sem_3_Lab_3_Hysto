#include "csw_writer_new.h"
#include "Count_Subsequence.h"


// Функция для выполнения теста с визуализацией и сохранением
void RunTest(const StringSequence& sequence, int lmin, int lmax, const std::string& filename) {
    auto result = CountSubsequences(sequence, lmin, lmax);

    // Логгируем результаты в консоль
    std::cout << "Results for sequence '" << sequence.GetData() << "':" << std::endl;
    for (int i = 0; i < result.GetLength(); ++i) {
        auto pair = result[i];
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    SaveResultsToCSV(filename, result);

    HistogramBuilder builder;
    builder.Build(result); // Используем IDictionary напрямую

    sf::RenderWindow window(sf::VideoMode(800, 600), "Подсчёт:");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        builder.DrawHistogram(window);
        window.display();
    }
}

void RunTests() {
    // Тест 1
    IDictionary<std::string, int> result1 = CountSubsequences(StringSequence("ababc"), 2, 3);
    assert(result1.Get("ab") == 2);
    assert(result1.Get("ba") == 1);
    assert(result1.Get("abc") == 1);
    assert(result1.Get("bab") == 1);

    // Преобразуем в map и строим гистограмму
    HistogramBuilder builder1;
    builder1.Build(result1);
    sf::RenderWindow window1(sf::VideoMode(800, 600), "Тест");
    while (window1.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window1.close();
            }
        }

        window1.clear(sf::Color::White);
        builder1.DrawHistogram(window1);
        window1.display();
    }

    // Тест 2
    IDictionary<std::string, int> result2 = CountSubsequences(StringSequence("aaaa"), 1, 2);
    assert(result2.Get("a") == 4);
    assert(result2.Get("aa") == 3);

    // Преобразуем в map и строим гистограмму
    HistogramBuilder builder2;
    builder2.Build(result2);
    sf::RenderWindow window2(sf::VideoMode(800, 600), "Тест 2");
    while (window2.isOpen()) {
        sf::Event event;
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window2.close();
            }
        }

        window2.clear(sf::Color::White);
        builder2.DrawHistogram(window2);
        window2.display();
    }

    // Тест 3
    IDictionary<std::string, int> result3 = CountSubsequences(StringSequence("abcde"), 2, 3);
    assert(result3.Get("ab") == 1);
    assert(result3.Get("bc") == 1);
    assert(result3.Get("abc") == 1);

    // Преобразуем в map и строим гистограмму
    HistogramBuilder builder3;
    builder3.Build(result3);
    sf::RenderWindow window3(sf::VideoMode(800, 600), "Тест 3");
    while (window3.isOpen()) {
        sf::Event event;
        while (window3.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window3.close();
            }
        }

        window3.clear(sf::Color::White);
        builder3.DrawHistogram(window3);
        window3.display();
    }

    // Тест 4
    IDictionary<std::string, int> result4 = CountSubsequences(StringSequence("abcdefg"), 1, 4);
    assert(result4.Get("ab") == 1);

    // Преобразуем в map и строим гистограмму
    HistogramBuilder builder4;
    builder4.Build(result4);
    sf::RenderWindow window4(sf::VideoMode(800, 600), "Тест 4");
    while (window4.isOpen()) {
        sf::Event event;
        while (window4.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window4.close();
            }
        }

        window4.clear(sf::Color::White);
        builder4.DrawHistogram(window4);
        window4.display();
    }

    // Тест 5
    IDictionary<std::string, int> result5 = CountSubsequences(StringSequence("abcabcabc"), 1, 3);
    assert(result5.Get("abc") == 3);

    // Преобразуем в map и строим гистограмму
    HistogramBuilder builder5;
    builder5.Build(result5);
    sf::RenderWindow window5(sf::VideoMode(800, 600), "Тест 5");
    while (window5.isOpen()) {
        sf::Event event;
        while (window5.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window5.close();
            }
        }

        window5.clear(sf::Color::White);
        builder5.DrawHistogram(window5);
        window5.display();
    }

    std::cout << "Все тесты пройдены успешно!" << std::endl;
}

void ManualInput() {
    std::string inputString;
    int lmin, lmax;
    std::string filename;

    std::cout << "Введите строку: ";
    std::cin >> inputString;

    std::cout << "Введите минимальную длину подпоследовательности (lmin): ";
    std::cin >> lmin;

    std::cout << "Введите максимальную длину подпоследовательности (lmax): ";
    std::cin >> lmax;

    RunTest(StringSequence(inputString), lmin, lmax, "result.csv");
}