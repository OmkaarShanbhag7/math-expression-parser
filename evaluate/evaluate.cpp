#include <bits/stdc++.h>
using namespace std;


int evaluate(TreeNode* node){

  if(node == nullptr) return 0;

  if(node->data >= '0' && node->data <= '9'){
    return node->data - '0';
  }

  int leftVal = evaluate(node->left.get());
  int rightVal = evaluate(node->right.get());


  if(node->data == '+') return leftVal + rightVal;
  if(node->data == '-') return leftVal - rightVal;
  if(node->data == '*') return leftVal * rightVal;
  if(node->data == '/') return leftVal / rightVal;

  return 0;
}