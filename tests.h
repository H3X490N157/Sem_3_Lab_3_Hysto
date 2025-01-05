#include <chrono>
#include <iomanip>
#include "person.h"
#include "csv_writer.h"


template <typename T>
void checkSorted(const Sequence<T>* seq) {
    for (int i = 1; i < seq->GetLength(); ++i) {
        assert(seq->Get(i-1) <= seq->Get(i) && "Ошибка сортировки!");
    }
    std::cout << "Успешно отсортировано\n";
}


template <typename T>
void testSorting(ISorter<T>& sorter, const char* sorterName) {
    std::cout << "Проверка " << sorterName << "...\n";

    ArraySequence<T> emptySequence;
    sorter.Sort(&emptySequence, compare);
    checkSorted(&emptySequence);
    printSequence(&emptySequence);

    ArraySequence<T> singleElementSequence;
    singleElementSequence.Append(42);
    sorter.Sort(&singleElementSequence, compare);
    checkSorted(&singleElementSequence);
    printSequence(&singleElementSequence);

    ArraySequence<T> sortedSequence;
    sortedSequence.Append(1);
    sortedSequence.Append(2);
    sortedSequence.Append(3);
    sorter.Sort(&sortedSequence, compare);
    checkSorted(&sortedSequence);
    printSequence(&sortedSequence);

    ArraySequence<T> reversedSequence;
    reversedSequence.Append(3);
    reversedSequence.Append(2);
    reversedSequence.Append(1);
    sorter.Sort(&reversedSequence, compare);
    checkSorted(&reversedSequence);
    printSequence(&reversedSequence);

    ArraySequence<T> randomSequence;
    randomSequence.Append(10);
    randomSequence.Append(2);
    randomSequence.Append(8);
    randomSequence.Append(5);
    randomSequence.Append(3);
    randomSequence.Append(-2281337);
    sorter.Sort(&randomSequence, compare);
    checkSorted(&randomSequence);
    printSequence(&randomSequence);

}


void testSorting(ISorter<std::string>& sorter, const char* sorterName) {
    std::cout << "Testing " << sorterName << " with strings...\n";

    ArraySequence<std::string> emptySequence;
    sorter.Sort(&emptySequence, compare<std::string>);
    checkSorted(&emptySequence);
    printSequence(&emptySequence);

    ArraySequence<std::string> singleElementSequence;
    singleElementSequence.Append("I am alone. HELLp");
    sorter.Sort(&singleElementSequence, compare<std::string>);
    checkSorted(&singleElementSequence);
    printSequence(&singleElementSequence);

    ArraySequence<std::string> reversedSequence;
    reversedSequence.Append("Cherry");
    reversedSequence.Append("Banana");
    reversedSequence.Append("Apple");
    sorter.Sort(&reversedSequence, compare<std::string>);
    checkSorted(&reversedSequence);
    printSequence(&reversedSequence);

    ArraySequence<std::string> randomSequence;
    randomSequence.Append("Zebra");
    randomSequence.Append("Apple");
    randomSequence.Append("Orange");
    randomSequence.Append("Banana");
    randomSequence.Append("Lemon");
    randomSequence.Append("Берёзовый сок");
    randomSequence.Append("Я не люблю BTS");
    sorter.Sort(&randomSequence, compare<std::string>);
    checkSorted(&randomSequence);
    printSequence(&randomSequence);
}


template <typename T>
void testUserSorting(ISorter<T>& sorter) {
    ArraySequence<T> sequence_test;
    T x;

    std::cout << "Введите элементы последовательности (введите 0 для завершения ввода):\n";
    while (true) {
        std::cin >> x;
        if (x == 0) break;
        sequence_test.Append(x);
    }

    std::cout << "Исходная последовательность:\n";
    printSequence(&sequence_test);

    sorter.Sort(&sequence_test, compare<T>);
    std::cout << "Отсортированная последовательность:\n";
    printSequence(&sequence_test);

    checkSorted(&sequence_test);
}

void testUserSortingString(ISorter<std::string>& sorter) {
    ArraySequence<std::string> sequence_test;
    std::string input;

    std::cout << "Введите строки для сортировки (введите пустую строку для завершения ввода):\n";
    std::cin.ignore(); // Очистка потока
    while (true) {
        std::getline(std::cin, input);
        if (input.empty()) break;
        sequence_test.Append(input);
    }

    std::cout << "Исходная последовательность:\n";
    printSequence(&sequence_test);

    sorter.Sort(&sequence_test, compare<std::string>);
    std::cout << "Отсортированная последовательность:\n";
    printSequence(&sequence_test);

    checkSorted(&sequence_test);
}

template <typename T>
void measureSortingTime(ISorter<T>& sorter, ArraySequence<T>& sequence, const std::string& algorithmName) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter.Sort(&sequence, comparePersons);  // Сортировка
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << algorithmName << " завершен за " << duration.count() << " миллисекунд.\n";
}

void testPersonSorting() {
    std::vector<Person> persons = readPersonsFromFile("persons.csv");
    if (persons.empty()) {
        std::cerr << "Нет данных для теста." << std::endl;
        return;
    }

    ArraySequence<Person> personSequence;
    for (const auto& person : persons) {
        personSequence.Append(person);
    }

    HeapSorter<Person> heapSorter;
    ShellSorter<Person> shellSorter;
    QuickSorter<Person> quickSorter;


    ArraySequence<Person> personSequenceForHeapSort = personSequence;  
    measureSortingTime(heapSorter, personSequenceForHeapSort, "HeapSort");

    ArraySequence<Person> personSequenceForShellSort = personSequence;  
    measureSortingTime(shellSorter, personSequenceForShellSort, "ShellSort");

    ArraySequence<Person> personSequenceForQuickSort = personSequence; 
    measureSortingTime(quickSorter, personSequenceForQuickSort, "QuickSort");

    writeResultsToCSV(personSequenceForQuickSort, "results.csv");

    std::cout << "Тестирование завершено.\n";
}

void testUserSortingPersons(ISorter<Person>& sorter) {
    std::cout << "Выберите способ ввода данных: (1 - вручную, 2 - файл): ";
    int inputChoice;
    std::cin >> inputChoice;
    ArraySequence<Person> persons;
    if (inputChoice == 1) {
        std::cout << "Введите количество записей: ";
        int n;
        std::cin >> n;
        std::cout << "Вводите данные в формате: Имя Фамилия Год_Рождения Рост Вес\n";
        while (n--) {
            std::string firstName, lastName;
            int birthYear;
            double height, weight;
            std::cin >> firstName >> lastName >> birthYear >> height >> weight;
            persons.Append({firstName, lastName, birthYear, height, weight});
        }
    } else {
        std::cout << "Введите имя файла с данными о людях (CSV: Имя,Фамилия,ГодРождения,Рост,Вес): ";
        std::string filename;
        std::cin >> filename;
        std::vector<Person> vectorPersons = readPersonsFromFile(filename);
        for (const auto& person : vectorPersons) {
            persons.Append(person);
        }
    }
    std::cout << "Сортировка началась...\n";
    sorter.Sort(&persons, comparePersons);

    // Вывод результата
    std::cout << "Сортировка завершена. Результат:\n";
    for (int i = 0; i < persons.GetLength(); ++i) {
        const Person& person = persons.Get(i);
        std::cout << person.GetFirstName() << " "
                  << person.GetLastName() << ", "
                  << person.GetBirthYear() << ", "
                  << person.GetHeight() << "m, "
                  << person.GetWeight() << "kg" << std::endl;
    }
}