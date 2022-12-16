#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int unique_chars(char *start, int len) {
  set<char> uniq;
  for(auto i = 0; i < len; i++) {
    uniq.insert(start[i]);
  }
  return uniq.size();
}

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  static const int MESSAGE_LENGTH = 14;

  int result;
  string line;

  while (getline(MyFile, line)) {
    cout << line << endl;
    for(auto i = MESSAGE_LENGTH; i < line.length(); i++) {
      if (unique_chars(&line[i - MESSAGE_LENGTH], MESSAGE_LENGTH) == MESSAGE_LENGTH) {
        result = i;
        break;
      }
    }
  }

  cout << "Result = " << result << endl;

  MyFile.close();
}
