#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human(const string& t = "human", const string& n = "person") : type(t), Name(n) {
    }
    virtual void Walk(const string& destination) const = 0;
    const string type;
    const string Name;
};


class Student : public Human {
public:
    Student(const string& name, const string& favouriteSong)
    : Human("Student", name), FavouriteSong(favouriteSong) {
    }

    void Learn() const {
        Print();
        cout << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Print();
        cout << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        Print();
        cout << " sings a song: " << FavouriteSong << endl;
    }

    void Print() const {
        cout << "Student: " << Name;
    }

public:
    const string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) : Human("Teacher", name), Subject(subject) {
    }

    void Teach() const {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }


    void Walk(const string& destination) const override {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

public:
    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(const string& name) : Human("Policeman", name) {
    }

    void Check(const Human& human) const {
        cout << "Policeman: " << Name << " checks "<< human.type <<". "<<human.type
             <<"'s name is: " << human.Name << endl;
    }

    void Walk(const string& destination) const override{
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
};


void VisitPlaces(const Human& human, const vector<string>& places) {
    for (const auto& p : places) {
        human.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
