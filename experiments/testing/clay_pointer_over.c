#define CLAY_IMPLEMENTATION

#include <clay.h>
#include <stdio.h>
#include <stdlib.h>

const Clay_Color COLOR_RED = (Clay_Color){168, 66, 28, 255};

void HandleClayErrors(Clay_ErrorData errorData) {
  // See the Clay_ErrorData struct for more information
  printf("%s", errorData.errorText.chars);
}

// Change the third parameter to void*
Clay_Dimensions MeasureTextTerminal(Clay_StringSlice text, Clay_TextElementConfig* cfg, void* userData) {
  // If you need an integer from the userData, cast it:
  uintptr_t foo = (uintptr_t)userData;

  // Monospace: one cell per character, one row high
  return (Clay_Dimensions){.width = (float)text.length, .height = 1.0f};
}

int main() {
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

  float screenWidth = 100.0f;
  float screenHeight = 100.0f;

  Clay_ElementId root_id = CLAY_SID(CLAY_STRING("root"));

  Clay_Initialize(arena, (Clay_Dimensions){screenWidth, screenHeight}, (Clay_ErrorHandler){HandleClayErrors});

  Clay_SetMeasureTextFunction(MeasureTextTerminal, NULL);

  Clay_SetLayoutDimensions((Clay_Dimensions){screenWidth, screenHeight});
  // Clay_SetPointerState((Clay_Vector2){15, 15}, true);

  Clay_BeginLayout();

  CLAY(CLAY_ID("root"),
       {.backgroundColor = COLOR_RED, .layout = {.sizing = {CLAY_SIZING_FIXED(20), CLAY_SIZING_FIXED(20)}}});

  // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
  Clay_RenderCommandArray renderCommands = Clay_EndLayout();

  Clay_SetLayoutDimensions((Clay_Dimensions){screenWidth, screenHeight});
  Clay_SetPointerState((Clay_Vector2){15, 15}, true);

  Clay_BeginLayout();

  CLAY(root_id, {.backgroundColor = COLOR_RED, .layout = {.sizing = {CLAY_SIZING_FIXED(20), CLAY_SIZING_FIXED(20)}}});

  // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
  Clay_EndLayout();

  printf("Mouse is in root %s\n", Clay_PointerOver(CLAY_SID(CLAY_STRING("root"))) ? "true" : "false");
  return 0;
}