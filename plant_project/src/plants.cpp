#include "plants.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace std;

// ---- функции ----
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
    default: throw invalid_argument("Неизвестный месяц");
    }
}

// ---- классы ----
Plant::Plant(const string& n) : name(n) {}
void Plant::print() const { cout << toString() << endl; }

Tree::Tree(const string& n, long a) : Plant(n), age(a) {}
string Tree::toString() const { return "Дерево: Название = " + name + ", Возраст = " + to_string(age); }
bool Tree::matches(const string& c) const {
    if (c.find("название") != string::npos) return name == extractQuoted(c);
    if (c.find("возраст") != string::npos) {
        if (c.find(">") != string::npos) return age > stol(c.substr(c.find(">") + 1));
        if (c.find("<") != string::npos) return age < stol(c.substr(c.find("<") + 1));
        if (c.find("==") != string::npos) return age == stol(c.substr(c.find("==") + 2));
    }
    return false;
}

Shrub::Shrub(const string& n, Month m) : Plant(n), floweringMonth(m) {}
string Shrub::toString() const { return "Кустарник: Название = " + name + ", Месяц цветения = " + monthToString(floweringMonth); }
bool Shrub::matches(const string& c) const {
    if (c.find("название") != string::npos) return name == extractQuoted(c);
    if (c.find("месяц") != string::npos && c.find("==") != string::npos) {
        string v = c.substr(c.find("==") + 2);
        v.erase(remove(v.begin(), v.end(), ' '), v.end());
        return floweringMonth == stringToMonth(v);
    }
    return false;
}

Cactus::Cactus(const string& n, double l) : Plant(n), spineLength(l) {}
string Cactus::toString() const { return "Кактус: Название = " + name + ", Длина колючек = " + to_string(spineLength); }
bool Cactus::matches(const string& c) const {
    if (c.find("название") != string::npos) return name == extractQuoted(c);
    if (c.find("длина") != string::npos) {
        if (c.find(">") != string::npos) return spineLength > stod(c.substr(c.find(">") + 1));
        if (c.find("<") != string::npos) return spineLength < stod(c.substr(c.find("<") + 1));
        if (c.find("==") != string::npos) return spineLength == stod(c.substr(c.find("==") + 2));
    }
    return false;
}

void PlantContainer::add(unique_ptr<Plant> p) { plants.push_back(move(p)); }
void PlantContainer::remove(const string& condition) {
    for (auto it = plants.begin(); it != plants.end(); ) {
        if ((*it)->matches(condition)) it = plants.erase(it);
        else ++it;
    }
}
