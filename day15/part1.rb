require 'set'

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

  def overlapping_points_y y_val
    y_dist_from_beacon = (y_val - y).abs
    return [] if y_dist_from_beacon >= m_dist

    number_of_points = (m_dist - y_dist_from_beacon) * 2 + 1
    min_x = x - (m_dist - y_dist_from_beacon)
    max_x = x + (m_dist - y_dist_from_beacon)
    (min_x..max_x).to_a.map { |x| [x, y_val] }
  end
end

sensors = []
File.open(ARGV[0], 'r') do |f|
  f.readlines.each do |line|
    sensors << Sensor.new(*line.scan(/=(-?\d*)/).flatten.map(&:to_i))
  end
end

sensors.each { |s| puts s.to_s }

line_to_scan = ARGV[0] == 'test.txt' ? 10 : 2000000

no_beacon_set = Set.new

# For each sensor, get all points with no beacon and add to set
sensors.each { |sensor|
  puts "Checking sensor - #{sensor}"
  puts "Adding #{sensor.overlapping_points_y(line_to_scan).count} points..."
  sensor.overlapping_points_y(line_to_scan).each { |point| 
    #puts " - Adding point #{point}"; 
    no_beacon_set << point 
  }
}

# Remove any points that actually contain a beacon
sensors.select { |sensor| sensor.by == line_to_scan }
       .each { |sensor| puts "Removing beacon point #{sensor.bx}, #{sensor.by}"; no_beacon_set.delete(sensor.beacon_point) }

puts "No beacon set size = #{no_beacon_set.size}" 