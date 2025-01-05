void writeResultsToCSV(const ArraySequence<Person>& persons, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи!" << std::endl;
        return;
    }

    outFile << "Имя,Фамилия,Год рождения,Рост,Вес\n"; 
    for (size_t i = 0; i < persons.GetLength(); ++i) {
        const Person& person = persons.Get(i);
        outFile << person.firstName << ","
                << person.lastName << ","
                << person.birthYear << ","
                << person.height << ","
                << person.weight << "\n";
    }

    outFile.close();
    std::cout << "Результаты записаны в файл: " << filename << "\n";
}