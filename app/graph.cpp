#include <iostream>
#include <string>

// This number is exclusive for the reddit hyperlinks body graph
// Number of nodes in the graph
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

struct node{
    int id;
};

class graph{
    private:
        std::string name;
    public:
        
        graph(){}
        ~graph(){}
    
        virtual bool *adj(node n, node m){
            return 0;
        }
        virtual node *neigh(node n){
            return node();
        }
        virtual node *rneigh(node n){
            return node();
        }
        virtual int outDegree(node n){
            return 0;
        }
        virtual int inDegree(node n){
            return 0;
        }

        std::string getName(){
            return name;
        }
};