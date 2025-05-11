#include <locale.h>

#define CLAY_IMPLEMENTATION
#define TB_IMPL
#define TERMBOX_RENDERER_IMPL
#include "../renderers/termbox2.h"

int main() {
  setlocale(LC_ALL, "");
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(
      totalMemorySize, malloc(totalMemorySize));

  tb_init();
  int screenWidth = tb_width();
  int screenHeight = tb_height();
  Clay_Initialize(arena, (Clay_Dimensions){screenWidth, screenHeight},
                  (Clay_ErrorHandler){HandleClayErrors});

  Clay_SetMeasureTextFunction(MeasureTextTerminal, NULL);

  struct tb_event ev;

  while (1) {
    Clay_SetLayoutDimensions(
        (Clay_Dimensions){.width = tb_width(), .height = tb_height()});
    tb_peek_event(&ev, 100);
    if (ev.type == TB_EVENT_KEY && ev.ch == 0x0071) {
      break;
    }

    Clay_BeginLayout();

    // An example of laying out a UI with a fixed width sidebar and flexible
    // width main content
    CLAY({.id = CLAY_ID("root"),
          .backgroundColor = COLOR_RED,
          .layout = {
              .padding = {1, 1, 1, 1},
              .sizing = {
                  .width = {.type = CLAY__SIZING_TYPE_FIXED,
                            .size = {.minMax = {.min = 20, .max = 20}}},
                  .height = {.type = CLAY__SIZING_TYPE_FIXED,
                             .size = {.minMax = {.min = 20, .max = 20}}}}}}) {
      CLAY({.id = CLAY_ID("first"),
            .backgroundColor = COLOR_BLUE,
            .layout = {.padding = {1, 1, 1, 1},
                       .sizing = {.width = {.type = CLAY__SIZING_TYPE_PERCENT,
                                            .size = {.percent = 0.5f}},
                                  .height = {.type = CLAY__SIZING_TYPE_PERCENT,
                                             .size = {.percent = 0.5f}}}}}) {}
    }

    // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    DrawClayCommands(renderCommands);
    tb_present();
  }
  tb_shutdown();
  return 0;
}