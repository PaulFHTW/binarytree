#include <iostream>
#include <fstream>
#include <vector>
#include <string> 

struct Node{
    int value;
    struct Node* left;
    struct Node* right;
    bool isAVL = true;
};

void readFile(std::vector<std::string>&, std::string);
Node* insertNode(Node*, int);
Node* findMin(Node*);
Node* findMax(Node*);
float findAvg(Node*, float&, std::vector<std::string>&);
int findHeight(Node*);
void printStats(Node*, std::vector<std::string>&);
Node* searchBinaryTree(Node*, int);
void deleteTree(Node*);

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout << "No File provided" << std::endl;
        exit(1);
    }

    std::vector<std::string> list;
    std::vector<std::string> sublist;
    Node *root = nullptr;

    readFile(list, argv[1]);

    for(int i = 0; i < list.size(); i++){
        root = insertNode(root, stoi(list.at(i)));
    }

    if(argc == 3){
        int counter = 0;
        Node *temp = nullptr;
        readFile(sublist, argv[2]);
        for(int j = 0; j < sublist.size(); j++){
           temp = searchBinaryTree(root, stoi(sublist.at(j)));
           if(temp == nullptr && sublist.size() == 1){
                std::cout << sublist.at(j) << " not found!" << std::endl;
                break;
           }
           else if(temp == nullptr && sublist.size() > 1){
                std::cout << "Subtree not found!" << std::endl;
                break;
           }
           else if(temp->value == stoi(sublist.at(j))){
                counter++;
           }
           else{
                std::cout << "Something went wrong" << std::endl;
                exit(1);
           }
        }
        
        if(counter == sublist.size()){
            if(sublist.size() == 1){
                std::cout << temp->value << " found!" << std::endl;
            }
            else{
                std::cout << "Subtree found!" << std::endl;
            }
        }
    }
    
    printStats(root, list);

    deleteTree(root);

    return 0;
}

Node* searchBinaryTree(Node* root, int value){
    if (root == nullptr || root->value == value) {
        return root;
    }
    else if (value < root->value) {
        return searchBinaryTree(root->left, value);
    }
    else{
        return searchBinaryTree(root->right, value);
    }
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

int findHeight(Node* root){
    if (root == nullptr) {
        return 0;
    } else {
        int rightHeight = findHeight(root->right);
        int leftHeight = findHeight(root->left);
        std::cout << "bal (" << root->value << ") = " << rightHeight - leftHeight;

        if(abs(rightHeight - leftHeight) > 1){
            root->isAVL = false;
            std::cout << " (AVL Violation!)" << std::endl;
        }
        else{
            std::cout << std::endl;
        }

        return std::max(leftHeight, rightHeight) + 1;
    }
}

Node* findMin(Node* root){
    if(root == nullptr)
        return nullptr;
    else if(root->left == nullptr)
        return root;
    else
        return findMin(root->left);
}

Node* findMax(Node* root){
    if(root == nullptr)
        return nullptr;
    else if(root->right == nullptr)
        return root;
    else
        return findMax(root->right);
}

float findAvg(Node *root, float &sum, std::vector<std::string>&list){
    if(root != nullptr){
        findAvg(root->left, sum, list);
        sum += root->value;
        findAvg(root->right, sum, list);
    }
    return sum/list.size();
}

void printStats(Node* root, std::vector<std::string> &list){
    Node *min = 0;
    Node *max = 0;
    float average = 0;

    findHeight(root);
    min = findMin(root);
    std::cout << "min: " << min->value << ", ";
    max = findMax(root);
    std::cout << "max: " << max->value << ", ";
    average = findAvg(root, average, list);
    std::cout << " avg: " << average << std::endl;
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

void deleteTree(Node *root){
    if(root != nullptr){
        deleteTree(root->left);
        deleteTree(root->right);
        delete(root);
    }
}