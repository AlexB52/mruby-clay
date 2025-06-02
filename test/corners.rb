class TestCorner < MTest::Unit::TestCase
  def test_query
    assert_equal({ top_left: 10, top_right: 10, bottom_left: 10, bottom_right: 10 }, Clay::Corners[10])
  end
end

MTest::Unit.new.run
