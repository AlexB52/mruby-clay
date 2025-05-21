class TestColors < MTest::Unit::TestCase
  def test_red
    subject = Clay::Colors.red

    assert_equal Clay::Colors.build(r: 255, g: 0, b: 0), subject
    assert_equal({ r: 255, g: 0, b: 0, a: 255 }, subject.to_h)
  end

  def test_blue
    subject = Clay::Colors.blue

    assert_equal Clay::Colors.build(r: 0, g: 0, b: 255), subject
    assert_equal({ r: 0, g: 0, b: 255, a: 255 }, subject.to_h)
  end
end

MTest::Unit.new.run