#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <ctime>
#include "user.cpp"
using namespace std;

class userDatabase
{
public:
    vector<user> users;
    void add(user newUser)
    {
        fstream userFile;
        userFile.open("userFile.txt", ios::app);
        userFile << newUser.username << "\n";
        userFile << newUser.password << "\n";
        userFile << newUser.role << "\n";
        userFile << newUser.id << "\n";
        userFile << "\n";
        userFile << "\n";
        cout << "user has been added" << endl;
        userFile.close();
    }
    void update(user toUpdate)
    {
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
                if (id != toUpdate.id)
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
                    newFile << toUpdate.role << endl;
                    newFile << id << endl;
                    if (toUpdate.books != "0")
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
                                    if (toUpdate.books == line)
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
                                            newBook << toUpdate.id << endl;
                                            time_t now = time(0);
                                            tm *ltm = localtime(&now);
                                            newBook << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                                            getline(issueBook, line);
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
                                newFile << books << "," << toUpdate.books << endl;
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
                                newFile << toUpdate.books << endl;
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
    void Delete(string userToDelete)
    {
        fstream userFile, newFile;
        bool exists = false;
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
                if (id != userToDelete)
                {
                    cout << id << endl;
                    newFile << username << endl;
                    newFile << password << endl;
                    newFile << role << endl;
                    newFile << id << endl;
                    newFile << books << endl;
                    newFile << dateIssued << endl;
                }
                else
                    exists = true;
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
            cout << "user has been deleted" << endl;
        }
    }
    bool search(user userToSearch)
    {
        fstream userFile;
        userFile.open("userFile.txt", ios::in);
        if (userFile.is_open())
        {
            string line;
            while (getline(userFile, line))
            {
                if (line == userToSearch.username)
                {
                    getline(userFile, line);
                    if (userToSearch.password == line)
                    {
                        // userFile.close();
                        fstream currUser;
                        currUser.open("currUser.txt", ios::out);
                        if (currUser.is_open())
                        {
                            currUser << userToSearch.username << endl;
                            getline(userFile, line);
                            currUser << line << endl;
                            getline(userFile, line);
                            currUser << line << endl;
                            getline(userFile, line);
                            currUser << line << endl;
                            getline(userFile, line);
                            currUser << line << endl;
                        }
                        currUser.close();
                        return true;
                    }
                    else
                    {
                        getline(userFile, line);
                        getline(userFile, line);
                        getline(userFile, line);
                        getline(userFile, line);
                    }
                }
            }
        }
        userFile.close();
        return false;
    }
    void display()
    {
        fstream userFile;
        userFile.open("userFile.txt", ios::in);
        if (userFile.is_open())
        {
            string line;
            int count = 0;
            while (getline(userFile, line))
            {
                if ((count + 1) % 6 == 1)
                {
                    cout << "--------------------------------" << endl;
                    cout << endl;
                }
                if ((count + 1) % 6 == 1)
                {
                    cout << "Username:" << line << endl;
                }
                else if ((count + 6) % 5 == 2)
                {
                    ;
                }
                else if ((count + 6) % 5 == 3)
                {
                    cout << "Role:" << line << endl;
                }
                if ((count + 1) % 6 == 4)
                {
                    cout << "id:" << line << endl;
                }
                if ((count + 1) % 6 == 5)
                {
                    cout << "books:" << line << endl;
                }
                if ((count + 1) % 6 == 0)
                {
                    cout << "dateIssued:" << line << endl;
                }
                count++;
            }
            cout << "--------------------------------" << endl;
            cout << endl;
        }
    }
    void issuedToUser()
    {
        cout << "enter the id of the user" << endl;
        getchar();
        string userId;
        getline(cin, userId);
        fstream userFile;
        userFile.open("userfile.txt");
        if (userFile.is_open())
        {
            string line;
            int count = 0;
            while (getline(userFile, line))
            {
                if (line == userId && (count + 1) % 5 == 4)
                {
                    getline(userFile, line);
                    cout << "books issued to the user " << line << endl;
                    count += 2;
                }
                else
                    count++;
                ;
            }
        }
        userFile.close();
    }
};