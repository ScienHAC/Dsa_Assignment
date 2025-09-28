#include <iostream>
#include <string>
using namespace std;

// ================= Weather Record ADT =================
class WeatherRecord {
public:
    string date;     // format: dd/mm/yyyy
    string city;
    double temperature;

    WeatherRecord() {
        date = "";
        city = "";
        temperature = -9999; // sentinel value for missing data
    }

    WeatherRecord(string d, string c, double t) {
        date = d;
        city = c;
        temperature = t;
    }
};

// ================= Data Storage Class =================
class WeatherStorage {
private:
    static const int MAX_YEARS = 5;   // for demo
    static const int MAX_CITIES = 5;  // for demo
    double data[MAX_YEARS][MAX_CITIES]; // 2D array

public:
    WeatherStorage() {
        // initialize with sentinel value for sparse data
        for (int i = 0; i < MAX_YEARS; i++) {
            for (int j = 0; j < MAX_CITIES; j++) {
                data[i][j] = -9999; // sentinel for "no data"
            }
        }
    }

    // Insert data (year index, city index, temperature)
    void insert(int yearIndex, int cityIndex, double temp) {
        if (yearIndex < MAX_YEARS && cityIndex < MAX_CITIES) {
            data[yearIndex][cityIndex] = temp;
        }
    }

    // Delete data
    void remove(int yearIndex, int cityIndex) {
        if (yearIndex < MAX_YEARS && cityIndex < MAX_CITIES) {
            data[yearIndex][cityIndex] = -9999; // reset to sentinel
        }
    }

    // Retrieve city’s data for a given year
    void retrieve(int yearIndex, int cityIndex) {
        if (data[yearIndex][cityIndex] == -9999) {
            cout << "No data available\n";
        } else {
            cout << "Temperature: " << data[yearIndex][cityIndex] << "°C\n";
        }
    }

    // Row-major access
    void rowMajorAccess() {
        cout << "\nRow-Major Access:\n";
        for (int i = 0; i < MAX_YEARS; i++) {
            for (int j = 0; j < MAX_CITIES; j++) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // Column-major access
    void columnMajorAccess() {
        cout << "\nColumn-Major Access:\n";
        for (int j = 0; j < MAX_CITIES; j++) {
            for (int i = 0; i < MAX_YEARS; i++) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // Handle sparse data (print only available records)
    void handleSparseData() {
        cout << "\nAvailable Data (ignoring sparse entries):\n";
        for (int i = 0; i < MAX_YEARS; i++) {
            for (int j = 0; j < MAX_CITIES; j++) {
                if (data[i][j] != -9999) {
                    cout << "Year " << i << ", City " << j
                         << " -> " << data[i][j] << "°C\n";
                }
            }
        }
    }

    // Simple complexity explanation
    void analyzeComplexity() {
        cout << "\nTime Complexity:\n";
        cout << "Insert/Delete/Retrieve: O(1)\n";
        cout << "Row/Column Traversal: O(n*m)\n";

        cout << "Space Complexity:\n";
        cout << "2D Array requires O(n*m)\n";
    }
};

// ================= Main Function =================
int main() {
    WeatherStorage ws;

    // Insert some sample data
    ws.insert(0, 0, 25.3); // Year 0, City 0
    ws.insert(0, 1, 28.7);
    ws.insert(1, 0, 22.5);

    // Retrieve a value
    cout << "Retrieve Year 0, City 1: ";
    ws.retrieve(0, 1);

    // Delete a record
    ws.remove(0, 1);
    cout << "After deletion: ";
    ws.retrieve(0, 1);

    // Row-major and Column-major
    ws.rowMajorAccess();
    ws.columnMajorAccess();

    // Sparse handling
    ws.handleSparseData();

    // Complexity Analysis
    ws.analyzeComplexity();

    return 0;
}
