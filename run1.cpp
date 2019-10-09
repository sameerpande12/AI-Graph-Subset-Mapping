#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <sstream>
#include <fstream>
using namespace std;


class Node{
    public:
        vector<Node*> neighbours;
        unordered_map<int,Node*> neighbour_map; 
        int indegree;
        int outdegree;
        int id;
    Node(){
        indegree = 0;
        outdegree = 0;
        neighbours.clear();
    }
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
        nodes.push_back(node);
    
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

    bool checkGraph(){
        for(int i =0 ;i<nodes.size();i++){
            if (!(nodes[i]->neighbours.size() == nodes[i]->neighbour_map.size())){
                return false;
            }
            for(int j = 0;j<nodes[i]->neighbours.size();j++){
                if( nodes[i]->neighbour_map.find(nodes[i]->neighbours[j]->id) == nodes[i]->neighbour_map.end())return false;
            }
        }
        return true;
    }
};

int main(int argc, char** argv){
    string line;
    bool isG_l = true;
    Graph Gl,Gs;
    Gl.nodes.clear();
    Gs.nodes.clear();
    int l_max=-1;
    int s_max=-1;
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
            if(x>l_max)l_max=x;
            if(y>l_max)l_max = y;
        }
        else{
            if(x>s_max)s_max = x;
            if(y>s_max)s_max = y;
            Gs.addEdge(x,y);
        }    

    }
    for(int i = 1;i<=l_max;i++){
        if(Gl.node_map.find(i) == Gl.node_map.end()){
            Gl.addNode(i);
        }

    }
    for(int i = 1;i<=s_max;i++){
        if(Gs.node_map.find(i) == Gl.node_map.end()){
            Gs.addNode(i);
        }
    }

    // cout<<"Large Graph  has atleast "<<Gs.nodes.size()<<" Nodes"<<endl;
    // cout<<"Small Graph  has atleast "<<Gs.nodes.size()<<" Nodes"<<endl;

    // for (int i = 0;i<Gs.nodes.size();i++){
    //     cout<<Gs.nodes[i]->id<<" :-";
    //     for(int j = 0;j<Gs.nodes[i]->neighbours.size();j++){
    //         cout<<Gs.nodes[i]->neighbours[j]->id<<" ";
    //     }
    //     cout<<endl;
    // }

    // cout<<"-----"<<endl<<endl;
    // for (int i = 0;i<Gl.nodes.size();i++){
    //     cout<<Gl.nodes[i]->id<<" :-";
    //     for(int j = 0;j<Gl.nodes[i]->neighbours.size();j++){
    //         cout<<Gl.nodes[i]->neighbours[j]->id<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"-----"<<endl<<endl;

    // cout<<"Gs"<<endl;
    // for (int i = 0;i<Gs.nodes.size();i++){
    //     cout<<Gs.nodes[i]->id<<" :- indegree = "<<Gs.nodes[i]->indegree<<" outdegree = "<<Gs.nodes[i]->outdegree<<endl;
        
        
    // }

    // cout<<"-----"<<endl<<endl;
    // cout<<"Gl"<<endl;
    // for (int i = 0;i<Gl.nodes.size();i++){
    //     cout<<Gl.nodes[i]->id<<" :- indegree = "<<Gl.nodes[i]->indegree<<" outdegree = "<<Gl.nodes[i]->outdegree<<endl;
        
        
    // }

    vector<vector<bool>>mapping;//mapping   (nodes of Gs) X (nodes of Gl) -> Boolean -> false if mapping is possible. true if possible (need not exist)
    vector<string> output_strings;
    long long int clauseCount = 0;
    // cout<<Gs.checkGraph()<<" "<<Gl.checkGraph()<<endl;
    int rows = Gs.nodes.size();
    int cols = Gl.nodes.size();
    ofstream satInputFile;
    string mode(argv[1]);
    satInputFile.open(mode+".satinput");

    for(int i =0 ;i<Gs.nodes.size();i++){
        vector<bool> temp;
        for(int j =0 ; j<Gl.nodes.size();j++){
            bool z = (Gs.nodes[i]->indegree <= Gl.nodes[j]->indegree) && (Gs.nodes[i]->outdegree <= Gl.nodes[j]->outdegree);
            temp.push_back(z);

            if(z==false){  
                stringstream ss;
                ss << "-"<< (Gs.nodes[i]->id - 1)*cols + (Gl.nodes[j]->id - 1) + 1<<" 0\n";// to clear out the cases in which indegree and out dgree do not match
                // output_strings.push_back(ss.str());
                satInputFile<<ss.str();
                clauseCount++;
    
            }
        }
        mapping.push_back(temp);
    }
    
    for(int i =0 ;i<Gs.nodes.size();i++){//to ensure one to one mapping
        for(int j = 0;j<Gl.nodes.size();j++){
            for(int k = j+1;k<Gl.nodes.size();k++){
                stringstream ss;
                ss<<"-"<<  (Gs.nodes[i]->id - 1)*cols + (Gl.nodes[j]->id - 1) + 1 <<" -"<<  (Gs.nodes[i]->id - 1)*cols + (Gl.nodes[k]->id - 1) + 1 <<" 0\n";
                // output_strings.push_back(ss.str());
                satInputFile<<ss.str();
                clauseCount++;
            }
        }

    }

    for(int i = 0;i<Gs.nodes.size();i++){
        stringstream ss;// to ensure that atleast one mapping exists 
        for(int j =0;j<Gl.nodes.size();j++){
            ss<< (Gs.nodes[i]->id - 1)*cols + (Gl.nodes[j]->id-1) + 1 <<" ";
        }
        ss<<"0\n";
        // output_strings.push_back(ss.str());
        satInputFile<<ss.str();
        clauseCount++;
    }

    for(int j = 0;j<Gl.nodes.size();j++){
        for(int i = 0;i<Gs.nodes.size();i++){//to ensure no to nodes map to same element
            for(int k = i+1;k<Gs.nodes.size();k++){
                stringstream ss;
                ss<<"-"<<(Gs.nodes[i]->id - 1)*cols + (Gl.nodes[j]->id -1 ) + 1<<" -"<<(Gs.nodes[k]->id - 1)*cols + (Gl.nodes[j]->id -1 ) + 1 <<" 0\n";
                // output_strings.push_back(ss.str());
                satInputFile<<ss.str();
                clauseCount++;
            }
        }
    }


    //to code for solution   (x[i][j] ^ e[i][p] ^ ~e[j][q] ) -> ~x[p][q]
    //                       (x[i][j] ^ ~e[i][p] ^ e[j][q] ) -> ~x[p][q]

            
    for(int i = 0;i<Gs.nodes.size();i++){
        for(int j = 0;j<Gl.nodes.size();j++){
            for(int p = 0;p<Gs.nodes.size();p++){
                if(i==p)continue;
                bool edge_i_p = false;
                if(!(Gs.nodes[i]->neighbour_map.find(Gs.nodes[p]->id) == Gs.nodes[i]->neighbour_map.end()))
                    edge_i_p = true;
                
                if(edge_i_p){//e[i][p] is true
                    for(int q = 0;q<Gl.nodes.size();q++){
                        bool edge_j_q = false;
                        if(!(Gl.nodes[j]->neighbour_map.find(Gl.nodes[q]->id)== Gl.nodes[j]->neighbour_map.end()))
                            edge_j_q = true;
                        
                        if(edge_i_p && !edge_j_q){
                            stringstream ss;
                            ss<< "-"<< (Gs.nodes[i]->id - 1)* cols +  (Gl.nodes[j]->id -1) + 1<<" -"<<  (Gs.nodes[p]->id - 1) *cols + (Gl.nodes[q]->id -1) + 1<<" 0\n";
                            // output_strings.push_back(ss.str());
                            satInputFile<<ss.str();
                            clauseCount++;
                        }
                        

                    }
                }
                else{// x[i][j] ^ ~e[i][p] ^ e[j][q]
                    for(int Q = 0;Q<Gl.nodes[j]->neighbours.size();Q++){
                        int q = Gl.nodes[j]->neighbours[Q]->id;
                        bool edge_j_q = false;
                        if(!(Gl.nodes[j]->neighbour_map.find(q)==Gl.nodes[j]->neighbour_map.end())){
                            edge_j_q = true;
                        }

                        if(edge_j_q){
                            stringstream ss;
                            ss<< "-"<< (Gs.nodes[i]->id - 1)* cols +  (Gl.nodes[j]->id -1) + 1<<" -"<<  (Gs.nodes[p]->id - 1) *cols + (q-1) + 1<<" 0\n";// (q-1) used plainly since q is already the id
                            // output_strings.push_back(ss.str());
                            satInputFile<<ss.str();
                            clauseCount++;
                        }
                    }
                }
            }


            

        }
    }
    satInputFile.close();
    int numVariables = cols * rows;
    ofstream satheaderfile;
    satheaderfile.open("header.txt");
    satheaderfile<<"p cnf "<<numVariables<<" "<<clauseCount<<endl;
    satheaderfile.close();
    
    // satInputFile<<"p cnf "<<numVariables<<" "<<output_strings.size()<<endl;

    for(int i =0 ;i<output_strings.size();i++)satInputFile<<output_strings[i];

    ofstream dimensionFile ;
    dimensionFile.open("Dimensions.txt");
    dimensionFile<<rows<<endl;
    dimensionFile<<cols;
    dimensionFile.close();
    return 0;
}