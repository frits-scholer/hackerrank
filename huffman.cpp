#include <iostream>
#include <string>
The structure of the node is

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;

void decode_huff(node * root,string s)
{
  auto p = s.begin();
  //set up position at beginning of s
  //set current node to root
  node *cur = root;
  //position at end of string?
  while (p != s.end()) {
  //no? get next char of s
    char c = *p;
  //if 0 set current node to left child else set current node to right child
    if (c=='0') cur = cur->left;
    else cur = cur->right;
    //is current node a leaf node?
    if (cur->data != '\0') {
      //yes? output data  set current node to root
      cout << cur->data;
      cur = root;
    }
  //increase position and go back to step 2
    ++p;
  }
  //yes? stop
}
