Clay.init(100, 100) do |error|
  raise error[:message]
end

Clay.measure_text do |text, config|
  [text.length, 1.0]
end

Clay.set_layout_dimensions(60, 40)

Clay.begin_layout

Clay.ui("root",
  background_color: Clay::Colors.red.to_h,
  layout: {
    padding: {top: 1, right: 1, bottom: 1, left: 1},
    child_gap: 1,
    sizing: {
      width: { min: 60, max: 60, type: 3 },
      height: { min: 40, max: 40, type: 3 },
    }
  }
) do
  Clay.ui("first",
    background_color: Clay::Colors.green.to_h,
    border: {
      background_color: Clay::Colors.green.to_h,
      color: Clay::Colors.green.to_h,
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
  ) do
    Clay.text("Hello, World!", color: Clay::Colors.yellow.to_h)
    Clay.text("Hello, World22222!", color: Clay::Colors.yellow.to_h)
  end

  Clay.ui("second",
    background_color: Clay::Colors.blue.to_h,
    layout: {
      sizing: {
        width: { type: 1 },
        height: { type: 1 },
      }
    }
  ) { Clay.text("Hello!", color: Clay::Colors.black.to_h) }

end

commands = Clay.end_layout

puts commands
