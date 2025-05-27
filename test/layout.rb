class TestLayout < MTest::Unit::TestCase
  def test_directions
    assert_equal(0, Clay::LayoutDirection[:left_to_right])
    assert_equal(1, Clay::LayoutDirection[:top_to_bottom])
    assert_equal(0, Clay::LayoutDirection[:unknown])
  end

  def test_child_alignment
    assert_equal({ x: 0, y: 0 }, Clay::ChildAlignment[:left, :top])
    assert_equal({ x: 1, y: 0 }, Clay::ChildAlignment[:right, :top])
    assert_equal({ x: 2, y: 0 }, Clay::ChildAlignment[:center, :top])
    assert_equal({ x: 0, y: 1 }, Clay::ChildAlignment[:left, :bottom])
    assert_equal({ x: 1, y: 1 }, Clay::ChildAlignment[:right, :bottom])
    assert_equal({ x: 2, y: 1 }, Clay::ChildAlignment[:center, :bottom])
    assert_equal({ x: 0, y: 2 }, Clay::ChildAlignment[:left, :center])
    assert_equal({ x: 1, y: 2 }, Clay::ChildAlignment[:right, :center])
    assert_equal({ x: 2, y: 2 }, Clay::ChildAlignment[:center, :center])

    # Edge cases
    assert_equal({ x: 0, y: 0 }, Clay::ChildAlignment[])
    assert_equal({ x: 0, y: 0 }, Clay::ChildAlignment[:unknown])
    assert_equal({ x: 0, y: 0 }, Clay::ChildAlignment[:unknown, :unknown])
  end

end

MTest::Unit.new.run