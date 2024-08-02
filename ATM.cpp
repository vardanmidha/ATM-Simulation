#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

// Define a structure to represent a user account
struct Node
{
    long long int card_no;
    int pin;
    string name;
    int cash;
    Node *next;
    Node *prev;
};

class ATM
{
    Node *head;                   // Pointer to the head of the linked list
    long long int loggedInCardNo; // Stores the card number of the logged-in user
    int loggedInPin;              // Stores the PIN of the logged-in user

public:
    ATM()
    {
        head = NULL;
        loggedInCardNo = 0;
        loggedInPin = 0;
    }

    // Function to create a new user account
    void CreateAccount()
    {
        Node *newNode = new Node;
        cout << "Enter Name: ";
        cin >> newNode->name;

        cout << "Enter Card No: ";
        cin >> newNode->card_no;

        cout << "Enter Pin: ";
        cin >> newNode->pin;

        newNode->cash = 0;
        newNode->next = NULL;

        if (head == NULL)
        {
            newNode->prev = NULL;
            head = newNode; // Set the head to the new node if it's the first account
        }
        else
        {
            Node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }

        cout << "Account Created" << endl;
    }

    // Function to log in to a user account
    int LoginToAccount()
    {
        cout << "Enter Card No: ";
        cin >> loggedInCardNo;

        cout << "Enter Your PIN: ";
        cin >> loggedInPin;

        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->card_no == loggedInCardNo && temp->pin == loggedInPin)
            {
                cout << "***********" << endl;
                cout << "Name: " << temp->name << endl;
                loggedInMenu(temp); // Proceed to the user menu upon successful login
                return 1;           // Successful login
            }
            temp = temp->next;
        }

        cout << "Wrong Card No or PIN" << endl;
        return 0; // Failed login
    }

    // Function to handle cash withdrawal
    void Withdraw()
    {
        Node *temp = findLoggedInUser();
        if (temp != NULL)
        {
            int amount;
            cout << "Enter the Amount to Withdraw: ";
            cin >> amount;

            if (temp->cash >= amount)
            {
                temp->cash -= amount;
                cout << "Amount Successfully Withdrawn" << endl;
            }
            else
            {
                cout << "Insufficient Balance" << endl;
            }
        }
    }

    // Function to handle cash deposit
    void Deposit()
    {
        Node *temp = findLoggedInUser();
        if (temp != NULL)
        {
            int amount;
            cout << "Enter the Amount to Deposit: ";
            cin >> amount;
            temp->cash += amount;
            cout << "Amount Successfully Deposited" << endl;
        }
    }

    // Function to check and display account balance
    void BalanceEnquiry()
    {
        Node *temp = findLoggedInUser();
        if (temp != NULL)
        {
            cout << "Your Balance is: " << temp->cash << endl;
        }
    }

    // Function to display the user menu and handle user actions
    void loggedInMenu(Node *user)
    {
        while (true)
        {
            cout << "USER MENU" << endl;
            cout << "1. Deposit Money" << endl;
            cout << "2. Withdraw Money" << endl;
            cout << "3. Check Balance" << endl;
            cout << "4. Logout" << endl;
            cout << "***********" << endl;
            int command;
            cout << "Enter the Command: ";
            cin >> command;

            switch (command)
            {
            case 1:
                Deposit();
                break;
            case 2:
                Withdraw();
                break;
            case 3:
                BalanceEnquiry();
                break;
            case 4:
                cout << "Logged out" << endl;
                return;
            default:
                cout << "Invalid Command" << endl;
                break;
            }
        }
    }

    // Function to find the logged-in user based on card number and PIN
    Node *findLoggedInUser()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->card_no == loggedInCardNo && temp->pin == loggedInPin)
            {
                return temp;
            }
            temp = temp->next;
        }
        cout << "User not found" << endl;
        return NULL;
    }
};

int main()
{
    system("color 07");
    ATM atm;

    cout << "***********" << endl;
    cout << "WELCOME TO THE ONLINE BANKING" << endl;
    cout << "***********" << endl;

    while (true)
    {
        cout << "MAIN MENU" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login to Account" << endl;
        cout << "3. Exit" << endl;
        cout << "***********" << endl;

        int command;
        cout << "Enter the Command: ";
        cin >> command;

        switch (command)
        {
        case 1:
            atm.CreateAccount();
            break;
        case 2:
            if (atm.LoginToAccount() == 1)
            {
                // Successful login, go to user menu
                atm.loggedInMenu(atm.findLoggedInUser());
            }
            break;
        case 3:
            cout << "Thank You for visiting :)" << endl;
            return 0;
        default:
            cout << "Invalid Command" << endl;
            break;
        }
    }

    return 0;
}
