#include<iostream>
#include<vector>
#include<fstream>
#include<filesystem>
#include<string>
#include<ctime>
using namespace std;
namespace fs=std::filesystem;

int main(){
//     // string a="s123456";
//     // ofstream out("test.txt",ios::app);
//     // out<<"rajiv";
//     // out.close();
//     // int x=7,y=3;
//     // cout<<x/y+x%y;
//     // ofstream in;
//     // string st;
//     // vector<string>s={"aesdhngybhkmh","waets geryrtyjhrdtgh","rdyh trzstyjnrzdfcvertjymyu"};
//     // string pass="C:\\micro_banking\\";
//     // in.open(pass+"passbook.txt");
//     // for(int i=0;i<3;i++)
//     // {
//     //     in<<s.at(i)+"\n";
//     // }
//     // in.close();
string pass="C:\\micro_banking\\";
fs::create_directory(pass+"\\new");
       ofstream out;
       out.open(pass+"\\text.txt");
       out<<"hello world!";
       out.close();
       return 0;
}