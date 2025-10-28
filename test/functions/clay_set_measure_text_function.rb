class TestSetMeasureTextFunction < MTest::Unit::TestCase
  def draw_text(text, **text_config, &measure_text_block)
    Clay.init(60, 40) do |error|
      raise error[:message]
    end

    Clay.measure_text(&measure_text_block)

    Clay.set_layout_dimensions(60, 40)

    Clay.begin_layout

    Clay.ui(background_color: Clay::Colors.red.to_h) do
      Clay.text(text,
        text_alignment: :left,
        **text_config
      )
    end

    Clay.end_layout
  end

  def text_cmd(commands)
    commands.find { |command| command["type"] == :text }
  end

  def test_hardcoded_values_for_a_single_word
    commands = draw_text("Hello") do |text, config|
      [1, 1]
    end

    assert_equal({
      "text" => "Hello",
      "bounding_box" => { "x" => 0.0, "y" => 0.0, "width" => 1.0, "height" => 1.0 },
    }, text_cmd(commands).slice('text', 'bounding_box'))
  end

  def test_hardcoded_values_for_multiple_words
    # It looks like text is measured per word. Spaces are also counted
    texts = []
    commands = draw_text("one two") do |text, config|
      texts << text
      [1, 1]
    end

    assert_equal [" ", "one", "two"], texts

    assert_equal({
      "text" => "one two",
      "bounding_box" => { "x" => 0.0, "y" => 0.0, "width" => 3.0, "height" => 1.0 },
    }, text_cmd(commands).slice('text', 'bounding_box'))
  end

  def test_text_default_config_passed_in
    configs = []
    draw_text("one two") do |text, config|
      configs << config
      [1, 1]
    end

    assert_equal [{line_height: 0, font_size: 0, letter_spacing: 0}], configs.uniq
  end

  def test_text_custom_config_passed_in
    configs = []
    draw_text("one two", letter_spacing: 1, font_size: 2, line_height: 3) do |text, config|
      configs << config
      [1, 1]
    end

    assert_equal [{letter_spacing: 1, font_size: 2, line_height: 3}], configs.uniq
  end

  def test_text_calculations_with_line_height
    commands = draw_text("one two", line_height: 3) do |text, config|
      [text.length, 1]
    end

    assert_equal({
      "text" => "one two",
      "bounding_box" => { "x" => 0.0, "y" => 1.0, "width" => 7.0, "height" => 3.0 },
    }, text_cmd(commands).slice('text', 'bounding_box'))
  end

  def test_text_calculations_with_letter_spacing
    # Not sure I understand letter spacing here
    commands = draw_text("one two", letter_spacing: 3) do |text, config|
      [text.length, 1]
    end

    assert_equal({
      "text" => "one two",
      "bounding_box" => { "x" => 0.0, "y" => 0.0, "width" => 4.0, "height" => 1.0 },
    }, text_cmd(commands).slice('text', 'bounding_box'))
  end

  def test_text_calculations_with_font_size
    # Not sure I understand letter spacing here
    commands = draw_text("one two", font_size: 3) do |text, config|
      [text.length, 1]
    end

    assert_equal({
      "text" => "one two",
      "bounding_box" => { "x" => 0.0, "y" => 0.0, "width" => 7.0, "height" => 1.0 },
    }, text_cmd(commands).slice('text', 'bounding_box'))
  end
end

MTest::Unit.new.run
