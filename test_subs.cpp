#include "Hystogram_Builder_For_Subs.h"
#include <fstream>

std::map<std::string, int> ConvertToMap(const IDictionary<std::string, int>& dictionary) {
    std::map<std::string, int> result;
    for (int i = 0; i < dictionary.GetLength(); ++i) {
        auto pair = dictionary[i];
        result[pair.first] = pair.second;
    }
    return result;
}

void SaveResultsToCSV(const std::string& filename, const IDictionary<std::string, int>& results) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "Subsequence,Count\n";  // Заголовки
    for (int i = 0; i < results.GetLength(); ++i) {
        auto pair = results[i];
        file << pair.first << "," << pair.second << "\n";
    }

    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}

// Функция для выполнения теста с визуализацией и сохранением
void RunTest(const StringSequence& sequence, int lmin, int lmax, const std::string& filename) {
    auto result = CountSubsequences(sequence, lmin, lmax);

    // Логгируем результаты в консоль
    std::cout << "Results for sequence '" << sequence.GetData() << "':" << std::endl;
    for (int i = 0; i < result.GetLength(); ++i) {
        auto pair = result[i];
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Сохраняем результаты в файл
    SaveResultsToCSV(filename, result);

    // Преобразуем IDictionary в std::map и строим гистограмму
    HistogramBuilder builder;
    builder.Build(ConvertToMap(result));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Subsequence Counts");
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
    RunTest(StringSequence("ababc"), 2, 3, "results_subs_ababc.csv");
    RunTest(StringSequence("aaaa"), 1, 2, "results_subs_aaaa.csv");
    RunTest(StringSequence("abcde"), 2, 3, "results_subs_abcde.csv");
    RunTest(StringSequence("abcdefg"), 1, 4, "results_subs_abcdefg.csv");
    RunTest(StringSequence("abcabcabc"), 1, 3, "results_subs_abcabcabc.csv");

    std::cout << "All tests passed successfully!" << std::endl;
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
        std::cerr << "Manual input is not supported yet." << std::endl;
        break;
    default:
        std::cerr << "Invalid choice. Exiting..." << std::endl;
        return 1;
    }

    return 0;
}

