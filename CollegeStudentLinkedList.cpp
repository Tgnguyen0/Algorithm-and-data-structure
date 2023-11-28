/*
 * Tên: Nguyễn Nhật Tấn
 * Mã sinh viên: 22695891
 * Email: nguyennhattan223344@gmail.com
 * Ngay thuc hien: 17/9/2023
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_STUDENT = 100; // So luong hoc sinh toi da
const int MAX_SUBJECT_PER_PERSON = 10; // So luong mon hoc toi da ma hoc vien tham gia
const double MIN_GPA = 0.0; // Diem trung binh toi thieu

typedef struct Subject {
    char name[10]; // Ten mon
    char subjectID[20]; // ID cua mon
    double classGPA; // So hoc sinh theo hoc
} Subject;

typedef struct Student {
    char name[30]; // Ten hoc vien
    char ID[10]; // ID cua hoc vien
    char sex[6]; // Gioi tinh hoc vien
    int numberOfSubject; // So luong mon hoc tham gia
    Subject subjects[MAX_SUBJECT_PER_PERSON]; // Cac mon hoc tham gia
    double subjectsGPA[MAX_SUBJECT_PER_PERSON]; // Cac diem theo tung mon
    double totalGPA; // Diem trung binh cua hoc vien
    Student* next; // Con tro next
} Student;

void addOneStudent(Student* &head, Student* &tail);
void addMoreStudent(Student* &head, Student* &tail);
void addStudentsFromFile(Student* &head, Student* &tail);
void swap(Student* a, Student* b);
void bubbleSort(Student* &head, Student* &tail, int sortBy);
void updatedStudentInfor(Student* &head, Student* &tail, char searchID[10]);
void printOneStudent(Student* Learner, Student* head, int index);
void printMoreStudent(Student* head, Student* tail);
Student* search(Student* head, Student* tail, char searchID[10]);
void Delete(Student* &head, Student* &tail, char searchID[10]);
void inGPAOrder(Student* &head, Student* &tail);
void inNameOrder(Student* &head, Student* &tail);
void attend(Student* head, Student* tail);
void academicPerformanceList(Student* head, Student* tail);
void studentGPAStatistic(Student* head, Student* tail, char searchID[10]);
void maleAndFemaleGPAComparison(Student* head, Student* tail);
void freeStudentList(Student* &head);

int main() {
    Student *head = NULL; // Con tro head
    Student *tail = NULL; // Con tro tail
    Student *cur = new Student();
    
    cout << "   ______          __         __    __  ___                                       __ "; cout << "\n";
    cout << "  / __/ /___ _____/ /__ ___  / /_  /  |/  /__ ____  ___ ____ ____ __ _  ___ ___  / /_"; cout << "\n";
    cout << " _\\ \\/ __/ // / _  / -_) _ \\/ __/ / /|_/ / _ `/ _ \\/ _ `/ _ `/ -_)  ' \\/ -_) _ \\/ __/"; cout << "\n";
    cout << "/___/\\__/\\_,_/\\_,_/\\__/_//_/\\__/ /_/  /_/\\_,_/_//_/\\_,_/\\_, /\\__/_/_/_/\\__/_//_/\\__/ "; cout << "\n";
    cout << "                                                       /___/                         "; cout << "\n";
    
    while(true) {

        cout << "+-----------------------&MENU&-----------------------+\n";
        cout << "| 1. Add one student.                                |\n";
        cout << "| 2. Add more students.                              |\n";
        cout << "| 3. Add students from file.                         |\n";
        cout << "| 4. Print students information.                     |\n";
        cout << "| 5. Search student via student ID.                  |\n";
        cout << "| 6. Delete student via student ID.                  |\n";
        cout << "| 7. Update student information.                     |\n";
        cout << "| 8. List of student in GPA order.                   |\n";
        cout << "| 9. List of student in alphabetical order.          |\n";
        cout << "| 10. List of student of that subject.               |\n";
        cout << "| 11. Academic performance List.                     |\n";
        cout << "| 12. Your subject GPA and GPA of class subject.     |\n";
        cout << "| 13. Male total GPA and female total GPA            |\n";
        cout << "| 14. Exit.                                          |\n";
        cout << "+-----------------------^----^-----------------------+\n";

        int choice = 0 , index2 = 0;
        Student* Learner = NULL;
        char answer;
        char searchID[10], findID[10];
        bool isExit = false;

        cout << "Your choice: ";
        cin >> choice;

        switch(choice) 
        {
            case 1:
                addOneStudent(head, tail);
                break;
            case 2:
                addMoreStudent(head, tail);
                break;
            case 3:
                addStudentsFromFile(head, tail);
                break;
            case 4:
                cout << "\n";
                bubbleSort(head, tail, 3); // Sap xep theo trat tu ID
                cout << "Student list:\n";
                printMoreStudent(head, tail);
                break;
            case 5:
                cout << "\n";
                cout << "Student ID: ";
                cin >> searchID;

                bubbleSort(head, tail, 3); // Sap xep theo trat tu ID
                Learner = search(head, tail, searchID); // Tim kiem nhan vien

                printOneStudent(Learner, head, 0);
                delete Learner;

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 6:
                cout << "\n";
                cout << "Student ID: ";
                cin >> searchID;
                bubbleSort(head, tail, 3); // Sap xep theo trat tu ID
                Delete(head, tail, searchID);
                
                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 7:
                cout << "\n";
                cout << "First displace student ID: ";
                cin >> searchID;
                updatedStudentInfor(head, tail, searchID);
                
                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 8:
                cout << "\n";
                inGPAOrder(head, tail);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 9:
                cout << "\n";
                inNameOrder(head, tail);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 10:
                cout << "\n";
                attend(head, tail);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 11:
                cout << "\n";
                cout << "Academic performance List:\n";
                academicPerformanceList(head, tail);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 12:
                cout << "\n";
                cout << "Student ID: ";
                cin >> searchID;
                studentGPAStatistic(head, tail, searchID);

                cout << "\n";
                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 13:
                bubbleSort(head, tail, 3);
                maleAndFemaleGPAComparison(head, tail);

                cout << "Press any key to continue..."; // Tam ngung chuong trinh
                cin.get();
                cin.ignore();

                break;
            case 14:
                freeStudentList(head);
                cout << "Exiting...";
                isExit = true;
                break;
            default:
                cout << "Wrong input! Try again!\n";
                break;
        }

        if (isExit == true) break;
    }
}

// Ham nhap 1 sinh vien
void addOneStudent(Student* &head, Student* &tail) {
    Student* Learner = new Student();
    cout << "Name: ";
    cin.ignore();
    cin.getline(Learner->name , 30); // Nhap ten

    cout << "ID: ";
    cin >> Learner->ID; // Nhap ID

    cout << "Sex: ";
    cin >> Learner->sex; // Nhap gioi tinh

    do 
    {
        cout << "Number of subjects that student attend: ";
        cin >> Learner->numberOfSubject; // Nhap so mon ma hoc vien tham gia
    }
    while(Learner->numberOfSubject <= 0 || Learner->numberOfSubject > MAX_SUBJECT_PER_PERSON);

    for (int i = 0 ; i < Learner->numberOfSubject ; i++) {

        cout << "Subject name: ";
        cin.ignore();
        cin.getline(Learner->subjects[i].name , 10); // Nhap ten mon

        cout << "Subject ID: ";
        cin >> Learner->subjects[i].subjectID; // ID cua mon

        do 
        {
            cout << "GPA of the class: ";
            cin >> Learner->subjects[i].classGPA; // Diem trung binh mon cua ca lop
        }
        while(Learner->subjects[i].classGPA < 0 || Learner->subjects[i].classGPA > 10);
    }

    for (int i = 0 ; i < Learner->numberOfSubject ; i++) {
        do 
        {
            cout << Learner->name << "'s " << Learner->subjects[i].name << " GPA: ";
            cin >> Learner->subjectsGPA[i]; // Diem trung binh moi mon cua sinh vien
        }
        while(Learner->subjectsGPA[i] < 0 || Learner->subjectsGPA[i] > 10);
        Learner->totalGPA += Learner->subjectsGPA[i];
    }

    Learner->totalGPA = Learner->totalGPA / Learner->numberOfSubject; // Diem trung binh tong cac mon cua sinh vien

    if (head == NULL) { // Neu danh sach rong
        head = tail = Learner;  // Gan head bang Learner moi nhap
    } else { // Neu danh sach khong rong
        tail->next = Learner; // Cho tro tail->next den Learner moi nhap
        tail = Learner; // Gan con tro tail voi Learner
    }
}

// Ham Nhap nhieu sinh vien
void addMoreStudent(Student* &head, Student* &tail) {
    char answer;

    while (true) {
        Student* Learner = new Student();
        cout << "Name: ";
        cin.ignore();
        cin.getline(Learner->name , 30); // Nhap ten

        cout << "ID: ";
        cin >> Learner->ID; // Nhap ID

        cout << "Sex: ";
        cin >> Learner->sex; // Nhap gioi tinh

        do 
        {
            cout << "Number of subjects that student attend: ";
            cin >> Learner->numberOfSubject; // Nhap so mon ma hoc vien tham gia
        }
        while(Learner->numberOfSubject <= 0 || Learner->numberOfSubject > MAX_SUBJECT_PER_PERSON);

        for (int i = 0 ; i < Learner->numberOfSubject ; i++) {

            cout << "Subject name: ";
            cin.ignore();
            cin.getline(Learner->subjects[i].name , 10); // Nhap ten mon

            cout << "Subject ID: ";
            cin >> Learner->subjects[i].subjectID; // ID cua mon

            do 
            {
                cout << "GPA of the class: ";
                cin >> Learner->subjects[i].classGPA; // Diem trung binh mon cua ca lop
            }
            while(Learner->subjects[i].classGPA < 0 || Learner->subjects[i].classGPA > 10);
        }

        for (int i = 0 ; i < Learner->numberOfSubject ; i++) {
            do 
            {
                cout << Learner->name << "'s " << Learner->subjects[i].name << " GPA: ";
                cin >> Learner->subjectsGPA[i]; // Diem trung binh moi mon cua sinh vien
            }
            while(Learner->subjectsGPA[i] < 0 || Learner->subjectsGPA[i] > 10);
            Learner->totalGPA += Learner->subjectsGPA[i];
        }

        Learner->totalGPA = Learner->totalGPA / Learner->numberOfSubject; // Diem trung binh tong cac mon cua sinh vien

        if (head == NULL) {
            head = tail = Learner;
        } else {
            tail->next = Learner;
            tail = Learner;
        }

        cout << "Continue ?(Y/N): "; 
        cin >> answer; // Tiep tuc nhap them hoc vien ?

        if (answer == 'N') {
            break;
        }
    }
}

void freeStudentList(Student* &head) {
    while (head != nullptr) {
        Student* temp = head;
        head = head->next;
        delete temp; // Giai phong bo nho
    }
}

// Ham hoan vi cho 2 sinh vien
void swap(Student* a, Student* b) {
    char tempName[30]; // Trao ten
    strcpy(tempName, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, tempName);

    char tempID[10]; // Trao Id
    strcpy(tempID, a->ID);
    strcpy(a->ID, b->ID);
    strcpy(b->ID, tempID);

    char tempSex[6]; // Trao gioi tinh
    strcpy(tempSex, a->sex);
    strcpy(a->sex, b->sex);
    strcpy(b->sex, tempSex);

    int tempNumberOfSubject = a->numberOfSubject; // Trao so luong mon hoc tham gia
    a->numberOfSubject = b->numberOfSubject;
    b->numberOfSubject = tempNumberOfSubject;

    for (int index = 0; index < MAX_SUBJECT_PER_PERSON; index++) { // Trao mon hoc cua sinh vien
        Subject tempSubject = a->subjects[index];
        a->subjects[index] = b->subjects[index];
        b->subjects[index] = tempSubject;

        double tempSubjectGPA = a->subjectsGPA[index];
        a->subjectsGPA[index] = b->subjectsGPA[index];
        b->subjectsGPA[index] = tempSubjectGPA;
    }

    double tempTotalGPA = a->totalGPA; // Trao diem trung binh tong cua GPA
    a->totalGPA = b->totalGPA;
    b->totalGPA = tempTotalGPA;
}

void bubbleSort(Student* &head, Student* &tail, int sortBy) {
    bool swapped;
    Student* current;
    Student* lastSorted = NULL;

    // Danh sach trong hoac co 1 phan tu khong can sap xep
    if (head == NULL || head->next == NULL) {
        return;
    }

    bool shouldSwap = false;

    do {
        swapped = false;
        current = head;

        while (current->next != lastSorted) {
            // So sanh tuy theo sortBy
            if (sortBy == 1) {
                shouldSwap = strcmp(current->name, current->next->name) >= 0;
            } else if (sortBy == 2) {
                shouldSwap = current->totalGPA > current->next->totalGPA;
            } else if (sortBy == 3) {
                shouldSwap = strcmp(current->ID, current->next->ID) >= 0;
            }

            if (shouldSwap) {
                // Hoan doi thong tin hai nut lien ket
                swap(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
        lastSorted = current;
    } while (swapped);
}

// Ham in ra thong tin 1 hoc vien
void printOneStudent(Student* Learner, Student* head, int index) {
    // In ra danh sach
    Student* cur = head;
    while (cur != Learner) {
        cur = cur->next;
        index++;
    }

    // In theo bang danh sach
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    printf("| %s | %-13s | %-25s | %-7s | %-9s |\n", "No.", "ID", "Name", "Sex", "Total GPA");
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf |\n",index+1 ,Learner->ID, Learner->name, Learner->sex, Learner->totalGPA);
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    cout << "\n";
}

// Ham in ra thong tin cac sinh vien
void printMoreStudent(Student* head , Student* tail) {
    // In ra danh sach
    int index = 1;
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    printf("| %s | %-13s | %-25s | %-7s | %-9s |\n", "No.", "ID", "Name", "Sex", "Total GPA");
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    
    // In theobang danh sach
    if (head != tail) {
        Student* Learner = head;
        while(Learner != NULL) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf |\n", index, Learner->ID, Learner->name, Learner->sex, Learner->totalGPA);
            index++;
            Learner = Learner->next;
        }
    } else {
        printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf |\n", index, head->ID, head->name, head->sex, head->totalGPA);
    }
    
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    cout << "\n";
}

// Ham tim kiem 1 sinh vien
Student* search(Student* head , Student* tail, char searchID[10]) {
    Student* current = head;

    while (current != nullptr) {
        int studentID = atoi(current->ID);

        if (studentID == atoi(searchID)) { // So sanh ID
            return current; // Tra ve vi tri
        }

        if (studentID > atoi(searchID)) {
            return nullptr; // Không cần tìm kiếm tiếp vì danh sách đã được sắp xếp theo ID.
        }

        current = current->next;
    }

    cout << "Student with ID " << searchID << " not found." << endl;
    return nullptr;
}

// Ham xoa sinh vien    
void Delete(Student* &head, Student* &tail, char searchID[10]) {
    bubbleSort(head, tail, 3);
    Student* del = search(head, tail, searchID); // Tra ve nhan vien

    if (del != NULL) {
        char doDelete;
        cout << "Do you really want to delete this? (Y/N): ";
        cin >> doDelete;

        if (doDelete == 'Y' || doDelete == 'y') {
            if (del == head) {
                head = head->next;
                delete del;

                if (head == nullptr) {
                    tail = nullptr; // Cap nhat tail khi danh sach rong
                }
            } else {
                Student* cur = head;
                while (cur->next != del) {
                    cur = cur->next;
                }

                cur->next = del->next;
                delete del;

                if (cur->next == nullptr) {
                    tail = cur; // Cap nhat tail sau khi xoa phan tu cuoi cung
                }
            }

            cout << "List after changing:\n";
            printMoreStudent(head, tail);
        } else {
            cout << "Deletion canceled." << endl;
        }
    } else {
        cout << "Student with ID " << searchID << " not found." << endl;
    }
}


// Ham sap xep theo diem trung binh
void inGPAOrder(Student* &head, Student* &tail) {
    bubbleSort(head, tail, 2); // Sap xep theo GPA
    cout << "List in greater GPA order:\n";
    printMoreStudent(head, tail);
}

// Ham sap xep theo thu tu chu cai
void inNameOrder(Student* &head, Student* &tail) {
    bubbleSort(head, tail, 1); // Sap xep theo ten
    cout << "List in alphabetical order:\n";
    printMoreStudent(head, tail);
}

/*Ngay thuc hien: 18/9/2023*/

// Ham in ra ket qua hoc tap cua sinh vien va cac sinh vien duoc hoc bong
void academicPerformanceList(Student* head, Student* tail) {
    int index = 1;
    
    // Sap xep danh sach theo thu Id tang dan
    bubbleSort(head, tail, 3);
    FILE* file = fopen("C:/Users/DELL/Desktop/Academic Performance List.txt", "w");

    // In ra man hinh bang
    cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
    printf("| %s | %-13s | %-25s | %-7s | %-9s | %-25s | %-13s | %-7s |\n", "No.", "ID", "Name", "Sex", "Total GPA", "Academic Performance", "Scholarship", "Relearn");
    cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";

    // In ra file bang
    fprintf(file, "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n");
    fprintf(file, "| %s | %-13s | %-25s | %-7s | %-9s | %-25s | %-13s | %-7s |\n", "No.", "ID", "Name", "Sex", "Total GPA", "Academic Performance", "Scholarship", "Relearn");
    fprintf(file, "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n");

    Student* current = head;  // Bat dau tai head

    // In danh sach nhan vien
    while (current != nullptr) {
        if (9.0 <= current->totalGPA) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "High distinction", "Qualified", "False");
            fprintf(file, "| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "High distinction", "Qualified", "False");
        } else if (8.0 <= current->totalGPA && current->totalGPA < 9.0) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Distinction", "Unqualified", "False");
            fprintf(file, "| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Distinction", "Unqualified", "False");
        } else if (6.5 <= current->totalGPA && current->totalGPA < 8.0) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Credit", "Unqualified", "False");
            fprintf(file, "| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Credit", "Unqualified", "False");
        } else if (5.0 <= current->totalGPA && current->totalGPA < 6.5) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Strong pass", "Unqualified", "False");
            fprintf(file, "| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Strong pass", "Unqualified", "False");
        } else if (3.5 <= current->totalGPA && current->totalGPA < 5.0) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Average", "Unqualified", "False");
            fprintf(file, "| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Average", "Unqualified", "False");
        } else if (current->totalGPA < 3.5) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Poor", "Unqualified", "True");
            fprintf(file, "| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n", index, current->ID, current->name, current->sex, current->totalGPA, "Poor", "Unqualified", "True");
        }
        current = current->next;
        index++;
    }

    cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
    cout << "\n";

    fprintf(file, "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n");

    fclose(file);
}

/*Ngay thuc hien: 22/9/2023*/

// Ham in danh sach hoc vien theo hoc cac mon
void attend(Student* head, Student* tail) {
    int index = 1;
    char searchSubjectID[20];
    cout << "Search subject ID: ";
    cin >> searchSubjectID;
    
    // Tao file moi in danh sach sinh vien cua lop hop
    FILE* file = fopen("C:/Users/DELL/Desktop/Subject student list.txt", "w");

    // In ra man hinh 
    cout << "List of student learn subject's ID: " << searchSubjectID << ":\n"; // In ra ten mon hoc
    cout << "+-----+---------------+---------------------------+---------+-------------+\n";
    printf("| %s | %-13s | %-25s | %-7s | %-10s |\n", "No.", "ID", "Name", "Sex", "Subject GPA");
    cout << "+-----+---------------+---------------------------+---------+-------------+\n";

    // In vao bieu mau file
    fprintf(file, "List of student learn subject's ID: %s\n", searchSubjectID);
    fprintf(file, "+-----+---------------+---------------------------+---------+-------------+\n");
    fprintf(file, "| %s | %-13s | %-25s | %-7s | %-10s |\n", "No.", "ID", "Name", "Sex", "Subject GPA");
    fprintf(file, "+-----+---------------+---------------------------+---------+-------------+\n");

    Student* current = head;

    // Luot danh sach
    while (current != nullptr) {
        bool found = false;
        
        for (int j = 0; j < current->numberOfSubject; j++) {
            if (strcmp(current->subjects[j].subjectID, searchSubjectID) == 0) {
                // In sinh vien theo hoc ra man hinh
                printf("| %-3d | %-13s | %-25s | %-7s | %-11.2lf |\n", index, current->ID, current->name, current->sex, current->subjectsGPA[j]);
                cout << "+-----+---------------+---------------------------+---------+-------------+\n";

                // In sinh vien theo hoc vao file
                fprintf(file, "| %-3d | %-13s | %-25s | %-7s | %-11.2lf |\n", index, current->ID, current->name, current->sex, current->subjectsGPA[j]);
                fprintf(file, "+-----+---------------+---------------------------+---------+-------------+\n");
                
                found = true;
                break;
            }
        }

        if (found) {
            index++;
        }

        current = current->next;
    }

    fclose(file);
    
    cout << "\n";
}

/*Ngay thuc hien 24/9/2023*/

//Ham cap nhat sinh vien
void updatedStudentInfor(Student* &head, Student* &tail, char searchID[10]) {
    bubbleSort(head, tail, 3);

    Student* update = search(head, tail, searchID);

    if (update == NULL) {
        cout << "Student with ID " << searchID << " not found." << endl;
        return;
    }

    Student* cur = head;
    while(cur != update) {
        cur = cur->next;
    }

    cout << "Updating information for student with ID " << searchID << ":\n";

    cout << "Name: ";
    cin.ignore();
    cin.getline(cur->name , 30); // Nhap ten

    cout << "ID: ";
    cin >> cur->ID; // Nhap ID

    cout << "Sex: ";
    cin >> cur->sex; // Nhap gioi tinh

    do 
    {
        cout << "Number of subjects that student attend: ";
        cin >> cur->numberOfSubject; // Nhap so mon ma hoc vien tham gia
    }
    while(cur->numberOfSubject <= 0 || cur->numberOfSubject > MAX_SUBJECT_PER_PERSON);

    // Nhap ten mon, Id mon, GPA mon cua lop
    for (int i = 0 ; i < cur->numberOfSubject ; i++) {

        cout << "Subject name: ";
        cin.ignore();
        cin.getline(cur->subjects[i].name , 10);

        cout << "Subject ID: ";
        cin >> cur->subjects[i].subjectID;

        do 
        {
            cout << "GPA of the class: ";
            cin >> cur->subjects[i].classGPA;
        }
        while(cur->subjects[i].classGPA < 0 || cur->subjects[i].classGPA > 10);
    }

    cur->totalGPA = 0;

    for (int i = 0 ; i < cur->numberOfSubject ; i++) {
        do 
        {
            cout << cur->name << "'s " << cur->subjects[i].name << " GPA: ";
            cin >> cur->subjectsGPA[i];
        }
        while(cur->subjectsGPA[i] < 0 || cur->subjectsGPA[i] > 10);
        cur->totalGPA += cur->subjectsGPA[i];
    }

    cur->totalGPA = cur->totalGPA / cur->numberOfSubject;
}

// Ham in bieu do thong ke GPA mon hoc cua sinh vien so voi GPA mon hoc cua lop
void studentGPAStatistic(Student* head, Student* tail, char searchID[10]) {
    bubbleSort(head, tail, 3); // Sap xep mang theo thu tu Id

    Student* found = search(head, tail, searchID); // Tim sinh vien can so sanh

    // Tra ve neu sinh vien ay khong ton tai
    if (found == NULL) {
        cout << "Student with ID " << searchID << " not found." << endl; // Tra ve neu khong co
        return;
    }

    for(int i = 0 ; i < found->numberOfSubject ; i++) {
        int toInt1 = found->subjectsGPA[i];
        int toInt2 = found->subjects[i].classGPA;

        if (toInt1 == toInt2) { // Neu phan nguyen hai so bang nhau
            cout << "Your subject GPA comparison with " << found->subjects[i].name << " GPA with " << toInt1 <<".x:\n";

            int dozens = toInt1;
            toInt1 = (int)(found->subjectsGPA[i] * 10) % 10; // Lay phan du subjectGPA[i]
            toInt2 = (int)(found->subjects[i].classGPA * 10) % 10; // Lay phan du subjects[i].classGPA

            // In bieu do
            for (int row = 11 ; row >= 1 ; row--) {
                for (int col = 0 ; col < 1 ; col++) {
                    cout << " ___ ";

                    if (row <= toInt1) {
                        cout << "|   |";
                    } else {
                        cout << " ___ ";
                    }
                    
                    if (row <= toInt2) {
                        cout << "|   |";
                    } else {
                        cout << " ___ ";
                    }

                    cout << " ___ ";
                }

                cout << "\n";
            }

            if (dozens == found->subjectsGPA[i]) { // Neu phan nguyen hai so khac nhau
                cout << "       " << found->subjectsGPA[i] << " ";
            } else {
                cout << "      " << found->subjectsGPA[i] << " ";
            }

            if (dozens == found->subjects[i].classGPA) {
                cout << "  " << found->subjects[i].classGPA << "      ";
            } else {
                cout << " " << found->subjects[i].classGPA << "      ";
            }

            cout << "\n";
        } else {
            cout << "Your subject GPA comparison with " << found->subjects[i].name << " GPA\n";

            // In bieu do
            for (int row = 11 ; row >= 1 ; row--) {
                for (int col = 0 ; col < 1 ; col++) {
                    cout << " ___ ";

                    if (row <= toInt1) {
                        cout << "|   |";
                    } else {
                        cout << " ___ ";
                    }

                    if (row <= toInt2) {
                        cout << "|   |";
                    } else {
                        cout << " ___ ";
                    }

                    cout << " ___ ";
                }

                cout << "\n";
            }

            if (toInt1 == found->subjectsGPA[i]) {
                cout << "       " << found->subjectsGPA[i] << "  ";
            } else {
                cout << "      " << found->subjectsGPA[i] << " ";
            }

            if (toInt2 == found->subjects[i].classGPA) {
                cout << "  " << found->subjects[i].classGPA << "      ";
            } else {
                cout << " " << found->subjects[i].classGPA << "      ";
            }

            cout << "\n";
        }
    }
}

/*Ngay thuc hien 25/9/2023*/

// Ham nhan du lieu tu file
void addStudentsFromFile(Student* &head, Student* &tail) {
    int size;

    FILE* file = fopen("C:/Users/DELL/Desktop/Input file.txt", "w"); // Mo tap tin o che do ghi

    cout << "Number of student: ";
    cin >> size; // So luong nhan vien can nhap

    // In so luong bieu mau dua theo so nhan vien
    for (int i = 0; i < size; i++) {
        fprintf(file, "Name: \n");
        fprintf(file, "ID: \n");
        fprintf(file, "Sex: \n");
        fprintf(file, "Number of subjects that student attend: \n");
        for (int j = 0; j < MAX_SUBJECT_PER_PERSON; j++) {
            fprintf(file, "Subject name: \n");
            fprintf(file, "Subject ID: \n");
            fprintf(file, "GPA of the class: \n");
            fprintf(file, "Student's subjects GPA: \n");
        }
        fprintf(file, "\n");
    }

    fclose(file); // Dong file sau khi in bieu mau xong

    cout << "Input file has been created or updated on your desktop.\n";
    cout << "You may begin typing student information now.\n";
    cout << "File may have some excess lines, so you must delete them to get the desired result.\n";
    cout << "If finished, press Enter to continue..."; // Tam ngung chuong trinh de nhap file
    cin.get();
    cin.ignore();

    file = fopen("C:/Users/DELL/Desktop/Input file.txt", "r"); // Mo tap tin o che do doc
    FILE *file1 = fopen("C:/Users/DELL/Desktop/InputFromUser.txt", "w"); // Mo tap tin luu du lieu

    // Nhan du lieu vua nhap vao trong chuong trinh
    for (int i = 0; i < size; i++) {
        Student* Learner = new Student();

        fscanf(file, "Name: %[^\n]\n", Learner->name);
        fprintf(file1, "Name: %s\n", Learner->name);

        fscanf(file, "ID: %s\n", Learner->ID);
        fprintf(file1, "ID: %s\n", Learner->ID);

        fscanf(file, "Sex: %s\n", Learner->sex);
        fprintf(file1, "Sex: %s\n", Learner->sex);

        fscanf(file, "Number of subjects that student attend: %d\n", &Learner->numberOfSubject);
        fprintf(file1, "Number of subjects that student attend: %d\n", Learner->numberOfSubject);

        for (int j = 0; j < Learner->numberOfSubject && j < MAX_SUBJECT_PER_PERSON; j++) {
            fscanf(file, "Subject name: %[^\n]\n", Learner->subjects[j].name);
            fprintf(file1, "Subject name: %s\n", Learner->subjects[j].name);

            fscanf(file, "Subject ID: %s\n", Learner->subjects[j].subjectID);
            fprintf(file1, "Subject ID: %s\n", Learner->subjects[j].subjectID);

            fscanf(file, "GPA of the class: %lf\n", &Learner->subjects[j].classGPA);
            fprintf(file1, "GPA of the class: %lf\n", Learner->subjects[j].classGPA);

            fscanf(file, "Student's subjects GPA: %lf\n", &Learner->subjectsGPA[j]);
            fprintf(file1, "Student's subjects GPA: %lf\n", Learner->subjectsGPA[j]);
            Learner->totalGPA += Learner->subjectsGPA[j];
        }

        Learner->totalGPA = Learner->totalGPA / Learner->numberOfSubject;

        if (head == NULL) {
            head = tail = Learner;
        } else {
            tail->next = Learner;
            tail = Learner;
        }
    }

    fclose(file); // Dong file sau khi nhap xong
}

// Ham so sanh trung binh GPA cua nam va nu
void maleAndFemaleGPAComparison(Student* head, Student* tail) {
    double maleTotalGPA = 0, femaleTotalGPA = 0;
    int maleCount = 0, femaleCount = 0;

    Student* cur = head;

    while(cur != tail) {
        string lowerSex = cur->sex;
        transform(lowerSex.begin(), lowerSex.end(), lowerSex.begin(), ::tolower);

        if (lowerSex == "male" || lowerSex == "nam") {
            maleTotalGPA += cur->totalGPA; // Tinh trung binh GPA cua nam
            maleCount++;
        } else if (lowerSex == "female" || lowerSex == "nu") {
            femaleTotalGPA += cur->totalGPA; // Tinh trung binh GPA cua nu
            femaleCount++;
        }

        cur = cur->next;
    }

    int toInt1 = 0, toInt2 = 0;
    if (maleCount != 0) {
        toInt1 = maleTotalGPA / maleCount;
    }
    
    if (maleCount != 0) {
        toInt2 = femaleTotalGPA / femaleCount;
    }

    if (toInt1 == toInt2) {  // Neu phan nguyen hai so bang nhau
        cout << "Male total GPA comparison with female total GPA " << toInt1 << ".x: \n";

        int dozens = toInt1;
        toInt1 = (int)((maleTotalGPA / maleCount) * 10) % 10; // Lay phan du cua maleTotalGPA
        toInt2 = (int)((femaleTotalGPA / femaleCount) * 10) % 10; // Lay phan du cua femaleTotalGPA

        // In bieu do
        for (int row = 11 ; row >= 1 ; row--) {
            for (int col = 0 ; col < 1 ; col++) {
                cout << " ___ ";

                if (row <= toInt1) {
                    cout << "|   |";
                } else {
                    cout << " ___ ";
                }
                    
                if (row <= toInt2) {
                    cout << "|   |";
                } else {
                    cout << " ___ ";
                }

                cout << " ___ ";
            }

            cout << "\n";
        }

        if (dozens == maleTotalGPA) {
            printf("       %d ", toInt1);
        } else {
            cout << "       " << toInt1 << "  ";
        }

        if (dozens == femaleTotalGPA) {
            printf("  %d      ", toInt2);
        } else {
            cout << "  " << toInt2 << "      ";
        }

        cout << "\n";
    } else { // Neu phan nguyen hai so khac nhau
        cout << "Male total GPA comparison with female total GPA: \n";

        // In bieu do
        for (int row = 11 ; row >= 1 ; row--) {
            for (int col = 0 ; col < 1 ; col++) {
                cout << " ___ ";

                if (row <= toInt1) {
                    cout << "|   |";
                } else {
                    cout << " ___ ";
                }

                if (row <= toInt2) {
                        cout << "|   |";
                    } else {
                        cout << " ___ ";
                    }

                    cout << " ___ ";
                }

                cout << "\n";
            }

        if (toInt1 == maleTotalGPA) {
            // Kiem tra co phai nam
            if (maleCount != 0) {
                printf("       %d  ", maleTotalGPA / maleCount);
            } else {
                cout << "       " << maleCount << "  ";
            }
                
        } else {
            // Kiem tra co phai nam
            if (maleCount != 0) {
                printf("      %.1f ", maleTotalGPA / maleCount);
            } else {
                cout << "       " << maleCount << "  ";
            }

        }

        if (toInt2 == femaleTotalGPA) {
            // Kiem tra co phai nua
            if (femaleCount != 0) {
                printf("  %d      ", femaleTotalGPA / femaleCount);
            } else {
                cout << "  " << femaleCount << "      ";
            }
                
        } else {
            // Kiem tra co phai nua
            if (femaleCount != 0) {
                printf(" %.1f      ", femaleTotalGPA / femaleCount);
            } else {
                cout << "  " << femaleCount << "      ";
            }
        }
        cout << "\n";
    }
}