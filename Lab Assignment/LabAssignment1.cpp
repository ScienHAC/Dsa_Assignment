#include <iostream>
#include <string>
using namespace std;

struct Item {
    int itemID;
    string itemName;
    int quantity;
    float price;
};

class Inventory {
    Item items[100];  // fixed-size array
    int count;

public:
    Inventory() { count = 0; }

    void insertItem(int id, string name, int qty, float price) {
        if (count < 100) {
            items[count++] = {id, name, qty, price};
            cout << "Item inserted successfully.\n";
        } else {
            cout << "Inventory full!\n";
        }
    }

    void deleteItem(int id) {
        for (int i = 0; i < count; i++) {
            if (items[i].itemID == id) {
                for (int j = i; j < count - 1; j++)
                    items[j] = items[j + 1];
                count--;
                cout << "Item deleted.\n";
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void searchItem(int id) {
        for (int i = 0; i < count; i++) {
            if (items[i].itemID == id) {
                cout << "Found: " << items[i].itemName 
                     << " | Qty: " << items[i].quantity 
                     << " | Price: " << items[i].price << endl;
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void displayAll() {
        cout << "\n--- Inventory List ---\n";
        for (int i = 0; i < count; i++) {
            cout << items[i].itemID << " | " << items[i].itemName 
                 << " | Qty: " << items[i].quantity 
                 << " | Price: " << items[i].price << endl;
        }
    }
};

int main() {
    Inventory inv;
    int choice, id, qty;
    string name;
    float price;

    do {
        cout << "\n1.Insert 2.Delete 3.Search 4.Display 5.Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter ID, Name, Qty, Price: ";
            cin >> id >> name >> qty >> price;
            inv.insertItem(id, name, qty, price);
            break;
        case 2:
            cout << "Enter ID to delete: ";
            cin >> id;
            inv.deleteItem(id);
            break;
        case 3:
            cout << "Enter ID to search: ";
            cin >> id;
            inv.searchItem(id);
            break;
        case 4:
            inv.displayAll();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
