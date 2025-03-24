// add deposite sucess and new amount
// add withdraw sucess and new amount 
// error check
#include <iostream>
#include <string>
#include <memory>
#include <exception>
#include <cmath>
#include <limits>
#include <unistd.h>

using namespace std;

class NegativeDepositException : public exception 
{
    const char* what() const noexcept
    {
        return "Negative amount deposited, please enter a postive number to deposite.";
    }
};

class NegativeWithdrawException : public exception 
{
    const char* what() const noexcept
    {
        return "Negative amount withdrawn, please enter a positive number to withdraw.";
    }
};

class OverdrawException : public exception 
{
    const char* what() const noexcept
    {
        return "Withdraw amount exceeds account balance, please select a valide withdraw amount.";
    }
};

class InvalidAccountOperationException : public exception 
{
    const char* what() const noexcept
    {
        return "Account Closed, cannot preform actions on closed account";
    }
};

class BankAccount// holds all the input validation functions used in other classes and functions
{
    private:
        string accountNumber;
        double balance;
        bool isActive;
    public:

    BankAccount(string accountNum, double balanceInit): accountNumber(accountNum), balance(balanceInit), isActive(true) {}

    void deposite (double amount)
    {
        if (isActive == false)
            throw InvalidAccountOperationException();
        if (amount < 0 )
            throw NegativeDepositException ();
        balance = balance + amount;
        cout<<"Succesful Deposite"<<endl;
    }

    void withdraw (double amount)
    {
        if (isActive == false)
            throw InvalidAccountOperationException();
        if (amount > balance)
            throw OverdrawException();
        if (amount < 0 )
            throw NegativeWithdrawException();
        balance = balance - amount;
        cout<<"Succesful Withdraw"<<endl;
    }

    void getBalance ()
    {
        if (isActive == false)
            throw InvalidAccountOperationException();
        cout<<"Current Balance: $"<< balance<< endl;
    }

    void closeAccount ()
    {
        if (isActive == false)
            throw InvalidAccountOperationException();

        isActive = false;
        cout<<"Account closed Sucesfully"<<endl;
    }
};


int InputValidation (int min, int max);// input validation for menu selection
double InputValidation (int min);// overloaded function that provided input validation for integets that have a min value
double InputValidation ();// overloaded function to take the input for starting balance
string AccountNumberInputValidation ();// account number input validation


main ()
{
bool exit=false;
string account_number;
double transaction;
int menu_opiton;

    cout<<"Please create a 6 digit account number: ";
    account_number = AccountNumberInputValidation ();
    cout<<"Please enter a starting balance: ";
    transaction = InputValidation ();
    auto account = make_unique<BankAccount>(account_number, transaction);

    do
    {
        cout<<endl<<endl;
        cout<<"-------------Welcome to the Best Bank-------------!"<<endl;
        cout<<"Please selection one of the following menu options."<<endl;
        cout<<"1) Deposite"<<endl;
        cout<<"2) Withdraw"<<endl;
        cout<<"3) Get Balance"<<endl;
        cout<<"4) Close Account"<<endl;
        cout<<"5) Exit"<<endl;
        cout<<"Enter number between 1-5: ";
        menu_opiton = InputValidation ( 1, 5);// input validation for menu selection;  ;
        try
        {
            switch (menu_opiton)
            {
            case 1:
                cout<<endl<<"Please enter amount you would like to deposite: ";
                transaction = InputValidation (0);// input validation to make sure value is a number;        
                account->deposite(transaction);
                break;
            case 2:
                cout<<endl<<"Please enter amount you would like to withdraw: ";
                transaction = InputValidation (0);// input validation to make sure value is a number      
                account->withdraw(transaction);
                break;
            case 3:
                account->getBalance();
                sleep(1);
                break;
            case 4:
                account->closeAccount();
                break;
            case 5: 
                exit=true;
                break;
            }
        }
        catch (exception& e) 
        {
            std::cout << "Error: " << e.what() << "\n"; 
        }

        sleep(1);

    }while (exit==false);

    cout<<endl<<"----------------------------------"<<endl;
    cout<<      "Thank you for using the Best Bank!"<<endl;
    cout<<      "Have a great day!"<<endl<<endl;


    return 0;
}

int InputValidation (int min, int max)// input validation for menu selection
{
    bool good_data = false;
    int check;
   // cin.ignore();
        
    do
    {
        cin >> check;
        good_data = cin.good();
        good_data = good_data && (check >= min) && (check <= max);

        if ( !cin.good() )
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
        }

        if ( !good_data)
        {
            cout<< "Invalid Input: Enter an integer between ";
            cout <<min <<"-"<< max<<". Please try again: ";
        }

    } while ( !good_data );

    cin.ignore();
    
    return check; 
}

double InputValidation (int min)// overloaded function that provided input validation for integets that have a min value
{
    bool good_data = false;
    int  size;
    long long int check;
        
    do
    {
        cin >> check;
        good_data = cin.good();
        good_data = good_data;//&& (check >= min);

        if ( !cin.good() )
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
        }

        if ( !good_data)
        {
            cout<< "Invalid Input: Enter a number larger than "<<min<<". Please try agian:";
        }

    } while ( !good_data );

    
    return check; 
}

double InputValidation ()// overloaded function that provided input validation for integets that have a min value
{
    bool good_data = false;
    int  size;
    long long int check;
        
    do
    {
        cin >> check;
        good_data = cin.good();
        good_data = good_data && (check >= 0);

        if ( !cin.good() )
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
        }

        if ( !good_data)
        {
            cout<< "Invalid Input: Enter a number larger than 0. Please try agian:";
        }

    } while ( !good_data );

    
    return check; 
}

string AccountNumberInputValidation ()// handles input validation for ISBM making sure 13 numberic digit is enterd
        {
            bool good_data = false;
            int  size, max =6;
            long long int check;
                
            do
            {
                // prompt user for value.
                cin >> check;
                good_data = cin.good();

                size = to_string(check).size();

                good_data = good_data && (size == max);

                if ( !cin.good() )
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
                }

                if ( !good_data)
                {
                    cout<< "Invalid Input: Enter a "<<max<<" digit number. Please try again: ";
                }

            } while ( !good_data );

            cin.ignore();
            
            return to_string(check); 
        }


