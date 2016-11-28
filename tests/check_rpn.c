#include <check.h>
#include <stdlib.h>
#include "../src/rpn.h"

START_TEST(test_infix_to_postfix_empty_string)
{
    ck_assert_str_eq(infix_to_postfix(""), "");
}
END_TEST

Suite* rpn_suite(void)
{
    Suite* s;
    TCase* tc_infix_to_postfix;

    s = suite_create("RPN");

    tc_infix_to_postfix = tcase_create("Infix To Postfix");

    tcase_add_test(tc_infix_to_postfix, test_infix_to_postfix_empty_string);
    suite_add_tcase(s, tc_infix_to_postfix);

    return s;
}

int main(void)
{
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = rpn_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}