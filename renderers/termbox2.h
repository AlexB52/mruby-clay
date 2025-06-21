#include "../clay/clay.h"
#include "../termbox2/termbox2.h"
#include <stdbool.h>
#include <math.h>

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


bool IsClipped(int x, int y);
uint16_t TBColorFromClayColor(const Clay_Color color);
Clay_Dimensions MeasureTextTerminal(Clay_StringSlice text, Clay_TextElementConfig* cfg, void* userData);
void PushClip(Clay_BoundingBox bbox);
void PopClip(void);
void DrawRectangle(const Clay_BoundingBox bbox, Clay_Color color);
void DrawText(Clay_BoundingBox bbox, Clay_TextRenderData text);
void DrawBorder(Clay_BoundingBox bbox, Clay_BorderRenderData text);
void DrawClayCommands(Clay_RenderCommandArray commands);
int clay_set_cell(int x, int y, uint32_t ch, uintattr_t fg, uintattr_t bg);

#ifdef TERMBOX_RENDERER_IMPL

int clay_set_cell(int x, int y, uint32_t ch, uintattr_t fg, uintattr_t bg) {
  if (IsClipped(x, y)) {
    return 0;
  }

  return tb_set_cell(x, y, ch, fg, bg);
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
      clay_set_cell(xx, yy, ' ', TB_BLACK, TBColorFromClayColor(color));
    }
  }
}

void DrawText(Clay_BoundingBox bbox, Clay_TextRenderData text) {
  // Starting position
  int x = (int)bbox.x;
  int y = (int)bbox.y;

  uint16_t fg = TBColorFromClayColor(text.textColor);
  uint16_t bg = TBColorFromClayColor(text.backgroundColor);

  // Iterate each rune in the slice
  const char* chars = text.stringContents.chars;
  int len = text.stringContents.length;

  // Advance by 1 cell + any extra letterSpacing per character
  int dx = 0;
  for (int i = 0; i < len; i++) {
    uint32_t ch = (uint32_t)chars[i];  // assumes ASCII or single‑cell runes
    clay_set_cell(x + dx, y, ch, fg, bg);
    dx += 1 + text.letterSpacing;
  }
}

typedef struct {
    int tl, tr, bl, br, hb, vb;
} BorderElements;

static const BorderElements BORDER_SIZES[] = {
    /* size 0 */ {  32,   32,   32,   32,   32,   32 },
    /* size 1 */ {  43,   43,   43,   43,   45,  124 },
    /* size 2 */ {9484, 9488, 9492, 9496, 9472, 9474 },
    /* size 3 */ {9487, 9491, 9495, 9499, 9473, 9475 },
    /* size 4 */ {9556, 9559, 9562, 9565, 9552, 9553 },
};

#define NUM_BORDER_SIZES \
    (sizeof BORDER_SIZES / sizeof BORDER_SIZES[0])

static inline BorderElements
BorderElementsFromSize(int size)
{
    if ((unsigned)size >= NUM_BORDER_SIZES)
        size = 0;
    return BORDER_SIZES[size];
}

void DrawBorder(Clay_BoundingBox bbox, Clay_BorderRenderData border) {
  // Starting position
  int x0 = (int)bbox.x;
  int y0 = (int)bbox.y;
  int w = (int)bbox.width;
  int h = (int)bbox.height;
  int x1 = x0 + w - 1;
  int y1 = y0 + h - 1;

  uint16_t fg = TBColorFromClayColor(border.color);
  uint16_t bg = TBColorFromClayColor(border.backgroundColor);

  int leftSize = (int)border.width.left;
  int topSize = (int)border.width.top;
  int rightSize = (int)border.width.right;
  int bottomSize = (int)border.width.bottom;

  BorderElements leftStyle = BorderElementsFromSize(leftSize);
  BorderElements topStyle = BorderElementsFromSize(topSize);
  BorderElements rightStyle = BorderElementsFromSize(rightSize);
  BorderElements bottomStyle = BorderElementsFromSize(bottomSize);

  clay_set_cell(x0, y0, topStyle.tl, fg, bg);
  clay_set_cell(x1, y0, topStyle.tr, fg, bg);
  clay_set_cell(x0, y1, bottomStyle.bl, fg, bg);
  clay_set_cell(x1, y1, bottomStyle.br, fg, bg);

  for (int i = x0+1; i < x1; ++i) {
    clay_set_cell(i, y0, topStyle.hb, fg, bg);
    clay_set_cell(i, y1, bottomStyle.hb, fg, bg);
  }

  for (int j = y0+1; j < y1; ++j) {
    clay_set_cell(x0, j, leftStyle.vb, fg, bg);
    clay_set_cell(x1, j, rightStyle.vb, fg, bg);
  }
}

// --------------------------------------------------
// clip_stack.h
// --------------------------------------------------
typedef struct {
    Clay_BoundingBox boundBox;
    bool             enabled;
} CurrentClip;

static CurrentClip currentClip = { .enabled = false };

// enable clipping
void EnableClip(Clay_BoundingBox bbox) {
    currentClip.boundBox = bbox;
    currentClip.enabled  = true;
}

// disable clipping
void DisableClip(void) {
    currentClip.enabled = false;
}

// test if a cell is outside the clip rect
bool IsClipped(int x, int y) {
    if (!currentClip.enabled) return false;
    Clay_BoundingBox c = currentClip.boundBox;
    return x < (int)c.x
        || y < (int)c.y
        || x >= (int)(c.x + c.width)
        || y >= (int)(c.y + c.height);
}

void DrawClayCommands(Clay_RenderCommandArray commands) {
  for (int i = 0; i < commands.length; i++) {
    Clay_RenderCommand* renderCommand = &commands.internalArray[i];
    switch (renderCommand->commandType) {
      case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START: {
        EnableClip(renderCommand->boundingBox);
        break;
      }

      case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END: {
        DisableClip();
        break;
      }

      case CLAY_RENDER_COMMAND_TYPE_RECTANGLE: {
        DrawRectangle(renderCommand->boundingBox,
                      renderCommand->renderData.rectangle.backgroundColor);
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_TEXT: {
        DrawText(renderCommand->boundingBox,
                        renderCommand->renderData.text);
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_BORDER:
        DrawBorder(renderCommand->boundingBox,
                          renderCommand->renderData.border);
        break;
      case CLAY_RENDER_COMMAND_TYPE_IMAGE:
      case CLAY_RENDER_COMMAND_TYPE_NONE:
      case CLAY_RENDER_COMMAND_TYPE_CUSTOM:
        break;
    }
  }
}

#endif // CLAY_RENDERER_IMPL