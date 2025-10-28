#include <locale.h>

#define CLAY_IMPLEMENTATION
#define TB_IMPL
#define TERMBOX_RENDERER_IMPL
#include "../renderers/termbox2.h"

int main() {
  setlocale(LC_ALL, "");
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

  tb_init();
  int screenWidth = tb_width();
  int screenHeight = tb_height();
  Clay_Initialize(arena, (Clay_Dimensions){screenWidth, screenHeight}, (Clay_ErrorHandler){HandleClayErrors});

  Clay_SetMeasureTextFunction(MeasureTextTerminal, NULL);

  struct tb_event ev;

  Clay_Color colors[9] = {
      [0] = COLOR_DEFAULT, [1] = COLOR_BLACK,   [2] = COLOR_RED,  [3] = COLOR_GREEN, [4] = COLOR_YELLOW,
      [5] = COLOR_BLUE,    [6] = COLOR_MAGENTA, [7] = COLOR_CYAN, [8] = COLOR_WHITE,
  };
  while (1) {
    Clay_SetLayoutDimensions((Clay_Dimensions){.width = tb_width(), .height = tb_height()});
    tb_peek_event(&ev, 100);
    if (ev.type == TB_EVENT_KEY && ev.ch == 0x0071) {
      break;
    }

    Clay_BeginLayout();

    // An example of laying out a UI with a fixed width sidebar and flexible
    // width main content
    CLAY(CLAY_ID("root"), {.backgroundColor = COLOR_RED,
                           .layout = {.childGap = 1,
                                      .layoutDirection = CLAY_TOP_TO_BOTTOM,
                                      .padding = CLAY_PADDING_ALL(1),
                                      .sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_GROW()}}}) {
      CLAY_AUTO_ID({.layout = {.sizing = {CLAY_SIZING_PERCENT(1.0f)}}}) {
        for (int i = 0; i < 4; ++i) {
          CLAY_AUTO_ID({.backgroundColor = colors[i % 9],
                        .clip = {.vertical = true},
                        .border = {.width = CLAY_BORDER_ALL(3), .color = COLOR_WHITE, .backgroundColor = colors[i % 9]},
                        .layout = {.padding = CLAY_PADDING_ALL(1), .sizing = {CLAY_SIZING_GROW()}}}) {
            CLAY_TEXT(CLAY_STRING("Lorem ipsum dolor sit amet, consectetur adipisicing "
                                  "elit, sed do eiusmod tempor incididunt ut labore et "
                                  "dolore magna aliqua. Ut enim ad minim veniam, quis "
                                  "nostrud exercitation ullamco laboris nisi ut "
                                  "aliquip ex ea commodo consequat. Duis aute irure "
                                  "dolor in reprehenderit in voluptate velit esse "
                                  "cillum dolore eu fugiat nulla pariatur. Excepteur "
                                  "sint occaecat cupidatat non proident, sunt in culpa "
                                  "qui officia deserunt mollit anim id est laborum."),
                      CLAY_TEXT_CONFIG({.textColor = colors[(i + 1) % 9], .backgroundColor = colors[i % 9]}));
          }
        }
      }
      CLAY_AUTO_ID({.layout = {.sizing = {CLAY_SIZING_PERCENT(1.0f)}}}) {
        for (int i = 0; i < 4; ++i) {
          CLAY_AUTO_ID({.backgroundColor = colors[i % 9],
                        .clip = {.vertical = true},
                        .border = {.width = CLAY_BORDER_ALL(3), .color = COLOR_WHITE, .backgroundColor = colors[i % 9]},
                        .layout = {.padding = CLAY_PADDING_ALL(1), .sizing = {CLAY_SIZING_GROW()}}}) {
            CLAY_TEXT(CLAY_STRING("Lorem ipsum dolor sit amet, consectetur adipisicing "
                                  "elit, sed do eiusmod tempor incididunt ut labore et "
                                  "dolore magna aliqua. Ut enim ad minim veniam, quis "
                                  "nostrud exercitation ullamco laboris nisi ut "
                                  "aliquip ex ea commodo consequat. Duis aute irure "
                                  "dolor in reprehenderit in voluptate velit esse "
                                  "cillum dolore eu fugiat nulla pariatur. Excepteur "
                                  "sint occaecat cupidatat non proident, sunt in culpa "
                                  "qui officia deserunt mollit anim id est laborum."),
                      CLAY_TEXT_CONFIG({.textColor = colors[(i + 1) % 9], .backgroundColor = colors[i % 9]}));
          }
        }
      }
    }

    // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    DrawClayCommands(renderCommands);
    tb_present();
  }
  tb_shutdown();
  return 0;
}