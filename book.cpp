#include <iostream>
#include <vector>
using namespace std;

class book
{
public:
    string Title;
    string Author;
    string ISBN;
    string Publication;
    void bookRequest()
    {
        //*****   this function has been implemented in the update() function of userDatabase class as add any book if issued else press 0
    }
    void dueDate()
    {
        cout << "enter the book ISBN number" << endl;
        getchar();
        string book,line;
        getline(cin, book);
        fstream bookFile;
        bookFile.open("bookFile.txt", ios::in);
        if (bookFile.is_open())
        {
            int count = 0,flag=1;
            while (getline(bookFile, line))
            {
                if(count%6==2 && line==book){
                    flag=0;
                }
                if (count % 6 == 5 && !flag)
                {
                    flag=0;
                    stringstream arrDate(line);
                    int temp[3];
                    int j = 0;
                    while (getline(arrDate, line, '/'))
                    {
                        temp[j] = stoi(line);
                        j++;
                    }
                    cout<<temp[0]<<"/"<<temp[1]<<"/"<<temp[2]<<endl;
                    break;
                }
                count++;
            }
            if(flag){
                cout<<"book does not exists"<<endl;
            }
        }
        bookFile.close();
        
    }
};