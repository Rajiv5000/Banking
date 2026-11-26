#include<iostream>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<filesystem>
using namespace std;
namespace fs=std::filesystem;

vector<string>passbook;
string *username;
string *password;
long long *number;
int total=0;
int position=0;
int count=0;
double amt=0;
// string passout="C:\\f\\";
string pass="C:\\micro_banking\\";

void deposit();
void withdraw();
void view();
void send();
int search(long long);
void setting();
void login();
void logout();
void end(string);
void input();
void output();
void load();
void profile();
void open_acc();
void end(string);
void change_username();
void change_password();
void change_number();
bool username_check(string s);
bool number_check(long long s);
void delete_acc();
string upper_case(string);
void passbook_write();
void passbook_read();
string date();
void passbook_add(string, double, double);
void passbook_add(string,string,string,long long, double, double);
void passbook_other(string,string,string,long long, double, double, int, long long);
string double_to_string(double);
void folder_check(string);
void folder_create(string);
string to_lower(string);
void user();
void key();
void num();
int main();

// class admin{    //work in progressssssssssssssssssssssssssssss

//     private:
//     vector<string> username;
//     vector<long long> number;
//     vector<string> password;
//     vector<string> admin_username;
//     vector<long long> admin_number;
//     vector<string> admin_password;
//     int size=0;

//     void login();
//     public:
//     void load(string * user, int user_size, long long * num, int num_size, string * password, int password_size)
//     {
//         username.assign(user,user+sizeof(user_size));
//         number.assign(num,num+sizeof(num_size));
//         admin::password.assign(password,password+sizeof(password_size));
//     }
//     void load_admin(string * user, int user_size, long long * num, int num_size, string * password, int password_size)
//     {
    
//     }
//     void search_by_username(string user)
//     {
        
//     }
//     void load()
//     {
//         folder_check(pass+"\\admin");
//         ifstream mem(pass+"\\admin\\member.txt");
//         mem>>size;
//         mem.close();
//     }
// };


// void admin::login()
// {
//     folder_check(pass+"\\admin");
//     ifstream mem(pass+"\\admin\\member.txt");
//     mem>>size;
//     mem.close();

// }

void menu()
{
    string n;
    cout<<"Dashboard \n1.Deposit \n2.Withdraw \n3.View Balance \n4.Send money \n5.Passbook \n6.Settings \n7.Log Out \n8.Exit"<<endl;
    cout<<"Enter The number"<<endl;
    cin>>n;
    if(n=="1")
    deposit();
    else if(n=="2")
    withdraw();
    else if(n=="3")
    view();
    else if(n=="4")
    send();
    else if(n=="5")
    {
        cout<<" Date            Description        Credit     Debit         Balance"<<endl;
        for(int i=passbook.size()-1;0<=i;i--)
        cout<<passbook[i]<<endl;
        passbook_read();
        menu();
    }
    else if(n=="6")
    setting();
    else if(n=="7")
    logout();
    else if(n=="8")
    end("Thank you for using Our ATM"); 
    else
    {
        cout<<"Invalid Number"<<endl;
        cout<<endl;
        menu();
    }
}
void deposit()
{
    double a;
    cout<<"\nEnter the amount to deposit"<<endl;
    cin>>a;
    amt+=a;
    cout<<"Amount is successfully deposited"<<endl;
    cout<<endl;
    folder_check(pass+to_string(number[position]));
    ofstream out(pass+to_string(number[position])+"\\"+username[position]+".txt");
    out<<amt;
    out.close();
    passbook_add("CASH DEP BY",a, 0);
    menu();
}
void withdraw()
{
    int a;
    cout<<"\nEnter the amount to withdraw"<<endl;
    cin>>a;
    if(a<=0)
    {
        cout<<"Invalid amount"<<endl;
        cout<<endl;
        withdraw();
    }
    else if(0<=amt-a)
    {
        amt-=a;
        cout<<"Amount is successfully withdrawal"<<endl;
        cout<<endl;
        folder_check(pass+to_string(number[position]));
        ofstream out(pass+to_string(number[position])+"\\"+username[position]+".txt");
        out<<amt;
        out.close();
        passbook_add("CASH WDL BY",0,a);
    }
    else
    cout<<"Insufficient Balance";
    cout<<endl;
    menu();
}
void view()
{
    cout<<"\nBank balance :"<<amt<<endl;
    cout<<endl;
    menu();
}
void send()
{
    long long n;
    double a=0,temp=0;
    int pos;
    cout<<"Enter mobile number to transfer money"<<endl;
    cin>>n;
    if(!number_check(n))
    {
        pos=search(n);
        again :cout<<"Enter the amount"<<endl;
        cin>>a;
        if(a<=0)
        {
            cout<<"Invalid amount"<<endl;
            cout<<endl;
            // withdraw();  //check yes or no
            goto again;
        }
        else if(0<=amt-a)
        {   
            amt-=a;
            cout<<"Transaction Successful"<<endl;
            cout<<endl;
            ofstream out(pass+to_string(number[position])+"\\"+username[position]+".txt");    
            out<<amt;
            out.close();
            passbook_add("UPI","DR",username[pos],number[pos],0,a);
            folder_check(pass+to_string(number[pos]));
            ifstream bal(pass+to_string(number[pos])+"\\"+username[pos]+".txt");
            if(bal.is_open())
            {
                bal>>temp;
            }
            bal.close();
            temp+=a;
            ofstream other(pass+to_string(number[pos])+"\\"+username[pos]+".txt");
            other<<temp;
            passbook_other("UPI","CR",username[position],number[position],a,0, pos, number[pos]);
            other.close();
        }
        else
        {
            cout<<"Insufficient Balance";
            menu();
        }
    }
    else
    {
        cout<<"This number is not already register";
        menu();
    }
}
int search(long long n)
{
    for(int i=0;i<total;i++)
    {
        if(n==number[i])
        return i;
    }
    return 0;
}
void setting()
{
    string s;
    cout<<"Settings \n1.View Profile \n2.Change User-Name \n3.Change Password \n4.Change Mobile Number \n5.Log-out \n6.Dashboard \n7.Delete Account \n8.Exit"<<endl;
    cout<<"Enter the number"<<endl;
    cin>>s;
    if(s=="1")
    profile();
    else if(s=="2")
    {
        change_username();
    }
    else if(s=="3")
    {
        change_password();
    }
    else if(s=="4")
    {
        change_number();
    }
    else if(s=="5")
    {
        logout();
    }
    else if(s=="6")
    menu();
    else if(s=="7")
    delete_acc();
    else if(s=="8")
    end("Thank you for using Our ATM");
    else
    {
        cout<<"Invalid Number"<<endl;
        cout<<endl;
        setting();
    }
}
void profile()
{
    cout<<"\nUsername :"<<username[position]<<endl;
    cout<<"password :"<<password[position]<<endl;
    cout<<"Mobile-Number :"<<number[position]<<endl;
    cout<<endl;
    setting();
}
void change_username()
{
    string s;
    cout<<"Enter the new username"<<endl;
    cin>>s;
    if(!isalpha(s[0]))
    {
        cout<<"Username must start from alphabet"<<endl;
    }
    if(!username_check(s))
    {
        cout<<"username already exists"<<endl;
    }
    else
    {
        string temp=username[position];
        double a=0;
        username[position]=s;
        user();
        ifstream in(pass+to_string(number[position])+"\\"+temp+".txt");
        in>>a;
        in.close();
        ofstream out(pass+to_string(number[position])+"\\"+s+".txt");
        out<<a;
        out.close();
        remove((pass+to_string(number[position])+"\\"+temp+".txt").c_str());
        cout<<endl;
    }
    setting();

}
void change_password()
{
    string s;
    cout<<"Enter the new password"<<endl;
    cin>>s;
    password[position]=s;
    cout<<endl;
    key();
    setting();
}
void change_number()
{
    long long n;
    cout<<"Enter the new number"<<endl;
    cin>>n;
    if(number_check(n))
    {
        cout<<"This number is already registered"<<endl;
    }
    else
    {
        number[position]=n;
        cout<<endl;
        num();
    }
    setting();
}
bool username_check(string s)
{
    for(int i=0;i<total;i++)
    {
        if(s==username[i])
        return false;
    }
    return true;
}
bool number_check(long long s)
{
    for(int i=0;i<total;i++)
    {
        if(s==number[i])
        return false;
    }
    return true;
}
void delete_acc()
{
    string s;
    cout<<"Type the \"Confirm\" to proceed"<<endl;
    cin>>s;
    s=to_lower(s);
    // cout<<(s)<<" "<<s.length()<<endl;
    if(s=="confirm")
    {
        ofstream member(pass+"member.txt");
        member<<total-1;
        member.close();
        folder_check(pass+to_string(number[position]));
        ofstream user(pass+"username.txt");   
        ofstream key(pass+"password.txt");    
        ofstream num(pass+"number.txt");       
        for(int i=0;i<total;i++)
        {
            if(i==position)
            continue;
            user<<username[i]<<endl;      
            key<<password[i]<<endl;       
            num<<number[i]<<endl;     
        }
        user.close();    
        key.close();
        num.close();
        ifstream name(pass+to_string(number[position])+"\\"+username[position]+".txt");// check it folder and file deletion
        if(name.is_open())
        {
            name.close();
            fs::remove_all((pass +to_string(number[position])).c_str());   // check
        }
        end("Thank you for using Our ATM");
    }
}
string to_lower(string s)
{
    string sp="";
    for(int i=0;i<s.length();i++)
    {
        if(isalpha(s[i])&&(int(s[i])<97))
        sp+=(char(int(s[i])+32));
        else
        sp+=s[i];
    }
    return sp;
}
void login()
{
    bool test1=false,test2=false;
    string in;
    double a=0;
    if(count==3)
    {
        cout<<"You have Entered Incorrect Id/Username or Password more than three time"<<endl;
        cout<<"Thank you for using our ATM"<<endl;
        exit(0);
    }
    cout<<"Enter the Username/Mobile Number"<<endl;
    cin>>in;
    for(int i=0;i<total;i++)
    {
        if(in==username[i]||(isdigit(in[0])&&(stoll(in)==number[i])))
        {
            position=i;
            test1=true;
            break;
        }
    }
    cout<<"Enter the password"<<endl;
    cin>>in;
    if(in==password[position])
    {
        test2=true;
    }
    if(!(test1&&test2))
    {
        cout<<"You have Entered Incorrect Id/Username or Password"<<endl;
        count++;
        login();
    }
    else
    {
        folder_check(pass+to_string(number[position]));
        user();
        key();
        num();
        ifstream data(pass+to_string(number[position])+"\\"+username[position]+".txt");  //username[position] ----> balance
        if(data.is_open())
        data>>a;
        amt+=a;
        data.close();
        cout<<endl;
    }
}
void logout()
{
    output();
    passbook_write();
    main();
}
void end(string s)
{
    output();
    passbook_write();
    cout<<s<<endl;
    exit(0);
}
void into()
{
    string h;
    cout<<"1.Open New Account \n2.Log-In"<<endl;
    cin>>h;
    if(h=="1")
    {
        open_acc();
    }
    else if(h=="2")
    {
        login();
    }
    else
    {
        cout<<"Invalid Number"<<endl;
        into();
    }
}
void open_acc()
{
    bool test1=false,test2=false;
    string s,p;
    long long n=0;
    cout<<"Create a username"<<endl;
    cin>>s;
    test1=!username_check(s);
    cout<<"Enter the number"<<endl;
    cin>>n;
    test2=!number_check(n);
    if(!isalpha(s[0]))
    {
        cout<<"Username must start from alphabet"<<endl;
        open_acc();
    }
    else if(test1)
    {
        cout<<"username already exists"<<endl;
        open_acc();
    }
    else if(test2)
    {
        cout<<"This number is already registered"<<endl;
        open_acc();
    }
    else
    {
        user();
        key();
        num();
        ofstream member(pass+"member.txt");
        ofstream user(pass+"username.txt",ios::app);
        ofstream key(pass+"password.txt",ios::app);
        ofstream num(pass+"number.txt",ios::app);
        cout<<"Enter the password"<<endl;
        cin>>p;
        member<<++total;
        user<<s<<endl;
        key<<p<<endl;
        num<<n<<endl;
        member.close();  //think to re-structure
        user.close();
        key.close();
        num.close();
        position=total-1;
        cout<<endl;
        input();
    }
    
}
void input()
{
    fstream file(pass+"member.txt");
    if(!file.is_open())
    {
        file.close();
        cout<<"You are 1st customer at SBS"<<endl;
        folder_check(pass);
        open_acc();
        //cout<<"Data is not found"<<endl;
        //exit(0);
        // end("Data is not found");
    }
    else
    {
        ifstream in;
        in.open(pass+"member.txt");
        in>>total;
        username=new string[total];
        password=new string[total];
        number=new long long[total];
        load();
        in.close();
        into();
    }
}
void output()
{
    ofstream member(pass+"member.txt");
    member<<total;
    member.close();
    folder_check(pass+to_string(number[position]));
    ofstream user(pass+"username.txt");
    ofstream key(pass+"password.txt");
    ofstream num(pass+"number.txt");
    for(int i=0;i<total;i++)
    {
        user<<username[i]<<endl;
        key<<password[i]<<endl;
        num<<number[i]<<endl;
    }
    user.close();
    key.close();
    num.close();
}
void load()
{
    ifstream user(pass+"username.txt");
    ifstream key(pass+"password.txt");
    ifstream num(pass+"number.txt");
    for(int i=0;i<total;i++)
    {
        user>>username[i];
        key>>password[i];
        num>>number[i];
    }
    user.close();
    key.close();
    num.close();
}
void passbook_add(string mode, double credit,double debit)
{
    cout<<fixed<<setprecision(2);
    if(debit==0)
    passbook.push_back(date()+"        "+mode+"        "+double_to_string(credit)+"                    "+to_string(0)+"        "+double_to_string(amt));
    else if(credit==0)
    passbook.push_back(date()+"        "+mode+"        "+to_string(0)+"                    "+double_to_string(debit)+"        "+double_to_string(amt));
}
void passbook_add(string mode,string type, string name, long long number, double credit, double debit)
{
    cout<<fixed<<setprecision(2);
    if(debit==0)
    passbook.push_back(date()+"        "+mode+"/"+type+"/"+(name)+"/"+to_string(number)+"         "+double_to_string(credit)+"         "+to_string(0)+"        "+double_to_string(amt));
    else if(credit==0)
    passbook.push_back(date()+"        "+mode+"/"+type+"/"+name+"/"+to_string(number)+"         "+to_string(0)+"         "+double_to_string(debit)+"        "+double_to_string(amt));
}
void passbook_write()
{
    ofstream out;
    string st;
    folder_check(pass+to_string(number[position]));
    out.open(pass+to_string(number[position])+"\\passbook.txt",ios::app);
    for(int i=0;i<passbook.size();i++)
    out<<passbook.at(i)<<endl;
    out.close();
}
void passbook_read()
{
    string st;
    vector<string>passbook;
    ifstream in;
    in.open(pass+to_string(number[position])+"\\passbook.txt");
    int i=9;
    while(getline(in,st))
    {
        passbook.push_back(st);
    }
    in.close();
    for(int i=passbook.size()-1;0<=i;i--)
    cout<<passbook.at(i)<<endl;
    cout<<endl;
}
void passbook_other(string mode,string type, string name, long long number, double credit, double debit, int position,long long sender_number)
{
    ofstream out;
    string st;
    folder_check(pass+to_string(sender_number));
    out.open(pass+to_string(sender_number)+"\\passbook.txt",ios::app);
    st=date()+"        "+mode+"/"+type+"/"+(name)+"/"+to_string(number)+"         "+double_to_string(credit)+"         "+to_string(0)+"        "+double_to_string(amt);
    out<<st+"\n";
    out.close();
}
string date()
{
    time_t t = std::time(nullptr); // get current time
    tm* now = std::localtime(&t);  // convert to local time
    return to_string(now->tm_mday) + '-'+ to_string(now->tm_mon + 1) + '-'+to_string((now->tm_year + 1900)%100);
}
string double_to_string(double value)
{
    ostringstream ss;
    ss<<fixed<<setprecision(2)<<value;
    return ss.str();
}
void folder_check(string path)
{
    if (!(fs::exists(path) && fs::is_directory(path))) 
    {   
        fs::create_directory(path);
    }
}
void user(){
    ofstream out(pass+to_string(number[position])+"\\"+"username.txt");
    out<<username[position];
    out.close();
}
void key(){
    ofstream out(pass+to_string(number[position])+"\\"+"password.txt");
    out<<password[position];
    out.close();
}
void num(){
    ofstream out(pass+to_string(number[position])+"\\"+"number.txt");
    out<<number[position];
    out.close();
}
int main()
{
    cout<<"Welcome to Simple Banking Services (SBS)"<<endl;
    input();
    menu();
    return 0;
}
