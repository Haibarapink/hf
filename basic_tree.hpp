#pragma once

template <typename T> struct node {
  node *left{nullptr};
  node *right{nullptr};
  node *parent{nullptr};
  T t;

  void left_rotate() {}
};
