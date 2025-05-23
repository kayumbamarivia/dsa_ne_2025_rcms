#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <iomanip>
#include <climits>

using namespace std;

class CityRoadManager {
private:
    // Data structures to store cities and roads
    vector<string> cities;
    vector<vector<int>> roadMatrix;    // Adjacency matrix for roads (0 or 1)
    vector<vector<double>> budgetMatrix; // Adjacency matrix for road budgets
    map<string, int> cityIndexMap;     // Maps city names to their indices

    // File names
    const string CITIES_FILE = "cities.txt";
    const string ROADS_FILE = "roads.txt";

    // Helper function to clear input buffer
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Helper function to get valid double input
    double getValidDoubleInput(const string& prompt, double min = -numeric_limits<double>::max(), double max = numeric_limits<double>::max()) {
        double value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                if (value >= min && value <= max) {
                    clearInputBuffer();
                    return value;
                }
                cout << "Please enter a number between " << min << " and " << max << endl;
            } else {
                cout << "Invalid input. Please enter a valid number." << endl;
                clearInputBuffer();
            }
        }
    }

    // Helper function to initialize matrices with zeros
    void initializeMatrices(size_t size) {
        roadMatrix.resize(size, vector<int>(size, 0));
        budgetMatrix.resize(size, vector<double>(size, 0.0));
    }

    // Helper functions
    void saveToFile() {
        // Save cities with header
        ofstream cityFile(CITIES_FILE);
        if (cityFile.is_open()) {
            cityFile << "Index\tCity Name" << endl;
            cityFile << "----------------" << endl;
            for (size_t i = 0; i < cities.size(); i++) {
                cityFile << (i + 1) << "\t" << cities[i] << endl;
            }
            cityFile.close();
        }

        // Save roads and budgets with header
        ofstream roadFile(ROADS_FILE);
        if (roadFile.is_open()) {
            roadFile << "Nbr\tRoad\tBudget" << endl;
            roadFile << "----------------" << endl;
            int roadNumber = 1;
            for (size_t i = 0; i < cities.size(); i++) {
                for (size_t j = i + 1; j < cities.size(); j++) {
                    if (roadMatrix[i+1][j+1] == 1) {
                        roadFile << roadNumber++ << "\t" 
                                << cities[i] << "-" << cities[j] << "\t" 
                                << fixed << setprecision(2) << budgetMatrix[i+1][j+1] << endl;
                    }
                }
            }
            roadFile.close();
        }
    }

    void loadFromFile() {
        // Load cities
        ifstream cityFile(CITIES_FILE);
        if (cityFile.is_open()) {
            string header;
            getline(cityFile, header);  // Skip header
            getline(cityFile, header);  // Skip separator line
            
            int index;
            string cityName;
            while (cityFile >> index >> cityName) {
                if (index > cities.size()) {
                    cities.resize(index);
                }
                cities[index - 1] = cityName;
                cityIndexMap[cityName] = index;
            }
            cityFile.close();
        }

        // Initialize matrices with zeros
        initializeMatrices(cities.size() + 1);

        // Load roads and budgets
        ifstream roadFile(ROADS_FILE);
        if (roadFile.is_open()) {
            string header;
            getline(roadFile, header);  // Skip header
            getline(roadFile, header);  // Skip separator line
            
            int roadNumber;
            string road, budget;
            while (roadFile >> roadNumber >> road >> budget) {
                size_t pos = road.find('-');
                string city1 = road.substr(0, pos);
                string city2 = road.substr(pos + 1);
                
                if (cityIndexMap.count(city1) && cityIndexMap.count(city2)) {
                    int i = cityIndexMap[city1];
                    int j = cityIndexMap[city2];
                    roadMatrix[i][j] = 1;
                    roadMatrix[j][i] = 1;
                    budgetMatrix[i][j] = stod(budget);
                    budgetMatrix[j][i] = stod(budget);
                }
            }
            roadFile.close();
        }
    }

public:
    CityRoadManager() {
        loadFromFile();
    }

     // Helper function to get valid integer input
    int getValidIntInput(const string& prompt, int min = INT_MIN, int max = INT_MAX) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                if (value >= min && value <= max) {
                    clearInputBuffer();
                    return value;
                }
                cout << "Please enter a number between " << min << " and " << max << endl;
            } else {
                cout << "Invalid input. Please enter a valid number." << endl;
                clearInputBuffer();
            }
        }
    }

    void addCities() {
        int numCities = getValidIntInput("Enter number of cities to add: ", 1, 100);
        int addedCount = 0;
        
        for (int i = 0; i < numCities; i++) {
            string cityName;
            cout << "Enter city name " << (i + 1) << ": ";
            getline(cin, cityName);

            // Check if city already exists
            if (cityIndexMap.find(cityName) != cityIndexMap.end()) {
                cout << "Error: City '" << cityName << "' already exists! Skipping..." << endl;
                continue;
            }

            // Add city with index starting from 1
            cities.push_back(cityName);
            cityIndexMap[cityName] = cities.size();  // Index will be 1-based
            addedCount++;

            // Initialize new matrices with zeros
            initializeMatrices(cities.size() + 1);  // +1 because we need space for index 0
        }
        saveToFile();
        cout << "Success: Added " << addedCount << " new cities. Total cities: " << cities.size() << endl;
    }

    void addRoad() {
        if (cities.size() < 2) {
            cout << "Error: Need at least 2 cities to add roads!" << endl;
            return;
        }

        string city1, city2;
        cout << "Enter first city name: ";
        getline(cin, city1);
        cout << "Enter second city name: ";
        getline(cin, city2);

        // Check if trying to add road to same city
        if (city1 == city2) {
            cout << "Error: Cannot add road between the same city!" << endl;
            return;
        }

        if (cityIndexMap.find(city1) == cityIndexMap.end() || 
            cityIndexMap.find(city2) == cityIndexMap.end()) {
            cout << "Error: One or both cities not found!" << endl;
            return;
        }

        int i = cityIndexMap[city1];
        int j = cityIndexMap[city2];

        if (roadMatrix[i+1][j+1] == 1) {
            cout << "Error: Road already exists between these cities!" << endl;
            return;
        }

        roadMatrix[i+1][j+1] = 1;
        roadMatrix[j+1][i+1] = 1;  // Make it bidirectional
        // Initialize budget to 0 for new road
        budgetMatrix[i+1][j+1] = 0.0;
        budgetMatrix[j+1][i+1] = 0.0;

        saveToFile();
        cout << "Success: Road added between " << city1 << " and " << city2 << endl;
    }

    void addBudget() {
        if (cities.size() < 2) {
            cout << "Error: Need at least 2 cities to add budgets!" << endl;
            return;
        }

        string city1, city2;
        cout << "Enter first city name: ";
        getline(cin, city1);
        cout << "Enter second city name: ";
        getline(cin, city2);

        // Check if trying to add budget to same city
        if (city1 == city2) {
            cout << "Error: Cannot add budget between the same city!" << endl;
            return;
        }

        if (cityIndexMap.find(city1) == cityIndexMap.end() || 
            cityIndexMap.find(city2) == cityIndexMap.end()) {
            cout << "Error: One or both cities not found!" << endl;
            return;
        }

        int i = cityIndexMap[city1];
        int j = cityIndexMap[city2];

        if (roadMatrix[i+1][j+1] == 0) {
            cout << "Error: No road exists between these cities! Add a road first." << endl;
            return;
        }

        double budget = getValidDoubleInput("Enter road budget: ", 0.0);
        budgetMatrix[i+1][j+1] = budget;
        budgetMatrix[j+1][i+1] = budget;  // Make it bidirectional

        saveToFile();
        cout << "Success: Budget of " << fixed << setprecision(2) << budget 
             << " added to road between " << city1 << " and " << city2 << endl;
    }

    void editCity() {
        if (cities.empty()) {
            cout << "Error: No cities to edit!" << endl;
            return;
        }

        int index = getValidIntInput("Enter city index to edit: ", 1, cities.size());
        
        string newName;
        cout << "Enter new city name: ";
        getline(cin, newName);

        if (cityIndexMap.find(newName) != cityIndexMap.end()) {
            cout << "Error: City name '" << newName << "' already exists!" << endl;
            return;
        }

        string oldName = cities[index - 1];
        cityIndexMap.erase(oldName);
        cities[index - 1] = newName;
        cityIndexMap[newName] = index;

        saveToFile();
        cout << "Success: City '" << oldName << "' renamed to '" << newName << "'" << endl;
    }

    void searchCity() {
        if (cities.empty()) {
            cout << "Error: No cities to search!" << endl;
            return;
        }

        int index = getValidIntInput("Enter city index to search: ", 1, cities.size());
        cout << "Success: Found city '" << cities[index - 1] << "' at index " << index << endl;
    }

    void displayCities() {
        if (cities.empty()) {
            cout << "Error: No cities to display!" << endl;
            return;
        }

        cout << "\nCities List:" << endl;
        cout << "Index\tCity Name" << endl;
        cout << "----------------" << endl;
        for (size_t i = 0; i < cities.size(); i++) {
            cout << (i + 1) << "\t" << cities[i] << endl;
        }
        cout << "Success: Displayed " << cities.size() << " cities" << endl;
    }

    void displayRoads() {
        if (cities.empty()) {
            cout << "Error: No cities to display roads for!" << endl;
            return;
        }

        cout << "\nRoads Matrix:" << endl;
        cout << setw(10) << " ";
        for (const auto& city : cities) {
            cout << setw(10) << city;
        }
        cout << endl;

        int roadCount = 0;
        for (size_t i = 0; i < cities.size(); i++) {
            cout << setw(10) << cities[i];
            for (size_t j = 0; j < cities.size(); j++) {
                cout << setw(10) << (roadMatrix[i+1][j+1] == 1 ? "1" : "0");
                if (roadMatrix[i+1][j+1] == 1) roadCount++;
            }
            cout << endl;
        }
        cout << "Success: Displayed " << roadCount/2 << " roads" << endl;
    }

    void displayBudgets() {
        if (cities.empty()) {
            cout << "Error: No cities to display budgets for!" << endl;
            return;
        }

        cout << "\nBudget Matrix:" << endl;
        cout << setw(10) << " ";
        for (const auto& city : cities) {
            cout << setw(10) << city;
        }
        cout << endl;

        int budgetCount = 0;
        for (size_t i = 0; i < cities.size(); i++) {
            cout << setw(10) << cities[i];
            for (size_t j = 0; j < cities.size(); j++) {
                if (roadMatrix[i+1][j+1] == 1) {
                    cout << setw(10) << fixed << setprecision(2) << budgetMatrix[i+1][j+1];
                    if (budgetMatrix[i+1][j+1] > 0) budgetCount++;
                } else {
                    cout << setw(10) << "0.00";
                }
            }
            cout << endl;
        }
        cout << "Success: Displayed " << budgetCount/2 << " road budgets" << endl;
    }

    void displayAllData() {
        displayCities();
        displayRoads();
        displayBudgets();
        cout << "Success: All data displayed successfully" << endl;
    }
};

int main() {
    CityRoadManager manager;
    
    while (true) {
        cout << "\n=== City and Road Management System ===" << endl;
        cout << "1. Add new city(ies)" << endl;
        cout << "2. Add road between cities" << endl;
        cout << "3. Add budget to existing road" << endl;
        cout << "4. Edit city" << endl;
        cout << "5. Search for a city" << endl;
        cout << "6. Display cities" << endl;
        cout << "7. Display roads" << endl;
        cout << "8. Display all recorded data" << endl;
        cout << "9. Exit" << endl;
        
        int choice = manager.getValidIntInput("Enter your choice: ", 1, 9);

        if (choice == 9) {
            cout << "Thank you for using the system!" << endl;
            return 0;
        }

        switch (choice) {
            case 1:
                manager.addCities();
                break;
            case 2:
                manager.addRoad();
                break;
            case 3:
                manager.addBudget();
                break;
            case 4:
                manager.editCity();
                break;
            case 5:
                manager.searchCity();
                break;
            case 6:
                manager.displayCities();
                break;
            case 7:
                manager.displayRoads();
                break;
            case 8:
                manager.displayAllData();
                break;
        }
    }

    return 0;
}