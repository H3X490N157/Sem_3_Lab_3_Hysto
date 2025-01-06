#ifndef IDICTIONARY_H
#define IDICTIONARY_H
#pragma once
#include "sequence.h"
#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm>

template <typename Key, typename Value>
class IDictionary : public Sequence<std::pair<Key, Value>> {
private:
    std::vector<std::pair<Key, Value>> items;

public:
    // Методы Sequence
    std::pair<Key, Value>& GetFirst() override {
        if (items.empty()) throw std::out_of_range("Dictionary is empty");
        return items.front();
    }

    std::pair<Key, Value>& GetLast() override {
        if (items.empty()) throw std::out_of_range("Dictionary is empty");
        return items.back();
    }

    std::pair<Key, Value>& Get(int index) const override {
        if (index < 0 || index >= items.size()) throw std::out_of_range("Index out of range");
        return const_cast<std::pair<Key, Value>&>(items[index]);
    }

    std::pair<Key, Value>& operator[](int index) override {
        return Get(index);
    }

    int GetLength() const override {
        return items.size();
    }

    void Append(std::pair<Key, Value> item) override {
        Add(item.first, item.second);
    }

    void Prepend(std::pair<Key, Value> item) override {
        items.insert(items.begin(), item);
    }

    void InsertAt(std::pair<Key, Value> item, int index) override {
        if (index < 0 || index > items.size()) throw std::out_of_range("Index out of range");
        items.insert(items.begin() + index, item);
    }

    // Методы IDictionary
    void Add(const Key& key, const Value& value) {
        for (auto& item : items) {
            if (item.first == key) {
                item.second = value;
                return;
            }
        }
        items.emplace_back(key, value);
    }

    Value& Get(const Key& key) {
        for (auto& item : items) {
            if (item.first == key) {
                return item.second;
            }
        }
        throw std::runtime_error("Key not found");
    }

    bool ContainsKey(const Key& key) const {
        for (const auto& item : items) {
            if (item.first == key) {
                return true;
            }
        }
        return false;
    }

    void Remove(const Key& key) {
        items.erase(std::remove_if(items.begin(), items.end(),
                                   [&key](const std::pair<Key, Value>& item) { return item.first == key; }),
                    items.end());
    }
};

#endif // IDICTIONARY_H
