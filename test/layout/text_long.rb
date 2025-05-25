class TestTextBasic < MTest::Unit::TestCase
  def test_commands
    Clay.init(60, 40) do |error|
      raise error[:message]
    end

    Clay.measure_text do |text, config|
      [text.length.to_f, 1.0]
    end

    Clay.set_layout_dimensions(60, 40)

    Clay.begin_layout

    Clay.ui(
      id: "root",
      background_color: Clay::Colors.red.to_h,
      layout: {
        padding: Clay::Padding[1],
        sizing: {
          width: { min: 20, max: 20, type: 0 },
          height: { min: 20, max: 20, type: 0 },
        }
      }
    ) do
      Clay.text(
        "Lorem ipsum dolor it amet, consectetur adipisicing elit, sed",
        color: Clay::Colors.yellow.to_h,
        background_color: Clay::Colors.yellow.to_h,
        text_alignment: 1,
      )
    end

    commands = Clay.end_layout
    
    yellow_config = Clay::Colors.yellow.to_h(:string_keys)

    assert_equal([
      {
        "type" => :rectangle,
        "bounding_box" => { "x" => 0.0, "y" => 0.0, "width" => 20.0, "height" => 20.0 },
        "background_color" => { "r" => 255.0, "g" => 0.0, "b" => 0.0, "a" => 255.0 },
        "corner_radius" => { "top_left" => 0.0, "top_right" => 0.0, "bottom_left" => 0.0, "bottom_right" => 0.0 }
      }, {
        "type" => :text,
        "bounding_box" => {"x" => 1.5, "y" => 1.0, "width" => 17.0, "height" => 1.0},
        "text" => "Lorem ipsum dolor",
        "color" => yellow_config,
        "background_color" => yellow_config
      }, {
        "type" => :text,
        "bounding_box" => {"x" => 6.0, "y" => 2.0, "width" => 8.0, "height" => 1.0},
        "text" => "it amet,",
        "color" => yellow_config,
        "background_color" => yellow_config
      }, {
        "type" => :text,
        "bounding_box" => {"x" => 4.5, "y" => 3.0, "width" => 11.0, "height" => 1.0},
        "text" => "consectetur",
        "color" => yellow_config,
        "background_color" => yellow_config
      }, {
        "type" => :text,
        "bounding_box" => {"x" => 1.5, "y" => 4.0, "width" => 17.0, "height" => 1.0},
        "text" => "adipisicing elit,",
        "color" => yellow_config,
        "background_color" => yellow_config
      }, {
        "type" => :text,
        "bounding_box" => {"x" => 8.5, "y" => 5.0, "width" => 3.0, "height" => 1.0},
        "text" => "sed",
        "color" => yellow_config,
        "background_color" => yellow_config
      }
    ], commands)

  end
end

MTest::Unit.new.run
