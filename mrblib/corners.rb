module Clay
  module Corners
    def self.[](radius)
      {
        top_left: radius,
        top_right: radius,
        bottom_left: radius,
        bottom_right: radius
      }
    end
  end
end