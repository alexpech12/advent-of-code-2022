#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  int maxCalories = 0;
  int calorieCounter = 0;

  string inputString;
  while (getline(MyFile, inputString)) {
    if (inputString == "") {
      if (calorieCounter > maxCalories) { maxCalories = calorieCounter; }
      calorieCounter = 0;
    }
    else
      calorieCounter += stoi(inputString);
  }
  cout << "Max calories: " << maxCalories;

  MyFile.close();
}