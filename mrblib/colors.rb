module Clay
  module Colors
    Color = ::Struct.new(:r, :g, :b, :a) do
      alias _to_h to_h
      def to_h(keys = :sym_keys)
        case keys
        when :string_keys
          {"r" => r, "g" => g, "b" => b, "a" => a}
        else
          _to_h
        end
      end

      def ==(other)
        if other.is_a?(Hash)
          return other == to_h(:sym_keys) || other == to_h(:string_keys)
        end

        super
      end
    end

    DEFAULT_COLORS = {
      :black  => Color.new(0, 0, 0, 255),
      :red    => Color.new(255, 0, 0, 255),
      :green  => Color.new(0, 255, 0, 255),
      :blue   => Color.new(0, 0, 255, 255),
      :yellow => Color.new(255, 255, 0, 255),
      :cyan   => Color.new(0, 255, 255, 255),
      :white  => Color.new(255, 255, 255, 255),
    }

    # The syntax highlighting doesn't work but this is valid ruby in the latest versions.
    def self.white  = DEFAULT_COLORS[:white]
    def self.red    = DEFAULT_COLORS[:red]
    def self.green  = DEFAULT_COLORS[:green]
    def self.blue   = DEFAULT_COLORS[:blue]
    def self.yellow = DEFAULT_COLORS[:yellow]
    def self.cyan   = DEFAULT_COLORS[:cyan]
    def self.black  = DEFAULT_COLORS[:black]

    def self.build(*args, r: nil, g: nil, b: nil, a: 255)
      if args.empty?
        Color.new(r,g,b,a)
      else
        Color.new(*args)
      end
    end
  end
end
