#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printHighestScore();
    void printGrade();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles() {
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as an input stream.
    ifstream stfile("./Students.txt");

    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;
        //if (!line.empty() && line.back() == '\r')line.pop_back();//此处两行为mac用，交文件时删掉！！！！！
        // The bufv vector stores each column in the line.
        bufv.clear();
        // Split the line into columns.
        //   pos1: beginning of the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);


        studentVec.push_back(st);
    }
    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    ifstream clfile("./Classes.txt");

    while (getline(clfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;
        //if (!line.empty() && line.back() == '\r')line.pop_back();//此处两行为mac用，交文件时删掉！！！！！
        // The bufv vector stores each column in the line.
        //bufv.clear();
// Split the line into columns.

        if(line[0]=='C'&&line[1]=='l'&&line[2]=='a'&&line[3]=='s'&&line[4]=='s'){
            clsname=line.substr(6,string::npos);
        }
        if(line.substr(0,6)=="Points"){
            point=line[7]-'0';
            cl=new Class(clsname,point);
            while(getline(clfile,line)){
                if(line.empty())break;
                else{
                    //if (!line.empty() && line.back() == '\r'){line.pop_back();if(line.empty())break;}//此处两行为mac用，交文件时删掉！！！！！
                    for(std::vector<Student *>::iterator it=studentVec.begin();
                    it!=studentVec.end();
                    it++){
                        if(line==(*it)->id){
                            Student* tmp=*it;
                            cl->addStudent(*tmp);
                            (*it)->addClass(cl);
                            break;
                        }
                    }
                }
            }
            classVec.push_back(cl);
        }
    }
    clfile.close();
}
void AppX::inputScore()
{
    // TODO: implement inputScore.
    // Hint: Take a look at printHighestScore().
    string sbuf;
    Class *cl;
    StudentWrapper *st;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }
        while (true) {
            cout << "Please input the student id and score(or input q to quit): ";
            size_t pos1,pos2;
            pos1 = 0;
            string line;
            cin>>line;
            string stu,sco;
            double inputscore;
            //while (true) {
                if(line=="q")break;
                //bool flag=true;
                pos2 = line.find(',', pos1 + 1);
                stu=line.substr(pos1, pos2 - pos1);
                sco=line.substr(pos2 + 1, string::npos);
                inputscore= stod(sco);
                /*if(sco[1]=='\0'||sco[2]=='\0'||sco[3]=='\0')flag=false;
                if(flag)
                {
                    cout<<"Wrong score!"<<endl;
                    //flag=false;
                    continue;
                }
                if(sco[1]=='\0'){

                    if(sco[0]-'0'>=0&&sco[0]-'0'<=9)
                        inputscore=sco[0]-'0';
                    /*else{
                        cout<<"Wrong score!"<<endl;
                        //flag=false;
                        continue;
                    }
                }
                if(sco[2]=='\0'&&sco[1]!='\0')
                {
                    if((sco[0]-'0'>=0&&sco[0]-'0'<=9)&&(sco[1]-'0'>=0&&sco[1]-'0'<=9)){
                        inputscore=(sco[0]-'0')*10+sco[1]-'0';
                    }
                    else{
                        cout<<"Wrong score!"<<endl;
                        //flag=false;
                        continue;
                    }
                }
                if(sco[3]=='\0'&&sco[2]!='\0'&&sco[1]!='\0')
                {
                    if(sco=="100")
                        inputscore=100;
                    else
                    {
                        cout<<"Wrong score!"<<endl;
                        //flag=false;
                        continue;
                    }
                }
                if(inputscore<0||inputscore>100)
                {
                    cout<<"Wrong score!"<<endl;
                    //flag=false;
                    continue;
                }
                */
                try {
                    (*cl).getStudentWrapper(stu).setScore(inputscore);
                }
                catch(const char* err) {
                    if(err=="Invalid Score!"){
                        cout<<"Wrong score!"<<endl;
                        continue;
                    }
                    else{
                        cout<<"No match student!"<<endl;
                        continue;
                    }
                }
            //}
        }
    }
}
/*for (vector<StudentWrapper>::iterator it = cl->students.begin(); it != cl->students.end(); it++) {
    if (it->id == inputString) {
        cout<<it->toString();
        cout << "please input the score: ";
        double inputScore;
        string stringA;
        cin>>stringA;
        if(stringA=="q")
            break;
        bool flag1=true;
        if(stringA[1]=='\0'||stringA[2]=='\0'||stringA[3]=='\0')
        flag1=false;

        try{it->setScore(inputScore);}
        catch(char const *s2){
            cout<<"Wrong score!"<<endl;
        }
        flag = false;

        continue;
        }
    }

    if (flag == true) {
        cout << "No match student!" << endl;
        continue;
    }
*/

void AppX::printHighestScore()
{
    string sbuf;
    Class *cl;
    double highest;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class*>::iterator it = classVec.begin();
                it != classVec.end();
                ++ it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        highest = cl->getHighestScore();
        cout << setiosflags(ios::fixed) << setprecision(2)<< "The highest score is: " << highest << endl;
    }
}

void AppX::printGrade()
{
    // TODO: implement printGrade.
    // Hint: Take a look at printHighestScore().
    string sbuf;
    Student *st;
    double gpa,avg;

    while (true) {
        cout << "Please input the student id (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        st = nullptr;
        for (vector<Student*>::iterator it = studentVec.begin();
            it != studentVec.end();
            ++ it) {
            if ((*it)->id == sbuf) {
                st = *it;
                break;
            }
        }
        if (st == nullptr) {
            cout << "No match student!" << endl;
            continue;
        }
        gpa=st->getGpa();
        avg=st->getAvgScore();
        cout<<"GPA,AVG = ";
        cout << setiosflags(ios::fixed) << setprecision(2)<<gpa;
        cout<<",";
        cout << setiosflags(ios::fixed) << setprecision(2)<<avg;
        cout<<endl;
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute highest score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printHighestScore();
        } else if (cmd == 'g') {
            printGrade();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
