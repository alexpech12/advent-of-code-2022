#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <regex>
#include <algorithm>

using namespace std;

class Monkey {
  public:
    enum Operation { add, multiply, square };

    int inspection_count = 0;
    deque<int> items;
    Operation operation;
    int operation_value;
    int divisible_test, true_monkey, false_monkey;

    Monkey(Operation operation, int operation_value, int divisible_test, int true_monkey, int false_monkey) {
      this->operation = operation;
      this->operation_value = operation_value;
      this->divisible_test = divisible_test;
      this->true_monkey = true_monkey;
      this->false_monkey = false_monkey;
    }

    void addItem(int item) {
      items.push_back(item);
    }

    int takeItem() {
      int item = items.front();
      items.pop_front();
      return item;
    }

    int nextMonkey(int &item) {
      inspection_count++;

      int worry_level = item;
      switch(operation) {
        case add:
          worry_level += operation_value;
          break;
        case multiply:
          worry_level *= operation_value;
          break;
        case square:
          worry_level *= worry_level;
          break;
      }

      worry_level /= 3;
      item = worry_level;
      if (worry_level % divisible_test == 0) {
        return true_monkey;
      }
      else {
        return false_monkey;
      }
    }
};

int extract_int(string str) {
  static regex const int_matcher( "\\d+" );
  smatch match;
  regex_search( str, match, int_matcher );
  return stoi(match[0]);
}

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  int result;
  string line;

  static regex const int_matcher( "\\d+" );
  static regex const operation_matcher( "  Operation: new = (.*)" );
  smatch match;

  vector<Monkey> monkeys;


  while (getline(MyFile, line)) {
    cout << line << endl;

    getline(MyFile, line);
    cout << line << endl;

    string::const_iterator search_start( line.cbegin() );

    vector<int> items;

    while ( regex_search( search_start, line.cend(), match, int_matcher ) )
    {
        items.push_back(stoi(match[0]));
        search_start = match.suffix().first;
    }

    getline(MyFile, line);
    cout << line << endl;
    regex_search( line, match, operation_matcher );
    cout << "Match: " << match.str(1) << endl;
    Monkey::Operation operation;
    int operation_value = 0;
    auto operation_cstr = match.str(1).c_str();
    if(strncmp(operation_cstr, "old +", 5) == 0) {
      operation = Monkey::Operation::add;
      operation_value = stoi(operation_cstr + 6);
    }
    else if (strncmp(operation_cstr, "old * old", 9) == 0) {
      operation = Monkey::Operation::square;
    }
    else {
      operation = Monkey::Operation::multiply;
      operation_value = stoi(operation_cstr + 6);
    }
    cout << "Operation = " << operation << ", Value = " << operation_value << endl;

    getline(MyFile, line);
    cout << line << endl;
    int divisible = extract_int(line);

    cout << "divisible = " << divisible << endl;

    getline(MyFile, line);
    cout << line << endl;
    int true_monkey = extract_int(line);

    cout << "true_monkey = " << true_monkey << endl;

    getline(MyFile, line);
    cout << line << endl;
    int false_monkey = extract_int(line);

    cout << "false_monkey = " << false_monkey << endl;

    // Get last empty line
    getline(MyFile, line);

    // Build monkey
    auto monkey = &monkeys.emplace_back(operation, operation_value, divisible, true_monkey, false_monkey);
    for (auto item : items) {
      monkey->addItem(item);
    }
  }

  int i = 0;
  for(auto monkey : monkeys) {
    cout << "Monkey " << i << endl;
    cout << "  Starting items: ";
    for(int i = 0; i < monkey.items.size(); ++i) {
      cout << monkey.items[i] << ",";
    }
    cout << endl;
    cout << "  Test: divisible by " << monkey.divisible_test << endl;
    cout << "    If true: throw to monkey " << monkey.true_monkey << endl;
    cout << "    If false: throw to monkey " << monkey.false_monkey << endl;
    cout <<endl;

    i++;
  }


  for(int round = 0; round < 20; round++) {

    int m = 0;
    for(auto &monkey : monkeys) {
      cout << "Monkey " << m << " has " << monkey.items.size() << " items to throw" << endl;

      while(monkey.items.size() > 0) {
        auto item = monkey.takeItem();
        cout << "Took item " << item << " from monkey " << m << endl;
        auto next_monkey = monkey.nextMonkey(item);
        cout << "Threw item " << item << " to monkey " << next_monkey << endl;
        monkeys[next_monkey].addItem(item);
        cout << "Monkey " << m << " now has items ";
        for(int i = 0; i < monkey.items.size(); ++i) { cout << monkey.items[i] << ","; }
        cout << endl;
        cout << "Monkey " << next_monkey << " now has items ";
        for(int i = 0; i < monkeys[next_monkey].items.size(); ++i) { cout << monkeys[next_monkey].items[i] << ","; }
        cout << endl;
      }
      cout << endl;
      m++;
    }
    m = 0;
    for(auto &monkey : monkeys) {
      cout << "Monkey " << m << " has items ";
      for(auto item : monkey.items) { cout << item << ","; }
      cout << endl;
      m++;
    }
  }
  cout << endl << "Inspection counts:" << endl;

  vector<int> inspection_counts;
  int m = 0;
  for(auto &monkey : monkeys) {
    cout << "Monkey " << m << " = " << monkey.inspection_count << endl;
    inspection_counts.push_back(monkey.inspection_count);
    m++;
  }

  sort(inspection_counts.begin(), inspection_counts.end());
  result = inspection_counts[inspection_counts.size()-1] * inspection_counts[inspection_counts.size()-2];
  cout << "result = " << result << endl;

  MyFile.close();
}
