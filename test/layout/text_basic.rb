class TestTextBasic < MTest::Unit::TestCase
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
      layout: {
        padding: Clay::Padding[1],
        child_alignment: Clay::ChildAlignment[:center, :top],
        sizing: {
          width: Clay::Sizing.fixed(20),
          height: Clay::Sizing.fixed(20),
        }
      }
    ) do
      Clay.text(
        "Hello, world!",
        color: Clay::Colors.yellow.to_h,
        text_alignment: :center
      )
    end

    commands = Clay.end_layout

    assert_equal([
      {
        "type" => :rectangle,
        "bounding_box" => { "x" => 0.0, "y" => 0.0, "width" => 20.0, "height" => 20.0 },
        "background_color" => { "r" => 255.0, "g" => 0.0, "b" => 0.0, "a" => 255.0 },
        "corner_radius" => { "top_left" => 0.0, "top_right" => 0.0, "bottom_left" => 0.0, "bottom_right" => 0.0 }
      },
      {
        "type" => :text,
        "bounding_box" => { "x" => 3.5, "y" => 1.0, "width" => 13.0, "height" => 1.0 },
        "text" => "Hello, world!",
        "color" => { "r" => 255.0, "g" => 255.0, "b" => 0.0, "a" => 255.0 },
        "background_color" => { "r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0 }
      }
    ], commands)

  end
end

MTest::Unit.new.run
