#pragma once

#include <string>

extern int N;
extern int E;

class BenchmarkDoc {
    public:
        std::string name;
        float ConstructionTime;
        float adjTime;
        float rneighTime;
        float outDegreeTime;
        float inDegreeTime;
        int sizePerEdge;

        BenchmarkDoc(std::string n, float constt, float adjt, float rneight, float outt, float innt, int sizePerEdge);
        ~BenchmarkDoc();
        void print();
};

class graph {
    private:
        std::string name;

    public:
        graph();
        virtual ~graph();

        virtual bool adj(int n, int m);
        virtual int neigh(int n, int j);
        virtual int rneigh(int n, int j);
        virtual int outDegree(int n);
        virtual int inDegree(int n);

        std::string getName();
};