#include<fstream>
#include<string.h>
#include<ctype.h>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<iostream>
using namespace std;
class account
{
public:
	int acno;
	char name[50];
	int deposit;
	char type;
	int flag=0;
public:
	void create_account();	
	void typeC();
	void typeS();
	void check_min_acc();
	void show_account();	
	void modify();   
	void dep(int);	
	void draw(int);	
	void report();	
	int retacno();	
	int retdeposit();	
	char rettype();	
};         

fstream fp;

void account::create_account()
{
	cout<<"\n\n\n\t\t\t\tAccount number: ";
	cin>>acno;
	cout<<"\n\n\t\t\t\tName of The account Holder : ";
	cin>>name;
	cout<<"\n\n\t\t\t\tEnter Type of The account (Enter 'C' for Current/'S' for Savings): ";
	cin>>type;
	type=toupper(type);
	if(type=='C')
	{
     	typeC();
    }
    else if(type=='S')
    {
    	typeS();
	}
    else
    {
		cout<<"You have entered an invalid type of account!!!"<<endl;
		cout<<"Account is not created.";
	}	
}

void account::typeC(){
	cout<<"\n\n\t\t\t\tEnter The Initial amount(Deposit >=1000 for Current account): ";
	cin>>deposit;
	check_min_acc();
	do
	{
	if(flag==1)
	{
		cout<<"\n\n\n\t\t\tAccount Created Successfully!";
		cout<<"\n\t\t\tAccount number is: "<<acno;
		break;
	}
	else
	{
		cout<<"\n\n\t\tDeposited amount is less than minimum balance required. Please deposit a required minimum balance amount.\n\n";
		cout<<"\n\n\t\t\t\tEnter The Initial amount(Deposit >= 1000 for Current account): ";
	    cin>>deposit;
		check_min_acc();
	}
    }while(true);
	
}

void account::typeS(){
	cout<<"\n\n\t\t\t\tEnter The Initial amount(Deposit >=500 for Savings account): ";
	cin>>deposit;
	check_min_acc();
	do
	{
	if(flag==1)
	{
		cout<<"\n\n\n\t\t\tAccount Created Successfully!";
		cout<<"\n\t\t\tAccount number is: "<<acno;
		break;
	}
	else
	{
		cout<<"\n\n\t\tDeposited amount is less than minimum balance required. Please deposit a required minimum balance amount.\n\n";
		cout<<"\n\n\t\t\t\tEnter The Initial amount(Deposit >=500 for Savings account): ";
	    cin>>deposit;
		check_min_acc();
	}
    }while(true);
}

void account::check_min_acc()
{
	if(type=='S')
	{
		if(deposit>=500)
		{
		 	flag = 1;
		}
		else
	   {
    		flag = 0;
	   }
	}
	else if(type=='C')
	{
		if(deposit>=1000)
		{
				flag = 1;
		}
		else
	    {
			flag = 0;
	    }
	}
	else
	{
		cout<<"Error! Invalid account type entered";
		flag = 0;
	}
}

void account::show_account()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nThe account No: "<<acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The amount : ";
	cin>>deposit;
}



void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report()
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int account::retacno()
{
	return acno;
}

int account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}


void write_account();	
void display_sp(int);	
void modify_account(int);	
void delete_account(int);	
void display_all();		
void deposit_withdraw(int, int); 
void intro();	
void home();
void Authentication();
void manage();
void customer();



int main()
{
	system("cls");
	intro();
	system("cls");
	home();
	return 0;
}




void write_account()
{
	account ac;
	ofstream outFile;
	fp.open("newAcc.txt",ios::app);
	outFile.open("account.txt",ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(account));
	fp<<ac.acno<<" | "<<ac.name<<" | "<<ac.deposit<<" | "<<ac.type<<" | "<<endl;
	fp.close();
	outFile.close();
}



void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
    inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
    while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
    inFile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
}




void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
    File.open("account.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account: "<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
		    File.write((char *) &ac, sizeof(account));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		  }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}




void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.txt");
	rename("Temp.txt","account.txt");
	cout<<"\n\n\tRecord Deleted ..";
}


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type        Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}



void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
    File.open("account.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
	 }
    File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}




void intro()
{
	cout<<"\n\n\t\t\t\t\tWELCOME TO";
	cout<<"\n\n\t\t\t\t     LS BANK PVT LTD.";
	cout<<"\n\n\n\n\t\t\t\tA File Structure MiniProject on";
	cout<<"\n\n\t\t\t\t\tBANKING SYSTEM";
	cout<<"\n\n\n\n\t\t\t      DESIGNED BY:  LIKITHA B 4SU16IS016\n\t\t\t\t\t    SANEESHA M V 4SU16IS029";
	cout<<"\n\n\t\t\t      COLLEGE : SDM INSTITUTE OF TECHNOLOGY, UJIRE.";
	cout<<"\n\n************************************************************************************************************************";
	cout<<"\n\n\n\n\n\nPress any button to continue...";
	getch();
}

void home(){
	char ch;
	int num;
	cout<<"\n\n\t\t\t\tWelcome to LS BANK"<<endl;
	cout<<"\n\n\n\t\t\t\tHOME"<<endl;
	cout<<"\n\n\n\n\n\t\t\t\tSelect an option..."<<endl;
	cout<<"\t\t\t\tLogin as...";
	cout<<"\n\n\t\t\t\t1.CUSTOMER\n\n\t\t\t\t2.BANK EMPLOYEE\n\n\t\t\t\t3.EXIT";
	cout<<"\n\n\n\t\t\t   Enter your option: ";
	cin>>ch;
	switch(ch)
	{
		system("cls");
		case '1':customer();
				 break;
		case '2':Authentication();
				 manage();
		  		 break;
		case '3':system("cls");
				 cout<<"Thank you for using LS Bank. Have a Good Day:)";
				 system("cls");
				 main();
		         break;
	    default: break;
	}
}

void manage()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\t\t\t\t\tYou are Logged in Successfully!";
	Sleep(1400);
	do
	{
		system("cls");
		cout<<"\n\n\n\t\t\t    MENU";
		cout<<"\n\n\t\t\t01. CREATE A NEW ACCOUNT";
		cout<<"\n\n\t\t\t02. USER BALANCE";
		cout<<"\n\n\t\t\t03. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t\t\t04. CLOSE AN ACCOUNT";
		cout<<"\n\n\t\t\t05. MODIFY AN ACCOUNT";
		cout<<"\n\n\t\t\t06. LOGOUT";
		cout<<"\n\n\t\t\t07. LOGOUT AND HOME";
		cout<<"\n\n\n\t\t\tEnter a choice number (1-6): ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '3':
			display_all();
			break;
		case '4':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '5':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '6':
		 	system("cls");
			cout<<"\n\n\n\n\n\n\t\t\tThank you:) Have a good day!!";
			Sleep(1200);
			system("cls");
			Authentication();
			break;
		 case '7':
		 	system("cls");
			cout<<"\n\n\n\n\n\n\t\t\tThank you:) Have a good day!!";
			Sleep(1200);
			system("cls");
			home();
			break;
		 default :system("cls");
		 		  cout<<"Error!!!";
		 		  cout<<"\a";
		 		  
		}
		getch();
    }while(ch!='6');
}

void Authentication(){
	char user[20],pass[20];
	int key;
	system("cls");
	cout<<"\n\n\n\t\t\t\t\tBank Employee Login";
	cout<<"\n\n\n\t\t\t\t\tUsername: ";
	cin>>user;
	cout<<"\n\t\t\t\t\tPassword: ";
	cin>>pass;
	if(strcmp(user,"user") == 0  && strcmp(pass,"pass")==0)
	{
		manage();
	}
	else
	{
		cout<<"\nInvalid username or password!";
		cout<<"\n\n";
		cout<<"Enter any key to continue";
		getch();
		Authentication();
	}
	
}

void customer(){
	char ch;
	int num;
	do
	{   system("cls");
		cout<<"\t\t\t\t\tCustomer Services"<<endl;
		cout<<"\n\n\n\t\t\t\t\t    MENU";
		cout<<"\n\t\t\tSelect an option number from the below"<<endl;
		cout<<"\n\n\t\t\t\t01. DEPOSIT";
		cout<<"\n\n\t\t\t\t02. WITHDRAW";
		cout<<"\n\n\t\t\t\t03. USER BALANCE";
		cout<<"\n\n\t\t\t\t04. HOME";
		cout<<"\n\n\n\t\t\tEnter your choice number (1-3): ";
		cin>>ch;
		system("cls");
		switch(ch){
		case '1':
			cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '4': cout<<"\n\n\tThanks for using bank managemnt system";
		          home();
		default: break;
	}
	getch();
	}while(ch!=3);
}


