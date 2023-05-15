#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#define FILE_NAME "shop.dat"

using namespace std;

class Item {
private:
    string itemCode, itemName;
    double itemPrice;
public:
    void readItem() {
        cout << endl << "INPUT ITEM DETAILS" << endl;
        cout << "ITEM CODE: ";
        cin >> itemCode;
        cin.ignore(); // ignore newline character left in input stream
        cout << "ITEM NAME: ";
        getline(cin, itemName);
        cout << "ITEM PRICE: ";
        cin >> itemPrice;
    }
    void displayItem() {
        cout << left << setw(15) << itemCode
             << left << setw(15) << itemName
             << left << setw(15) << setprecision(4) << itemPrice << endl;
    }
    string getItemCode() const { return itemCode; }
};

int writeToFile(Item item, string filename) {
    item.readItem();
    ofstream file;
    file.open(filename, ios::binary|ios::app);
    if (!file.is_open()){
        cout << "Error writing file" << endl;
        return -1;
    }
    file.write((char*)&item, sizeof(item));
    file.close();
    cout << "SAVED..." << endl;
    return 0;
}

int readFromFile(string filename) {
    Item item;
    ifstream file;
    file.open(filename, ios::binary);
    if (!file.is_open()){
        cout << "Error opening file" << endl;
        return -1;
    }
    cout << endl
         << left << setw(15) << "ITEM CODE"
         << left << setw(15) << "ITEM NAME"
         << left << setw(15) << "ITEM PRICE" << endl;
    while (file.read((char*)&item, sizeof(item))) {
        item.displayItem();
    }
    file.close();
    return 0;
}

int searchItemCode(string search, string filename) {
    Item item;
    ifstream file;
    file.open(filename, ios::binary);
    if (!file.is_open()){
        cout << "Error opening file" << endl;
        return -1;
    }
    bool found = false;
    while (file.read((char*)&item, sizeof(item))) {
        if (item.getItemCode() == search) {
            cout << endl
                 << left << setw(15) << "ITEM CODE"
                 << left << setw(15) << "ITEM NAME"
                 << left << setw(15) << "ITEM PRICE" << endl;
            item.displayItem();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Item not found." << endl;
    }
    file.close();
    cout << endl;
    return 0;
}

int main()
{
    int menuItem;
    string search;
    cout << "**********SHOP PROGRAM**********" << endl;
    cout << "0: EXIT" << endl;
    cout << "1: ADD ITEM" << endl;
    cout << "2: DISPLAY ALL ITEMS" << endl;
    cout << "3: SEARCH ITEM" << endl;
    while (true) {
        cout << endl << "PLEASE SELECT AN OPTION: ";
        cin >> menuItem;
        switch(menuItem) {
        case 0:
            return 0;
        case 1:
            {
                Item item;
                writeToFile(item, FILE_NAME);
                break;
            }
        case 2:
            readFromFile(FILE_NAME);
            break;
        case 3:
            cout << "\nSearch for item code: ";
            cin >> search

