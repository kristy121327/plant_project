#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>
#include <locale>

using namespace std;

enum class Month {
    JAN, FEB, MAR, APR, MAY, JUN,
    JUL, AUG, SEP, OCT, NOV, DEC
};

string extractQuoted(const string& s) {
    size_t p1 = s.find('\'');
    size_t p2 = s.find('\'', p1 + 1);
    if (p1 != string::npos && p2 != string::npos)
        return s.substr(p1 + 1, p2 - p1 - 1);
    return "";
}

Month stringToMonth(const string& m) {
    if (m == "ЯНВАРЬ") return Month::JAN;
    if (m == "ФЕВРАЛЬ") return Month::FEB;
    if (m == "МАРТ") return Month::MAR;
    if (m == "АПРЕЛЬ") return Month::APR;
    if (m == "МАЙ") return Month::MAY;
    if (m == "ИЮНЬ") return Month::JUN;
    if (m == "ИЮЛЬ") return Month::JUL;
    if (m == "АВГУСТ") return Month::AUG;
    if (m == "СЕНТЯБРЬ") return Month::SEP;
    if (m == "ОКТЯБРЬ") return Month::OCT;
    if (m == "НОЯБРЬ") return Month::NOV;
    if (m == "ДЕКАБРЬ") return Month::DEC;
    throw invalid_argument("Неизвестный месяц");
}

string monthToString(Month m) {
    switch (m) {
    case Month::JAN: return "Январь";
    case Month::FEB: return "Февраль";
    case Month::MAR: return "Март";
    case Month::APR: return "Апрель";
    case Month::MAY: return "Май";
    case Month::JUN: return "Июнь";
    case Month::JUL: return "Июль";
    case Month::AUG: return "Август";
    case Month::SEP: return "Сентябрь";
    case Month::OCT: return "Октябрь";
    case Month::NOV: return "Ноябрь";
    case Month::DEC: return "Декабрь";
    throw invalid_argument("Неизвестный месяц");
    }
}

class Plant {
protected:
    string name;

public:
    Plant(const string& n) : name(n) {}
    virtual ~Plant() = default;

    virtual string toString() const = 0;
    virtual bool matches(const string& condition) const = 0;

    void print() const {
        cout << toString() << endl;
    }
};

class Tree : public Plant {
    long age;

public:
    Tree(const string& n, long a) : Plant(n), age(a) {}

    string toString() const override {
        return "Дерево: Название = " + name + ", Возраст = " + to_string(age);
    }

    bool matches(const string& c) const override {
        if (c.find("название") != string::npos) {
            return name == extractQuoted(c);
        }
        if (c.find("возраст") != string::npos) {
            if (c.find(">") != string::npos)
                return age > stol(c.substr(c.find(">") + 1));
            if (c.find("<") != string::npos)
                return age < stol(c.substr(c.find("<") + 1));
            if (c.find("==") != string::npos)
                return age == stol(c.substr(c.find("==") + 2));
        }
        return false;
    }
};

class Shrub : public Plant {
    Month floweringMonth;

public:
    Shrub(const string& n, Month m) : Plant(n), floweringMonth(m) {}

    string toString() const override {
        return "Кустарник: Название = " + name +
            ", Месяц цветения = " + monthToString(floweringMonth);
    }

    bool matches(const string& c) const override {
        if (c.find("название") != string::npos) {
            return name == extractQuoted(c);
        }
        if (c.find("месяц") != string::npos && c.find("==") != string::npos) {
            string v = c.substr(c.find("==") + 2);
            v.erase(remove(v.begin(), v.end(), ' '), v.end());
            return floweringMonth == stringToMonth(v);
        }
        return false;
    }
};

class Cactus : public Plant {
    double spineLength;

public:
    Cactus(const string& n, double l) : Plant(n), spineLength(l) {}

    string toString() const override {
        return "Кактус: Название = " + name +
            ", Длина колючек = " + to_string(spineLength);
    }

    bool matches(const string& c) const override {
        if (c.find("название") != string::npos) {
            return name == extractQuoted(c);
        }
        if (c.find("длина") != string::npos) {
            if (c.find(">") != string::npos)
                return spineLength > stod(c.substr(c.find(">") + 1));
            if (c.find("<") != string::npos)
                return spineLength < stod(c.substr(c.find("<") + 1));
            if (c.find("==") != string::npos)
                return spineLength == stod(c.substr(c.find("==") + 2));
        }
        return false;
    }
};

class PlantContainer {
    vector<unique_ptr<Plant>> plants;

public:
    void add(unique_ptr<Plant> p) {
        plants.push_back(std::move(p));
    }

    void remove(const string& condition) {
        cout << "Удаление по условию: " << condition << endl;

        bool removed = false;
        for (auto it = plants.begin(); it != plants.end(); ) {
            if ((*it)->matches(condition)) {
                cout << "Удалён объект: " << (*it)->toString() << endl;
                it = plants.erase(it);
                removed = true;
            }
            else {
                ++it;
            }
        }

        if (!removed)
            cout << "По данному условию объекты не найдены" << endl;

        cout << endl;
    }

    void print() const {
        if (plants.empty()) {
            cout << "Контейнер пуст\n\n";
            return;
        }
        cout << "--- Коллекция растений ---\n";
        for (const auto& p : plants)
            p->print();
        cout << "Всего растений: " << plants.size() << "\n\n";
    }
};

unique_ptr<Plant> parseAdd(const string& data) {
    istringstream iss(data);
    string type, name;
    iss >> type >> name;

    if (type == "Дерево") {
        long age; iss >> age;
        return make_unique<Tree>(name, age);
    }
    if (type == "Кустарник") {
        string m; iss >> m;
        return make_unique<Shrub>(name, stringToMonth(m));
    }
    if (type == "Кактус") {
        double l; iss >> l;
        return make_unique<Cactus>(name, l);
    }
    throw invalid_argument("Неизвестный тип растения");
}

void processFile(const string& filename, PlantContainer& c) {
    ifstream f(filename);
    string line;

    while (getline(f, line)) {
        if (line.substr(0, 3) == "ADD") {
            c.add(parseAdd(line.substr(4)));
        } 
        else if (line.substr(0, 3) == "REM") {
            c.remove(line.substr(4));
        } 
        else if (line == "PRINT") {
            c.print();
        }
    }
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    setlocale(LC_ALL, "Russian");

    ofstream f("plants.txt");
    f << "ADD Дерево Дуб 150\n";
    f << "ADD Кустарник Сирень ИЮНЬ\n";
    f << "ADD Кактус Сагуаро 2.5\n";
    f << "ADD Дерево Береза 30\n";
    f << "PRINT\n";
    f << "REM название == 'Сирень'\n";
    f << "PRINT\n";
    f << "REM возраст > 50\n";
    f << "PRINT\n";
    f.close();

     try {
        PlantContainer c;
        processFile("plants.txt", c);
    } 
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка при обработке данных: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}