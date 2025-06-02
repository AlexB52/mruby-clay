class TestClayExample < MTest::Unit::TestCase
  COLOR_90 = Clay::Colors.build(90, 90, 90, 255)
  COLOR_120 = Clay::Colors.build(120, 120, 120, 255)
  COLOR_140 = Clay::Colors.build(140, 140, 140, 255)
  COLOR_255 = Clay::Colors.build(255, 255, 255, 255)
  LAYOUT_EXPAND = {width: Clay::Sizing.grow, height: Clay::Sizing.grow}

  def test_commands

    Clay.init(10_000, 10_000) do |error|
      raise error[:message]
    end

    Clay.measure_text do |text, config|
      [text.length, 1]
    end

    Clay.set_layout_dimensions(10_000, 10_000)

    Clay.begin_layout

    Clay.ui(
      id: "OuterContainer",
      background_color: Clay::Colors.build(43, 41, 51, 255).to_h,
      layout: {
        layout_direction: Clay::LayoutDirection[:top_to_bottom],
        sizing: LAYOUT_EXPAND,
        padding: Clay::Padding[16],
        child_gap: 16
      }
    ) do
      Clay.ui(
        id: "HeaderBar",
        background_color: COLOR_90.to_h,
        corner_radius: Clay::Corners[8],
        layout: {
          sizing: { height: Clay::Sizing.fixed(60), width: Clay::Sizing.grow },
          padding: Clay::Padding[0, 16],
          child_gap: 16,
          child_alignment: Clay::ChildAlignment[:left, :center],
        }
      ) do
        render_header_button("File")
        render_header_button("Edit")
        Clay.ui(layout: { sizing: { width: Clay::Sizing.grow, height: Clay::Sizing.grow }})
        render_header_button("Upload")
        render_header_button("Media")
        render_header_button("Support")
      end
      Clay.ui(id: "LowerContent", layout: { sizing: LAYOUT_EXPAND, child_gap: 16 }) do
        Clay.ui(
          id: "sidebar",
          background_color: COLOR_90.to_h,
          layout: {
            layout_direction: Clay::LayoutDirection[:top_to_bottom],
            padding: Clay::Padding[16],
            child_gap: 8,
            sizing: { width: Clay::Sizing.fixed(250), height: Clay::Sizing.grow }
          }
        ) do
          button_layout = { sizing: { width: Clay::Sizing.grow, height: Clay::Sizing.fit }, padding: Clay::Padding[16] }
          Clay.ui(layout: button_layout, background_color: COLOR_120.to_h, corner_radius: Clay::Corners[8]) do
            Clay.text("Squirrels", text_color: COLOR_255.to_h)
          end
          Clay.ui(layout: button_layout, background_color: Clay::Colors.build(120, 120, 120, 0).to_h, corner_radius: Clay::Corners[8]) do
            Clay.text("Lorem Ipsum", text_color: COLOR_255.to_h)
          end
          Clay.ui(layout: button_layout, background_color: Clay::Colors.build(120, 120, 120, 0).to_h, corner_radius: Clay::Corners[8]) do
            Clay.text("Vacuum Instructions", text_color: COLOR_255.to_h)
          end
          Clay.ui(layout: button_layout, background_color: Clay::Colors.build(120, 120, 120, 0).to_h, corner_radius: Clay::Corners[8]) do
            Clay.text("Article 4", text_color: COLOR_255.to_h)
          end
          Clay.ui(layout: button_layout, background_color: Clay::Colors.build(120, 120, 120, 0).to_h, corner_radius: Clay::Corners[8]) do
            Clay.text("Article 5", text_color: COLOR_255.to_h)
          end
        end

        Clay.ui(
          id: "MainContent",
          background_color: COLOR_90.to_h,
          clip: { vertical: true, child_offset: { x: 0, y: 0 }},
          layout: {
            layout_direction: Clay::LayoutDirection[:top_to_bottom],
            child_gap: 16,
            padding: Clay::Padding[16],
            sizing: LAYOUT_EXPAND
          }
        ) do
          Clay.text("Squirrels", text_color: COLOR_255.to_h)
          Clay.text(<<~TEXT, text_color: COLOR_255.to_h)
            The Secret Life of Squirrels: Nature's Clever Acrobats
            Squirrels are often overlooked creatures, dismissed as mere park inhabitants or backyard nuisances. Yet, beneath their fluffy tails and twitching noses lies an intricate world of cunning, agility, and survival tactics that are nothing short of fascinating. As one of the most common mammals in North America, squirrels have adapted to a wide range of environments from bustling urban centers to tranquil forests and have developed a variety of unique behaviors that continue to intrigue scientists and nature enthusiasts alike.

            Master Tree Climbers
            At the heart of a squirrel's skill set is its impressive ability to navigate trees with ease. Whether they're darting from branch to branch or leaping across wide gaps, squirrels possess an innate talent for acrobatics. Their powerful hind legs, which are longer than their front legs, give them remarkable jumping power. With a tail that acts as a counterbalance, squirrels can leap distances of up to ten times the length of their body, making them some of the best aerial acrobats in the animal kingdom.
            But it's not just their agility that makes them exceptional climbers. Squirrels' sharp, curved claws allow them to grip tree bark with precision, while the soft pads on their feet provide traction on slippery surfaces. Their ability to run at high speeds and scale vertical trunks with ease is a testament to the evolutionary adaptations that have made them so successful in their arboreal habitats.

            Food Hoarders Extraordinaire
            Squirrels are often seen frantically gathering nuts, seeds, and even fungi in preparation for winter. While this behavior may seem like instinctual hoarding, it is actually a survival strategy that has been honed over millions of years. Known as 'scatter hoarding,' squirrels store their food in a variety of hidden locations, often burying it deep in the soil or stashing it in hollowed-out tree trunks.
            Interestingly, squirrels have an incredible memory for the locations of their caches. Research has shown that they can remember thousands of hiding spots, often returning to them months later when food is scarce. However, they don't always recover every stash some forgotten caches eventually sprout into new trees, contributing to forest regeneration. This unintentional role as forest gardeners highlights the ecological importance of squirrels in their ecosystems.

            The Great Squirrel Debate: Urban vs. Wild
            While squirrels are most commonly associated with rural or wooded areas, their adaptability has allowed them to thrive in urban environments as well. In cities, squirrels have become adept at finding food sources in places like parks, streets, and even garbage cans. However, their urban counterparts face unique challenges, including traffic, predators, and the lack of natural shelters. Despite these obstacles, squirrels in urban areas are often observed using human infrastructure such as buildings, bridges, and power lines as highways for their acrobatic escapades.
            There is, however, a growing concern regarding the impact of urban life on squirrel populations. Pollution, deforestation, and the loss of natural habitats are making it more difficult for squirrels to find adequate food and shelter. As a result, conservationists are focusing on creating squirrel-friendly spaces within cities, with the goal of ensuring these resourceful creatures continue to thrive in both rural and urban landscapes.

            A Symbol of Resilience
            In many cultures, squirrels are symbols of resourcefulness, adaptability, and preparation. Their ability to thrive in a variety of environments while navigating challenges with agility and grace serves as a reminder of the resilience inherent in nature. Whether you encounter them in a quiet forest, a city park, or your own backyard, squirrels are creatures that never fail to amaze with their endless energy and ingenuity.
            In the end, squirrels may be small, but they are mighty in their ability to survive and thrive in a world that is constantly changing. So next time you spot one hopping across a branch or darting across your lawn, take a moment to appreciate the remarkable acrobat at work a true marvel of the natural world.
          TEXT
        end
      end
    end

    commands = Clay.end_layout
    File.open('result.txt', 'wb') { |f| f.write(commands) }
    assert_equal([
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 0.0, "y" => 0.0, "width" => 10000.0, "height" => 10000.0},
        "background_color" => {"r" => 43.0, "g" => 41.0, "b" => 51.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 0.0, "top_right" => 0.0, "bottom_left" => 0.0, "bottom_right" => 0.0}
      },
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 16.0, "y" => 16.0, "width" => 9968.0, "height" => 60.0},
        "background_color" => {"r" => 90.0, "g" => 90.0, "b" => 90.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 8.0, "top_right" => 8.0, "bottom_left" => 8.0, "bottom_right" => 8.0}
      },
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 32.0, "y" => 37.5, "width" => 36.0, "height" => 17.0},
        "background_color" => {"r" => 140.0, "g" => 140.0, "b" => 140.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 5.0, "top_right" => 5.0, "bottom_left" => 5.0, "bottom_right" => 5.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 48.0, "y" => 45.5, "width" => 4.0, "height" => 1.0},
        "text" => "File",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 84.0, "y" => 37.5, "width" => 36.0, "height" => 17.0},
        "background_color" => {"r" => 140.0, "g" => 140.0, "b" => 140.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 5.0, "top_right" => 5.0, "bottom_left" => 5.0, "bottom_right" => 5.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 100.0, "y" => 45.5, "width" => 4.0, "height" => 1.0},
        "text" => "Edit",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 9822.0, "y" => 37.5, "width" => 38.0, "height" => 17.0},
        "background_color" => {"r" => 140.0, "g" => 140.0, "b" => 140.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 5.0, "top_right" => 5.0, "bottom_left" => 5.0, "bottom_right" => 5.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 9838.0, "y" => 45.5, "width" => 6.0, "height" => 1.0},
        "text" => "Upload",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 9876.0, "y" => 37.5, "width" => 37.0, "height" => 17.0},
        "background_color" => {"r" => 140.0, "g" => 140.0, "b" => 140.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 5.0, "top_right" => 5.0, "bottom_left" => 5.0, "bottom_right" => 5.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 9892.0, "y" => 45.5, "width" => 5.0, "height" => 1.0},
        "text" => "Media",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 9929.0, "y" => 37.5, "width" => 39.0, "height" => 17.0},
        "background_color" => {"r" => 140.0, "g" => 140.0, "b" => 140.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 5.0, "top_right" => 5.0, "bottom_left" => 5.0, "bottom_right" => 5.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 9945.0, "y" => 45.5, "width" => 7.0, "height" => 1.0},
        "text" => "Support",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 16.0, "y" => 92.0, "width" => 250.0, "height" => 9892.0},
        "background_color" => {"r" => 90.0, "g" => 90.0, "b" => 90.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 0.0, "top_right" => 0.0, "bottom_left" => 0.0, "bottom_right" => 0.0}
      },
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 32.0, "y" => 108.0, "width" => 218.0, "height" => 33.0},
        "background_color" => {"r" => 120.0, "g" => 120.0, "b" => 120.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 8.0, "top_right" => 8.0, "bottom_left" => 8.0, "bottom_right" => 8.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 48.0, "y" => 124.0, "width" => 9.0, "height" => 1.0},
        "text" => "Squirrels",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 48.0, "y" => 165.0, "width" => 11.0, "height" => 1.0},
        "text" => "Lorem Ipsum",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 48.0, "y" => 206.0, "width" => 19.0, "height" => 1.0},
        "text" => "Vacuum Instructions",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 48.0, "y" => 247.0, "width" => 9.0, "height" => 1.0},
        "text" => "Article 4",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 48.0, "y" => 288.0, "width" => 9.0, "height" => 1.0},
        "text" => "Article 5",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :scissor_start,
        "bounding_box" => {"x" => 282.0, "y" => 92.0, "width" => 9702.0, "height" => 9892.0}
      },
      {
        "type" => :rectangle,
        "bounding_box" => {"x" => 282.0, "y" => 92.0, "width" => 9702.0, "height" => 9892.0},
        "background_color" => {"r" => 90.0, "g" => 90.0, "b" => 90.0, "a" => 255.0},
        "corner_radius" => {"top_left" => 0.0, "top_right" => 0.0, "bottom_left" => 0.0, "bottom_right" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 108.0, "width" => 9.0, "height" => 1.0},
        "text" => "Squirrels",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 125.0, "width" => 54.0, "height" => 1.0},
        "text" => "The Secret Life of Squirrels: Nature's Clever Acrobats",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 126.0, "width" => 527.0, "height" => 1.0},
        "text" => "Squirrels are often overlooked creatures, dismissed as mere park inhabitants or backyard nuisances. Yet, beneath their fluffy tails and twitching noses lies an intricate world of cunning, agility, and survival tactics that are nothing short of fascinating. As one of the most common mammals in North America, squirrels have adapted to a wide range of environments from bustling urban centers to tranquil forests and have developed a variety of unique behaviors that continue to intrigue scientists and nature enthusiasts alike.",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 128.0, "width" => 20.0, "height" => 1.0},
        "text" => "Master Tree Climbers",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 129.0, "width" => 506.0, "height" => 1.0},
        "text" => "At the heart of a squirrel's skill set is its impressive ability to navigate trees with ease. Whether they're darting from branch to branch or leaping across wide gaps, squirrels possess an innate talent for acrobatics. Their powerful hind legs, which are longer than their front legs, give them remarkable jumping power. With a tail that acts as a counterbalance, squirrels can leap distances of up to ten times the length of their body, making them some of the best aerial acrobats in the animal kingdom.",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 130.0, "width" => 399.0, "height" => 1.0},
        "text" => "But it's not just their agility that makes them exceptional climbers. Squirrels' sharp, curved claws allow them to grip tree bark with precision, while the soft pads on their feet provide traction on slippery surfaces. Their ability to run at high speeds and scale vertical trunks with ease is a testament to the evolutionary adaptations that have made them so successful in their arboreal habitats.",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 132.0, "width" => 28.0, "height" => 1.0},
        "text" => "Food Hoarders Extraordinaire",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 133.0, "width" => 404.0, "height" => 1.0},
        "text" => "Squirrels are often seen frantically gathering nuts, seeds, and even fungi in preparation for winter. While this behavior may seem like instinctual hoarding, it is actually a survival strategy that has been honed over millions of years. Known as 'scatter hoarding,' squirrels store their food in a variety of hidden locations, often burying it deep in the soil or stashing it in hollowed-out tree trunks.",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 134.0, "width" => 467.0, "height" => 1.0},
        "text" => "Interestingly, squirrels have an incredible memory for the locations of their caches. Research has shown that they can remember thousands of hiding spots, often returning to them months later when food is scarce. However, they don't always recover every stash some forgotten caches eventually sprout into new trees, contributing to forest regeneration. This unintentional role as forest gardeners highlights the ecological importance of squirrels in their ecosystems.",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 136.0, "width" => 41.0, "height" => 1.0},
        "text" => "The Great Squirrel Debate: Urban vs. Wild",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 137.0, "width" => 571.0, "height" => 1.0},
        "text" => "While squirrels are most commonly associated with rural or wooded areas, their adaptability has allowed them to thrive in urban environments as well. In cities, squirrels have become adept at finding food sources in places like parks, streets, and even garbage cans. However, their urban counterparts face unique challenges, including traffic, predators, and the lack of natural shelters. Despite these obstacles, squirrels in urban areas are often observed using human infrastructure such as buildings, bridges, and power lines as highways for their acrobatic escapades.",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 138.0, "width" => 437.0, "height" => 1.0},
        "text" => "There is, however, a growing concern regarding the impact of urban life on squirrel populations. Pollution, deforestation, and the loss of natural habitats are making it more difficult for squirrels to find adequate food and shelter. As a result, conservationists are focusing on creating squirrel-friendly spaces within cities, with the goal of ensuring these resourceful creatures continue to thrive in both rural and urban landscapes.",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 140.0, "width" => 22.0, "height" => 1.0},
        "text" => "A Symbol of Resilience",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 141.0, "width" => 424.0, "height" => 1.0},
        "text" => "In many cultures, squirrels are symbols of resourcefulness, adaptability, and preparation. Their ability to thrive in a variety of environments while navigating challenges with agility and grace serves as a reminder of the resilience inherent in nature. Whether you encounter them in a quiet forest, a city park, or your own backyard, squirrels are creatures that never fail to amaze with their endless energy and ingenuity.",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :text,
        "bounding_box" => {"x" => 298.0, "y" => 142.0, "width" => 308.0, "height" => 1.0},
        "text" => "In the end, squirrels may be small, but they are mighty in their ability to survive and thrive in a world that is constantly changing. So next time you spot one hopping across a branch or darting across your lawn, take a moment to appreciate the remarkable acrobat at work a true marvel of the natural world.",
        "text_color" => {"r" => 255.0, "g" => 255.0, "b" => 255.0, "a" => 255.0},
        "background_color" => {"r" => 0.0, "g" => 0.0, "b" => 0.0, "a" => 0.0}
      },
      {
        "type" => :scissor_end,
        "bounding_box" => {"x" => 0.0, "y" => 0.0, "width" => 0.0, "height" => 0.0}
      }
    ], commands)

  end

  def render_header_button(text)
    Clay.ui(
      layout: { padding: Clay::Padding[8, 16] },
      background_color: COLOR_140.to_h,
      corner_radius: Clay::Corners[5]
    ) do
      Clay.text(text, text_color: COLOR_255.to_h)
    end
  end
end

MTest::Unit.new.run
