#include<iostream>
using namespace std;
#include<cstring>
#include<stack>

class node{
    public:
    string word;
    string meaning;
    node* left;
    node* right;

    node(string word, string meaning){
        this -> word = word;
        this -> meaning = meaning;
        this -> left = NULL;
        this -> right = NULL;
    }
};

class BST{
    public: 
    node* root;
    // stack<node*>s;
    BST(){
        root = NULL;
    }

    void addNode(string word, string meaning){
        node* newNode = new node(word, meaning);
        
        if(root == NULL){
            root = newNode;
            return;
        }

        node* temp = root;
        node* parent = NULL;

        while(temp != NULL){
            parent = temp;

                if(temp -> word == word){
                    cout<<"the "<<word<<" is duplicated !!! "<<endl;
                    delete newNode;
                    return;
                }
                else if(temp -> word > word){
                    temp = temp -> left;
                }else{
                    temp = temp -> right;
                }
            }
            if(parent -> word > word){
                parent -> left = newNode;
            }else{
                parent -> right = newNode;
            }
    }

    void inorder(node* root){
        if(root == NULL){
            return;
        }
        inorder(root -> left);
        cout<<"word : "<<root->word<< "| meaning : " <<root->meaning<<"  ";
        inorder(root-> right); 
    }

    // void INORDERBST(node* root){
    //     if(root == NULL){
    //         return;
    //     }
    //     INORDERBST(root -> left);
    //     s.push(root);
    //     INORDERBST(root -> right);
    // }
    void update(string word){
        
        if(root == NULL){
            cout<<"\nthe dict is Empty"<<endl;
            return;
        }
        node* temp = root;
        
        while(temp != NULL){
            if(temp -> word == word){
                cout<<"word is found"<<endl;
                cout<<"enter the new meaning for "<<temp -> word<<" :: ";
                cin>>temp -> meaning; 
                return;

            }else if(temp -> word > word){
                temp = temp -> left;
            }else{
                temp = temp -> right;
            }
        }
        cout<<word<<" not found !!!"<<endl;
        return;
    }

    void search(string word){

        if(root == NULL){
            cout<<"dict is empty !!! "<<endl;
            return;
        }
        node* temp = root;

        while(temp != NULL){
            if(temp -> word == word){
                cout<<word<<" found with meaning "<<temp->meaning;
                return;
            }else if(temp -> word > word){
                temp = temp -> left;
            }else{
                temp = temp -> right;
            }
        }
        cout<<word<<"  NOT found in this dict!!!! "<<endl;
        return;
    }

    void BstAscOrder(node* root){
        if(root == NULL){
            return;
        }
        BstAscOrder(root -> left);
        cout<<root -> word <<" | "<<root->meaning<<"  ";
        BstAscOrder(root -> right);
        
        
    }
    void BstDscOrder(node* root){
            if(root == NULL){
                return;
            }
            BstDscOrder(root -> right);
            cout<<root -> word<<" | "<<root ->meaning<<"  ";
            BstDscOrder(root -> left);
    }

    node* successor(node* root){
        if(root->left != NULL) root = root -> left;
        return root;
    }
    node* deleteNode(node* root, string word){

        if(root == NULL)return root;

        if(word < root -> word){
            root -> left = deleteNode(root -> left, word); 
        }else if(word > root -> word){
            root -> right = deleteNode(root -> right, word);
        }else{
            //if 1 or 0 child haaving
            if(root -> left == NULL){
                node* temp = root -> right;
                delete root;
                return temp;
            }else if(root -> right == NULL){
                node* temp = root -> left;
                delete root;
                return temp;
            }
            //if both child having
            node* temp = successor(root -> right);
    
            root -> word = temp -> word;
            root -> meaning = temp -> meaning;
    
            root -> right = deleteNode(root -> right, temp -> word);
        }
        return root;
    }
};

int main(){

    BST e;

    e.addNode("apple", "fruit");
    e.addNode("baby", "human");
    e.addNode("lion", "animal");

    e.inorder(e.root);
    
    e.update("baby");
    e.search("apple");
    e.inorder(e.root);

    cout<<endl;
    
    e.BstAscOrder(e.root);
    cout<<endl;
    cout<<endl;
    e.BstDscOrder(e.root);

    e.root = e.deleteNode(e.root, "apple");

    e.inorder(e.root);

    return 0;
}