class TestNestedLayout < MTest::Unit::TestCase
  def test_commands
    Clay.init(60, 40) do |error|
      raise error[:message]
    end

    Clay.measure_text do |text, config|
      [text.length, 1]
    end

    Clay.set_layout_dimensions(60, 40)

    Clay.begin_layout

    # The parent node is restricted to 20 x 20 in a 60 x 40 window
    Clay.ui("parent",
      background_color: Clay::Colors.green.to_h,
      layout: {
        padding: Clay::Padding[1],
        sizing: {
          width: Clay::Sizing.fixed(20),
          height: Clay::Sizing.fixed(20),
        }
      }
    ) do
      Clay.ui("child1",
        background_color: Clay::Colors.red.to_h,
        layout: {
          sizing: {
            width: Clay::Sizing.grow,
            height: Clay::Sizing.grow,
          }
        }
      )
      Clay.ui("child2",
        background_color: Clay::Colors.blue.to_h,
        layout: {
          sizing: {
            width: Clay::Sizing.grow,
            height: Clay::Sizing.grow,
          }
        }
      )
    end

    commands = Clay.end_layout

    assert_equal([
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 0.0, "y" => 0.0, "width" => 20.0, "height" => 20.0},
        "background_color" => {"r" => 0.0, "g" => 255.0, "b" => 0.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 0.0, "top_right" => 0.0, "bottom_left" => 0.0, "bottom_right" => 0.0}
      }, {
        "type" => :rectangle,
        "bounding_box" => {"x" => 1.0, "y" => 1.0, "width" => 9.0, "height" => 18.0},
        "background_color" => {"r" => 255.0, "g" => 0, "b" => 0.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 0.0, "top_right" => 0.0, "bottom_left" => 0.0, "bottom_right" => 0.0}
      }, {"type" => :rectangle,
        "bounding_box" => {"x" => 10.0, "y" => 1.0, "width" => 9.0, "height" => 18.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 255.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 0.0, "top_right" => 0.0, "bottom_left" => 0.0, "bottom_right" => 0.0}
      }
    ], commands)

  end
end

MTest::Unit.new.run
