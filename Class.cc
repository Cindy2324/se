#include "Class.h"
#include <string>
#include "Student.h"

void Class::addStudent(const Student& st) {
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper& Class::getStudentWrapper(const std::string& studentId) {
    for (std::vector<StudentWrapper>::iterator it = students.begin();
            it != students.end();
            ++ it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No match student!";
}
double Class::getHighestScore() {
    // TODO implement getHighestScore
    double max=0;
    int students_num=0;
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it){
        if(max<it->getScore()) max=it->getScore();
        students_num++;
    }
    if (students_num) return max;
    return 0.0;
}
