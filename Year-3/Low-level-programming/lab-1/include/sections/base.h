#pragma once

#include "../database.h"

#include <inttypes.h>
#include <stdbool.h>

struct BaseSection {
	uint8_t type;
	uint32_t size;
};

struct SOPointer {
	fileoff_t sect_address;
	sectoff_t offset;
};

enum SectionTypes {
	TYPE_UNKNOWN,
	TYPE_DATABASE,
	TYPE_HASHTABLE,
	TYPE_BACKET,
	TYPE_PAGE,
	TYPE_DATA,
	TYPE_TABLE,
	TYPE_TMP,
	TYPE_DUMPED,
};

my_defstruct(BaseSection);
my_defstruct(SOPointer);

// RAM
void *section_malloc(const sectoff_t sect_size);
void *section_load(const Database *database, const fileoff_t offset);
void section_unload(void **section);

// FILE or FILE + RAM(sync)
fileoff_t section_create(Database *database, const BaseSection *section);

bool section_alter(Database *database, const fileoff_t fileoff,
									 const BaseSection *sect);
bool section_alter_sectoff(Database *database, const fileoff_t fileoff,
													 const sectoff_t offset, const void *data, const size_t size);
bool section_alter_sync_sectoff(Database *database, const fileoff_t fileoff,
																const sectoff_t offset, BaseSection *base,
																const void *data, const size_t size);

bool section_sync_drop(Database *database, const fileoff_t fileoff,
											 BaseSection *section);
