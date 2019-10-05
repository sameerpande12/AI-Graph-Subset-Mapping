#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <sstream>
using namespace std;


class Node{
    public:
        vector<Node*> neighbours;
        unordered_map<int,Node*> neighbour_map; 
        int indegree;
        int outdegree;
        int id;
};


class Graph{

    public:
        vector<Node*> nodes;
        unordered_map<int,Node*> node_map;

    void addNode(Node* node){
        nodes.push_back(node);
        node_map[node->id]=node;
    }    
    void addNode(int id){
        Node* node = new Node();
        node->id = id;
        node->neighbours.clear();
        node_map[id] = node;
    }

    void addEdge(int x,int y){
        if( node_map.find(x) == node_map.end())addNode(x);
        if( node_map.find(y) == node_map.end())addNode(y);
        Node* xNode = node_map[x];
        Node* yNode = node_map[y];
        
        xNode->neighbours.push_back(yNode);
        xNode->neighbour_map[yNode->id] = yNode;

        xNode->outdegree = xNode->outdegree + 1;
        yNode->indegree = yNode->indegree + 1;
        
    }
};

int main(){
    string line;
    bool isG_l = true;
    Graph Gl,Gs;
    Gl.nodes.clear();
    Gs.nodes.clear();
    while(getline(cin,line)){
        
        string first;
        string second ;
        first="";
        second= "";
        bool readFirst = true;
        for(int i=0;i<line.size();i++){
            
            
            if(line[i]==' '){
                readFirst=false;
                continue;
            }
            if(readFirst)first = first + line[i];
            else second = second + line[i];
        }
        int x,y;
        x = stoi(first);
        y = stoi(second);

        if(x==y && x==0){
            isG_l = false;
            continue;
        }
        if(isG_l){
            Gl.addEdge(x,y);
            
        }
        else{
            Gs.addEdge(x,y);
        }    

    }

    vector<vector<bool>>mapping;
    vector<string> output_strings;

    int rows = Gs.nodes.size();
    int cols = Gl.nodes.size();
    
    for(int i =0 ;i<Gs.nodes.size();i++){
        vector<bool> temp;
        for(int j =0 ; j<Gl.nodes.size();j++){
            bool z = (Gs.nodes[i]->indegree == Gl.nodes[j]->indegree) && (Gs.nodes[i]->outdegree == Gl.nodes[j]->outdegree);
            temp.push_back(z);

            if(z==false){  
                stringstream ss;
                ss << "-"<< i*cols + j + 1<<" 0\n";
                output_strings.push_back(ss.str());
    
            }
        }
        mapping.push_back(temp);
    }
    

    for(int i = 0;i<Gs.nodes.size();i++){
        for(int j = 0;j<Gl.nodes.size();j++){
            //
            if(mapping[i][j]==true){
                for(int p = 0; p < Gs.nodes[i]->neighbours.size();p++){
                    bool edge_i_p = false;
                    if(!(Gs.nodes[i]->neighbour_map.find(Gs.nodes[p]->id) == Gs.nodes[i]->neighbour_map.end())){
                        edge_i_p = true;
                    }

                    for(int q  = 0;q<Gl.nodes[j]->neighbours.size();q++){
                        bool edge_j_q = false;

                        if(!(Gl.nodes[j]->neighbour_map.find(Gl.nodes[q]->id)== Gl.nodes[j]->neighbour_map.end())){
                            edge_j_q = true;
                        }

                        if( i==p && j == q)continue;

                        if(  !edge_i_p && !edge_j_q)continue;

                        stringstream ss;
                        ss<< "-"<< i * cols + j + 1<<" -"<< p*cols + q + 1<<" 0\n";
                        output_strings.push_back(ss.str());
                    }
                }

            }

        }
    }
    int numVariables = cols * rows;

    cout<<"p cnf "<<numVariables<<" "<<output_strings.size();

    for(int i =0 ;i<output_strings.size();i++)cout<<output_strings[i];


    return 0;
}