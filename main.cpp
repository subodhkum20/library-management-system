#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "bookDatabase.cpp"
#include "userDatabase.cpp"
using namespace std;

int main()
{
    bool loggedIn = false;
    while (true)
    {
        userDatabase users;
        bookDatabase books;
        if (!loggedIn)
        {
            user userToLogin;
            string role;
            cout << "Enter your username" << endl;
            getline(cin, userToLogin.username);
            cout << "Enter your password" << endl;
            getline(cin, userToLogin.password);
            if (users.search(userToLogin))
            {
                loggedIn = true;
                cout << "you are successfully logged in" << endl;
            }
            else
            {
                cout << "user does not exists" << endl;
            }
        }
        else
        {
            cout << "press 0 to logout" << endl
                 << "press 1 to go to main menu" << endl;
            int response;
            cin >> response;
            getchar();
            if (response == 0)
            {
                loggedIn = false;
            }
            else
            {
                fstream currUser;
                string line;
                currUser.open("currUser.txt", ios::in);
                if (currUser.is_open())
                {
                    getline(currUser, line);
                    getline(currUser, line);
                    if (line == "librarian")
                    {
                        int libRes;
                        cout << "press 0 to add/delete/update user" << endl
                             << "press 1 to add/update/delete/unissue/issue book" << endl
                             << "press 2 to get the list of all books" << endl
                             << "press 3 to get the list of all users" << endl
                             << "press 4 to get the list of books issued to a user" << endl
                             << "press 5 to get the user to whoom the book is issued" << endl
                             << "press 6 to get the dueDate of a book" << endl;
                        cin >> libRes;
                        if (libRes == 0)
                        {
                            cout << "press 0 to add a user" << endl
                                 << "press 1 to delete a user" << endl
                                 << "press 2 to update a user" << endl;
                            cin >> libRes;
                            if (libRes == 0)
                            {
                                user newUser;
                                string username, password, id, role;
                                cout << "enter the username" << endl;
                                getchar();
                                getline(cin, newUser.username);
                                cout << "enter the password" << endl;
                                getline(cin, newUser.password);
                                cout << "enter the role" << endl;
                                getline(cin, newUser.role);
                                cout << "enter the id" << endl;
                                getline(cin, newUser.id);
                                users.add(newUser);
                            }
                            else if (libRes == 1)
                            {
                                cout << "Enter the id of the user to be deleted" << endl;
                                string id;
                                getchar();
                                getline(cin, id);
                                users.Delete(id);
                            }
                            else if (libRes == 2)
                            {
                                user updateUser;
                                cout << "Enter the id of the user to be updated" << endl;
                                getchar();
                                getline(cin, updateUser.id);
                                cout << "Enter the new username of the user" << endl;
                                getline(cin, updateUser.username);
                                cout << "Enter the new passord of the user" << endl;
                                getline(cin, updateUser.password);
                                cout << "Enter the new role of the user" << endl;
                                getline(cin, updateUser.role);
                                
                                users.update(updateUser);
                            }
                        }
                        else if (libRes == 1)
                        {
                            cout << "press 0 to add a book" << endl
                                 << "press 1 to delete a book" << endl
                                 << "press 2 to update a book" << endl
                                 << "press 3 to unissue a book" << endl
                                 << "press 4 to issue a book" << endl;
                            cin >> libRes;
                            if (libRes == 0)
                            {
                                book newBook;
                                string Title, Author, ISBN, Publication;
                                cout << "enter the book title" << endl;
                                getchar();
                                getline(cin, newBook.Title);
                                cout << "enter the author name" << endl;
                                getline(cin, newBook.Author);
                                cout << "enter the ISBN number" << endl;
                                getline(cin, newBook.ISBN);
                                cout << "enter the publication" << endl;
                                getline(cin, newBook.Publication);
                                books.addBook(newBook);
                            }
                            else if (libRes == 1)
                            {
                                cout << "Enter the ISBN  number of the book to be deleted" << endl;
                                string ISBN;
                                getchar();
                                getline(cin, ISBN);
                                books.deleteBook(ISBN);
                            }
                            else if (libRes == 2)
                            {
                                string updateBook;
                                cout << "Enter the ISBN of the book to be updated" << endl;
                                getchar();
                                getline(cin, updateBook);
                                books.updateBook(updateBook);
                            }
                            else if(libRes==3){
                                books.unissue();
                            }
                            else if(libRes==4){
                                book newbook;
                                newbook.bookRequest();
                            }
                        }
                        else if (libRes == 2)
                        {
                            books.Display();
                        }
                        else if(libRes == 3){
                            users.display();
                        }
                        else if(libRes == 4){
                            users.issuedToUser();
                        }
                        else if(libRes == 5){
                            books.bookIssuedTo();
                        }
                        else if(libRes == 6){
                            book newBook;
                            newBook.dueDate();
                        }
                    }
                    else if (line=="student"){
                        cout<<"press 0 to see all the books"<<endl
                        <<"press 1 to see all the books issued to you"<<endl
                        <<"press 2 to check whether the book can be issued or not"<< endl
                        <<"press 3 to get your fine amount"<< endl
                        <<"press 4 to clear your fine amount"<< endl;
                        int n;
                        cin>>n;
                        getchar();
                        if(n==0){
                            books.Display();
                        }
                        else if(n==1){
                            student you;
                            you.issuedToMe();
                        }
                        else if(n==2){
                            books.checkIssue();
                        }
                        else if(n==3){
                            student you;
                            you.fineAmount();
                        }
                        else if(n==4){
                            student you;
                            you.clearFineAmount();
                        }
                    }
                }
                else
                {
                    cout << "unable to open file" << endl;
                }
            }
        }
    }
}