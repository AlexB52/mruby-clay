class TestSizing < MTest::Unit::TestCase
  def test_fit
    assert_equal({min: 20.5, max: 35.2, type: 0}, Clay::Sizing.fit(20.5, 35.2))
    assert_equal({min: 1, type: 0}, Clay::Sizing.fit(1))
    assert_equal({min: 0, type: 0}, Clay::Sizing.fit)
  end

  def test_grow
    assert_equal({min: 20.5, max: 35.2, type: 1}, Clay::Sizing.grow(20.5, 35.2))
    assert_equal({min: 0, type: 1}, Clay::Sizing.grow(0))
    assert_equal({min: 0, type: 1}, Clay::Sizing.grow)
  end

  def test_percent
    assert_equal({percent: 0.65, type: 2}, Clay::Sizing.percent(0.65))
  end

  def test_fixed
    assert_equal({min: 20, max: 20, type: 3}, Clay::Sizing.fixed(20))
  end
end

MTest::Unit.new.run