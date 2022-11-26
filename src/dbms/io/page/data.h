#pragma once

#include "base.h"

#include <stddef.h>

typedef struct data_header {
  struct base_header base;
  pageoff_t stored_end;
} data_header;

typedef struct data_page {
  struct data_header header;
  uint8_t body[];
} __attribute__((packed)) data_page;

// Bodyoff/pageoff
INLINE_BODYOFF_TO_PAGEOFF(data_page, body, da)
INLINE_PAGEOFF_TO_BODYOFF(data_page, body, da)

PAGE_CONSTRUCT_DEFAULT(data_page, da)
PAGE_DESTRUCT_DEFAULT(data_page, da)
struct data_page *da_construct_init(struct pageoff_t size);

size_t da_space_left(const struct data_page *page);
pageoff_t da_insert_data(struct data_page *page, const void *data, size_t size);
