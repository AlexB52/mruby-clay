#include <clay.h>
#include <mruby.h>
#include <mruby/hash.h>
#include <mruby/string.h>
#include <string.h>

// --- [CONFIG] ---

mrb_value mrb_get_hash_value(mrb_state* mrb, mrb_value hash, const char* key) {
  mrb_value result =
      mrb_hash_get(mrb, hash, mrb_symbol_value(mrb_intern_cstr(mrb, key)));
  // mrb_p(mrb, mrb_str_new_lit(mrb, "------------"));
  // mrb_p(mrb, mrb_str_new_cstr(mrb, key));
  // mrb_p(mrb, result);
  // mrb_p(mrb, mrb_str_new_lit(mrb, "------------"));
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

Clay_ClipElementConfig mrb_cast_clay_clip_element_config(mrb_state* mrb,
                                                         mrb_value hash) {
  mrb_value child_offset = mrb_get_hash_value(mrb, hash, "childOffset");
  return (Clay_ClipElementConfig){
      .vertical = mrb_bool(mrb_get_hash_value(mrb, hash, "vertical")),
      .horizontal = mrb_bool(mrb_get_hash_value(mrb, hash, "horizontal")),
      .childOffset = mrb_cast_clay_vector2(mrb, child_offset)};
}

Clay_BorderWidth mrb_cast_clay_border_width(mrb_state* mrb, mrb_value hash) {
  return (Clay_BorderWidth){
      .left = mrb_fixnum(mrb_get_hash_value(mrb, hash, "left")),
      .right = mrb_fixnum(mrb_get_hash_value(mrb, hash, "right")),
      .top = mrb_fixnum(mrb_get_hash_value(mrb, hash, "top")),
      .bottom = mrb_fixnum(mrb_get_hash_value(mrb, hash, "bottom")),
      .betweenChildren =
          mrb_fixnum(mrb_get_hash_value(mrb, hash, "between_children"))};
}

Clay_BorderElementConfig mrb_cast_clay_border_config(mrb_state* mrb,
                                                     mrb_value hash) {
  return (Clay_BorderElementConfig){
      .color = mrb_cast_clay_color(mrb, mrb_get_hash_value(mrb, hash, "color")),
      .backgroundColor = mrb_cast_clay_color(
          mrb, mrb_get_hash_value(mrb, hash, "background_color")),
      .width = mrb_cast_clay_border_width(mrb, hash),
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
    return (Clay_SizingAxis){.size = {.percent = mrb_fixnum(percent)},
                             .type = type};
  } else {
    return (Clay_SizingAxis){
        .size = {.minMax =
                     (Clay_SizingMinMax){
                         .min =
                             mrb_fixnum(mrb_get_hash_value(mrb, hash, "min")),
                         .max =
                             mrb_fixnum(mrb_get_hash_value(mrb, hash, "max")),
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

Clay_ChildAlignment mrb_cast_clay_child_alignment(mrb_state* mrb,
                                                  mrb_value hash) {
  return (Clay_ChildAlignment){.x = (Clay_LayoutAlignmentX)mrb_fixnum(
                                   mrb_get_hash_value(mrb, hash, "x")),
                               .y = (Clay_LayoutAlignmentY)mrb_fixnum(
                                   mrb_get_hash_value(mrb, hash, "y"))};
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
  mrb_value layout_direction =
      mrb_get_hash_value(mrb, hash, "layout_direction");
  if (mrb_fixnum_p(layout_direction)) {
    result.layoutDirection = (Clay_LayoutDirection)mrb_fixnum(layout_direction);
  }

  return result;
}

mrb_value mrb_clay_clay_ui(mrb_state* mrb, mrb_value self) {
  Clay_ElementDeclaration config = {};

  mrb_value options = mrb_hash_new(mrb);
  mrb_get_args(mrb, "H", &options);

  mrb_value layout = mrb_get_hash_value(mrb, options, "layout");
  if (mrb_hash_p(layout)) {
    config.layout = mrb_cast_clay_layout_config(mrb, layout);
  }

  mrb_value border = mrb_get_hash_value(mrb, options, "border");
  if (mrb_hash_p(border)) {
    config.border = mrb_cast_clay_border_config(mrb, border);
  }

  mrb_value id = mrb_get_hash_value(mrb, options, "id");
  if (mrb_string_p(id)) {
    config.id = mrb_cast_clay_id(mrb, id);
  }

  mrb_value bg_color = mrb_get_hash_value(mrb, options, "background_color");
  if (mrb_hash_p(bg_color)) {
    config.backgroundColor = mrb_cast_clay_color(mrb, bg_color);
  }

  mrb_value clip = mrb_get_hash_value(mrb, options, "clip");
  if (mrb_hash_p(clip)) {
    config.clip = mrb_cast_clay_clip_element_config(mrb, clip);
  }

  printf("min: %f\n", config.layout.sizing.width.size.minMax.min);
  printf("max: %f\n", config.layout.sizing.width.size.minMax.max);
  printf("type: %d\n", config.layout.sizing.width.type);

  printf("min: %f\n", config.layout.sizing.height.size.minMax.min);
  printf("max: %f\n", config.layout.sizing.height.size.minMax.max);
  printf("type: %d\n", config.layout.sizing.height.type);

  printf("padding left: %d\n", config.layout.padding.left);
  printf("padding top: %d\n", config.layout.padding.top);
  printf("padding right: %d\n", config.layout.padding.right);
  printf("padding bottom: %d\n", config.layout.padding.bottom);

  printf("ID: %s\n", config.id.stringId.chars);

  printf("color R: %f\n", config.backgroundColor.r);
  printf("color G: %f\n", config.backgroundColor.g);
  printf("color B: %f\n", config.backgroundColor.b);
  printf("color A: %f\n", config.backgroundColor.a);

  CLAY(config){};
  return mrb_nil_value();
}
