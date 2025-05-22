module Clay
  module Padding

=begin
    This method takes n number of arguments but expects no more than 4.
    It follows CSS padding definitions
      * padding: 1;          <=> Clay::Padding[1]
      * padding: 1, 2;       <=> Clay::Padding[1, 2]
      * padding: 1, 2, 3;    <=> Clay::Padding[1, 2, 3]
      * padding: 1, 2, 3, 4; <=> Clay::Padding[1, 2, 3, 4]

    Usage:
      Clay::Padding[2, 3]
      => {top: 2, right: 3, bottom: 2, left: 3}
=end
    def self.[](*args)
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

      {top: top, right: right, bottom: bottom, left: left}
    end
  end
end