#include <iostream>
#include<fstream>
#include<cstring>
using namespace std;
short header=-1;
struct Book
{
    char Isbn[5]= {'\0'};
    char title[20]= {'\0'};
    char authorname[20]= {'\0'};
    char price[20]= {'\0'};
    char numofpages[20]= {'\0'};
    char year[20]= {'\0'};


};
void addheader()
{
    fstream file;
    file.open("myfile.txt",ios::out|ios::app);
    file.write((char*)&header,2);
}
void addrecord()
{
    fstream file;
    file.open("myfile.txt",ios::out|ios::app);
    Book b;
    cout<<"enter isbn:";
    cin.getline(b.Isbn,5);
    cout<<"enter  title :";
    cin.getline(b.title,20);

    cout<<"enter authorname:";
    cin.getline(b.authorname,20);

    cout<<"enter price:";
    cin.getline(b.price,20);

    cout<<"enter year:";

    cin.getline(b.year,20);

    cout<<"enter numofgaes:";
    cin.getline(b.numofpages,20);

    file.write((char*)&b,sizeof(b));



}
void printall()
{
    Book p;
    fstream file;
    file.open("myfile.txt",ios::in);
    file.seekg(0,ios::beg);
    file.read((char*)&header,sizeof(header));

    while(!file.eof())
    {

        file.read((char*)&p,sizeof(p));
        cout<<"ISBN:"<<p.Isbn<<endl;
        cout<<"Title:" <<p.title<<endl;
        cout<<"AuthorName:"<<p.authorname<<endl;
        cout<<"Price:"<<p.price<<endl;
        cout<<"Number Of Pages Is:"<<p.numofpages<<endl;
        cout<<"Year Is:"<<p.year<<endl;
    }
}
void printbyisbn()
{
    fstream file;
    file.open("myfile.txt",ios::in);
    string key;
    Book p;
    cout<<"Enter The ISBN :";
    cin>>key;
    file.seekg(0,ios::beg);
    file.read((char*)&header,sizeof(header));
    while(!file.eof())
    {
        file.read((char*)&p,sizeof(p));

        if(p.Isbn==key)
        {
            cout<<"ISBN:"<<p.Isbn<<endl;
            cout<<"Title:"<<p.title<<endl;
            cout<<"AuthorName:"<<p.authorname<<endl;
            cout<<"Price:"<<p.price<<endl;
            cout<<"Number Of Pages :"<<p.numofpages<<endl;
            cout<<"Year:"<<p.year<<endl;
            break;
        }


    }
}

void delte(string key)
{
    fstream file;
    int counter=0;
    Book p;
    //string key;
    file.open("myfile.txt",ios::out|ios::in);
    // cout<<"Enter The ISBN:";
    //cin>>key;
    file.seekg(0,ios::beg);
    file.read((char*)&header,sizeof(header));
    while(!file.fail())
    {
        file.read((char*)&p,sizeof(p));
        //cout<<p.Isbn;
        if(key!=p.Isbn)
        {
            counter++;
        }
        else if (key==p.Isbn)
        {
            int Size=sizeof(p);
            file.seekp(-Size,ios::cur);
            //int n=iff.tellp();

            //p.Isbn[1]= {'*'};
            file.write("*",1);
            file.write((char*)&header,1);
            header=counter;
            file.seekg(0,ios::beg);
            file.write((char*)&header,sizeof(header));
            break;
        }


    }

    cout<<counter;
}
void update(fstream&file)
{
    Book p;
    string key;

    cout<<"Enter The ISBN :";
    cin>>key;
    file.seekg(0,ios::beg);
    file.read((char*)&header,sizeof(header));
    while(!file.fail())
    {
        file.read((char*)&p,sizeof(p));
        if (key==p.Isbn)
        {
            delte(key);
            cin.ignore();
            addrecord();

        }


    }
}
void compact(){
    Book b;
    short h= -1;
fstream in,out;
in.open("myfile.txt",ios::in);
out.open("newfile.txt",ios::out|ios::app);
in.seekg(0,ios::beg);
in.read((char*)&header,sizeof(header));
            bool found=true;

while(!in.fail()){
    in.read((char*)&b,sizeof(b));
    if(b.Isbn[0]!='*'){

                if(found)
                {
                out.write((char*)&header,sizeof(header));

                }
                found=false;
        out.write((char*)&b,sizeof(b));

    }
}
in.close();
out.close();
remove("myfile.txt");
rename("newfile.txt","myfile.txt");

}
int main()
{
    fstream file;
// file.open("myfile.txt",ios::in);
//   file.read((char*)&header,sizeof(header));
//   cout<<header;
    while(1)
    {
        int y;
        cout<<"press 0 to add a header"<<endl;
        cout<<"enter 1 to add book"<<endl;
        cout<<"press 2 to print all "<<endl;
        cout<<"enter 3 print by isbn"<<endl;
        cout<<"enter 4  delte"<<endl;
        cout<<"enter 5 update"<<endl;
        cout<<"enter 6  compact"<<endl;
        cout<<"enter 7 to exit"<<endl;


        cin>>y;
        if(y==0)
        {
            addheader();
        }
        if(y==1)
        {
            //  file.open("myfile.txt",ios::out|ios::app);
            int x;
            cout<<"enter number of recodrs u want to add "<<endl;
            cin>>x;
            bool found=true;
            for(int i=0; i<x; i++)
            {
                if(found)
                {
                    cin.ignore();
                }
                found=false;
                addrecord();
            }

        }
        if(y==2)
        {
            //file.open("myfile.txt",ios::in);
            printall();

        }
        if(y==3)
        {
            //file.open("myfile.txt",ios::in);
            printbyisbn();

        }
        if(y==4)
        {

            // file.open("myfile.txt",ios::out|ios::in);
            string c;
            cout<<"enter isbn :";
            cin>>c;
            delte(c);
        }
        if(y==5)
        {
            file.open("myfile.txt",ios::out|ios::in|ios::app);
            update(file);
        }
        if(y==6){

            compact();
        }
        if(y==7)
        {
            return 0;
        }

    }
}
