class TestBorders < MTest::Unit::TestCase
  def test_borders
    assert_equal({top: 0, right: 0, bottom: 0, left: 0, between_children: 0}, Clay::Borders[])
    assert_equal({top: 1, right: 1, bottom: 1, left: 1, between_children: 0}, Clay::Borders[1])
    assert_equal({top: 2, right: 3, bottom: 2, left: 3, between_children: 0}, Clay::Borders[2, 3])
    assert_equal({top: 2, right: 3, bottom: 4, left: 3, between_children: 0}, Clay::Borders[2, 3, 4])
    assert_equal({top: 1, right: 2, bottom: 3, left: 4, between_children: 0}, Clay::Borders[1, 2, 3, 4])
    assert_equal({top: 1, right: 2, bottom: 0, left: 4, between_children: 0}, Clay::Borders[1, 2, nil, 4])

    assert_equal({top: 0, right: 0, bottom: 0, left: 0, between_children: 5}, Clay::Borders[between_children: 5])
    assert_equal({top: 1, right: 1, bottom: 1, left: 1, between_children: 5}, Clay::Borders[1, between_children: 5])
    assert_equal({top: 2, right: 3, bottom: 2, left: 3, between_children: 5}, Clay::Borders[2, 3, between_children: 5])
    assert_equal({top: 2, right: 3, bottom: 4, left: 3, between_children: 5}, Clay::Borders[2, 3, 4, between_children: 5])
    assert_equal({top: 1, right: 2, bottom: 3, left: 4, between_children: 5}, Clay::Borders[1, 2, 3, 4, between_children: 5])
    assert_equal({top: 1, right: 2, bottom: 0, left: 4, between_children: 5}, Clay::Borders[1, 2, nil, 4, between_children: 5])
  end
end

MTest::Unit.new.run
