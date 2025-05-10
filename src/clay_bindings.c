#define CLAY_IMPLEMENTATION
#include <clay.h>

#define TB_IMPL
#include <termbox2.h>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/hash.h>

// -- [INITIALIZATION] --

mrb_value mrb_clay_min_memory_size(mrb_state* mrb, mrb_value self) {
  return mrb_fixnum_value(Clay_MinMemorySize());
}

// -- [LAYOUT] --

mrb_value mrb_clay_begin_layout() {
  Clay_BeginLayout();
  return mrb_nil_value();
}

mrb_value mrb_clay_color(mrb_state* mrb, Clay_Color color) {
  mrb_value result = mrb_hash_new_capa(mrb, 4);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "r"),
               mrb_float_value(mrb, color.r));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "g"),
               mrb_float_value(mrb, color.g));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "b"),
               mrb_float_value(mrb, color.b));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "a"),
               mrb_float_value(mrb, color.a));
  return result;
}

mrb_value mrb_clay_bounding_box(mrb_state* mrb, Clay_BoundingBox bbox) {
  mrb_value result = mrb_hash_new_capa(mrb, 4);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "x"),
               mrb_float_value(mrb, bbox.x));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "y"),
               mrb_float_value(mrb, bbox.y));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "width"),
               mrb_float_value(mrb, bbox.y));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "height"),
               mrb_float_value(mrb, bbox.y));
  return result;
}

mrb_value mrb_clay_corner_radius(mrb_state* mrb,
                                 Clay_CornerRadius cornerRadius) {
  mrb_value result = mrb_hash_new_capa(mrb, 4);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "top_left"),
               mrb_float_value(mrb, cornerRadius.topLeft));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "top_right"),
               mrb_float_value(mrb, cornerRadius.topRight));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bottom_left"),
               mrb_float_value(mrb, cornerRadius.bottomLeft));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bottom_right"),
               mrb_float_value(mrb, cornerRadius.bottomRight));
  return result;
}

mrb_value mrb_clay_border_width(mrb_state* mrb, Clay_BorderWidth borderWidth) {
  mrb_value result = mrb_hash_new_capa(mrb, 5);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "left"),
               mrb_fixnum_value(borderWidth.left));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "right"),
               mrb_fixnum_value(borderWidth.right));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "top"),
               mrb_fixnum_value(borderWidth.top));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "bottom"),
               mrb_fixnum_value(borderWidth.bottom));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "between_children"),
               mrb_fixnum_value(borderWidth.betweenChildren));
  return result;
}

mrb_value mrb_clay_rectangle_render_data(mrb_state* mrb,
                                         Clay_RectangleRenderData rectData) {
  mrb_value result = mrb_hash_new_capa(mrb, 2);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "background_color"),
               mrb_clay_color(mrb, rectData.backgroundColor));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "corner_radius"),
               mrb_clay_corner_radius(mrb, rectData.cornerRadius));
  return result;
}

mrb_value mrb_clay_text_render_data(mrb_state* mrb,
                                    Clay_TextRenderData textData) {
  mrb_value result = mrb_hash_new_capa(mrb, 7);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "text"),
               mrb_str_new(mrb, textData.stringContents.chars,
                           textData.stringContents.length));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "color"),
               mrb_clay_color(mrb, textData.textColor));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "background_color"),
               mrb_clay_color(mrb, textData.backgroundColor));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "font_id"),
               mrb_int_value(mrb, textData.fontId));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "font_size"),
               mrb_int_value(mrb, textData.fontSize));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "letter_spacing"),
               mrb_int_value(mrb, textData.letterSpacing));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "line_height"),
               mrb_int_value(mrb, textData.lineHeight));

  return result;
}

mrb_value mrb_clay_border_render_data(mrb_state* mrb,
                                      Clay_BorderRenderData borderData) {
  mrb_value result = mrb_hash_new_capa(mrb, 4);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "color"),
               mrb_clay_color(mrb, borderData.color));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "background_color"),
               mrb_clay_color(mrb, borderData.backgroundColor));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "corner_radius"),
               mrb_clay_corner_radius(mrb, borderData.cornerRadius));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "width"),
               mrb_clay_border_width(mrb, borderData.width));
  return result;
}

mrb_value mrb_clay_clip_render_data(mrb_state* mrb,
                                    Clay_ClipRenderData clipData) {
  mrb_value result = mrb_hash_new_capa(mrb, 2);
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "horizontal"),
               mrb_bool_value(clipData.horizontal));
  mrb_hash_set(mrb, result, mrb_str_new_lit(mrb, "vertical"),
               mrb_bool_value(clipData.vertical));
  return result;
}

mrb_value mrb_clay_end_layout(mrb_state* mrb, mrb_value self) {
  Clay_RenderCommandArray clay_commands = Clay_EndLayout();
  mrb_value commands = mrb_ary_new_capa(mrb, clay_commands.length);

  for (int i = 0; i < clay_commands.length; ++i) {
    Clay_RenderCommand* renderCommand = &clay_commands.internalArray[i];
    switch (renderCommand->commandType) {
      case CLAY_RENDER_COMMAND_TYPE_RECTANGLE: {
        mrb_ary_set(mrb, commands, i,
                    mrb_clay_rectangle_render_data(
                        mrb, renderCommand->renderData.rectangle));
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_BORDER: {
        mrb_ary_set(
            mrb, commands, i,
            mrb_clay_border_render_data(mrb, renderCommand->renderData.border));
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_TEXT: {
        mrb_ary_set(
            mrb, commands, i,
            mrb_clay_text_render_data(mrb, renderCommand->renderData.text));
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START:
      case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END: {
        mrb_ary_set(mrb, commands, i,
                    mrb_clay_bounding_box(mrb, renderCommand->boundingBox));
        break;
      }
      case CLAY_RENDER_COMMAND_TYPE_IMAGE:
      case CLAY_RENDER_COMMAND_TYPE_CUSTOM:
      case CLAY_RENDER_COMMAND_TYPE_NONE:
        break;
    }
  }

  return commands;
}

// -- [MEASURE TEXT] --

static mrb_state* CLAY_mrb = NULL;
static mrb_value CLAY_measure_proc = {0};

static Clay_Dimensions measure_text_callback(Clay_StringSlice text,
                                             Clay_TextElementConfig* config,
                                             void* user_data) {
  mrb_value textConfig = mrb_hash_new_capa(CLAY_mrb, 2);
  mrb_hash_set(CLAY_mrb, textConfig,
               mrb_symbol_value(mrb_intern_lit(CLAY_mrb, "font_size")),
               mrb_fixnum_value(config->fontSize));
  mrb_hash_set(CLAY_mrb, textConfig,
               mrb_symbol_value(mrb_intern_lit(CLAY_mrb, "line_height")),
               mrb_fixnum_value(config->lineHeight));

  // build Ruby args: [ text_str, config_hash ]
  mrb_value args = mrb_ary_new_capa(CLAY_mrb, 2);
  mrb_ary_set(CLAY_mrb, args, 0,
              mrb_str_new(CLAY_mrb, text.chars, text.length));
  mrb_ary_set(CLAY_mrb, args, 1, textConfig);

  // returns [width, height]
  mrb_value ret = mrb_yield(CLAY_mrb, CLAY_measure_proc, args);

  // extract width & height
  mrb_value width = mrb_ary_ref(CLAY_mrb, ret, 0);
  mrb_value height = mrb_ary_ref(CLAY_mrb, ret, 1);

  return (Clay_Dimensions){mrb_float(width), mrb_float(height)};
}

static mrb_value mrb_clay_set_measure_text(mrb_state* mrb, mrb_value self) {
  mrb_value blk;
  mrb_get_args(mrb, "&", &blk);
  if (mrb_nil_p(blk)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Clay.measure_text requires a block");
  }

  // GLOBAL variables used in measure_text_callback
  CLAY_mrb = mrb;
  CLAY_measure_proc = blk;

  Clay_SetMeasureTextFunction(measure_text_callback, NULL);

  return mrb_nil_value();
}

void mrb_mruby_clay_gem_init(mrb_state* mrb) {
  struct RClass* module = mrb_define_module(mrb, "clay");
  mrb_define_module_function(mrb, module, "measure_text",
                             mrb_clay_set_measure_text, MRB_ARGS_BLOCK());
  mrb_define_module_function(mrb, module, "begin_layout", mrb_clay_begin_layout,
                             MRB_ARGS_NONE());
  mrb_define_module_function(mrb, module, "end_layout", mrb_clay_end_layout,
                             MRB_ARGS_NONE());
  mrb_define_module_function(mrb, module, "min_memory_size",
                             mrb_clay_min_memory_size, MRB_ARGS_NONE());
}

void mrb_mruby_clay_gem_final(mrb_state* mrb) { /* nothing to clean up */ }
