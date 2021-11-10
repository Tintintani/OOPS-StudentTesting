#include <climits>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>


using namespace std;

class User {
   private:                                             // User Class
    char username[25];
    char password[25];
    char name[25];
    public:
        void setUsername(char username[]){
            strcpy(this->username, username);
        };
        void setPassword(char password[]){
            strcpy(this->password, password);
        };
        void setName(char name[]){
            strcpy(this->name, name);
        };
        char *getUsername() { return username; }
        char *getPassword() { return password; }
};

class Student : public User {
   private:
    int rollNo;                                        // Student Class Inherited from User
    int cls;
    char sec;
    int marks[5];
    public:
        Student(){};
        Student(char username[], char password[], char name[], int rollNo, int cls, char sec) {
            setUsername(username);
            setPassword(password);
            setName(name);
            this->cls = cls;
            this->rollNo = rollNo;
            this->sec = sec;
            for (int i = 0; i < 5; i++) marks[i] = INT_MIN;
        }
        void studentPage();
        void showProfile();
        void selectPaper();
        void checkProgress();
};

class Teacher : public User {
   public:
    Teacher(){};
    Teacher(char username[], char password[], char name[]){
         setUsername(username);
         setPassword(password);
         setName(name);
    }
    void teacherPage();                                // Teacher Class Inherited from User
    void makePaper();
    void selectPaper();
    void studentResults();
};

class QuestionPaper;
class Question {
   private:
    int correctAns, ans;
    char name[30];
    char option[4][75];                                // Question Class, for each question
    char question[150];

   public:
    void setQuestion();
    void putQuestionTeacher();
    void putQuestionStudent();
    friend class QuestionPaper;
    friend class Teacher;
};

class QuestionPaper {
   private:
    Question questions[10];                            // QuestionPaper class, contains an array of question class Objects

   public:
    char name[30];
    void getPaperStudent();
    void getPaperTeacher();
    int calculateMarks();
    friend class Teacher;
};

vector<Student> students;                   // Vector to store data of students after reading from file
vector<Teacher> teachers;                   // Vector to store data of teachers after reading from file
vector<QuestionPaper> questionpapers;       // Vector to store data of questionpapers after reading from file

void frontPage();
void signUpPage();
void loginPage();
void stuSignUp();
void stuLogin();
void tchSignUp();
void tchLogin();
void Loading();
void readFile();
void writeFile(Student s);
void writeFile(Teacher t);
void writeFile(QuestionPaper q);
void updateFile();

int main(void) {
    frontPage();
    return 0;
}

void frontPage() {                           // Function to Display Front Page
    ifstream fin;
    fin.open("Logo.txt", ios ::in);
    char ch;

    while (!fin.eof()){
        fin.get(ch);
        cout << ch;
    }
    fin.close();
    cin.get();
    
    system("cls");
    readFile();                         // Reads file when program starts
    
    while (true) {
        system("cls");
        cout << "1. Login" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Choice: ";
        int option;
        cin >> option;

        if (option == 1)
            loginPage();               // Login Page
        else if (option == 2)
            signUpPage();              // Sign Up Page
        else if (option == 3)
            exit(0);
        else
            cout << "Wrong Choice" << endl;
    }
}

void signUpPage() {
    system("cls");
    cout << "Sign Up as: " << endl;
    cout << "1. Student" << endl;
    cout << "2. Teacher" << endl;
    cout << "3. Go Back" << endl;
    cout << "Enter Choice: ";
    int option;

    while (true) {
        cin >> option;

        if (option == 1) {
            stuSignUp();                // Signing Up as Student
            return;
        }

        else if (option == 2) {
            tchSignUp();                // Signing Up as Teacher
            return;
        }
        
        else if (option == 3)
            return;

        else
            cout << "Wrong Input!" << endl;
    }
}

void loginPage() {
    int option;

    while (true) {
        system("cls");
        cout << "Login as: " << endl;
        cout << "1. Student" << endl;
        cout << "2. Teacher" << endl;
        cout << "3. Go Back" << endl;
        cout << "Enter Choice: ";
        cin >> option;

        if (option == 1) {
            stuLogin();                       // Logging in as Student
            return;
        }

        else if (option == 2) {
            tchLogin();                       // Logging in as Teacher
            return;
        }

        else if (option == 3)
            return;

        else
            cout << "Wrong Input!" << endl;
    }
}

void stuSignUp() {                                        // Student Sign Up Page
    system("cls");
    char name[25], password[25], username[25], sec;
    int rollNo, cls;
    cout << "Input exit to Go to Front Page" << endl;
    cout << "Enter Your Name: ";                          // Getting Student Details
    cin >> name;
    if (strcmp(name, "exit") == 0)
            return;
    cout << "Enter Roll Number: ";
    cin >> rollNo;
    bool userNameTaken;

    do {
        userNameTaken = false;
        cout << "Create User Name: ";
        cin >> username;
        for (int i = 0; i < students.size(); i++) {
            if (strcmp(students[i].getUsername(), username) == 0) {   // Checking if entered username is already present
                cout << "Entered Username is already taken, please choose another" << endl;                
                Sleep(1000);                
                userNameTaken = true;
                break;
            }
        }
    } while (userNameTaken);

    cout << "Create Password: ";
    cin >> password;
    cout << "Enter Class: ";
    cin >> cls;
    cout << "Enter Section: ";
    cin >> sec;
    Student s(username, password, name, rollNo, cls, sec);
    writeFile(s);                                       // Appending Object Data to File
}

void stuLogin() {                                        // Student Login Page
    string userid, password;
    int currentStudent;
    bool loginSuccessful = false;

    do {
        system("cls");
        cout << "Student Login\n" << endl;
        cout << "Input exit to Go to Front Page" << endl;
        cout << "Enter Username: ";
        cin >> userid;
        if (userid == "exit")
            return;
        cout << "Enter Password: ";
        cin >> password;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getUsername() == userid &&           // Matching Username and Password
                students[i].getPassword() == password) {
                cout << "Login Successful!" << endl;
                Sleep(1000);
                currentStudent = i;
                loginSuccessful = true;
                break;
            }
        }

        if (!loginSuccessful) {
            cout << "Invalid Username or Password" << endl;
            Sleep(1000);
        }

    } while (!loginSuccessful);

    system("cls");
    Loading();

    cout << "Welcome " << students[currentStudent].getUsername() << endl;
    Sleep(1000);
    students[currentStudent].studentPage();
    return;
}

void tchSignUp() {                                      // Teacher Sign Up Page
    system("cls");
    char name[25], password[25], username[25];
    cout << "Input exit to Go to Front Page" << endl;
    cout << "Enter Your Name: ";                        // Getting Teacher Details
    cin >> name;
    if (strcmp(name, "exit") == 0){
        return;
    }

    bool userNameTaken;
    do {
        userNameTaken = false;
        cout << "Create User Name: ";
        cin >> username;
        for (int i = 0; i < teachers.size(); i++) {
            if (strcmp(teachers[i].getUsername(), username) == 0) {    // Checking if entered username is already present
                cout << "Entered Username is already taken, please choose another" << endl;
                Sleep(1000);
                userNameTaken = true;
                break;
            }
        }
    } while (userNameTaken);

    cout << "Create Password: ";
    cin >> password;
    Teacher t(username, password, name);

    writeFile(t);                                       // Appending Object Data to File
}

void tchLogin() {                                       // Teacher Login Page
    string userid, password;
    int currentTeacher;
    bool loginSuccessful = false;

    do {
        system("cls");
        cout << "Teacher Login\n" << endl;
        cout << "Input exit to Go to Front Page" << endl;
        cout << "Enter Username: ";
        cin >> userid;
        if (userid == "exit")
            return;
        cout << "Enter Password: ";
        cin >> password;
        for (int i = 0; i < teachers.size(); i++) {
            if (teachers[i].getUsername() == userid &&
                teachers[i].getPassword() == password) {                // Matching Username and Password
                cout << "Login Successful!" << endl;
                Sleep(1000);
                currentTeacher = i;
                loginSuccessful = true;
                break;
            }
        }

        if (!loginSuccessful) {
            cout << "Invalid Username or Password" << endl;
            Sleep(1000);
        }

    } while (!loginSuccessful);

    system("cls");
    Loading();

    cout << "Welcome " << teachers[currentTeacher].getUsername() << endl;
    Sleep(1000);
    teachers[currentTeacher].teacherPage();
    return;
}

void Student :: studentPage() {                          // Student Page
    system("cls");
    readFile();
    int option;

    while (true) {
        system("cls");
        showProfile();
        cout << "1. Attempt Papers" << endl;
        cout << "2. Check Your Progress" << endl;
        cout << "3. Log Out" << endl;
        cout << "Choose Option: ";
        cin >> option;

        if (option == 1)
            selectPaper();

        else if (option == 2)
            checkProgress();

        else if (option == 3)
            return;

        else {
            cout << "Wrong Input" << endl;
            Sleep(500);
        }
    }
    return;
}

void Student :: showProfile() {                   // Shows Detailed Profile of Student
    cout << "Name    : " << getUsername() << endl;
    cout << "Roll No : " << rollNo << endl;
    cout << "Class   : " << cls << endl;
    cout << "Section : " << sec << endl;
    return;
}

void Student :: selectPaper() {                    // Selecting Paper to attempt
    system("cls");

    if (questionpapers.size() == 0) {
        cout << "No Question Papers created till yet" << endl;
        Sleep(1000);
        return;
    }
    cout << "1. Papers: " << endl;
    int i;
    for (i = 0; i < questionpapers.size(); i++)
        cout << "\t" << i + 1 << " " << questionpapers[i].name << endl;
    cout << i + 1 << ". Go Back" << endl;
    cout << endl;
    int option;

    while (true) {
        cout << "Choose Paper: ";
        cin >> option;

        if (option == i + 1)
            return;

        if (option - 1 < questionpapers.size()) {
            cout << "All the Best!" << endl;
            Sleep(100);
            system("cls");
            questionpapers[option - 1].getPaperStudent();       // Displays selected paper to student
            break;
        } 

        else {
            cout << "Wrong Input!";
            Sleep(1000);
        }

        system("cls");
    }
    system("cls");
    marks[option - 1] = questionpapers[option - 1].calculateMarks();   // Updating Marks
    cout << "Hope Your Paper Went Well!" << endl;
    cout << "You can check you marks at the portal" << endl;

    updateFile();                          // Updating File after updating marks
    Sleep(500);
    return;
}

void Student :: checkProgress() {            // Displays progress of Student
    fflush(stdin);

    for (int i = 0; i < 5; i++) {
        cout << "Paper " << i + 1 << ": ";
        if (marks[i] == INT_MIN)
            cout << "Not Attempted" << endl;
        else
            cout << marks[i] << endl;
    }

    cin.get();
    return;
}

void Teacher :: teacherPage() {                          // Teacher Page
    readFile();
    int option;
    
    while (true) {
        system("cls");
        cout << "Name    : " << getUsername() << endl;
        cout << "1. See Papers" << endl;
        cout << "2. Create Paper" << endl;
        cout << "3. See Students Progress" << endl;
        cout << "4. Log Out" << endl;
        cout << "Choose Option: ";
        cin >> option;
        if (option == 1)
            selectPaper();

        else if (option == 2)
            makePaper();

        else if (option == 3)
            studentResults();

        else if (option == 4)
            return;

        else {
            cout << "Wrong Input" << endl;
            Sleep(1000);
        }
    }

    return;
}

void Teacher :: selectPaper() {               //Teachers able to see all Question Papers
    system("cls");

    if (questionpapers.size() == 0) {
        cout << "No Question Papers created till yet" << endl;
        Sleep(1000);
        return;
    }

    cout << "1. Papers: " << endl;
    int i;
    for (i = 0; i < questionpapers.size(); i++)             // Displays names of all Question Paper present
        cout << "\t" << i + 1 << " " << questionpapers[i].name << endl;
    cout << i + 1 <<". Go Back" << endl;
    cout << endl;
    int option;

    while (true) {
        cout << "Choose Paper: ";
        cin >> option;

        if (option == i + 1)
            return;

        if (option - 1 < questionpapers.size()) {
            questionpapers[option - 1].getPaperTeacher();   // Displays the Question Paper to Teacher
            break;
        } 

        else
            cout << "Wrong Input!";
        system("cls");
    }

    return;
}

void Teacher :: makePaper() {                  // Creating Question Paper
    fflush(stdin);
    QuestionPaper qp;
    system("cls");
    cout << "Enter Paper Name: ";
    cin >> qp.name;

    for (int i = 0; i < 10; i++) {
        fflush(stdin);
        cout << "Question " << i + 1 << ": ";
        strcpy(qp.questions[i].name, qp.name);
        qp.questions[i].setQuestion();
    }

    qp.getPaperTeacher();
    writeFile(qp);

    return;
}

void Teacher :: studentResults() {              // Teacher able to see Marks of Students
    system("cls");
    for (int i = 0; i < students.size(); i++) {
        students[i].showProfile();
        cout << endl;

        students[i].checkProgress();
        cout << endl;
        system("cls");
    }
    return;
}

void Question :: setQuestion() {                            // Setting Question
    fflush(stdin);
    cin.getline(question, 150);
    for (int i = 0; i < 4; i++) {
        fflush(stdin);
        cout << "Enter Option " << i + 1 << " : ";
        cin.getline(option[i], 75);
    }
    cout << "Enter Correct answer: ";
    cin >> correctAns;                                   // Inputting Correct Answer

    return;
}

void Question :: putQuestionStudent() {                         // Displays Current Question To Student
    cout << question << endl;
    for (int i = 0; i < 4; i++) cout << i + 1 << ". " << option[i] << endl;
    fflush(stdin);
    cout << "Enter Your Choice: (1/2/3/4) 0 to Skip Question" << endl;  // Inputting Answer
    cin >> ans;

    return;
}

void Question :: putQuestionTeacher() {
    cout << question << endl;                                   // Displays Current Question to Teacher
    for (int i = 0; i < 4; i++) cout << i + 1 << ". " << option[i] << endl;
    cout << "Correct Answer: " << correctAns << endl;          // Show Correct Answer

    return;
}

void QuestionPaper :: getPaperStudent() {            // To show Paper to Student
    for (int i = 0; i < 10; i++) {                   // Doesn't Show Correct Answer
        cout << name << endl;
        cout << "Q. " << i + 1 << ": ";
        questions[i].putQuestionStudent();
        system("cls");
    }

    return;
}

void QuestionPaper :: getPaperTeacher() {             // To show Paper to Teacher
    system("cls");
    fflush(stdin);
    for (int i = 0; i < 10; i++) {                    // Shows the Correct Answer
        cout << name << endl;
        cout << "Q. " << i + 1 << ": ";
        questions[i].putQuestionTeacher();
        cin.get();
        system("cls");
    }

    return;
}

int QuestionPaper :: calculateMarks() {        // Calculating Marks for the Paper attempted
    int marks = 0;
    for (int i = 0; i < 10; i++) {
        if (questions[i].ans == 0)
            continue;

        else if (questions[i].ans == questions[i].correctAns)
            marks += 4;

        else
            marks -= 1;
    }
    return marks;
}

void readStudents() {                 // Reading Students from Student.dat file
    students.clear();
    ifstream fin("Student.dat", ios::in | ios::binary);

    while (!fin.eof()) {
        Student s;                                   // Reading Each individual Student Object
        fin.read((char *)&s, sizeof(Student));       // from Student.dat file
        students.push_back(s);                       // Pushing read student object to vector 
    }
    fin.close();
}

void readTeachers() {                  // Reading Teachers from Teacher.dat file
    teachers.clear();
    ifstream fin("Teacher.dat", ios::in | ios ::binary);

    while (!fin.eof()) {
        Teacher t;                                   // Reading Each individual Teacher Object
        fin.read((char *)&t, sizeof(Teacher));       // from Teacher.dat file
        teachers.push_back(t);                       // Pushing read teacher object to vector
    }
    fin.close();
}

void readQuestionPaper() {              // Reading QuestionPapers from QuestionPaper.dat file
    questionpapers.clear();
    ifstream fin("QuestionBank.dat", ios :: in | ios::binary);

    while (!fin.eof()) {
        QuestionPaper q;                                   // Reading Each individual Question Paper Object
        fin.read((char *)&q, sizeof(QuestionPaper));       // from QuestionPaper.dat file
        questionpapers.push_back(q);                       // Pushing read QuestionPaper Object to vector
    }
    fin.close();
}

void readFile() {
    readStudents();
    readTeachers();
    readQuestionPaper();

    // Removing Extra Object read from file
    if (students.size()) students.pop_back();          
    if (teachers.size()) teachers.pop_back();
    if (questionpapers.size()) questionpapers.pop_back();

    return;
}

void writeFile(Student s) {                         // Writing Student Object to Student.dat file
    ofstream fout;
    fout.open("Student.dat", ios::app | ios::binary);
    fout.write((char *)&s, sizeof(Student));         
    fout.close();
    cout << "\nAccount Added!" << endl;
    Sleep(1000);
    readFile();              // Read Files again after update 
    return;
}

void writeFile(Teacher t) {                         // Writing Teacher Object to Teacher.dat file
    ofstream fout;
    fout.open("Teacher.dat", ios::app | ios :: binary);
    fout.write((char *)&t, sizeof(Teacher));
    fout.close();
    cout << "\nAccount Added!" << endl;

    Sleep(1000);
    readFile();                             // Read Files again after update 
    return;
}

void writeFile(QuestionPaper qp){           // Writing QuestionPaper Object to QuestionPaper.dat file
    cout << endl;
    ofstream fout;
    fout.open("QuestionBank.dat", ios::app | ios :: binary);
    fout.write((char *)&qp, sizeof(QuestionPaper));
    fout.close();
    cout << "\nPaper Added!" << endl;

    Sleep(1000);
    readFile();              // Read Files again after update 
    return;
}

void updateFile() {                     // Updating Files
    ofstream fout;

    Sleep(1000);
    fout.open("Student.dat", ios::out | ios:: binary);
    for (int i = 0; i < students.size(); i++)                 // Updating Students
        fout.write((char *)&students[i], sizeof(Student));
    fout.close();
    fout.open("Teacher.dat", ios::out | ios :: binary);
    for (int i = 0; i < teachers.size(); i++)                 // Updating Teachers
        fout.write((char *)&teachers[i], sizeof(Teacher));
    fout.close();
    return;
}

void Loading(){                         // Loading Animation
    string array[5] = {" ", ".", "..", "...", "...."};
    int j = 0;
    for (int i = 0; i < 20; i++){
        cout << "Loading: ";
        cout << array[j++ % 5];
        Sleep(100);
        if (i > 10 && i <=15)
            Sleep(50);
        if (i > 15)
            Sleep(25);
        system("cls");
    }
    system("cls");
}