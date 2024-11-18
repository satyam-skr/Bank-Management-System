#include <bits/stdc++.h>
using namespace std;
class BranchEmployee;
class HeadEmployee;
class Account;
class SavingsAccount;
class CurrentAccount;
class Employee
{
protected:
    string name;
    int dob; // ddmmyy
    string post;
    int salary;

public:
    virtual void display() = 0;
};

class BranchEmployee : public Employee
{
    string branch;
    int doj;

public:
    void display() override
    {
        cout << "--------------------------" << endl;
        cout << "Name: " << name << endl;
        cout << "Post: " << post << endl;
        cout << "Branch: " << branch << endl;
        cout << "Date of Birth(ddmmyyyy): " << dob / 1000000 << "-" << (dob / 10000) % 100 << "-" << dob % 10000 << endl;
        cout << "Date of Joining: " << doj << endl;
        cout << "Salary: " << salary << endl;
        cout << "--------------------------" << endl;
    }

    friend void loadbanksemp();
    friend class Bank;
};

class HeadEmployee : public Employee
{
    int doj;

public:
    void display() override
    {
        cout << "--------------------------" << endl;
        cout << "Name: " << name << endl;
        cout << "Post: " << post << endl;
        cout << "Date of Birth(ddmmyyyy): " << dob / 1000000 << "-" << (dob / 10000) % 100 << "-" << dob % 10000 << endl;
        cout << "Date of Joining: " << doj << endl;
        cout << "Salary: " << salary << endl;
        cout << "--------------------------" << endl;
    }

    friend void loadheadofficeemp();
    friend class HeadOffice;
};

class SavingsAccount;
class CurrentAccount;

class Bank
{
    string branch;
    string IFSC;
    vector<BranchEmployee> allBranchEmployees;
    vector<SavingsAccount> allSavingsAccounts;
    vector<CurrentAccount> allCurrentAccounts;

public:
    int minBalCurrent;
    int minBalSavings;
    int rateOfInterest;

public:
    void addBranchEmployee();
    void openSavingsAccount();
    void openCurrentAccount();
    void loadSavingsAccounts();
    void loadCurrentAccounts();
    bool loaded = false;
    string getifsc()
    {
        return IFSC;
    }
    void display()
    {
        cout << "--------------------------" << endl;
        cout << "Branch Name: " << branch << endl;
        cout << "IFSC Code: " << IFSC << endl;
        cout << "Minimum Balance (Current): " << minBalCurrent << endl;
        cout << "Minimum Balance (Savings): " << minBalSavings << endl;
        cout << "Rate of Interest: " << rateOfInterest << "%" << endl;
        cout << "Number of Branch Employees: " << allBranchEmployees.size() << endl;
        cout << "--------------------------" << endl;
    }
    void displayNoOfAccounts()
    {
        cout << "Number of Savings Accounts: " << allSavingsAccounts.size() << endl;
        cout << "Number of Current Accounts: " << allCurrentAccounts.size() << endl
             << endl;
    }
    void displayAllSavingsAccounts();

    void displayAllCurrentAccounts();

    void displayAllBranchEmployees()
    {
        cout << "Displaying All Branch Employees:" << endl;
        cout << "--------------------------" << endl;
        for (auto &employee : allBranchEmployees)
        {
            employee.display();
        }
    }
    friend SavingsAccount *pointerToSavingsAccount(Bank &b, int accno);
    friend CurrentAccount *pointerToCurrentAccount(Bank &b, int accno);
    friend void loadheadofficebanks();
    friend void loadbanksemp();
    friend class HeadOffice;
};

class HeadOffice
{
    vector<Bank> allBanks;
    vector<HeadEmployee> allHeadEmployees;

public:
    void addBank();
    void addBank(Bank bank);
    void addHeadEmployee();
    void addHeadEmployee(HeadEmployee he);

    void displayAllBanks()
    {
        cout << "Displaying All Banks:" << endl;
        cout << "--------------------------" << endl;
        for (auto &bank : allBanks)
        {
            bank.display();
        }
    }
    void displayAllHeadEmployees()
    {
        cout << "Displaying All Head Employees:" << endl;
        cout << "--------------------------" << endl;
        for (auto &employee : allHeadEmployees)
        {
            employee.display();
        }
    }

    Bank *getBankByIFSC(const string &ifsc)
    {
        for (auto &bank : allBanks)
        {
            if (bank.IFSC == ifsc)
            {
                return &bank;
            }
        }
        return nullptr;
    }

    friend void loadbanksemp();
};

class Account
{
public:
    int accountnumber;
    string pin;
    string holdername;
    double balance;

public:
    void deposit(Bank *selectedbank, double amount);
    virtual void withdraw(double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient balance!" << endl;
        }
        else
        {
            balance -= amount;
            cout << "Withdrew " << amount << ". New Balance: " << balance << endl;
        }
    }

    int getBalance()
    {
        return balance;
    }
    string getHolderName()
    {
        return holdername;
    }
    int getAccountNumber()
    {
        return accountnumber;
    }

    string getpin()
    {
        return pin;
    }
    void displayAccountDetails()
    {
        cout << "Holder Name: " << holdername << endl;
        cout << "Account Number: " << accountnumber << endl;
        cout << "pin: " << pin << endl;
        cout << "Balance: " << balance << endl;
        cout << "----------------------------------\n";
    }
};

class SavingsAccount : public Account
{
    int minBal;
    bool overdraft;
    int rateOfInterest;

public:
    SavingsAccount(int mb = 0, bool od = false, int roi = 6)
        : minBal(mb), overdraft(od), rateOfInterest(roi) {}

    friend SavingsAccount *pointerToSavingsAccount(Bank &obj, int accno);
    friend class Bank;
};

class CurrentAccount : public Account
{
    int minBal;
    bool overdraft;

public:
    CurrentAccount(int mb = 0, bool od = true)
        : minBal(mb), overdraft(od) {}

    void withdraw(double amount)
    {
        if (amount > balance)
        {
            cout << "Alert! Negative Balance." << endl;
        }

        balance -= amount;
        cout << "Withdrew " << amount << ". New Balance: " << balance << endl;
    }

    friend CurrentAccount *pointerToCurrentAccount(Bank &obj, int accno);
    friend class Bank;
};

// Implementing HeadOffice functions
void HeadOffice::addBank()
{
    Bank newBank;
    cout << "\n---------Enter details of new Bank-----------\n";
    cout << "Enter Branch Name: ";
    cin >> newBank.branch;
    cout << "Enter IFSC code: ";
    cin >> newBank.IFSC;
    cout << "Enter minimum Balance for current account: ";
    cin >> newBank.minBalCurrent;
    cout << "Enter minimum Balance for savings account: ";
    cin >> newBank.minBalSavings;
    cout << "Enter rate of interest in savings account: ";
    cin >> newBank.rateOfInterest;

    for (auto &x : allBanks)
    {
        if (x.IFSC == newBank.IFSC)
        {
            cout << "\nThis Branch is already there\n";
            return;
        }
    }
    allBanks.push_back(newBank);
    cout << "\n-----------------Bank added successfully------------------\n";
    ofstream fout;
    fout.open("headofficebanks.txt", ios::binary | ios::app);
    fout << newBank.branch << " " << newBank.IFSC << " " << newBank.minBalCurrent << " " << newBank.minBalSavings << " " << newBank.rateOfInterest << endl;
    fout.close();
}
void HeadOffice::addBank(Bank bank)
{
    allBanks.push_back(bank);
}

void HeadOffice::addHeadEmployee()
{
    HeadEmployee newheademp;
    cout << "\n---------Enter details of new Head Employee-----------\n";
    cout << "Enter Name: ";
    getchar();
    getline(cin, newheademp.name);
    cout << "Enter post: ";
    getline(cin, newheademp.post);
    cout << "Enter Date of Birth: ";
    cin >> newheademp.dob;
    cout << "Enter Date of Joining: ";
    cin >> newheademp.doj;
    cout << "Enter Salary: ";
    cin >> newheademp.salary;
    allHeadEmployees.push_back(newheademp);
    cout << "\n----------Employee added successfully----------\n";
    ofstream fout;
    fout.open("headofficeemp.txt", ios::binary | ios::app);
    fout << newheademp.name << endl;
    fout << newheademp.post << endl;
    fout << newheademp.dob << " " << newheademp.doj << " " << newheademp.salary << endl;
    fout.close();
}
void HeadOffice ::addHeadEmployee(HeadEmployee he)
{
    allHeadEmployees.push_back(he);
}

void Bank::addBranchEmployee()
{
    BranchEmployee newbranchemp;
    cout << "\n---------Enter details of new Branch Employee-----------\n";
    getchar();
    cout << "Enter Name: ";
    getline(cin, newbranchemp.name);
    cout << "Enter post: ";
    getline(cin, newbranchemp.post);
    cout << "Enter Branch: ";
    cin >> newbranchemp.branch;
    cout << "Enter Date of Birth: ";
    cin >> newbranchemp.dob;
    cout << "Enter Date of Joining: ";
    cin >> newbranchemp.doj;
    cout << "Enter Salary: ";
    cin >> newbranchemp.salary;
    allBranchEmployees.push_back(newbranchemp);
    cout << "\n----------Employee added successfully----------\n";
    ofstream fout;
    fout.open(this->IFSC + "emp.txt", ios::binary | ios::app);
    fout << newbranchemp.name << endl;
    fout << newbranchemp.post << endl;
    fout << newbranchemp.branch << " " << newbranchemp.dob << " " << newbranchemp.doj << " " << newbranchemp.salary << endl;
    fout.close();
}

void Bank ::openSavingsAccount()
{
    SavingsAccount newsavacc;
    cout << "\n---------------Enter the details to open account-----------\n";
    getchar();
    cout << "Enter Account Holder name: ";
    getline(cin, newsavacc.holdername);
    cout << "Enter account number : ";
    cin >> newsavacc.accountnumber;
    cout << "Enter pin : ";
    cin >> newsavacc.pin;
    newsavacc.balance = 0;
    newsavacc.minBal = minBalSavings;

    allSavingsAccounts.push_back(newsavacc);
    cout << "-------------------Account opened Successfully-----------------------\n";

    ofstream fout(this->IFSC + "_savings_accounts.txt", ios::app); // appends data to file
    fout << newsavacc.holdername << "\n"
         << newsavacc.accountnumber << " " << newsavacc.pin << "\n"
         << newsavacc.balance << " " << endl;
    fout.close();
}

void Bank ::openCurrentAccount()
{
    CurrentAccount newcurracc;
    cout << "\n---------------Enter the details to open account-----------\n";
    getchar();
    cout << "Enter Account Holder name: ";
    getline(cin, newcurracc.holdername);
    cout << "Enter account number : ";
    cin >> newcurracc.accountnumber;
    cout << "Enter pin : ";
    cin >> newcurracc.pin;
    newcurracc.balance = 0;
    newcurracc.minBal = minBalCurrent;

    allCurrentAccounts.push_back(newcurracc);
    cout << "-------------------Account opened Successfully-----------------------\n";

    ofstream fout(this->IFSC + "_current_accounts.txt", ios::app); // appends data to file
    fout << newcurracc.holdername << "\n"
         << newcurracc.accountnumber << " " << newcurracc.pin << "\n"
         << newcurracc.balance << " " << endl;
    fout.close();
}

void Bank ::displayAllSavingsAccounts()
{
    for (auto &x : this->allSavingsAccounts)
    {
        x.displayAccountDetails();
    }
}
void Bank ::displayAllCurrentAccounts()
{
    for (auto &x : allCurrentAccounts)
    {
        x.displayAccountDetails();
    }
}

SavingsAccount *pointerToSavingsAccount(Bank &obj, int accno)
{
    auto it = obj.allSavingsAccounts.end(); // Initialize to end

    for (auto &x : obj.allSavingsAccounts)
    {
        if (x.accountnumber == accno)
        {
            return &x;
            break;
        }
    }
    return 0;
}

CurrentAccount *pointerToCurrentAccount(Bank &obj, int accno)
{
    auto it = obj.allCurrentAccounts.end(); // Initialize to end

    for (auto &x : obj.allCurrentAccounts)
    {
        if (x.accountnumber == accno)
        {
            return &x;
            break;
        }
    }
    return nullptr;
}

void changepinofsavingsaccount(Bank *selectedbank, SavingsAccount *selectedSA, string oldpass, string newpass)
{
    fstream file;
    string filename = selectedbank->getifsc() + "_savings_accounts.txt";
    file.open(filename, ios::in);

    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string fileContent;
    string line;
    bool accountFound = false;

    // Read each line and check if it contains the account number
    while (getline(file, line))
    {
        int accountNumInFile;
        string pinInFile;

        istringstream iss(line);
        iss >> accountNumInFile >> pinInFile;

        // Check if this line matches the account
        if (accountNumInFile == selectedSA->accountnumber)
        {
            if (pinInFile == oldpass)
            {
                // Replace the pin in this line
                accountFound = true;
                line = to_string(accountNumInFile) + " " + newpass;
                cout << "pin changed successfully\n";
            }
            else
            {
                cout << "Old pin does not match\n";
                return;
            }
        }
        fileContent += line + "\n";
    }

    file.close();

    // Write the updated content back to the file if the account was found
    if (accountFound)
    {
        file.open(filename, ios::out | ios::trunc);
        if (!file.is_open())
        {
            cout << "Error opening file for writing!" << endl;
            return;
        }
        file << fileContent;
        file.close();
    }
    else
    {
        cout << "Account not found\n";
    }
}

void changepinofcurrentaccount(Bank *selectedbank, CurrentAccount *selectedCA, string oldpass, string newpass)
{
    fstream file;
    string filename = selectedbank->getifsc() + "_current_accounts.txt";
    file.open(filename, ios::in);

    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string fileContent;
    string line;
    bool accountFound = false;

    // Read each line and check if it contains the account number
    while (getline(file, line))
    {
        int accountNumInFile;
        string pinInFile;

        istringstream iss(line);
        iss >> accountNumInFile >> pinInFile;

        // Check if this line matches the account
        if (accountNumInFile == selectedCA->accountnumber)
        {
            if (pinInFile == oldpass)
            {
                // Replace the pin in this line
                accountFound = true;
                line = to_string(accountNumInFile) + " " + newpass;
                cout << "pin changed successfully\n";
            }
            else
            {
                cout << "Old pin does not match\n";
                return;
            }
        }
        fileContent += line + "\n";
    }

    file.close();

    // Write the updated content back to the file if the account was found
    if (accountFound)
    {
        file.open(filename, ios::out | ios::trunc);
        if (!file.is_open())
        {
            cout << "Error opening file for writing!" << endl;
            return;
        }
        file << fileContent;
        file.close();
    }
    else
    {
        cout << "Account not found\n";
    }
}

void Account::deposit(Bank *selectedbank, double amount)
{
    // Update the balance in memory
    balance += amount;
    cout << "Deposited " << amount << ". New Balance: " << balance << endl;

    // Prepare to open and read the file
    fstream file;
    string filename = selectedbank->getifsc() + "_savings_accounts.txt";
    file.open(filename, ios::in);

    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    // Read the file contents into a vector to store each line
    vector<string> lines;
    string line;
    bool accountFound = false;

    while (getline(file, line))
    {
        int accountNumInFile;
        string pinInFile;
        double balanceInFile;

        // Read account details from the line
        istringstream iss(line);
        iss >> accountNumInFile >> pinInFile >> balanceInFile;

        // Check if the account number matches
        if (accountNumInFile == accountnumber)
        {
            // Update the balance for this account
            line = to_string(accountNumInFile) + " " + pinInFile + "\n" + to_string(balance);
            accountFound = true;
        }

        // Add the line (modified or unmodified) to the vector
        lines.push_back(line);
    }

    file.close();

    // Write the updated content back to the file if the account was found
    if (accountFound)
    {
        file.open(filename, ios::out | ios::trunc);
        if (!file.is_open())
        {
            cout << "Error opening file for writing!" << endl;
            return;
        }

        // Write each line back to the file, preserving original structure
        for (const auto &l : lines)
        {
            file << l << endl;
        }
        file.close();
        cout << "Balance updated in file." << endl;
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

// Global instance for HeadOffice
HeadOffice wowbank;

void loadheadofficebanks()
{
    ifstream fin("headofficebanks.txt");
    if (!fin)
    {
        return;
    }

    string branch, ifsc;
    int minBalCurrent, minBalSavings, rateOfInterest;

    while ((fin >> branch) && (fin >> ifsc) && (fin >> minBalCurrent) && (fin >> minBalSavings) && (fin >> rateOfInterest))
    {

        fin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to the next line for the next bank

        Bank bank;
        bank.branch = branch;
        bank.IFSC = ifsc;
        bank.minBalCurrent = minBalCurrent;
        bank.minBalSavings = minBalSavings;
        bank.rateOfInterest = rateOfInterest;

        wowbank.addBank(bank);
    }

    fin.close();
}

void loadheadofficeemp()
{
    ifstream fin2("headofficeemp.txt", ios::binary);

    if (!fin2)
    {
        return;
    }

    string name, post;
    int dob, doj, salary;

    // Ensure each read operation is successful
    while (getline(fin2, name) && getline(fin2, post) && fin2 >> dob >> doj >> salary)
    {
        fin2.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in the line

        HeadEmployee he;
        he.name = name;
        he.post = post;
        he.dob = dob;
        he.doj = doj;
        he.salary = salary;

        wowbank.addHeadEmployee(he);
    }

    fin2.close();
}

void loadbanksemp()
{
    vector<Bank> *allbanks = &wowbank.allBanks;
    for (auto &x : *allbanks)
    {
        string name, post, branch;
        int dob, doj, salary;

        ifstream fin(x.IFSC + "emp.txt"); // Open the file corresponding to the bank's IFSC code
        if (!fin)
        {
            continue;
        }

        while (getline(fin, name) && getline(fin, post) && fin >> branch >> dob >> doj >> salary)
        {
            fin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in the line

            BranchEmployee be;
            be.name = name;
            be.post = post;
            be.branch = branch;
            be.dob = dob;
            be.doj = doj;
            be.salary = salary;
            x.allBranchEmployees.push_back(be);
        }

        fin.close(); // Close the file after reading all employees
    }
}

void Bank::loadSavingsAccounts()
{
    ifstream fin(this->IFSC + "_savings_accounts.txt");
    if (!fin)
    {
        return;
    }

    int accno, balance;
    string pass, holdername;
    // name \n accno pass \n balance \n

    while (getline(fin, holdername) && fin >> accno && fin >> pass && fin >> balance)
    {

        fin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to the next line for the next bank

        SavingsAccount sa;
        sa.holdername = holdername;
        sa.accountnumber = accno;
        sa.balance = balance;
        sa.pin = pass;
        (this->allSavingsAccounts).push_back(sa);
    }

    fin.close();
}

void Bank::loadCurrentAccounts()
{
    ifstream fin(this->IFSC + "_current_accounts.txt");
    if (!fin)
    {
        return;
    }

    int accno, balance;
    string pass, holdername;
    // name \n accno pass \n balance \n

    while (getline(fin, holdername) && fin >> accno && fin >> pass && fin >> balance)
    {

        fin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to the next line for the next bank

        CurrentAccount ca;
        ca.holdername = holdername;
        ca.accountnumber = accno;
        ca.balance = balance;
        ca.pin = pass;
        (this->allCurrentAccounts).push_back(ca);
    }

    fin.close();
}

int main()
{
    loadheadofficebanks();
    loadheadofficeemp();
    loadbanksemp();
    string adminpass = "123";
    string enteredpass;
    do
    {
        cout << "Enter pin: ";
        cin >> enteredpass;
        if (adminpass != enteredpass)
        {
            cout << "Wrong pin\nTry again\n";
        }
    } while (enteredpass != adminpass);
    cout << "\n-----------------LoggedIn Successfully-----------------------------\n";

    int choice;
label2:
    do
    {
        cout << "\nEnter 1 to display all branches of banks\n";
        cout << "Enter 2 to display all employees in head office\n";
        cout << "Enter 3 to add bank\n";
        cout << "Enter 4 for add employee in head office\n";
        cout << "Enter 5 to login as admin of a bank\n";
        cout << "Enter 6 to exit\n";
        cout << "Enter your choice : ";
        cin >> choice;
        if (choice == 1)
        {
            wowbank.displayAllBanks();
        }
        else if (choice == 2)
        {
            wowbank.displayAllHeadEmployees();
        }
        else if (choice == 3)
        {
            wowbank.addBank();
        }
        else if (choice == 4)
        {
            wowbank.addHeadEmployee();
        }
        else if (choice == 5)
        {
        }
        else if (choice == 6)
        {
            cout << "Thank You!\n";
            return 0;
        }
        else
        {
            cout << "Enter valid option\n";
            goto label2;
        }
    } while (choice != 5);

label3:
    string enteredifsc;
    cout << "\n\nEnter the IFSC code of the bank : ";
    cin >> enteredifsc;
    Bank *selectedbank = wowbank.getBankByIFSC(enteredifsc);
    if (selectedbank == nullptr)
    {
        cout << "Bank with IFSC code " << enteredifsc << " not found\n";
        goto label3;
    }

    if (selectedbank->loaded == false)
    {
        selectedbank->loadSavingsAccounts();
        selectedbank->loadCurrentAccounts();
        selectedbank->loaded = true;
    }

    selectedbank->display();
    selectedbank->displayNoOfAccounts();

label4:
    int choice2;
    do
    {
        cout << "\nEnter 1 to display the detials of this Bank\n";
        cout << "Enter 2 to display employees of this branch\n";
        cout << "Enter 3 to add employee in this branch\n";
        cout << "Enter 4 to open an account in this branch\n";
        cout << "Enter 5 to become admin of an account\n";
        cout << "Enter 6 to display all savings accounts\n";
        cout << "Enter 7 to display all current accounts\n";
        cout << "Enter 8 to exit\n";
        cout << "Enter 0 to go back\n";
        cin >> choice2;

        if (choice2 == 1)
        {
            selectedbank->display();
            selectedbank->displayNoOfAccounts();
        }
        else if (choice2 == 2)
        {
            selectedbank->displayAllBranchEmployees();
        }
        else if (choice2 == 3)
        {
            selectedbank->addBranchEmployee();
        }
        else if (choice2 == 4)
        {
        label5:
            int choice3;
            cout << "\nEnter 1 to open Savings Account\n";
            cout << "Enter 2 to open Current Account\n";
            cout << "Enter 3 to exit\n";
            cout << "Enter 0 to go back\n";
            cout << "Enter your choice : ";
            cin >> choice3;
            if (choice3 == 1)
            {
                selectedbank->openSavingsAccount();
            }
            else if (choice3 == 2)
            {
                selectedbank->openCurrentAccount();
            }
            else if (choice3 == 3)
            {
                cout << "\nThank you!\n";
                return 0;
            }
            else if (choice3 == 0)
            {
                goto label4;
            }
            else
            {
                cout << "Invalid Choice. Enter a valid choice : ";
                goto label5;
            }
        }
        else if (choice2 == 5)
        {
        }
        else if (choice2 == 6)
        {
            selectedbank->displayAllSavingsAccounts();
        }
        else if (choice2 == 7)
        {
            selectedbank->displayAllCurrentAccounts();
        }
        else if (choice2 == 8)
        {
            cout << "Thank You!\n";
            return 0;
        }
        else if (choice2 == 0)
        {
            goto label2;
        }
        else
        {
            cout << "Invalid Entry! Try again\n";
            goto label4;
        }
    } while (choice2 != 5);

    // controller of an account
    int choice3;
    int accno, type;
label7:
    cout << "\nEnter account number : ";
    cin >> accno;
    cout << "\nEnter type\n\t 1 for savings 2 for current : ";
    cin >> type;
    if (type == 1)
    {
        SavingsAccount *selectedSA = pointerToSavingsAccount(*(selectedbank), accno);
        if (selectedSA == nullptr)
        {
            cout << "No data found\n Try again\n";
            goto label7;
        }
        do
        {
            cout << "Enter 1 to change pin\nEnter 2 to withdraw\nEnter 3 to deposit\nEnter 4 to exit\nEnter 0 to go back\n";
            cout << "Enter your choice : ";
            cin >> choice3;
            if (choice3 == 1)
            {
            label8:
                string oldpass, newpass;
                cout << "Enter old pin : ";
                cin >> oldpass;
                if (oldpass != selectedSA->getpin())
                {
                    cout << "Incorrect pin\n Try again\n";
                    goto label8;
                }
                cout << "Enter new pin : ";
                cin >> newpass;
                changepinofsavingsaccount(selectedbank, selectedSA, oldpass, newpass);
            }
            if (choice3 == 2)
            {
            label9:
                double amount;
                cout << "Enter amount to withdraw : ";
                cin >> amount;
                if (selectedSA->getBalance() < amount)
                {
                    cout << "Insufficient Balance\n";
                    goto label9;
                }
                selectedSA->withdraw(amount);
                if (selectedSA->getBalance() < selectedbank->minBalSavings)
                {
                    cout << "Alert! your balance is less than minimum balance\n";
                }
            }
            if (choice3 == 3)
            {
                double amount;
                cout << "Enter amount to deposit : ";
                cin >> amount;
                selectedSA->deposit(selectedbank, amount);
            }
            if (choice3 == 4)
            {
                cout << "\nThank You!\nExiting...\n";
                return 0;
            }
            if (choice3 == 0)
            {
                goto label7;
            }
            else
            {
                cout << "Invalid choice\n";
            }
        } while (choice3 != 4);
    }
    else if (type == 2)
    {
        CurrentAccount *selectedCA = pointerToCurrentAccount(*(selectedbank), accno);
        if (selectedCA == nullptr)
        {
            cout << "No data found \n Try again\n";
            goto label7;
        }
        do
        {
            cout << "Enter 1 to change pin\nEnter 2 to withdraw\nEnter 3 to deposit\nEnter 4 to exit\nEnter 0 to go back\n";
            cout << "Enter your choice : ";
            cin >> choice3;
            if (choice3 == 1)
            {
            label10:
                string oldpass, newpass;
                cout << "Enter old pin : ";
                cin >> oldpass;
                if (oldpass != selectedCA->getpin())
                {
                    cout << "Incorrect pin\n Try again\n";
                    goto label10;
                }
                cout << "Enter new pin : ";
                cin >> newpass;
                changepinofcurrentaccount(selectedbank, selectedCA, oldpass, newpass);
            }
            if (choice3 == 2)
            {
            label11:
                double amount;
                cout << "Enter amount to withdraw : ";
                cin >> amount;
                selectedCA->withdraw(amount);
                if (selectedCA->getBalance() < selectedbank->minBalSavings)
                {
                    cout << "Alert! your balance is less than minimum balance\n";
                }
            }
            if (choice3 == 3)
            {
                double amount;
                cout << "Enter amount to deposit : ";
                cin >> amount;
                selectedCA->deposit(selectedbank, amount);
                ;
            }
            if (choice3 == 4)
            {
                cout << "\nThank You!\nExiting...\n";
                return 0;
            }
            if (choice3 == 0)
            {
                goto label7;
            }
            else
            {
                cout << "Invalid choice\n";
            }
        } while (choice3 != 4);
    }
    else
    {
        cout << "You fooline me! Go back\n";
        goto label7;
    }
}