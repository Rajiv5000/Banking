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
    passbook_write();
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
void passbook_add(string mode, double credit,double debit)
{
    cout<<fixed<<setprecision(2);
    if(debit==0)
    passbook.push_back(date()+"        "+mode+"        "+double_to_string(credit)+"                    "+to_string(0)+"        "+double_to_string(amt));
    else if(credit==0)
    passbook.push_back(date()+"        "+mode+"        "+to_string(0)+"                    "+double_to_string(debit)+"        "+double_to_string(amt));
}
void passbook_add(string mode,string type, string name, long number, double credit, double debit)
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
    out<<passbook.at(i)+"\n";
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
    cout<< " " <<passbook.at(i)<<endl;
    cout<<endl;
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
        folder_create(path);
        cout<<(fs::exists(path) && fs::is_directory(path))<<endl;
    }
}
void folder_create(string folder_name)
{
    fs::create_directory(folder_name);
}
int main()