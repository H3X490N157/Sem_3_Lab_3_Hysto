#pragma once

#include "IDictionary_Sequence.h"
#include "String_Sequence.h"
#include <string>
#include <vector>
#include <stdexcept>


IDictionary<std::string, int> CountSubsequences(const StringSequence& sequence, int lmin, int lmax) {
    IDictionary<std::string, int> counts;
    const std::string& data = sequence.GetData();  // Получаем строку напрямую
    for (int len = lmin; len <= lmax; ++len) {
        for (int i = 0; i <= data.size() - len; ++i) {
            std::string subsequence = data.substr(i, len);
            if (counts.ContainsKey(subsequence)) {
                counts.Get(subsequence)++;
            } else {
                counts.Add(subsequence, 1);
            }
        }
    }
    return counts;
}