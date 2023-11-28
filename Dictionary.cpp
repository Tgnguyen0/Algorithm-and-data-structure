/*
 * Tên: Nguyễn Nhật Tấn
 * Mã sinh viên: 22695891
 * Email: nguyennhattan223344@gmail.com
 * Ngay thuc hien: 15/9/2023
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct Node {
    string key;
    string meaning;
    string type;
    vector<string> examples;
    int height;
    Node* left;
    Node* right;

    Node(string k, string m, string t) : key(k), meaning(m), type(t), height(1), left(nullptr), right(nullptr) {}
};

void freeMemory(Node* root);
void inputExamples(vector<string>& examples);
int getHeight(Node* node);
int getBalance(Node* node);
Node* minValueNode(Node* node);
Node* search(Node* root, string key);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
Node* deleteNode(Node* root, string key);
void editWord(Node* root);
void searchByPrefixHelper(Node* root, string prefix);
void searchByPrefix(Node* root);
void inOrder(Node* root);
void saveToFile(Node* root, ofstream& outFile);
Node* loadFromFile(Node* root, ifstream& inFile);
int countWords(Node* root);
int treeHeight(Node* root);
void getNodesInOrder(Node* root, vector<Node*>& nodes);
Node* getRandomNode(Node* root);
void quiz(Node* root);
void inputType(string& type);
void inputExamples(vector<string>& examples);
void displayMenu();
void addWordHelper(Node*& root);
void searchWordHelper(Node* root);
void deleteWordHelper(Node*& root);
void displayDictionaryHelper(Node* root);
void editWordHelper(Node* root);
void searchByPrefixHelper(Node* root);
void performQuizHelper(Node* root);
void displayDictionaryInfoHelper(Node* root);
void saveAndExitHelper(Node* root);
void freeMemory(Node* root);

int main() {
    Node* root = nullptr; // nut goc cua cay tu dien
    ifstream inFile("C:/Users/DELL/Desktop/Dictionary.txt"); // nhan du lieu tu file dictionary
    if (inFile.is_open()) {
        root = loadFromFile(root, inFile);
        inFile.close();
        cout << "Dictionary loaded from 'Dictionary.txt'.\n";
    } else {
        cout << "No existing dictionary file found. Starting with an empty dictionary.\n";
    }

    int choice;
    do {
        cout << "________  .__        __  .__                                   \n";
        cout << "\\______ \\ |__| _____/  |_|__| ____   ____ _____ _______ ___.__.\n";
        cout << " |    |  \\|  |/ ___\\   __\\  |/  _ \\ /    \\\\__  \\\\_  __ <   |  |\n";
        cout << " |    `   \\  \\  \\___|  | |  (  <_> )   |  \\/ __ \\|  | \\/\\___  |\n";
        cout << "/_______  /__|\\___  >__| |__|\\____/|___|  (____  /__|   / ____|\n";
        cout << "        \\/        \\/                    \\/     \\/       \\/     \n";

        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addWordHelper(root);
                break;
            case 2:
                searchWordHelper(root);
                break;
            case 3:
                deleteWordHelper(root);
                break;
            case 4:
                displayDictionaryHelper(root);
                break;
            case 5:
                editWordHelper(root);
                break;
            case 6:
                searchByPrefixHelper(root);
                break;
            case 7:
                performQuizHelper(root);
                break;
            case 8:
                displayDictionaryInfoHelper(root);
                break;
            case 9:
                saveAndExitHelper(root);
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 9.\n";
                break;
        }
    } while (choice != 9);

    return 0;
}

// Ham lay do cao cua 1 node
int getHeight(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

// Ham lay su can bang cua hai ben phai trai cua cay
int getBalance(Node* node) {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

// Ham tra ve gia tri be nhat
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Ham tim tu can kiem
Node* search(Node* root, string key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

// Ham quay phai node
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Ham quay trai node
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Ham nhap tu moi vao tu dien
Node* insert(Node* root, string key, string meaning, string type, const vector<string>& examples) {
    if (root == nullptr) { // neu rong thi nhap han vao root
        Node* newNode = new Node(key, meaning, type);
        newNode->examples = examples;
        return newNode;
    }

    if (key < root->key) { // Truong hop tu co do dai ngan hon voi tu duoc so
        root->left = insert(root->left, key, meaning, type, examples);
    } else if (key > root->key) { // Truong hop tu co do dai lon hon voi tu duoc so
        root->right = insert(root->right, key, meaning, type, examples);
    } else {  // Nhap Node
        root->meaning = meaning;
        root->type = type;
        root->examples = examples;
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key) { // Lech trai
        return rightRotate(root);
    }

    if (balance < -1 && key > root->right->key) { // lech phai
        return leftRotate(root);
    }

    if (balance > 1 && key > root->left->key) { // lech trai phai
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    if (balance < -1 && key < root->right->key) { // lenh phai trai
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Ham xoa tu khoi tu dien
Node* deleteNode(Node* root, string key) {
    if (root == nullptr) { // Neu rong thi huy
        return root;
    }

    if (key < root->key) { // Truong hop be hon thi di chuyen ben trai
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) { // Truong hop be hon thi di chuyen ben phai
        root->right = deleteNode(root->right, key);
    } else { // Bat dau xoa Tu
        if (root->left == nullptr || root->right == nullptr) { // Tim node ma co 1 con
            Node* temp = root->left ? root->left : root->right; // Kiem node con cua node co 1 con

            // Neu temp rong thi gan root rong
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else { // Khong thi gan root voi temp
                *root = *temp;
            }

            delete temp; // Xoa Node temp
        } else {
            Node* temp = minValueNode(root->right);

            // Chuyen du lieu tu temp sang root
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->type = temp->type;
            root->examples = temp->examples;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    //Neu rong tra ve 
    if (root == nullptr) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right)); // Lay chieu cao cua root

    int balance = getBalance(root); // Lay do can bang

    if (balance > 1 && getBalance(root->left) >= 0) { // Thuc hien quay phai neu lech trai
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) { // Thuc hien quay phai neu lech trai phai
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) { // Thuc hien quay phai neu lech phai
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) { // Thuc hien quay phai neu lech phai trai
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Ham cap nhat tu
void editWord(Node* root) {
    string key, meaning, type;
    vector<string> examples;

    cout << "Enter word to edit: ";
    cin >> key;

    Node* searchResult = search(root, key);
    // Cap nhat neu co
    if (searchResult != nullptr) {
        cout << "Current meaning of word '" << key << "': " << searchResult->meaning << endl;
        cout << "Current type of word '" << key << "': " << searchResult->type << endl;
        cout << "Current examples:\n";
        for (const string& example : searchResult->examples) {
            cout << example << endl;
        }

        cout << "Enter new meaning: ";
        cin.ignore();
        getline(cin, meaning);

        cout << "Enter new type: ";
        cin >> type;

        inputExamples(examples);

        searchResult->meaning = meaning;
        searchResult->type = type;
        searchResult->examples = examples;

        cout << "Meaning of word has been updated.\n";
    } else {
        cout << "Word '" << key << "' is not in the dictionary.\n";
    }
}

// Ham kiem tu theo loai
void searchByPrefixHelper(Node* root, string prefix) {
    if (root != nullptr) {
        if (root->key.compare(0, prefix.length(), prefix) == 0) {
            cout << root->key << ": " << root->meaning << endl;
            cout << "Type of word: " << root->type << endl;
            cout << "Examples:\n";
            for (const string& example : root->examples) {
                cout << example << endl;
            }
        }
        searchByPrefixHelper(root->left, prefix);
        searchByPrefixHelper(root->right, prefix);
    }
}


void searchByPrefix(Node* root) {
    string prefix;
    cout << "Enter prefix of word to search: ";
    cin >> prefix;
    searchByPrefixHelper(root, prefix);
}

//Ham in node theo thu tu tu
void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << "@" << root->key << ": " << root->meaning << endl;
        cout << "Type of word: " << root->type << endl;
        cout << "Examples:\n";
        for (const string& example : root->examples) {
            cout << example << endl;
        }
        inOrder(root->right);
    }
}

// Ham luu vao file
void saveToFile(Node* root, ofstream& outFile) {
    if (root != nullptr) {
        saveToFile(root->left, outFile);
        outFile << root->key << " " << root->meaning << " " << root->type << endl;

        for (const string& example : root->examples) {
            outFile << example << endl;
        }

        outFile << endl;

        saveToFile(root->right, outFile);
    }
}

/*
 * Tên: Nguyễn Nhật Tấn
 * Mã sinh viên: 22695891
 * Email: nguyennhattan223344@gmail.com
 * Ngay thuc hien: 16/9/2023
 */

// Ham lay tu file
Node* loadFromFile(Node* root, ifstream& inFile) {
    string line;
    while (getline(inFile, line)) {
        size_t pos1 = line.find(" ");
        size_t pos2 = line.find(" ", pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos) {
            string key = line.substr(0, pos1);
            string meaning = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string type = line.substr(pos2 + 1);

            vector<string> examples;
            while (getline(inFile, line) && !line.empty()) {
                examples.push_back(line);
            }

            root = insert(root, key, meaning, type, examples);
        }
    }
    return root;
}

// Ham dem tu
int countWords(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + countWords(root->left) + countWords(root->right);
}

// Ham in do dai cua cay
int treeHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

// Ham lay node theo thu tu inOrder
void getNodesInOrder(Node* root, vector<Node*>& nodes) {
    if (root != nullptr) {
        getNodesInOrder(root->left, nodes);
        nodes.push_back(root);
        getNodesInOrder(root->right, nodes);
    }
}

// Ham lay node bat ky
Node* getRandomNode(Node* root) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomIndex = rand() % countWords(root);
    vector<Node*> nodes;
    getNodesInOrder(root, nodes);
    return nodes[randomIndex];
}

// Ham do vui
void quiz(Node* root) {
    int numQuestions;
    cout << "Enter number of questions: ";
    cin >> numQuestions;

    vector<Node*> nodes;
    getNodesInOrder(root, nodes);

    if (numQuestions > countWords(root)) {
        cout << "Number of questions is greater than the number of words in the dictionary.\n";
        return;
    }

    cin.ignore();  

    cout << "Start Quiz:\n";
    for (int i = 0; i < numQuestions; ++i) {
        Node* questionNode = getRandomNode(root);
        cout << "Question " << i + 1 << ": Meaning of word '" << questionNode->key << "': ";
        
        string userAnswer;

        do {
            getline(cin, userAnswer);
            userAnswer.erase(userAnswer.begin(), find_if(userAnswer.begin(), userAnswer.end(), [](unsigned char ch) {
                return !isspace(ch);
            }));

            transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::tolower);

            if (userAnswer == questionNode->meaning) {
                cout << "Correct!\n";
            } else {
                cout << "Incorrect. The correct answer is: " << questionNode->meaning << endl;
            }
        } while (userAnswer != questionNode->meaning);
    }
    cout << "Quiz complete.\n";
}

// Ham nhap loai tu
void inputType(string& type) {
    cout << "Enter word type: ";
    getline(cin, type);
}

// Ham nhap vi du cua tu
void inputExamples(vector<string>& examples) {
    cin.ignore(); 
    cout << "Enter examples (enter an empty line to finish):\n";
    string example;
    while (true) {
        cout << "> ";
        getline(cin, example);

        if (example.empty()) {
            break;
        }

        examples.push_back(example);
    }
}

// Ham in ra menu
void displayMenu() {
    cout << "+-----------------------&MENU&-----------------------+\n";
    cout << "| 1. Add a Word.                                     |\n";
    cout << "| 2. Search for a Word.                              |\n";
    cout << "| 3. Delete a Word.                                  |\n";
    cout << "| 4. Display Dictionary.                             |\n";
    cout << "| 5. Edit a Word.                                    |\n";
    cout << "| 6. Search Words by Prefix.                         |\n";
    cout << "| 7. Perform Quiz.                                   |\n";
    cout << "| 8. Display Dictionary Info.                        |\n";
    cout << "| 9. Save and Exit.                                  |\n";
    cout << "+-----------------------^----^-----------------------+\n";
    cout << "Enter your choice (1-9): ";
}

// Ham them du lieu tu
void addWordHelper(Node*& root) {
    string key, meaning, type;
    vector<string> examples;

    cout << "Enter word: ";
    cin >> key;

    Node* searchResult = search(root, key);
    if (searchResult != nullptr) {
        cout << "Word '" << key << "' already exists in the dictionary.\n";
        return;
    }

    cout << "Enter meaning: ";
    cin.ignore();
    getline(cin, meaning);

    cout << "Enter word type: ";
    getline(cin, type);

    inputExamples(examples);

    root = insert(root, key, meaning, type, examples);

    cout << "Word added to the dictionary.\n";
}

// Ham kiem tu
void searchWordHelper(Node* root) {
    cin.ignore(); 
    string key;
    cout << "Enter word to search: ";
    getline(cin, key);

    Node* searchResult = search(root, key);
    if (searchResult != nullptr) {
        cout << "Meaning of word '" << key << "': " << searchResult->meaning << endl;
        cout << "Type of word: " << searchResult->type << endl;
        cout << "Examples:\n";
        for (const string& example : searchResult->examples) {
            cout << example << endl;
        }
    } else {
        cout << "Word '" << key << "' is not in the dictionary.\n";
    }
}

// Ham xoa tu
void deleteWordHelper(Node*& root) {
    cin.ignore(); 
    string key;
    cout << "Enter word to delete: ";
    getline(cin, key);

    Node* searchResult = search(root, key);
    if (searchResult != nullptr) {
        root = deleteNode(root, key);
        cout << "Word '" << key << "' deleted from the dictionary.\n";
    } else {
        cout << "Word '" << key << "' is not in the dictionary.\n";
    }
}

// Ham in ra thong tin cac tu
void displayDictionaryHelper(Node* root) {
    cout << "Dictionary:\n";
    inOrder(root);
}

// Ham chinh sua luu du lieu chinh sua
void editWordHelper(Node* root) {
    string key, meaning, type;
    vector<string> examples;

    cout << "Enter word to edit: ";
    cin >> key;

    Node* searchResult = search(root, key);
    if (searchResult != nullptr) {
        cout << "Current meaning of word '" << key << "': " << searchResult->meaning << endl;
        cout << "Current type of word '" << key << "': " << searchResult->type << endl;
        cout << "Current examples:\n";
        for (const string& example : searchResult->examples) {
            cout << example << endl;
        }

        cout << "Enter new meaning: ";
        cin.ignore();
        getline(cin, meaning);

        cout << "Enter new type: ";
        cin >> type;

        inputExamples(examples);

        searchResult->meaning = meaning;
        searchResult->type = type;
        searchResult->examples = examples;

        cout << "Meaning of word has been updated.\n";
    } else {
        cout << "Word '" << key << "' is not in the dictionary.\n";
    }
}

// Ham kiem prefix
void searchByPrefixHelper(Node* root) {
    string prefix;
    cout << "Enter prefix of word to search: ";
    cin >> prefix;
    searchByPrefix(root);
}

// Ham thuc hien quiz
void performQuizHelper(Node* root) {
    quiz(root);
}

// Ham in thong tin cua tu dien
void displayDictionaryInfoHelper(Node* root) {
    cout << "Number of Words in the Dictionary: " << countWords(root) << endl;
    cout << "Height of the Dictionary Tree: " << treeHeight(root) << endl;
}

// Ham thoat va luu
void saveAndExitHelper(Node* root) {
    ofstream outFile("C:/Users/DELL/Desktop/Dictionary.txt");
    if (outFile.is_open()) {
        saveToFile(root, outFile);
        outFile.close();
        cout << "Dictionary saved to 'Dictionary.txt'.\n";
    } else {
        cout << "Error: Unable to save the dictionary to 'Dictionary.txt'.\n";
    }

    freeMemory(root);
    cout << "Exiting the Dictionary Management System.\n";
}

// Ham giai phong bo nho
void freeMemory(Node* root) {
    if (root != nullptr) {
        freeMemory(root->left);
        freeMemory(root->right);
        delete root;
    }
}
