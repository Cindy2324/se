#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:
    const std::string name;
    const std::string year;
    const enum Degree degree;
protected:
    std::vector<Class*> classes;
public:
    const std::string id;
    std::string toString() const;
    void addClass(Class* c){
        classes.push_back(c);
    };
    virtual double getGpa()=0;
    virtual double getAvgScore()=0;
    Student(const std::string& col1,const std::string& col2,const std::string& col3,const Degree d):id(col1),name(col2),year(col3),degree(d){
    }
};

// TODO: implement class Graduate.
class Graduate:public Student{
public:
    Graduate(const std::string& col1,const std::string& col2,const std::string& col3)
        : Student(col1,col2,col3,graduate){}
    double getGpa();
    double getAvgScore();

};

// TODO: implement class Undergraduate.
class Undergraduate:public Student{
public:
    Undergraduate(const std::string& col1,const std::string& col2,const std::string& col3)
            : Student(col1,col2,col3,undergraduate){}
    double getGpa();
    double getAvgScore();
};

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error
    StudentWrapper(const std::string &id, const Student &student): id(id),student (student){}

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Invalid Score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
