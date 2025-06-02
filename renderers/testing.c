#include <stdint.h>
#include <stdio.h>
#include "clay.h"  // Adjust path as needed for Clay types

void HandleClayErrors(Clay_ErrorData errorData) {
  // See the Clay_ErrorData struct for more information
  printf("%d: %s", errorData.errorType, errorData.errorText.chars);
}

// Change the third parameter to void*
Clay_Dimensions MeasureTextTerminal(Clay_StringSlice text, Clay_TextElementConfig* cfg, void* userData) {
  // If you need an integer from the userData, cast it:
  uintptr_t foo = (uintptr_t)userData;

  // Monospace: one cell per character, one row high
  return (Clay_Dimensions){.width = (float)text.length, .height = 1.0f};
}

void write_indent(FILE* file, int level) {
  for (int i = 0; i < level; ++i) {
    fputs("  ", file);
  }
}

void write_color(FILE* file, const char* name, Clay_Color color, int level) {
  write_indent(file, level);
  fprintf(file, "%s:\n", name);
  write_indent(file, level + 1);
  fprintf(file, "r: %.1f\n", color.r);
  write_indent(file, level + 1);
  fprintf(file, "g: %.1f\n", color.g);
  write_indent(file, level + 1);
  fprintf(file, "b: %.1f\n", color.b);
  write_indent(file, level + 1);
  fprintf(file, "a: %.1f\n", color.a);
}

void write_corner_radius(FILE* file, Clay_CornerRadius radius, int level) {
  write_indent(file, level);
  fprintf(file, "corner_radius:\n");
  write_indent(file, level + 1);
  fprintf(file, "top_left: %.2f\n", radius.topLeft);
  write_indent(file, level + 1);
  fprintf(file, "top_right: %.2f\n", radius.topRight);
  write_indent(file, level + 1);
  fprintf(file, "bottom_left: %.2f\n", radius.bottomLeft);
  write_indent(file, level + 1);
  fprintf(file, "bottom_right: %.2f\n", radius.bottomRight);
}

void write_rectangle_yaml(Clay_RenderCommand* cmd, FILE* file, int level) {
  write_indent(file, level);
  fprintf(file, "- type: rectangle\n");
  write_indent(file, level + 1);
  fprintf(file, "bounding_box:\n");
  write_indent(file, level + 2);
  fprintf(file, "x: %.2f\n", cmd->boundingBox.x);
  write_indent(file, level + 2);
  fprintf(file, "y: %.2f\n", cmd->boundingBox.y);
  write_indent(file, level + 2);
  fprintf(file, "width: %.2f\n", cmd->boundingBox.width);
  write_indent(file, level + 2);
  fprintf(file, "height: %.2f\n", cmd->boundingBox.height);
  write_color(file, "background_color", cmd->renderData.rectangle.backgroundColor, level + 1);
  write_corner_radius(file, cmd->renderData.rectangle.cornerRadius, level + 1);
}

void write_border_yaml(Clay_RenderCommand* cmd, FILE* file, int level) {
  write_indent(file, level);
  fprintf(file, "- type: border\n");
  write_indent(file, level + 1);
  fprintf(file, "bounding_box:\n");
  write_indent(file, level + 2);
  fprintf(file, "x: %.2f\n", cmd->boundingBox.x);
  write_indent(file, level + 2);
  fprintf(file, "y: %.2f\n", cmd->boundingBox.y);
  write_indent(file, level + 2);
  fprintf(file, "width: %.2f\n", cmd->boundingBox.width);
  write_indent(file, level + 2);
  fprintf(file, "height: %.2f\n", cmd->boundingBox.height);
  write_color(file, "color", cmd->renderData.border.color, level + 1);
  write_corner_radius(file, cmd->renderData.border.cornerRadius, level + 1);
}

void write_text_yaml(Clay_RenderCommand* cmd, FILE* file, int level) {
  write_indent(file, level);
  fprintf(file, "- type: text\n");
  write_indent(file, level + 1);
  fprintf(file, "bounding_box:\n");
  write_indent(file, level + 2);
  fprintf(file, "x: %.2f\n", cmd->boundingBox.x);
  write_indent(file, level + 2);
  fprintf(file, "y: %.2f\n", cmd->boundingBox.y);
  write_indent(file, level + 2);
  fprintf(file, "width: %.2f\n", cmd->boundingBox.width);
  write_indent(file, level + 2);
  fprintf(file, "height: %.2f\n", cmd->boundingBox.height);

  write_indent(file, level + 1);
  fprintf(file, "text: \"%.*s\"\n", cmd->renderData.text.stringContents.length,
          cmd->renderData.text.stringContents.chars);

  write_color(file, "text_color", cmd->renderData.text.textColor, level + 1);

  write_indent(file, level + 1);
  fprintf(file, "font_id: %u\n", cmd->renderData.text.fontId);
  write_indent(file, level + 1);
  fprintf(file, "font_size: %u\n", cmd->renderData.text.fontSize);
  write_indent(file, level + 1);
  fprintf(file, "letter_spacing: %u\n", cmd->renderData.text.letterSpacing);
  write_indent(file, level + 1);
  fprintf(file, "line_height: %u\n", cmd->renderData.text.lineHeight);
}

void write_image_yaml(Clay_RenderCommand* cmd, FILE* file, int level) {
  write_indent(file, level);
  fprintf(file, "- type: image\n");
  write_indent(file, level + 1);
  fprintf(file, "bounding_box:\n");
  write_indent(file, level + 2);
  fprintf(file, "x: %.2f\n", cmd->boundingBox.x);
  write_indent(file, level + 2);
  fprintf(file, "y: %.2f\n", cmd->boundingBox.y);
  write_indent(file, level + 2);
  fprintf(file, "width: %.2f\n", cmd->boundingBox.width);
  write_indent(file, level + 2);
  fprintf(file, "height: %.2f\n", cmd->boundingBox.height);

  write_color(file, "background_color", cmd->renderData.image.backgroundColor, level + 1);
  write_corner_radius(file, cmd->renderData.image.cornerRadius, level + 1);

  write_indent(file, level + 1);
  fprintf(file, "source_dimensions:\n");
  write_indent(file, level + 2);
  fprintf(file, "width: %.2f\n", cmd->renderData.image.sourceDimensions.width);
  write_indent(file, level + 2);
  fprintf(file, "height: %.2f\n", cmd->renderData.image.sourceDimensions.height);

  write_indent(file, level + 1);
  fprintf(file, "image_data: \"%p\"\n", cmd->renderData.image.imageData);
}

void write_scissor_start_yaml(Clay_RenderCommand* cmd, FILE* file, int level) {
  write_indent(file, level);
  fprintf(file, "- type: scissor_start\n");
  write_indent(file, level + 1);
  fprintf(file, "bounding_box:\n");
  write_indent(file, level + 2);
  fprintf(file, "x: %.2f\n", cmd->boundingBox.x);
  write_indent(file, level + 2);
  fprintf(file, "y: %.2f\n", cmd->boundingBox.y);
  write_indent(file, level + 2);
  fprintf(file, "width: %.2f\n", cmd->boundingBox.width);
  write_indent(file, level + 2);
  fprintf(file, "height: %.2f\n", cmd->boundingBox.height);
}

void write_scissor_end_yaml(Clay_RenderCommand* cmd, FILE* file, int level) {
  write_indent(file, level);
  fprintf(file, "- type: scissor_end\n");
  write_indent(file, level + 1);
  fprintf(file, "note: end of scissor\n");
}

void reset_yaml_output(const char* filename) {
  FILE* file = fopen(filename, "w");  // "w" truncates the file
  if (file) {
    fputs("# Clay Render Commands Dump\n", file);
    fclose(file);
  }
}

void append_command_to_yaml(const char* filename, Clay_RenderCommand* cmd) {
  FILE* file = fopen(filename, "a");
  if (!file)
    return;

  switch (cmd->commandType) {
    case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
      write_rectangle_yaml(cmd, file, 0);
      break;
    case CLAY_RENDER_COMMAND_TYPE_BORDER:
      write_border_yaml(cmd, file, 0);
      break;
    case CLAY_RENDER_COMMAND_TYPE_TEXT:
      write_text_yaml(cmd, file, 0);
      break;
    case CLAY_RENDER_COMMAND_TYPE_IMAGE:
      write_image_yaml(cmd, file, 0);
      break;
    case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START:
      write_scissor_start_yaml(cmd, file, 0);
      break;
    case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END:
      write_scissor_end_yaml(cmd, file, 0);
      break;
    case CLAY_RENDER_COMMAND_TYPE_CUSTOM:
      break;
    default:
      write_indent(file, 0);
      fprintf(file, "- type: unknown\n");
  }

  fclose(file);
}
