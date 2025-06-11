#ifndef SALESRECORD_H
#define SALESRECORD_H
#include "aystr.h"


class SalesRecord {
    AYstr itemName;
    AYstr customerName;
    int quantity;
    float unitPrice;
    int day, month, year; 

public:
    SalesRecord();
    SalesRecord(const AYstr& itemName, const AYstr& customerName, int quantity, float price, int day, int month, int year);

    void print() const;

    int getQuantity() const;
    float getUnitPrice() const;
    AYstr getItemName() const;
    AYstr getCustomerName() const;
    float getTotal() const;

    bool isSameDate(int d, int m, int y) const;
};


#endif 