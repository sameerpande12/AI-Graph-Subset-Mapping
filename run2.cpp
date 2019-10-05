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
        if(count==0)rows = stoi(temp);
        else if(count==1)cols = stoi(temp);
    }

    string result;
    cin>>result;

    if(!(result.compare("UNSAT")==0)){
        
        string values ;
        cin>>values;

        string temp= "";
        bool sign = true;
        for(int i = 0;i<values.size();i++){

            if(values[i]==' '){
                if(sign==true){
                    int pos = stoi(temp);
                    int row_num = (pos-1)/cols;
                    int col_num = (pos-1)%cols;

                    cout<< ( row_num + 1 ) <<" "<<(col_num + 1) <<endl;
                }
                    sign = true;
                    temp = "";
            }
            else if(values[i]=='-'){
                sign = false;
                temp = "";
            }
            else temp = temp + values[i];
        }
        
    }
    else cout<<0<<endl;
    
}