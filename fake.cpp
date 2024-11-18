#include<bits/stdc++.h>
using namespace std;

int main()
{
    fstream f;
    f.open("headofficebanks.txt", ios::in);
    while(!f.eof())
    {
        string s;
        getline(f,s);
        istringstream iss(s);
        string ss;
        iss>>ss;
        iss>>ss;
        ofstream file;
        file.open(ss+"_current_accounts.txt",ios::out);
        file.close();
        ofstream file1;
        file1.open(ss+"_savings_accounts.txt",ios::out);
        file1.close();
    }
}