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
Node* insertNode(Node*, std::vector<std::string>&);


int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout << "No File provided" << std::endl;
        exit(1);
    }

    std::vector<std::string> list;
    Node *root = nullptr;

    readFile(list, argv[1]);
    insertNode(root, list);
    
    
    return 0;
}

Node* insertNode(Node *root, std::vector<std::string> &list){
    if(root == nullptr){
        root = new Node;
        return root;
    }
    else{
        if(stoi(list.at(1)) < root->value){
            root->left =  insertNode(root, list);
        }
        else{
            root->right = insertNode(root, list);
        }
    }
    return root;
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