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

RIGHT_ORDER = -1
WRONG_ORDER = 1
def compare(a, b)
  tab_puts "Compare #{a} vs #{b}"
  tab
  if a.is_a?(Integer) && b.is_a?(Integer)
    if a < b
      tab_puts 'Left side is smaller, so inputs are in the right order' 
      untab
      return RIGHT_ORDER
    elsif a == b
      untab
      return nil
    else
      tab_puts 'Right side is smaller, so inputs are not in the right order'
      untab
      return WRONG_ORDER
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
      return RIGHT_ORDER
    elsif b.empty?
      tab_puts 'Right side ran out of items, so inputs are not in the right order'
      untab
      return WRONG_ORDER
    end
    (0..).each do |i|
      #tab_puts "Checking #{a[i]} vs #{b[i]}"
      if a[i].nil? && b[i].nil?
        untab
        return nil
      elsif a[i].nil?
        tab_puts 'Left side ran out of items, so inputs are in the right order'
        untab
        return RIGHT_ORDER
      elsif b[i].nil?
        tab_puts 'Right side ran out of items, so inputs are not in the right order'
        untab
        return WRONG_ORDER
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

  unsorted_list = lines.map do |line|
    eval(line.strip)
  end.compact

  decoder_keys = [
    [[2]],
    [[6]]
  ]
  unsorted_list += decoder_keys

  puts unsorted_list.to_s

  sorted_list = unsorted_list.sort { |a, b| compare(a, b) }
  
  sorted_list.each { |x| puts x.to_s }

  decoder_key = (sorted_list.index(decoder_keys[0]) + 1) * (sorted_list.index(decoder_keys[1]) + 1)
  puts decoder_key
end