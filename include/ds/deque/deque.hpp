#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <array>     // std::array
#include <cmath>     // std::floor, std::ceil
#include <cstddef>   // std::size_t, ptrdiff_t
#include <iostream>  // sttd::cout
#include <iterator>  // std::iterator_traits, std::distance
#include <memory>    // std::shared_ptr, std::unique_ptr, std::make_shared, std::make_unique
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::out_of_range
#include <utility>   // std::move
#include <vector>    // std::vector

#include "iterator.hpp"

namespace ds
{
template<typename T, std::size_t BlockSize = 3, std::size_t DefaultBlkMapSize = 1>
class Deque
{
public:
  //================================================== MEMBER TYPES
  //== Typical container aliases
  using size_type = std::size_t;             //!< The size type.
  using value_type = T;                      //!< The value type.
  using pointer = value_type*;               //!< Pointer to a value stored in the container.
  using reference = value_type&;             //!< Reference to a value.
  using const_reference = const value_type&; //!< Const reference to a value.
  using difference_type = ptrdiff_t;         //!< Difference type between pointers.

  //== Aliases for the Deque types.
  /// A block is a fixed sized array of T that actually holds the data.
  using block_t = std::array<T, BlockSize>;
  /// Basic smart pointer to a block of data items.
  using block_sptr_t = std::shared_ptr<block_t>;
  /// This type represents a list of smart pointers to blocks of memory.
  using block_list_t = std::vector<block_sptr_t>;
  /// Regular iterator.
  using iterator = Iterator<T, BlockSize, typename block_list_t::iterator, typename block_t::iterator>;
  /// Const iterator.
  using const_iterator =
    Iterator<const T, BlockSize, typename block_list_t::const_iterator, typename block_t::const_iterator>;

private:
  //================================================== MEMBER VARIABLES
  std::unique_ptr<block_list_t> m_mob; //!< The dynamic map of blocks.
  iterator m_front;                    //!< Iterator to the front block.
  iterator m_back;                     //!< Iterator to the back block.
  std::size_t m_count;                 //!< # of elements stored in the map.

public:
  //================================================== MEMBER FUNCTIONS
  /**
   * @brief Default constructor.

   * Constructs an empty Deque.
   */
  Deque() : m_mob(std::make_unique<block_list_t>(DefaultBlkMapSize)), m_count(0) {
    /*!
     * In default case, `start_block` will be given the floor value of 1/2, i.e.
     * 0. And `start_index` will be given the floor value of 3/2, i.e 1.
     *
     * I.e., we want something like this.
     *
     *                     *m_front.m_block
     *                      | *m_front_itr.m_current
     *                      |  |
     *                      v  v
     * Deque<int, 3, 1> = { [- - -] }
     *
     *                      *m_back_itr.m_block
     *                       | *m_back_itr.m_current
     *                       |  |
     *                       v  v
     * Deque<int, 3, 1> = { *[- - -] }
     *
     * ==================================================================================================
     *
     * In case, for example, with block map size equals 3 and block size equals
     * 5, we need something like this:
     *
     *                                   *m_front_itr.m_block
     *                                    |   *m_front_itr.m_current
     *                                    |    |
     *                                    v    v
     * Deque<int, 5, 3> = { *[- - - - -] *[- - - - -] *[- - - - -] }
     *
     *                                   *m_back_itr.m_block
     *                                    |   *m_back_itr.m_current
     *                                    |    |
     *                                    v    v
     * Deque<int, 5, 3> = { *[- - - - -] *[- - - - -] *[- - - - -] }
     */

    //!< Offset to determine the starting block (center of the map).
    size_type offset_mob{ m_mob->size() / 2 };
    //!< Offset to determine the starting element within the starting block (center).
    size_type offset_block{ BlockSize / 2 };

    // [!] Allocates a block only to the central iterators.
    (*m_mob)[offset_mob] = std::make_shared<block_t>();

    // [!] Set iterators to the middle of the block map.
    m_front = iterator(m_mob->begin() + offset_mob, (*m_mob)[offset_mob]->begin() + offset_block);
    m_back = iterator(m_mob->begin() + offset_mob, (*m_mob)[offset_mob]->begin() + offset_block);
  }

  /**
   * @brief Fill constructor.
   *
   * Constructs a Deque and initialize it with `n` copies of `value` of type
   * `value_type`. If `value` is not provided, a default constructor
   * `value_type()` is used.
   */
  explicit Deque(size_type n, const_reference value = value_type()) : m_count(n) {
    size_type blocks_needed{ (n + BlockSize) / BlockSize };
    size_type map_size{ std::max(DefaultBlkMapSize, blocks_needed) };

    m_mob = std::make_unique<block_list_t>(map_size);
    for (size_type i{ 0 }; i < blocks_needed; ++i) {
      (*m_mob)[i] = std::make_shared<block_t>();
    }

    // [!] Set iterators to the start of the block map.
    m_front = iterator(m_mob->begin(), (*m_mob)[0]->begin());

    iterator it{ m_front };
    for (size_type i{ 0 }; i < n; ++i) {
      *(it) = value;
      ++it;
    }

    m_back = it;
  }

  /**
   * @brief Range consatructor.
   *
   * Constructs a container with as many elements as the range [first,last), in
   * the same order.
   */
  template<typename InputIt, typename = typename std::iterator_traits<InputIt>::iterator_category>
  Deque(InputIt first, InputIt last) {
    size_type n{ static_cast<size_type>(std::distance(first, last)) };
    size_type blocks_needed{ (n + BlockSize) / BlockSize };
    size_type map_size{ std::max(DefaultBlkMapSize, blocks_needed) };

    m_mob = std::make_unique<block_list_t>(map_size);
    for (size_type i{ 0 }; i < blocks_needed; ++i) {
      (*m_mob)[i] = std::make_shared<block_t>();
    }

    // [!] Set iterators to the start of the block map.
    m_front = iterator(m_mob->begin(), (*m_mob)[0]->begin());

    iterator it{ m_front };
    InputIt runner{ first };
    while (runner != last) {
      *it = *runner;
      ++it;
      ++runner;
    }

    m_back = it;
    m_count = n;
  }

  /**
   * @brief Copy constructor.
   *
   * Constructs a container with a copy of each of the elements in `other`.
   */
  Deque(const Deque& other) : m_mob(std::make_unique<block_list_t>(other.m_mob->size())), m_count(other.m_count) {
    for (size_type i{ 0 }; i < m_mob->size(); ++i) {
      (*m_mob)[i] = std::make_shared<block_t>();
      std::copy((*other.m_mob)[i]->begin(), (*other.m_mob)[i]->end(), (*m_mob)[i]->begin());
    }

    const auto mob_front_offset{ std::distance(other.m_mob->begin(), other.m_front.m_block) };
    const auto block_front_offset{ std::distance((*other.m_front.m_block)->begin(), other.m_front.m_current) };
    const auto mob_back_offset{ std::distance(other.m_mob->begin(), other.m_back.m_block) };
    const auto block_back_offset{ std::distance((*other.m_back.m_block)->begin(), other.m_back.m_current) };

    m_front = iterator(m_mob->begin() + mob_front_offset, (*m_mob)[mob_front_offset]->begin() + block_front_offset);
    m_back = iterator(m_mob->begin() + mob_back_offset, (*m_mob)[mob_back_offset]->begin() + block_back_offset);
  }

  /**
   * @brief Initializer list constructor.
   *
   * Constructs a container initialized with the elements in the initializer
   * list `il`, in the same order.
   */
  Deque(const std::initializer_list<T>& il) {
    size_type n{ static_cast<size_type>(il.size()) }; // Número de elementos no intervalo

    // Número de blocos necessários para armazenar n elementos
    size_type blocks_needed{ (n + BlockSize - 1) / BlockSize };

    // Sempre alocar 3 blocos (1 no meio com espaço para crescer dos dois lados)
    size_type map_size{ blocks_needed + 1 }; // adiciona 1 blocos extra
    // Inicializa o vetor de blocos com ponteiros nulos
    m_mob = std::make_unique<block_list_t>(map_size);
    // Aloca os blocos
    for (size_type i{ 0 }; i < map_size; ++i) {
      (*m_mob)[i] = std::make_shared<block_t>(); // O tamanho do bloco está
                                                 // definido em `block_t`.
    }
    // Posição central onde os dados começarão
    size_type start_block{ 0 };
    // Inicializa iterador para o início (posição lógica 0)
    m_front = iterator(m_mob->begin() + start_block,  // iterador para o bloco do início
                       (*m_mob)[start_block]->begin() // iterador para a posição inicial dentro do bloco
    );

    auto it{ m_front };
    int c{ 0 };
    // Preenche os elementos com os valores do intervalo [first, last)
    for (auto i : il) {
      *(it) = i;
      ++it;
      ++c;
    }
    m_back = it; // aponta para uma posição além do último
    // Atualiza a contagem
    m_count = c;
  }

  /**
   * @brief Destructor.
   *
   * Destroys all container elements, and deallocates all the storage allocated
   * by the Deque.
   */
  ~Deque() = default;

  /**
   * @brief Assign operator.
   *
   * Copies all the elements from `other` into the container.
   */
  Deque& operator=(const Deque& other) {
    if (this != &other) {
      size_type mob_size{ other.m_mob->size() }; // Número de blocos alocados
      m_mob = std::make_unique<block_list_t>(mob_size);

      // Aloca e copia os blocos
      for (size_type i = 0; i < mob_size; ++i) {
        (*m_mob)[i] = std::make_shared<block_t>();
        std::copy((*other.m_mob)[i]->begin(),
                  (*other.m_mob)[i]->end(),
                  (*m_mob)[i]->begin()); // Copia os elementos do bloco
      }

      // Recalcula a distância entre m_mob->begin() e os iteradores do other
      auto front_blk_index{ other.m_front.m_block - other.m_mob->begin() }; // faz o calculo da distância entre o
                                                                            // bloco inicial e o bloco atual
      auto back_blk_index{ other.m_back.m_block - other.m_mob->begin() };   // faz o calculo da distância entre o
                                                                            // bloco inicial e o bloco atual
      // Recalcula a posição dentro do bloco
      auto front_pos{ other.m_front.m_current - (*other.m_front.m_block)->begin() }; // valor da posição dentro do bloco
      auto back_pos{ other.m_back.m_current - (*other.m_back.m_block)->begin() }; // valor da posição dentro do bloco

      // Cria novos iteradores com base nos blocos da nova m_mob
      m_front = iterator(m_mob->begin() + front_blk_index,
                         (*m_mob)[front_blk_index]->begin() + front_pos); // iterador para o bloco do início

      m_back = iterator(m_mob->begin() + back_blk_index,
                        (*m_mob)[back_blk_index]->begin() + back_pos); // iterador para o bloco do fim
      m_count = other.m_count;                                         // Atualiza a contagem
    }
    return *this;
  }

  //================================================== ITERATORS:
  /// Return an iterator to the Deque's first element.
  iterator begin() { return m_front; }

  /// Return an iterator to a location following the Deque's last element.
  iterator end() { return m_back; }

  /// Return a const iterator to the Deque's first element.
  const_iterator cbegin() const { return const_iterator(m_front.m_block, m_front.m_current); }

  /// Return a const iterator to a location following the Deque's last element.
  const_iterator cend() const { return const_iterator(m_back.m_block, m_back.m_current); }

  //================================================== CAPACITY
  /**
   * @brief Returns the number of elements currently stored in the Deque.
   *
   * @return The number of elements in the Deque.
   */
  [[nodiscard]] size_type size() const { return m_count; }

  /// Change the number of elements stored in the container.
  /*!
   * If the current size ( size() ) is greater than `count` , the container is
   * reduced to the first count element. On the other hand, if the current size
   * is less than count , then additional default-inserted elements are appended
   * to the container.
   *
   * Lastly, if current size is equal to count, nothing happens.
   */
  void resize(size_type count) {
    if (m_count < count) {
      while (m_count < count) {
        push_back(value_type());
      }
    } else if (m_count > count) {
      while (m_count > count) {
        pop_back();
      }
    }
  }

  /**
   * @brief Returns the total storage capacity of the Deque.
   *
   * The capacity corresponds to the maximum number of elements that the Deque
   * can currently hold without reallocating memory.
   *
   * @return The total capacity of the Deque.
   */
  [[nodiscard]] size_type capacity() { return (m_mob->size() * BlockSize); }

  /**
   * @brief Checks whether the Deque is empty.
   *
   * @return `true` if the Deque is empty, `false` otherwise.
   */
  [[nodiscard]] bool empty() const { return (m_count == 0); }

  /// Deletes unused slots.
  void shrink_to_fit() {
    size_t front_elem_idx = m_front.m_current - (*m_front.m_block)->begin();
    size_t back_elem_idx = m_back.m_current - (*m_back.m_block)->begin();

    block_list_t new_blocks;
    auto front_block_it{ m_front.m_block };
    auto back_block_it{ m_back.m_block };

    for (auto it{ front_block_it }; it <= back_block_it; ++it) {
      if (*it) {
        new_blocks.push_back(*it);
      }
    }

    *m_mob = std::move(new_blocks);

    m_front = iterator(m_mob->begin(), (*m_mob)[0]->begin() + front_elem_idx);
    m_back = iterator(m_mob->begin() + (m_mob->size() - 1), (*m_mob).back()->begin() + back_elem_idx);

    m_mob->shrink_to_fit();
  }

  //================================================== ELEMENT ACCESS:
  /// Returns a reference to the element at specified location `pos`.
  /*! No bounds checking is performed.
   */
  reference operator[](size_type idx) {
    // [1] Calculate the block and position inside the block.
    // Devemos considerar m_front_itr.m_current como valor do deque[0]
    iterator block_index{ m_front + idx };

    return (*block_index.m_current);
  }

  /// Returns a const ref. to the element at specified location pos.
  /*! No bounds checking is performed.
   */
  const_reference operator[](size_type idx) const {
    // [1] Calculate the block and position inside the block.
    iterator block_index{ m_front + idx };

    return (*block_index.m_current);
  }

  /// Returns a reference to the element at specified location `pos`.i
  /*! This method checks the bounds and may throw std::out_of_range,
   * in case the idx is outside the Deque's limits.
   */
  reference at(size_type idx) {
    // [0] Check if the index is within bounds.
    if (idx >= m_count) {
      throw std::out_of_range("Deque::operator[]: index out of range");
    }
    // [1] Calculate the block and position inside the block.
    iterator block_index{ m_front + idx };
    return (*block_index.m_current);
  }

  /// Returns a const ref. to the element at specified location pos.
  /*! This method checks the bounds and may throw std::out_of_range,
   * in case the idx is outside the Deque's limits.
   */
  const_reference at(size_type idx) const {
    // [0] Check if the index is within bounds.
    if (idx >= m_count) {
      throw std::out_of_range("Deque::operator[]: index out of range");
    }
    // [1] Calculate the block and position inside the block.
    iterator block_index{ m_front + idx };
    return (*block_index.m_current);
  }

  reference front() { return *begin(); }

  const_reference front() const { return *cbegin(); }

  reference back() { return *(--end()); }

  const_reference back() const { return *(--cend()); }

  //================================================== MODIFIERS:
  /// Replaces the content of the Deque with 'count' copies f 'value'.
  void assign(size_type count, const_reference value) {
    clear();
    for (size_type i{ 0 }; i < count; ++i) {
      push_back(value);
    }
  }

  /// Replaces the content of the Deque with the values from the initializer_list.
  void assign(const std::initializer_list<T>& il) { assign(il.begin(), il.end()); }

  /// Replaces the content of the Deque with the values from [first,last).
  template<typename InputIt, typename = typename std::iterator_traits<InputIt>::iterator_category>
  void assign(InputIt first, InputIt last) {
    clear();
    auto runner{ first };
    while (runner != last) {
      push_back(*runner);
      ++runner;
    }
  }

  /// Insert `value` at the beginning of the Deque.
  void push_front(const_reference value) { insert_at_front(value); }

  /// Insert `value` at the end of the Deque.
  void push_back(const_reference value) { insert_at_back(value); }

  /// Remove the first element of the Deque.
  void pop_front() {
    if (not empty()) {
      erase(begin());
    }
  }

  /// Remove the last element of the Deque.
  void pop_back() {
    if (not empty()) {
      erase((m_back - 1));
    }
  }

  /// Inserts `value` before `cpos`.
  iterator insert(const_iterator cpos, const_reference value) {
    if (empty()) {
      return insert_at_back(value);
    }

    difference_type index_cpos{ cpos - cbegin() };
    iterator pos{ begin() + index_cpos };

    if (pos == m_front) {
      return insert_at_front(value);
    }

    if (pos == m_back) {
      return insert_at_back(value);
    }

    return insert_at(pos, value);
  }

  /// Inserts `count` copies of `value` before `cpos`.
  iterator insert(const_iterator cpos, size_type count, const T& value) {
    iterator pos{ begin() + (cpos - cbegin()) };
    for (size_type i = 0; i < count; ++i) {
      pos = insert(const_iterator(pos.m_block, pos.m_current), value);
    }
    return pos; //> Retorna o último iterador válido
  }

  /// Inserts elements from an initializer_list before  `cpos`.
  iterator insert(const_iterator cpos, const std::initializer_list<T>& il) {
    iterator pos{ begin() + (cpos - cbegin()) };
    for (const auto& value : il) {
      pos = insert(const_iterator(pos.m_block, pos.m_current), value);
    }
    return pos; //> Retorna o último iterador válido
  }

  /// Inserts elements from range [first, last) before `cpos`.
  template<class InputIt, typename = typename std::iterator_traits<InputIt>::iterator_category>
  iterator insert(const_iterator cpos, InputIt first, InputIt last) {
    iterator pos{ begin() + (cpos - cbegin()) };
    InputIt runner{ first };
    while (runner != last) {
      pos = insert(const_iterator(pos.m_block, pos.m_current), *runner);
      ++runner;
    }
    return pos; //> Retorna o último iterador válido
  }

  /// Removes the element at `pos`.
  iterator erase(iterator pos) {
    if (empty() or pos == m_back) {
      return m_back;
    }

    if (pos == m_front) {
      ++m_front;
      m_count--;
      return m_front;
    }

    const bool front_is_closer = (pos - m_front) < (m_back - pos);

    if (front_is_closer) {
      iterator curr{ pos };
      iterator prev{ pos - 1 };

      while (curr != m_front) {
        *curr = std::move(*prev);
        --curr;
        --prev;
      }

      ++m_front;
      m_count--;
      return pos - 1;
    } else {
      iterator curr{ pos };
      iterator next{ pos + 1 };

      while (next != m_back) {
        *curr = std::move(*next);
        ++curr;
        ++next;
      }

      --m_back;
      m_count--;
      return pos;
    }
  }

  /// Removes the element at `cpos`.
  iterator erase(const_iterator cpos) {
    difference_type index_cpos{ cpos - cbegin() };
    iterator pos{ begin() + index_cpos };
    return erase(pos);
  }

  /// Removes the elements in the range `[first,last)`.
  iterator erase(iterator first, iterator last) {
    if (first == last) return last;
    iterator runner{ first };
    while (runner != last) {
      erase(runner);
      ++runner;
    }
    return runner;
  }

  /// Removes the elements in the range `[first,last)`.
  iterator erase(const_iterator first, const_iterator last) {
    difference_type index_first{ first - cbegin() };
    difference_type index_last{ last - cbegin() };

    iterator it_first{ begin() + index_first };
    iterator it_last{ begin() + index_last };

    return erase(it_first, it_last);
  }

  /// Remove all elements from the Deque.
  void clear() {
    if (empty()) return;
    // [!] Traverse all blocks in m_mob and reset them.
    iterator it{ begin() };
    while (it != end()) {
      // [!] Checks if bloco is allocated (not nullptr).
      *it = value_type();
      ++it;
    }

    //!< Offset to determine the starting block (center of the map).
    size_type offset_mob_start{ m_mob->size() / 2 };
    //!< Offset to determine the starting element within the starting block (center).
    size_type offset_block_start{ BlockSize / 2 };

    // [!] Reset iterators to the middle of the block map.
    m_front = iterator(m_mob->begin() + offset_mob_start, (*m_mob)[offset_mob_start]->begin() + offset_block_start);
    m_back = iterator(m_mob->begin() + offset_mob_start, (*m_mob)[offset_mob_start]->begin() + offset_block_start);

    // [!] Reset element count.
    m_count = 0;
  }

private:
  [[nodiscard]] bool need_expand_before_front() const {
    bool in_mob_start{ m_front.m_block == m_mob->begin() };
    bool in_block_start{ m_front.m_current == (*m_front.m_block)->begin() };
    return in_mob_start and in_block_start;
  }

  [[nodiscard]] bool need_allocate_before_front() const {

    bool in_mob_start{ m_front.m_block == m_mob->begin() };
    bool in_block_start{ m_front.m_current == (*m_front.m_block)->begin() };
    // [!] `not in_mob_start` prevines access before 'mob' begin.
    bool to_allocate{ not in_mob_start and *(std::prev(m_front.m_block)) == nullptr };
    return in_block_start and to_allocate;
  }

  [[nodiscard]] bool need_expand_after_back() const {
    bool in_mob_end{ m_back.m_block == m_mob->end() - 1 };
    bool in_block_end{ m_back.m_current == (*m_back.m_block)->end() - 1 };
    return in_mob_end and in_block_end;
  }

  [[nodiscard]] bool need_allocate_after_back() const {
    bool in_mob_end{ m_back.m_block == m_mob->end() - 1 };
    bool in_block_end{ m_back.m_current == (*m_back.m_block)->end() - 1 };
    // [!] `not in_mob_end` prevines access after 'mob' end.
    bool to_allocate{ not in_mob_end and *(std::next(m_back.m_block)) == nullptr };
    return in_block_end and to_allocate;
  }

  iterator insert_at_front(const_reference value) {
    if (need_expand_before_front()) {
      expand_mob(1);
    }

    if (need_allocate_before_front()) {
      *(std::prev(m_front.m_block)) = std::make_shared<block_t>();
    }

    --m_front;
    *m_front.m_current = value;
    ++m_count;

    return m_front;
  }

  iterator insert_at_back(const_reference value) {
    if (need_expand_after_back()) {
      expand_mob(1);
    }

    if (need_allocate_after_back()) {
      *(std::next(m_back.m_block)) = std::make_shared<block_t>();
    }

    *m_back.m_current = value;
    ++m_back;
    ++m_count;

    return std::prev(m_back);
  }

  iterator insert_at(iterator pos, const_reference value) {
    const bool front_is_closer{ (pos - m_front) < (m_back - pos) };

    if (front_is_closer) {
      if (need_expand_before_front()) {
        difference_type index_cpos{ pos - begin() };
        expand_mob(1);
        pos = begin() + index_cpos;
      }

      if (need_allocate_before_front()) {
        *(m_front.m_block - 1) = std::make_shared<block_t>();
      }

      --m_front;
      iterator it{ m_front };
      while (it != pos) {
        *it = *(it + 1);
        ++it;
      }
    } else {
      if (need_expand_after_back()) {
        difference_type index_cpos{ pos - begin() };
        expand_mob(1);
        pos = begin() + index_cpos;
      }

      if (need_allocate_after_back()) {
        *(m_back.m_block + 1) = std::make_shared<block_t>();
      }

      ++m_back;
      iterator it{ m_back };
      while (it != pos) {
        *it = *(it - 1);
        --it;
      }
    }

    *pos = value;
    ++m_count;

    return pos;
  }

  /// Returns how many unused slots of the MOB we have at the target zone.
  // size_t free_slots(zone_e zone)
  // {
  //     return (zone == zone_e::at_front) ? std::distance(m_mob->begin(),
  //     m_front_itr.block)
  //                                       :
  //                                       std::distance(std::next(m_back_itr.block),
  //                                       m_mob->end());
  // }

  /// Return how many free slots the entire MOB has.
  // size_t free_slots() { return free_slots(zone_e::at_front) +
  // free_slots(zone_e::at_back); }

  /// Expand the Map Of (pointers to) Blocks (aka MOB).
  /*!
   * This method creates a new MOB with length at least equal to the current
   * length, possibly adding the extra slots requested.
   *
   * The new MOB would have the same length in case the number of requested
   * blocks is less than half the number of free slots available.
   * The goal here is to avoid increasing the MOB size unnecessarily.
   *
   * The currently used pointers from the old map are copied to the new map.
   *
   * @param extra_slots Number of slots to add to the new MOB.
   *
   * @note The block pointers are copied to the middle zone of the
   * new map, so that we leave room for occupation both at the front and
   * the back of the new map.
   *
   * @note All iterators to the old map become invalid.
   *
   * @postcondition The front and back iterators point to the new map of
   * blocks.
   */
  void expand_mob(const size_type& extra_slots) {
    //!< Total number of blocks currently used (fully + partially).
    const size_type total_blocks_in_use{ used_blocks() + partially_used_blocks() };
    //!< Current size (number of blocks) of the MOB.
    const size_type old_mob_size{ m_mob->size() };
    //!< Number of completely free blocks in the current MOB.
    const size_type free_blocks{ old_mob_size - total_blocks_in_use };
    //!< Initialize new size with the current size.
    size_type new_size{ old_mob_size };

    /*!
     * Only expand the MOB if the requested extra slots exceed half of the
     * free blocks. This prevents unnecessary over-allocation.
     */
    if (extra_slots > (free_blocks / 2)) {
      /*!
       * Multiply by 2 to allocate extra space both at the beginning and end
       * of the MOB, maintaining balance and avoiding fragmentation.
       */
      new_size = total_blocks_in_use + (2 * extra_slots);
    }

    //!< Create the new MOB vector with `new_size` blocks, all initialized to
    //!< nullptr.
    auto new_mob{ std::make_unique<block_list_t>(new_size, nullptr) };

    // [!] References for clarity:
    //!< Old MOB vector reference.
    auto& old_mob_ref{ *m_mob };
    //!< New MOB vector reference.
    auto& new_mob_ref{ *new_mob };
    //!< Offset to center the used blocks inside the new MOB.
    const size_type offset{ (new_size - total_blocks_in_use) / 2 };

    //!< Indices of the first and last occupied blocks in the old MOB.
    size_type old_front_idx = static_cast<size_type>(m_front.m_block - m_mob->begin());
    size_type old_back_idx = static_cast<size_type>(m_back.m_block - m_mob->begin());

    /*!
     * Copy all occupied blocks from the old MOB to the new MOB,
     * starting at the offset to keep them centered.
     */
    for (size_type i{ old_front_idx }; i <= old_back_idx; ++i) {
      new_mob_ref[offset + (i - old_front_idx)] = old_mob_ref[i];
    }

    //=========================================================================
    /*!
     * Relocate the front and back iterators to the new blocks, preserving
     * their exact position within each block.
     */
    //!< New front block iterator.
    const auto new_front_blk{ new_mob->begin() + offset };
    //!< New back block iterator.
    const auto new_back_blk{ new_front_blk + (old_back_idx - old_front_idx) };

    //!< References to the blocks pointed by the new front and back iterators.
    const auto& new_front_blk_ref{ *new_front_blk };
    const auto& new_back_blk_ref{ *new_back_blk };

    //!< Offsets within their old blocks.
    const auto offset_front{ m_front.m_current - old_mob_ref[old_front_idx]->begin() };
    const auto offset_back{ m_back.m_current - old_mob_ref[old_back_idx]->begin() };

    // [!] Update m_front_itr and m_back_itr to point to the corresponding
    // elements in the new blocks.
    m_front = iterator(new_front_blk, new_front_blk_ref->begin() + offset_front);
    m_back = iterator(new_back_blk, new_back_blk_ref->begin() + offset_back);

    // [!] Replace the old MOB with the new, expanded and balanced MOB.
    m_mob = std::move(new_mob);
  }

  /// Returns the number of occupied 100% blocks in the MOB.
  size_type used_blocks() { return (m_count / BlockSize); }

  /// Returns the number of blocks partially occupied in the MOB.
  size_type partially_used_blocks() { return ((m_count == capacity()) ? 0 : 1); }

  /// Returns how many elements exist in the end block of the target `zone`.
  // [[nodiscard]] size_type block_occupancy_of(zone_e zone) const {}

  /// Clear the Deque of all elements by resetting the control iterators to
  /// middle of the MOB.
  void reset() { }

public:
  [[nodiscard]] std::string to_string() const {
    // return to_string_address();
    // return to_string_full();
    // return to_string_short();
    return std::string();
  }

  [[nodiscard]] std::string to_string_full() const {
    std::ostringstream oss;
    size_t map_slot_idx{ 0 };
    bool show_values{ false };

    // Special case
    if (empty()) {
      oss << "{<empty>}";
      return oss.str();
    }
    // Traverse each of the slots in the map of blocks.
    // for (const auto& sptr_blk : (*m_mob)) {
    for (const typename block_list_t::value_type& sptr_blk : (*m_mob)) {
      oss << "<&block:" << static_cast<const void*>(sptr_blk.get()) << "> ";
      oss << "[" << map_slot_idx++ << "]";
      // Slots in the map that is not in use.
      if (sptr_blk == nullptr) {
        oss << "<null>\n";
        continue;
      }

      oss << "{ ";
      // Traverse each item of the data block.
      for (const typename block_t::value_type& item : (*sptr_blk)) {
        // Start showing values only when we reach the front.
        if (&item == m_front.m_current) {
          show_values = true;
        }
        // Stop showing values when we reach the back.
        if (&item == m_back.m_current) {
          show_values = false;
        }
        if (show_values) {
          oss << item << " ";
        } else {
          oss << (&item == m_back.m_current ? "x " : "- ");
        }
      }
      oss << "} \n";
    }
    auto front_block_idx = std::distance(m_mob->begin(), m_front.m_block);
    auto back_block_idx = std::distance(m_mob->begin(), m_back.m_block);
    oss << "  front blk idx: [" << front_block_idx << "], back blk idx: [" << back_block_idx << "]";
    oss << "\n *front_ptr: " << *m_front.m_current << ", *back_ptr: " << *(m_back - 1).m_current;
    oss << " e size: " << size() << "\n";
    return oss.str();
  }

  [[nodiscard]] std::string to_string_short() const {
    std::ostringstream oss;
    bool show_values{ false };

    // Special case.
    if (empty()) {
      oss << "{<empty>}";
      return oss.str();
    }
    oss << "{ ";
    // Traverse each of the slots in the map of blocks.
    // for (const auto& sptr_blk : (*m_mob)) {
    for (const typename block_list_t::value_type& sptr_blk : (*m_mob)) {
      // Slots in the map that is not in use.
      if (sptr_blk == nullptr) {
        continue;
      }
      // Traverse each item of the data block.
      // for (const auto& item : (*sptr_blk)) {
      for (const typename block_t::value_type& item : (*sptr_blk)) {
        // Turn show numbers on when we reach the front.
        if (&item == m_front.m_current) {
          show_values = true;
        }
        // Turn show number off when we reach the back.
        if (&item == m_back.m_current) {
          show_values = false;
        }
        if (show_values) {
          oss << item << " ";
        } else {
          oss << (&item == m_back.m_current ? "x " : "- ");
        }
      }
    }
    oss << "} ";
    return oss.str();
  }
};

template<typename T>
bool operator==(const Deque<T>& lhs, const Deque<T>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template<typename T>
bool operator!=(const Deque<T>& lhs, const Deque<T>& rhs) {
  return not(lhs == rhs);
}
} // namespace ds

#endif // DEQUE_HPP
