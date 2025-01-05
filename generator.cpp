#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

struct Person {
    std::string firstName;
    std::string lastName;
    int birthYear;
    double height;
    double weight;
};


std::vector<std::string> russianFirstNames = {
    "Алексей", "Иван", "Дмитрий", "Максим", "Никита", "Придурочный", "Чувак", "Четтер", "Николай", "Егор", "ЫЫЫЫ"
};
std::vector<std::string> russianLastNames = {
    "Иванов", "Петров", "Сидоров", "Кузнецов", "Попов", "Смирнов", "Васильев", "Новиков", "Морозов", "Фёдоров", "Йоу", "Человек"
};

std::vector<std::string> englishFirstNames = {
    "Vladimir", "John", "Michael", "Robert", "William", "David", "Mary", "Patricia", "Jennifer", "Linda", "Elizabeth"
};
std::vector<std::string> englishLastNames = {
    "Roslovtsev", "Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"
};

std::string getRandomElement(const std::vector<std::string>& list, std::mt19937& rng) {
    std::uniform_int_distribution<size_t> dist(0, list.size() - 1);
    return list[dist(rng)];
}

int main() {
    std::ofstream outFile("persons.csv");
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> yearDist(1950, 2023);
    std::uniform_real_distribution<double> heightDist(1.5, 2.28);
    std::uniform_real_distribution<double> weightDist(50.0, 120.0);

    std::cout << "Введите количество элементов";
    int number;
    std::cin >> number;
    for (int i = 0; i < number; ++i) {
        bool isRussian = rng() % 2;
        std::string firstName = isRussian ? getRandomElement(russianFirstNames, rng) : getRandomElement(englishFirstNames, rng);
        std::string lastName = isRussian ? getRandomElement(russianLastNames, rng) : getRandomElement(englishLastNames, rng);
        int birthYear = yearDist(rng);
        double height = heightDist(rng);
        double weight = weightDist(rng);

        outFile << firstName << "," << lastName << "," << birthYear << "," 
                << height << "," << weight << "\n";
    }

    outFile.close();
    std::cout << "Сгенерированы элементы в 'persons.csv" << std::endl;

    return 0;
}
