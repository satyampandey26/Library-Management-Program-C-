#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<iomanip.h>
#include<time.h>
void BookIssue();
void BookDeposit();
void delay(int);

//function to display the time
char* ptime()
{
time_t t;
time(&t);
return ctime(&t);
}

//class containing the details of books
class Book
{
int bkno,stock;
char bknm[30], authornm[30];
public:
int getbkno()               //function to get bkno
{
return bkno;
}
void setbknm(char *newnm)    //function to set the bknm
{
strcpy(bknm,newnm);
}
void setauthornm(char *newnm) //function to set the authornm
{
strcpy(authornm,newnm);
}
void setstock(int st)         //function to set stock
{
stock=st;
}
int getstock()                //function to get the stock
{
return stock;
}
void incstock()               //function to increse stock by 1
{
stock ++;
}
void decstock()               //function to decrease stock by 1
{
stock --;
}
void getbkdetail();
void showbkdetail();
void shownesdetail();
void modifybkdetail();
void bkdatawrite();
void bkdataread();
void addbk();
void showmodify();
}B1;

//function to get the details of the book
void Book::getbkdetail()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
cout<<"\n";
cout<<"Enter Book Number ";
cin>>bkno;
cout<<"Enter Book Name ";
gets(bknm);
cout<<"Enter Author Name ";
gets(authornm);
cout<<"Enter the stock available ";
cin>>stock;
}

//function to show only necessary the book details
void Book::shownesdetail()
{
cout<<"\nBook Name   : "<<bknm;
cout<<"\nBook Author : "<<authornm;
}

//function to show the book details
void Book::showbkdetail()
{
cout.setf(ios::left);
cout<<setw(15)<<bkno<<setw(30)<<bknm<<setw(20)<<authornm<<setw(10)<<stock<<endl;
}

//function to add new book 
void Book::addbk()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
int ch;
do
{
ifstream f1("book.txt",ios::binary);
ofstream of("temp.txt",ios::binary);
Book newob;
int last=1;
cout<<"\n\nENTER THE NEW BOOK DETAILS \n";
newob.getbkdetail();
while(f1.read((char*)&B1,sizeof(B1)))
{
if(newob.getbkno()>B1.getbkno())
{
of.write((char*)&B1,sizeof(B1));
}
else
{
of.write((char*)&newob,sizeof(newob));
of.write((char*)&B1,sizeof(B1));
last=0;
break;
}
}
if(last==1)
of.write((char*)&newob,sizeof(newob));
else
{
while(f1.read((char*)&B1,sizeof(B1)))
{
of.write((char*)&B1,sizeof(B1));
}
}
f1.close();
of.close();
remove("book.txt");
rename("temp.txt","book.txt");
cout<<"\nDO YOU WANT TO ADD MORE BOOK...(1/0).. ";
cin>>ch;
}while(ch!=0);
}

void Book::showmodify()
{
cout<<"\nBOOK NAME   : "<<bknm;
cout<<"\nAUTHOR NAME : "<<authornm;
cout<<"\nSTOCK       : "<<stock;
}

//function to modify book details
void Book::modifybkdetail()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
int ch,bno,f=0,op;
do
{
ifstream f1("book.txt",ios::binary);
ofstream of("temp.txt",ios::binary);
cout<<"\n\nENTER THE BOOK NUMBER WHOSE RECORD YOU WANT TO MODIFY ";
cin>>bno;
while(f1.read((char*)&B1,sizeof(B1)))
{
if(bno==bkno)
{
f=1;
cout<<"CUURENT INFOMARTION \n";
showmodify();
cout<<"\n\nEnter :-";
cout<<"\n1 -> TO UPDATE BOOK NAME ";
cout<<"\n2 -> TO UPDATE AUTHOR NAME ";
cout<<"\n3 -> TO UPDATE STOCK AVAILABLE ";
cout<<"\n4 -> TO EXIT ";
cin>>ch;
switch(ch)
{
case 1: char nm[30];
	cout<<"\nENTER THE NEW BOOK NAME ";
	gets(nm);
	setbknm(nm);
break;
case 2: char anm[40];
	cout<<"\nENTER THE NEW AUTHOR NAME ";
	gets(anm);
	setauthornm(anm);
break;
case 3: int nst;
	cout<<"\nENTER THE NEW STOCK ";
	cin>>nst;
	setstock(nst);
break;
}
of.write((char*)&B1,sizeof(B1));
}
else
of.write((char*)&B1,sizeof(B1));
}
if(f==0)
cout<<"\nRECORD NOT FOUND ";
f1.close();
of.close();
remove("book.txt");
rename("temp.txt","book.txt");
cout<<"\nDO YOU WANT TO MODIFY MORE RECORDS...(1/0).. ";
cin>>op;
}while(op!=0);
}

//function to write the book details in file
void Book::bkdatawrite()
{
int ch;
ofstream of("book.txt",ios::binary);
while(1)
{
getbkdetail();
of.write((char*)&B1,sizeof(B1));
cout<<"\nDO YOU WANT TO ADD RECORDS FOR MORE BOOK...(1/0)... ";
cin>>ch;
if(ch==0)
break;
}
of.close();
}

//function to read book details from file
void Book::bkdataread()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();

cout<<".......................................................................";
cout<<"\nBOOK NUMBER \tBOOK NAME \t\t     AUTHOR NAME \tSTOCK\n";
cout<<".......................................................................\n";
ifstream f1("book.txt",ios::binary);
while(f1.read((char*)&B1,sizeof(B1)))
{
showbkdetail();
}
}

//class containing the details of members
class Member
{
int memid,bstatus,mbno;
char memnm[30];
public:
void setbstatus()   //function to set(1) the bstatus
{
bstatus=1;
}
void resetbstatus()   //function to reset(0) the bstatus
{
bstatus=0;
}
int getbstatus()      //function to get the value of bstatus
{
return bstatus;
}
int getmemid()        //fuction to get the value of memid
{
return memid;
}
void setmbno(int a=0)     //function to set mbno
{
mbno=a;
}
int getmbno()             //function to get mbno
{
return mbno;
}
void setnm(char *nm)      //function to set the memnm
{
strcpy(memnm,nm);
}
void getmemdetail();
void showmemdetail();
void modifymemdetail();
void memdatawrite();
void memdataread();
void addmem();
void delmem();
void shownesmemdetail();
}M1;

//function to get the details of members
void Member::getmemdetail()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
cout<<"\nEnter Member ID ";
cin>>memid;
cout<<"Enter Member Name ";
gets(memnm);
resetbstatus();
setmbno();
}

//function to display the member details
void Member::showmemdetail()
{
cout.setf(ios::left);
cout<<setw(15)<<memid<<setw(25)<<memnm<<setw(16);
if(bstatus==1)
{
cout<<"Taken ";
cout<<mbno;
}
else
cout<<"Not Taken ";
cout<<endl;
}

void Member::shownesmemdetail()
{
cout<<"\nNAME\t    : "<<memnm;
cout<<"\nBOOK STATUS : ";
if(bstatus==1)
{
cout<<"Taken ";
cout<<"\nBOOK NUMBER : ";
cout<<mbno;
}
else
cout<<"Not Taken ";
cout<<"\n";
}

//function to modify the member details
void Member::modifymemdetail()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
int id,f=0,ch,op;
do
{
ifstream f1("member.txt",ios::binary);
ofstream of("temp.txt",ios::binary);
cout<<"\nENTER THE MEMBER ID WHOSE DETAIL YOU WANT TO MODIFY ";
cin>>id;
while(f1.read((char*)&M1,sizeof(M1)))
{
if(id==memid)
{
f=1;
cout<<"\nCUURENT INFOMARTION \n";
cout<<"MEMBER NAME "<<memnm;
cout<<"\n\nEnter :-";
cout<<"\n1 -> TO CHANGE NAME ";
cout<<"\n2 -> TO EXIT ";
cin>>ch;
switch(ch)
{
case 1: char nm[30];
	cout<<"\nENTER THE NEW NAME ";
	gets(nm);
	setnm(nm);
break;
}
of.write((char*)&M1,sizeof(M1));
}
else
of.write((char*)&M1,sizeof(M1));
}
if(f==0)
cout<<"\nRECORD NOT FOUND ";
f1.close();
of.close();
remove("member.txt");
rename("temp.txt","member.txt");
cout<<"\nDO YOU WANT TO MODIFY RECORD OF OTHER MEMBER...(1/0).. ";
cin>>op;
}while(op!=0);
}

//function to write the member details in file
void Member::memdatawrite()
{
clrscr();
int ch;
ofstream of("MEMBER.txt",ios::binary);
while(1)
{
getmemdetail();
of.write((char*)&M1,sizeof(M1));
cout<<"\nDO YOU WANT TO ADD RECORD FOR MEMBER...(1/0)... ";
cin>>ch;
if(ch==0)
break;
}
of.close();
}

//function to read the member details from the file
void Member::memdataread()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
ifstream f1("Member.txt",ios::binary);
cout<<"--------------------------------------------------------------------";
cout<<"\nMEMBER ID\tMEMBER NAME \t\tBOOK STATUS \tBOOK NUMBER\n";
cout<<"--------------------------------------------------------------------\n";
while(f1.read((char*)&M1,sizeof(M1)))
{
showmemdetail();
}
f1.close();
}

//function to add new member
void Member::addmem()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
int ch;
do
{
ifstream f1("member.txt",ios::binary);
ofstream of("temp.txt",ios::binary);
Member newob;
int last=1;
cout<<"\n\nENTER THE NEW MEMBER DETAILS \n";
newob.getmemdetail();
while(f1.read((char*)&M1,sizeof(M1)))
{
if(newob.getmemid()>M1.getmemid())
{
of.write((char*)&M1,sizeof(M1));
}
else
{
of.write((char*)&newob,sizeof(newob));
of.write((char*)&M1,sizeof(M1));
last=0;
break;
}
}
if(last==1)
of.write((char*)&newob,sizeof(newob));
else
{
while(f1.read((char*)&M1,sizeof(M1)))
{
of.write((char*)&M1,sizeof(M1));
}
}
f1.close();
of.close();
remove("member.txt");
rename("temp.txt","member.txt");
cout<<"\nDO YOU WANT TO ADD MORE MEMBERS...(1/0).. ";
cin>>ch;
}while(ch!=0);
}

//function to delete the member record
void Member::delmem()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
ifstream f1("member.txt",ios::binary);
ofstream of("temp.txt",ios::binary);
int mid,ch,f=0,st;
cout<<"\n\nENTER THE MEMBER ID WHOSE RECORD YOU WANT TO DELETE\n";
cin>>mid;
while(f1.read((char*)&M1,sizeof(M1)))
{
if(mid==M1.getmemid())
{
f=1;
cout<<"\nRECORD FOUND \n";
shownesmemdetail();
cout<<"DO YOU WANT TO RECORD THE DELETE...(1/0)\n";
cin>>ch;
if(ch==0)
of.write((char*)&M1,sizeof(M1));
else
{
cout<<"\n....RECORD DELETED SUCCESSFULLY...";
st=getbstatus();
if(st==1)
{
fstream bk("book.txt",ios::in|ios::out|ios::binary);
while(bk.read((char*)&B1,sizeof(B1)))
{
if(B1.getbkno()==getmbno())
{
B1.incstock();
int bpos=-1*sizeof(B1);
bk.seekp(bpos,ios::cur);
bk.write((char*)&B1,sizeof(B1));
}
}
bk.close();
}
}
}
else
of.write((char*)&M1,sizeof(M1));
}
if(f==0)
cout<<"\n!RECORD NOT FOUND!\n";
f1.close();
of.close();
remove("member.txt");
rename("temp.txt","member.txt");
}

//class for maintaining menus
class Menu
{
int achoice,mchoice;
char pass[10];
public:
void amenu();
void passcheck();
void afnrun();
void mmenu();
void mfnrun();
void intro();
}MM;

//function to display the introduction
void Menu::intro()
{
clrscr();
cout<<"\n\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
cout<<"\t\t\t WELCOME ";
cout<<"\n\t\t\t TO THE \n";
cout<<"\t\tLIBRARY MANAGEMENT SYSTEM \n";
cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*";
delay(10);
clrscr();
cout<<"\n\nNOTE:- IN THE PROGRAM...(1/0)... 1 MEANS YES & 0 MEANS NO...";
delay(10);
mmenu();
}

//function to display the admin menu
void Menu::amenu()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
cout<<"----------------------------------------------------------------";
cout<<"\n\t\t\tADMIN MENU ";
cout<<"\n----------------------------------------------------------------\n";
cout<<"\tENTER :- ";
cout<<"\n\t1 -> TO ADD NEW BOOK ";
cout<<"\n\t2 -> TO MODIFY EXISTING BOOK RECORD";
cout<<"\n\t3 -> TO SHOW DETAILS OF ALL BOOK AVAILABLE ";
cout<<"\n\t4 -> TO ADD NEW MEMBER ";
cout<<"\n\t5 -> TO MODIFY EXISTING MEMBER RECORD ";
cout<<"\n\t6 -> TO DELETE THE MEMBER RECORD ";
cout<<"\n\t7 -> TO SHOW DETAILS OF ALL MEMBERS ";
cout<<"\n\t8 -> TO EXIT TO MAIN MENU ";
cout<<"\n\tENTER YOUR CHOICE ";
cin>>achoice;
afnrun();
}

//function for checking the password entered
void Menu::passcheck()
{
clrscr();
int ty;
again:
clrscr();
cout<<"\n\n\nENTER THE PASSWORD ";
cout<<"\n(HINT:- INITIALS OF PROJECT NAME WITH MIDDLE ONE IN LOWER CASE (lmp))\n";
gets(pass);
if(strcmp(pass,"LmP")==0)
{
cout<<"\nADMIN MENU ACCESSIBLE ";
delay(10);
amenu();
}
else
{
cout<<"\n!!WRONG PASSWORD!! \n!!ACCESS DENIED!! ";
cout<<"\nDO YOU WANT TO TRY AGAIN..(1/0).. ";
cin>>ty;
if(ty==1)
goto again;
else
{
cout<<"\n.....EXITING TO MAIN MENU.....\n";
delay(10);
mmenu();
}
}
}

void Menu::afnrun()
{
switch(achoice)
{
case 1: B1.addbk();
break;
case 2: B1.modifybkdetail();
break;
case 3: B1.bkdataread();
break;
case 4: M1.addmem();
break;
case 5: M1.modifymemdetail();
break;
case 6: M1.delmem();
break;
case 7: M1.memdataread();
break;
case 8: cout<<"\n\t.....GOING TO MAIN MENU..... \n";
	delay(5);
	mmenu();
break;
default: cout<<"\n!! WRONG INPUT !!";
break;
}
}

//function to display the main menu
void Menu::mmenu()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
cout<<"------------------------------------------------";
cout<<"\n\t\t    MAIN MENU \n";
cout<<"------------------------------------------------\n";
cout<<"\tEnter :-";
cout<<"\n\t1 -> TO ISSUE BOOK ";
cout<<"\n\t2 -> TO DEPOSIT BOOK ";
cout<<"\n\t3 -> TO USE ADMIN MENU ";
cout<<"\n\t4 -> TO EXIT PROGRAM ";
cout<<"\n\tENTER YOUR CHOICE ";
cin>>mchoice;
mfnrun();
}

void Menu::mfnrun()
{
switch(mchoice)
{
case 1: BookIssue();
break;
case 2: BookDeposit();
break;
case 3: passcheck();
	int ans;
	do
	{
	cout<<"\n\nDO YOU WANT TO PERFORM ANY OTHER FUNCTION..(1/0).. ";
	cin>>ans;
	if(ans==1)
	{
	delay(2);
	amenu();
	}
	}while(ans!=0);
	delay(3);
	cout<<"\n...EXITING TO MAIN MENU...";
	delay(3);
	mmenu();
break;
case 4: cout<<"\n\t!-!*!-!EXITING!-!*!-!\n";
	delay(10);
	exit(0);
break;
default: cout<<"\n !!! WRONG INPUT !!!";
	 cout<<"\n .!.!.ABORTING.!.!.";
	 delay(6);
	 exit(0);
}
}

//delay loop function
void delay(int n)
{
long i;
for(i=0;i<1000000*n;i++);
}

//function for issuing book
void BookIssue()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
cout<<"................................................................\n";
cout<<"\t\t\tBOOK ISSUING COUNTER\n";
cout<<"................................................................\n";
int mid,bno,mf=0,bf=0,st=0,bs=0,op;
fstream f1,f2;
f1.open("member.txt",ios::in|ios::out|ios::binary);
f2.open("book.txt",ios::in|ios::out|ios::binary);
cout<<"\nENTER THE MEMBER ID ";
cin>>mid;
while(f1.read((char*)&M1,sizeof(M1)))
{
if(mid==M1.getmemid())
{
mf=1;
bs=M1.getbstatus();
if(bs==0)
{
cout<<"\nENTER THE BOOK NO ";
cin>>bno;
while(f2.read((char*)&B1,sizeof(B1)))
{
if(bno==B1.getbkno())
{
bf=1;
B1.shownesdetail();
st=B1.getstock();
if(st>0)
{
cout<<"\nBOOK AVAILABLE ";
cout<<"\nDO YOU WANT TO TAKE THE BOOK...(1/0)... ";
cin>>op;
if(op==1)
{
cout<<"\n!*!PLEASE WAIT!*!\n";
delay(10);
cout<<"\n***BOOK ISSUED SUCCESSFULLY*** ";
M1.setbstatus();
int no=B1.getbkno();
M1.setmbno(no);
int mpos=-1*sizeof(M1);
f1.seekp(mpos,ios::cur);
f1.write((char*)&M1,sizeof(M1));
B1.decstock();
int bpos=-1*sizeof(B1);
f2.seekp(bpos,ios::cur);
f2.write((char*)&B1,sizeof(B1));
}
}
}
}
}
}
}
if(mf==0)
cout<<"\n!!CANNOT ISSUE BOOK TO YOU AS YOU ARE NOT THE MEMBER OF THE LIBRARY!! ";
else if(mf==1&&bs==1)
cout<<"\n!!YOU HAVE ALREADY TAKEN THE BOOK PLEASE FIRST RETURN THE PREVIOUS BOOK!! ";
else if(mf==1&&bf==0)
cout<<"\n!!NO SUCH BOOK IS AVAILABLE IN THE LIBRARY!! ";
else if(mf==1&&bf==1&&st==0)
cout<<"\n!!SORRY BOOK AVAILABLE IN LIBRARY BUT CURRENTLY OUT OF STOCK!! ";
else if(op==0)
cout<<"\n!!YOU OPTED NOT TO TAKE THE BOOK!! ";
f1.close();
f2.close();
delay(10);
delay(10);
cout<<"\n\n......RETURNING TO MAIN MENU......";
delay(10);
MM.mmenu();
}

//function for depositing book
void BookDeposit()
{
clrscr();
cout<<"\n\n";
cout<<"\t\t\t\t\t\t\t"<<ptime();
cout<<"..............................................................\n";
cout<<"\t\t\tBOOK DEPOSIT COUNTER\n";
cout<<"..............................................................\n";
int mid,mf=0,bs=0,bno;
fstream f1,f2;
f1.open("member.txt",ios::in|ios::out|ios::binary);
f2.open("book.txt",ios::in|ios::out|ios::binary);
cout<<"\nENTER YOUR MEMBER ID ";
cin>>mid;
while(f1.read((char*)&M1,sizeof(M1)))
{
if(mid==M1.getmemid())
{
mf=1;
bs=M1.getbstatus();
if(bs==1)
{
bno=M1.getmbno();
while(f2.read((char*)&B1,sizeof(B1)))
{
if(bno==B1.getbkno())
{
cout<<"\nBOOK DETAILS \n";
B1.shownesdetail();
cout<<"\n\n\n......DEPOSITING YOUR BOOK......";
M1.resetbstatus();
int mpos=-1*sizeof(M1);
f1.seekp(mpos,ios::cur);
f1.write((char*)&M1,sizeof(M1));
B1.incstock();
int bpos=-1*sizeof(B1);
f2.seekp(bpos,ios::cur);
f2.write((char*)&B1,sizeof(B1));
delay(10);
cout<<"\n\n\n***BOOK DEPOSITED SUCCESSFULLY***";
}
}
}
}
}
if(mf==0)
cout<<"\n!!YOU ARE NOT THE MEMBER OF THE LIBRARY!!";
else if(mf==1&&bs==0)
cout<<"\n!!PREVIOUSLY YOU HAVE NOT TAKEN ANY BOOK!!";
delay(10);
cout<<"\n\n......RETURNING TO MAIN MENU......";
delay(10);
delay(10);
MM.mmenu();
}

main()
{
MM.intro();
getch();
}


