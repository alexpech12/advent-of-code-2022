# Advent of Code Solutions 2022

https://adventofcode.com/2022

This year, I'm branching out from my usual Ruby-ing and dusting off my C++.

## Day 1 ⭐️⭐️

## Day 2 ⭐️⭐️

### Part 1
Thought I was being _so_ clever with a regex.
```
static std::regex const matcher( "([ABC]) ([XYZ])" );
```
This is not the way...

Pretty neat that the RPS combinations map to unique scores 1-9. Nifty.

### Part 2
Hardest part was the mental gymnastics required to map each scenario to a score (i.e. if they choose rock and I win then I choose paper (2 points) + 3 points for winning = 5 points)

## Day 3 ⭐️⭐️

### Part 1
Gross string comparisons with nested loops. Oh well, it works I guess...
```
matched = false;
for(auto c2 : l2) {
  for(auto c1 : l1) {
    if (c1 == c2) {
      matched = true;
      prioritySum += priority(c1);
      break;
    }
  }
  if (matched)
    break;
}
```

Would've been cool if the character priorities went in ASCII order. Alas, an upper/lower conditional was required.
```
int priority(char c) {
  return c >= 97 ? c - 96 : c - 38;
}
```

### Part 2
Gah! Algorithms are hard. Hacking together an inefficient 'intersection' of two sets.
```
string common_chars(string str1, string str2) {
  string common = "";
  for(char c : str2) {
    if(str1.find(c) != -1) {
      common.push_back(c);
    }
  }
  return common;
}
```

## Day 4 ⭐️⭐️

_Now_ is the time for regex!
```
/(\\d*)-(\\d*),(\\d*)-(\\d*)/
```

Reminder, this is how to get regex captures in C++.
```
#include <regex>

// Define regex
static regex const matcher( "(\\d*)-(\\d*),(\\d*)-(\\d*)" );
smatch result;

// Perform matching
regex_search("7-11,8-15", result, matcher);

// Extract captures
int c1 = stoi(result.str(1));
int c2 = stoi(result.str(2));
int c3 = stoi(result.str(3));
int c4 = stoi(result.str(4));
```

## Day 5 ⭐️⭐️

## Day 6 ⭐️⭐️

### Part 1
Brute-forcing a test for unique characters. So far so good...
```
line[i-3] != line[i-2] &&
line[i-3] != line[i-1] &&
line[i-3] != line[i] &&
line[i-2] != line[i-1] &&
line[i-2] != line[i] &&
line[i-1] != line[i]
```

### Part 2
Brute-forcing not really an option when we need to compare 14 characters, so it's time to use sets!

The function to count unique characters in a string:
```
int unique_chars(char *start, int len) {
  set<char> uniq;
  for(auto i = 0; i < len; i++) {
    uniq.insert(start[i]);
  }
  return uniq.size();
}
```

This is neat because we just pass in our `char*` pointer plus the number of characters to add to our set. The `set<char>` handles all the uniqueness checks for us!

Definitely not a *safe* function, but it's quick.

## Day 7 ⭐️

### Part 1

Lambdas and recursive functions!
```
class Node {
  ...
    template<typename Functor>
    void traverse(Functor yield) {
      if (children.size() == 0)
        return;

      for(auto pair : children) {
        auto child = &pair.second;
        yield(child);
        child->traverse(yield);
      }
    }
  ...
};

...

auto print_tree = [](Node *node) mutable {
  for(int i = 0; i < node->getDepth(); i++) {
    cout << "   ";
  }
  cout << node->getName() << " (" << (node->isDir() ? "dir" : "file") << ", size=" << node->getSize() << ")\n";
};

tree.traverse(print_tree);
```