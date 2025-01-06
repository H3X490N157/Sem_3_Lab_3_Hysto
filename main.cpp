#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>  // для std::pair

// Определяем структуру для хранения данных в HashMap
template <typename KeyType, typename ValueType>
class HashMap {
private:
    // Внутренний контейнер для хранения ключ-значение (с использованием связных списков)
    std::vector<std::list<std::pair<KeyType, ValueType>>> table;
    size_t size;

    // Хеш-функция для вычисления индекса
    size_t hash(const KeyType& key) const {
        std::hash<KeyType> hashFn;
        return hashFn(key) % table.size();
    }

public:
    HashMap(size_t capacity = 100) : table(capacity), size(0) {}

    // Добавление элемента в HashMap
    void insert(const KeyType& key, const ValueType& value) {
        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;  // Обновление значения, если ключ уже существует
                return;
            }
        }
        table[index].emplace_back(key, value);  // Добавление нового элемента
        ++size;
    }

    // Метод для получения значения по ключу
    bool get(const KeyType& key, ValueType& value) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;  // Если ключ не найден
    }

    // Итератор для перебора элементов
    class Iterator {
    private:
        typename std::list<std::pair<KeyType, ValueType>>::iterator listIt;
        typename std::vector<std::list<std::pair<KeyType, ValueType>>>::iterator vecIt;
        typename std::vector<std::list<std::pair<KeyType, ValueType>>>::iterator vecEnd;

    public:
        Iterator(typename std::vector<std::list<std::pair<KeyType, ValueType>>>::iterator start,
                 typename std::vector<std::list<std::pair<KeyType, ValueType>>>::iterator end)
            : vecIt(start), vecEnd(end) {
            // Находим первый непустой список
            while (vecIt != vecEnd && vecIt->empty()) {
                ++vecIt;
            }
            if (vecIt != vecEnd) {
                listIt = vecIt->begin();
            }
        }

        // Оператор разыменования
        std::pair<KeyType, ValueType>& operator*() {
            return *listIt;
        }

        // Оператор доступа к элементу
        std::pair<KeyType, ValueType>* operator->() {
            return &(*listIt);
        }

        // Оператор инкремента (для перехода к следующему элементу)
        Iterator& operator++() {
            ++listIt;
            // Если дошли до конца списка, переходим к следующему не пустому списку
            while (vecIt != vecEnd && listIt == vecIt->end()) {
                ++vecIt;
                if (vecIt != vecEnd) {
                    listIt = vecIt->begin();
                }
            }
            return *this;
        }

        // Оператор сравнения
        bool operator!=(const Iterator& other) const {
            return vecIt != other.vecIt || (vecIt == other.vecIt && listIt != other.listIt);
        }
    };

    // Метод begin, возвращает итератор на первый элемент
    Iterator begin() {
        return Iterator(table.begin(), table.end());
    }

    // Метод end, возвращает итератор на "конец"
    Iterator end() {
        return Iterator(table.end(), table.end());
    }
};

int main() {
    HashMap<std::string, int> histogram;

    // Вставка значений
    histogram.insert("apple", 3);
    histogram.insert("banana", 2);
    histogram.insert("cherry", 5);

    // Перебор элементов с использованием итераторов
    for (const auto& pair : histogram) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
