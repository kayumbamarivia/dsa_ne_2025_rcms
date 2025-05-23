# City and Road Management System

A magical system that helps you manage cities and roads between them! Think of it like a digital map maker where you can:
- Add new cities (like adding houses to a neighborhood)
- Connect cities with roads (like building paths between houses)
- Give money to roads (like paying to fix and take care of paths)
- Change city names (like putting new name signs on houses)
- Look for cities (like finding a specific house)
- Show your map with all cities and roads

## Project Structure

The project is organized into three main files:
1. `CityRoadManager.h` - The blueprint for our magical map maker
2. `CityRoadManager.cpp` - The instructions that make our map maker work
3. `main.cpp` - The front door to our program

## How to Compile and Run

### Using g++ (Linux/Mac)
```bash
# Compile the program
g++ -o city_manager main.cpp CityRoadManager.cpp

# Run the program
./city_manager
```

### Using Visual Studio (Windows)
1. Create a new C++ Console Application
2. Add all three files to your project
3. Build and run the project

### Using MinGW (Windows)
```bash
# Compile the program
g++ -o city_manager.exe main.cpp CityRoadManager.cpp

# Run the program
city_manager.exe
```

## Features

1. **Add Cities**
   - Add one or more cities to your map
   - Each city gets a unique number
   - Cities can't have the same name

2. **Add Roads**
   - Connect two cities with a road
   - Can't add roads between the same city
   - Roads go both ways (like a two-way street)

3. **Add Budgets**
   - Give money to build and take care of roads
   - Can only add budgets to existing roads
   - Budgets are the same in both directions

4. **Edit Cities**
   - Change a city's name
   - Can't use a name that's already taken
   - Keeps all roads and budgets the same

5. **Search Cities**
   - Find a city by its number
   - Shows the city's name and number

6. **Display Information**
   - Show all cities in a list
   - Show all roads in a matrix
   - Show all budgets in a matrix
   - Show everything at once

## File Format

The program saves information in two files:

1. `cities.txt`
   ```
   Index   City Name
   ----------------
   1       City1
   2       City2
   ...
   ```

2. `roads.txt`
   ```
   Nbr     Road        Budget
   ----------------
   1       City1-City2 1000.00
   2       City1-City3 2000.00
   ...
   ```

## Error Handling

The program is very careful and will tell you if:
- You try to add a city that already exists
- You try to add a road between the same city
- You try to add a road between cities that don't exist
- You try to add a budget to a road that doesn't exist
- You try to use a city name that's already taken
- You enter invalid numbers or text

## Success Messages

The program will tell you when things work:
- How many cities were added
- Which cities were connected by roads
- How much money was given to roads
- When city names were changed
- When cities were found
- How many cities, roads, and budgets were shown 