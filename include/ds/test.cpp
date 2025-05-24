#include "deque.hpp"
#include <iostream>

int main() {
  std::cout << "testando o construtor padrão\n";
  ds::Deque<int> de; // Cria deque vazio
  std::cout << de.to_string_full ();
  std::cout << "\n";
  std::cout << "testando o construtor com valor padrão\n";
  ds::Deque<int> d(5, 42); // Cria deque com 5 elementos iguais a 42
  std::cout << d.to_string_full();
  std::cout << "\n";

    auto it = d.begin();     // Iterador para o primeiro elemento

    std::cout << "Testando begin() e pré-incremento (++it):\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 42 42 42 42 42
        ++it;
    }
    std::cout << "\n";

    it = d.begin(); // Reseta o iterador

    std::cout << "Testando pós-incremento (it++):\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 42 42 42 42 42
        it++;
    }
    std::cout << "\n";

    // Reposiciona o iterador para o final
    it = d.begin();
    for (int i = 0; i < 5; ++i) ++it; // avança até o final (equivalente a end())

    std::cout << "Testando pré-decremento (--it):\n";
    for (int i = 0; i < 5; ++i) {
        --it;
        std::cout << it.to_string() << "-> value: " << *it <<"\n";// Deve imprimir: 42 42 42 42 42
    }
    std::cout << "\n";

    // Reposiciona o iterador para o final novamente
    it = d.begin();
    for (int i = 0; i < 5; ++i) ++it;

    std::cout << "Testando pós-decremento (it--):\n";
    for (int i = 0; i < 5; ++i) {
        it--;
        std::cout << it.to_string() << "-> value: " << *it <<"\n";// Deve imprimir: 42 42 42 42 42
    }
    std::cout << "\n";

    return 0;
}
