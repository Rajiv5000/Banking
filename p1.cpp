#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;

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
void change_username();
void change_password();
void change_number();
bool username_check(string s);
bool number_check(long long s);
void delete_acc();
string upper_case(string);
int main();
void menu()
{
    string n;
    cout<<"Dashboard \n1.Deposit \n2.Withdraw \n3.View Balance \n4.Send money \n5.Settings \n6.Log Out \n7.Exit"<<endl;
    // cout<<"Enter The Number"<<endl;
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
    setting();
    else if(n=="6")
    logout();
    else if(n=="7")
    {
        cout<<"Thank you for using Our ATM"<<endl;
        exit(0);
    } 
    else
    {
        cout<<"Invalid Number";
        menu();
    }
}
void deposit()
{
    double a;
    cout<<"\nEnter the amount to deposit"<<endl;
    cin>>a;
    amt+=a;
    cout<<"Amount is successfully deposited";
    cout<<position<<endl;
    ofstream out(pass+username[position]+".txt");
    out<<amt;
    out.close();
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
        withdraw();
    }
    else if(0<=amt-a)
    {
        amt-=a;
        cout<<"Amount is successfully withdrawal"<<endl;
        ofstream out(pass+username[position]+".txt");
        out<<amt;
        out.close();
    }
    else
    cout<<"Insufficient Balance";
    menu();
}
void view()
{
    cout<<"\nBank balance :"<<amt<<endl;
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
        cout<<"Enter the amount"<<endl;
        cin>>a;
        if(a<=0)
        {
            cout<<"Invalid amount"<<endl;
            withdraw();
        }
        else if(0<=amt-a)
        {   
            amt-=a;
            cout<<"Transaction Successful"<<endl;    
            ofstream out(pass+username[position]+".txt");    
            out<<amt;
            out.close();
            ifstream bal(pass+username[pos]+".txt");
            if(bal.is_open())
            {
                bal>>temp;
            }
            bal.close();
            temp+=a;
            ofstream other(pass+username[pos]+".txt");
            other<<temp;
            other.close();
        }
        else
        {
            cout<<"Insufficient Balance";
        }
    }
    else
    {
    cout<<"This number is not already register";
    }
    menu();
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
        change_password();
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
    {
        output();
        cout<<"Thank you for using Our ATM";
        exit(0);
    }
    else
    {
        cout<<"Invalid Number"<<endl;
        setting();
    }
}
void profile()
{
    cout<<"\nUsername :"<<username[position]<<endl;
    cout<<"password :"<<password[position]<<endl;
    cout<<"Mobile-Number :"<<number[position]<<endl;
    menu();
}
void change_username()
{
    string s;
    cout<<"Enter the new username"<<endl;
    cin>>s;
    if(!isalpha(s[0]))
    {
        cout<<"Username must start from alphabet"<<endl;
        change_username();
    }

    if(username_check(s))
    {
        cout<<"username already exists"<<endl;
        change_username();
    }
    else
    {
        username[position]=s;
    }

}
void change_password()
{
    string s;
    cout<<"Enter the new password"<<endl;
    cin>>s;
    password[position]=s;
}
void change_number()
{
    long long n;
    cout<<"Enter the new "<<endl;
    cin>>n;
    if(number_check(n))
    {
        cout<<"This number is already registered"<<endl;
        change_number();
    }
    else
    {
        number[position]=n;
    }
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
    if(s=="confirm")
    {
        ofstream member(pass+"member.txt");
        member<<total-1;
        member.close();
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
        ifstream name(pass+username[position]+".txt");
        if(name.is_open())
        remove((pass + username[position] + ".txt").c_str());
        name.close();
        cout<<"Thank you for using Our ATM"<<endl;
        exit(0);
    }
    menu();
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
        ifstream data(pass+username[position]+".txt");
        if(data.is_open())
        data>>a;
        amt+=a;
        data.close();
    }
}
void logout()
{
    output();
    main();
}
void end(string s)
{
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
        member.close();
        user.close();
        key.close();
        num.close();
        position=total-1;
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
int main()
{
    cout<<"Welcome to Simple Banking Services (SBS)"<<endl;
    input();
    into();
    menu();
    return 0;
}