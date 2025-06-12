#include "Cafeteria.h"
#include <iostream>

using namespace std;

void displayMainMenu() {
    cout << "\n--- Welcome to Bia's Cafe. Specify your role please---\n";
    cout << "1. Admin\n";
    cout << "2. Customer\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void displayAdminMenu() {
    cout << "\n--- Admin Menu ---\n";
    cout << "1. Menu Management\n";
    cout << "2. Customer Management\n";
    cout << "3. Generate Reports\n";
    cout << "4. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void displayCustomerMenu() {
    cout << "\n--- Customer Menu ---\n";
    cout << "1. Register\n";
    cout << "2. Place Order\n";
    cout << "3. View Order History\n";
    cout << "4. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

int main() {
    Cafeteria cafeteria;
    int mainChoice, subChoice;
    bool running = true;

    while (running) {
        displayMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            do {
                displayAdminMenu();
                cin >> subChoice;
                switch (subChoice) {
                case 1: cafeteria.menuManagement(); break;
                case 2: cafeteria.customerManagement(); break;
                case 3: cafeteria.displayReportingOptions(); break;
                case 4: break;
                default: cout << "Invalid choice.\n";
                }
            } while (subChoice != 4);
            break;

        case 2:
            do {
                displayCustomerMenu();
                cin >> subChoice;
                switch (subChoice) {
                case 1:
                    cafeteria.customerManagement();
                    break;
                case 2:
                    cafeteria.placeOrder();
                    break;
                case 3:
                    cafeteria.customerManagement();
                    break;
                case 4: break;
                default: cout << "Invalid choice.\n";
                }
            } while (subChoice != 4);
            break;

        case 3:
            running = false;
            cout << "Exiting the system. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    cafeteria.saveData();
    return 0;
}