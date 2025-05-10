#include <clay.h>
#include <termbox2.h>

const Clay_Color COLOR_DEFAULT = (Clay_Color){0, 0, 0, 0};
const Clay_Color COLOR_BLACK = (Clay_Color){0, 0, 0, 255};
const Clay_Color COLOR_RED = (Clay_Color){255, 0, 0, 255};
const Clay_Color COLOR_GREEN = (Clay_Color){0, 255, 0, 255};
const Clay_Color COLOR_YELLOW = (Clay_Color){255, 255, 0, 255};
const Clay_Color COLOR_BLUE = (Clay_Color){0, 0, 255, 255};
const Clay_Color COLOR_MAGENTA = (Clay_Color){255, 0, 255, 255};
const Clay_Color COLOR_CYAN = (Clay_Color){0, 255, 255, 255};
const Clay_Color COLOR_WHITE = (Clay_Color){255, 255, 255, 255};

#define TB_DEFAULT 0x0000
#define TB_BLACK 0x0001
#define TB_RED 0x0002
#define TB_GREEN 0x0003
#define TB_YELLOW 0x0004
#define TB_BLUE 0x0005
#define TB_MAGENTA 0x0006
#define TB_CYAN 0x0007
#define TB_WHITE 0x0008

void HandleClayErrors(Clay_ErrorData errorData);
uint16_t TBColorFromClayColor(const Clay_Color color);
Clay_Dimensions MeasureTextTerminal(Clay_StringSlice text, Clay_TextElementConfig* cfg, void* userData);
void DrawRectangle(const Clay_BoundingBox bbox, Clay_Color color);
void DrawTextCommand(Clay_BoundingBox bbox, Clay_TextRenderData text);
void DrawClayCommands(Clay_RenderCommandArray commands);

#ifdef TERMBOX_RENDERER_IMPL

void HandleClayErrors(Clay_ErrorData errorData) {
  // See the Clay_ErrorData struct for more information
  printf("%s", errorData.errorText.chars);
}

uint16_t TBColorFromClayColor(const Clay_Color color) {
  if (color.a == 0) {
    return TB_DEFAULT;
  }

  uint32_t rgb =
      ((uint32_t)color.r << 16) | ((uint32_t)color.g << 8) | (uint32_t)color.b;

  switch (rgb) {
    case 0x000000:
      return TB_BLACK;
    case 0xFF0000:
      return TB_RED;
    case 0x00FF00:
      return TB_GREEN;
    case 0xFFFF00:
      return TB_YELLOW;
    case 0x0000FF:
      return TB_BLUE;
    case 0xFF00FF:
      return TB_MAGENTA;
    case 0x00FFFF:
      return TB_CYAN;
    case 0xFFFFFF:
      return TB_WHITE;
    default:
      return TB_DEFAULT;
  }
}

// Change the third parameter to void*
Clay_Dimensions MeasureTextTerminal(Clay_StringSlice text, Clay_TextElementConfig* cfg, void* userData) {
  // If you need an integer from the userData, cast it:
  uintptr_t foo = (uintptr_t)userData;

  // Monospace: one cell per character, one row high
  return (Clay_Dimensions){.width = (float)text.length, .height = 1.0f};
}

void DrawRectangle(const Clay_BoundingBox bbox, Clay_Color color) {
  // Convert floats → ints
  int x0 = (int)bbox.x;
  int y0 = (int)bbox.y;
  int w = (int)bbox.width;
  int h = (int)bbox.height;
  int x1 = x0 + w - 1;
  int y1 = y0 + h - 1;
  // tb_printf(0, 0, TB_DEFAULT, TB_BLACK, "%f,%f,%f,%f", x0, y0, w, h);

  for (int yy = y0; yy <= y1; yy++) {
    for (int xx = x0; xx <= x1; xx++) {
      tb_set_cell(xx, yy, ' ', TB_BLACK, TBColorFromClayColor(color));
    }
  }
}

void DrawTextCommand(Clay_BoundingBox bbox, Clay_TextRenderData text) {
  // Starting position
  int x = (int)bbox.x;
  int y = (int)bbox.y;

  // Convert Clay’s RGBA textColor → TB_* (8‑color) fg attribute
  uint16_t fg = TBColorFromClayColor(text.textColor);
  // We'll use the default background
  const uint16_t bg = TB_BLACK;

  // Iterate each rune in the slice
  const char* chars = text.stringContents.chars;
  int len = text.stringContents.length;

  // Advance by 1 cell + any extra letterSpacing per character
  int dx = 0;
  for (int i = 0; i < len; i++) {
    uint32_t ch = (uint32_t)chars[i];  // assumes ASCII or single‑cell runes
    tb_set_cell(x + dx, y, ch, fg, bg);
    dx += 1 + text.letterSpacing;
  }
}

void DrawClayCommands(Clay_RenderCommandArray commands) {
  for (int i = 0; i < commands.length; i++) {
    Clay_RenderCommand* renderCommand = &commands.internalArray[i];
    switch (renderCommand->commandType) {
      case CLAY_RENDER_COMMAND_TYPE_RECTANGLE: {
        DrawRectangle(renderCommand->boundingBox,
                      renderCommand->renderData.rectangle.backgroundColor);
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_TEXT: {
        DrawTextCommand(renderCommand->boundingBox,
                        renderCommand->renderData.text);
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_NONE:
      case CLAY_RENDER_COMMAND_TYPE_BORDER:
      case CLAY_RENDER_COMMAND_TYPE_IMAGE:
      case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START:
      case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END:
      case CLAY_RENDER_COMMAND_TYPE_CUSTOM:
        break;
    }
  }
}

#endif // CLAY_RENDERER_IMPL