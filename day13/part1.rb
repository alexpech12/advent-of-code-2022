def extract_value(str, from_index)
  # If first value is a [, take everything until that bracket is closed
  # Else, value is an integer
  if str[from_index] == '['
    to_index = from_index

    nesting = 0
    to_index = (from_index..(str.length-1)).find do |i|
      nesting += 1 if str[i] == '['
      nesting -= 1 if str[i] == ']'
      break if nesting == 0
    end
    str[(from_index..to_index)]
  else
    str[(from_index..)].to_i
  end
end

@nesting = 0

def tab
  @nesting += 1
end

def untab
  @nesting -= 1
  @nesting = 0 if @nesting < 0
end

def tab_puts(str)
  puts "#{'  ' * @nesting}- #{str}"
end

def compare(a, b)
  tab_puts "Compare #{a} vs #{b}"
  tab
  if a.is_a?(Integer) && b.is_a?(Integer)
    if a < b
      tab_puts 'Left side is smaller, so inputs are in the right order' 
      untab
      return true
    elsif a == b
      untab
      return nil
    else
      tab_puts 'Right side is smaller, so inputs are not in the right order'
      untab
      return false
    end
  elsif a.is_a? Integer
    tab_puts "Mixed types; convert left to [#{a}] and retry comparison"
    compare([a], b)
  elsif b.is_a? Integer
    tab_puts "Mixed types; convert right to [#{b}] and retry comparison"
    compare(a, [b])
  else
    if a.empty? && b.empty?
      untab
      return nil
    end
    if a.empty?
      tab_puts 'Left side ran out of items, so inputs are in the right order'
      untab
      return true
    elsif b.empty?
      tab_puts 'Right side ran out of items, so inputs are not in the right order'
      untab
      return false
    end
    (0..).each do |i|
      #tab_puts "Checking #{a[i]} vs #{b[i]}"
      if a[i].nil? && b[i].nil?
        untab
        return nil
      elsif a[i].nil?
        tab_puts 'Left side ran out of items, so inputs are in the right order'
        untab
        return true
      elsif b[i].nil?
        tab_puts 'Right side ran out of items, so inputs are not in the right order'
        untab
        return false
      end
      
      result = compare(a[i], b[i])
      #tab_puts "result = #{result}"
      unless result.nil?
        untab
        #tab_puts "Returning compare(#{a[i]}, #{b[i]}) = #{result}"
        return result
      end
    end
  end
end

File.open(ARGV[0], 'r') do |f|
  lines = f.readlines

  sum_indices = 0
  lines.each_slice(3).with_index do |(a, b, _newline), i|
    puts "== Pair #{i + 1} =="
    sum_indices += i+1 if compare(eval(a.rstrip), eval(b.rstrip))
    puts
    #break if i == 1
  end

  puts sum_indices
end