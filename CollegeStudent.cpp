/*
 * Tên: Nguyễn Nhật Tấn
 * Mã sinh viên: 22695891
 * Email: nguyennhattan223344@gmail.com
 * Ngay thuc hien: 27/8/2023
 */

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAX_STUDENT = 100;
const int MAX_SUBJECT_PER_PERSON = 10;
const double MIN_GPA = 0.0;

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
} Student;

void addOneStudent(Student studentList[], int &size);
void addMoreStudent(Student studentList[], int &size);
void Swap(Student &a , Student &b);
int partition(Student studentList[], int low, int high, int sortBy);
void quickSort(Student studentList[], int low, int high, int sortBy);
void updatedStudentInfor(Student studentList[] , int &size , char searchID[10]);
void printOneStudent(Student Learner, int index);
void printMoreStudent(Student studentList[], int size);
int search(Student studentList[], int size, char searchID[10]);
void Delete(Student studenList[], int &size, char searchID[10]);
void inGPAOrder(Student studentList[] , int size);
void inNameOrder(Student studentList[], int size);
void attend(Student studentList[] , int size);
void academicPerformanceList(Student studentList[] , int size);
void statistic(Student studentList[] , int size , char searchID[10]);

int main() {
    int size = 0;
    Student studentList[MAX_STUDENT]; // Mang danh sach sinh vien
    
    cout << "   ______          __         __    __  ___                                       __ "; cout << "\n";
    cout << "  / __/ /___ _____/ /__ ___  / /_  /  |/  /__ ____  ___ ____ ____ __ _  ___ ___  / /_"; cout << "\n";
    cout << " _\\ \\/ __/ // / _  / -_) _ \\/ __/ / /|_/ / _ `/ _ \\/ _ `/ _ `/ -_)  ' \\/ -_) _ \\/ __/"; cout << "\n";
    cout << "/___/\\__/\\_,_/\\_,_/\\__/_//_/\\__/ /_/  /_/\\_,_/_//_/\\_,_/\\_, /\\__/_/_/_/\\__/_//_/\\__/ "; cout << "\n";
    cout << "                                                       /___/                         "; cout << "\n";
    
    while(true) {

        cout << "+-----------------------&MENU&-----------------------+\n";
        cout << "| 1. Add one student.                                |\n";
        cout << "| 2. Add more students.                              |\n";
        cout << "| 3. Print students information.                     |\n";
        cout << "| 4. Search student via student ID.                  |\n";
        cout << "| 5. Delete student via student ID.                  |\n";
        cout << "| 6. Update student information.                     |\n";
        cout << "| 7. List of student in GPA order.                   |\n";
        cout << "| 8. List of student in alphabetical order.          |\n";
        cout << "| 9. List of student of that subject.                |\n";
        cout << "| 10. Academic performance List.                     |\n";
        cout << "| 11. Your subject GPA and GPA of class subject.     |\n";
        cout << "| 12. Exit.                                          |\n";
        cout << "+-----------------------^----^-----------------------+\n";

        int choice = 0 , index1 = 0, index2 = 0;
        char searchID[10], findID[10];
        bool isExit = false;


        cout << "Your choice: ";
        cin >> choice;

        switch(choice) 
        {
            case 1:
                addOneStudent(studentList, size);
                break;
            case 2:
                addMoreStudent(studentList, size);
                break;
            case 3:
                quickSort(studentList, 0, size - 1, 3); // Sap xep theo trat tu ID
                printMoreStudent(studentList, size);
                break;
            case 4:
                cout << "ID: ";
                cin >> searchID;
                quickSort(studentList, 0, size - 1, 3); // Sap xep theo trat tu ID
                index1 = search(studentList, size, searchID);
                printOneStudent(studentList[index1], index1);
                break;
            case 5:
                cout << "ID: ";
                cin >> searchID;
                quickSort(studentList, 0, size - 1, 3); // Sap xep theo trat tu ID
                Delete(studentList, size, searchID);
                break;
            case 6:
                cout << "First displace student ID: ";
                cin >> searchID;
                updatedStudentInfor(studentList , size , searchID);
                break;
            case 7: 
                inGPAOrder(studentList, size);
                break;
            case 8:
                inNameOrder(studentList, size);
                break;
            case 9:
                attend(studentList , size);
                break;
            case 10:
                academicPerformanceList(studentList , size);
                break;
            case 11:
                cout << "ID: ";
                cin >> searchID;
                statistic(studentList, size, searchID);
                break;
            case 12:
                cout << "Exiting...";
                isExit = true;
                break;
            default:
                cout << "Wrong input! Try again!\n";
        }

        if (isExit == true) break;
    }
}

// Ham nhap 1 sinh vien
void addOneStudent(Student studentList[] , int &size) {
    Student Learner;
    cout << "Name: ";
    cin.ignore();
    cin.getline(Learner.name , 30); // Nhap ten

    cout << "ID: ";
    cin >> Learner.ID; // Nhap ID

    cout << "Sex: ";
    cin >> Learner.sex; // Nhap gioi tinh

    do 
    {
        cout << "Number of subjects that student attend: ";
        cin >> Learner.numberOfSubject; // Nhap so mon ma hoc vien tham gia
    }
    while(Learner.numberOfSubject <= 0 || Learner.numberOfSubject > MAX_SUBJECT_PER_PERSON);

    for (int i = 0 ; i < Learner.numberOfSubject ; i++) {

        cout << "Subject name: ";
        cin.ignore();
        cin.getline(Learner.subjects[i].name , 10); // Nhap ten mon

        cout << "Subject ID: ";
        cin >> Learner.subjects[i].subjectID; // ID cua mon

        do 
        {
            cout << "GPA of the class: ";
            cin >> Learner.subjects[i].classGPA; // Diem trung binh mon cua ca lop
        }
        while(Learner.subjects[i].classGPA < 0 || Learner.subjects[i].classGPA > 10);
    }

    for (int i = 0 ; i < Learner.numberOfSubject ; i++) {
        do 
        {
            cout << Learner.name << "'s " << Learner.subjects[i].name << " GPA: ";
            cin >> Learner.subjectsGPA[i]; // Diem trung binh moi mon cua sinh vien
        }
        while(Learner.subjectsGPA[i] < 0 || Learner.subjectsGPA[i] > 10);
        Learner.totalGPA += Learner.subjectsGPA[i];
    }

    Learner.totalGPA = Learner.totalGPA / Learner.numberOfSubject; // Diem trung binh tong cac mon cua sinh vien

    studentList[size] = Learner;
    size++;
}

// Ham Nhap nhieu sinh vien
void addMoreStudent(Student studentList[] , int &size) {
    char answer;

    while (true) {

        if (size >= MAX_STUDENT) {
            cout << "student list is full!" << endl;
            break;
        }

        Student Learner;
        cout << "Name: ";
        cin.ignore();
        cin.getline(Learner.name , 30); // Nhap ten

        cout << "ID: ";
        cin >> Learner.ID; // Nhap ID

        cout << "Sex: ";
        cin >> Learner.sex; // Nhap gioi tinh

        do 
        {
            cout << "Number of subjects that student attend: ";
            cin >> Learner.numberOfSubject; // Nhap so mon ma hoc vien tham gia
        }
        while(Learner.numberOfSubject <= 0 || Learner.numberOfSubject > MAX_SUBJECT_PER_PERSON);

        for (int i = 0 ; i < Learner.numberOfSubject ; i++) {

            cout << "Subject name: ";
            cin.ignore();
            cin.getline(Learner.subjects[i].name , 10); // Nhap ten mon

            cout << "Subject ID: ";
            cin >> Learner.subjects[i].subjectID; // ID cua mon

            do 
            {
                cout << "GPA of the class: ";
                cin >> Learner.subjects[i].classGPA; // Diem trung binh mon cua ca lop
            }
            while(Learner.subjects[i].classGPA < 0 || Learner.subjects[i].classGPA > 10);
        }

        Learner.totalGPA = 0;

        for (int i = 0 ; i < Learner.numberOfSubject ; i++) {
            do 
            {
                cout << Learner.name << "'s " << Learner.subjects[i].name << " GPA: "; // Diem trung binh moi mon cua sinh vien
                cin >> Learner.subjectsGPA[i];
            }
            while(Learner.subjectsGPA[i] < 0 || Learner.subjectsGPA[i] > 10);
            Learner.totalGPA += Learner.subjectsGPA[i];
        }

        Learner.totalGPA /= Learner.numberOfSubject; // Diem trung binh tong cac mon cua sinh vien

        studentList[size] = Learner;
        size++;

        cout << "Continue ?(Y/N): "; 
        cin >> answer; // Tiep tuc nhap them hoc vien ?

        if (answer == 'N') {
            break;
        }
    }
}

// Ham hoan vi cho 2 sinh vien
void swap(Student &a, Student &b) {
    Student temp = a;
    a = b;
    b = temp;
}

// Ham tim vi tri ngay giua va chia mang
int partition(Student studentList[], int low, int high, int sortBy) {
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        bool shouldSwap = false;

        if (sortBy == 1) { // Neu la 1 la sap xep theo bang chu cai
            shouldSwap = strcmp(studentList[j].name, studentList[high].name) <= 0;
        } else if (sortBy == 2) { // Neu la 2 la sap xep theo GPA tang dan
            shouldSwap = studentList[j].totalGPA <= studentList[high].totalGPA;
        } else { // Neu la 3 thi la sap xep theo ID tang dan
            shouldSwap = strcmp(studentList[j].ID, studentList[high].ID) <= 0;
        }

        if (shouldSwap) {
            i++;
            swap(studentList[i], studentList[j]); // Goi ham hoan vi cho 2 sinh vien
        }
    }
    swap(studentList[i + 1], studentList[high]); // Goi ham hoan vi cho 2 sinh vien
    return (i + 1);
}

// Ham quick sort sap xep trat tu theo GPA tang dan , ID tang dan , thu tu bang chu cai
void quickSort(Student studentList[], int low, int high, int sortBy) {
    if (low < high) {
        int pi = partition(studentList, low, high, sortBy);
        quickSort(studentList, low, pi - 1, sortBy);
        quickSort(studentList, pi + 1, high, sortBy);
    }
}

// Ham in ra thong tin 1 hoc vien
void printOneStudent(Student Learner, int index) {
    // In ra danh sach
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    printf("| %s | %-13s | %-25s | %-7s | %-9s |\n", "No.", "ID", "Name", "Sex", "Total GPA");
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf |\n",index + 1,Learner.ID, Learner.name, Learner.sex, Learner.totalGPA);
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    cout << "\n";
}

// Ham in ra thong tin cac sinh vien
void printMoreStudent(Student studentList[] , int size) {
    // In ra danh sach
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    printf("| %s | %-13s | %-25s | %-7s | %-9s |\n", "No.", "ID", "Name", "Sex", "Total GPA");
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    
    for (int i = 0 ; i < size ; i++) {
        printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf |\n", i+1, studentList[i].ID, studentList[i].name, studentList[i].sex, studentList[i].totalGPA);
    }
    
    cout << "+-----+---------------+---------------------------+---------+-----------+\n";
    cout << "\n";
}

// Ham tim kiem 1 sinh vien
int search(Student studentList[] , int size , char searchID[10]) {
    int left = 0 , right = size - 1;

    while (left <= right) {
        int index = (left + right) / 2; // vi tri nam giua chu chot

        int studentID = atoi(studentList[index].ID);

        if (studentID == atoi(searchID)) { // So sanh ID
            return index; // Tra ve vi tri
        }

        if (studentID > atoi(searchID)) {
            right = index - 1;
        } else {
            left = index + 1;
        }
    }

    cout << "Student with ID " << searchID << " not found." << endl;
    return -1;
}

// Ham xoa sinh vien    
void Delete(Student studentList[] , int &size, char searchID[10]) {
    char doAdjust;
    do
    {
        cout << "Do you want to adjust?(Y/N): ";
        cin >> doAdjust; // Xac nhan chinh sua
        if (doAdjust != 'Y' && doAdjust != 'N') {
            cout << "It must be 'Y'(=Yes) or 'N'(=No)\n";
        }
    }
    while(doAdjust != 'Y' && doAdjust != 'N');

    if (doAdjust == 'Y') {
        int numericalOrder = search(studentList , size , searchID);

        char doDelete;
        do
        {
            cout << "Do you really want to delete this?(Y/N): ";
            cin >> doDelete; // Xac nhan quyen xoa
            if (doDelete != 'Y' && doDelete != 'N') {
                cout << "It must be 'Y'(=Yes) or 'N'(=No)\n";
            }
        }
        while(doDelete != 'Y' && doDelete != 'N');

        if (doDelete == 'Y') {
            for (int i = numericalOrder ; i < size - 1 ; i++) {
                studentList[i] = studentList[i+1]; // Cho phan tu hien tai bang phan tu ke tiep
            }
            size--; // Giam kich thuoc
            cout << "List after changing:\n";
            printMoreStudent(studentList , size);
        } else {
            return;
        }
    } else {
        return;
    }
}

// Ham sap xep theo diem trung binh
void inGPAOrder(Student studentList[], int size) {
    quickSort(studentList, 0, size - 1, 2); // Sap xep theo GPA
    cout << "List in greater GPA order:\n";
    printMoreStudent(studentList, size);
}

// Ham sap xep theo thu tu chu cai
void inNameOrder(Student studentList[], int size) {
    quickSort(studentList, 0, size - 1, 1); // Sap xep theo ten
    cout << "List in alphabetical order:\n";
    printMoreStudent(studentList , size);
}

/*Ngay thuc hien: 29/8/2023*/

// Ham in ra ket qua hoc tap cua sinh vien va cac sinh vien duoc hoc bong
void academicPerformanceList(Student studentList[] , int size) {
    quickSort(studentList , 0 , size - 1 , 2);

    cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
    printf("| %s | %-13s | %-25s | %-7s | %-6s | %-25s | %-13s | %-7s |\n", "No.", "ID", "Name", "Sex", "Total GPA", "Academic Performance", "Scholarship", "Relearn");
    cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
    for (int i = 0 ; i < size ; i++) {
        if (9.0 <= studentList[i].totalGPA) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n",i+1 ,studentList[i].ID, studentList[i].name, studentList[i].sex, studentList[i].totalGPA, "High distinction", "Qualified", "False");
            cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
        } else if (8.0 <= studentList[i].totalGPA && studentList[i].totalGPA < 9.0) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n",i+1 ,studentList[i].ID, studentList[i].name, studentList[i].sex, studentList[i].totalGPA, "Distinction", "Unqualified", "False");
            cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
        } else if (6.5 <= studentList[i].totalGPA && studentList[i].totalGPA < 8.0) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n",i+1 ,studentList[i].ID, studentList[i].name, studentList[i].sex, studentList[i].totalGPA, "Credit", "Unqualified", "False");
            cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
        } else if (5.0 <= studentList[i].totalGPA && studentList[i].totalGPA < 6.5) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n",i+1 ,studentList[i].ID, studentList[i].name, studentList[i].sex, studentList[i].totalGPA, "Strong pass", "Unqualified", "False");
            cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
        } else if (3.5 <= studentList[i].totalGPA && studentList[i].totalGPA < 5.0) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n",i+1 ,studentList[i].ID, studentList[i].name, studentList[i].sex, studentList[i].totalGPA, "Avarage", "Unqualified", "False");
            cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
        } else if (studentList[i].totalGPA < 3.5) {
            printf("| %-3d | %-13s | %-25s | %-7s | %-9.2lf | %-25s | %-13s | %-7s |\n",i+1 ,studentList[i].ID, studentList[i].name, studentList[i].sex, studentList[i].totalGPA, "Poor", "Unqualified", "True");
            cout << "+-----+---------------+---------------------------+---------+-----------+---------------------------+---------------+---------+\n";
        }
    }
}

/*Ngay thuc hien: 30/8/2023*/

// Ham in danh sach hoc vien theo hoc cac mon
void attend(Student studentList[] , int size) {
    char searchSubjectID[20];
    cout << "Search subject ID: ";
    cin >> searchSubjectID;

    for (int i = 0 ; i < size ; i++) {
        for (int j = 0 ; j < studentList[i].numberOfSubject ; i++) {
            for (int k = j + 1 ; k < studentList[i].numberOfSubject ; k++) {
                if (strcmp(studentList[i].subjects[j].subjectID , studentList[i].subjects[k].subjectID) < 0) {
                    swap(studentList[i].subjects[j], studentList[i].subjects[k]);
                }
            }
        }
    }

    cout << "Danh sach sinh vien hoc mon co ID: " << searchSubjectID << ":\n"; // In ra ten mon hoc
    cout << "+-----+---------------+---------------------------+---------+-------------+\n";
    printf("| %s | %-13s | %-25s | %-7s | %-10s |\n", "No.", "ID", "Name", "Sex", "Subject GPA");
    cout << "+-----+---------------+---------------------------+---------+-------------+\n";
    for (int i = 0 ; i < size ; i++) { // xet qua cac ID trong mang gradID
        for (int j = 0; j < studentList[i].numberOfSubject; j++) {
            if (strcmp(studentList[i].subjects[j].subjectID, searchSubjectID) == 0) {
                printf("| %-3d | %-13s | %-25s | %-7s | %-11.2lf |\n", i + 1, studentList[i].ID, studentList[i].name, studentList[i].sex, studentList[i].subjectsGPA[j]);
                cout << "+-----+---------------+---------------------------+---------+-------------+\n";
                break;
            }
        }
    }
    cout << "\n";
}

/*Ngay thuc hien 31/8/2023*/

//Ham cap nhat sinh vien
void updatedStudentInfor(Student studentList[] , int &size , char searchID[10]) {
    quickSort(studentList, 0, size - 1, 3);

    int index = search(studentList, size, searchID);

    cout << "Name: ";
    cin.ignore();
    cin.getline(studentList[index].name , 30); // Nhap ten

    cout << "ID: ";
    cin >> studentList[index].ID; // Nhap ID

    cout << "Sex: ";
    cin >> studentList[index].sex; // Nhap gioi tinh

    do 
    {
        cout << "Number of subjects that student attend: ";
        cin >> studentList[index].numberOfSubject; // Nhap so mon ma hoc vien tham gia
    }
    while(studentList[index].numberOfSubject <= 0 || studentList[index].numberOfSubject > MAX_SUBJECT_PER_PERSON);

    for (int i = 0 ; i < studentList[index].numberOfSubject ; i++) {

        cout << "Subject name: ";
        cin.ignore();
        cin.getline(studentList[index].subjects[i].name , 10);

        cout << "Subject ID: ";
        cin >> studentList[index].subjects[i].subjectID;

        do 
        {
            cout << "GPA of the class: ";
            cin >> studentList[index].subjects[i].classGPA;
        }
        while(studentList[index].subjects[i].classGPA < 0 || studentList[index].subjects[i].classGPA > 10);
    }

    studentList[index].totalGPA = 0;

    for (int i = 0 ; i < studentList[index].numberOfSubject ; i++) {
        do 
        {
            cout << studentList[index].name << "'s " << studentList[index].subjects[i].name << " GPA: ";
            cin >> studentList[index].subjectsGPA[i];
        }
        while(studentList[index].subjectsGPA[i] < 0 || studentList[index].subjectsGPA[i] > 10);
        studentList[index].totalGPA += studentList[index].subjectsGPA[i];
    }

    studentList[index].totalGPA = studentList[index].totalGPA / studentList[index].numberOfSubject;
}

// Ham in bieu do thong ke GPA mon hoc cua sinh vien so voi GPA mon hoc cua lop
void statistic(Student studentList[] , int size , char searchID[10]) {
    quickSort(studentList, 0, size - 1, 3);

    int index = search(studentList , size , searchID);

    for(int i = 0 ; i < studentList[index].numberOfSubject ; i++) {
        int toInt1 = studentList[index].subjectsGPA[i];
        int toInt2 = studentList[index].subjects[i].classGPA;

        if (toInt1 == toInt2) {
            cout << "Your subject GPA comparison with " << studentList[index].subjects[i].name << " GPA with " << toInt1 <<".x:\n";

            int dozens = toInt1;
            toInt1 = (int)(studentList[index].subjectsGPA[i] * 10) % 10;
            toInt2 = (int)(studentList[index].subjects[i].classGPA * 10) % 10;

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

            if (dozens == studentList[index].subjectsGPA[i]) {
                cout << "       " << studentList[index].subjectsGPA[i] << " ";
            } else {
                cout << "      " << studentList[index].subjectsGPA[i] << " ";
            }

            if (dozens == studentList[index].subjects[i].classGPA) {
                cout << "  " << studentList[index].subjects[i].classGPA << "      ";
            } else {
                cout << " " << studentList[index].subjects[i].classGPA << "      ";
            }

            cout << "\n";
        } else {
            cout << "Your subject GPA comparison with " << studentList[index].subjects[i].name << " GPA\n";

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

            if (toInt1 == studentList[index].subjectsGPA[i]) {
                cout << "       " << studentList[index].subjectsGPA[i] << "  ";
            } else {
                cout << "      " << studentList[index].subjectsGPA[i] << " ";
            }

            if (toInt2 == studentList[index].subjects[i].classGPA) {
                cout << "  " << studentList[index].subjects[i].classGPA << "      ";
            } else {
                cout << " " << studentList[index].subjects[i].classGPA << "      ";
            }

            cout << "\n";
        }
    }
}