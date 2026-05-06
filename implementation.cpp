#include<iostream>
#include<queue>
using namespace std;

class Node{
  public:
    int data;
    Node* left;
    Node* right;


    Node(int data){
        this -> data = data;
        this -> left = NULL;
        this -> right = NULL;
    }
};

Node* BuildTree(Node* root){
    int data;
    cout<<"enter the data : "<<endl;
    cin>>data;
    root = new Node(data);

    if(data == -1){
        return NULL;
    }
    cout<<"enter the data for leftside of "<<data<<" : ";
    root -> left = BuildTree(root);
    cout<<endl;
    cout<<"enter the data for rightside of "<<data<<" : ";
    root -> right = BuildTree(root);
    return root;
}

void BuildFromLevelorderTravercel(Node* &root){
    queue<Node*> q;
    cout<<"enter the data for root : ";
    int data;
    cin>>data;
    cout<<endl;
    root = new Node(data);

    if(data == -1){
        return;
    }

    q.push(root);

    while(!q.empty()){
        Node* temp = q.front();
        q.pop();

        cout<<" enteer the leftside data for "<<temp->data<<" : ";
        int leftside;
        cin>>leftside;
        cout<<endl;
        
        if(leftside != -1){
            temp -> left = new Node(leftside);
            q.push(temp -> left);
        }
        cout<<" enteer the rightside data for "<<temp->data<< " : ";
        int rightside;
        cin>>rightside;
        cout<<endl;

        if(rightside != -1){
            temp -> right = new Node(rightside);
            q.push(temp -> right);
        }
    }
}

void levelordertravercel(Node* root){
    queue<Node*> q;     //storing nodes
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        
        if(temp == NULL){          //last level completed also the temp child are push inside the queue
            cout<<endl;
            if(!q.empty()){        
                q.push(NULL);
            }
        }else{
            cout<<temp-> data<<" ";
            if(temp -> left){
                q.push(temp -> left);
            }
            if(temp -> right){
                q.push(temp -> right);
            }
        }
    }
}

void inorder(Node* root){
    if(root == NULL){
        return;
    }

        inorder(root -> left);
        cout<<root -> data;
        inorder(root -> right);

}
void preorder(Node* root){
    if(root == NULL){
        return;
    }

    cout<<root -> data;
    preorder(root -> left);
    preorder(root -> right);

}
void postorder(Node* root){
    if(root == NULL){
        return;
    }

    postorder(root -> left);
    postorder(root -> right);
    cout<<root -> data;

}


int main(){

    Node* root = NULL;

    BuildFromLevelorderTravercel(root);
    levelordertravercel(root);

    // root = BuildTree(root);
    // cout<<endl<<endl;
    // cout<<endl<<endl;
    // inorder(root);
    // cout<<endl;
    // postorder(root);
    // cout<<endl;
    // preorder(root);
    // cout<<endl;
    return 0;
}