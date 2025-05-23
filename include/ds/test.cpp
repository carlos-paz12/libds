#include "deque.hpp"  
#include <iostream>
int main() {
    ds::Deque<int> d(5, 42); // Cria deque com 5 elementos iguais a 42

    auto it = d.begin();     // Iterador para o primeiro elemento

    std::cout << "Testando pré-incremento (++it):\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << *it << ' '; // Deve imprimir: 42 42 42 42 42
        ++it;
    }
    std::cout << "\n";

    it = d.begin(); // Reseta o iterador

    std::cout << "Testando pós-incremento (it++):\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << *it << ' '; // Deve imprimir: 42 42 42 42 42
        it++;
    }
    std::cout << "\n";

    return 0;
}
