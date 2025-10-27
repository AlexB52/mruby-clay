# CLAY_WASM_EXPORT("Clay_PointerOver")
# bool Clay_PointerOver(Clay_ElementId elementId) { // TODO return priority for separating multiple results
#     Clay_Context* context = Clay_GetCurrentContext();
#     for (int32_t i = 0; i < context->pointerOverIds.length; ++i) {
#         if (Clay_ElementIdArray_Get(&context->pointerOverIds, i)->id == elementId.id) {
#             return true;
#         }
#     }
#     return false;
# }

class TestPointerOver < MTest::Unit::TestCase
  def draw_rectangle
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

      Clay.ui('root',
        background_color: Clay::Colors.red.to_h,
        corner_radius: { top_left: 10, top_right: 10, bottom_left: 10, bottom_right: 10 },
        layout: {
          sizing: {
            width: Clay::Sizing.fixed(20),
            height: Clay::Sizing.fixed(20),
          }
        }
      )

      Clay.end_layout
    end
  end

  def test_invalid_inputs
    draw_rectangle do
      Clay.set_pointer_state({x: 15, y: 15}, false)
    end

    assert_equal false, Clay.pointer_over({})
    assert_equal false, Clay.pointer_over(nil)
  end

  def test_when_pointer_is_in_bounding_box
    draw_rectangle do
      Clay.set_pointer_state({x: 15, y: 15}, true)
    end

    assert_equal true, Clay.pointer_over(:root)
    assert_equal true, Clay.pointer_over('root')
  end

  def test_when_pointer_is_out_of_bounding_box
    draw_rectangle do
      Clay.set_pointer_state({x: 21, y: 15}, false)
    end

    assert_equal false, Clay.pointer_over(:root)
  end
end

MTest::Unit.new.run
