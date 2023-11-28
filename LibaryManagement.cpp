/*
 * Tên: Nguyễn Nhật Tấn
 * Mã sinh viên: 22695891
 * Email: nguyennhattan223344@gmail.com
 * Ngay thuc hien: 8/10/2023
 */

#include <iostream>
#include <string>
#include <chrono>
#include <cstring>
#include <sstream>
#include <cmath>

using namespace std;
using namespace chrono;

const int MAX_READER = 100;

typedef struct Book {
    char ID[10];
    char bookName[30];
    char catergoryName[10];
    char publisher[20];
    char author[15];
    float price;
    bool isBorrowed;
} Book;

typedef struct Node {
    Book data;
    Node *next;
} Node;

typedef struct Reader {
    char readerId[10];
    char readerName[20];
    char sex[6];
    int numberOfBooks;
    Node *booksBorrowed[10];
    time_point<system_clock> borrowedDate;
    time_point<system_clock> returnedDate;
} Reader;

typedef struct BooKQueue {
    int numOfBooks;
    Node *front, *rear;
} BookQueue;

bool inItBookQueue(BookQueue &booksList);
bool isEmpty(BookQueue booksList);
bool isFull(BookQueue booksList);
void addBook(BookQueue &booksList);
void addBookFromFile(BookQueue &booksList);
void printOneBook(BookQueue booksList, Node *book, int index);
void printAllBook(BookQueue booksList, int index);
void swapBubble(Book *a, Book *b);
void bubbleSort(BooKQueue booksList, int sortedBy);
void swapQuick(Reader &a, Reader &b);
int partition(Reader readersList[], int low, int high, int sortedBy);
void quickSort(Reader readersList[], int low, int high, int sortedBy);
Node* search(BookQueue booksList, char searchName[40]);
Node* deleteBook(BookQueue &booksList);
void readerBorrow(Reader readersList[], int &size, BookQueue booksList);
Reader* findReaderById(Reader readersList[], int size, const char* searchReaderId);
float calculateTotalPrice(Reader &readerReceipt);
void displayReceipt(Reader &readerReceipt);
void receipt(Reader readersList[], int size);
void inCategory(BookQueue booksList, char catergory[30]);
void bookPublish(BookQueue booksList, char publisher[30]);
void booksAuthor(BookQueue booksList, char author[30]);

int main() {
    cout << "   ___            __     __  ___                                       __ " << endl;
    cout << "  / _ )___  ___  / /__  /  |/  /__ ____  ___ ____ ____ __ _  ___ ___  / /_" << endl;
    cout << " / _  / _ \\/ _ \\/  '_/ / /|_/ / _ `/ _ \\/ _ `/ _ `/ -_)  ' \\/ -_) _ \\/ __/" << endl;
    cout << "/____/\\___/\\___/_/\\_\\ /_/  /_/\\_,_/_//_/\\_,_/\\_, /\\__/_/_/_/\\__/_//_/\\__/ " << endl;
    cout << "                                            /___/                         " << endl;

    int size = 0, index = 0;
    BookQueue booksList;
    Reader readersList[MAX_READER];
    inItBookQueue(booksList);

    while(true) {

        cout << "+-----------------------&MENU&-----------------------+\n";
        cout << "| 1. Add books.                                      |\n";
        cout << "| 2. Add books from file.                            |\n";
        cout << "| 3. Print books information.                        |\n";
        cout << "| 4. Search book.                                    |\n";
        cout << "| 5. Delete book.                                    |\n";
        cout << "| 6. Books rental.                                   |\n";
        cout << "| 7. Rental receipt.                                 |\n";
        cout << "| 8. Books in catergory.                             |\n";
        cout << "| 9. Books in publisher.                             |\n";
        cout << "| 10. Books in Author.                               |\n";
        cout << "| 11. Exit.                                          |\n";
        cout << "+-----------------------^----^-----------------------+\n";

        int choice = 0;
        char catergory[30], publisher[30], name[30], author[30];
        bool isExit = false;
        Node *book;
        cout << "Your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                if (isEmpty(booksList)) {
                    inItBookQueue(booksList);
                }
                addBook(booksList);
                break;
            case 2:
                if (isEmpty(booksList)) {
                    inItBookQueue(booksList);
                }
                addBookFromFile(booksList);
                break;
            case 3:
                //mergeSort(booksList, 1);
                printAllBook(booksList, 0);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 4:
                cout << "Book's name: ";
                cin.ignore();
                cin.getline(name, 20);

                book = search(booksList, name);
                printOneBook(booksList, book, 0);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();

                break;
            case 5:
                cout << "Book you have just deleted:" << endl;

                book = deleteBook(booksList);
                cout << "+-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+\n";
                printf("| %s | %-10s | %-25s | %-15s | %-20s | %-18s | %-13s | %-13s |\n", "No.", "ID", "Name", "Catergory", "Publisher", "Author", "Rental price", "Is borrowed?");
                cout << "+-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+\n";
                printf("| %-3d | %-10s | %-25s | %-15s | %-20s | %-18s | %-13f | %-13s |\n", 1, book->data.ID, book->data.bookName, book->data.catergoryName, book->data.publisher, book->data.author, book->data.price, (book->data.isBorrowed) ? "Yes" : "No");
                cout << "+-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+\n";

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 6:
                readerBorrow(readersList, size, booksList);
                break;
            case 7:
                receipt(readersList, size);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 8:
                cout << "Category: ";
                cin.ignore();
                cin.getline(catergory, 20);

                inCategory(booksList , catergory);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                break;
            case 9:
                cout << "Publisher: ";
                cin.ignore();
                cin.getline(publisher, 20);
        
                bookPublish(booksList, publisher);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                break;
            case 10:
                cout << "Author: ";
                cin.ignore();
                cin.getline(author, 20);

                booksAuthor(booksList, author);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                break;
            case 11:
                cout << "Exiting...";
                isExit = true;
                break;
            default:
                cout << "Wrong choice!";
                break;
        }

        if (isExit == true) break;
    }
}

bool inItBookQueue(BookQueue &booksList) {
    booksList.numOfBooks = 0;
    booksList.front = booksList.rear = NULL;
    return true;
}

bool isEmpty(const BookQueue booksList) {
    return (booksList.numOfBooks == 0);
}

bool isFull(const BookQueue booksList) {
    Book* newBook = new Book();
    if (newBook == NULL) {
        return true;
    }
    delete newBook;
    return false;
}

void addBook(BookQueue &booksList) {
    while(true) {
        if (isFull(booksList)) {
            return;
        }

        Node *newBook = new Node();

        cout << "Book Id: ";
        cin >> newBook->data.ID;

        cout << "Book name: ";
        cin.ignore();
        cin.getline(newBook->data.bookName, 30);

        cout << "Book's category: ";
        cin.getline(newBook->data.catergoryName, 30);

        cout << "Book's publisher: ";
        cin.getline(newBook->data.publisher, 30);

        cout << "Book's author: ";
        cin.getline(newBook->data.author, 30);

        do {
            cout << "Book's rental price: ";
            cin >> newBook->data.price;
        } while (newBook->data.price <= 0);
        
        newBook->data.isBorrowed = false;

        if (booksList.front == nullptr && booksList.rear == nullptr) {
            booksList.front = booksList.rear = newBook;
        } else {
            booksList.rear->next = newBook;
            booksList.rear = newBook;
        }

        booksList.numOfBooks++;

        char isContinue;
        cout << "Continue(Y/N)?: ";
        cin >> isContinue;
        if (isContinue == 'N') {
            break;
        }
    }
}

void addBookFromFile(BookQueue &booksList) {
    if (isFull(booksList)) {
        return;
    }

    int size = 0;
    FILE *file = fopen("C:/Users/DELL/Desktop/input.txt", "w");

    cout << "Number of books: ";
    cin >> size;

    for (int i = 0; i < size; i++) {
        fprintf(file, "Book's name: \n");
        fprintf(file, "Book's ID: \n");
        fprintf(file, "Category: \n");
        fprintf(file, "Publisher: \n");
        fprintf(file, "Book's author: \n");
        fprintf(file, "Rental price: \n");
        fprintf(file, "\n");
    }

    fclose(file);

    cout << "Input file has been created or updated on your desktop.\n";
    cout << "You may begin typing books information now.\n";
    cout << "File may have some excess lines, so you must delete them to get the desired result.\n";
    cout << "If finished, press Enter to continue..."; // Tam ngung chuong trinh de nhap file
    cin.get();
    cin.ignore();

    file = fopen("C:/Users/DELL/Desktop/input.txt", "r");

    for (int i = 0; i < size; i++) {
        if (isFull(booksList)) {
            return;
        }

        Node *newBook = new Node();

        fscanf(file, "Book's name: %[^\n]\n", newBook->data.bookName);
        fscanf(file, "Book's ID: %s\n", newBook->data.ID);
        fscanf(file, "Category: %[^\n]\n", newBook->data.catergoryName);
        fscanf(file, "Publisher: %[^\n]\n", newBook->data.publisher);
        fscanf(file, "Book's author: %[^\n]\n", newBook->data.author);
        fscanf(file, "Rental price: %f\n", &newBook->data.price);

        if (booksList.front == NULL) {
            booksList.front = booksList.rear = newBook;
        } else {
            booksList.rear->next = newBook;
            booksList.rear = newBook;
        }

        booksList.numOfBooks++;
    }

    fclose(file);
}

void printOneBook(BookQueue booksList, Node* book, int index) {
    if (isEmpty(booksList)) {
        return;
    }

    Node* cur = booksList.front;
    while (cur != book) {
        cur = cur->next;
        index++;
    }

    cout << "+-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+\n";
    printf("| %s | %-10s | %-25s | %-15s | %-20s | %-18s | %-13s | %-13s |\n", "No.", "ID", "Name", "Catergory", "Publisher", "Author", "Rental price", "Is borrowed?");
    cout << "+-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+\n";
    printf("| %-3d | %-10s | %-25s | %-15s | %-20s | %-18s | %-13f | %-13s |\n", index+1, book->data.ID, book->data.bookName, book->data.catergoryName, book->data.publisher, book->data.author, book->data.price, (book->data.isBorrowed) ? "Yes" : "No");
    cout << "+-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+\n";
    cout << endl;
}

void printAllBook(BookQueue booksList, int index) {
    if (isEmpty(booksList)) {
        return;
    }

    cout << "+-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+\n";
    printf("| %s | %-10s | %-25s | %-15s | %-20s | %-18s | %-13s | %-13s |\n", "No.", "ID", "Name", "Catergory", "Publisher", "Author", "Rental price", "Is borrowed?");
    cout << "+-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+\n";

    Node* cur = booksList.front;
    while (cur != nullptr) {
        printf("| %-3d | %-10s | %-25s | %-15s | %-20s | %-18s | %-13f | %-13s |\n", index+1, cur->data.ID, cur->data.bookName, cur->data.catergoryName, cur->data.publisher, cur->data.author, cur->data.price, (cur->data.isBorrowed) ? "Yes" : "No");
        cout << "+-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+\n";
        cur = cur->next;
        index++;
    }

    cout << endl;
}

// Ham hoan vi cho 2 quyen truyen
void swapBubble(Node* a, Node* b) {
    Book temp = a->data; // Trao gia
    a->data = b->data;
    b->data = temp;
}

// Ham trao hai quyen truyen voi nhau
void bubbleSort(BookQueue booksList, int sortedBy) {
    bool swapped;
    Node *cur = booksList.front;
    Node *lastSorted = NULL;

    if (booksList.front == NULL && booksList.front->next == NULL) { // Neu danh sach rong thi ngung
        return;
    }

    bool shouldSwap = false;

    do {
        swapped = false; // Kiem tra viec trao
        cur = booksList.front;

        while(cur->next != lastSorted) { // Nham bo phan tu da trao
            if (sortedBy == 1) { // Xep theo ID
                shouldSwap = strcmp(cur->data.ID, cur->next->data.ID) >= 0;
            } else if (sortedBy == 2) { // Xep theo ten
                shouldSwap = strcmp(cur->data.bookName, cur->next->data.bookName) >= 0;
            } else if (sortedBy == 3) { // Xep theo loai
                shouldSwap = strcmp(cur->data.catergoryName, cur->next->data.catergoryName) >= 0;
            } else if (sortedBy == 4) { // Xep theo tac gia
                shouldSwap = strcmp(cur->data.author, cur->next->data.author) >= 0;
            }

            if (shouldSwap) {
                swapBubble(cur, cur->next);
                swapped = true; // Kiem tra viec da trao
            }

            cur = cur->next;
        }
        lastSorted = cur; // Nhan phan tu trao lan truoc
    } while(swapped); // Kiem tra cac phan tu sap xep het
}


// Ham tim kiem truyen theo ten truyen
Node* search(BookQueue booksList, char searchName[30]) {
    if (isEmpty(booksList)) { // Neu danh sach rong thi ngung
        return NULL;
    }

    Node *cur = booksList.front;
    
    bubbleSort(booksList, 2);

    while(cur != NULL) {
        if (strcmp(cur->data.bookName, searchName) == 0) { // Trung ten tra ve cur
            return cur;
        }
        
        cur = cur->next;
    }

    return NULL; // Tra ve NULL neu khong thay
}

void swapQuick(Reader &a, Reader &b) {
    Reader temp = a;
    a = b;
    b = temp;
}

int partition(Reader readersList[], int low, int high, int sortedBy) {
    Reader pivot = readersList[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        int shouldSwap = 0;
        if (sortedBy == 1) {
            shouldSwap = strcmp(readersList[j].readerId, pivot.readerId);
        } else {
            shouldSwap = strcmp(readersList[j].readerName, pivot.readerName);
        }

        if (shouldSwap < 0) {
            i++;
            swapQuick(readersList[i], readersList[j]);
        }
    }

    swapQuick(readersList[i + 1], readersList[high]);
    return i + 1;
}

void quickSort(Reader readersList[], int low, int high, int sortedBy) {
    if (low < high) {
        int pi = partition(readersList, low, high, sortedBy);

        quickSort(readersList, low, pi - 1, sortedBy);
        quickSort(readersList, pi + 1, high, sortedBy);
    }
}

void readerBorrow(Reader readersList[], int &size, BookQueue booksList) {
    if (isEmpty(booksList)) {
        return;
    }

    while(true) {
        Reader newReader;

        cout << "Reader id: ";
        cin >> newReader.readerId;

        cout << "Reader name: ";
        cin.ignore();
        cin.getline(newReader.readerName, 30);

        cout << "Reader's sex: ";
        cin >> newReader.sex;

        printAllBook(booksList, 0);

        char bookName[30];
        newReader.numberOfBooks = 0;
        while(true) {
            cout << "Book name: ";
            cin.ignore();
            cin.getline(bookName, 30);
            Node* borrowBook = search(booksList, bookName);

            if (borrowBook == NULL) {
                cout << "This book is not available!\n";
            } else if (borrowBook->data.isBorrowed == true) {
                cout << "This book is borrowed!\n";
            } else {
                borrowBook->data.isBorrowed = true;
                newReader.booksBorrowed[newReader.numberOfBooks] = borrowBook;
                newReader.numberOfBooks++;
            }

            char isContinue;
            cout << "Continue choosing book(Y/N)?: ";
            cin >> isContinue;
            if (isContinue == 'N') {
                break;
            }
        }

        string inputDate;
        int dayBorrowed, dayReturned, monthBorrowed, monthReturned, yearBorrowed, yearReturned;
        char separator;

        while (true) {
            cout << "Borrowed date (dd/mm/yyyy): ";
            cin >> inputDate;
            istringstream dateStream(inputDate);
            dateStream >> dayBorrowed >> separator >> monthBorrowed >> separator >> yearBorrowed;

            if (dateStream.fail() || dayBorrowed < 1 || dayBorrowed > 31 || monthBorrowed < 1 || monthBorrowed > 12) {
                cout << "Invalid date. Please enter a valid date." << endl;
            } else {
                tm borrowedTm = {0};
                borrowedTm.tm_mday = dayBorrowed;
                borrowedTm.tm_mon = monthBorrowed - 1;
                borrowedTm.tm_year = yearBorrowed - 1900;
                newReader.borrowedDate = system_clock::from_time_t(mktime(&borrowedTm));
                break;
            }
        }

        while (true) {
            cout << "Return date (dd/mm/yyyy): ";
            cin >> inputDate;
            istringstream dateStream(inputDate);
            dateStream >> dayReturned >> separator >> monthReturned >> separator >> yearReturned;

            if (dateStream.fail() || dayReturned < 1 || dayReturned > 31 || monthReturned < 1 || monthReturned > 12) {
                cout << "Invalid date. Please enter a valid date." << endl;
            } else if (dayReturned < dayBorrowed && monthReturned < monthBorrowed && yearReturned < yearBorrowed) {
                cout << "The return date must be greater than the borrowed date!" << endl;
            } else if (((yearReturned - yearBorrowed) * 12 + monthReturned - monthBorrowed) * 30 + dayReturned - dayBorrowed > 10) {
                cout << "The days you rent the books must not be greater than 10 days!" << endl;

                // 01/01/2024
                // 30/10/2023
                // 10/11/2023
                // 20/11/2023
                // 01/01/2024
            } else {
                tm returnedTm = {0};
                returnedTm.tm_mday = dayReturned;
                returnedTm.tm_mon = monthReturned - 1;
                returnedTm.tm_year = yearReturned - 1900;
                newReader.returnedDate = system_clock::from_time_t(mktime(&returnedTm));
                break;
            }
        }

        readersList[size] = newReader;
        size++;

        char isContinue;
        cout << "Any reader left(Y/N)?: ";
        cin >> isContinue;
        if (isContinue == 'N') {
            break;
        }
    }

}

Node* deleteBook(BookQueue &booksList) {
    if (isEmpty(booksList)) {
        return NULL;
    }

    Node* frontBook = booksList.front;
    booksList.front = frontBook->next;
    Node* bookOut = frontBook;
    delete frontBook;

    booksList.numOfBooks--;

    if (booksList.numOfBooks == 0) {
        inItBookQueue(booksList);
    }
    return bookOut;
}

Reader *findReaderById(Reader readersList[], int size, const char searchReaderId[10]) {
    int low = 0, high = size - 1;
    quickSort(readersList, low, high, 1);

    while (low <= high) {
        int index = (low + high) / 2;
        int identical = strcmp(readersList[index].readerId, searchReaderId);
        if (identical == 0) {
            return &readersList[index];
        }

        if (identical < 0) {
            low = index + 1;
        } else {
            high = index - 1;
        }
    }

    return NULL;
}

float calculateTotalPrice(Reader &readerReceipt) {
    float totalPrice = 0.0;
    float overtimePay = 0.0;

    time_point<system_clock> now = system_clock::now();
    duration<int, ratio<1>> days = duration_cast<duration<int, ratio<1>>>(now - readerReceipt.returnedDate);
    int daysCount = days.count() / (60 * 60 * 24);

    for (int i = 0; i < readerReceipt.numberOfBooks; i++) {
        if (readerReceipt.booksBorrowed[i] != nullptr) {
            totalPrice += readerReceipt.booksBorrowed[i]->data.price;
            if (daysCount > 7) {
                overtimePay += readerReceipt.booksBorrowed[i]->data.price * ((daysCount - 7) * 0.05 + 1);
            }
        }
    }

    return totalPrice + overtimePay;
}

/*
 * Tên: Nguyễn Nhật Tấn
 * Mã sinh viên: 22695891
 * Email: nguyennhattan223344@gmail.com
 * Ngay thuc hien: 9/10/2023
 */

void displayReceipt(Reader &readerReceipt) {
    char borrowedDateStr[12];
    auto borrowedDate = system_clock::to_time_t(readerReceipt.borrowedDate);
    strftime(borrowedDateStr, sizeof(borrowedDateStr), "%d/%m/%Y", localtime(&borrowedDate));

    char returnDateStr[12];
    auto returnedDate = system_clock::to_time_t(readerReceipt.returnedDate);
    strftime(returnDateStr, sizeof(returnDateStr), "%d/%m/%Y", localtime(&returnedDate));

    cout << "+----+--------------------------------------------------------------------------------------------------------------------------------------------+----+\n";
    cout << "|    |                                                            Customer's Receipt                                                              |    |\n";
    cout << "+----+--------------------------------------------------------------------------------------------------------------------------------------------+----+\n";
    printf("|     Name: %-20s                                                                                                                       |\n", readerReceipt.readerName);
    printf("|     ID: %-10s                                                                                                                                   |\n", readerReceipt.readerId);
    printf("|     Sex: %-6s                                                                                                                                      |\n", readerReceipt.sex);
    printf("|     Borrow Date: %-12s                                                                                                                        |\n", borrowedDateStr);
    printf("|     Return Date: %-12s                                                                                                                        |\n", returnDateStr);
    printf("|     Invoice Date:                                                                                                                                    |\n");
    cout << "|                                                                                                                                                      |\n";
    cout << "|    +-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+    |\n";
    printf("|    | %s | %-10s | %-25s | %-15s | %-20s | %-18s | %-13s | %-13s |    |\n", "No.", "ID", "Name", "Category", "Publisher", "Author", "Rental price", "Is Borrowed?");
    cout << "|    +-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+    |\n";

    for (int i = 0 ; i < 1 ; i++) {
        if (readerReceipt.booksBorrowed[i] != NULL) {
            printf("|    | %-3d | %-10s | %-25s | %-15s | %-20s | %-18s | %-13f | %-13s |    |\n", i+1, readerReceipt.booksBorrowed[i]->data.ID, readerReceipt.booksBorrowed[i]->data.bookName, 
            readerReceipt.booksBorrowed[i]->data.catergoryName, readerReceipt.booksBorrowed[i]->data.publisher, readerReceipt.booksBorrowed[i]->data.author, 
            readerReceipt.booksBorrowed[i]->data.price, (readerReceipt.booksBorrowed[i]->data.isBorrowed) ? "Yes" : "No");
            cout << "|    +-----+------------+---------------------------+-----------------+----------------------+--------------------+---------------+---------------+    |\n";
        }
    }

    float totalPrice = calculateTotalPrice(readerReceipt);

    cout << "|                                                                                                                                                      |\n";
    printf("|    Total price: %-30f                                                                                                       |\n", totalPrice);
    cout << "+----+--------------------------------------------------------------------------------------------------------------------------------------------+----+\n";
}

void receipt(Reader readersList[], int size) {
    if (size == 0) {
        return;
    }

    char searchReaderId[10];
    cout << "Reader id: ";
    cin >> searchReaderId;

    Reader readerReceipt;
    
    if (size > 1) {
        readerReceipt = *findReaderById(readersList, size, searchReaderId);
    } else {
        readerReceipt = readersList[0];
    }

    displayReceipt(readerReceipt);
}

void inCategory(BookQueue booksList, char catergory[10]) {
    bubbleSort(booksList, 3);

    Node *cur = booksList.front;
    int index = 0;

    cout << "+-----------------+-----+------------+---------------------------+----------------------+--------------------+---------------+---------------+\n";
    printf("| %-15s | %s | %-10s | %-25s | %-20s | %-18s | %-13s | %-13s |\n", "Category", "No.", "ID", "Name", "Publisher", "Author", "Rental Price", "Is borrowed?");
    cout << "+-----------------+-----+------------+---------------------------+----------------------+--------------------+---------------+---------------+\n";

    while(cur != NULL) {
        if (strcmp(cur->data.catergoryName, catergory) == 0 && cur->data.isBorrowed == 0) {
            printf("| %-15s | %-3d | %-10s | %-25s | %-20s | %-18s | %-13f | %-13s |\n", cur->data.catergoryName, index+1, cur->data.ID, cur->data.bookName, cur->data.publisher, cur->data.author, cur->data.price);
            cout << "+-----------------+-----+------------+---------------------------+----------------------+--------------------+---------------+---------------+\n";
            index++;
        }
        cur = cur->next;
    }
}

void bookPublish(BookQueue booksList, char publisher[20]) {
    bubbleSort(booksList, 5);

    Node *cur = booksList.front;
    int index = 0;
    cout << "+----------------------+-----+------------+---------------------------+-----------------+--------------------+---------------+---------------+\n";
    printf("| %-20s | %s | %-10s | %-25s | %-15s | %-18s | %-13s | %-13s |\n", "Publisher", "No.", "ID", "Name", "Category", "Author", "Rental Price", "Is Borrowed");
    cout << "+----------------------+-----+------------+---------------------------+-----------------+--------------------+---------------+---------------+\n";

    while(cur != NULL) {
        if (strcmp(cur->data.publisher, publisher) == 0 && cur->data.isBorrowed == 0) {
            printf("| %-20s | %-3d | %-10s | %-25s | %-15s | %-18s | %-13f | %-13s |\n", cur->data.publisher, index+1, cur->data.ID, cur->data.bookName, cur->data.catergoryName, cur->data.author, cur->data.price);
            cout << "+----------------------+-----+------------+---------------------------+-----------------+--------------------+---------------+---------------+\n";
            index++;
        }
        cur = cur->next;
    }
}

void booksAuthor(BookQueue booksList, char author[15]) {
    bubbleSort(booksList, 4);

    Node *cur = booksList.front;
    int index = 0;

    cout << "+--------------------+-----+------------+---------------------------+-----------------+----------------------+---------------+---------------+\n";
    printf("| %-18s | %s | %-10s | %-25s | %-15s | %-20s | %-13s | %-13s |\n", "Author", "No.", "ID", "Name", "Category", "Publisher", "Rental Price", "Is Borrowed");
    cout << "+--------------------+-----+------------+---------------------------+-----------------+----------------------+---------------+---------------+\n";

    while(cur != NULL) {
        if (strcmp(cur->data.author, author) == 0 && cur->data.isBorrowed == 0) {
            printf("| %-18s | %-3d | %-10s | %-25s | %-15s | %-20s | %-13f | %-13s |\n", cur->data.author, index+1, cur->data.ID, cur->data.bookName, cur->data.catergoryName, cur->data.publisher, cur->data.price);
            cout << "+--------------------+-----+------------+---------------------------+-----------------+----------------------+---------------+---------------+\n";
            index++;
        }
        cur = cur->next;
    }
}

