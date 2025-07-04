class TestRectangle < MTest::Unit::TestCase
  def test_commands
    Clay.init(60, 40) do |error|
      raise error[:message]
    end

    Clay.measure_text do |text, config|
      [text.length, 1]
    end

    Clay.set_layout_dimensions(60, 40)

    Clay.begin_layout

    Clay.ui(
      id: "root",
      background_color: Clay::Colors.red.to_h,
      border: {
        color: Clay::Colors.red.to_h,
        background_color: Clay::Colors.blue.to_h,
        width: { left: 1, right: 1, top: 1, bottom: 1, between_children: 1 }
      },
      corner_radius: { top_left: 10, top_right: 10, bottom_left: 10, bottom_right: 10 },
      layout: {
        sizing: {
          width: Clay::Sizing.fixed(20),
          height: Clay::Sizing.fixed(20),
        }
      }
    )

    commands = Clay.end_layout

    assert_equal([
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 0.0, "y" => 0.0, "width" => 20.0, "height" => 20.0},
        "background_color" => {"r" => 255.0, "g" => 0.0, "b" => 0.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 10.0, "top_right" => 10.0, "bottom_left" => 10.0, "bottom_right" => 10.0}
      },
      {
        "type" => :border,
        "bounding_box" => {"x" => 0.0, "y" => 0.0, "width" => 20.0, "height" => 20.0},
        "color" => {"r" => 255.0, "g" => 0.0, "b" => 0.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 255.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 10.0, "top_right" => 10.0, "bottom_left" => 10.0, "bottom_right" => 10.0},
        "width" => {"left" => 1, "right" => 1, "top" => 1, "bottom" => 1, "between_children" => 1}
      }
    ], commands)
  end
end

MTest::Unit.new.run
