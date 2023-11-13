#include <iostream>

using namespace std;

class base {
public:
  string public_num = "public";

protected:
  string protected_str = "protected";

private:
  string private_str = "private";
};

class drive : private base {
public:
  explicit drive() {}
  void func() { cout << this->protected_str << endl; }
};

int main(int, char **) { drive{}.func(); }