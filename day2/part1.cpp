#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <cassert>

using namespace std;


/**
 * R = 1, P = 2, S = 3
 * Lose = 0, Draw = 3, Win = 6
 * R R | 4
 * R P | 8
 * R S | 3
 * P R | 1
 * P P | 5
 * P S | 9
 * S R | 7
 * S P | 2
 * S S | 6
 *
 * Sorted by score:
 * P R | 1
 * S P | 2
 * R S | 3
 * R R | 4
 * P P | 5
 * S S | 6
 * S R | 7
 * R P | 8
 * P S | 9
 *
 * */

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  // Score of round is the index of element + 1
  string scores[] = {
    "B X",
    "C Y",
    "A Z",
    "A X",
    "B Y",
    "C Z",
    "C X",
    "A Y",
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
