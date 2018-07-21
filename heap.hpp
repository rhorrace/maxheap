#include <iostream>
#include <queue>
#include <cmath>

struct node {
  int data;
  int level;
  node* parent;
  node* left;
  node* right;
};

class heap {
public:
  heap();
  ~heap();
  int insert(int num);
  int display_all();
  int get_max();
  void display_max();
  int remove_max();
  int remove_all();
private:
  int heapify(node*& root);
  int farthest_right();
  int heapify_down(node*& root);
  int remove_all(node*& root);
  node* root;
};
