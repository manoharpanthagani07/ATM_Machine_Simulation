#include <bits/stdc++.h>
using namespace std;
class ATM {
private:
    int balance;
    int pin;
    int denominations[4] = {2000, 500, 200, 100};
    int counts[4] = {10, 10, 10, 10}; 
public:
    ATM(int bal, int p) {
        balance = bal;
        pin = p;
    }
    bool authenticate() {
        int userPin;
        cout << "Enter PIN: ";
        cin >> userPin;
        if (userPin == pin) {
            cout << "Login Successful!\n";
            return true;
        }
        cout << "Incorrect PIN! Access Denied.\n";
        return false;
    }
    void showBalance() {
        cout << "Your Balance: ₹" << balance << "\n";
    }
    void deposit() {
        int amount;
        cout << "Enter amount to deposit: ₹";
        cin >> amount;
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }
        balance += amount;
        cout << "Deposit Successful!\n";
        cout << "Updated Balance: ₹" << balance << "\n";
    }
    void showDenominations() {
        cout << "ATM Denomination Availability:\n";
        for (int i = 0; i < 4; i++) {
            cout << "₹" << denominations[i] << " → " << counts[i] << " notes\n";
        }
        cout << endl;
    }
    void withdraw() {
        int amount;
        cout << "Enter amount to withdraw: ₹";
        cin >> amount;
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
            return;
        }
        if (amount % 100 != 0) {
            cout << "Amount must be in multiples of 100.\n";
            return;
        }
        int tempCounts[4], usedNotes[4];
        for (int i = 0; i < 4; i++) {
            tempCounts[i] = counts[i];
            usedNotes[i] = 0;
        }
        int remaining = amount;
        for (int i = 0; i < 4; i++) {
            int note = denominations[i];
            int maxNotes = remaining / note;
            if (maxNotes > tempCounts[i])
                maxNotes = tempCounts[i]; 
            usedNotes[i] = maxNotes;
            remaining -= maxNotes * note;
        }
        if (remaining != 0) {
            cout << "ATM cannot dispense this amount with available denominations.\n";
            showDenominations();
            return;
        }
        for (int i = 0; i < 4; i++)
            counts[i] -= usedNotes[i];
        balance -= amount;
        cout << "Cash Withdrawal Successful!\n";
        cout << "Denomination Breakup:\n";
        for (int i = 0; i < 4; i++) {
            if (usedNotes[i] > 0)
                cout << "₹" << denominations[i] << " x " << usedNotes[i] << "\n";
        }
        cout << "Updated Balance: ₹" << balance << "\n";
    }
    void menu() {
        int choice;
        do {
            cout << "===== ATM MENU =====\n";
            cout << "1. Balance Inquiry\n";
            cout << "2. Cash Withdrawal\n";
            cout << "3. Deposit\n";
            cout << "4. Show Denominations\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: showBalance(); break;
                case 2: withdraw(); break;
                case 3: deposit(); break;
                case 4: showDenominations(); break;
                case 5: cout << "Thank you for using the ATM!\n"; break;
                default: cout << "Invalid Option! Try again.\n";
            }

        } while (choice != 5);
    }
};

int main() {
    ATM atm(15000, 1234);

    if (atm.authenticate()) {
        atm.menu();
    }

    return 0;
}