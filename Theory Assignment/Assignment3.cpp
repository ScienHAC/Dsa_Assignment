#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

class Student {
public:
    int StudentID;
    string StudentName;
    float Marks;
    string CourseDetails;

    // DEFAULT constructor (required by vector)
    Student() {
        StudentID = 0;
        StudentName = "";
        Marks = 0.0;
        CourseDetails = "";
    }

    // PARAMETERIZED constructor
    Student(int id, string name, float marks, string cd) {
        StudentID = id;
        StudentName = name;
        Marks = marks;
        CourseDetails = cd;
    }
};

class HashTable {
private:
    int size;
    vector<vector<Student>> table;

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTable(int s = 10) {
        size = s;
        table.resize(size);
    }

    void insertStudent(Student s) {
        int index = hashFunction(s.StudentID);
        table[index].push_back(s);
    }

    Student* searchStudent(int roll) {
        int index = hashFunction(roll);
        for (auto &st : table[index]) {
            if (st.StudentID == roll)
                return &st;
        }
        return nullptr;
    }

    vector<Student> getAllStudents() {
        vector<Student> list;
        for (auto &bucket : table)
            for (auto &x : bucket)
                list.push_back(x); 
        return list;
    }
};

Student* sequentialSearch(vector<Student>& list, int roll) {
    for (auto &s : list)
        if (s.StudentID == roll)
            return &s;
    return nullptr;
}

Student* binarySearch(vector<Student>& list, int roll) {
    int l = 0, r = list.size() - 1;

    while (l <= r) {
        int m = (l + r) / 2;

        if (list[m].StudentID == roll)
            return &list[m];
        else if (list[m].StudentID < roll)
            l = m + 1;
        else
            r = m - 1;
    }
    return nullptr;
}

int partitionMarks(vector<Student>& a, int low, int high) {
    float pivot = a[high].Marks;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (a[j].Marks < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSortMarks(vector<Student>& a, int low, int high) {
    if (low < high) {
        int pi = partitionMarks(a, low, high);
        quickSortMarks(a, low, pi - 1);
        quickSortMarks(a, pi + 1, high);
    }
}

void heapify(vector<Student>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l].Marks > arr[largest].Marks) largest = l;
    if (r < n && arr[r].Marks > arr[largest].Marks) largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSortMarks(vector<Student>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int getMaxRoll(vector<Student>& arr) {
    int mx = arr[0].StudentID;
    for (auto &s : arr)
        mx = max(mx, s.StudentID);
    return mx;
}

void countingSort(vector<Student>& arr, int exp) {
    int n = arr.size();
    vector<Student> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i].StudentID / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int idx = (arr[i].StudentID / exp) % 10;
        output[count[idx] - 1] = arr[i];
        count[idx]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSortRoll(vector<Student>& arr) {
    int m = getMaxRoll(arr);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

void compareSortingPerformance(vector<Student> arr) {
    auto arr1 = arr;
    auto arr2 = arr;

    auto s1 = chrono::high_resolution_clock::now();
    quickSortMarks(arr1, 0, arr1.size() - 1);
    auto e1 = chrono::high_resolution_clock::now();

    auto s2 = chrono::high_resolution_clock::now();
    heapSortMarks(arr2);
    auto e2 = chrono::high_resolution_clock::now();

    cout << "\nQuick Sort Time: " 
         << chrono::duration_cast<chrono::microseconds>(e1 - s1).count() 
         << " microseconds\n";

    cout << "Heap Sort Time: " 
         << chrono::duration_cast<chrono::microseconds>(e2 - s2).count() 
         << " microseconds\n";
}

int main() {
    HashTable ht(10);

    ht.insertStudent(Student(101, "Amit", 85, "CSE"));
    ht.insertStudent(Student(102, "Piyush", 92, "CSE"));
    ht.insertStudent(Student(103, "Riya", 76, "ECE"));
    ht.insertStudent(Student(104, "John", 89, "EEE"));

    cout << "Search by Roll Number (Hash Table):\n";
    Student* s = ht.searchStudent(102);
    if (s) cout << s->StudentName << " found with marks " << s->Marks << endl;

    vector<Student> list = ht.getAllStudents();

    cout << "\nSorting by Marks using Quick Sort:\n";
    quickSortMarks(list, 0, list.size() - 1);
    for (auto &x : list)
        cout << x.StudentID << " " << x.Marks << endl;

    list = ht.getAllStudents();
    cout << "\nSorting by Marks using Heap Sort:\n";
    heapSortMarks(list);
    for (auto &x : list)
        cout << x.StudentID << " " << x.Marks << endl;

    list = ht.getAllStudents();
    cout << "\nSorting by Roll Number using Radix Sort:\n";
    radixSortRoll(list);
    for (auto &x : list)
        cout << x.StudentID << endl;

    compareSortingPerformance(ht.getAllStudents());

    return 0;
}
