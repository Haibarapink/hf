#include <iostream>
#include <vector>


template <typename T> class MinHeap {
public:
  MinHeap() : size_(0) {}

  void push(const T &value) {
    data_.push_back(value);
    size_++;
    swim(size_);
  }

  T pop() {
    T value = data_[0];
    data_[0] = data_[size_ - 1];
    data_.pop_back();
    size_--;
    sink(1);
    return value;
  }

  bool empty() const { return size_ == 0; }

private:
  std::vector<T> data_;
  int size_;

  void swim(int cur) {
    while (cur > 1 && data_[cur - 1] < data_[cur / 2 - 1]) {
      std::swap(data_[cur - 1], data_[cur / 2 - 1]);
      cur /= 2;
    }
  }

  void sink(int cur) {
    while (cur * 2 <= size_) {
      int child = cur * 2;
      if (child < size_ && data_[child - 1] > data_[child]) {
        child++;
      }
      if (data_[cur - 1] <= data_[child - 1]) {
        break;
      }
      std::swap(data_[cur - 1], data_[child - 1]);
      cur = child;
    }
  }
};