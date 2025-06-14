#ifndef DEQUE_ITERATOR_HPP
#define DEQUE_ITERATOR_HPP

#include <cstddef>  // std::size_t
#include <iterator> // std::random_access_iterator_tag
#include <sstream>  // std::ostringstream

namespace ds
{
template<typename T, std::size_t BlockSize, typename BlockItr, typename ItemItr>
class Iterator
{
public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

private:
  BlockItr m_block;  //!< Ponteiro para o bloco atual.
  ItemItr m_current; //!< Ponteiro para o elemento dentro do bloco atual.

  // [!] Nós Precisamos de conceder esta amizade para permitir que o Deque
  // acesso os atributos privados do iterador.
  template<typename, std::size_t, std::size_t>
  friend class Deque;

public:
  /// @brief Construtor padrão.
  Iterator() : m_block(), m_current() { }

  /// @brief Construtor utilitário.
  Iterator(const BlockItr& block, const ItemItr& current) : m_block(block), m_current(current) { }

  /// @brief Construtor de cópia.
  Iterator(const Iterator& other) : m_block(other.m_block), m_current(other.m_current) { }

  /// @brief Operador de atribuição.
  Iterator& operator=(const Iterator& other) {
    if (this != &other) {
      m_block = other.m_block;
      m_current = other.m_current;
    }
    return *this;
  }

  /// @brief Operador de dereferência.
  reference operator*() { return *m_current; }

  /// @brief Operador de pré-incremento.
  Iterator& operator++() {
    if (m_current + 1 == (*m_block)->end()) // [!] Verifica se chegou no fim do bloco atual.
    {
      // [!] Se chegou...
      m_block++;                       // [!] avança para o próximo bloco e...
      m_current = (*m_block)->begin(); // [!] posiciona o ponteiro do elemento
                                       // para o início do novo bloco.
    } else {
      m_current++;
    } // [!] Avança o iterador dentro do bloco atual
    return *this;
  }

  /// @brief Operador de pós-incremento.
  Iterator operator++(int) {
    Iterator temp = *this; // [!] Armazena temporariamente o estado atual do iterador.
    ++(*this);             // [!] Chama o pré-incremento.
    return temp;           // [!] Retorna o iterador antigo.
  }

  /// @brief Operador de pré-incremento.
  Iterator& operator--() {
    if (m_current == (*m_block)->begin()) { // Se chegou ao início do bloco
      m_block--;                            // Retrocede para o bloco anterior
      m_current = (*m_block)->end();        // Posição após o último
    }
    m_current--; // Agora retrocede para o último elemento válido
    return *this;
  }

  /// @brief Operador de pós-incremento.
  Iterator operator--(int) {
    Iterator temp = *this; // salva estado atual
    --(*this);             // chama o Pre-decremente
    return temp;           // @brief Operador de pré-incrementoretorna o iterador antigo
  }

  /// @brief Operador de adição à direita.
  Iterator operator+(difference_type n) const {
    Iterator temp = *this; // salva estado atual
    for (difference_type i = 0; i < n; ++i) {
      ++temp; // Avança o iterador dentro do bloco atual
    }
    return temp; // Retorna o iterador avançado
  }

  /// @brief Operador de adição à esquerda.
  friend Iterator operator+(Iterator::difference_type n, const Iterator& other) {
    Iterator temp = other; // salva estado atual
    for (difference_type i = 0; i < n; ++i) {
      ++temp; // Avança o iterador dentro do bloco atual
    }
    return temp; // Retorna o iterador avançado
  }

  /// @brief Operador de subtração à direita.
  Iterator operator-(difference_type n) const {
    Iterator temp = *this; // salva estado atual
    for (difference_type i = 0; i < n; ++i) {
      --temp; // Retrocede o iterador dentro do bloco atual
    }
    return temp; // Retorna o iterador retrocedido
  }

  /// @brief Operador de salto para frente.
  Iterator operator+=(difference_type n) {
    *this = *this + n; // Chama o operador de soma
    return *this;      // Retorna o iterador atualizado
  }

  /// @brief Operador de salto para trás.
  Iterator operator-=(difference_type n) {
    *this = *this - n; // Chama o operador de subtração
    return *this;      // Retorna o iterador atualizado
  }

  /// @brief Operadador de subtração entre iteradores.
  difference_type operator-(const Iterator& other) const {
    // Diferença de blocos
    difference_type block_diff = this->m_block - other.m_block;
    block_diff *= BlockSize;

    // Diferença dentro dos blocos
    difference_type this_offset = m_current - (*m_block)->begin();
    difference_type other_offset = other.m_current - (*other.m_block)->begin();

    return block_diff + (this_offset - other_offset);
  }

  /**
   * @brief Compara se o iterador à esquerda é igual ao iterador à direita.
   *
   * @param other Iterador à direita.
   *
   * @return true Se os dois iteradores são iguais, `false` caso contrário.
   */
  bool operator==(const Iterator& other) const { return (m_current == other.m_current) and (m_block == other.m_block); }

  /**
   * @brief Compara se o iterador à esquerda é diferente do iterador à direita.
   *
   * @param other Iterador à direita.
   *
   * @return true Se os dois iteradores são diferentes, `false` caso contrário.
   */
  bool operator!=(const Iterator& other) const { return not(*this == other); }

  /**
   * @brief Compara se o iterador à esquerda é menor que o iterador à direita.
   *
   * @param other Iterador à direita.
   *
   * @return true Se o iterador à esquerda é menor que o iterador à direita,
   * `false` caso contrário.
   */
  bool operator<(const Iterator& other) const {
    return (m_block < other.m_block) or ((m_block == other.m_block) and (m_current < other.m_current));
  }

  /**
   * @brief Compara se o iterador à esquerda é maior que o iterador à direita.
   *
   * @param other Iterador à direita.
   *
   * @return true Se o iterador à esquerda é maior que o iterador à direita,
   * `false` caso contrário.
   */
  bool operator>(const Iterator& other) const { return not(*this < other); }

  /**
   * @brief Compara se o iterador à esquerda é menor ou igual que o iterador à
   * direita.
   *
   * @param other Iterador à direita.
   *
   * @return true Se o iterador à esquerda é menor ou igual que o iterador à
   * direita, `false` caso contrário.
   */
  bool operator<=(const Iterator& other) const { return (*this < other) or (*this == other); }

  /**
   * @brief Compara se o iterador à esquerda é maior ou igual que o iterador à
   * direita.
   *
   * @param other Iterador à direita.
   *
   * @return true Se o iterador à esquerda é maior ou igual que o iterador à
   * direita, `false` caso contrário.
   */
  bool operator>=(const Iterator& other) const { return not(*this < other); }

  /**
   * @brief Retorna o conteúdo do iterador como uma string.
   */
  [[nodiscard]] std::string to_string() const {
    std::ostringstream oss{};
    oss << "[&block: " << *m_block << ", &current: " << m_current << "]";
    return oss.str();
  }
};
} // namespace ds

#endif