#include <gtest/gtest.h>

#include "util/printers.hpp"

extern "C" {
#include "../src/dbms/dto/dto_table.h"
#include "../src/table.h"
#include "database.h"
}

TEST(table, create_and_drop) {
  dbms *dbms = dbms_create("tmp/db.bin");

  dto_table *table = dto_table_construct((char *)"table1");
  dto_table_add_column(table, (char *)"column1", DTO_COLUMN_STRING,
                       (dto_table_column_limits){.is_null = true, .is_unique = false});
  dto_table_add_column(table, (char *)"column2", DTO_COLUMN_INT,
                       (dto_table_column_limits){.is_null = false, .is_unique = true});
  EXPECT_EQ(table_create(dbms, table), true);
  EXPECT_EQ(table_create(dbms, table), false);
  EXPECT_EQ(table_drop(dbms, table), true);

  dto_table_destruct(&table);
  dbms_close(&dbms);
  std::remove("tmp/db.bin");
}

TEST(table, list_inserted) {
  dbms *dbms = dbms_create("tmp/db.bin");

  dto_table *table = dto_table_construct((char *)"table 1");
  dto_table_add_column(table, (char *)"column1", DTO_COLUMN_STRING,
                       (dto_table_column_limits){.is_null = true, .is_unique = false});
  dto_table_add_column(table, (char *)"column2", DTO_COLUMN_INT,
                       (dto_table_column_limits){.is_null = false, .is_unique = true});
  EXPECT_EQ(table_create(dbms, table), true);
  free(table->name);
  table->name = strdup("table 2");
  EXPECT_EQ(table_create(dbms, table), true);
  free(table->name);
  table->name = strdup("table 3");
  EXPECT_EQ(table_create(dbms, table), true);
  free(table->name);
  table->name = strdup("table 4");
  EXPECT_EQ(table_create(dbms, table), true);

  dp_iter *iter = dp_iter_construct(dbms);
  dp_typle *typle = dp_iter_get(iter);
  while (typle) {
    // print_database_typle(typle);
    dp_iter_next(iter);
    typle = dp_iter_get(iter);
  }
  dp_iter_destruct(&iter);

  dto_table_destruct(&table);
  dbms_close(&dbms);

  std::remove("tmp/db.bin");
}
