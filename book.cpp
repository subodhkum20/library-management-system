#include <iostream>
#include <vector>
#include <ctime>
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
        string userid,book;
        cout<<"enter the id of the user to whom the book is to be issued"<<endl;
        getchar();
        getline(cin,userid);
        cout<<"enter the book ISBN number which is to be issued"<<endl;
        getline(cin,book);
        fstream userFile, newFile;
        bool exists = false;
        int flag = 1;
        userFile.open("userFile.txt", ios::in);
        newFile.open("userFile2.txt", ios::out);
        if (userFile.is_open())
        {
            string username, password, role, id, books, dateIssued;
            while (getline(userFile, username))
            {
                getline(userFile, password);
                getline(userFile, role);
                getline(userFile, id);
                getline(userFile, books);
                getline(userFile, dateIssued);
                if (id != userid)
                {
                    newFile << username << endl;
                    newFile << password << endl;
                    newFile << role << endl;
                    newFile << id << endl;
                    newFile << books << endl;
                    newFile << dateIssued << endl;
                }
                else
                {
                    exists = true;
                    newFile << username << endl;
                    newFile << password << endl;
                    newFile << role << endl;
                    newFile << id << endl;
                    if (book != "0")
                    {
                        fstream issueBook, newBook;
                        issueBook.open("bookFile.txt", ios::in);
                        newBook.open("bookFile2.txt", ios::out);
                        if (issueBook.is_open())
                        {
                            string line;
                            int count = 0;
                            while (getline(issueBook, line))
                            {
                                if ((count + 1) % 6 == 3)
                                {
                                    if (book == line)
                                    {
                                        newBook << line << endl;
                                        getline(issueBook, line);
                                        newBook << line << endl;
                                        getline(issueBook, line);
                                        if (line != "")
                                        {
                                            cout << "--------------------------------" << endl;
                                            cout << "this book is already issued to someone" << endl;
                                            cout << "--------------------------------" << endl;
                                            newBook << line << endl;
                                            flag = 0;
                                            getline(issueBook, line);
                                            newBook << line << endl;
                                        }
                                        else
                                        {
                                            newBook << userid << endl;
                                            time_t now = time(0);
                                            tm *ltm = localtime(&now);
                                            newBook << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                                            getline(issueBook, line);
                                        }
                                    }
                                    else
                                    {
                                        newBook << line << endl;
                                        getline(issueBook, line);
                                        newBook << line << endl;
                                        getline(issueBook, line);
                                        newBook << line << endl;
                                        getline(issueBook, line);
                                        newBook << line << endl;
                                    }
                                    count += 4;
                                }
                                else
                                {
                                    newBook << line << endl;
                                    count++;
                                }
                            }
                        }
                        issueBook.close();
                        newBook.close();
                        remove("bookFile.txt");
                        rename("bookFile2.txt", "bookFile.txt");
                        if (books != "")
                        {
                            if (flag)
                            {
                                newFile << books << "," <<book << endl;
                                time_t now = time(0);
                                tm *ltm = localtime(&now);
                                newFile << dateIssued << "," << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                            }
                            else
                            {
                                newFile << books << endl;
                                newFile << dateIssued << endl;
                            }
                        }
                        else
                        {
                            if (flag)
                            {
                                newFile <<book << endl;
                                time_t now = time(0);
                                tm *ltm = localtime(&now);
                                newFile << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                            }
                            else
                                newFile << books << endl;
                        }
                    }
                    else
                    {
                        newFile << books << endl;
                        newFile << dateIssued << endl;
                    }
                }
            }
            userFile.close();
            newFile.close();
            remove("userFile.txt");
            rename("userFile2.txt", "userFile.txt");
        }
        if (!exists)
        {
            cout << "user not exists" << endl;
        }
        else
        {
            cout << "user has been updated" << endl;
        }
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