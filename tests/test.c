#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"
#include <CUnit/Automated.h>
#include "test.h"

#include "test_http.h"
#include "../webserver/file.h"

static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
    if (NULL == (temp_file = fopen("./temp.txt", "w+")))
        return -1;
    else
        return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    if (0 != fclose(temp_file))
        return -1;
    else {
        remove("./temp.txt");
        temp_file = NULL;
        return 0;
    }
}

FILE *get_temp_file(void) {
    return temp_file;
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_ADD_TEST(pSuite, test_rewrite_target)) ||
            (NULL == CU_ADD_TEST(pSuite, test_get_date_http_format)) ||
            (NULL == CU_ADD_TEST(pSuite, test_send_status)) ||
            (NULL == CU_ADD_TEST(pSuite, test_parse_http_request))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    if (CU_get_number_of_tests_failed() > 0)
        exit(EXIT_FAILURE);

    CU_cleanup_registry();

    exit(EXIT_SUCCESS);
}
