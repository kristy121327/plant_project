#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

enum class Month { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

string extractQuoted(const string& s);
Month stringToMonth(const string& m);
string monthToString(Month m);

class Plant {
protected:
    string name;
public:
    Plant(const string& n);
    virtual ~Plant() = default;

    virtual string toString() const = 0;
    virtual bool matches(const string& condition) const = 0;
    void print() const;
};

class Tree : public Plant {
    long age;
public:
    Tree(const string& n, long a);
    string toString() const override;
    bool matches(const string& c) const override;
};

class Shrub : public Plant {
    Month floweringMonth;
public:
    Shrub(const string& n, Month m);
    string toString() const override;
    bool matches(const string& c) const override;
};

class Cactus : public Plant {
    double spineLength;
public:
    Cactus(const string& n, double l);
    string toString() const override;
    bool matches(const string& c) const override;
};

class PlantContainer {
    vector<unique_ptr<Plant>> plants;
public:
    void add(unique_ptr<Plant> p);
    void remove(const string& condition);
    void print() const;
    size_t size() const { return plants.size(); }
};

unique_ptr<Plant> parseAdd(const string& data);
