#include<iostream>
#include<stack>
#include<cstring>
using namespace std;

class Node{
    public:
    char data;
    Node* left;
    Node* right;
    Node(char data){
        this-> data = data;
        this-> right = NULL;
        this->left = NULL;
    }
};

class ExpressionTree{
    public:

        stack<Node*> s;
        Node *root, *t1, *t2;

    bool isOprator(char token){
        return (token == '+' || token == '-' || token == '/' || token == '*');
    }
    Node* ExpTreeBuild(string exp){
        for(int i = exp.length()-1; i >= 0; i--){
            if(isOprator(exp[i])){
                root = new Node(exp[i]);
                t1 = s.top(); s.pop(); 
                t2 = s.top(); s.pop();

                root -> left = t1;
                root -> right = t2;

                s.push(root);
            }else{
                root = new Node(exp[i]);
                s.push(root);
            }
        }
        root = s.top();
        s.pop();
        return root;
    }

    void inorder(Node* root){
        if(root == NULL)return;

        inorder(root -> left);
        cout<< root -> data <<"  ";

        inorder(root -> right);
    }

    void nonRecursive(){
        stack<Node*> s1,s2;

        s1.push(root);
        Node* temp;
        while(!s1.empty()){
            
            temp = s1.top();
            s1.pop();
            s2.push(temp);

            if(temp -> left != NULL){
                s1.push(temp -> left);
            }
            if(temp -> right != NULL){
                s1.push(temp -> right);
            }
        }

        while(!s2.empty()){
            temp = s2.top();
            s2.pop();
            cout<<temp->data<<"  ";
        }
        cout<<endl;        
    }
};

int main(){
    ExpressionTree e;
    string exp = "+*abc";
    Node* root = e.ExpTreeBuild(exp);
    e.inorder(root);
    e.nonRecursive();

    return 0;
}