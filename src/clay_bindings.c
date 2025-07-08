#define CLAY_IMPLEMENTATION
#include <clay.h>
#include "helpers.c"
#include "structs.c"

// #define TB_IMPL
#include <termbox2.h>

#include <locale.h>
#include <mruby.h>
#include <mruby/array.h>
#include <mruby/hash.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>

// -- [GLOBALS] --

// -- [HELPERS] --

// -- [INITIALIZATION] --

void HandleClayErrors(Clay_ErrorData errorData) {
  mrb_state* mrb = (mrb_state*)errorData.userData;
  mrb_value error_proc = mrb_gv_get(mrb, mrb_intern_lit(mrb, "$__clay_error_proc"));

  mrb_value error = mrb_hash_new_capa(mrb, 2);
  mrb_sym error_type;

  switch (errorData.errorType) {
    case CLAY_ERROR_TYPE_TEXT_MEASUREMENT_FUNCTION_NOT_PROVIDED: {
      error_type = mrb_intern_lit(mrb, "text_measurement_function_not_provided");
      break;
    }
    case CLAY_ERROR_TYPE_ARENA_CAPACITY_EXCEEDED: {
      error_type = mrb_intern_lit(mrb, "arena_capacity_exceeded");
      break;
    }
    case CLAY_ERROR_TYPE_ELEMENTS_CAPACITY_EXCEEDED: {
      error_type = mrb_intern_lit(mrb, "elements_capacity_exceeded");
      break;
    }
    case CLAY_ERROR_TYPE_TEXT_MEASUREMENT_CAPACITY_EXCEEDED: {
      error_type = mrb_intern_lit(mrb, "text_measurement_capacity_exceeded");
    } break;
    case CLAY_ERROR_TYPE_DUPLICATE_ID: {
      error_type = mrb_intern_lit(mrb, "duplicate_id");
      break;
    }
    case CLAY_ERROR_TYPE_FLOATING_CONTAINER_PARENT_NOT_FOUND: {
      error_type = mrb_intern_lit(mrb, "floating_container_parent_not_found");
    } break;
    case CLAY_ERROR_TYPE_PERCENTAGE_OVER_1: {
      error_type = mrb_intern_lit(mrb, "percentage_over_1");
      break;
    }
    case CLAY_ERROR_TYPE_INTERNAL_ERROR: {
      error_type = mrb_intern_lit(mrb, "internal_error");
      break;
    }
  }

  mrb_hash_set(mrb, error, mrb_str_new_lit(mrb, "message"),
               mrb_str_new(mrb, errorData.errorText.chars, errorData.errorText.length));

  mrb_hash_set(mrb, error, mrb_str_new_lit(mrb, "type"), mrb_symbol_value(error_type));
  mrb_yield(mrb, error_proc, error);
}

mrb_value mrb_clay_initialize(mrb_state* mrb, mrb_value self) {
  setlocale(LC_ALL, "");

  // Taking some shortcuts here for now by initializing the minimum arena
  mrb_int width, height;
  mrb_value error_blk;
  mrb_get_args(mrb, "ii&", &width, &height, &error_blk);

  // Store in global Ruby var to protect from GC
  mrb_gv_set(mrb, mrb_intern_lit(mrb, "$__clay_error_proc"), error_blk);

  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

  Clay_Initialize(arena, (Clay_Dimensions){width, height}, (Clay_ErrorHandler){HandleClayErrors, (void*)mrb});
  mrb_cstring_arena_init(&bindingArena);

  return mrb_nil_value();
}

mrb_value mrb_clay_min_memory_size(mrb_state* mrb, mrb_value self) {
  return mrb_fixnum_value(Clay_MinMemorySize());
}

mrb_value mrb_clay_dimensions(mrb_state* mrb, Clay_Dimensions dimensions) {
  mrb_value result = mrb_hash_new_capa(mrb, 2);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "width"), mrb_fixnum_value(dimensions.width));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "height"), mrb_fixnum_value(dimensions.height));
  return result;
}

mrb_value mrb_clay_set_layout_dimensions(mrb_state* mrb, mrb_value self) {
  mrb_int width, height;
  mrb_get_args(mrb, "ii", &width, &height);
  Clay_Dimensions dimensions = {.width = width, .height = height};
  Clay_SetLayoutDimensions(dimensions);
  return mrb_clay_dimensions(mrb, dimensions);
}

// -- [LAYOUT] --

mrb_value mrb_clay_begin_layout() {
  Clay_BeginLayout();
  return mrb_nil_value();
}

mrb_value mrb_clay_color(mrb_state* mrb, Clay_Color color) {
  mrb_value result = mrb_hash_new_capa(mrb, 4);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "r"), mrb_float_value(mrb, round_to_2_decimal(color.r)));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "g"), mrb_float_value(mrb, round_to_2_decimal(color.g)));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "b"), mrb_float_value(mrb, round_to_2_decimal(color.b)));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "a"), mrb_float_value(mrb, round_to_2_decimal(color.a)));
  return result;
}

mrb_value mrb_clay_bounding_box(mrb_state* mrb, Clay_BoundingBox bbox) {
  mrb_value result = mrb_hash_new_capa(mrb, 4);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "x"), mrb_float_value(mrb, bbox.x));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "y"), mrb_float_value(mrb, bbox.y));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "width"), mrb_float_value(mrb, bbox.width));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "height"), mrb_float_value(mrb, bbox.height));
  return result;
}

mrb_value mrb_clay_corner_radius(mrb_state* mrb, Clay_CornerRadius cornerRadius) {
  mrb_value result = mrb_hash_new_capa(mrb, 4);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "top_left"), mrb_float_value(mrb, cornerRadius.topLeft));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "top_right"), mrb_float_value(mrb, cornerRadius.topRight));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bottom_left"), mrb_float_value(mrb, cornerRadius.bottomLeft));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bottom_right"), mrb_float_value(mrb, cornerRadius.bottomRight));
  return result;
}

mrb_value mrb_clay_border_width(mrb_state* mrb, Clay_BorderWidth borderWidth) {
  mrb_value result = mrb_hash_new_capa(mrb, 5);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "left"), mrb_fixnum_value(borderWidth.left));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "right"), mrb_fixnum_value(borderWidth.right));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "top"), mrb_fixnum_value(borderWidth.top));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bottom"), mrb_fixnum_value(borderWidth.bottom));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "between_children"), mrb_fixnum_value(borderWidth.betweenChildren));
  return result;
}

mrb_value mrb_clay_rectangle_render_data(mrb_state* mrb, Clay_RectangleRenderData rectData, Clay_BoundingBox bbox) {
  mrb_value result = mrb_hash_new_capa(mrb, 4);

  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "type"), mrb_symbol_value(mrb_intern_lit(mrb, "rectangle")));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bounding_box"), mrb_clay_bounding_box(mrb, bbox));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "background_color"), mrb_clay_color(mrb, rectData.backgroundColor));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "corner_radius"), mrb_clay_corner_radius(mrb, rectData.cornerRadius));
  return result;
}

mrb_value mrb_clay_text_render_data(mrb_state* mrb, Clay_TextRenderData textData, Clay_BoundingBox bbox) {
  mrb_value result = mrb_hash_new_capa(mrb, 5);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "type"), mrb_symbol_value(mrb_intern_lit(mrb, "text")));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bounding_box"), mrb_clay_bounding_box(mrb, bbox));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "text"),
               mrb_str_new(mrb, textData.stringContents.chars, textData.stringContents.length));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "text_color"), mrb_clay_color(mrb, textData.textColor));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "background_color"), mrb_clay_color(mrb, textData.backgroundColor));
  return result;
}

mrb_value mrb_clay_border_render_data(mrb_state* mrb, Clay_BorderRenderData borderData, Clay_BoundingBox bbox) {
  mrb_value result = mrb_hash_new_capa(mrb, 6);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "type"), mrb_symbol_value(mrb_intern_lit(mrb, "border")));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bounding_box"), mrb_clay_bounding_box(mrb, bbox));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "color"), mrb_clay_color(mrb, borderData.color));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "background_color"), mrb_clay_color(mrb, borderData.backgroundColor));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "corner_radius"),
               mrb_clay_corner_radius(mrb, borderData.cornerRadius));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "width"), mrb_clay_border_width(mrb, borderData.width));
  return result;
}

mrb_value mrb_clay_clip_start_render_data(mrb_state* mrb, Clay_BoundingBox bbox) {
  mrb_value result = mrb_hash_new_capa(mrb, 2);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "type"), mrb_symbol_value(mrb_intern_lit(mrb, "scissor_start")));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bounding_box"), mrb_clay_bounding_box(mrb, bbox));
  return result;
}

mrb_value mrb_clay_clip_end_render_data(mrb_state* mrb, Clay_BoundingBox bbox) {
  mrb_value result = mrb_hash_new_capa(mrb, 2);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "type"), mrb_symbol_value(mrb_intern_lit(mrb, "scissor_end")));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bounding_box"), mrb_clay_bounding_box(mrb, bbox));
  return result;
}

mrb_value mrb_clay_end_layout(mrb_state* mrb, mrb_value self) {
  Clay_RenderCommandArray clay_commands = Clay_EndLayout();
  mrb_value commands = mrb_ary_new_capa(mrb, clay_commands.length);

  for (int i = 0; i < clay_commands.length; ++i) {
    Clay_RenderCommand* renderCommand = &clay_commands.internalArray[i];
    switch (renderCommand->commandType) {
      case CLAY_RENDER_COMMAND_TYPE_RECTANGLE: {
        mrb_ary_set(
            mrb, commands, i,
            mrb_clay_rectangle_render_data(mrb, renderCommand->renderData.rectangle, renderCommand->boundingBox));
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_BORDER: {
        mrb_ary_set(mrb, commands, i,
                    mrb_clay_border_render_data(mrb, renderCommand->renderData.border, renderCommand->boundingBox));
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_TEXT: {
        mrb_ary_set(mrb, commands, i,
                    mrb_clay_text_render_data(mrb, renderCommand->renderData.text, renderCommand->boundingBox));
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START: {
        mrb_ary_set(mrb, commands, i, mrb_clay_clip_start_render_data(mrb, renderCommand->boundingBox));
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END: {
        mrb_ary_set(mrb, commands, i, mrb_clay_clip_end_render_data(mrb, renderCommand->boundingBox));
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_IMAGE:
      case CLAY_RENDER_COMMAND_TYPE_CUSTOM:
      case CLAY_RENDER_COMMAND_TYPE_NONE:
        break;
    }
  }
  mrb_cstring_arena_clear(&bindingArena);
  return commands;
}

// -- [MEASURE TEXT] --

static Clay_Dimensions measure_text_callback(Clay_StringSlice text, Clay_TextElementConfig* config, void* user_data) {
  mrb_state* mrb = (mrb_state*)user_data;

  mrb_value textConfig = mrb_hash_new_capa(mrb, 2);
  mrb_hash_set(mrb, textConfig, mrb_symbol_value(mrb_intern_lit(mrb, "font_size")), mrb_fixnum_value(config->fontSize));
  mrb_hash_set(mrb, textConfig, mrb_symbol_value(mrb_intern_lit(mrb, "line_height")),
               mrb_fixnum_value(config->lineHeight));

  // build Ruby args: [ text_str, config_hash ]
  mrb_value args = mrb_ary_new_capa(mrb, 2);
  mrb_ary_set(mrb, args, 0, mrb_str_new(mrb, text.chars, text.length));
  mrb_ary_set(mrb, args, 1, textConfig);

  // returns [width, height]
  mrb_value block = mrb_gv_get(mrb, mrb_intern_lit(mrb, "$__clay_measure_proc"));
  mrb_value ret = mrb_yield(mrb, block, args);

  // extract width & height
  mrb_value width = mrb_ary_ref(mrb, ret, 0);
  mrb_value height = mrb_ary_ref(mrb, ret, 1);

  // return (Clay_Dimensions){.width = (float)text.length, .height = 1.0f};

  return (Clay_Dimensions){.width = mrb_float(mrb_to_float(mrb, width)),
                           .height = mrb_float(mrb_to_float(mrb, height))};
}

static mrb_value mrb_clay_set_measure_text(mrb_state* mrb, mrb_value self) {
  mrb_value blk;
  mrb_get_args(mrb, "&", &blk);

  if (!mrb_proc_p(blk)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Clay.measure_text requires a block");
  }

  // Store in global Ruby var to protect from GC
  mrb_gv_set(mrb, mrb_intern_lit(mrb, "$__clay_measure_proc"), blk);

  Clay_SetMeasureTextFunction(measure_text_callback, (void*)mrb);

  return mrb_nil_value();
}

mrb_value mrb_clay_get_element_data(mrb_state* mrb, mrb_value self) {
  mrb_value id;
  mrb_get_args(mrb, "o", &id);

  if (mrb_symbol_p(id)) {
    id = mrb_sym2str(mrb, mrb_symbol(id));
  } else if (!mrb_string_p(id)) {
    return mrb_nil_value();
  }

  Clay_String cid = mrb_cast_clay_string(mrb, id);
  Clay_ElementData data = Clay_GetElementData(Clay_GetElementId(cid));

  if (data.found) {
    return mrb_clay_bounding_box(mrb, data.boundingBox);
  } else {
    return mrb_nil_value();
  }
}

void mrb_mruby_clay_gem_init(mrb_state* mrb) {
  struct RClass* module = mrb_define_module(mrb, "Clay");
  mrb_define_module_function(mrb, module, "measure_text", mrb_clay_set_measure_text, MRB_ARGS_BLOCK());
  mrb_define_module_function(mrb, module, "begin_layout", mrb_clay_begin_layout, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, module, "end_layout", mrb_clay_end_layout, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, module, "min_memory_size", mrb_clay_min_memory_size, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, module, "set_layout_dimensions", mrb_clay_set_layout_dimensions, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, module, "init", mrb_clay_initialize, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, module, "ui", mrb_clay_clay_ui, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, module, "text", mrb_clay_clay_text, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, module, "get_element_data", mrb_clay_get_element_data, MRB_ARGS_REQ(1));
}

void mrb_mruby_clay_gem_final(mrb_state* mrb) { /* nothing to clean up */ }
