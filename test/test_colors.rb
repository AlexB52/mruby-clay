class TestColors < MTest::Unit::TestCase
  def test_red
    assert_default_colors(Clay::Colors.red, { r: 255, g: 0, b: 0, a: 255 })
  end

  def test_blue
    assert_default_colors(Clay::Colors.blue, { r: 0, g: 0, b: 255, a: 255 })
  end

  def test_green
    assert_default_colors(Clay::Colors.green, { r: 0, g: 255, b: 0, a: 255 })
  end

  def test_yellow
    assert_default_colors(Clay::Colors.yellow, { r: 255, g: 255, b: 0, a: 255 })
  end

  def test_cyan
    assert_default_colors(Clay::Colors.cyan, { r: 0, g: 255, b: 255, a: 255 })
  end

  def test_black
    assert_default_colors(Clay::Colors.black, { r: 255, g: 255, b: 255, a: 255 })
  end

  def test_build
    subject = Clay::Colors.build(r: 20, g: 17, b: 89, a: 36)
    assert_equal({ r: 20, g: 17, b: 89, a: 36 }, subject.to_h)
  end

  private
  def assert_default_colors(subject, params)
    assert_equal Clay::Colors.build(**params), subject
    assert_equal(params, subject.to_h)
  end

end

MTest::Unit.new.run