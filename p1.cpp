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
double view(string, int);
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
void end_program(string);
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
void passbook_other(string,string,string,long long, double, double, int, long long, double);
string double_to_string(double);
void folder_check(string);
void folder_create(string);
string to_lower(string);
void user();
void key();
void num();
int main();

class admin{    //work in progressssssssssssssssssssssssssssss

    private:
    int count=0;
    int position;
    vector<string> username;
    vector<long long> number;
    vector<string> password;
    vector<string> admin_username;
    vector<long long> admin_number;
    vector<string> admin_password;
    int size=0;

    void menu()
    {
        int in;
        cout<<"1.Search \n2.Check passbook \n3.Delete Account"<<endl;
        cout<<"Enter the number"<<endl;
        cin>>in;
        if(in==1)
        {
            int out=search();
            if(out==-1)
            cout<<"No Record is Found"<<endl;
            else
            view(out);
            cout<<endl;
            menu();
        }
        else if(in==2)
        check_passbook();
        else if(in==3)
        delete_account();
        else
        {
            cout<<"Invalid Number"<<endl;
            cout<<endl;
            menu();
        }
    }
    int search()
    {
        string num;
        int in;
        cout<<"Enter the Username/Mobile Number for search"<<endl;
        cin>>num;
        if(isdigit(num[0]))
        in=search_by_number(stoll(num));
        else
        in=search_by_username(num);
        return in;
    }
    int search_by_number(long long num)
    {
        int i=0;
        while(i<number.size())
        {
            if(num==number.at(i))
            {
                cout<<"Found details"<<endl;
                return i;
            }
            i++;
        }
        return -1;
    }
    int search_by_username(string user)
    {
        int i=0;
        while(i<username.size())
        {
            if(user==username.at(i))
            {
                cout<<"Found details"<<endl;
                return i;
            }
            i++;
        }
        return -1;
    }
    void view(int i)
    {
        cout<<"Username : "<<username.at(i)<<endl;
        cout<<"Number : "<<number.at(i)<<endl;
        cout<<"Password : "<<password.at(i)<<endl;
    }
    void check_passbook()
    {
        string num;
        cout<<"Enter the Username/Mobile Number for search"<<endl;
        cin>>num;
        if(isdigit(num[0]))
        passbook_by_number(stoll(num));
        else
        passbook_by_username(num);
        cout<<endl;
        menu();
    }
    void passbook_by_number(long long num)
    {
        int in=search_by_number(num);
        if(in==-1)
        cout<<"Invalid Number"<<endl;
        else
        {
            if(folder_check(pass,in))
            passbook_read(in);
            else
            cout<<"No Passbook Is Generated"<<endl;
        }
    }
    void passbook_by_username(string user)
    {
        int in=search_by_username(user);
        if(in==-1)
        cout<<"Invalid Number"<<endl;
        else
        {
            if(folder_check(pass,in))
            passbook_read(in);
            else
            cout<<"No Passbook Is Generated"<<endl;
        }
    }
    void passbook_read(int position)
    {
        string st;
        vector<string>passbook;
        ifstream in;
        in.open(pass+to_string(number[position])+"\\passbook.txt");
        while(getline(in,st))
        {
            passbook.push_back(st);
        }
        in.close();
        cout<<" Date            Description        Credit     Debit         Balance"<<endl;
        for(int i=passbook.size()-1;0<=i;i--)
        cout<<passbook.at(i)<<endl;
        cout<<endl;
    }
    bool folder_check(string pass, int i)
    {
        if (!(fs::exists(pass) && fs::is_directory(pass)))
        return false;
        if (!(fs::exists(pass+to_string(number[position])) && fs::is_directory(pass+to_string(number[position]))))
        return false;
        if (!(fs::exists(pass+to_string(number[position])+"\\passbook.txt") && fs::is_directory(pass+to_string(number[position])+"\\passbook.txt")))
        return false;
        return true;
    }
    void delete_account()
    {
        int in;
        cout<<"\n 1. Delete Sepecific Account \n2. Delete All Account"<<endl;
        cin>>in;
        if(in==1)
        {
            int out=search();
            string s;
            cout<<"Type the \"Confirm\" to proceed"<<endl;
            cin>>s;
            s=to_lower(s);
            if(s=="confirm")
            delete_acc(out);
        }
    }
    void delete_all_account()
    {
        string s;
        cout<<"Type the \"Confirm\" to proceed"<<endl;
        cin>>s;
        s=to_lower(s);
        if(s=="confirm")
        {
            for(int i=0;i<username.size();i++)
            delete_acc(i);
        }
    }
    void delete_acc(int position)
    {
        string s;
        // cout<<"Type the \"Confirm\" to proceed"<<endl;
        cin>>s;
        s=to_lower(s);
        if(s=="confirm")
        {
            ofstream member(pass+"member.txt");
            member<<total-1;
            member.close();
            ::folder_check(pass+to_string(number[position]));
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
            ifstream name(pass+to_string(number[position])+"\\"+username[position]+".txt");// check it folder and file deletion
            if(name.is_open())
            {
                name.close();
                fs::remove_all((pass +to_string(number[position])).c_str());   // check
            }
            cout<<"Done"<<endl;
    }
}
    void login()
    {
        bool test1=false,test2=false;
        string in;
        if(count==3)
        {
            cout<<"You have Entered Incorrect Id/Username or Password more than three time"<<endl;
            cout<<"Thank you for using our ATM"<<endl;
            exit(0);
        }
        cout<<"Enter the Username/Mobile Number"<<endl;
        cin>>in;
        for(int i=0;i<size;i++)
        {
            if(in==admin_username[i]||(isdigit(in[0])&&(stoll(in)==admin_number[i])))
            {
                position=i;
                test1=true;
                break;
            }
        }
        cout<<"Enter the password"<<endl;
        cin>>in;
        if(in==admin_password[position])
        {
            test2=true;
        }
        if(!(test1&&test2))
        {
            cout<<"You have Entered Incorrect Id/Username or Password"<<endl;
            count++;
            login();
        }
    }
    public:
    void load(string * user, long long * num, string * password, int size)
    {
        username.assign(user,user+sizeof(size));
        number.assign(num,num+sizeof(size));
        admin::password.assign(password,password+sizeof(size));
        load();
        login();
    }
    void load()
    {
        ::folder_check(pass+"\\admin");
        ifstream mem(pass+"\\admin\\member.txt");
        if(mem.is_open())
        mem>>size;
        mem.close();
        ifstream in(pass+"\\admin\\username.txt");
        upload(in,size, admin_username);
        in.close();
        in.open(pass+"\\admin\\password.txt");
        upload(in,size, admin_password);
        in.close();
        in.open(pass+"\\admin\\number.txt");
        upload(in,size, admin_number);
        in.close();
    }
    void upload(ifstream& in,int size, vector<string> &temp)
    {
        string s;
        while(0<size)
        {
            in>>s;
            temp.push_back(s);
            --size;
        }
        in.close();
    }
    void upload(ifstream& in,int size, vector<long long> &temp)
    {
        long long s;
        while(0<size)
        {
            in>>s;
            temp.push_back(s);
            --size;
        }
        in.close();
    }
};

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
    end_program("Thank you for using Our ATM"); 
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
    cout<<"Balance : "<<amt<<endl;
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
            passbook_other("UPI","CR",username[position],number[position],a,0, pos, number[pos],pos);
            other.close();
        }
        else
        {
            cout<<"Insufficient Balance";
        }
        menu();
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
    end_program("Thank you for using Our ATM");
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
        end_program("Thank you for using Our ATM");
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
void end_program(string s)
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
        cout<<"Data is not found"<<endl;
        exit(0);
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
    while(getline(in,st))
    {
        passbook.push_back(st);
    }
    in.close();
    for(int i=passbook.size()-1;0<=i;i--)
    cout<<passbook.at(i)<<endl;
    cout<<endl;
}
void passbook_other(string mode,string type, string name, long long number, double credit, double debit, int position,long long sender_number, int pos)
{
    ofstream out;
    string st;
    folder_check(pass+to_string(sender_number));
    out.open(pass+to_string(sender_number)+"\\passbook.txt",ios::app);
    st=date()+"        "+mode+"/"+type+"/"+(name)+"/"+to_string(number)+"         "+double_to_string(credit)+"         "+to_string(0)+"        "+double_to_string(view(to_string(number),pos));
    out<<st+"\n";
    out.close();
}
double view(string number, int pos)
{
    double amt=0;
    ifstream in(pass+number+"\\"+username[pos]+".txt");
    in>>amt;
    return amt;
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
    here : cout<<"1. Admin/Staff \n2. Customer"<<endl;
    int in;
    cin>>in;
    input();
    if(in==1)
    {
        admin start;
        start.load(username, number, password, total);
    }
    else if(in==2)
    {
        into();
        menu();
        return 0;
    }
    else
    {
        cout<<"Invalid Input"<<endl;
        cout<<endl;
        goto here;
    }
}