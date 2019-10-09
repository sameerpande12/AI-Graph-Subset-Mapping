#include<iostream>
#include<fstream>
#include <vector>
using namespace std;
int main(){

    ifstream readDimension;
    readDimension.open("Dimensions.txt");

    int rows;
    int cols;
    
    int count = 0;
    while(!readDimension.eof()){
        string temp;
        readDimension>>temp;
        if(count==0){rows = stoi(temp); count = count + 1;}
        else if(count==1)cols = stoi(temp);
    }
    string result;
    cin>>result;
    
    for(int i =0 ;i<cols*rows+1;i++){
        int x;
        cin>>x;
        if(x>0){
            int row_num = (x-1)/cols;
            int col_num = (x-1)%cols;
            cout<<row_num + 1 << " "<<col_num + 1<<endl;
        }
    }
    
    // if(!(result.compare("UNSAT")==0)){
        
    //     string values;


        
    // }
    // else cout<<0<<endl;
    
}