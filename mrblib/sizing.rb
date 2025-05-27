# Contrary to CLAY we're not using the same structure
# {
#   sizing: { min_max: { :min, :max }, :percent, :type }
# }
# BUT
# {
#   :min, :max, :type, :percent
# }

module Clay
  module Sizing
    # Wraps tightly to the size of the element's contents.
    TYPE_FIT = 0
    # Expands along this axis to fill available space in the parent element,
    # sharing it with other GROW elements.
    TYPE_GROW = 1
    # Expects 0-1 range. Clamps the axis size to a percent of the parent
    # container's axis size minus padding and child gaps.
    TYPE_PERCENT = 2
    # Clamps the axis size to an exact size in pixels.
    TYPE_FIXED = 3

    def self.fit(min = 0, max = nil)
      result = { type: TYPE_FIT, min: min }
      if max
        result.merge!(max: max)
      end
      result
    end

    def self.grow(min = 0, max = nil)
      result = { type: TYPE_GROW, min: min }
      if max
        result.merge!(max: max)
      end
      result
    end

    def self.fixed(width)
      { type: TYPE_FIXED, min: width, max: width }
    end

    def self.percent(percentage)
      { type: TYPE_PERCENT, percent: percentage }
    end
  end
end
