```cpp
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;

// ----------------- Linked List for Patient Records -----------------
struct PatientNode {
    int pid;
    string name;
    string date;
    string details;
    PatientNode* next;
    PatientNode(int id, string n, string d, string det) {
        pid = id;
        name = n;
        date = d;
        details = det;
        next = NULL;
    }
};

class PatientLinkedList {
    PatientNode* head;
public:
    PatientLinkedList() { head = NULL; }

    void insertPatient(int id, string name, string date, string details) {
        PatientNode* newNode = new PatientNode(id, name, date, details);
        if (head == NULL) head = newNode;
        else {
            PatientNode* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    bool deletePatient(int id) {
        PatientNode* temp = head;
        PatientNode* prev = NULL;
        while (temp) {
            if (temp->pid == id) {
                if (prev) prev->next = temp->next;
                else head = temp->next;
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    void retrievePatient(int id) {
        PatientNode* temp = head;
        while (temp) {
            if (temp->pid == id) {
                cout << "ID: " << temp->pid 
                     << " Name: " << temp->name 
                     << " Date: " << temp->date 
                     << " Details: " << temp->details << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Patient not found!" << endl;
    }
};

// ----------------- Stack for Undo Admissions -----------------
class UndoStack {
    stack<int> st;
public:
    void push(int id) { st.push(id); }
    int pop() {
        if (st.empty()) return -1;
        int x = st.top(); st.pop(); return x;
    }
};

// ----------------- Circular Queue for Emergency Patients -----------------
class EmergencyQueue {
    int size, front, rear, count;
    vector<string> arr;
public:
    EmergencyQueue(int s) {
        size = s; front = 0; rear = -1; count = 0;
        arr.resize(size);
    }
    void enqueue(string name) {
        if (count == size) {
            cout << "Queue Full!" << endl;
            return;
        }
        rear = (rear + 1) % size;
        arr[rear] = name;
        count++;
    }
    string dequeue() {
        if (count == 0) {
            cout << "Queue Empty!" << endl;
            return "";
        }
        string data = arr[front];
        front = (front + 1) % size;
        count--;
        return data;
    }
};

// ----------------- Polynomial Billing -----------------
int evaluate_polynomial(vector<pair<int,int>> poly, int x) {
    int total = 0;
    for (auto term : poly) {
        total += term.first * pow(x, term.second);
    }
    return total;
}

// ----------------- Postfix Expression Evaluation (simple, no sstream) -----------------
int evaluate_postfix(string expr) {
    stack<int> st;
    for (int i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (c == ' ') continue; // skip spaces

        if (isdigit(c)) {
            st.push(c - '0'); // single-digit numbers
        } else {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            if (c == '+') st.push(a+b);
            else if (c == '-') st.push(a-b);
            else if (c == '*') st.push(a*b);
            else if (c == '/') st.push(a/b);
        }
    }
    return st.top();
}

// ----------------- Demo -----------------
int main() {
    PatientLinkedList patients;
    UndoStack undo;
    EmergencyQueue emergency(3);

    // Add patients
    patients.insertPatient(1, "Ram", "01/09/25", "Fever");
    patients.insertPatient(2, "Shyam", "02/09/25", "Injury");
    undo.push(2); // last admission saved for undo

    // Retrieve patient
    cout << "Patient 1 details:" << endl;
    patients.retrievePatient(1);

    // Undo admission
    int last = undo.pop();
    if (last != -1) {
        patients.deletePatient(last);
        cout << "Last admission undone (Patient ID " << last << ")" << endl;
    }

    // Emergency Queue
    emergency.enqueue("Critical A");
    emergency.enqueue("Critical B");
    cout << "Emergency Dequeued: " << emergency.dequeue() << endl;

    // Billing
    vector<pair<int,int>> bill = {{5,2}, {3,1}, {2,0}}; // 5x^2 + 3x + 2
    cout << "Billing Amount: " << evaluate_polynomial(bill, 2) << endl;

    // Inventory using postfix (example only works for single-digit numbers)
    cout << "Inventory Calculation: " << evaluate_postfix("1 2 + 3 *") << endl;

    return 0;
}
```
