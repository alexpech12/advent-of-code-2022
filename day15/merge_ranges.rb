def merge_ranges ranges, debug: false
  ranges.sort_by(&:begin).each_with_object([]) { |range, merged|
    puts "Range: #{range}, Merged: #{merged}" if debug
    last_merge = merged[-1]
    if !last_merge.nil? && last_merge.end + 1 >= range.begin
      # Can merge
      merged[-1] = (last_merge.begin..[range.end, last_merge.end].max)
    else
      # New segment
      merged << range
    end
  }
end