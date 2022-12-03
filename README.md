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