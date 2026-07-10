#pragma once

#include <string>

extern int N;

class BenchmarkDoc {
public:
    std::string name;
    float ConstructionTime;
    float adjTime;
    float rneighTime;
    float outDegreeTime;
    float inDegreeTime;

    BenchmarkDoc(std::string n, float constt, float adjt, float rneight, float outt, float innt);
    ~BenchmarkDoc();
    void print();
};

struct node {
    int id;
};

class graph {
private:
    std::string name;

public:
    graph();
    virtual ~graph();

    virtual bool* adj(node n, node m);
    virtual node* neigh(node n);
    virtual node* rneigh(node n);
    virtual int outDegree(node n);
    virtual int inDegree(node n);

    std::string getName();
};