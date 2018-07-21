#include "heap.hpp"

using namespace std;

int main() {
  heap test;
  int n = 10;
  for(int i = 1;i <= n;++i) {
    test.insert(i);
    test.display_all();
    cout << endl;
  }
  test.remove_max();
  test.display_all();
  return 0;
}
