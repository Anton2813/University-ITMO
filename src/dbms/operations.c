#pragma once

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "converters/table.h"
#include "core/meta.h"
#include "page.h"
#include "sso.h"

// Just insert table, no checks for existance
void dbms_insert_table(const struct dto_table *dto_table, struct dbms *dbms) {
  // Convert dto to entity
  dpt_header header = {};
  header.cols = dto_table_columns(dto_table);
  header.fileoff = get_fileoff_t(0);// TODO: add table page
  dbms_insert_sso(&header.sso, dto_table->name, dbms);
  // construct dptyple
  size_t typle_size = dp_typle_size(header.cols);
  dp_typle *typle = malloc(typle_size);
  typle->header = header;

  dto_table_column *dto_col = dto_table->first;
  dpt_column col = {};
  for (size_t i = 0; i < typle->header.cols; ++i) {
    // convert dto column to entity
    table_column_limits_to_page(&dto_col->lims, &col.limits);
    col.type = table_column_type_to_page(dto_col->type);
    dbms_insert_sso(&col.sso, dto_col->name, dbms);

    typle->columns[i] = col;
    dto_col = dto_col->next;
  }
  // select last page
  database_page *page = dbms_dp_select(dbms, dbms->meta->dp.last);
  if (dp_insert_typle(page, typle).bytes == 0) {
    dp_destruct(&page);

    pageoff_t size =
        dp_bodyoff_to_pageoff(get_bodyoff_t(typle_size + sizeof(page_index)));
    fileoff_t page_loc = dbms_dp_create(dbms, size, &page);

    assert(dp_insert_typle(page, typle).bytes > 0);
    dbms_dp_close(&page, page_loc, dbms);
  }
}
