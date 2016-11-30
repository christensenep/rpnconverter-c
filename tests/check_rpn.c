#include <check.h>
#include <stdlib.h>
#include "../src/rpn.h"

START_TEST(i2p_should_convert_empty_string_to_empty_string)
{
    char* output = infix_to_postfix("");
    ck_assert_str_eq(output, "");
    free(output);
}
END_TEST

START_TEST(i2p_should_convert_single_operand)
{
    char* output = infix_to_postfix("a");
    ck_assert_str_eq(output, "a");
    free(output);
}
END_TEST

START_TEST(i2p_should_convert_single_operator)
{
    char* output = infix_to_postfix("a+b");
    ck_assert_str_eq(output, "ab+");
    free(output);
}
END_TEST

START_TEST(i2p_should_convert_chain_of_equal_precedence_operators)
{
    char* output = infix_to_postfix("a+b+c");
    ck_assert_str_eq(output, "ab+c+");
    free(output);
}
END_TEST

START_TEST(i2p_should_recognize_all_operators)
{
    char* output = infix_to_postfix("a+b-c*d/e^f");
    ck_assert_str_eq(output, "abcdef^/*-+");
    free(output);
}
END_TEST

START_TEST(i2p_should_recognize_operator_precedence)
{
    char* output = infix_to_postfix("a-b+c^d/e*f");
    ck_assert_str_eq(output, "ab-cd^e/f*+");
    free(output);
}
END_TEST

START_TEST(i2p_should_recognize_a_single_parenthetical_expression)
{
    char* output = infix_to_postfix("a-(b+c^d)/e*f");
    ck_assert_str_eq(output, "abcd^+e/f*-");
    free(output);
}
END_TEST

START_TEST(i2p_should_recognize_multiple_non_nested_parenthetical_groupings)
{
    char* output = infix_to_postfix("a-(b+c^d)/(e*f)");
    ck_assert_str_eq(output, "abcd^+ef*/-");
    free(output);
}
END_TEST

START_TEST(i2p_should_recognize_nested_parenthetical_groupings)
{
    char* output = infix_to_postfix("a-((b+c)^(d/e))*f");
    ck_assert_str_eq(output, "abc+de/^f*-");
    free(output);
}
END_TEST

START_TEST(i2p_should_handle_provided_examples)
{
    char* output1 = infix_to_postfix("a+b-c");
    char* output2 = infix_to_postfix("(a+b)-c");
    char* output3 = infix_to_postfix("l/m^n*o-p");
    char* output4 = infix_to_postfix("((l/(m^n))*o)-p");
    char* output5 = infix_to_postfix("((v/w)^x)*(y-z)");

    ck_assert_str_eq(output1, "abc-+");
    ck_assert_str_eq(output2, "ab+c-");
    ck_assert_str_eq(output3, "lmn^/o*p-");
    ck_assert_str_eq(output4, "lmn^/o*p-");
    ck_assert_str_eq(output5, "vw/x^yz-*");

    free(output1);
    free(output2);
    free(output3);
    free(output4);
    free(output5);
}
END_TEST

Suite* rpn_suite(void)
{
    Suite* s;
    TCase* tc_infix_to_postfix;

    s = suite_create("RPN");

    tc_infix_to_postfix = tcase_create("Infix To Postfix");

    tcase_add_test(tc_infix_to_postfix, i2p_should_convert_empty_string_to_empty_string);
    tcase_add_test(tc_infix_to_postfix, i2p_should_convert_single_operand);
    tcase_add_test(tc_infix_to_postfix, i2p_should_convert_single_operator);
    tcase_add_test(tc_infix_to_postfix, i2p_should_convert_chain_of_equal_precedence_operators);
    tcase_add_test(tc_infix_to_postfix, i2p_should_recognize_all_operators);
    tcase_add_test(tc_infix_to_postfix, i2p_should_recognize_operator_precedence);
    tcase_add_test(tc_infix_to_postfix, i2p_should_recognize_a_single_parenthetical_expression);
    tcase_add_test(tc_infix_to_postfix, i2p_should_recognize_multiple_non_nested_parenthetical_groupings);
    tcase_add_test(tc_infix_to_postfix, i2p_should_recognize_nested_parenthetical_groupings);
    tcase_add_test(tc_infix_to_postfix, i2p_should_handle_provided_examples);



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

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}