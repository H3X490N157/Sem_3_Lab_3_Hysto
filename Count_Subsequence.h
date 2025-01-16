#ifndef COUNT_SUBSEQUENCE_H
#define COUNT_SUBSEQUENCE_H

#pragma once

#include "IDictionary_Sequence.h"
#include "sequence.h"
#include <string>
#include <vector>
#include <stdexcept>

template <typename T>
IDictionary<std::string, int> CountSubsequences(const Sequence<T>& input, int l_min, int l_max) {
    IDictionary<std::string, int> result;

    int n = input.GetLength();
    for (int start = 0; start < n; ++start) {
        for (int length = l_min; length <= l_max && start + length <= n; ++length) {
            std::string substring;
            for (int i = 0; i < length; ++i) {
                substring += const_cast<Sequence<T>&>(input)[start + i]; // Снятие const
            }

            if (result.ContainsKey(substring)) {
                result.Get(substring) += 1;
            } else {
                result.Add(substring, 1);
            }
        }
    }

    return result;
}

#endif // COUNT_SUBSEQUENCE_H
