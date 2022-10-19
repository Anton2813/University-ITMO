#pragma once

#include "sections/base.h"
#include "sections/base_util.h"

extern sectoff_t DATABASE_SECTION_SIZE;

// DatabaseSection
struct DSHeader {
	struct BaseSection base;
	fileoff_t next;
	fileoff_t previous;
	/* Non-inclusive body offset */
	bodyoff_t index_last;
	/* From start to end */
	bodyoff_t typle_start;
};

struct DatabaseSection {
	struct DSHeader header;
	char body[];
};

struct DSIndex {
	bodyoff_t start;
	bodyoff_t end;
	bool is_cleared;
};

enum TableColumnTypes {
	COLUMN_TYPE_INT = 0,
	COLUMN_TYPE_FLOAT = 1,
	COLUMN_TYPE_STRING = 2,
	COLUMN_TYPE_BOOL = 3,
};

// DSTyple
struct DSTHeader {
	fileoff_t fileoff;
	size_t cols;
	struct SSO name;
};

struct DSTColumnLimits {
	bool is_null;
	bool is_unique;
};

struct DSTColumn {
	/* TableColumnType */
	int8_t type;
	struct DSTColumnLimits limits;
	struct SSO name;
};

struct DSTyple {
	struct DSTHeader header;
	struct DSTColumn columns[];
};

// DSTyple in RAM
struct DSTHeaderRAM {
	fileoff_t fileoff;// offset to table
	size_t cols;

	bool changed;// does name in file is pointed

	bool is_inline;
	SOPointer so;
	char ssize[SSO_STRING_SIZE];
	char *name;
};

// linked list
struct DSTColumnRAM {
	struct DSTColumnRAM *next;

	int8_t type; /* TableColumnType */
	struct DSTColumnLimits limits;

	bool changed;// does name in file is pointed

	bool is_inline;
	SOPointer so;
	char ssize[SSO_STRING_SIZE];
	char *name;
};

struct DSTypleRAM {
	struct DSTHeaderRAM header;
	struct DSTColumnRAM *columns;
};

// HELPER
struct DatabaseSectionWr {// wrapper
	fileoff_t fileoff;
	struct DatabaseSection *ds;// linked list
};

struct DSTypleRAMWr {
	fileoff_t ifileoff;// section where index is located
	bodyoff_t ibodyoff;// offset to index
	struct DSTypleRAM *typle;
};

// Typedefs
my_defstruct(DSHeader);
my_defstruct(DatabaseSection);
my_defstruct(DatabaseSectionWr);

my_defstruct(DSIndex);

my_defstruct(DSTHeader);
my_defstruct(DSTColumnLimits);
my_defstruct(DSTColumn);
my_defstruct(DSTyple);

my_defstruct(DSTIHeader);
my_defstruct(DSTIColumn);

my_defstruct(DSTHeaderRAM);
my_defstruct(DSTColumnRAM);
my_defstruct(DSTypleRAM);
my_defstruct(DSTypleRAMWr);

// Function declarations
size_t ds_get_space_left(const DatabaseSection *dbs);
size_t ds_get_body_size(const DatabaseSection *dbs);
bodyoff_t ds_get_bodyoff(sectoff_t sectoff);
sectoff_t ds_get_sectoff(bodyoff_t bodyoff);

// DatabaseSection specific
DatabaseSectionWr ds_create(Database *db, DatabaseSection *prev, fileoff_t prev_pos);
void ds_alter(Database *database, const fileoff_t fileoff, const DatabaseSection *ds);
void ds_alter_bodyoff(Database *database, const void *data, fileoff_t fileoff,
											bodyoff_t offset, size_t size);
void ds_alter_sync_bodyoff(Database *database, DatabaseSection *ds, const void *data,
													 fileoff_t fileoff, bodyoff_t offset, size_t size);
void ds_drop(Database *database, fileoff_t pos);

DatabaseSectionWr ds_load_next(Database *database, const DatabaseSection *current);
DatabaseSection *ds_load(Database *database, fileoff_t fileoff);
void ds_unload(DatabaseSection **ds);

// DatabaseSection Typle and Index specific
DSTypleRAM *ds_typle_ram_load(Database *db, DatabaseSection *section,
													 const DSIndex *index);
void ds_typle_ram_unload(DSTypleRAM **const ram_ptr);

DSTypleRAM ds_typle_ram_create(char *name, size_t nsize, DSTColumnRAM *column,
															 size_t cols);
DSTColumnRAM ds_typle_column_ram_create(int8_t type, DSTColumnLimits limits, char *name,
																				size_t size);

DSTyple *ds_typle_ram_to_typle(const DSTypleRAM *typle);

DSTypleRAMWr ds_table_select(Database *database, const char *name);
DSTypleRAMWr ds_table_create(Database *database, DSTypleRAM *wrapper);
DSTypleRAMWr ds_table_drop(Database *database, const char *name);
