#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>
#include <locale>

using namespace std;
//hello
enum class Month {
    ЯНВАРЬ, ФЕВРАЛЬ, МАРТ, АПРЕЛЬ, МАЙ, ИЮНЬ,
    ИЮЛЬ, АВГУСТ, СЕНТЯБРЬ, ОКТЯБРЬ, НОЯБРЬ, ДЕКАБРЬ
};

Month stringToMonth(const string& m) {
    if (m == "ЯНВАРЬ") return Month::ЯНВАРЬ;
    if (m == "ФЕВРАЛЬ") return Month::ФЕВРАЛЬ;
    if (m == "МАРТ") return Month::МАРТ;
    if (m == "АПРЕЛЬ") return Month::АПРЕЛЬ;
    if (m == "МАЙ") return Month::МАЙ;
    if (m == "ИЮНЬ") return Month::ИЮНЬ;
    if (m == "ИЮЛЬ") return Month::ИЮЛЬ;
    if (m == "АВГУСТ") return Month::АВГУСТ;
    if (m == "СЕНТЯБРЬ") return Month::СЕНТЯБРЬ;
    if (m == "ОКТЯБРЬ") return Month::ОКТЯБРЬ;
    if (m == "НОЯБРЬ") return Month::НОЯБРЬ;
    if (m == "ДЕКАБРЬ") return Month::ДЕКАБРЬ;
    throw invalid_argument("Неизвестный месяц");
}

string monthToString(Month m) {
    switch (m) {
    case Month::ЯНВАРЬ: return "Январь";
    case Month::ФЕВРАЛЬ: return "Февраль";
    case Month::МАРТ: return "Март";
    case Month::АПРЕЛЬ: return "Апрель";
    case Month::МАЙ: return "Май";
    case Month::ИЮНЬ: return "Июнь";
    case Month::ИЮЛЬ: return "Июль";
    case Month::АВГУСТ: return "Август";
    case Month::СЕНТЯБРЬ: return "Сентябрь";
    case Month::ОКТЯБРЬ: return "Октябрь";
    case Month::НОЯБРЬ: return "Ноябрь";
    case Month::ДЕКАБРЬ: return "Декабрь";
    }
    return "";
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
            size_t p1 = c.find('\'');
            size_t p2 = c.find('\'', p1 + 1);
            return p1 != string::npos && p2 != string::npos &&
                name == c.substr(p1 + 1, p2 - p1 - 1);
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
            size_t p1 = c.find('\'');
            size_t p2 = c.find('\'', p1 + 1);
            return p1 != string::npos && p2 != string::npos &&
                name == c.substr(p1 + 1, p2 - p1 - 1);
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
            size_t p1 = c.find('\'');
            size_t p2 = c.find('\'', p1 + 1);
            return p1 != string::npos && p2 != string::npos &&
                name == c.substr(p1 + 1, p2 - p1 - 1);
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
        plants.push_back(move(p));
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
        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "ADD") {
            string data;
            getline(iss, data);
            c.add(parseAdd(data));
        }
        else if (cmd == "REM") {
            string cond;
            getline(iss, cond);
            c.remove(cond);
        }
        else if (cmd == "PRINT") {
            c.print();
        }
    }
}

int main() {
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

    PlantContainer c;
    processFile("plants.txt", c);
    return 0;
}
