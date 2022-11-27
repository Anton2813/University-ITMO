#include "gtest/gtest.h"

extern "C" {
#include "../src/dbms/core/dbfile.h"
#include "../src/dbms/core/dbms.h"
#include "../src/dbms/core/meta.h"
#include "../src/dbms/dto/table.h"
#include "../src/dbms/iterator.h"
#include "../src/dbms/page.h"
#include "../src/table.h"
#include "database.h"
#include <database.h>
}


int test(int argc, char **argv) {
  return 0;
}

int test_google(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

int main(int argc, char **argv) {
  // return test(argc, argv);
  return test_google(argc, argv);
}
