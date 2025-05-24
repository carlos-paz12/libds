/**
 * @file test.cpp
 * @author José Carlos da Paz Silva (carlos.paz.707@ufrn.edu.br)
 * @author Leandro Andrade (leandro.andrade.401@ufrn.edu.br)
 * @brief  class de testes do Deque sem cmake
 * @version 0.1
 * @date 202k-0k-24
 * 
 * @copyright Copyright (c) 202k
 * 
 */
#include "deque.hpp"
#include <iostream>

int main() {
  std::cout << "testando o construtor padrão\n";
  ds::Deque<int> de; // Cria deque vazio
  std::cout << de.to_string_full (); // delhalhe do deque
  std::cout << "\n";
  std::cout << "testando o construtor com valor padrão\n";
  int k = 5;
  ds::Deque<int> d(k, 42); // Cria deque com k elementos iguais a 42 * i, d  = {0, 42, 84,..., 42*(k-1)}
  std::cout << d.to_string_full(); // delhalhe do deque
  std::cout << "\n";

    auto it = d.begin();     // Iterador para o primeiro elemento

    std::cout << "Testando begin() e pré-incremento (++it):\n";
   //deve imprimir : 0 , 42, 84, 126, 168
    for (int i = 0; i < k; ++i) {
        std::cout << it.to_string() << "-> value: " << *it <<"\n"; 
        ++it;
    }
    std::cout << "\n";

    it = d.begin(); // Reseta o iterador

    std::cout << "Testando pós-incremento (it++):\n";
    // deve imprimir : 0 , 42, 84, 126, 168
    for (int i = 0; i < k; ++i) {
        std::cout << it.to_string() << "-> value: " << *it <<"\n"; 
        it++;
    }
    std::cout << "\n";

    // Reposiciona o iterador para o final
    it = d.begin();
    for (int i = 0; i < k; ++i) ++it; // avança até o final (equivalente a end())

    std::cout << "Testando pré-decremento (--it):\n";
    // deve imprimir : 168, 126, 84, 42, 0
    for (int i = 0; i < k; ++i) {
        --it;
        std::cout << it.to_string() << "-> value: " << *it <<"\n";
    }
    std::cout << "\n";

    // Reposiciona o iterador para o final novamente
    it = d.begin();
    for (int i = 0; i < k; ++i) ++it; // avança até o final (equivalente a end())
    //deve imprimir : 0 , 42, 84, 126, 168
    std::cout << "Testando pós-decremento (it--):\n";
    for (int i = 0; i < k; ++i) {
        it--;
        std::cout << it.to_string() << "-> value: " << *it <<"\n";
    }
    std::cout << "\n";

    std::cout << d.to_string_full(); // delhalhe do deque
    std::cout << "\n";

    std::cout << "Testando o it + numero:\n";
    it = d.begin();
    auto it2 = it + 3; // Avança 3 posições
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 0
    std::cout << it2.to_string() << "-> value: " << *it2 <<"\n"; // Deve imprimir: 128
    std::cout << "\n";

    std::cout << "Testando o numero + it:\n";
    it = d.begin();
    auto it3 = 3 + it; // Avança 3 posições
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 0
    std::cout << it3.to_string() << "-> value: " << *it3 <<"\n"; // Deve imprimir: 128
    std::cout << "\n";

    std::cout << "Testando o it - numero:\n";
    it = d.begin() + 4; // Avança 4 posições
    auto it4 = it - 3; // Retrocede 3 posições
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 168
    std::cout << it4.to_string() << "-> value: " << *it4 <<"\n"; // Deve imprimir: 42
    std::cout << "\n";

    std::cout<<"Testando o it += numero:\n";
    it = d.begin();
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 0
    it += 3; // Avança 3 posições
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 126
    std::cout << "\n";

    std::cout<<"Testando o it -= numero:\n";
    it = d.begin() + 4; // Avança 4 posições
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 168
    it -= 3; // Retrocede 3 posições
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 42
    std::cout << "\n";

    std::cout << "Testando o it - it:\n";
    it = d.begin() + 4; // Avança 4 posições
    auto itk = d.begin() + 1; // Avança 1 posição
    auto diff = it - itk; // Calcula a diferença
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 168
    std::cout << itk.to_string() << "-> value: " << *itk <<"\n"; // Deve imprimir: 42
    std::cout << "Diferença: " << diff << "\n"; // Deve imprimir: 3
    std::cout << "\n";

    std::cout << "Testando o it1 == it2:\n";
    it = d.begin() + 4; // Avança 4 posições
    auto it5 = d.begin() + 4; // Avança 4 posições
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 168
    std::cout << it5.to_string() << "-> value: " << *it5 <<"\n"; // Deve imprimir: 168
    std::cout << (it == it5 ? "iguais" : "diferentes") << "\n"; // Deve imprimir: iguais
    std::cout << "\n";

    std::cout << "Testando o it1 != it2:\n";
    it = d.begin() + 4; // Avança 4 posições
    auto it6 = d.begin() + 1; // Avança 1 posição
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 168
    std::cout << it6.to_string() << "-> value: " << *it6 <<"\n"; // Deve imprimir: 42
    std::cout << (it != it6 ?  "diferentes" : "iguais") << "\n"; // Deve imprimir: diferentes
    std::cout << "\n";

    return 0;
}
