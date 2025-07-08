class TestHovered < MTest::Unit::TestCase
  def draw_rectangle
    results = []

    Clay.init(30, 30) do |error|
      raise error[:message]
    end

    Clay.measure_text do |text, config|
      [text.length, 1]
    end

    # Important to note that pointer_over is on the last frame which means that we
    # need to draw the layout then check pointer over on a second pass. This is
    # why we have drawn the rectangle twice
    # See https://github.com/nicbarker/clay?tab=readme-ov-file#clay_pointerover
    2.times do
      Clay.set_layout_dimensions(30, 30)
      yield

      Clay.begin_layout

      Clay.ui(
        id: :root,
        background_color: Clay::Colors.red.to_h,
        layout: {
          sizing: {
            width: Clay::Sizing.fixed(20),
            height: Clay::Sizing.fixed(20),
          }
        }
      ) do
        text = Clay.hovered? ? "Root is hovered" : "Root is NOT hovered"
        Clay.text(text, text_color: Clay::Colors.green.to_h)
      end

      results = Clay.end_layout
    end
    results
  end

  def test_hovered_is_triggered_inside_block
    commands = draw_rectangle do
      Clay.set_pointer_state({x: 15, y: 15}, false) # mouse hovering
    end

    command = commands.find { |cmd| cmd["type"] == :text }

    assert_equal(command["text"], "Root is hovered")
  end

  def test_hovered_is_not_triggered_inside_block
    commands = draw_rectangle do
      Clay.set_pointer_state({x: 21, y: 15}, false) # mouse outside bounding box
    end

    command = commands.find { |cmd| cmd["type"] == :text }

    assert_equal(command["text"], "Root is NOT hovered")
  end
end

MTest::Unit.new.run
