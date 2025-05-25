#include <stdlib.h>

#define CLAY_IMPLEMENTATION
#include "../renderers/testing.c"

int main() {
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

  float screenWidth = 120.0f;
  float screenHeight = 120.0f;

  Clay_Initialize(arena, (Clay_Dimensions){screenWidth, screenHeight}, (Clay_ErrorHandler){HandleClayErrors});

  Clay_SetMeasureTextFunction(MeasureTextTerminal, NULL);

  Clay_BeginLayout();

  // An example of laying out a UI with a fixed width sidebar and flexible
  // width main content
  CLAY({.id = CLAY_ID("root"),
        .backgroundColor = COLOR_RED,
        .layout = {.padding = CLAY_PADDING_ALL(1),
                   .sizing = {.width = {.type = CLAY__SIZING_TYPE_GROW}, .height = {.type = CLAY__SIZING_TYPE_GROW}}}

  }) {
    CLAY({.backgroundColor = COLOR_RED,
          .layout = {.padding = CLAY_PADDING_ALL(1),
                     .sizing = {.width = {.type = CLAY__SIZING_TYPE_GROW}, .height = {.type = CLAY__SIZING_TYPE_GROW}}}

    }) {
      CLAY_TEXT(CLAY_STRING("Lorem ipsum dolor it amet, consectetur adipisicing elit, sed"),
                CLAY_TEXT_CONFIG({.textColor = COLOR_YELLOW, .textAlignment = CLAY_TEXT_ALIGN_LEFT}));
    }
    CLAY({.backgroundColor = COLOR_RED,
          .layout = {.padding = CLAY_PADDING_ALL(1),
                     .sizing = {.width = {.type = CLAY__SIZING_TYPE_GROW}, .height = {.type = CLAY__SIZING_TYPE_GROW}}}

    }) {
      CLAY_TEXT(CLAY_STRING("Lorem ipsum dolor it amet, consectetur adipisicing elit, sed"),
                CLAY_TEXT_CONFIG({.textColor = COLOR_YELLOW, .textAlignment = CLAY_TEXT_ALIGN_CENTER}));
    }
    CLAY({.backgroundColor = COLOR_RED,
          .layout = {.padding = CLAY_PADDING_ALL(1),
                     .sizing = {.width = {.type = CLAY__SIZING_TYPE_GROW}, .height = {.type = CLAY__SIZING_TYPE_GROW}}}

    }) {
      CLAY_TEXT(CLAY_STRING("Lorem ipsum dolor it amet, consectetur adipisicing elit, sed"),
                CLAY_TEXT_CONFIG({.textColor = COLOR_YELLOW, .textAlignment = CLAY_TEXT_ALIGN_RIGHT}));
    }
  }

  // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
  Clay_RenderCommandArray renderCommands = Clay_EndLayout();

  const char* filename = "experiments/testing/text_alignments.yml";
  reset_yaml_output(filename);
  for (int i = 0; i < renderCommands.length; ++i) {
    append_command_to_yaml(filename, &renderCommands.internalArray[i]);
  }

  return 0;
}
