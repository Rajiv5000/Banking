#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

int main(){
    // string a="s123456";
    // ofstream out("test.txt",ios::app);
    // out<<"rajiv";
    // out.close();
    // int x=7,y=3;
    // cout<<x/y+x%y;
    ofstream in;
    string st;
    vector<string>s={"aesdhngybhkmh","waets geryrtyjhrdtgh","rdyh trzstyjnrzdfcvertjymyu"};
    string pass="C:\\micro_banking\\";
    in.open(pass+"passbook.txt");
    for(int i=0;i<3;i++)
    {
        in<<s.at(i)+"\n";
    }
    in.close();
    return 0;
}