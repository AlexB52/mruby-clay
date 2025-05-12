#ifndef MRUBY_STRING_ARENA_H
#define MRUBY_STRING_ARENA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple arena to manage strdup'd C strings
typedef struct {
  char** items;
  size_t count;
  size_t capacity;
} MRB_CStringArena;

// GLOBALS

MRB_CStringArena bindingArena;

// Initialize an empty arena
static inline void mrb_cstring_arena_init(MRB_CStringArena* arena) {
  arena->items = NULL;
  arena->count = 0;
  arena->capacity = 0;
}

// Free all strings and clear the arena
static inline void mrb_cstring_arena_clear(MRB_CStringArena* arena) {
  if (!arena)
    return;
  for (size_t i = 0; i < arena->count; ++i) {
    free(arena->items[i]);
  }
  free(arena->items);
  arena->items = NULL;
  arena->count = 0;
  arena->capacity = 0;
}

// Add a strdup'd string to the arena
static inline void mrb_cstring_arena_add(MRB_CStringArena* arena, char* str) {
  if (!arena || !str)
    return;
  if (arena->count >= arena->capacity) {
    size_t new_cap = (arena->capacity == 0) ? 8 : arena->capacity * 2;
    char** new_items = realloc(arena->items, sizeof(char*) * new_cap);
    if (!new_items)
      return;  // allocation failed
    arena->items = new_items;
    arena->capacity = new_cap;
  }
  arena->items[arena->count++] = str;
}

// Utility to strdup and track a C string
static inline char* mrb_cstring_arena_strdup(MRB_CStringArena* arena, const char* source) {
  if (!source)
    return NULL;
  char* copy = strdup(source);
  if (copy) {
    mrb_cstring_arena_add(arena, copy);
  }
  return copy;
}

#endif  // MRUBY_STRING_ARENA_H
