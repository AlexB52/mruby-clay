Clay.init(60, 40) do |error|
  raise error[:message]
end

Clay.measure_text do |text, config|
  [text.length, 1]
end

Clay.set_layout_dimensions(60, 40)

Clay.begin_layout

Clay.ui(:root,
  background_color: { r:255, g:0, b:0, a: 255},
  layout: {
    padding: {
      top:1, left:1, right: 1, bottom: 1
    },
    sizing: {
      width: { min: 20, max: 20, type: 3 },
      height: { min: 20, max: 20, type: 3 },
    }
  }
)

commands = Clay.end_layout

puts commands.inspect
