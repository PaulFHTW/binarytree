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
void printValues(Node *root);
Node* findMin(Node*, int&);
Node* findMax(Node*, int&);
float findAvg(Node*, float&, std::vector<std::string>&);

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout << "No File provided" << std::endl;
        exit(1);
    }

    std::vector<std::string> list;
    Node *root = nullptr;
    int leftHeight = 0;
    int rightHeight = 0;
    float average = 0;

    readFile(list, argv[1]);
    
    for(int i = 0; i < list.size(); i++){
        root = insertNode(root, stoi(list.at(i)));
    }

    average = findAvg(root, average, list);
    std::cout << average << std::endl;
    /*
    Node *temp = root;
    Node *left = findMin(root, leftHeight);
    Node *right = findMax(root, rightHeight);
    int balance = rightHeight - leftHeight;
    std::cout << balance << std::endl; 
    */
    //printValues(root);
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

Node* findMin(Node* root, int &leftHeight){
    if(root == nullptr)
        return nullptr;
    else if(root->left == nullptr)
        return root;
    else
        leftHeight++;
        return findMin(root->left, leftHeight);
}

Node* findMax(Node* root, int &rightHeight){
    if(root == nullptr)
        return nullptr;
    else if(root->right == nullptr)
        return root;
    else
        rightHeight++;
        return findMax(root->right, rightHeight);
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