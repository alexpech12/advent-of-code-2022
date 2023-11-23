require 'set'

class Valve
  attr_reader :label, :flow_rate, :connections, :minimum_paths

  def initialize(label, flow_rate, connections)
    @label = label
    @flow_rate = flow_rate
    @connections = connections
    @minimum_paths = {}
    @open = false
  end

  def open!
    @open = true
  end

  def open?
    @open
  end

  def closed?
    !open?
  end

  def to_s
    "Valve #{label}"
  end

  def details
    "Valve #{label}, #{flow_rate}, -> #{connections}"
  end

  # def calculate_minimum_paths(other_valves)
  #   # Add immediate connections first
  #   connections.each { |c| minimum_paths[c] = c }
  # end
end

valves = {}
File.open(ARGV[0], 'r') { |f|
  f.readlines.each { |line|
  puts line
    label, flow_rate, connections = line.match(/Valve (\w\w).*=(\d*);.*valves? (.*)/).captures
    valves[label] = Valve.new(label, flow_rate.to_i, connections.split(', '))
  }
}

valves.each { |k, v| puts v.details }

def shortest_path(valves, source, target)
  # https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

  dist = {}
  prev = {}
  q = Set.new

  #for each vertex v in Graph.Vertices:
  valves.each do |v|
    #dist[v] ← INFINITY
    dist[v] = 1_000_000
    #prev[v] ← UNDEFINED
    prev[v] = nil
    #add v to Q
    q << v
  end
  # puts "Initialized path"

  #dist[source] ← 0
  dist[source] = 0

  # while Q is not empty:
  until q.empty?
    #u ← vertex in Q with min dist[u]
    u = q.min { |a,b| dist[a] <=> dist[b] }
    # puts "Min valve = #{u}"
    break if u == target

    #remove u from Q
    q.delete(u)
          
    #for each neighbor v of u still in Q:
    neighbours_of_u = valves.select { |v| u.connections.include? v.label }.map(&:label)
    # puts " - Neighhours: #{neighbours_of_u}"
    q.select { |v| neighbours_of_u.include? v.label }.each do |v|
      # puts " - Checking distance to #{v}"
      #alt ← dist[u] + Graph.Edges(u, v)
      alt = dist[u] + 1
      # puts " - alt = #{alt}, dist[v] = #{dist[v]}"
      #if alt < dist[v]:
      if alt < dist[v]
        # puts " - Updating dist[v] and prev[v]..."
        #dist[v] ← alt
        dist[v] = alt
        #prev[v] ← u
        prev[v] = u
      end
    end
    # puts "- dist = #{dist.values}"
    # puts "- prev = #{prev.values.compact.map(&:label)}"
  end

  # Traverse back
  #S ← empty sequence
  s = Set.new
  #u ← target
  u = target
  #if prev[u] is defined or u = source:          // Do something only if the vertex is reachable
  # puts "Traversing back..."
  # puts "prev[u] = #{prev[u]}"
  if prev[u] || u == source
    #while u is defined:                       // Construct the shortest path with a stack S
    until u.nil?
      #insert u at the beginning of S        // Push the vertex onto the stack
      s << u
      #u ← prev[u]                           // Traverse from target to source
      u = prev[u]
      # puts "s = #{s.map(&:label)}"
    end
  end
  s
end

test = shortest_path(valves.values, valves['CC'], valves['JJ'])
puts "#{test.map(&:label)}"



valves_to_open = valves.values.select { |v| v.flow_rate > 0 }

# Store distances between each node combination in a map
path_map = {}
valves_to_open.combination(2).each { |a, b|
  key = [a.label, b.label].sort.join('-')
  next if path_map.key? key

  path_map[key] = shortest_path(valves.values, a, b).length - 1
}
puts "#{path_map}"

# Get all permutations of valves to open
minimum_path = nil
maximum_value = 0
valves_to_open.permutation.each do |path|
  # Calculate value of path
  minutes_remaining = 30
  source = 'AA'
  destination = path[0].label
  distance = [source, destination].sort.join('-')

  while minutes_remaining > 0

  end
end

# At a given location, we know the total value of going straight to a valve and opening it
# 1. We need to know how many tunnels to get to the valve
# 2. The value of the valve is (minutes_remaining - time_in_tunnels(1 per tunnel) - time_to_open(1)) * flow_rate
# 3. Pick the highest value


#minutes_remaining = 30

# while minutes_remaining > 0
#   # Choose the valve with the highest value as the next destination
#   destination = valves.values.select(&:closed?).sort_by { |valve|
#     path = shortest_path(valves.values, valve, destination)
#     value = valve.flow_rate * (minutes_remaining - (path.length - 1) - 1)
#     puts "Evaluating #{valve}, value is #{value}, shortest path = #{path}"
#     value
#   }.last

#   puts "Moving to open #{destination}"
#   break
# end