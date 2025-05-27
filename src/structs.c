#include <clay.h>
#include <mruby.h>
#include <mruby/hash.h>
#include <mruby/string.h>
#include <stdlib.h>
#include <string.h>
#include "arena.h"

// --- [CONFIG] ---

mrb_value mrb_get_hash_value(mrb_state* mrb, mrb_value hash, const char* key) {
  mrb_value result = mrb_hash_get(mrb, hash, mrb_symbol_value(mrb_intern_cstr(mrb, key)));
  return result;
}

Clay_Color mrb_cast_clay_color(mrb_state* mrb, mrb_value hash) {
  return (Clay_Color){
      .r = mrb_fixnum(mrb_get_hash_value(mrb, hash, "r")),
      .g = mrb_fixnum(mrb_get_hash_value(mrb, hash, "g")),
      .b = mrb_fixnum(mrb_get_hash_value(mrb, hash, "b")),
      .a = mrb_fixnum(mrb_get_hash_value(mrb, hash, "a")),
  };
}

Clay_ElementId mrb_cast_clay_id(mrb_state* mrb, mrb_value id) {
  const char* cid = mrb_str_to_cstr(mrb, id);
  Clay_String clay_string = {.chars = cid, .length = strlen(cid)};
  return CLAY_SID(clay_string);
}

Clay_Vector2 mrb_cast_clay_vector2(mrb_state* mrb, mrb_value hash) {
  return (Clay_Vector2){.x = mrb_fixnum(mrb_get_hash_value(mrb, hash, "x")),
                        .y = mrb_fixnum(mrb_get_hash_value(mrb, hash, "y"))};
}

Clay_ClipElementConfig mrb_cast_clay_clip_element_config(mrb_state* mrb, mrb_value hash) {
  Clay_ClipElementConfig result = {};
  mrb_value child_offset = mrb_get_hash_value(mrb, hash, "child_offset");
  if (mrb_hash_p(child_offset)) {
    result.childOffset = mrb_cast_clay_vector2(mrb, child_offset);
  }

  mrb_value vertical = mrb_get_hash_value(mrb, hash, "vertical");
  if (!mrb_nil_p(vertical)) {
    result.vertical = mrb_bool(vertical);
  }

  mrb_value horizontal = mrb_get_hash_value(mrb, hash, "horizontal");
  if (!mrb_nil_p(horizontal)) {
    result.horizontal = mrb_bool(horizontal);
  }

  return result;
}

Clay_BorderWidth mrb_cast_clay_border_width(mrb_state* mrb, mrb_value hash) {
  return (Clay_BorderWidth){.left = mrb_fixnum(mrb_get_hash_value(mrb, hash, "left")),
                            .right = mrb_fixnum(mrb_get_hash_value(mrb, hash, "right")),
                            .top = mrb_fixnum(mrb_get_hash_value(mrb, hash, "top")),
                            .bottom = mrb_fixnum(mrb_get_hash_value(mrb, hash, "bottom")),
                            .betweenChildren = mrb_fixnum(mrb_get_hash_value(mrb, hash, "between_children"))};
}

Clay_BorderElementConfig mrb_cast_clay_border_config(mrb_state* mrb, mrb_value hash) {
  return (Clay_BorderElementConfig){
      .color = mrb_cast_clay_color(mrb, mrb_get_hash_value(mrb, hash, "color")),
      .backgroundColor = mrb_cast_clay_color(mrb, mrb_get_hash_value(mrb, hash, "background_color")),
      .width = mrb_cast_clay_border_width(mrb, mrb_get_hash_value(mrb, hash, "width")),
  };
}

Clay_Padding mrb_cast_clay_padding(mrb_state* mrb, mrb_value hash) {
  return (Clay_Padding){
      .left = mrb_fixnum(mrb_get_hash_value(mrb, hash, "left")),
      .right = mrb_fixnum(mrb_get_hash_value(mrb, hash, "left")),
      .top = mrb_fixnum(mrb_get_hash_value(mrb, hash, "top")),
      .bottom = mrb_fixnum(mrb_get_hash_value(mrb, hash, "bottom")),
  };
}

Clay_SizingAxis mrb_cast_clay_sizing_axis(mrb_state* mrb, mrb_value hash) {
  mrb_value percent = mrb_get_hash_value(mrb, hash, "percent");
  Clay__SizingType type = mrb_fixnum(mrb_get_hash_value(mrb, hash, "type"));

  if (mrb_fixnum_p(percent)) {
    return (Clay_SizingAxis){.size = {.percent = mrb_fixnum(percent)}, .type = type};
  } else {
    return (Clay_SizingAxis){.size = {.minMax =
                                          (Clay_SizingMinMax){
                                              .min = mrb_fixnum(mrb_get_hash_value(mrb, hash, "min")),
                                              .max = mrb_fixnum(mrb_get_hash_value(mrb, hash, "max")),
                                          }},
                             .type = type};
  }
}

Clay_Sizing mrb_cast_clay_sizing(mrb_state* mrb, mrb_value hash) {
  Clay_Sizing result = {.width = {}, .height = {}};
  mrb_value width = mrb_get_hash_value(mrb, hash, "width");
  if (mrb_hash_p(width)) {
    result.width = mrb_cast_clay_sizing_axis(mrb, width);
  }

  mrb_value height = mrb_get_hash_value(mrb, hash, "height");
  if (mrb_hash_p(height)) {
    result.height = mrb_cast_clay_sizing_axis(mrb, height);
  }
  return result;
}

Clay_ChildAlignment mrb_cast_clay_child_alignment(mrb_state* mrb, mrb_value hash) {
  return (Clay_ChildAlignment){.x = (Clay_LayoutAlignmentX)mrb_fixnum(mrb_get_hash_value(mrb, hash, "x")),
                               .y = (Clay_LayoutAlignmentY)mrb_fixnum(mrb_get_hash_value(mrb, hash, "y"))};
}

Clay_LayoutConfig mrb_cast_clay_layout_config(mrb_state* mrb, mrb_value hash) {
  Clay_LayoutConfig result = {};

  mrb_value child_gap = mrb_get_hash_value(mrb, hash, "childGap");
  if (mrb_fixnum_p(child_gap)) {
    result.childGap = mrb_fixnum(child_gap);
  }

  mrb_value padding = mrb_get_hash_value(mrb, hash, "padding");
  if (mrb_hash_p(padding)) {
    result.padding = mrb_cast_clay_padding(mrb, padding);
  }

  mrb_value sizing = mrb_get_hash_value(mrb, hash, "sizing");
  if (mrb_hash_p(sizing)) {
    result.sizing = mrb_cast_clay_sizing(mrb, sizing);
  }

  mrb_value alignment = mrb_get_hash_value(mrb, hash, "child_alignment");
  if (mrb_hash_p(alignment)) {
    result.childAlignment = mrb_cast_clay_child_alignment(mrb, alignment);
  }
  mrb_value layout_direction = mrb_get_hash_value(mrb, hash, "layout_direction");
  if (mrb_fixnum_p(layout_direction)) {
    result.layoutDirection = (Clay_LayoutDirection)mrb_fixnum(layout_direction);
  }

  return result;
}

Clay_TextElementConfig mrb_cast_clay_text_config(mrb_state* mrb, mrb_value hash) {
  Clay_TextElementConfig result = {0};

  mrb_value text_alignment = mrb_get_hash_value(mrb, hash, "text_alignment");
  if (mrb_fixnum_p(text_alignment)) {
    result.textAlignment = (Clay_TextAlignment)mrb_fixnum(text_alignment);
  }

  if (mrb_symbol_p(text_alignment)) {
    mrb_sym sym = mrb_symbol(text_alignment);
    if (sym == mrb_intern_lit(mrb, "left")) {
      result.textAlignment = CLAY_TEXT_ALIGN_LEFT;
    } else if (sym == mrb_intern_lit(mrb, "center")) {
      result.textAlignment = CLAY_TEXT_ALIGN_CENTER;
    } else if (sym == mrb_intern_lit(mrb, "right")) {
      result.textAlignment = CLAY_TEXT_ALIGN_RIGHT;
    }
  }

  mrb_value color = mrb_get_hash_value(mrb, hash, "color");
  if (mrb_hash_p(color)) {
    result.textColor = mrb_cast_clay_color(mrb, color);
  }

  mrb_value backgroundColor = mrb_get_hash_value(mrb, hash, "background_color");
  if (mrb_hash_p(backgroundColor)) {
    result.backgroundColor = mrb_cast_clay_color(mrb, backgroundColor);
  }
  return result;
}

typedef struct {
  mrb_state* mrb;
  mrb_value blk;
} clay_elem_ctx_t;

mrb_value mrb_clay_clay_ui(mrb_state* mrb, mrb_value self) {
  Clay_ElementDeclaration config = {};

  mrb_value block = mrb_nil_value();
  mrb_value options = mrb_hash_new(mrb);
  mrb_get_args(mrb, "H|&", &options, &block);

  mrb_value id = mrb_get_hash_value(mrb, options, "id");
  if (mrb_string_p(id)) {
    config.id = mrb_cast_clay_id(mrb, id);
  }

  mrb_value bg_color = mrb_get_hash_value(mrb, options, "background_color");
  if (mrb_hash_p(bg_color)) {
    config.backgroundColor = mrb_cast_clay_color(mrb, bg_color);
  }

  mrb_value layout = mrb_get_hash_value(mrb, options, "layout");
  if (mrb_hash_p(layout)) {
    config.layout = mrb_cast_clay_layout_config(mrb, layout);
  }

  mrb_value border = mrb_get_hash_value(mrb, options, "border");
  if (mrb_hash_p(border)) {
    config.border = mrb_cast_clay_border_config(mrb, border);
  }

  mrb_value clip = mrb_get_hash_value(mrb, options, "clip");
  if (mrb_hash_p(clip)) {
    config.clip = mrb_cast_clay_clip_element_config(mrb, clip);
  }

  clay_elem_ctx_t context = {mrb, block};

  CLAY(config) {
    if (!mrb_nil_p(context.blk)) {
      mrb_yield(context.mrb, context.blk, mrb_nil_value());
    }
  };

  return mrb_nil_value();
}

mrb_value mrb_clay_clay_text(mrb_state* mrb, mrb_value self) {
  const char* cstr;
  mrb_int len;
  mrb_value options;

  mrb_get_args(mrb, "s|H", &cstr, &len, &options);
  if (mrb_nil_p(options)) {
    options = mrb_hash_new(mrb);
  }

  Clay_TextElementConfig config = mrb_cast_clay_text_config(mrb, options);
  const char* ctext = mrb_cstring_arena_strdup(&bindingArena, cstr);
  Clay_String clay_text = {.chars = ctext, .length = len, .isStaticallyAllocated = false};

  CLAY_TEXT(clay_text, CLAY_TEXT_CONFIG(config));

  return mrb_nil_value();
}
