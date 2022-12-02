#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  vector<int> calorieSums;
  int calorieCounter = 0;

  string inputString;
  while (getline(MyFile, inputString)) {
    if (inputString == "") {
      calorieSums.push_back(calorieCounter);
      calorieCounter = 0;
    }
    else
      calorieCounter += stoi(inputString);
  }

  sort(calorieSums.begin(), calorieSums.end(), greater<int>());

  for(int i = 0; i < 3; i++) {
    cout << calorieSums[i] << endl;
  }

  cout << calorieSums[0] + calorieSums[1] + calorieSums[2];

  MyFile.close();
}