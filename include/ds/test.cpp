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
void test_Constructs(){
    std::cout << "===============Constructs=======================\n";
    std::cout << "testando o construtor padrão\n";
    ds::Deque<int> d0; // Cria deque vazio
    std::cout << d0.to_string_full (); // delhalhe do deque
    std::cout << "\n\n";

    std::cout << "Testando o construtor com valor padrão\n";
    ds::Deque<int> d1(9, 100); // Cria deque com 9 elementos iguais a 100
    std::cout << d1.to_string_full(); // delhalhe do deque
    std::cout << "\n\n";
  
    std::cout << "Testando o  construtor de incio/fim:\n";
    ds::Deque<int> d2(d1.begin(), d1.end()); // Cria deque a partir do deque d1
    std::cout << d2.to_string_full(); // delhalhe do deque
    std::cout << "\n\n";

    std::cout << "Testando o construtor de copia:\n";
    ds::Deque<int> d3(d2); // Cria deque a partir do deque d2
    std::cout << d3.to_string_full(); // delhalhe do deque
    std::cout << "\n\n";
    std::cout << "Testando o construtor de lista de inicialização:\n";
    ds::Deque<int> d4{1, 2, 3, 4, 5,6,7,8,9}; // Cria deque a partir de uma lista de inicialização
    std::cout << d4.to_string_full(); // delhalhe do deque
    std::cout << "\n\n";
   
}
void test_Iterators(){
    std::cout << "===============Iterators========================\n\n";
  int k = 9;
  ds::Deque<int> d(k, 100); // Cria deque com k elementos iguais a 100}
  std::cout << "Deque para os testes:\n";
  std::cout << d.to_string_full(); // delhalhe do deque
  std::cout << "\n";
   auto it = d.begin();     // Iterador para o primeiro elemento

    std::cout << "Testando pré-incremento (++it):\n";
    for (int i = 0; i < k; ++i) {
        std::cout << it.to_string() << "-> value: " << *it <<"\n"; 
        ++it;
    }
    std::cout << "\n";

    it = d.begin(); // Reseta o iterador

    std::cout << "Testando pós-incremento (it++):\n";
    for (int i = 0; i < k; ++i) {
        std::cout << it.to_string() << "-> value: " << *it <<"\n"; 
        it++;
    }
    std::cout << "\n";


     it = d.end(); // Iterador para o último elemento

    std::cout << "Testando pré-decremento (--it):\n";
    
    for (int i = 0; i < k; ++i) {
        --it;
        std::cout << it.to_string() << "-> value: " << *it <<"\n";
    }
    std::cout << "\n";

    it = d.end (); // Iterador para o último elemento
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

    std::cout << "Testando o it1 < it2:\n";
    it = d.begin() + 4; // Avança 4 posições
    auto it7 = d.begin() + 1; // Avança 1 posição
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 168
    std::cout << it7.to_string() << "-> value: " << *it7 <<"\n"; // Deve imprimir: 42
    std::cout << (it < it7 ? "menor" : "maior ou igual") << "\n"; // Deve imprimir: maior ou igual
    std::cout << "\n";

    std::cout << "Testando o it1 > it2:\n";
    it = d.begin() + 4; // Avança 4 posições
    auto it8 = d.begin() + 1; // Avança 1 posição
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 168
    std::cout << it8.to_string() << "-> value: " << *it8 <<"\n"; // Deve imprimir: 42
    std::cout << (it > it8 ? "maior" : "menor ou igual") << "\n"; // Deve imprimir: maior
    std::cout << "\n";

    std::cout << "Testando o it1 <= it2:\n";
    it = d.begin() + 4; // Avança 4 posições
    auto it9 = d.begin() + 1; // Avança 1 posição
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 168
    std::cout << it9.to_string() << "-> value: " << *it9 <<"\n"; // Deve imprimir: 42
    std::cout << (it <= it9 ? "menor ou igual" : "maior") << "\n"; // Deve imprimir: maior
    std::cout << "\n";

    std::cout << "Testando o it1 >= it2:\n";
    it = d.begin() + 4; // Avança 4 posições
    auto it10 = d.begin() + 4; // Avança 1 posição
    std::cout << it.to_string() << "-> value: " << *it <<"\n"; // Deve imprimir: 168
    std::cout << it10.to_string() << "-> value: " << *it10 <<"\n"; // Deve imprimir: 168
    std::cout << (it >= it10 ? "maior ou igual" : "menor") << "\n"; // Deve imprimir: maior ou igual
    
}
int main() {
    std::cout << "================DEQUE OF TESTS==================\n\n";
   // test_Iterators();
   test_Constructs();
    return 0;
}
