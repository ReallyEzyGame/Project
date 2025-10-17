/*

Implement Client, Account, and SavingAccount classes
• Client
• Attribute: name, client ID
• Method: display (prints client info)
• Account
• Attribute: client, account number, balance
• Method: get balance, deposit (balance += amount), withdraw (balance -= amount),
display (prints account info)

• SavingAccount (inherits from Account)
• Attribute: interest rate
• Method: apply interest (balance += balance * interestRate), display (prints saving
account info)

*/
#include <string>

class Client;
class Account;
class SavingAccount;

class Client {
private:
    std::string name;
    std::string ID;          // Using HCMUS's ID rules
public:
    void display() {
        printf("\t+ ID: %s\n\t+ Name: %s\n", ID.c_str(), name.c_str());
    }
};


class Account {
private:
    Client client;
    std::string number;
protected:
    long long balance;
    long long overflow_unit;        // if the balance overflow the long long type then increase the unit by 1
public:
    Account() : client(Client()) {
        number =  "0000000000";
        balance = 0;
        overflow_unit = 0;
    }


    long long getBalance();
    void deposite(long long amount) {
        // handle it later on
        long long new_balance = ((balance % LONG_LONG_MAX) + (amount % LONG_LONG_MAX)) % LONG_LONG_MAX; 
        // if overflow occurs then icrease the overflow unit by 1
        if (new_balance < balance)
            overflow_unit++;

        balance = new_balance;
    }
    void withdraw(long long amount) {
        if (amount < 0) return;

        if (balance < amount)
        {
            printf("Error: the Withdraw amount is greater than the balance in the account\n");
            return;
        }
        balance -= amount;
    }
    void display() {
        client.display();
        printf("\t+ Balance Number: %s\n\t+ overflow time(s): %lld\n\t+ Balance: %lld\n", number.c_str(), overflow_unit, balance);
    }
};


class SavingAccount : public Account{
private:
    float interest_rate;
public:
    void applyInterest() {
        long long new_balance = (1.0f + interest_rate) * balance;
        if (new_balance < balance)
        {
            overflow_unit++;
            balance = new_balance % LONG_LONG_MAX;
        }
        balance = new_balance;
    }
    void display() {
        Account::display();
        printf("\tInterest  rate: %.3f\n", interest_rate);
    }
};