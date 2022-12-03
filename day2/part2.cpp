#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <cassert>

using namespace std;


/**
 * Remapping to follow the new rules:
 * A = Rock (1), B = Paper (2), C = Scissors (3)
 * A > C, B > A, C > B
 * X = Lose (0), Y = Draw (3), Z = Win (6)
 * A X | 3
 * A Y | 4
 * A Z | 8
 * B X | 1
 * B Y | 5
 * B Z | 9
 * C X | 2
 * C Y | 6
 * C Z | 7
 *
 * Sorted by score:
 * B X | 1
 * C X | 2
 * A X | 3
 * A Y | 4
 * B Y | 5
 * C Y | 6
 * C Z | 7
 * A Z | 8
 * B Z | 9
 *
 * */

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  // Score of round is the index of element + 1
  string scores[] = {
    "B X",
    "C X",
    "A X",
    "A Y",
    "B Y",
    "C Y",
    "C Z",
    "A Z",
    "B Z"
  };

  int total_score = 0;
  string line;
  while (getline(MyFile, line)) {
    int score = find(scores, end(scores), line) - begin(scores) + 1;
    // cout << "Score for " << line << " = " << score << endl;
    total_score += score;
  }

  cout << "Total score: " << total_score;

  MyFile.close();
}
