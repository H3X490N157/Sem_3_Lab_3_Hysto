#include "tests.h"

int main() {
    std::cout << "Выберите режим работы:\n";
    std::cout << "1. Автоматические тесты\n";
    std::cout << "2. Ручной ввод\n";
    std::cout << "Введите номер режима: ";
    int choice;
    while (true){
        std::cin >> choice;
        switch (choice) {
            case 1:
            RunTests();
            break;
        case 2:
            ManualInput();
            break;
        default:
            std::cerr << "До свидания..." << std::endl;
            return 0;
    }
    }
    return 0;
}
