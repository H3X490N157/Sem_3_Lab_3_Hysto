#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#pragma once


struct Person {
    std::string firstName;
    std::string lastName;
    int birthYear;
    double height;
    double weight;

    // Конструктор по умолчанию
    Person() : firstName(""), lastName(""), birthYear(0), height(0.0), weight(0.0) {}

    // Конструктор с параметрами
    Person(const std::string& firstName, const std::string& lastName, int birthYear, double height, double weight)
        : firstName(firstName), lastName(lastName), birthYear(birthYear), height(height), weight(weight) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.firstName << " " << p.lastName << ", " 
           << p.birthYear << ", " << p.height << " m, " 
           << p.weight << " kg";
        return os;
    }

    const std::string& GetFirstName() const { return firstName; }
    const std::string& GetLastName() const { return lastName; }
    int GetBirthYear() const { return birthYear; }
    double GetHeight() const { return height; }
    double GetWeight() const { return weight; }
    std::string GetName() const {
        return firstName + " " + lastName;
    }

    bool operator<=(const Person& other) const {
        if (firstName != other.firstName)
            return firstName < other.firstName;
        if (lastName != other.lastName)
            return lastName < other.lastName;
        if (birthYear != other.birthYear)
            return birthYear < other.birthYear;
        if (height != other.height)
            return height < other.height;
        return weight <= other.weight;
    }

    bool operator<(const Person& other) const {
        if (firstName != other.firstName)
            return firstName < other.firstName;
        if (lastName != other.lastName)
            return lastName < other.lastName;
        if (birthYear != other.birthYear)
            return birthYear < other.birthYear;
        if (height != other.height)
            return height < other.height;
        return weight < other.weight;
    }
};




int comparePersons(const Person& a, const Person& b) {
    if (a.firstName < b.firstName) return -1;
    if (a.firstName > b.firstName) return 1;

    if (a.lastName < b.lastName) return -1;
    if (a.lastName > b.lastName) return 1;

    if (a.birthYear < b.birthYear) return -1;
    if (a.birthYear > b.birthYear) return 1;

    if (a.height < b.height) return -1;
    if (a.height > b.height) return 1;

    if (a.weight < b.weight) return -1;
    if (a.weight > b.weight) return 1;

    return 0;
}


std::vector<Person> readPersonsFromFile(const std::string& filename) {
    std::vector<Person> persons;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return persons;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Person p;
        std::getline(iss, p.firstName, ',');
        std::getline(iss, p.lastName, ',');
        iss >> p.birthYear;
        iss.ignore(); // Пропустить запятую
        iss >> p.height;
        iss.ignore(); // Пропустить запятую
        iss >> p.weight;
        persons.push_back(p);
    }

    file.close();
    return persons;
}
