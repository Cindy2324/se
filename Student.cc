#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.
    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
    return "";
}
// TODO: implement functions which are declared in Student.h.
double Graduate::getGpa() {
    int points = 0;
    double gpa = 0.0;
    double score;
    for (std::vector<Class *>::iterator it = classes.begin();
         it != classes.end();
         ++it) {
        score = (*it)->getStudentWrapper(id).getScore();
        switch(int(score/10)){
            case 10:
            case 9:
                gpa+=4.0*(*it)->point;
                break;
            case 8:
                gpa+=3.5*(*it)->point;
                break;
            case 7:
                gpa+=3.0*(*it)->point;
                break;
            case 6:
                gpa+=2.5*(*it)->point;
                break;
            default:
                gpa+=2.0*(*it)->point;
        }
        points+=(*it)->point;
    }
    gpa = gpa/points;
    return gpa;
}


double Graduate::getAvgScore() {
    int points = 0;
    double scores = 0.0;
    double score;
    for (std::vector<Class *>::iterator it = classes.begin();
         it != classes.end();
         ++it) {
        score = (*it)->getStudentWrapper(id).getScore();
        scores += score * (*it)->point;
        points+=(*it)->point;
    }
    scores = scores/points;
    return scores;
}


double Undergraduate::getGpa() {
    int points = 0;
    double gpa = 0.0;
    double score;
    for (std::vector<Class *>::iterator it = classes.begin();
         it != classes.end();
         ++it) {
        score = (*it)->getStudentWrapper(id).getScore();
        gpa += score * (*it)->point / 20;
        points += (*it)->point;
    }
    gpa=gpa/points;
    return gpa;
}

double Undergraduate::getAvgScore() {
    int points = 0;
    double scores = 0.0;
    double score;
    for (std::vector<Class *>::iterator it = classes.begin();
         it != classes.end();
         ++it) {
        score = (*it)->getStudentWrapper(id).getScore();
        scores += score * (*it)->point;
        points+=(*it)->point;
    }
    scores = scores/points;
    return scores;
}
