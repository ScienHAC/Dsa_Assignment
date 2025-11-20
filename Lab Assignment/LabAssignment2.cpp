#include <iostream>
#include <string>
using namespace std;

// ------------------------------------------------------------
// 1. Ticket Node (Singly Linked List)
// ------------------------------------------------------------
struct Ticket {
    int id;
    string name;
    string issue;
    int priority;
    Ticket* next;

    Ticket(int i, string n, string is, int p) {
        id = i;
        name = n;
        issue = is;
        priority = p;
        next = NULL;
    }
};

// Singly Linked List for Tickets
class TicketList {
public:
    Ticket* head;

    TicketList() { head = NULL; }

    void insertTicket(int id, string name, string issue, int priority) {
        Ticket* t = new Ticket(id, name, issue, priority);
        if (head == NULL) {
            head = t;
        } else {
            Ticket* temp = head;
            while (temp->next != NULL) temp = temp->next;
            temp->next = t;
        }
        cout << "Ticket Added.\n";
    }

    void deleteTicket(int id) {
        if (head == NULL) {
            cout << "List Empty.\n";
            return;
        }
        if (head->id == id) {
            Ticket* del = head;
            head = head->next;
            delete del;
            cout << "Ticket Deleted.\n";
            return;
        }
        Ticket* temp = head;
        while (temp->next != NULL && temp->next->id != id)
            temp = temp->next;

        if (temp->next == NULL) {
            cout << "Ticket not found.\n";
            return;
        }

        Ticket* del = temp->next;
        temp->next = del->next;
        delete del;
        cout << "Ticket Deleted.\n";
    }

    Ticket* search(int id) {
        Ticket* t = head;
        while (t != NULL) {
            if (t->id == id) return t;
            t = t->next;
        }
        return NULL;
    }

    void display() {
        Ticket* t = head;
        while (t != NULL) {
            cout << "ID: " << t->id << ", Name: " << t->name
                << ", Issue: " << t->issue << ", Priority: " << t->priority << endl;
            t = t->next;
        }
    }
};

// ------------------------------------------------------------
// 2. Stack for Undo Operations
// ------------------------------------------------------------
class UndoStack {
public:
    int top;
    int arr[100];

    UndoStack() { top = -1; }

    void push(int id) {
        arr[++top] = id;
    }

    int pop() {
        if (top == -1) return -1;
        return arr[top--];
    }
};

// ------------------------------------------------------------
// 3. Priority Queue (For urgent tickets)
// ------------------------------------------------------------
class PriorityQueue {
public:
    Ticket* arr[100];
    int size;

    PriorityQueue() { size = 0; }

    void enqueue(Ticket* t) {
        arr[size++] = t;
    }

    Ticket* dequeue() {
        if (size == 0) return NULL;

        int best = 0;
        for (int i = 1; i < size; i++) {
            if (arr[i]->priority < arr[best]->priority)
                best = i;
        }

        Ticket* temp = arr[best];
        arr[best] = arr[size-1];
        size--;
        return temp;
    }
};

// ------------------------------------------------------------
// 4. Circular Queue (Round-Robin Tickets)
// ------------------------------------------------------------
class CircularQueue {
public:
    int front, rear, count;
    Ticket* arr[20];

    CircularQueue() {
        front = rear = count = 0;
    }

    void enqueue(Ticket* t) {
        if (count == 20) {
            cout << "Circular Queue Full.\n";
            return;
        }
        arr[rear] = t;
        rear = (rear + 1) % 20;
        count++;
    }

    Ticket* dequeue() {
        if (count == 0) return NULL;
        Ticket* t = arr[front];
        front = (front + 1) % 20;
        count--;
        return t;
    }
};

// ------------------------------------------------------------
// 5. Polynomial Linked List for Billing History
// ------------------------------------------------------------
struct Poly {
    int coeff;
    int exp;
    Poly* next;

    Poly(int c, int e) {
        coeff = c;
        exp = e;
        next = NULL;
    }
};

class PolyList {
public:
    Poly* head;

    PolyList() { head = NULL; }

    void insertTerm(int c, int e) {
        Poly* p = new Poly(c, e);
        if (head == NULL) head = p;
        else {
            Poly* t = head;
            while (t->next != NULL) t = t->next;
            t->next = p;
        }
    }

    int evaluate(int x) {
        int sum = 0;
        Poly* t = head;
        while (t != NULL) {
            int value = 1;
            for (int i = 0; i < t->exp; i++)
                value *= x;
            sum += t->coeff * value;
            t = t->next;
        }
        return sum;
    }
};

// ------------------------------------------------------------
// MAIN Customer Support System
// ------------------------------------------------------------
int main() {
    TicketList tickets;
    UndoStack undo;
    PriorityQueue pq;
    CircularQueue cq;
    PolyList bill1, bill2;

    int choice;

    cout << "Customer Support Ticket System\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Ticket\n";
        cout << "2. Undo Last Ticket\n";
        cout << "3. Search Ticket\n";
        cout << "4. Process Priority Ticket\n";
        cout << "5. Round Robin Ticket\n";
        cout << "6. Enter Billing Records\n";
        cout << "7. Compare Billing\n";
        cout << "8. Display Ticket List\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            int id, p;
            string name, issue;

            cout << "ID: "; cin >> id;
            cout << "Name: "; cin >> name;
            cout << "Issue: "; cin >> issue;
            cout << "Priority (1=urgent): "; cin >> p;

            tickets.insertTicket(id, name, issue, p);

            undo.push(id);

            Ticket* t = tickets.search(id);
            pq.enqueue(t);
            cq.enqueue(t);
        }

        else if (choice == 2) {
            int last = undo.pop();
            if (last == -1)
                cout << "Nothing to undo.\n";
            else
                tickets.deleteTicket(last);
        }

        else if (choice == 3) {
            int id;
            cout << "Enter ID: ";
            cin >> id;
            Ticket* t = tickets.search(id);
            if (t == NULL) cout << "Not found.\n";
            else
                cout << "Found: " << t->name << " (" << t->issue << ")\n";
        }

        else if (choice == 4) {
            Ticket* t = pq.dequeue();
            if (t == NULL) cout << "No tickets.\n";
            else
                cout << "Processing urgent ticket: " << t->id << endl;
        }

        else if (choice == 5) {
            Ticket* t = cq.dequeue();
            if (t == NULL) cout << "No tickets.\n";
            else {
                cout << "Round Robin Processing Ticket: " << t->id << endl;
                cq.enqueue(t);
            }
        }

        else if (choice == 6) {
            int c, e;
            cout << "Enter 3 terms for Bill 1 (coeff exp):\n";
            for (int i = 0; i < 3; i++) {
                cin >> c >> e;
                bill1.insertTerm(c, e);
            }
            cout << "Enter 3 terms for Bill 2:\n";
            for (int i = 0; i < 3; i++) {
                cin >> c >> e;
                bill2.insertTerm(c, e);
            }
        }

        else if (choice == 7) {
            int x;
            cout << "Enter x: ";
            cin >> x;

            int v1 = bill1.evaluate(x);
            int v2 = bill2.evaluate(x);

            cout << "Bill1 = " << v1 << endl;
            cout << "Bill2 = " << v2 << endl;

            if (v1 == v2) cout << "Bills are equal.\n";
            else cout << "Bills differ.\n";
        }

        else if (choice == 8) {
            tickets.display();
        }
    }

    return 0;
}
