require 'set'

def print_map(map)
  map.each { |m| puts m.join('') }
end

# Read input ranges
input_ranges = []
min_x, min_y, max_x, max_y = [1000, 1000, 0, 0]
File.open(ARGV[0], 'r') do |f|
  f.readlines.each do |line|
    input_ranges << line.split(' -> ').map do |point|
      x, y = point.split(',').map(&:to_i)

      # Determine min/max x/y values
      min_x = x if x < min_x
      max_x = x if x > max_x
      min_y = y if y < min_y
      max_y = y if y > max_y
      [x,y]
    end
  end
end

input_ranges.each { |x| puts x.to_s }
puts min_x
puts max_x
puts min_y
puts max_y

offset_x = min_x - 1
offset_y = min_y - 1
range_x = max_x - min_x + 2
range_y = max_y - min_y + 2

EMPTY = '.'
WALL = '#'
SAND = 'o'

# Define 2d array and draw lines
scan = Array.new(range_y)
# (0..range_y).each do |y|
(0..max_y + 1).each do |y|
  scan[y] = Array.new(range_x)
  (0..range_x).each do |x|
    scan[y][x] = EMPTY
  end
end

input_ranges.each do |input_range|
  input_range.each_cons(2) do |a, b|
    puts "Drawing #{a} to #{b}"
    # Fill in walls from a to b
    if a[0] == b[0]
      # Vertical
      x = a[0] - offset_x
      range = Range.new(*[a[1],b[1]].sort)
      range.each { |y| scan[y][x] = WALL }
    else
      # Horizontal
      y = a[1]
      range = Range.new(*[a[0],b[0]].sort)
      range.each { |x| puts "Drawing at #{x - offset_x}, #{y}"; scan[y][x - offset_x] = WALL }
    end
  end
end

print_map(scan)

sand_count = 0
falling_forever = false
until falling_forever
  sand = [500 - offset_x, 0]
  sand_count += 1
  until scan[sand[1]][sand[0]] == SAND # At rest
    if sand[1] == max_y + 1
      falling_forever = true
      sand_count -= 1 # Sand falls off
      break
    end
    if scan[sand[1]+1][sand[0]] == EMPTY
      # Move down
      sand[1] += 1
    elsif scan[sand[1]+1][sand[0]-1] == EMPTY
      # Move down and left
      sand[0] -= 1
      sand[1] += 1
    elsif scan[sand[1]+1][sand[0]+1] == EMPTY
      # Move down and right
      sand[0] += 1
      sand[1] += 1
    else
      # At rest
      scan[sand[1]][sand[0]] = SAND
    end
  end
  print_map(scan)
end

print_map(scan)

puts "Sand count: #{sand_count}"