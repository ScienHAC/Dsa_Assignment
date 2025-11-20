#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -------------------------------------------------------
// Student Record Structure
// -------------------------------------------------------
struct Student {
    int id;
    string name;
    float grade;
    string course;
};

// -------------------------------------------------------
// 1. Sequential Search
// -------------------------------------------------------
int sequentialSearch(vector<Student>& arr, int key) {
    for (int i = 0; i < arr.size(); i++)
        if (arr[i].id == key)
            return i;
    return -1;
}

// -------------------------------------------------------
// 2. Binary Search (array must be sorted by ID)
// -------------------------------------------------------
int binarySearch(vector<Student>& arr, int key) {
    int l = 0, r = arr.size() - 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid].id == key) return mid;
        if (arr[mid].id < key) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

// -------------------------------------------------------
// 3. Bubble Sort (sort by grade)
// -------------------------------------------------------
void bubbleSort(vector<Student>& arr) {
    for (int i = 0; i < arr.size() - 1; i++)
        for (int j = 0; j < arr.size() - i - 1; j++)
            if (arr[j].grade > arr[j + 1].grade)
                swap(arr[j], arr[j + 1]);
}

// -------------------------------------------------------
// 4. Insertion Sort (sort by grade)
// -------------------------------------------------------
void insertionSort(vector<Student>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].grade > key.grade) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// -------------------------------------------------------
// 5. Merge Sort (sort by grade)
// -------------------------------------------------------
void merge(vector<Student>& arr, int l, int m, int r) {
    vector<Student> L, R;
    for (int i = l; i <= m; i++) L.push_back(arr[i]);
    for (int i = m+1; i <= r; i++) R.push_back(arr[i]);

    int i = 0, j = 0, k = l;

    while (i < L.size() && j < R.size()) {
        if (L[i].grade <= R[j].grade)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<Student>& arr, int l, int r) {
    if (l < r) {
        int m = (l+r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// -------------------------------------------------------
// 6. Quick Sort (sort by grade)
// -------------------------------------------------------
int partition(vector<Student>& arr, int low, int high) {
    float pivot = arr[high].grade;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].grade < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i + 1;
}

void quickSort(vector<Student>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// -------------------------------------------------------
// 7. Heap Sort (rank by performance)
// -------------------------------------------------------
void heapify(vector<Student>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l].grade > arr[largest].grade)
        largest = l;
    if (r < n && arr[r].grade > arr[largest].grade)
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<Student>& arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// -------------------------------------------------------
// 8. Hash Table (Separate Chaining)
// -------------------------------------------------------
class HashTable {
public:
    vector<vector<Student>> table;
    int size = 10;

    HashTable() {
        table.resize(size);
    }

    int hashFunction(int id) {
        return id % size;
    }

    void insertStudent(Student s) {
        int index = hashFunction(s.id);
        table[index].push_back(s);
    }

    Student* search(int id) {
        int index = hashFunction(id);
        for (auto &s : table[index])
            if (s.id == id)
                return &s;
        return NULL;
    }

    vector<Student> getAll() {
        vector<Student> result;
        for (auto &bucket : table)
            for (auto &s : bucket)
                result.push_back(s);
        return result;
    }
};

// -------------------------------------------------------
// MENU + MAIN SYSTEM
// -------------------------------------------------------
int main() {
    HashTable ht;
    vector<Student> studentArray;

    while (true) {
        cout << "\n--- Student Performance Tracker ---\n";
        cout << "1. Add Student\n";
        cout << "2. Sequential Search\n";
        cout << "3. Binary Search\n";
        cout << "4. Bubble Sort\n";
        cout << "5. Insertion Sort\n";
        cout << "6. Merge Sort\n";
        cout << "7. Quick Sort\n";
        cout << "8. Heap Sort (Rank)\n";
        cout << "9. Display All Students\n";
        cout << "0. Exit\n";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            Student s;
            cout << "ID: "; cin >> s.id;
            cout << "Name: "; cin >> s.name;
            cout << "Grade: "; cin >> s.grade;
            cout << "Course: "; cin >> s.course;

            ht.insertStudent(s);
            studentArray.push_back(s);

            cout << "Student Added.\n";
        }

        else if (choice == 2) {
            int id; cout << "Enter ID: "; cin >> id;
            int pos = sequentialSearch(studentArray, id);

            if (pos == -1) cout << "Not Found.\n";
            else cout << "Found: " << studentArray[pos].name << endl;
        }

        else if (choice == 3) {
            bubbleSort(studentArray); // ensure sorted for binary search
            int id; cout << "Enter ID: "; cin >> id;

            int pos = binarySearch(studentArray, id);
            if (pos == -1) cout << "Not Found.\n";
            else cout << "Found: " << studentArray[pos].name << endl;
        }

        else if (choice == 4) {
            bubbleSort(studentArray);
            cout << "Bubble Sort Done.\n";
        }

        else if (choice == 5) {
            insertionSort(studentArray);
            cout << "Insertion Sort Done.\n";
        }

        else if (choice == 6) {
            mergeSort(studentArray, 0, studentArray.size()-1);
            cout << "Merge Sort Done.\n";
        }

        else if (choice == 7) {
            quickSort(studentArray, 0, studentArray.size()-1);
            cout << "Quick Sort Done.\n";
        }

        else if (choice == 8) {
            heapSort(studentArray);
            cout << "Heap Sort Ranking Done.\n";
        }

        else if (choice == 9) {
            for (auto &s : studentArray)
                cout << s.id << " " << s.name << " " << s.grade << endl;
        }
    }

    return 0;
}
