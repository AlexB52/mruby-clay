module Clay
=begin
    This method takes n number of arguments but expects no more than 4. It
    follows CSS padding definitions.

    Usage:
      Clay::Borders[2, 3]
      => {top: 2, right: 3, bottom: 2, left: 3, between_children: 0}
=end
  module Borders
    def self.[](*args, between_children: 0)
      paddings = args.map { |i| i || 0 }

      top = right = bottom = left = paddings[0] || 0
      if paddings[1]
        right = left = paddings[1]
      end
      if paddings[2]
        bottom = paddings[2]
      end
      if paddings[3]
        left = paddings[3]
      end

      {top: top, right: right, bottom: bottom, left: left, between_children: between_children}
    end
  end
end