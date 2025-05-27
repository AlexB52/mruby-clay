module Clay
  module LayoutDirection
    DIRECTION_LEFT_TO_RIGHT = 0
    DIRECTION_TOP_TO_BOTTOM = 1

    def self.[](direction)
      case direction
      when :left_to_right then DIRECTION_LEFT_TO_RIGHT
      when :top_to_bottom then DIRECTION_TOP_TO_BOTTOM
      else                     DIRECTION_LEFT_TO_RIGHT
      end
    end
  end
#
  module ChildAlignment
    ALIGNMENT_LEFT = 0
    ALIGNMENT_RIGHT = 1
    ALIGNMENT_TOP = 0
    ALIGNMENT_BOTTOM = 1
    ALIGNMENT_CENTER = 2

    X_MAPPING = {
      left: ALIGNMENT_LEFT,
      right: ALIGNMENT_RIGHT,
      center: ALIGNMENT_CENTER,
    }

    Y_MAPPING = {
      top: ALIGNMENT_TOP,
      bottom: ALIGNMENT_BOTTOM,
      center: ALIGNMENT_CENTER,
    }

    def self.[](x = nil, y = nil)
      {
        x: (X_MAPPING[x] || ALIGNMENT_LEFT),
        y: (Y_MAPPING[y] || ALIGNMENT_TOP)
      }
    end
  end
end