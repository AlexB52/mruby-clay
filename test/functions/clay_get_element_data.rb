# CLAY_WASM_EXPORT("Clay_GetElementData")
# Clay_ElementData Clay_GetElementData(Clay_ElementId id){
#     Clay_LayoutElementHashMapItem * item = Clay__GetHashMapItem(id.id);
#     if(item == &Clay_LayoutElementHashMapItem_DEFAULT) {
#         return CLAY__INIT(Clay_ElementData) CLAY__DEFAULT_STRUCT;
#     }

#     return CLAY__INIT(Clay_ElementData){
#         .boundingBox = item->boundingBox,
#         .found = true
#     };
# }

# typedef struct Clay_ElementData {
#     // The rectangle that encloses this UI element, with the position relative to the root of the layout.
#     Clay_BoundingBox boundingBox;
#     // Indicates whether an actual Element matched the provided ID or if the default struct was returned.
#     bool found;
# } Clay_ElementData;

class TestGetElementData < MTest::Unit::TestCase
  def test_retrieving_data_from_id
    Clay.init(60, 40) do |error|
      raise error[:message]
    end

    Clay.measure_text do |text, config|
      [text.length, 1]
    end

    Clay.set_layout_dimensions(60, 40)

    Clay.begin_layout

    Clay.ui(:root,
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

    expected_bounding_box = {"x" => 0.0, "y" => 0.0, "width" => 20.0, "height" => 20.0}

    assert_equal(expected_bounding_box, Clay.get_element_data(:root))
    assert_equal(expected_bounding_box, Clay.get_element_data("root"))
    assert_nil Clay.get_element_data("unknown_id")
    assert_nil Clay.get_element_data({})
    assert_nil Clay.get_element_data(nil)
  end
end

MTest::Unit.new.run
