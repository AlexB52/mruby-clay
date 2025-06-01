#include <stdlib.h>

#define CLAY_IMPLEMENTATION
#include "../renderers/testing.c"
#include "clay_example_layout.c"

int main() {
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

  float screenWidth = 10000.0f;
  float screenHeight = 10000.0f;

  Clay_Initialize(arena, (Clay_Dimensions){screenWidth, screenHeight}, (Clay_ErrorHandler){HandleClayErrors});

  Clay_SetMeasureTextFunction(MeasureTextTerminal, NULL);

  ClayVideoDemo_Data data = ClayVideoDemo_Initialize();

  // Run once per frame
  Clay_SetLayoutDimensions((Clay_Dimensions){.width = 10000.0f, .height = 10000.0f});

  Clay_SetPointerState((Clay_Vector2){0, 0}, false);
  Clay_UpdateScrollContainers(true, (Clay_Vector2){0, 0}, 0.8f);

  Clay_RenderCommandArray renderCommands = ClayVideoDemo_CreateLayout(&data);

  const char* filename = "experiments/testing/clay_example.yml";
  reset_yaml_output(filename);
  for (int i = 0; i < renderCommands.length; ++i) {
    append_command_to_yaml(filename, &renderCommands.internalArray[i]);
  }

  return 0;
}