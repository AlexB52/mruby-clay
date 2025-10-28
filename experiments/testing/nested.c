#include <stdlib.h>

#define CLAY_IMPLEMENTATION
#include "../renderers/testing.c"

int main() {
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

  float screenWidth = 100.0f;
  float screenHeight = 100.0f;

  Clay_Initialize(arena, (Clay_Dimensions){screenWidth, screenHeight}, (Clay_ErrorHandler){HandleClayErrors});

  Clay_SetMeasureTextFunction(MeasureTextTerminal, NULL);

  Clay_BeginLayout();
  CLAY(CLAY_ID("root"),
       {.backgroundColor = COLOR_RED,
        .layout = {
            .padding = {1, 1, 1, 1},
            .sizing = {.width = {.type = CLAY__SIZING_TYPE_FIXED, .size = {.minMax = {.min = 20, .max = 20}}},
                       .height = {.type = CLAY__SIZING_TYPE_FIXED, .size = {.minMax = {.min = 20, .max = 20}}}}}}) {
    CLAY(CLAY_ID("first"),
         {.backgroundColor = COLOR_BLUE,
          .layout = {.padding = {1, 1, 1, 1},
                     .sizing = {.width = {.type = CLAY__SIZING_TYPE_PERCENT, .size = {.percent = 0.5f}},
                                .height = {.type = CLAY__SIZING_TYPE_PERCENT, .size = {.percent = 0.5f}}}}}) {}
  }

  // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
  Clay_RenderCommandArray renderCommands = Clay_EndLayout();

  const char* filename = "experiments/testing/nested.yml";
  reset_yaml_output(filename);
  for (int i = 0; i < renderCommands.length; ++i) {
    append_command_to_yaml(filename, &renderCommands.internalArray[i]);
  }

  return 0;
}