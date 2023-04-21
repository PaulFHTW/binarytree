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
void printValues(Node *root);
Node* findMin(Node*);
Node* findMax(Node*);
float findAvg(Node*, float&, std::vector<std::string>&);
int height(Node*);

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout << "No File provided" << std::endl;
        exit(1);
    }

    std::vector<std::string> list;
    Node *root = nullptr;
    Node *min = 0;
    Node *max = 0;
    float average = 0;

    readFile(list, argv[1]);
    
    for(int i = 0; i < list.size(); i++){
        root = insertNode(root, stoi(list.at(i)));
    }

    height(root);
    min = findMin(root);
    std::cout << "min: " << min->value << ", ";
    max = findMax(root);
    std::cout << "max: " << max->value << ", ";
    average = findAvg(root, average, list);
    std::cout << " avg: " << average << std::endl;

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

int height(Node* root){
    if (root == nullptr) {
        return 0;
    } else {
        int rightHeight = height(root->right);
        int leftHeight = height(root->left);
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

bool isBalanced(Node* root){
    if(root == nullptr){
        return true;
    } 
    else{
        int balanceFactor = height(root->left) - height(root->right);
        if(balanceFactor < -1 || balanceFactor > 1) {
            return false;
        }
        else{
            return isBalanced(root->left) && isBalanced(root->right);
        }
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

void printValues(Node *root){
    if(root != nullptr){
        printValues(root->left);
        std::cout << root->value << std::endl;
        printValues(root->right);
    }
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