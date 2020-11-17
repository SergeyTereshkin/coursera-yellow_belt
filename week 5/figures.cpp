#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <memory>
#include <iomanip>
#include <vector>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;
    virtual float Area() const = 0;
    virtual float Perimeter() const = 0;
};

class Triangle : public Figure {
public:
    Triangle(const string& new_name, const int& new_fside, const int& new_sside, const int& new_tside) {
        name = new_name;
        first_side = new_fside;
        second_side = new_sside;
        third_side = new_tside;
    }
    string Name() const override {
        return name;
    }
    float Perimeter() const override {
        return static_cast<float>(first_side + second_side + third_side);
    }
    float Area() const override {
        auto p = Perimeter() / 2;
        float area = sqrt(p * (p - first_side) * (p - second_side) * (p - third_side));
        return area;
    }

private:
    string name;
    int first_side;
    int second_side;
    int third_side;
};

class Circle : public Figure {
public:
    Circle(const string& new_name, const int& new_radius) {
        name = new_name;
        radius = new_radius;
    }
    string Name() const override {
        return name;
    }
    float Perimeter() const override {
        return 2 * 3.14 * radius;
    }
    float Area() const override {
        return 3.14 * radius * radius;
    }
private:
    string name;
    int radius;
};

class Rect : public Figure {
public:
    Rect(const string& new_name, const int& new_first_side, const int& new_second_side) {
        name = new_name;
        first_side = new_first_side;
        second_side = new_second_side;
    }
    string Name() const override {
        return name;
    }

    float Perimeter() const override {
        return static_cast<float>(2 * first_side + 2 * second_side);
    }

    float Area() const override {
        return static_cast<float>(first_side * second_side);
    }
private:
    string name;
    int first_side;
    int second_side;
};


shared_ptr<Figure> CreateFigure(istringstream& is) {
    string name;
    is >> name;
    int x, y, z;
    is >> x;
    if (is.eof()) {
        shared_ptr<Circle> c = make_shared<Circle>(name, x);
        return c;
    } else {
        is >> y;
        if (is.eof()) {
            shared_ptr<Rect> r = make_shared<Rect>(name, x, y);
            return r;
        } else {
            is >> z;
            shared_ptr<Triangle> tr = make_shared<Triangle>(name, x, y, z);

            return tr;
        }
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
