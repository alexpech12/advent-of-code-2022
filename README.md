# Advent of Code Solutions 2022

https://adventofcode.com/2022

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