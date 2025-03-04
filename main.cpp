using namespace std;
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>

class BankAccount{
    private: 
        string accountName;
        string accountNum;
        double balance;
    
    public:
        BankAccount(string name, double intialBalance){
            accountName = name;
            accountNum = "Acc" + to_string(static_cast<int>(rand() %10000)); //func for random acc number
            if(intialBalance < 0){ //check to see if initial deposit is greater than 0
                throw invalid_argument("Error. Initial Balance can't be negative.");
            }
            balance = intialBalance;
        }
        void deposit(double money){
            if (money <= 0){
                throw invalid_argument("Error. Deposit Amount needs to be greater than $0.00!");
            }
            balance += money;
        }
        void withdraw(double money){
            if (money<= 0){
                throw invalid_argument("Error. Withdrawl Amount needs to be greater than $0.00!");
            }
            if (money > balance){ //check balance to withdrawl ratio
                throw runtime_error("Insufficient funds!");
            }
            balance-= money;
        }
        double currentBalance()const{
            return balance;
        }
        string getAccountName()const{
            return accountName;
        }
        string getAccountNum()const{
            return accountNum;
        }

};

void clearDisplay() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

int mainMenu(){
    int choice;

    cout<<"Welcome to ERIC's Simple Bank System"<<endl;
    cout<< "\n Please make a selection.\n" <<endl;
    cout<<"1. Create an Account"<<endl;
    cout<<"2. Sign In"<<endl;
    cout<<"3. Exit"<<endl;
    cin>> choice;
    clearDisplay();
    return choice;
}

int signedInMenu(){
    int choice;
    cout<< "\n Please make a selection.\n" <<endl;
    cout<<"1. Deposit Money"<<endl;
    cout<<"2. Withdraw Money"<<endl;
    cout<<"3. Check Account Balance"<<endl;
    cout<<"4. Exit and Sign Out"<<endl;
    cin>> choice;
    clearDisplay();
    return choice;
}

//checks sign in acc key
string getStringVerif(const string& prompt){
    string value;
    while(true){
        cout<< prompt;
    
        getline(cin,value);
        if(!value.empty()){
            return value;
        }else{
            cout<<"No input detected.."<<endl;
        }

    }
}

//check to see if its valid num
double getNumVal(const string & prompt){
    double value;
    while (true){
        cout<<prompt;
        if(cin >>value){
            clearDisplay();
            return value;
        }
        else {
            cout<<"Invalid Input. Please Enter a NUMBER"<<endl;
            clearDisplay();
        }
    }
}



int main() {
    srand(time(0)); 
    vector<BankAccount*> accounts; 
    BankAccount* account = nullptr; // Current account
    bool running = true;

    while (running) {
        int startMenu = mainMenu();

        switch (startMenu) {
            case 1: { //check to see if its valid num
                string name;
                cout << "\nEnter the account Holder's name or create a username: ";
                getline(cin, name);


                double initialBalance = getNumVal("Enter initial deposit amount: ");
                account = new BankAccount(name, initialBalance);
                accounts.push_back(account); 
                cout << "Account Successfully created! Your account number is: " << account->getAccountNum() << "\n" << endl;
                break;
            }

            case 2: {
                if (accounts.empty()) { 
                    cout << "\n Login not found. Account for this device does not exist. Please create an account.\n" << endl;
                    break;
                }
                string inputACCnum = getStringVerif("\nPlease Enter the Account Number: ");
                bool accVerified = false;
                for (BankAccount* acc : accounts) {
                    if (acc->getAccountNum() == inputACCnum) {
                        account = acc; 
                        accVerified = true;
                        break;
                    }
                }
                if (accVerified) {
                    cout << "\n" << "Signed in as " << account->getAccountName() << "\n" << "Account Number: " << account->getAccountNum() << endl;
                    bool signedIn = true;
                    while (signedIn) {
                        int signedInChoice = signedInMenu();

                        switch (signedInChoice) {
                            case 1: { 
                                double depositMoney = getNumVal("Enter Deposit Amount: ");
                                try {
                                    account->deposit(depositMoney);
                                    cout << "Deposit Complete! New Balance: $" << account->currentBalance() << endl;
                                } catch (const invalid_argument& e) {
                                    cout << "Error, Invalid Amount, please enter a REAL number." << endl;
                                }catch (const runtime_error& e){
                                    cout<<"Error, Invalid Input. Please select a different amount."<<endl;
                                }
                                break;
                            }

                            case 2: { //check balance to withdrawl ratio
                                double withdrawalMoney = getNumVal("Enter Withdrawal amount: ");
                                try {
                                    account->withdraw(withdrawalMoney);
                                    cout << "Withdrawal Complete! Your Current Balance: $" << account->currentBalance() << endl;
                                } catch (const invalid_argument& e) {
                                    cout << "\n Error, Invalid Choice. Please Select a Number from the Menu" << endl;
                                } catch (const runtime_error& e) {
                                    cout << "Error, Insufficient Funds, please select a different amount." << endl;
                                }
                                break;
                            }

                            case 3: { 
                                cout << "Current Account Balance: $" << account->currentBalance() << endl;
                                break;
                            }

                            case 4: { 
                                signedIn = false;
                                cout << "You have Successfully signed out of ERIC'S SIMPLE BANKING!" << endl;
                                account = nullptr;
                                break;
                            }

                            default: { 
                                cout << "Error, Input does not match our database, please make another selection" << endl;
                                break;
                            }
                        }
                    }
                } else {
                    cout << "\n\nLogin not found." << endl;
                }
                break;
            }

            case 3: { //check to see if its valid num
                running = false;
                if (account != nullptr) {
                    delete account;
                    account = nullptr;
                }
                for (BankAccount* acc : accounts) {
                    delete acc; // Clean dynamic allocated memory
                }
                accounts.clear();
                cout << "Thank you for choosing ERIC'S SIMPLE BANKING SYSTEM" << endl;
                break;
            }

            default: { //check to see if its valid num
                cout << "Invalid input. Please make a numeric selection from the menu." << endl;
                break;
            }
        }
    }

    return 0;
}
