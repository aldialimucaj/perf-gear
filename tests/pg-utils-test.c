/*
 * File:   pg-utils-test.c
 * Author: garmin
 *
 * Created on Mar 19, 2015, 3:31:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../src/pg-utils.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_pg_build_filename() {
    struct pg_config c = {
        .folder = "/tmp/"
    };

    char *path = "func1/test/hit";

    char *filename = pg_build_filename(path, &c);
    CU_ASSERT_STRING_EQUAL(filename, "/tmp/func1_test_hit.json");
    if (filename) free(filename);

    struct pg_config c1 = {
        .folder = "/tmp"
    };

    char *path1 = "func2/test/time";

    char *filename1 = pg_build_filename(path1, &c1);
    CU_ASSERT_STRING_EQUAL(filename1, "/tmp/func2_test_time.json");
    if (filename1) free(filename1);

}

void test_str_ends_with() {
    char *str0 = NULL;
    char *str0_1 = "";
    char *str0_2 = "/tmp";
    char *str1 = "/tmp/whatever/";
    char *str1_1 = "/tmp/";
    char *str1_2 = "/tmp//";
    char *str1_3 = "/";
    char *str1_4 = "tmp/";

    int result = pg_str_ends_with(str0, "/");
    CU_ASSERT_NOT_EQUAL(result, 1);

    result = pg_str_ends_with(str0_1, "/");
    CU_ASSERT_NOT_EQUAL(result, 1);

    result = pg_str_ends_with(str0_2, "/");
    CU_ASSERT_NOT_EQUAL(result, 1);

    result = pg_str_ends_with(str1, "/");
    CU_ASSERT_EQUAL(result, 1);

    result = pg_str_ends_with(str1_1, "/");
    CU_ASSERT_EQUAL(result, 1);

    result = pg_str_ends_with(str1_2, "/");
    CU_ASSERT_EQUAL(result, 1);

    result = pg_str_ends_with(str1_3, "/");
    CU_ASSERT_EQUAL(result, 1);

    result = pg_str_ends_with(str1_4, "/");
    CU_ASSERT_EQUAL(result, 1);
}

void test_pg_str_replace() {
    char *path = "func1/test/hit";
    char *path_exp = "func1_test_hit";
    char *repl_path = pg_str_replace(path, '/', "_");
    CU_ASSERT_STRING_EQUAL(repl_path, path_exp);
    if (repl_path) free(repl_path);

    char *path1 = "func1/test/hit";
    char *path1_exp = "func1__test__hit";
    char *repl_path1 = pg_str_replace(path, '/', "__");
    CU_ASSERT_STRING_EQUAL(repl_path1, path1_exp);
    if (repl_path) free(repl_path1);
}

void test_pg_mkdir() {
    char *path = "/tmp/pg_tests";
    char *path2 = "/tmp/pg_tests2/";
    pg_mkdir(path);
    pg_mkdir(path2);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("pg-utils-test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_str_ends_with", test_str_ends_with);
    CU_add_test(pSuite, "test_pg_build_filename", test_pg_build_filename);
    CU_add_test(pSuite, "test_pg_str_replace", test_pg_str_replace);
    CU_add_test(pSuite, "test_pg_mkdir", test_pg_mkdir);

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}