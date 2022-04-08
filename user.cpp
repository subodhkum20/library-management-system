#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <array>
#include <algorithm>
using namespace std;

class user
{
public:
    string username;
    string id;
    string password;
    string role;
    string books;
};

class student : public user
{
public:
    void issuedToMe()
    {
        fstream currUser;
        currUser.open("currUser.txt", ios::in);
        if (currUser.is_open())
        {
            string line;
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            stringstream ss(line);
            bookDatabase newBook;
            while(getline(ss, line,',')){
                newBook.Search(line);
            }
        }
        currUser.close();
    }
    void fineAmount()
    {
        fstream currUser;
        currUser.open("currUser.txt", ios::in);
        if (currUser.is_open())
        {
            string line;
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            stringstream date(line);
            vector<string> dates;
            vector<array<int,3>> arrDates;
            int i=0;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            array<int,3> today={ltm->tm_mday,ltm->tm_mon+1,ltm->tm_year+1900};
            long int fine=0;
            while (getline(date, line, ','))
            {
                dates.push_back(line);
                stringstream arrDate(line);
                array<int,3> temp;
                int j=0;
                while(getline(arrDate, line, '/')){
                    temp.at(j)=stoi(line);
                    j++;
                }
                arrDates.push_back(temp);
                int days=countNoOfDays(arrDates[i],today);
                if(days>30){
                    fine+=(days-30)*5;
                }
                i++;
            }
            cout<<"Your total fine amount is "<<fine<<endl;
        }
    }
    void clearFineAmount(){
        cout<<"enter the books ISBN number on which you have fine one by one and once you have finished press 0"<<endl;
        int res=1;
        while(res){
            bookDatabase books;
            books.unissue();
            cout<<"press 0 to exit and 1 to continue"<<endl;
            cin>>res;
        }
    }

private:
    const int monthDays[12] = {31, 59, 90, 120, 151, 181, 212, 243,
                               273, 304, 334, 365};
    int countLeapYearDays(array<int,3> d)
    {
        int years = d.at(2);
        if (d.at(1) <= 2)
            years--;
        return ((years / 4) - (years / 100) + (years / 400));
    }
    int countNoOfDays(array<int,3> date1, array<int,3> date2)
    {
        long int dayCount1 = (date1.at(2) * 365);
        dayCount1 += monthDays[date1.at(1)];
        dayCount1 += date1.at(0);
        dayCount1 += countLeapYearDays(date1);
        long int dayCount2 = (date2.at(2) * 365);
        dayCount2 += monthDays[date2.at(1)];
        dayCount2 += date2.at(0);
        dayCount2 += countLeapYearDays(date2);
        return (abs(dayCount1 - dayCount2));
    }
};
class professor : public user
{
public:
    void issuedToMe()
    {
        fstream currUser;
        currUser.open("currUser.txt", ios::in);
        if (currUser.is_open())
        {
            string line;
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            stringstream ss(line);
            bookDatabase newBook;
            while(getline(ss, line)){
                newBook.Search(line);
            }
        }
        currUser.close();
    }
    void fineAmount()
    {
        fstream currUser;
        currUser.open("currUser.txt", ios::in);
        if (currUser.is_open())
        {
            string line;
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            getline(currUser, line);
            stringstream date(line);
            vector<string> dates;
            vector<array<int,3>> arrDates;
            int i=0;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            array<int,3> today={ltm->tm_mday,ltm->tm_mon+1,ltm->tm_year+1900};
            long int fine=0;
            while (getline(date, line, ','))
            {
                dates.push_back(line);
                stringstream arrDate(line);
                array<int,3> temp;
                int j=0;
                while(getline(arrDate, line, '/')){
                    temp.at(j)=stoi(line);
                    j++;
                }
                arrDates.push_back(temp);
                int days=countNoOfDays(arrDates[i],today);
                if(days>30){
                    fine+=(days-30)*2;
                }
                i++;
            }
            cout<<"Your total fine amount is "<<fine<<endl;
        }
    }
    void clearFineAmount(){
        cout<<"enter the books ISBN number on which you have fine one by one and once you have finished press 0"<<endl;
        int res=1;
        while(res){
            bookDatabase books;
            books.unissue();
            cout<<"press 0 to exit and 1 to continue"<<endl;
            cin>>res;
        }
    }

private:
    const int monthDays[12] = {31, 59, 90, 120, 151, 181, 212, 243,
                               273, 304, 334, 365};
    int countLeapYearDays(array<int,3> d)
    {
        int years = d.at(2);
        if (d.at(1) <= 2)
            years--;
        return ((years / 4) - (years / 100) + (years / 400));
    }
    int countNoOfDays(array<int,3> date1, array<int,3> date2)
    {
        long int dayCount1 = (date1.at(2) * 365);
        dayCount1 += monthDays[date1.at(1)];
        dayCount1 += date1.at(0);
        dayCount1 += countLeapYearDays(date1);
        long int dayCount2 = (date2.at(2) * 365);
        dayCount2 += monthDays[date2.at(1)];
        dayCount2 += date2.at(0);
        dayCount2 += countLeapYearDays(date2);
        return (abs(dayCount1 - dayCount2));
    }
};