#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_CUSTOMERS = 100;

struct Customer {
   int accountNumber;
    string name;
    string cnic;
    string dateOfBirth; 
    string address;     
    string email;       
    string accountType;
    double balance;
    string transactionHistory;
};

Customer customers[MAX_CUSTOMERS];
int totalCustomers = 0;

void saveDataToFile() {
    ofstream outFile("bank_data.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < totalCustomers; ++i) {
            outFile << customers[i].accountNumber << " "
                    << customers[i].name << " "
                    << customers[i].cnic << " "           
                    << customers[i].dateOfBirth << " "    
                    << customers[i].address << " "        
                    << customers[i].email << " "          
                    << customers[i].accountType << " "
                    << customers[i].balance << " "
                    << customers[i].transactionHistory << "\n";
        }
        outFile.close();
        cout << "Data saved to file.\n";
    } else {
        cout << "Error: Unable to save data to file.\n";
    }
}

void loadDataFromFile() {
    ifstream inFile("bank_data.txt");
    if (inFile.is_open()) {
        while (totalCustomers < MAX_CUSTOMERS &&
               inFile >> customers[totalCustomers].accountNumber
               >> customers[totalCustomers].name
               >> customers[totalCustomers].accountType
               >> customers[totalCustomers].balance
               >> customers[totalCustomers].transactionHistory) {
            totalCustomers++;
        }
        inFile.close();
        cout << "Data loaded from file.\n";
    } else {
        cout << "No previous data found.\n";
    }
}

void addNewCustomer() {
    if (totalCustomers >= MAX_CUSTOMERS) {
        cout << "Error: Maximum number of customers reached.\n";
        return;
    }

    Customer newCustomer;
    cout << "Enter account number: ";
    cin >> newCustomer.accountNumber;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newCustomer.name);
    cout << "Enter CNIC: ";
    getline(cin, newCustomer.cnic);
    cout << "Enter date of birth: ";
    getline(cin, newCustomer.dateOfBirth);
    cout << "Enter address: ";       
    getline(cin, newCustomer.address);
    cout << "Enter email: ";         
    getline(cin, newCustomer.email);
    cout << "Enter account type (savings or checking): ";
    cin >> newCustomer.accountType;
    cout << "Enter initial balance: ";
    cin >> newCustomer.balance;
    newCustomer.transactionHistory = "Account created with an initial balance of " + to_string(newCustomer.balance) + "\n";

    customers[totalCustomers++] = newCustomer;
    cout << "New customer added successfully.\n";
}





int findCustomerByAccountNumber(int accountNumber) {
    for (int i = 0; i < totalCustomers; ++i) {
        if (customers[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}

void depositMoney() {
    int accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    int index = findCustomerByAccountNumber(accountNumber);
    if (index != -1) {
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;

        customers[index].balance += amount;
        customers[index].transactionHistory += "Deposited " + to_string(amount) + "\n";

        cout << "Amount deposited successfully.\n";
    } else {
        cout << "Error: Account not found.\n";
    }
}

void withdrawMoney() {
    int accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    int index = findCustomerByAccountNumber(accountNumber);
    if (index != -1) {
        double amount;
        cout << "Enter amount to withdraw: $";
        cin >> amount;

        if (customers[index].balance >= amount) {
            customers[index].balance -= amount;
            customers[index].transactionHistory += "Withdrawn " + to_string(amount) + "\n";

            cout << "Amount withdrawn successfully.\n";
        } else {
            cout << "Error: Insufficient balance.\n";
        }
    } else {
        cout << "Error: Account not found.\n";
    }
}

void displayCustomerDetails(int index) {
    cout << "Account Number: " << customers[index].accountNumber << "\n";
    cout << "Name: " << customers[index].name << "\n";
    cout << "CNIC: " << customers[index].cnic << "\n";
    cout << "Date of Birth: " << customers[index].dateOfBirth << "\n";
    cout << "Address: " << customers[index].address << "\n";
    cout << "Email: " << customers[index].email << "\n";
    cout << "Account Type: " << customers[index].accountType << "\n";
    cout << "Balance: " << customers[index].balance << "\n";
    cout << "Transaction History:\n" << customers[index].transactionHistory << "\n";
}

void searchCustomer() {
    int choice;
    cout << "Search by:\n";
    cout << "1. Account Number\n";
    cout << "2. Name\n";
    cout << "3. CNIC\n";
    cout << "Enter choice: ";
    cin >> choice;

    int accountNumber;
    string name, cnic; 
    int index;

    switch (choice) {
        case 1:
            cout << "Enter account number: ";
            cin >> accountNumber;
            index = findCustomerByAccountNumber(accountNumber);
            break;
        case 2:
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            for (int i = 0; i < totalCustomers; ++i) {
                if (customers[i].name == name) {
                    index = i;
                    break;
                }
            }
            break;
        case 3:
            cout << "Enter CNIC: ";
            cin.ignore();
            getline(cin, cnic);
            for (int i = 0; i < totalCustomers; ++i) {
                if (customers[i].cnic == cnic) {
                    index = i;
                    break;
                }
            }
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    if (index != -1) {
        displayCustomerDetails(index);
    } else {
        cout << "Customer not found.\n";
    }
}


void sortByBalance() {
    for (int i = 0; i < totalCustomers - 1; ++i) {
        for (int j = 0; j < totalCustomers - i - 1; ++j) {
            if (customers[j].balance > customers[j + 1].balance) {
                swap(customers[j], customers[j + 1]);
            }
        }
    }

    cout << "Data sorted by balance.\n";
}

int main() {
    loadDataFromFile();

    int choice;
    do {
        cout << "\nBank Management System\n";
        cout << "1. Add New Customer\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Search Customer\n";
        cout << "5. Display All Customers\n";
        cout << "6. Sort by Balance\n";
        cout << "7. Save Data to File\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewCustomer();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                searchCustomer();
                break;
            case 5:
                for (int i = 0; i < totalCustomers; ++i) {
                    displayCustomerDetails(i);
                }
                break;
            case 6:
                sortByBalance();
                break;
            case 7:
                saveDataToFile();
                break;
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}