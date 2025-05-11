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
# int main() {
#   setlocale(LC_ALL, "");
#   uint64_t totalMemorySize = Clay_MinMemorySize();
#   Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(
#       totalMemorySize, malloc(totalMemorySize));

#   tb_init();
#   int screenWidth = tb_width();
#   int screenHeight = tb_height();
#   Clay_Initialize(arena, (Clay_Dimensions){screenWidth, screenHeight},
#                   (Clay_ErrorHandler){HandleClayErrors});

#   Clay_SetMeasureTextFunction(MeasureTextTerminal, NULL);

#   struct tb_event ev;

#   while (1) {
#     Clay_SetLayoutDimensions(
#         (Clay_Dimensions){.width = tb_width(), .height = tb_height()});
#     tb_peek_event(&ev, 100);
#     if (ev.type == TB_EVENT_KEY && ev.ch == 0x0071) {
#       break;
#     }

#     Clay_BeginLayout();

#     // An example of laying out a UI with a fixed width sidebar and flexible
#     // width main content
#     CLAY({.id = CLAY_ID("root"),
#           .backgroundColor = COLOR_RED,
#           .layout = {
#               .childGap = 10, .padding = 1, .sizing = {CLAY_SIZING_GROW(0)}}}) {
#       CLAY({.id = CLAY_ID("FIRST"),
#             .backgroundColor = COLOR_BLACK,
#             .layout = {
#                 .padding = 1,
#                 .sizing = {CLAY_SIZING_PERCENT(.5f), CLAY_SIZING_GROW()}}}) {
#         CLAY_TEXT(CLAY_STRING("Hello, World!"),
#                   CLAY_TEXT_CONFIG({.textColor = COLOR_WHITE}));
#       }
#       CLAY({.id = CLAY_ID("SECOND"),
#             .backgroundColor = COLOR_GREEN,
#             .layout = {
#                 .sizing = {CLAY_SIZING_PERCENT(.5f), CLAY_SIZING_GROW(0)}}}) {
#         CLAY_TEXT(CLAY_STRING("Hello, World!"),
#                   CLAY_TEXT_CONFIG({.textColor = COLOR_WHITE}));
#       }
#     }

#     // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
#     Clay_RenderCommandArray renderCommands = Clay_EndLayout();
#     DrawClayCommands(renderCommands);
#     tb_present();
#   }
#   tb_shutdown();
#   return 0;
# }