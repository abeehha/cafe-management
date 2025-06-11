#include "salesrecord.h"
#include <iostream>

SalesRecord::SalesRecord() : quantity(0), unitPrice(0.0f), day(0), month(0), year(0) {}

SalesRecord::SalesRecord(const AYstr& item, const AYstr& customer, int qty, float price, int d, int m, int y)
    : itemName(item), customerName(customer), quantity(qty), unitPrice(price), day(d), month(m), year(y) {
}

void SalesRecord::print() const {
    std::cout << "Item: ";
    itemName.print();
    std::cout << "Customer: "; 
    customerName.print();
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Unit Price: " << unitPrice << "\n";
    std::cout << "Date: " << day << "/" << month << "/" << year << "\n";
    std::cout << "Total: " << getTotal() << "\n";
}

int SalesRecord::getQuantity() const { return quantity; }
float SalesRecord::getUnitPrice() const { return unitPrice; }
AYstr SalesRecord::getItemName() const { return itemName; }
AYstr SalesRecord::getCustomerName() const { return customerName; }
float SalesRecord::getTotal() const { return quantity * unitPrice; }

bool SalesRecord::isSameDate(int d, int m, int y) const {
    return day == d && month == m && year == y;
}
