template <typename T>
void printSequence(const Sequence<T>* seq) {
    for (int i = 0; i < seq->GetLength(); ++i) {
        std::cout << seq->Get(i) << " ";
    }
    std::cout << "\n";
}