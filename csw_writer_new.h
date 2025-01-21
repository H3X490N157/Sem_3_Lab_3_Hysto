#include "Hystogram_Builder_For_Subs.h"
#include <fstream>
#include <cassert>
#include <SFML/Graphics.hpp>

void SaveResultsToCSV(const std::string& filename, const IDictionary<std::string, int>& results) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия: " << filename << std::endl;
        return;
    }

    file << "Subsequence,Count\n";  // Заголовки
    for (int i = 0; i < results.GetLength(); ++i) {
        auto pair = results[i];
        file << pair.first << "," << pair.second << "\n";
    }

    file.close();
    std::cout << "Результаты сохранены " << filename << std::endl;
}