#include <fstream>
#include <sstream>
#include <vector>
#include "person.h"

std::vector<Person> read_persons_from_csv(const std::string& filename) {
    std::vector<Person> persons;
    std::ifstream file(filename);
    std::string line;

    // Пропустить заголовок, если он есть
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string first_name, last_name;
        int birth_year;
        double height, weight;

        // Чтение данных из строки
        std::getline(ss, first_name, ',');
        std::getline(ss, last_name, ',');
        ss >> birth_year;
        ss.ignore();  // Пропускаем запятую
        ss >> height;
        ss.ignore();  // Пропускаем запятую
        ss >> weight;

        persons.push_back(Person(first_name, last_name, birth_year, height, weight));
    }

    return persons;
}
