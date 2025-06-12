#include "cafeteria.h"
#include <iostream>
#include <fstream>

Cafeteria::Cafeteria() : totalSales(0.0) {
    currentDate = Date::getCurrentDate();
    loadSalesRecords();
}
void Cafeteria::suggestMenuItems(const Customer& customer) {
    AYstr preference = customer.getPreference();
    MyVector<AYstr> history = customer.getOrderHistory();

    std::cout << "\n--- Personalized Suggestions ---\n";

    if (history.empty()) {
        std::cout << "Welcome new customer!\n";
        if (!preference.isequal("None")) {
            std::cout << "Based on your " << preference.c_str() << " preference:\n";
            bool found = false;
            for (int i = 0; i < menuManager.getMenu().size(); ++i) {
                if (menuManager.getMenu()[i]->getCategory().isequal(preference)) {
                    std::cout << "- ";
                    menuManager.getMenu()[i]->getName().print();
                    std::cout << "\n";
                    found = true;
                }
            }
            if (!found) {
                std::cout << "No items match your preference.\n";
            }
        }
        return;
    }

    if (!preference.isequal("None")) {
        std::cout << "Recommended based on your " << preference.c_str() << " preference:\n";
        for (int i = 0; i < menuManager.getMenu().size(); ++i) {
            if (menuManager.getMenu()[i]->getCategory().isequal(preference)) {
                std::cout << "- ";
                menuManager.getMenu()[i]->getName().print();
                std::cout << "\n";
            }
        }
    }
}

void Cafeteria::saveSalesRecord(const AYstr& itemName, int quantity, double price, const AYstr& customerName) {
    salesRecords.push_back(SalesRecord(itemName, customerName, quantity, price,
        currentDate.getDay(), currentDate.getMonth(), currentDate.getYear()));
}

void Cafeteria::loadSalesRecords() {
    std::ifstream file("sales_records.txt");
    if (!file.is_open()) return;

    char buffer[256];
    while (file.getline(buffer, 256)) {
        AYstr line(buffer);
        int commaPos[4];
        int pos = 0;

        for (int i = 0; i < 4; i++) {
            pos = line.find_first(',', pos);
            if (pos == -1) break;
            commaPos[i] = pos;
            pos++;
        }

        if (commaPos[0] == -1 || commaPos[1] == -1 || commaPos[2] == -1 || commaPos[3] == -1) continue;

        AYstr dateStr = line.substring(0, commaPos[0]);
        AYstr itemName = line.substring(commaPos[0] + 1, commaPos[1] - commaPos[0] - 1);
        AYstr quantityStr = line.substring(commaPos[1] + 1, commaPos[2] - commaPos[1] - 1);
        AYstr priceStr = line.substring(commaPos[2] + 1, commaPos[3] - commaPos[2] - 1);
        AYstr customerName = line.substring(commaPos[3] + 1, line.strlength(line.c_str()) - commaPos[3] - 1);

        int dashPos1 = dateStr.find_first('-');
        int dashPos2 = dateStr.find_first('-', dashPos1 + 1);
        if (dashPos1 == -1 || dashPos2 == -1) continue;

        AYstr dayStr = dateStr.substring(0, dashPos1);
        AYstr monthStr = dateStr.substring(dashPos1 + 1, dashPos2 - dashPos1 - 1);
        AYstr yearStr = dateStr.substring(dashPos2 + 1, dateStr.strlength(dateStr.c_str()) - dashPos2 - 1);

        int day = dayStr.strtoint(dayStr.c_str());
        int month = monthStr.strtoint(monthStr.c_str());
        int year = yearStr.strtoint(yearStr.c_str());
        int quantity = quantityStr.strtoint(quantityStr.c_str());
        double price = priceStr.strtodouble(priceStr.c_str());

        salesRecords.push_back(SalesRecord(itemName, customerName, quantity, price, day, month, year));
    }
    file.close();
}

void Cafeteria::saveSalesRecordsToFile() {
    std::ofstream file("sales_records.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < salesRecords.size(); ++i) {
        file << salesRecords[i].getDate().getFormattedDate().c_str() << ","
            << salesRecords[i].getItemName().c_str() << ","
            << salesRecords[i].getQuantity() << ","
            << salesRecords[i].getUnitPrice() << ","
            << salesRecords[i].getCustomerName().c_str() << "\n";
    }
    file.close();
}

void Cafeteria::displayMenu() {
    menuManager.displayCompleteMenu();
}

void Cafeteria::placeOrder() {
    char name[100];
    std::cout << "Enter customer name: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    Customer* customer = customerManager.findCustomerByName(AYstr(name));
    if (!customer) {
        std::cout << "Customer not found! Please register first.\n";
        return;
    }

    suggestMenuItems(*customer);
    menuManager.displayCompleteMenu();

    MyVector<AYstr> orderItems;
    double orderTotal = 0.0;

    while (true) {
        int choice;
        std::cout << "Select menu item by number (-1 to finish): ";
        std::cin >> choice;

        if (choice == -1) break;
        if (choice < 1 || choice > menuManager.getMenu().size()) {
            std::cout << "Invalid choice!\n";
            continue;
        }

        int quantity;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;

        MenuItem* item = menuManager.getMenu()[choice - 1];
        if (!item->isAvailable(quantity)) {
            std::cout << "Not enough stock available!\n";
            continue;
        }

        item->updateStock(quantity);
        orderItems.push_back(item->getName());
        orderTotal += item->getPrice() * quantity;
    }

    if (orderItems.empty()) {
        std::cout << "No items selected. Order cancelled.\n";
        return;
    }

    std::cout << "\nOrder Summary:\n";
    for (int i = 0; i < orderItems.size(); ++i) {
        std::cout << "- ";
        orderItems[i].print();
        std::cout << "\n";
    }
    std::cout << "Total: $" << orderTotal << "\n";

    char confirm;
    std::cout << "Confirm order? (y/n): ";
    std::cin >> confirm;

    if (tolower(confirm) != 'y') {
        std::cout << "Order cancelled.\n";
        return;
    }

    for (int i = 0; i < orderItems.size(); ++i) {
        saveSalesRecord(orderItems[i], 1, menuManager.getItemPrice(orderItems[i]), AYstr(name));
        customer->addOrderToHistory(orderItems[i]);
    }

    customer->addLoyaltyPoints(3.0);
    totalSales += orderTotal;

    std::cout << "Order placed successfully!\n";
}

void Cafeteria::generateDailySalesReport() {
    double dailyTotal = 0.0;
    std::cout << "\nDaily Sales Report for ";
    currentDate.getFormattedDate().print();
    std::cout << "\n";

    for (int i = 0; i < salesRecords.size(); ++i) {
        if (salesRecords[i].isSameDate(currentDate.getDay(), currentDate.getMonth(), currentDate.getYear())) {
            salesRecords[i].print();
            dailyTotal += salesRecords[i].getTotal();
        }
    }

    std::cout << "Total Daily Sales: $" << dailyTotal << "\n";
}

void Cafeteria::generateMonthlySalesReport() {
    double monthlyTotal = 0.0;
    std::cout << "\nMonthly Sales Report for ";
    currentDate.getMonthName().print();
    std::cout << "\n";

    for (int i = 0; i < salesRecords.size(); ++i) {
        if (salesRecords[i].isSameDate(0, currentDate.getMonth(), currentDate.getYear())) {
            salesRecords[i].print();
            monthlyTotal += salesRecords[i].getTotal();
        }
    }

    std::cout << "Total Monthly Sales: $" << monthlyTotal << "\n";
}

void Cafeteria::generatePopularItemsReport() {
    MyVector<AYstr> itemNames;
    MyVector<int> itemCounts;

    for (int i = 0; i < salesRecords.size(); ++i) {
        bool found = false;
        for (int j = 0; j < itemNames.size(); ++j) {
            if (itemNames[j].isequal(salesRecords[i].getItemName())) {
                itemCounts[j] += salesRecords[i].getQuantity();
                found = true;
                break;
            }
        }
        if (!found) {
            itemNames.push_back(salesRecords[i].getItemName());
            itemCounts.push_back(salesRecords[i].getQuantity());
        }
    }
    for (int i = 0; i < itemNames.size() - 1; ++i) {
        for (int j = 0; j < itemNames.size() - i - 1; ++j) {
            if (itemCounts[j] < itemCounts[j + 1]) {
                int tempCount = itemCounts[j];
                itemCounts[j] = itemCounts[j + 1];
                itemCounts[j + 1] = tempCount;

                AYstr tempName = itemNames[j];
                itemNames[j] = itemNames[j + 1];
                itemNames[j + 1] = tempName;
            }
        }
    }

    std::cout << "\nMost Popular Items:\n";
    for (int i = 0; i < itemNames.size() && i < 5; ++i) {
        itemNames[i].print();
        std::cout << " - Sold " << itemCounts[i] << " times\n";
    }
}

void Cafeteria::displayReportingOptions() {
    int choice;
    do {
        std::cout << "\n--- Reporting Options ---\n";
        std::cout << "1. Daily Sales Report\n";
        std::cout << "2. Monthly Sales Report\n";
        std::cout << "3. Popular Items Report\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: generateDailySalesReport(); break;
        case 2: generateMonthlySalesReport(); break;
        case 3: generatePopularItemsReport(); break;
        case 4: break;
        default: std::cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

void Cafeteria::menuManagement() {
    menuManager.displayMenuOptions();
}

void Cafeteria::customerManagement() {
    int choice;
    do {
        std::cout << "\n--- Customer Management ---\n";
        std::cout << "1. Register Customer\n";
        std::cout << "2. Update Customer Info\n";
        std::cout << "3. View Order History\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: customerManager.registerCustomer(); break;
        case 2: customerManager.updateCustomerInfo(); break;
        case 3: customerManager.displayOrderHistory(); break;
        case 4: break;
        default: std::cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

void Cafeteria::saveData() {
    menuManager.saveMenuToFile();
    customerManager.saveAllCustomerData();
    saveSalesRecordsToFile();
}
void Cafeteria::displayOrderHistory() {
    customerManager.displayOrderHistory();
}