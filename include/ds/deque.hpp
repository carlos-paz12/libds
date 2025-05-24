#ifndef _DEQUE_HPP_
#define _DEQUE_HPP_

#include <algorithm> // std::copy, std::equal, std::fill
#include <array>
#include <cmath>
#include <cstddef> // std::size_t
#include <cstdint>
#include <initializer_list> // std::initializer_list
#include <iostream>         // std::cout, std::endl
#include <iterator> // std::advance, std::begin(), std::end(), std::ostream_iterator, std::distance|
#include <memory> // std::unique_ptr
#include <sstream>
#include <utility>
#include <vector>

namespace ds {
// Forward declaration. This is necessary so that we can state
// that Deque is a friend of Iterator.
// Inside Deque we need access to the private members of Iterator.
template <typename T, size_t BlockSize = 3, size_t DefaultBlkMapSize = 1>
class Deque;

template <typename T, std::size_t BlockSize, typename BlockItr,
          typename ItemItr>
class Iterator {
public:
  //== Typical iterator aliases
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

private:
  BlockItr m_block;  //!< The block the iterator points to.
  ItemItr m_current; //!< The last location where an insertion happened inside
                     //!< the block.

  // We need to grant this friendship to allow Deque access to the iterator's
  // private attributes.
  friend class Deque<T>;

public:
/// Default constructor.
Iterator() : m_block(), m_current() {}

/// Useful constructor.
Iterator(BlockItr block, ItemItr current)
: m_block(block), m_current(current) {}

  /// Copy constructor.
  Iterator(const Iterator &other)
      : m_block(other.m_block), m_current(other.m_current) {}

  /// Assigment operator.
  Iterator &operator=(const Iterator &other) {
    if (this != &other) {
      m_block = other.m_block;
      m_current = other.m_current;
    }
    return *this;
  }

  /// Dereference operator.
  reference operator*() { return *m_current; }

// Pre-increment operator.
Iterator &operator++() {
    m_current++; // Avança o iterador dentro do bloco atual
    if (m_current == (*m_block)->end()) { // Se chegou ao fim do bloco
      m_block++;                       // Avança para o próximo bloco
      m_current = (*m_block)->begin(); // Posiciona no início do novo bloco
    }
    return *this;
  }
  
  
  /// Post-increment operator.
  Iterator operator++(int) {
    Iterator temp = *this; // salva estado atual
    ++(*this);             // chama o pré-incremento
    return temp;           // retorna o iterador antigo
  }

  /// Pre-decremente operator.
  Iterator &operator--() {
    if (m_current == (*m_block)->begin()) { // Se chegou ao início do bloco
        m_block--;                          // Retrocede para o bloco anterior
        m_current = (*m_block)->end();      // Posição após o último
    }
    m_current--;                            // Agora retrocede para o último elemento válido
    return *this;
   }

  /// Post-decremente operator.
  Iterator operator--(int) { 
    Iterator temp = *this; // salva estado atual
  --(*this);             // chama o Pre-decremente 
    return temp;           // retorna o iterador antigo
  }
  // it = it2 + 3; or it = it2 + (-3)
  Iterator operator+(difference_type n) const { 
    Iterator temp = *this; //salva estado atual
    for (difference_type i = 0; i < n; ++i) {
      ++temp; // Avança o iterador dentro do bloco atual
    }
    return temp; // Retorna o iterador avançado
  }
  // it = 3 + it2; or it = (-3) + it2
  friend Iterator operator+(Iterator::difference_type n,const Iterator &other) {
    Iterator temp = other; //salva estado atual
    for (difference_type i = 0; i < n; ++i) {
      ++temp; // Avança o iterador dentro do bloco atual
    }
    return temp; // Retorna o iterador avançado
    }
    // it = it2 - 3; or it = it2 - (-3)
    Iterator operator-(difference_type n) const { 
      Iterator temp = *this; //salva estado atual
      for (difference_type i = 0; i < n; ++i) {
        --temp; // Retrocede o iterador dentro do bloco atual
      }
      return temp; // Retorna o iterador retrocedido
     }
  // it += 3; or it += -3;
  Iterator operator+=(difference_type n) { return *this; }
  // it -= 3; or it -= -3;
  Iterator operator-=(difference_type n) { return *this; }
  // it = it2 - it3;
  // The *this iterator is usually the farther iterator (down the Deque).
  difference_type operator-(const Iterator &other) const { return 0; }
  bool operator==(const Iterator &other) const { return false; }
  bool operator!=(const Iterator &other) const { return false; }
  bool operator<(const Iterator &other) const { return false; }
  bool operator>(const Iterator &other) const { return false; }
  bool operator<=(const Iterator &other) const { return false; }
  bool operator>=(const Iterator &other) const { return false; }
  
  pointer get_current() const { return m_current; }
  BlockItr get_block() const { return m_block; }

  [[nodiscard]] std::string to_string() const {
    std::ostringstream oss;
    oss << "[&block: " << *m_block << ", &current: " << m_current << "]";
    return oss.str();
  }
};

template <typename T, size_t BlockSize, size_t DefaultBlkMapSize> class Deque {
public:
  //== Typical container aliases
  using size_type = unsigned long; //!< The size type.
  using value_type = T;            //!< The value type.
  using pointer = value_type *; //!< Pointer to a value stored in the container.
  using reference = value_type &;             //!< Reference to a value.
  using const_reference = const value_type &; //!< Const reference to a value.
  using difference_type = ptrdiff_t; //!< Difference type between pointers.

  //== Aliases for the Deque types.
  /// A block is a fixed sized array of T that actually holds the data.
  using block_t = std::array<T, BlockSize>;
  /// Basic smart pointer to a block of data items.
  using block_sptr_t = std::shared_ptr<block_t>;
  /// This type represents a list of smart pointers to blocks of memory.
  using block_list_t = std::vector<block_sptr_t>;
  /// Regular iterator.
  using iterator = Iterator<T, BlockSize, typename block_list_t::iterator,
                            typename block_t::iterator>;
  /// Const iterator.
  using const_iterator =
      Iterator<const T, BlockSize, typename block_list_t::const_iterator,
               typename block_t::const_iterator>;

private:
  //== Management variables.
  std::unique_ptr<block_list_t> m_mob; //!< The dynamic map of blocks.
  iterator m_front_itr;                //!< Iterator to the front block.
  iterator m_back_itr;                 //!< Iterator to the back block.
  size_t m_count{0};                   //!< # of elements stored in the map.

public:
  /// Dtro.
  ~Deque() = default;

  /// Default Ctro.
  Deque() {
    // Sempre alocar 3 blocos (1 no meio com espaço para crescer dos dois lados)
    size_type map_size{DefaultBlkMapSize}; // 2 extras: frente e trás
    // Inicializa o vetor de blocos com ponteiros nulos
    m_mob = std::make_unique<block_list_t>(map_size);

    // Aloca os blocos
    for (size_type i{0}; i < map_size; ++i) {
      (*m_mob)[i] = std::make_shared<block_t>(); // O tamanho do bloco está
                                                 // definido em `block_t`.
    }

    // Posição central onde os dados começarão
    size_type start_block{1};

    // Inicializa iterador para o início (posição lógica 0)
    m_front_itr = iterator(
        m_mob->begin() + start_block, // iterador para o bloco do início
        (*m_mob)[start_block]
            ->begin() // iterador para a posição inicial dentro do bloco
    );

    // Inicializa iterador para o fim
    size_type end_block{start_block + DefaultBlkMapSize};
    size_type offset{DefaultBlkMapSize % BlockSize};

    m_back_itr = iterator(
        m_mob->begin() + end_block, // iterador para o último bloco com dados
        (*m_mob)[end_block]->begin() + offset // posição dentro do bloco
    );
  }

  /*! Construct a Deque and initialize it with `n` copies of `value` of type
   * `T`. If `value` is not provided, a default constructor `T()` is used.
   */
  explicit Deque(size_type n, const_reference value = T()) {
    // Número de blocos necessários para armazenar n elementos
    size_type blocks_needed{
        static_cast<size_type>(std::ceil((n + BlockSize - 1) / BlockSize))};

    // Sempre alocar 3 blocos (1 no meio com espaço para crescer dos dois lados)
    size_type map_size{blocks_needed + 2}; // 2 extras: frente e trás
    // Inicializa o vetor de blocos com ponteiros nulos
    m_mob = std::make_unique<block_list_t>(map_size);
    // Aloca os blocos
    for (size_type i{0}; i < map_size; ++i) {
      (*m_mob)[i] = std::make_shared<block_t>(); // O tamanho do bloco está
                                                 // definido em `block_t`.
    }
    // Posição central onde os dados começarão
    size_type start_block{1};
    // Inicializa iterador para o in ício (posição lógica 0)
    m_front_itr = iterator(
        m_mob->begin() + start_block, // iterador para o bloco do início
        (*m_mob)[start_block]
            ->begin() // iterador para a posição inicial dentro do bloco
    );
    // Inicializa iterador para o fim
    size_type end_block{start_block + (blocks_needed ? blocks_needed - 1 : 0)};
    size_type offset{
        (n == 0) ? n
                 : (n - 1) % BlockSize}; /// @todo para que serve o `offset`.

    m_back_itr = iterator(
        m_mob->begin() + end_block, // iterador para o último bloco com dados
        (*m_mob)[end_block]->begin() + offset // posição dentro do bloco
    );

    // Preenche os elementos com 'value'
    iterator it{m_front_itr};
    for (size_type i = 0; i < n; ++i) {
      *(it) = value * i; // remover o * i depois...
      ++it;
    }

    // Atualiza a contagem
    m_count = n;
  }

  /// Ctro. from a range.
  // template <class InputIt>
  template <typename InputIt, typename = typename std::iterator_traits<
                                  InputIt>::iterator_category>
  Deque(InputIt first, InputIt last) {}

  /// Copy Ctro.
  Deque(const Deque &other) {}

  /// Initializer list Ctro.
  Deque(const std::initializer_list<T> &il) {}

  Deque &operator=(const Deque &other) {}

  /// Return the number of elements in the Deque.
  [[nodiscard]] size_type size() const { return m_count; }

  /// Return `true` if the Deque has no elements, `false` otherwise.
  [[nodiscard]] bool empty() const { return m_count == 0; }

  /// Remove all elements from the Deque.
  void clear() {}

  /// Insert `value` at the beginning of the Deque.
  void push_front(const_reference value) { insert(cbegin(), value); }

  /// Insert `value` at the end of the Deque.
  void push_back(const_reference value) { insert(cend(), value); }

  /// Remove the first element of the Deque.
  void pop_front() {}

  /// Remove the last element of the Deque.
  void pop_back() {}

  reference front() { return *begin(); }
  const_reference front() const { return *cbegin(); }
  reference back() { return *(--end()); }
  const_reference back() const { return *(--cend()); }

  /// Replaces the content of the Deque with 'count' copies f 'value'.
  void assign(size_type count, const T &value) {}

  /// Returns a reference to the element at specified location `pos`.
  /*! No bounds checking is performed.
   */
  reference operator[](size_type idx) {}

  /// Returns a const ref. to the element at specified location pos.
  /*! No bounds checking is performed.
   */
  const_reference operator[](size_type idx) const {}

  /// Returns a reference to the element at specified location `pos`.i
  /*! This method checks the bounds and may throw std::out_of_range,
   * in case the idx is outside the Deque's limits.
   */
  reference at(size_type idx) {}

  /// Returns a const ref. to the element at specified location pos.
  /*! This method checks the bounds and may throw std::out_of_range,
   * in case the idx is outside the Deque's limits.
   */
  const_reference at(size_type idx) const {}

  /// Returns the storage capacity of the Deque.
  size_t capacity() { return m_mob->size() * BlockSize; }

  /// Change the number of elements stored in the container.
  /*!
   * If the current size ( size() ) is greater than `count` , the container is
   * reduced to the first count element. On the other hand, if the current size
   * is less than count , then additional default-inserted elements are appended
   * to the container.
   *
   * Lastly, if current size is equal to count, nothing happens.
   */
  void resize(size_type count) {}

  /// Deletes unused slots.
  void shrink_to_fit() {}

  /// Return an iterator to the Deque's first element.
 iterator begin() { return iterator(m_front_itr); }

  /// Return an iterator to a location following the Deque's last element.
  iterator end()   { return iterator(m_back_itr); }
  /// Return a const iterator to the Deque's first element.
  const_iterator cbegin() const {}

  /// Return a const iterator to a location following the Deque's last element.
  const_iterator cend() const {}

  /// Inserts `value` before `cpos`.
  iterator insert(const_iterator cpos, const T &value) {}

  /// Inserts `count` copies of `value` before `cpos`.
  iterator insert(const_iterator cpos, size_type count, const T &value) {}

  /// Inserts elements from an initializer_list before  `cpos`.
  iterator insert(const_iterator cpos, const std::initializer_list<T> &il) {}

  /// Inserts elements from range [first, last) before `cpos`.
  template <class InputIt>
  iterator insert(const_iterator cpos, InputIt first, InputIt last) {}

  /// Removes the elements in the range `[first,last)`.
  iterator erase(iterator first, iterator last) {}

  /// Removes the elements in the range `[first,last)`.
  iterator erase(const_iterator first, const_iterator last) {}

  /// Removes the element at `pos`.
  iterator erase(const_iterator cpos) {}
  /// Removes the element at `pos`.
  iterator erase(iterator pos) {}

  /// Replaces the content of the Deque with the values from [first,last).
  template <typename InputIt> void assign(InputIt first, InputIt last) {}

  /// Replaces the content of the Deque with the values from the
  /// initializer_list.
  void assign(const std::initializer_list<T> &il) {}

private:
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
   * @postcondition The front and back iterators point to the new map of blocks.
   */
  void expand_mob(size_type extra_slots) {
    // [0] Conservative MOB growth.
    auto new_mob_size = used_blocks() + (2 * extra_slots);
    // [0] Aggressive MOB growth.
    // auto new_mob_size = 2 * m_mob->size() + extra_slots;
    // =================================================================
    // [1] Allocate the new expanded memory for the map.
    // =================================================================

    // =================================================================
    // [2] Copy data from old memory to the new one.
    // =================================================================

    // =================================================================
    // [3] Update pointers to the new memory.
    // =================================================================
  }

  /// Returns the number of occupied blocks in the m.o.b.
  size_type used_blocks() { return 0; }

  /// Returns how many elements exist in the end block of the target `zone`.
  // [[nodiscard]] size_type block_occupancy_of(zone_e zone) const {}

  /// Clear the Deque of all elements by resetting the control iterators to
  /// middle of the MOB.
  void reset() {}

public:
  [[nodiscard]] std::string to_string() const {
    // return to_string_address();
    // return to_string_full();
    // return to_string_short();
    return std::string();
  }

  [[nodiscard]] std::string to_string_full() const {
    std::ostringstream oss;
    size_t map_slot_idx{0};
    bool show_values{false};

    // Special case
    if (empty()) {
      oss << "{<empty>}";
      return oss.str();
    }
    // Traverse each of the slots in the map of blocks.
    // for (const auto& sptr_blk : (*m_mob)) {
    for (const typename block_list_t::value_type &sptr_blk : (*m_mob)) {
      oss << "<&block:" << static_cast<const void*>(sptr_blk.get()) << "> ";
      oss << "[" << map_slot_idx++ << "]";
      // Slots in the map that is not in use.
      if (sptr_blk == nullptr) {
        oss << "<null> ";
        continue;
      }
      
      oss << "{ ";
      // Traverse each item of the data block.
      for (const typename block_t::value_type &item : (*sptr_blk)) {
        // Start showing values only when we reach the front.
        if (&item == m_front_itr.get_current()) {
          show_values = true;
        }
        // Stop showing values when we reach the back.
        if (&item == m_back_itr.get_current()) {
          show_values = false;
        }
        if (show_values) {
          oss << item << " ";
        } else {
          oss << (&item == m_back_itr.get_current() ? "x " : "- ");
        }
      }
      oss << "} \n";
    }
    auto front_block_idx = std::distance(m_mob->begin(), m_front_itr.get_block());
    auto back_block_idx = std::distance(m_mob->begin(), m_back_itr.get_block());
    oss << "  front blk idx: [" << front_block_idx << "], back blk idx: ["
        << back_block_idx << "]";
    auto last = std::prev(m_back_itr);
    oss << "\n *front_ptr: " << *m_front_itr.get_current()
        << ", *back_ptr: " << *last.get_current();
    oss << " e size: " << size() <<"\n";
    return oss.str();
  }

  [[nodiscard]] std::string to_string_short() const {
    std::ostringstream oss;
    bool show_values{false};

    // Special case.
    if (empty()) {
      oss << "{<empty>}";
      return oss.str();
    }
    oss << "{ ";
    // Traverse each of the slots in the map of blocks.
    // for (const auto& sptr_blk : (*m_mob)) {
    for (const typename block_list_t::value_type &sptr_blk : (*m_mob)) {
      // Slots in the map that is not in use.
      if (sptr_blk == nullptr) {
        continue;
      }
      // Traverse each item of the data block.
      // for (const auto& item : (*sptr_blk)) {
      for (const typename block_t::value_type &item : (*sptr_blk)) {
        // Turn show numbers on when we reach the front.
        if (&item == m_front_itr.current) {
          show_values = true;
        }
        // Turn show number off when we reach the back.
        if (&item == m_back_itr.current) {
          show_values = false;
        }
        if (show_values) {
          oss << item << " ";
        } else {
          oss << (&item == m_back_itr.current ? "x " : "- ");
        }
      }
    }
    oss << "} ";
    return oss.str();
  }
};

template <typename T>
bool operator==(const Deque<T> &lhs, const Deque<T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <typename T>
bool operator!=(const Deque<T> &lhs, const Deque<T> &rhs) {
  return not(lhs == rhs);
}
} // namespace ds

#endif //!< _DEQUE_HPP_
