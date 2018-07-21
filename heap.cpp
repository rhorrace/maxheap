#include "heap.hpp"

using namespace std;

heap::heap():root(NULL) {}
heap::~heap() {
  remove_all(root);
}

int heap::insert(int num) {
  if(!root) {
    root = new node;
    root->data = num;
    root->level = 1;
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;
    return 1;
  }
  node* temp = NULL;
  node* child = new node;
  child->data = num;
  child->parent = NULL;
  child->left = NULL;
  child->right = NULL;
  queue<node*> q;
  q.push(root);
  while(!q.empty()) {
    temp = q.front();
    q.pop();
    if(!temp->left) {
      temp->left = child;
      child->parent = temp;
      break;
    }
    else {
      q.push(temp->left);
    }
    if(!temp->right) {
      temp->right = child;
      child->parent = temp;
      child->level = temp->level+1;
      break;
    }  
    else {
      q.push(temp->right);
    }
  }
  return heapify(child);
}

int heap::heapify(node*& root) {
  if(!root) {
    return 0;
  }
  if(!root->parent) {
    return 1;
  }
  if(root->parent->data < root->data) {
    int temp = root->data;
    root->data = root->parent->data;
    root->parent->data = temp;
    return heapify(root->parent);
  }
}

int heap::display_all() {
  if(!root) {
    return 0;
  }
  int prev = 0;
  node* temp = NULL;
  queue<node*> q;
  q.push(root);
  while(!q.empty()) {
    temp = q.front();
    q.pop();
    cout << temp->data;
    if(temp->level == prev+1) {
      cout << endl;
      prev = temp->level;
    }
    else {
      cout << " ";
    }
    if(temp->left) {
      q.push(temp->left);
    }
    if(temp->right) {
      q.push(temp->right);
    }
  }
  cout << endl;
  return 1;
}

int heap::get_max() {
  return (!root) ? 0:root->data;
}

void heap::display_max() {
  if(!root) {
    cout << "0\n";
  }
  else {
    cout << root->data << endl;
  }
}

int heap::remove_max() {
   if(!root) {
     return 0;
   }
   if(!root->left && !root->right) {
     delete root;
     root = NULL;
   }
   int num = farthest_right();
   root->data = num;
   return heapify_down(root);
}

int heap::farthest_right() {
  node* temp;
  queue<node*> q;
  q.push(root);
  while(!q.empty()) {
    temp = q.front();
    q.pop();
    if(temp->left) {
      q.push(temp->left);
    }
    if(temp->right) {
      q.push(temp->right);
    }
  }
  int num = temp->data;
  if(temp == temp->parent->left) {
    temp->parent->left = NULL;
  }
  else {
    temp->parent->right = NULL;
  }
  temp->parent = NULL;
  delete temp;
  temp = NULL;
  return num;
}

int heap::heapify_down(node*& root) {
  int temp;
  if(!root) {
    return 0;
  }
  if(!root->left && !root->right) {
    return 1;
  }
  else if(root->left && !root->right) {
    if(root->left->data > root->data) {
      temp = root->data;
      root->data = root->left->data;
      root->left->data = temp;
      return heapify_down(root->left);
    }
  }
  else if(!root->left && root->right) {
    if(root->right->data > root->data) {
      temp = root->data;
      root->data = root->right->data;
      root->right->data = temp;
      return heapify_down(root->right);
    }
  }
  else {
    int mx = max(root->left->data, root->right->data);
    if(mx == root->right->data) {
      if(mx > root->data) {
        temp = root->data;
        root->data = root->right->data;
        root->right->data = temp;
        return heapify_down(root->right);
      }
    }
    else {
      if(mx > root->data) {
        temp = root->data;
        root->data = root->left->data;
        root->left->data = temp;
        return heapify_down(root->left);
      }
    }
  }
  return 1;
}

int heap::remove_all() {
  return remove_all(root);
}
int heap::remove_all(node*& root) {
  if(!root) {
    return 0;
  }
  remove_all(root->left);
  remove_all(root->right);
  delete root;
  root = NULL;
  return 1;
}
