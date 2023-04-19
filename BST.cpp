#include <iostream>
#include <fstream>
#include <vector>
#include <string> 

struct Node{
    int value;
    struct Node* left;
    struct Node* right;
};

void readFile(std::vector<std::string>&, std::string);
Node* insertNode(Node*, int);
void printTree(Node *root);

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout << "No File provided" << std::endl;
        exit(1);
    }

    std::vector<std::string> list;
    Node *root = nullptr;
    int index = 0;

    readFile(list, argv[1]);
    
    for(int i = 0; i < list.size(); i++){
        root = insertNode(root, stoi(list.at(i)));
    }
    
    printTree(root);
    return 0;
}

Node* insertNode(Node *root, int value){
    if(root == nullptr){
        root = new Node;
        root->value = value;
        root->left = nullptr;
        root->right = nullptr;
    }
    else{
        if(value < root->value){
            root->left =  insertNode(root->left, value);
        }
        else{
            root->right = insertNode(root->right, value);
        }
    }
    return root;
}

void printTree(Node *root){
    std::cout << "Print Tree" << std::endl;

    Node *temp = root;
    while(temp->left != nullptr){
        std::cout << temp->value;
        std::cout << " left ";
        temp = temp->left;
    }
    while(temp->right != nullptr){
        std::cout << temp->value;
        std::cout << " right ";
        temp = temp->right;
    }
    std::cout << temp->value;
    std::cout << std::endl;
}

void readFile(std::vector<std::string> &list, std::string filepath){
    std::ifstream file(filepath);

    if(file.is_open()){
        std::string number;
        while(file.good()){
            std::getline(file, number, '\n');
            list.insert(list.end(), number);
        }
    }
    else{
        std::cout << "Error opening File" << std::endl;
    }

    file.close();
}