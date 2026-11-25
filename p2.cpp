#include<iostream>
#include<vector>
#include<fstream>
#include<filesystem>
#include<string>
#include<ctime>
using namespace std;
namespace fs=std::filesystem;
void log();
class admin
{
      public: void log()
       {
              cout<<"Class"<<endl;
              ::log();
       }
};
void log()
{
       cout<<"Gobal"<<endl;
}
int main(){
       admin a;
       a.log();
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
// string pass="C:\\micro_banking\\";
// // fs::create_directory(pass+"\\new\\plus");
// //        ofstream out;
// //        out.open(pass+"\\text.txt");
// //        out<<"hello world!";
// //        out.close();
//        string folderPath = pass+"\\new";
//        if (!fs::exists(folderPath) && fs::is_directory(folderPath)) 
//        {
//               cout << "Folder exists";
//        } 
//        else
//        {
//               cout << "Folder does not exist";
//        }
//        cout<<(fs::exists(folderPath) && fs::is_directory(folderPath))<<endl;
       return 0;
}