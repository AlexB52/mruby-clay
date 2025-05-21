module Clay
  module Colors
    Color = ::Struct.new(:r, :g, :b, :a)

    RED = Color.new(255, 0, 0, 255)
    GREEN = Color.new(0, 255, 0, 255)
    BLUE = Color.new(0, 0, 255, 255)
    YELLOW = Color.new(255, 255, 0, 255)
    CYAN = Color.new(0, 255, 255, 255)
    BLACK = Color.new(255, 255, 255, 255)

    def self.build(r:, g:, b:, a: 255)
      Color.new(r,g,b,a)
    end

    def self.red
      RED
    end

    def self.green
      GREEN
    end

    def self.blue
      BLUE
    end

    def self.yellow
      YELLOW
    end

    def self.cyan
      CYAN
    end

    def self.black
      BLACK
    end
  end
end
