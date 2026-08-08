#pragma once

#include <string>
#include <vector>


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
        virtual int neighj(int n, int j);
        virtual std::vector<int> neigh(int n);
        virtual int rneighj(int n, int j);
        virtual std::vector<int> rneigh(int n);
        virtual int outDegree(int n);
        virtual int inDegree(int n);

        std::string getName();
};