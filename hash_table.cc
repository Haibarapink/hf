#include <cassert>
#include <functional>
#include <hash_map>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>


using namespace std;

// 线性探测
template <size_t hash_table_len, typename T> class HashTable {
public:
  constexpr size_t hash_table_capacity() const { return hash_table_len; }
  bool existed(const T &t) {
    size_t p = std::hash<T>{}(t) % hash_table_capacity();
    auto &slot = hash_table[p];
    if (!slot)
      return false;
    if (slot == t)
      return true;

    for (auto i = p + 1; i != p;) {
      if (hash_table[i] == t)
        return true;
      i = (i + 1) % hash_table_capacity();
    }

    return false;
  }

  bool insert(const T &t) {
    size_t p = std::hash<T>{}(t) % hash_table_capacity();
    auto &slot = hash_table[p];
    if (!slot) {
      slot = t;
      return true;
    }

    auto free_space = free_space_from(p);
    if (!free_space) {
      return false;
    }
    p = *free_space;
    hash_table[p] = t;
    return true;
  }

private:
  std::optional<size_t> free_space_from(size_t p) const {
    if (p >= hash_table_capacity()) {
      throw std::runtime_error{"assertion"};
    }

    for (auto i = p; i != p;) {
      if (!hash_table[i])
        return i;
      i = (i + 1) % hash_table_capacity();
    }

    if (!hash_table[p])
      return p;
    return std::nullopt;
  }
  std::array<std::optional<T>, hash_table_len> hash_table;
};

void test_hash_table() {
  HashTable<10, int> hash_table;
  hash_table.insert(1);
  hash_table.insert(2);
  hash_table.insert(3);
  hash_table.insert(4);
  hash_table.insert(5);
  hash_table.insert(6);
  hash_table.insert(7);
  hash_table.insert(8);
  hash_table.insert(9);
  hash_table.insert(10);
  hash_table.insert(11);
  hash_table.insert(12);
  hash_table.insert(13);
  hash_table.insert(14);
  hash_table.insert(15);
  hash_table.insert(16);
  hash_table.insert(17);
  hash_table.insert(18);
  hash_table.insert(19);
  hash_table.insert(20);
  hash_table.insert(21);
  hash_table.insert(22);
  hash_table.insert(23);
  hash_table.insert(24);
  hash_table.insert(25);
  hash_table.insert(26);
  hash_table.insert(27);
  hash_table.insert(28);
  hash_table.insert(29);
  hash_table.insert(30);
  hash_table.insert(31);
  hash_table.insert(32);
  hash_table.insert(33);
  hash_table.insert(34);
  hash_table.insert(35);
  hash_table.insert(36);
  hash_table.insert(37);
  hash_table.insert(38);
  hash_table.insert(39);
  hash_table.insert(40);
  hash_table.insert(41);
  hash_table.insert(42);
  hash_table.insert(43);
  hash_table.insert(44);
  hash_table.insert(45);
  hash_table.insert(46);
  hash_table.insert(47);
  hash_table.insert(48);
  hash_table.insert(49);
  hash_table.insert(50);
  hash_table.insert(51);
  hash_table.insert(52);
  hash_table.insert(53);
  hash_table.insert(54);
  hash_table.insert(55);
  hash_table.insert(56);
  hash_table.insert(57);
  hash_table.insert(58);
  hash_table.insert(59);
  hash_table.insert(60);
  hash_table.insert(61);
  hash_table.insert(62);
  hash_table.insert(63);
  hash_table.insert(64);
  hash_table.insert(65);
  hash_table.insert(66);
  hash_table.insert(67);
  hash_table.insert(68);
  hash_table.insert(69);

  assert(hash_table.existed(1));
  assert(!hash_table.existed(100));
}

int main(int, char **) { test_hash_table(); }