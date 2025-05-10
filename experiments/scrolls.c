#include <locale.h>
#define CLAY_IMPLEMENTATION
#define TB_IMPL
#define TERMBOX_RENDERER_IMPL
#include "../renderers/termbox2.h"

int main() {
  setlocale(LC_ALL, "");
  // Note: malloc is only used here as an example, any allocator that
  // provides a pointer to addressable memory of at least totalMemorySize
  // will work
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(
      totalMemorySize, malloc(totalMemorySize));

  tb_init();
  tb_set_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
  // buf now contains "The answer is 42", nothing has been printed
  int screenWidth = tb_width();
  int screenHeight = tb_height();
  Clay_Initialize(arena, (Clay_Dimensions){screenWidth, screenHeight},
                  (Clay_ErrorHandler){HandleClayErrors});

  Clay_SetMeasureTextFunction(MeasureTextTerminal, NULL);

  char rightText[128] = "Hello";
  Clay_Vector2 pointerPos = {0, 0};
  float scrollX, scrollY = 0.0f;
  bool isMouseDown = false;
  struct tb_event ev;

  while (1) {
    Clay_SetLayoutDimensions(
        (Clay_Dimensions){.width = tb_width(), .height = tb_height()});
    scrollX = 0.0f;
    scrollY = 0.0f;
    tb_peek_event(&ev, 100);
    if (ev.type == TB_EVENT_KEY && ev.ch == 0x0071) {
      break;
    }

    if (ev.type == TB_EVENT_MOUSE) {
      // track pointer pos + button
      pointerPos.x = (float)ev.x;
      pointerPos.y = (float)ev.y;
      isMouseDown = (ev.key == TB_KEY_MOUSE_LEFT);

      // accumulate wheel deltas
      if (ev.key == TB_KEY_MOUSE_WHEEL_UP) {
        scrollY += 0.1f;
      } else if (ev.key == TB_KEY_MOUSE_WHEEL_DOWN) {
        scrollY -= 0.1f;
      }
    }
    snprintf(rightText, sizeof(rightText), "%.1f,%.1f - %.1f,%.1f - %d",
             pointerPos.x, pointerPos.y, scrollX, scrollY, isMouseDown);

    Clay_SetPointerState(pointerPos, isMouseDown);
    Clay_UpdateScrollContainers(true, (Clay_Vector2){scrollY, scrollY}, 0.1f);

    Clay_BeginLayout();

    // An example of laying out a UI with a fixed width sidebar and flexible
    // width main content
    CLAY(
        {.id = CLAY_ID("root"),
         .backgroundColor = COLOR_RED,
         .layout = {.childGap = 1,
                    .padding = CLAY_PADDING_ALL(1),
                    .sizing = {
                        // make the root fill the space given by Clay_Initialize
                        CLAY_SIZING_GROW(0),  // width
                        CLAY_SIZING_GROW(0)   // height
                    }}}) {
      CLAY({.id = CLAY_ID("FIRST"),
            .backgroundColor = COLOR_BLACK,
            .clip = {.vertical = true, .childOffset = Clay_GetScrollOffset()},
            .border = {.width = CLAY_BORDER_ALL(3),
                       .backgroundColor = COLOR_BLACK},
            .layout = {
                .padding = CLAY_PADDING_ALL(1),
                .sizing = {CLAY_SIZING_PERCENT(.5f), CLAY_SIZING_FIXED(25)}}}) {
        CLAY_TEXT(
            CLAY_STRING(
                "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed "
                "do eiusmod tempor incididunt ut labore et dolore magna "
                "aliqua. Ut enim ad minim veniam, quis nostrud exercitation "
                "ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis "
                "aute irure dolor in reprehenderit in voluptate velit esse "
                "cillum dolore eu fugiat nulla pariatur. Excepteur sint "
                "occaecat cupidatat non proident, sunt in culpa qui officia "
                "deserunt mollit anim id est laborum.Lorem ipsum dolor sit "
                "amet, consectetur adipisicing elit, sed do eiusmod tempor "
                "incididunt ut labore et dolore magna aliqua. Ut enim ad minim "
                "veniam, quis nostrud exercitation ullamco laboris nisi ut "
                "aliquip ex ea commodo consequat. Duis aute irure dolor in "
                "reprehenderit in voluptate velit esse cillum dolore eu fugiat "
                "nulla pariatur. Excepteur sint occaecat cupidatat non "
                "proident, sunt in culpa qui officia deserunt mollit anim id "
                "est laborum.Lorem ipsum dolor sit amet, consectetur "
                "adipisicing elit, sed do eiusmod tempor incididunt ut labore "
                "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud "
                "exercitation ullamco laboris nisi ut aliquip ex ea commodo "
                "\n\n"
                "consequat. Duis aute irure dolor in reprehenderit in "
                "voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
                "Excepteur sint occaecat cupidatat non proident, sunt in culpa "
                "qui officia deserunt mollit anim id est laborum.Lorem ipsum "
                "dolor sit amet, consectetur adipisicing elit, sed do eiusmod "
                "tempor incididunt ut labore et dolore magna aliqua. Ut enim "
                "ad minim veniam, quis nostrud exercitation ullamco laboris "
                "nisi ut aliquip ex ea commodo consequat. Duis aute irure "
                "dolor in reprehenderit in voluptate velit esse cillum dolore "
                "eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
                "non proident, sunt in culpa qui officia deserunt mollit anim "
                "id est laborum.Lorem ipsum dolor sit amet, consectetur "
                "adipisicing elit, sed do eiusmod tempor incididunt ut labore "
                "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud "
                "exercitation ullamco laboris nisi ut aliquip ex ea commodo "
                "\n\n"
                "consequat. Duis aute irure dolor in reprehenderit in "
                "voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
                "Excepteur sint occaecat cupidatat non proident, sunt in culpa "
                "qui officia deserunt mollit anim id est laborum.Lorem ipsum "
                "dolor sit amet, consectetur adipisicing elit, sed do eiusmod "
                "tempor incididunt ut labore et dolore magna aliqua. Ut enim "
                "ad minim veniam, quis nostrud exercitation ullamco laboris "
                "nisi ut aliquip ex ea commodo consequat. Duis aute irure "
                "dolor in reprehenderit in voluptate velit esse cillum dolore "
                "eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
                "non proident, sunt in culpa qui officia deserunt mollit anim "
                "id est laborum.Lorem ipsum dolor sit amet, consectetur "
                "adipisicing elit, sed do eiusmod tempor incididunt ut labore "
                "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud "
                "exercitation ullamco laboris nisi ut aliquip ex ea commodo "
                "\n\n"
                "consequat. Duis aute irure dolor in reprehenderit in "
                "voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
                "Excepteur sint occaecat cupidatat non proident, sunt in culpa "
                "qui officia deserunt mollit anim id est laborum.Lorem ipsum "
                "dolor sit amet, consectetur adipisicing elit, sed do eiusmod "
                "tempor incididunt ut labore et dolore magna aliqua. Ut enim "
                "ad minim veniam, quis nostrud exercitation ullamco laboris "
                "nisi ut aliquip ex ea commodo consequat. Duis aute irure "
                "dolor in reprehenderit in voluptate velit esse cillum dolore "
                "eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
                "non proident, sunt in culpa qui officia deserunt mollit anim "
                "id est laborum.Lorem ipsum dolor sit amet, consectetur "
                "adipisicing elit, sed do eiusmod tempor incididunt ut labore "
                "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud "
                "exercitation ullamco laboris nisi ut aliquip ex ea commodo "
                "\n\n"
                "consequat. Duis aute irure dolor in reprehenderit in "
                "voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
                "Excepteur sint occaecat cupidatat non proident, sunt in culpa "
                "qui officia deserunt mollit anim id est laborum.Lorem ipsum "
                "dolor sit amet, consectetur adipisicing elit, sed do eiusmod "
                "tempor incididunt ut labore et dolore magna aliqua. Ut enim "
                "ad minim veniam, quis nostrud exercitation ullamco laboris "
                "nisi ut aliquip ex ea commodo consequat. Duis aute irure "
                "dolor in reprehenderit in voluptate velit esse cillum dolore "
                "eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
                "non proident, sunt in culpa qui officia deserunt mollit anim "
                "id est laborum.Lorem ipsum dolor sit amet, consectetur "
                "adipisicing elit, sed do eiusmod tempor incididunt ut labore "
                "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud "
                "exercitation ullamco laboris nisi ut aliquip ex ea commodo "
                "\n\n"
                "consequat. Duis aute irure dolor in reprehenderit in "
                "voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
                "Excepteur sint occaecat cupidatat non proident, sunt in culpa "
                "qui officia deserunt mollit anim id est laborum.Lorem ipsum "
                "dolor sit amet, consectetur adipisicing elit, sed do eiusmod "
                "tempor incididunt ut labore et dolore magna aliqua. Ut enim "
                "ad minim veniam, quis nostrud exercitation ullamco laboris "
                "nisi ut aliquip ex ea commodo consequat. Duis aute irure "
                "dolor in reprehenderit in voluptate velit esse cillum dolore "
                "eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
                "non proident, sunt in culpa qui officia deserunt mollit anim "
                "id est laborum."),
            CLAY_TEXT_CONFIG({.textColor = COLOR_WHITE,
                              .backgroundColor = COLOR_BLACK,
                              .textAlignment = CLAY_TEXT_ALIGN_CENTER}));
      }
      CLAY({.id = CLAY_ID("SECOND"),
            .backgroundColor = COLOR_GREEN,
            .layout = {
                .sizing = {CLAY_SIZING_PERCENT(.5f), CLAY_SIZING_GROW(0)}}}) {
        Clay_String text = (Clay_String){.isStaticallyAllocated = false,
                                         .length = (uint32_t)strlen(rightText),
                                         .chars = rightText};

        CLAY_TEXT(text, CLAY_TEXT_CONFIG({.textColor = COLOR_WHITE}));
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