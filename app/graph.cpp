#include <iostream>
#include <string>

// This number is exclusive for the reddit hyperlinks body graph
// Number of ints in the graph
int N = 35777;

class BenchmarkDoc{
    public:
        std::string name;
        float ConstructionTime;
        float adjTime;
        float rneighTime;
        float outDegreeTime;
        float inDegreeTime;
        BenchmarkDoc(std::string n, float constt, float adjt, float rneight, float outt, float innt){
            name = n;
            ConstructionTime = constt;
            adjTime = adjt;
            rneighTime = rneight;
            outDegreeTime = outt;
            inDegreeTime = innt;
        }
        ~BenchmarkDoc(){}
        void print(){
            std::cout << "===== BENCHMARK RESULTS: " << name << " =====" << std::endl;
            std::cout << "Construction Time: " << ConstructionTime << std::endl;
            std::cout << "Adjacency Time: " << adjTime << std::endl;
            std::cout << "Reverse Neighbors Time: " << rneighTime << std::endl;
            std::cout << "Out Degree Time: " << outDegreeTime << std::endl;
            std::cout << "In Degree Time: " << inDegreeTime << std::endl;
        }
};

class graph{
    private:
        std::string name;
    public:
        
        graph(){}
        ~graph(){}
    
        virtual bool adj(int n, int m){
            return 0;
        }
        virtual int neigh(int n, int j){
            return 0;
        }
        virtual int rneigh(int n, int j){
            return 0;
        }
        virtual int outDegree(int n){
            return 0;
        }
        virtual int inDegree(int n){
            return 0;
        }

        std::string getName(){
            return name;
        }
};