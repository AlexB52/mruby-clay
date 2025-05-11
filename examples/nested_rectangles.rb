Clay.init(60, 40) do |error|
  raise error[:message]
end

Clay.measure_text do |text, config|
  [text.length, 1]
end

Clay.set_layout_dimensions(60, 40)

Clay.begin_layout

Clay.ui(
  id: "root",
  background_color: { r:255, g:0, b:0, a: 255 },
  layout: {
    padding: {top: 1, right: 1, bottom: 1, left: 1},
    child_gap: 1,
    sizing: {
      width: { min: 60, max: 60, type: 3 },
      height: { min: 40, max: 40, type: 3 },
    }
  }
) do
  Clay.ui(
    id: "first",
    background_color: { r:0, g: 255, b:0, a: 255 },
    border: {
      background_color: { r:0, g: 255, b:0, a: 255 },
      color: { r:0, g: 255, b:0, a: 255 },
      width: {
        left: 1, top: 1, right: 1, bottom: 1
      }
    },
    layout: {
      sizing: {
        width: { type: 1 },
        height: { type: 1 },
      }
    }
  )

  Clay.ui(
    id: "second",
    background_color: { r:0, g:0, b:255, a: 255 },
    layout: {
      sizing: {
        width: { type: 1 },
        height: { type: 1 },
      }
    }
  )

end

commands = Clay.end_layout

puts commands
