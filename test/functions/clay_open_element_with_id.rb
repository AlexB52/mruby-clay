class TestOpenElementWithId < MTest::Unit::TestCase
  def draw_element(id)
    Clay.init(60, 40) do |error|
      raise error[:message]
    end

    Clay.measure_text do |text, config|
      [text.length, 1]
    end

    Clay.set_layout_dimensions(60, 40)

    Clay.begin_layout

    Clay.ui(id, background_color: :red)

    Clay.end_layout
  end

  def test_invalid_id
    assert_raise(ArgumentError) do
      draw_element(1)
    end
  end

  def test_string_id
    draw_element('root')
  end

  def test_symbol_id
    draw_element(:root)
  end
end

MTest::Unit.new.run
