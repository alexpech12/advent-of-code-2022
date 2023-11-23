require 'set'
require_relative 'merge_ranges.rb'

class Sensor
  attr_reader :x, :y, :bx, :by, :m_dist

  def initialize(x, y, bx, by)
    @x = x
    @y = y
    @bx = bx
    @by = by
    @m_dist = (x - bx).abs + (y - by).abs
  end

  def to_s
    "Sensor: #{x}, #{y}, Beacon: #{bx}, #{by}, Manhattan distance: #{m_dist}"
  end

  def beacon_point
    [bx, by]
  end

  def overlapping_range_y y_val
    y_dist_from_beacon = (y_val - y).abs
    return nil if y_dist_from_beacon >= m_dist

    number_of_points = (m_dist - y_dist_from_beacon) * 2 + 1
    min_x = x - (m_dist - y_dist_from_beacon)
    max_x = x + (m_dist - y_dist_from_beacon)
    (min_x..max_x)
  end
end

sensors = []
File.open(ARGV[0], 'r') do |f|
  f.readlines.each do |line|
    sensors << Sensor.new(*line.scan(/=(-?\d*)/).flatten.map(&:to_i))
  end
end

sensors.each { |s| puts s.to_s }

max_distance = ARGV[0] == 'test.txt' ? 20 : 4000000

signal_point = nil
(0..max_distance).each do |y|
  puts "Checking #{y} to #{y + 999}..." if y % 10000 == 0
  no_beacon_ranges = []

  # For each sensor, get all points with no beacon and add to set
  sensors.each { |sensor|
    #puts "Checking sensor - #{sensor}"
    #puts "Adding #{sensor.overlapping_range_y(y)} range..."
    range = sensor.overlapping_range_y(y)
    next if range.nil?
    next if (range.begin < 0 && range.end < 0)
    next if (range.begin > max_distance && range.end > max_distance)

    no_beacon_ranges << range
  }

  #puts "#{no_beacon_ranges.compact}"

  # Merge ranges
  no_beacon_ranges = merge_ranges(no_beacon_ranges.compact)
  #puts "Merged: #{no_beacon_ranges}"

  #puts "Beacons at #{beacon_points.uniq}"
  #puts " - Range: #{no_beacon_ranges}"
  if no_beacon_ranges.length > 1
    signal_point = [no_beacon_ranges.first.end + 1, y]
    break
  end
end

puts "Signal at #{signal_point} - freq = #{signal_point[0] * 4000000 + signal_point[1]}"