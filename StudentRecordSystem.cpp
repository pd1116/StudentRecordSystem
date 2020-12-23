#include<iostream>      /// i/p and o/p stream....
#include<fstream>       // file stream...
#include<iomanip>       
#include<conio.h>      
#include<string.h>      // for String operations...we used strcmp so need to include this header file
using namespace std;


class Student 
{
    char name[20],div,grade;
    float m,p,c,cs,e,tot,per;
    int roll_no;

    public:
        void SetData()      
        {
            cout<<"\tEnter Student Name : ";
            cin>>name;
            cout<<"\tEnter Roll NO : ";
            cin>>roll_no;
            cout<<"\tEnter Student Division : ";
            cin>>div;
            cout<<"\tEnter Marks obtained in MAths : ";
            cin>>m;
            cout<<"\tEnter marks obtained in Physics : ";
            cin>>p;
            cout<<"\tEnter marks obtained in chemistry : ";
            cin>>c;
            cout<<"\tEnter marks obtained in CS : ";
            cin>>cs;
            cout<<"\tEnter marks obtained in English : ";
            cin>>e;
            calculate();

        }
        void calculate()           
        {   
            tot=m+p+c+cs+e;
            per=tot/5;
            cout<<"\tTotal Marks obatined by "<<name<<" is "<<tot<<endl;
            cout<<"\tPercentage obtained : "<<per<<"%"<<endl;
            if(per>=70)
            {
                grade='A';
            }
            else if(per>=60 && per<70)
            {
                    grade='B';
            }
            else if(per>=35 && per<60)
            {
                grade='C';
            }
            else
            {
                grade='F';
            }
            cout<<"\tGrade Obtained : "<<grade<<endl;
        }
        void DisplayRecordInTable()         
        {
            cout<<roll_no<<setw(14)<<name<<setw(6)<<p<<setw(5)<<c<<setw(5)<<m<<setw(5)<<cs<<setw(5)<<e<<setw(5)<<setprecision(5)<<per<<"     "<<grade<<endl;
            cout<<endl;
        }
        void show()             
        {
            cout<<"Student Name : "<<name<<endl;
            cout<<"Roll No : "<<roll_no<<endl; 
            cout<<"Student Division : "<<div<<endl;
            cout<<"Marks obtained in MAths : "<<m<<endl;
            cout<<"Marks obtained in Physics : "<<p<<endl;
            cout<<"Marks obtained in chemistry : "<<c<<endl;
            cout<<"Marks obtained in CS : "<<cs<<endl;
            cout<<"Marks obtained in English : "<<e<<endl;
            cout<<"Total marks obtained by "<<name<<" is "<<tot<<endl;
            cout<<"Percentage obtained by "<<name<<" is "<<per<<"%"<<endl;
            cout<<"Grade Obtained by "<<name<<" is "<<grade<<endl;
        }
        int getRoll()
        {
            return roll_no;
        }
};

fstream file;
Student s;

void DataInFile()               // Create record...
{
    file.open("pd.dat",ios::out|ios::app);
    s.SetData();
    file.write((char*)&s,sizeof(s));
    file.close();
    cout<<"\n\n\t\tStudent Record Created!!";
}
void Display_all_student()             //Display all students Result of Students for Faculties....
{
    cout<<"\t\t******Displaying Students Record******"<<endl;
    file.open("pd.dat",ios::in);
    
    while(file.read((char*)&s,sizeof(s)))
    {
        s.show();
        cout<<"================================="<<endl;
    }
    file.close();
}

void DisplaySearchByRoll(int n)            // For Searching Particular Student Result
{
    int flag=0;
    file.open("pd.dat",ios::binary|ios::in);
    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.getRoll()==n)
        {
            s.show();
            flag=1;
        }
    }
    file.close();
    if(flag==0)
    {
        cout<<"\n\tRecord does not Exist!!!"<<endl;
    }
}
void ModifyStudent()
{
    int c;
    int found=0;
    cout<<"Enter Roll no that u want to update : ";
    cin>>c;
    file.open("pd.dat",ios::in|ios::out);
    while(file.read((char*)&s,sizeof(Student)) && found==0)
    {
        if(s.getRoll()==c)
        {
            s.show();
            // \n\t for the new line and a Tab after the Previous Results are been Displayed...
            cout<<"\n\t\t********** MODIFYING SECTION **********"<<endl;
            cout<<"\n\tEnter NEW Details of Student : -  ";
            cout<<endl;
            s.SetData();
            int pos=-1*sizeof(Student);
            file.seekp(pos,ios::cur);
            file.write((char*)&s,sizeof(Student));
            cout<<"\n\n\t\tRecord updated!!"<<endl;
            found=1;
        }
    }
    file.close();
    if(found==0)
    {
        cout<<"Record Not Found!!!"<<endl;
    }
}
void DeleteStudent()
{
    int z;
    cout<<"Enter Roll no that u want Delete : ";
    cin>>z;
    file.open("pd.dat",ios::in|ios::out);
    int flag=-1;
    fstream n;
    n.open("rep.dat",ios::out);
    file.seekg(0,ios::beg);
    while(file.read((char*)&s,sizeof(Student)))
    {
        if(s.getRoll()!=z)
        {
            n.write((char*)&s,sizeof(Student));
            flag=0;
        }
        
    }
    n.close();
    file.close();
    remove("pd.dat");
    rename("rep.dat","pd.dat");
    if(flag==-1)
    {
        cout<<"Student Is not in the record!!.....So can't be Deleted!!"<<endl;
    }
    else
    {
        cout<<"Record Deleted!!"<<endl;
    }
}

void StudentResult()
{
    file.open("pd.dat",ios::in);
    if(!file)
    {
        cout<<"File Not Found!! It Seems that file is Missing in System.....Contact the Faculty!!"<<endl;
        exit(0);
    }
    cout<<"\n\t****ALL STUDENTS RESULT***"<<endl;
    cout<<"============================================================"<<endl;
    cout<<"Roll No.       Name     P   C    M   CS    E   per%   Grade"<<endl;                                                      
    cout<<"============================================================"<<endl;
    
    while(file.read((char*)&s,sizeof(s)))
    {
        s.DisplayRecordInTable();
    }
    file.close();
}
void FirstScreen()
{
    cout<<"\n\n\n\n\t\t\t\t************REPORT MANAGER**************";
    cout<<"\n\n\n\n\t\t\t\t********STUDENT  RECORD  SYSTEM*******";
 
}

void StudentMainMenu();         // Student's Main Menu....
void FacultyMainMenu();         // Faculty Main Menu....

class Login
{
    private:            
        char username[50];
        char password[50];
        char a;
    public:
        void Register()
        {
            ofstream fs("logindata.txt",ios::app);   
            cout<<endl;
            cout<<"\n\t\tEnter username: ";
            cin>>username;
            cout<<"\n\t\tEnter password: ";
            cin>>password;
            cout<<"\n\t\tSelect Whether to Register this username and password for Student/Faculty : "<<endl;
            cout<<"\n\t\tS-> Student ";
            cout<<"\n\t\tT-> Teacher "<<endl;
            cout<<"\n\t\tRegister this Username and Password as? : ";
            cin>>a;
            fs<<username<<" "<<password<<" "<<a<<" "<<endl;   // Writes in file....
            cout<<"\n\n\t\t\tREGISTERED SUCCESSFULLY!!!!"<<endl;
            fs.close();
        }
        void login(char un[],char pw[])
        {
            int search=0;
            ifstream fs("logindata.txt",ios::in);
            while(!fs.eof())
            {
                fs>>username>>password>>a;      //   reads out the username and password from file logindata.txt....
               
                if(strcmp(un,this->username)==0 && strcmp(pw,this->password)==0)
                {
                    if(a=='S'||a=='s')
                    {
                        cout<<"\n\n\n\t\t\t*******WELCOME "<<username<<"(Student) TO RECORD*******"<<endl;
                        search=1;
                        StudentMainMenu();
                    }
                    if(a=='T'||a=='t')
                    {
                        cout<<"\n\n\n\t******WELCOME "<<username<<"(Faculty) TO RECORD SYSTEM******"<<endl;
                        search=1;
                        FacultyMainMenu();
                    }
                    
                }
            }
            if(search==0)
            {
                cout<<"\n\tLogin Failed!!!....Please Enter Valid Details!!!"<<endl;
                cout<<"\n\tEither Username or Password is Incorrect!! "<<endl;
            }
            fs.close();   
        }
};

int main()
{
    FirstScreen();
    
    Login st;
    while(1)
    {
        char un[50],pass[50];
        int ch;
        
        cout<<"\n\t\t======================================================================================="<<endl;
        cout<<"\t\t\t\t********Welcome to Student Record System ********"<<endl;
        cout<<"\t\t======================================================================================="<<endl;
        
        cout<<"\n\t\t1. Login "<<endl;
        cout<<"\n\t\t2. Register "<<endl;
        cout<<"\n\t\t3. EXIT "<<endl;
        cout<<"\n\t\tEnter choice : ";
        cin>>ch;
        switch(ch)
        {
            case 1:
                cout<<" Username : ";
                cin>>un;
                cout<<" Password : ";
                cin>>pass;
                st.login(un,pass);
                break;
            case 2:
                st.Register();
                break;
            case 3:
                exit(0);
                break;
            default:
                cout<<"choose a Valid option!!!"<<endl;
                break;
        }
        
    }
    return 0;
}


void StudentMainMenu()
{
    int as;
    while(1)
    {
        cout<<"\n\n*************Student Record*************"<<endl;
        cout<<"\n\n1]All Students Record"<<endl;
        cout<<"\n\n2]Search Result By Roll No"<<endl;
        cout<<"\n\n3]Log Out!"<<endl;
        cout<<"\n\nChoose Option(1-3) : ";
        cin>>as;
        switch(as)
        {
            case 1:
                StudentResult();
                break;
            case 2:
            
                char h;
                do
                {
                    int q;
                    cout<<"Enter the Roll No That u want to search : ";
                    cin>>q;
                    DisplaySearchByRoll(q);
                    cout<<endl;
                    cout<<"Want to see more results? : ";
                    cin>>h;
                } while (h=='y'||h=='Y');
                break;
            case 3:
                main();
                break;
            default:
                cout<<"Invalid Option...Choose Valid option!!!"<<endl;
                cout<<"\a";
        }
    }
}
void FacultyMainMenu()
{
    int w;
    while(1)
    {
        cout<<"\n\n\n\t******TEACHERS MAIN MENU******"<<endl;
        cout<<"\n\n\t1]CREATE STUDENT RECORD";
        cout<<"\n\n\t2]DISPLAY ALL STUDENTS RECORDS";
        cout<<"\n\n\t3]SEARCH STUDENT RECORD ";
        cout<<"\n\n\t4]MODIFY STUDENT RECORD";
        cout<<"\n\n\t5]DELETE STUDENT RECORD";
        cout<<"\n\n\t6]LOG OUT!!";
        cout<<"\n\n\tPlease Enter Your Choice (1-6): ";
        cin>>w;
        cout<<endl;
        switch(w)
        {
            case 1:
                DataInFile();                   // Function for Creating a Student Record...
                break;
            case 2:
                Display_all_student();              // Founction Call for Displaying all students record...
                break;
            case 3:
                int num;
                cout<<"Enter Roll No that u want to search : ";
                cin>>num;
                DisplaySearchByRoll(num);               // Display particular Student Record using Roll NO...
                break;
            case 4:
                ModifyStudent();                    // to modify Record....
                break;
            case 5:
                DeleteStudent();                    // to delete a particular Student's Record...
                break;
            case 6:
                main();                             // call for main method ,for the Logging out!!...
                break;
            default:
                cout<<"Invalid option selected!!....Please select Valid option!!"<<endl;
                FacultyMainMenu();              // Recursion....
        }
    }
}






