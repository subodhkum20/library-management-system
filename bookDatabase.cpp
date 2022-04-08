#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "book.cpp"
using namespace std;

class bookDatabase
{
public:
    vector<book> books;
    void addBook(book newFile)
    {
        fstream bookFile;
        bookFile.open("bookFile.txt", ios::app);
        bookFile << newFile.Title << "\n";
        bookFile << newFile.Author << "\n";
        bookFile << newFile.ISBN << "\n";
        bookFile << newFile.Publication << "\n";
        bookFile << "\n";
        bookFile << endl;
        cout << "book has been added" << endl;
        bookFile.close();
    }
    void updateBook(string toUpdate)
    {
        fstream bookFile, newFile;
        bool exists = false;
        bookFile.open("bookFile.txt", ios::in);
        newFile.open("bookFile2.txt", ios::out);
        if (bookFile.is_open())
        {
            string Title, Author, ISBN, Publication, issuedTo,dateIssued;
            while (getline(bookFile, Title))
            {
                getline(bookFile, Author);
                getline(bookFile, ISBN);
                getline(bookFile, Publication);
                getline(bookFile, issuedTo);
                getline(bookFile, dateIssued);
                if (ISBN != toUpdate)
                {
                    newFile << Title << endl;
                    newFile << Author << endl;
                    newFile << ISBN << endl;
                    newFile << Publication << endl;
                    newFile << issuedTo << endl;
                    newFile << dateIssued << endl;
                }
                else
                {
                    exists = true;
                    cout << "enter the updated book title" << endl;
                    getline(cin, Title);
                    newFile << Title << endl;
                    cout << "enter the updated book Author" << endl;
                    getline(cin, Author);
                    newFile << Author << endl;
                    newFile << ISBN << endl;
                    cout << "enter the updated book Publication" << endl;
                    getline(cin, Publication);
                    newFile << Publication << endl;
                    newFile << issuedTo << endl;
                    newFile << dateIssued << endl;
                }
            }
            if (!exists)
            {
                cout << "book does not exists" << endl;
            }
            else
            {
                cout << "book has been updated successfully";
            }
            bookFile.close();
            newFile.close();
            remove("bookFile.txt");
            rename("bookFile2.txt", "bookFile.txt");
        }
    }
    void deleteBook(string toDelete)
    {
        fstream bookFile, newFile;
        bool exists = false;
        bookFile.open("bookFile.txt", ios::in);
        newFile.open("bookFile2.txt", ios::out);
        if (bookFile.is_open())
        {
            string bookname, Author, ISBN, publication, issuedTo,dateIssued;
            while (getline(bookFile, bookname))
            {
                getline(bookFile, Author);
                getline(bookFile, ISBN);
                getline(bookFile, publication);
                getline(bookFile, issuedTo);
                getline(bookFile, dateIssued);
                if (ISBN != toDelete)
                {
                    cout << ISBN << endl;
                    newFile << bookname << endl;
                    newFile << Author << endl;
                    newFile << ISBN << endl;
                    newFile << publication << endl;
                    newFile << issuedTo << endl;
                    newFile << dateIssued << endl;
                }
                else
                    exists = true;
            }
            bookFile.close();
            newFile.close();
            remove("bookFile.txt");
            rename("bookFile2.txt", "bookFile.txt");
        }
        if (!exists)
        {
            cout << "book does not exists" << endl;
        }
        else
        {
            cout << "book has been deleted" << endl;
        }
    }
    void Search( string bookISBN)
    {
        fstream bookFile;
        bookFile.open("bookFile.txt");
        if (bookFile.is_open())
        {
            string bookName;
            while (getline(bookFile, bookName))
            {
                string author, publication, ISBN, IssuedTo,dateIssued;
                getline(bookFile, author);
                getline(bookFile, ISBN);
                getline(bookFile, publication);
                getline(bookFile, IssuedTo);
                getline(bookFile, dateIssued);
                if (ISBN == bookISBN)
                {
                    cout << "--------------------------------" << endl
                         << bookName << endl
                         << author << endl
                         << publication << endl
                         << ISBN << endl
                         << IssuedTo << endl
                         << dateIssued << endl
                         << "--------------------------------" << endl;
                }
            }
        }
    }
    void Display()
    {
        fstream bookFile;
        bookFile.open("bookFile.txt", ios::in);
        if (bookFile.is_open())
        {
            string line;
            int count = 0;
            while (getline(bookFile, line))
            {
                if (count % 6 == 0)
                {
                    cout << "--------------------------------" << endl;
                    cout << endl;
                }
                count++;
                cout << line << endl;
            }
            cout << "--------------------------------" << endl;
            cout << endl;
        }
    }
    void unissue()
    {
        cout << "enter the ISBN of the book you want to unissue" << endl;
        string line, bookISBN;
        int count = 0;
        getchar();
        getline(cin, bookISBN);
        fstream bookFile, newFile;
        bookFile.open("bookFile.txt", ios::in);
        newFile.open("bookFile2.txt", ios::out);
        if (bookFile.is_open())
        {
            while (getline(bookFile, line))
            {
                if ((count + 1) % 6 == 3)
                {
                    if (bookISBN == line)
                    {
                        newFile << line << endl;
                        getline(bookFile, line);
                        newFile << line << endl;
                        getline(bookFile, line);
                        fstream userFile, unIssued;
                        userFile.open("userFile.txt", ios::in);
                        unIssued.open("userFile2.txt", ios::out);
                        if (userFile.is_open())
                        {
                            string temp;
                            int ccount = 0;
                            while (getline(userFile, temp))
                            {
                                if (temp == line && (ccount + 1) % 6 == 4)
                                {
                                    unIssued << temp << endl;
                                    getline(userFile, temp);
                                    stringstream x(temp);
                                    int flag = 1;
                                    int i = 0, pos;
                                    while (getline(x, temp, ','))
                                    {
                                        if (temp != bookISBN && flag)
                                        {
                                            flag = 0;
                                            unIssued << temp;
                                        }
                                        else if (temp != bookISBN)
                                        {
                                            unIssued << temp << ",";
                                        }
                                        else
                                            pos = i;
                                        i++;
                                    }
                                    unIssued << endl;
                                    i = 0, flag = 1;
                                    getline(userFile, temp);
                                    stringstream y(temp);
                                    while (getline(y, temp, ','))
                                    {
                                        if (pos == 0 && flag)
                                        {
                                            flag = 0;
                                        }
                                        else if (pos == i)
                                        {
                                        }
                                        else if (flag)
                                        {
                                            flag = 0;
                                            unIssued << temp;
                                        }
                                        else
                                        {
                                            unIssued << temp << ",";
                                        }
                                        i++;
                                    }
                                    unIssued << endl;
                                    ccount += 2;
                                }
                                else
                                {
                                    unIssued << temp << endl;
                                }
                                ccount++;
                            }
                        }
                        userFile.close();
                        unIssued.close();
                        remove("userFile.txt");
                        rename("userFile2.txt", "userFile.txt");
                        newFile << endl;
                        getline(bookFile,line);
                        newFile << endl;
                    }
                    else
                    {
                        newFile << line << endl;
                        getline(bookFile, line);
                        newFile << line << endl;
                        getline(bookFile, line);
                        newFile << line << endl;
                        getline(bookFile, line);
                        newFile << line << endl;
                    }
                    count += 4;
                }
                else
                {
                    newFile << line << endl;
                    count++;
                }
            }
        }
        bookFile.close();
        newFile.close();
        remove("bookFile.txt");
        rename("bookFile2.txt", "bookFile.txt");
    }
    void bookIssuedTo()
    {
        cout << "Enter the ISBN of the book" << endl;
        getchar();
        string ISBN;
        getline(cin, ISBN);
        fstream bookFile;
        bookFile.open("bookFile.txt");
        if (bookFile.is_open())
        {
            string line;
            int count = 0;
            while (getline(bookFile, line))
            {
                if (line == ISBN && (count + 1) % 6 == 3)
                {
                    getline(bookFile, line);
                    getline(bookFile, line);
                    cout << "--------------------------------" << endl;
                    if (line != "")
                        cout << "book is issued to:" << line << endl;
                    else
                        cout << "this book is not issued to anyone" << endl;
                    cout << "--------------------------------" << endl;
                    getline(bookFile, line);
                    count += 4;
                }
                else
                    count++;
            }
        }
        bookFile.close();
    }
    void checkIssue()
    {
        cout << "enter the book name you want to check" << endl;
        string bookname;
        getline(cin, bookname);
        fstream bookFile;
        bookFile.open("bookFile.txt", ios::in);
        if (bookFile.is_open())
        {
            string line;
            while (getline(bookFile, line))
            {
                if (line == bookname)
                {
                    getline(bookFile, line);
                    getline(bookFile, line);
                    getline(bookFile, line);
                    getline(bookFile, line);
                    if (line == "")
                    {
                        cout << "this book is not issued to anyone" << endl;
                    }
                    else
                    {
                        cout << "this book is already issued to someone" << endl;
                    }
                    getline(bookFile,line);
                }
            }
        }
    }
};