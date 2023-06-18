#include <iostream>
#include <stack>
using namespace std;
struct Node
{
    int data;
    Node *left, *right;
};
class BstIterator
{
public:
    stack<Node *> st;
    bool reverse;
    BstIterator(Node *root, bool isrev)
    {
        reverse = isrev;
        pushAll(root);
    }
    void pushAll(Node* root){
        while(root){
            st.push(root);
            if(reverse)root=root->right;
            else root=root->left;
        }
    }
    int next(){
        Node* t=st.top();
        st.pop();
        if(reverse)pushAll(t->left);
        else pushAll(t->right);
    }
    bool hasNext(){
        return !st.empty();
    }
};