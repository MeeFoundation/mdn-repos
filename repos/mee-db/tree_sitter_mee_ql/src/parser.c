#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef _MSC_VER
#pragma optimize("", off)
#elif defined(__clang__)
#pragma clang optimize off
#elif defined(__GNUC__)
#pragma GCC optimize ("O0")
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 745
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 139
#define ALIAS_COUNT 0
#define TOKEN_COUNT 68
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 20
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 22

enum ts_symbol_identifiers {
  anon_sym_LBRACK = 1,
  anon_sym_RBRACK = 2,
  anon_sym_LPAREN = 3,
  anon_sym_RPAREN = 4,
  anon_sym_LPAREN_RPAREN = 5,
  anon_sym_EQ = 6,
  anon_sym_EQ_EQ = 7,
  anon_sym_BANG_EQ = 8,
  anon_sym_GT = 9,
  anon_sym_LT = 10,
  anon_sym_GT_EQ = 11,
  anon_sym_LT_EQ = 12,
  anon_sym_matches = 13,
  anon_sym_after = 14,
  anon_sym_before = 15,
  anon_sym_between = 16,
  anon_sym_and = 17,
  anon_sym_contains = 18,
  anon_sym_exists = 19,
  anon_sym_DOT = 20,
  sym_pos_int = 21,
  anon_sym_LBRACE = 22,
  anon_sym_COMMA = 23,
  anon_sym_RBRACE = 24,
  anon_sym_COLON = 25,
  anon_sym_DQUOTE_DQUOTE = 26,
  anon_sym_DQUOTE = 27,
  sym_string_content = 28,
  sym_escape_sequence = 29,
  sym_number = 30,
  anon_sym_ERROR_missing_query_start = 31,
  anon_sym_ERROR_missing_query_body = 32,
  anon_sym_ERROR_missing_main_iterator = 33,
  anon_sym_ERROR_missing_array_query_end = 34,
  anon_sym_ERROR_missing_element_query_end = 35,
  anon_sym_ERROR_missing_iterator = 36,
  anon_sym_ERROR_missing_update_field = 37,
  anon_sym_ERROR_missing_delete_field = 38,
  anon_sym_ERROR_missing_filter_expression = 39,
  anon_sym_ERROR_missing_offset_value = 40,
  anon_sym_ERROR_missing_limit_value = 41,
  anon_sym_ERROR_missing_expression = 42,
  anon_sym_ERROR_missing_bool_value = 43,
  anon_sym_ERROR_missing_equals = 44,
  anon_sym_ERROR_missing_colon = 45,
  anon_sym_ERROR_missing_value = 46,
  anon_sym_ERROR_missing_brace_end = 47,
  anon_sym_ERROR_missing_array_end = 48,
  anon_sym_ERROR_missing_parenthesis_end = 49,
  anon_sym_ERROR_missing_string_end = 50,
  anon_sym_for = 51,
  anon_sym_let = 52,
  anon_sym_in = 53,
  sym_true = 54,
  sym_false = 55,
  sym_null = 56,
  anon_sym_and2 = 57,
  anon_sym_or = 58,
  anon_sym_not = 59,
  anon_sym_if = 60,
  anon_sym_set = 61,
  anon_sym_delete = 62,
  anon_sym_offset = 63,
  anon_sym_limit = 64,
  anon_sym_append = 65,
  anon_sym_values = 66,
  aux_sym_ident_token1 = 67,
  sym_start = 68,
  sym__query = 69,
  sym_array_query = 70,
  sym_element_query = 71,
  sym__missing_query = 72,
  sym__query_body = 73,
  sym_iterator_stmt = 74,
  sym_assignment = 75,
  sym_update_stmt = 76,
  sym_append_stmt = 77,
  sym_delete_stmt = 78,
  sym_filter_stmt = 79,
  sym_offset_stmt = 80,
  sym_limit_stmt = 81,
  sym__bool_expression = 82,
  sym_comparison = 83,
  sym_comparator = 84,
  sym_not_expression = 85,
  sym_and_expression = 86,
  sym_or_expression = 87,
  sym__bool_value = 88,
  sym__parenthesized_bool_expression = 89,
  sym__expression = 90,
  sym__parenthesized_expression = 91,
  sym_path = 92,
  sym_object = 93,
  sym_pair = 94,
  sym_array = 95,
  sym_string = 96,
  aux_sym__string_content = 97,
  sym__expected_expression = 98,
  sym_missing_query_start = 99,
  sym_missing_query_body = 100,
  sym_missing_main_iterator = 101,
  sym_missing_array_query_end = 102,
  sym_missing_element_query_end = 103,
  sym_missing_iterator = 104,
  sym_missing_update_field = 105,
  sym_missing_delete_field = 106,
  sym_missing_filter_expression = 107,
  sym_missing_offset_value = 108,
  sym_missing_limit_value = 109,
  sym_missing_expression = 110,
  sym_missing_bool_value = 111,
  sym_missing_equals = 112,
  sym_missing_colon = 113,
  sym_missing_identifier = 114,
  sym_missing_brace_end = 115,
  sym_missing_array_end = 116,
  sym_missing_parenthesis_end = 117,
  sym_missing_string_end = 118,
  sym__for = 119,
  sym__let = 120,
  sym__in = 121,
  sym__and = 122,
  sym__or = 123,
  sym__not = 124,
  sym__if = 125,
  sym__set = 126,
  sym__delete = 127,
  sym__offset = 128,
  sym__limit = 129,
  sym__append = 130,
  sym__values = 131,
  sym_ident = 132,
  aux_sym__query_body_repeat1 = 133,
  aux_sym_and_expression_repeat1 = 134,
  aux_sym_or_expression_repeat1 = 135,
  aux_sym_path_repeat1 = 136,
  aux_sym_object_repeat1 = 137,
  aux_sym_array_repeat1 = 138,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_LPAREN_RPAREN] = "()",
  [anon_sym_EQ] = "=",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_GT] = ">",
  [anon_sym_LT] = "<",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_matches] = "matches",
  [anon_sym_after] = "after",
  [anon_sym_before] = "before",
  [anon_sym_between] = "between",
  [anon_sym_and] = "and",
  [anon_sym_contains] = "contains",
  [anon_sym_exists] = "exists",
  [anon_sym_DOT] = ".",
  [sym_pos_int] = "pos_int",
  [anon_sym_LBRACE] = "{",
  [anon_sym_COMMA] = ",",
  [anon_sym_RBRACE] = "}",
  [anon_sym_COLON] = ":",
  [anon_sym_DQUOTE_DQUOTE] = "\"\"",
  [anon_sym_DQUOTE] = "\"",
  [sym_string_content] = "string_content",
  [sym_escape_sequence] = "escape_sequence",
  [sym_number] = "number",
  [anon_sym_ERROR_missing_query_start] = "ERROR_missing_query_start",
  [anon_sym_ERROR_missing_query_body] = "ERROR_missing_query_body",
  [anon_sym_ERROR_missing_main_iterator] = "ERROR_missing_main_iterator",
  [anon_sym_ERROR_missing_array_query_end] = "ERROR_missing_array_query_end",
  [anon_sym_ERROR_missing_element_query_end] = "ERROR_missing_element_query_end",
  [anon_sym_ERROR_missing_iterator] = "ERROR_missing_iterator",
  [anon_sym_ERROR_missing_update_field] = "ERROR_missing_update_field",
  [anon_sym_ERROR_missing_delete_field] = "ERROR_missing_delete_field",
  [anon_sym_ERROR_missing_filter_expression] = "ERROR_missing_filter_expression",
  [anon_sym_ERROR_missing_offset_value] = "ERROR_missing_offset_value",
  [anon_sym_ERROR_missing_limit_value] = "ERROR_missing_limit_value",
  [anon_sym_ERROR_missing_expression] = "ERROR_missing_expression",
  [anon_sym_ERROR_missing_bool_value] = "ERROR_missing_bool_value",
  [anon_sym_ERROR_missing_equals] = "ERROR_missing_equals",
  [anon_sym_ERROR_missing_colon] = "ERROR_missing_colon",
  [anon_sym_ERROR_missing_value] = "ERROR_missing_value",
  [anon_sym_ERROR_missing_brace_end] = "ERROR_missing_brace_end",
  [anon_sym_ERROR_missing_array_end] = "ERROR_missing_array_end",
  [anon_sym_ERROR_missing_parenthesis_end] = "ERROR_missing_parenthesis_end",
  [anon_sym_ERROR_missing_string_end] = "ERROR_missing_string_end",
  [anon_sym_for] = "for",
  [anon_sym_let] = "let",
  [anon_sym_in] = "in",
  [sym_true] = "true",
  [sym_false] = "false",
  [sym_null] = "null",
  [anon_sym_and2] = "and",
  [anon_sym_or] = "or",
  [anon_sym_not] = "not",
  [anon_sym_if] = "if",
  [anon_sym_set] = "set",
  [anon_sym_delete] = "delete",
  [anon_sym_offset] = "offset",
  [anon_sym_limit] = "limit",
  [anon_sym_append] = "append",
  [anon_sym_values] = "values",
  [aux_sym_ident_token1] = "ident_token1",
  [sym_start] = "start",
  [sym__query] = "_query",
  [sym_array_query] = "array_query",
  [sym_element_query] = "element_query",
  [sym__missing_query] = "_missing_query",
  [sym__query_body] = "_query_body",
  [sym_iterator_stmt] = "iterator_stmt",
  [sym_assignment] = "assignment",
  [sym_update_stmt] = "update_stmt",
  [sym_append_stmt] = "append_stmt",
  [sym_delete_stmt] = "delete_stmt",
  [sym_filter_stmt] = "filter_stmt",
  [sym_offset_stmt] = "offset_stmt",
  [sym_limit_stmt] = "limit_stmt",
  [sym__bool_expression] = "_bool_expression",
  [sym_comparison] = "comparison",
  [sym_comparator] = "comparator",
  [sym_not_expression] = "not_expression",
  [sym_and_expression] = "and_expression",
  [sym_or_expression] = "or_expression",
  [sym__bool_value] = "_bool_value",
  [sym__parenthesized_bool_expression] = "_parenthesized_bool_expression",
  [sym__expression] = "_expression",
  [sym__parenthesized_expression] = "_parenthesized_expression",
  [sym_path] = "path",
  [sym_object] = "object",
  [sym_pair] = "pair",
  [sym_array] = "array",
  [sym_string] = "string",
  [aux_sym__string_content] = "_string_content",
  [sym__expected_expression] = "_expected_expression",
  [sym_missing_query_start] = "missing_query_start",
  [sym_missing_query_body] = "missing_query_body",
  [sym_missing_main_iterator] = "missing_main_iterator",
  [sym_missing_array_query_end] = "missing_array_query_end",
  [sym_missing_element_query_end] = "missing_element_query_end",
  [sym_missing_iterator] = "missing_iterator",
  [sym_missing_update_field] = "missing_update_field",
  [sym_missing_delete_field] = "missing_delete_field",
  [sym_missing_filter_expression] = "missing_filter_expression",
  [sym_missing_offset_value] = "missing_offset_value",
  [sym_missing_limit_value] = "missing_limit_value",
  [sym_missing_expression] = "missing_expression",
  [sym_missing_bool_value] = "missing_bool_value",
  [sym_missing_equals] = "missing_equals",
  [sym_missing_colon] = "missing_colon",
  [sym_missing_identifier] = "missing_identifier",
  [sym_missing_brace_end] = "missing_brace_end",
  [sym_missing_array_end] = "missing_array_end",
  [sym_missing_parenthesis_end] = "missing_parenthesis_end",
  [sym_missing_string_end] = "missing_string_end",
  [sym__for] = "_for",
  [sym__let] = "_let",
  [sym__in] = "_in",
  [sym__and] = "_and",
  [sym__or] = "_or",
  [sym__not] = "_not",
  [sym__if] = "_if",
  [sym__set] = "_set",
  [sym__delete] = "_delete",
  [sym__offset] = "_offset",
  [sym__limit] = "_limit",
  [sym__append] = "_append",
  [sym__values] = "_values",
  [sym_ident] = "ident",
  [aux_sym__query_body_repeat1] = "_query_body_repeat1",
  [aux_sym_and_expression_repeat1] = "and_expression_repeat1",
  [aux_sym_or_expression_repeat1] = "or_expression_repeat1",
  [aux_sym_path_repeat1] = "path_repeat1",
  [aux_sym_object_repeat1] = "object_repeat1",
  [aux_sym_array_repeat1] = "array_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_LPAREN_RPAREN] = anon_sym_LPAREN_RPAREN,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [anon_sym_matches] = anon_sym_matches,
  [anon_sym_after] = anon_sym_after,
  [anon_sym_before] = anon_sym_before,
  [anon_sym_between] = anon_sym_between,
  [anon_sym_and] = anon_sym_and,
  [anon_sym_contains] = anon_sym_contains,
  [anon_sym_exists] = anon_sym_exists,
  [anon_sym_DOT] = anon_sym_DOT,
  [sym_pos_int] = sym_pos_int,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_DQUOTE_DQUOTE] = anon_sym_DQUOTE_DQUOTE,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [sym_string_content] = sym_string_content,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_number] = sym_number,
  [anon_sym_ERROR_missing_query_start] = anon_sym_ERROR_missing_query_start,
  [anon_sym_ERROR_missing_query_body] = anon_sym_ERROR_missing_query_body,
  [anon_sym_ERROR_missing_main_iterator] = anon_sym_ERROR_missing_main_iterator,
  [anon_sym_ERROR_missing_array_query_end] = anon_sym_ERROR_missing_array_query_end,
  [anon_sym_ERROR_missing_element_query_end] = anon_sym_ERROR_missing_element_query_end,
  [anon_sym_ERROR_missing_iterator] = anon_sym_ERROR_missing_iterator,
  [anon_sym_ERROR_missing_update_field] = anon_sym_ERROR_missing_update_field,
  [anon_sym_ERROR_missing_delete_field] = anon_sym_ERROR_missing_delete_field,
  [anon_sym_ERROR_missing_filter_expression] = anon_sym_ERROR_missing_filter_expression,
  [anon_sym_ERROR_missing_offset_value] = anon_sym_ERROR_missing_offset_value,
  [anon_sym_ERROR_missing_limit_value] = anon_sym_ERROR_missing_limit_value,
  [anon_sym_ERROR_missing_expression] = anon_sym_ERROR_missing_expression,
  [anon_sym_ERROR_missing_bool_value] = anon_sym_ERROR_missing_bool_value,
  [anon_sym_ERROR_missing_equals] = anon_sym_ERROR_missing_equals,
  [anon_sym_ERROR_missing_colon] = anon_sym_ERROR_missing_colon,
  [anon_sym_ERROR_missing_value] = anon_sym_ERROR_missing_value,
  [anon_sym_ERROR_missing_brace_end] = anon_sym_ERROR_missing_brace_end,
  [anon_sym_ERROR_missing_array_end] = anon_sym_ERROR_missing_array_end,
  [anon_sym_ERROR_missing_parenthesis_end] = anon_sym_ERROR_missing_parenthesis_end,
  [anon_sym_ERROR_missing_string_end] = anon_sym_ERROR_missing_string_end,
  [anon_sym_for] = anon_sym_for,
  [anon_sym_let] = anon_sym_let,
  [anon_sym_in] = anon_sym_in,
  [sym_true] = sym_true,
  [sym_false] = sym_false,
  [sym_null] = sym_null,
  [anon_sym_and2] = anon_sym_and,
  [anon_sym_or] = anon_sym_or,
  [anon_sym_not] = anon_sym_not,
  [anon_sym_if] = anon_sym_if,
  [anon_sym_set] = anon_sym_set,
  [anon_sym_delete] = anon_sym_delete,
  [anon_sym_offset] = anon_sym_offset,
  [anon_sym_limit] = anon_sym_limit,
  [anon_sym_append] = anon_sym_append,
  [anon_sym_values] = anon_sym_values,
  [aux_sym_ident_token1] = aux_sym_ident_token1,
  [sym_start] = sym_start,
  [sym__query] = sym__query,
  [sym_array_query] = sym_array_query,
  [sym_element_query] = sym_element_query,
  [sym__missing_query] = sym__missing_query,
  [sym__query_body] = sym__query_body,
  [sym_iterator_stmt] = sym_iterator_stmt,
  [sym_assignment] = sym_assignment,
  [sym_update_stmt] = sym_update_stmt,
  [sym_append_stmt] = sym_append_stmt,
  [sym_delete_stmt] = sym_delete_stmt,
  [sym_filter_stmt] = sym_filter_stmt,
  [sym_offset_stmt] = sym_offset_stmt,
  [sym_limit_stmt] = sym_limit_stmt,
  [sym__bool_expression] = sym__bool_expression,
  [sym_comparison] = sym_comparison,
  [sym_comparator] = sym_comparator,
  [sym_not_expression] = sym_not_expression,
  [sym_and_expression] = sym_and_expression,
  [sym_or_expression] = sym_or_expression,
  [sym__bool_value] = sym__bool_value,
  [sym__parenthesized_bool_expression] = sym__parenthesized_bool_expression,
  [sym__expression] = sym__expression,
  [sym__parenthesized_expression] = sym__parenthesized_expression,
  [sym_path] = sym_path,
  [sym_object] = sym_object,
  [sym_pair] = sym_pair,
  [sym_array] = sym_array,
  [sym_string] = sym_string,
  [aux_sym__string_content] = aux_sym__string_content,
  [sym__expected_expression] = sym__expected_expression,
  [sym_missing_query_start] = sym_missing_query_start,
  [sym_missing_query_body] = sym_missing_query_body,
  [sym_missing_main_iterator] = sym_missing_main_iterator,
  [sym_missing_array_query_end] = sym_missing_array_query_end,
  [sym_missing_element_query_end] = sym_missing_element_query_end,
  [sym_missing_iterator] = sym_missing_iterator,
  [sym_missing_update_field] = sym_missing_update_field,
  [sym_missing_delete_field] = sym_missing_delete_field,
  [sym_missing_filter_expression] = sym_missing_filter_expression,
  [sym_missing_offset_value] = sym_missing_offset_value,
  [sym_missing_limit_value] = sym_missing_limit_value,
  [sym_missing_expression] = sym_missing_expression,
  [sym_missing_bool_value] = sym_missing_bool_value,
  [sym_missing_equals] = sym_missing_equals,
  [sym_missing_colon] = sym_missing_colon,
  [sym_missing_identifier] = sym_missing_identifier,
  [sym_missing_brace_end] = sym_missing_brace_end,
  [sym_missing_array_end] = sym_missing_array_end,
  [sym_missing_parenthesis_end] = sym_missing_parenthesis_end,
  [sym_missing_string_end] = sym_missing_string_end,
  [sym__for] = sym__for,
  [sym__let] = sym__let,
  [sym__in] = sym__in,
  [sym__and] = sym__and,
  [sym__or] = sym__or,
  [sym__not] = sym__not,
  [sym__if] = sym__if,
  [sym__set] = sym__set,
  [sym__delete] = sym__delete,
  [sym__offset] = sym__offset,
  [sym__limit] = sym__limit,
  [sym__append] = sym__append,
  [sym__values] = sym__values,
  [sym_ident] = sym_ident,
  [aux_sym__query_body_repeat1] = aux_sym__query_body_repeat1,
  [aux_sym_and_expression_repeat1] = aux_sym_and_expression_repeat1,
  [aux_sym_or_expression_repeat1] = aux_sym_or_expression_repeat1,
  [aux_sym_path_repeat1] = aux_sym_path_repeat1,
  [aux_sym_object_repeat1] = aux_sym_object_repeat1,
  [aux_sym_array_repeat1] = aux_sym_array_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_matches] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_after] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_before] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_between] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_and] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_contains] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_exists] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [sym_pos_int] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [sym_string_content] = {
    .visible = true,
    .named = true,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_ERROR_missing_query_start] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_query_body] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_main_iterator] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_array_query_end] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_element_query_end] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_iterator] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_update_field] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_delete_field] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_filter_expression] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_offset_value] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_limit_value] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_expression] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_bool_value] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_equals] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_colon] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_value] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_brace_end] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_array_end] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_parenthesis_end] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ERROR_missing_string_end] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_for] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_let] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_in] = {
    .visible = true,
    .named = false,
  },
  [sym_true] = {
    .visible = true,
    .named = true,
  },
  [sym_false] = {
    .visible = true,
    .named = true,
  },
  [sym_null] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_and2] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_or] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_not] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_if] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_set] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_delete] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_offset] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_limit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_append] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_values] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_ident_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_start] = {
    .visible = true,
    .named = true,
  },
  [sym__query] = {
    .visible = false,
    .named = true,
  },
  [sym_array_query] = {
    .visible = true,
    .named = true,
  },
  [sym_element_query] = {
    .visible = true,
    .named = true,
  },
  [sym__missing_query] = {
    .visible = false,
    .named = true,
  },
  [sym__query_body] = {
    .visible = false,
    .named = true,
  },
  [sym_iterator_stmt] = {
    .visible = true,
    .named = true,
  },
  [sym_assignment] = {
    .visible = true,
    .named = true,
  },
  [sym_update_stmt] = {
    .visible = true,
    .named = true,
  },
  [sym_append_stmt] = {
    .visible = true,
    .named = true,
  },
  [sym_delete_stmt] = {
    .visible = true,
    .named = true,
  },
  [sym_filter_stmt] = {
    .visible = true,
    .named = true,
  },
  [sym_offset_stmt] = {
    .visible = true,
    .named = true,
  },
  [sym_limit_stmt] = {
    .visible = true,
    .named = true,
  },
  [sym__bool_expression] = {
    .visible = false,
    .named = true,
  },
  [sym_comparison] = {
    .visible = true,
    .named = true,
  },
  [sym_comparator] = {
    .visible = true,
    .named = true,
  },
  [sym_not_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_and_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_or_expression] = {
    .visible = true,
    .named = true,
  },
  [sym__bool_value] = {
    .visible = false,
    .named = true,
  },
  [sym__parenthesized_bool_expression] = {
    .visible = false,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym__parenthesized_expression] = {
    .visible = false,
    .named = true,
  },
  [sym_path] = {
    .visible = true,
    .named = true,
  },
  [sym_object] = {
    .visible = true,
    .named = true,
  },
  [sym_pair] = {
    .visible = true,
    .named = true,
  },
  [sym_array] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__string_content] = {
    .visible = false,
    .named = false,
  },
  [sym__expected_expression] = {
    .visible = false,
    .named = true,
  },
  [sym_missing_query_start] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_query_body] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_main_iterator] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_array_query_end] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_element_query_end] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_iterator] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_update_field] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_delete_field] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_filter_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_offset_value] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_limit_value] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_bool_value] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_equals] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_colon] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_brace_end] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_array_end] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_parenthesis_end] = {
    .visible = true,
    .named = true,
  },
  [sym_missing_string_end] = {
    .visible = true,
    .named = true,
  },
  [sym__for] = {
    .visible = false,
    .named = true,
  },
  [sym__let] = {
    .visible = false,
    .named = true,
  },
  [sym__in] = {
    .visible = false,
    .named = true,
  },
  [sym__and] = {
    .visible = false,
    .named = true,
  },
  [sym__or] = {
    .visible = false,
    .named = true,
  },
  [sym__not] = {
    .visible = false,
    .named = true,
  },
  [sym__if] = {
    .visible = false,
    .named = true,
  },
  [sym__set] = {
    .visible = false,
    .named = true,
  },
  [sym__delete] = {
    .visible = false,
    .named = true,
  },
  [sym__offset] = {
    .visible = false,
    .named = true,
  },
  [sym__limit] = {
    .visible = false,
    .named = true,
  },
  [sym__append] = {
    .visible = false,
    .named = true,
  },
  [sym__values] = {
    .visible = false,
    .named = true,
  },
  [sym_ident] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__query_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_and_expression_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_or_expression_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_path_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_object_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_array_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_body = 1,
  field_comparator = 2,
  field_expr = 3,
  field_field = 4,
  field_filter = 5,
  field_from = 6,
  field_item = 7,
  field_key = 8,
  field_limit = 9,
  field_main_iterator = 10,
  field_offset = 11,
  field_result = 12,
  field_right = 13,
  field_source = 14,
  field_statements = 15,
  field_to = 16,
  field_val = 17,
  field_value = 18,
  field_values = 19,
  field_var = 20,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_body] = "body",
  [field_comparator] = "comparator",
  [field_expr] = "expr",
  [field_field] = "field",
  [field_filter] = "filter",
  [field_from] = "from",
  [field_item] = "item",
  [field_key] = "key",
  [field_limit] = "limit",
  [field_main_iterator] = "main_iterator",
  [field_offset] = "offset",
  [field_result] = "result",
  [field_right] = "right",
  [field_source] = "source",
  [field_statements] = "statements",
  [field_to] = "to",
  [field_val] = "val",
  [field_value] = "value",
  [field_values] = "values",
  [field_var] = "var",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 4},
  [2] = {.index = 4, .length = 1},
  [3] = {.index = 5, .length = 4},
  [4] = {.index = 9, .length = 2},
  [5] = {.index = 11, .length = 2},
  [6] = {.index = 13, .length = 1},
  [7] = {.index = 14, .length = 1},
  [8] = {.index = 15, .length = 1},
  [9] = {.index = 16, .length = 1},
  [10] = {.index = 17, .length = 3},
  [11] = {.index = 20, .length = 2},
  [12] = {.index = 22, .length = 2},
  [13] = {.index = 24, .length = 2},
  [14] = {.index = 26, .length = 2},
  [15] = {.index = 28, .length = 2},
  [16] = {.index = 30, .length = 2},
  [17] = {.index = 32, .length = 1},
  [18] = {.index = 33, .length = 2},
  [19] = {.index = 35, .length = 2},
  [20] = {.index = 37, .length = 3},
  [21] = {.index = 40, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_body, 0, .inherited = true},
    {field_main_iterator, 0, .inherited = true},
    {field_result, 0, .inherited = true},
    {field_statements, 0, .inherited = true},
  [4] =
    {field_main_iterator, 0},
  [5] =
    {field_body, 1},
    {field_main_iterator, 1, .inherited = true},
    {field_result, 1, .inherited = true},
    {field_statements, 1, .inherited = true},
  [9] =
    {field_main_iterator, 0},
    {field_statements, 1},
  [11] =
    {field_main_iterator, 1},
    {field_result, 0},
  [13] =
    {field_filter, 1},
  [14] =
    {field_field, 1},
  [15] =
    {field_offset, 1},
  [16] =
    {field_limit, 1},
  [17] =
    {field_main_iterator, 1},
    {field_result, 0},
    {field_statements, 2},
  [20] =
    {field_key, 0},
    {field_value, 2},
  [22] =
    {field_comparator, 1},
    {field_val, 0},
  [24] =
    {field_field, 1},
    {field_value, 2},
  [26] =
    {field_expr, 2},
    {field_var, 0},
  [28] =
    {field_item, 1},
    {field_source, 3},
  [30] =
    {field_expr, 3},
    {field_var, 1},
  [32] =
    {field_right, 1},
  [33] =
    {field_expr, 3},
    {field_field, 1},
  [35] =
    {field_field, 1},
    {field_values, 3},
  [37] =
    {field_item, 1},
    {field_source, 3},
    {field_source, 4},
  [40] =
    {field_from, 1},
    {field_to, 3},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 2,
  [4] = 2,
  [5] = 2,
  [6] = 2,
  [7] = 2,
  [8] = 2,
  [9] = 9,
  [10] = 10,
  [11] = 10,
  [12] = 9,
  [13] = 9,
  [14] = 14,
  [15] = 14,
  [16] = 14,
  [17] = 10,
  [18] = 18,
  [19] = 18,
  [20] = 20,
  [21] = 20,
  [22] = 20,
  [23] = 18,
  [24] = 20,
  [25] = 18,
  [26] = 18,
  [27] = 18,
  [28] = 28,
  [29] = 29,
  [30] = 29,
  [31] = 28,
  [32] = 18,
  [33] = 29,
  [34] = 29,
  [35] = 28,
  [36] = 28,
  [37] = 18,
  [38] = 18,
  [39] = 18,
  [40] = 18,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 46,
  [49] = 46,
  [50] = 46,
  [51] = 51,
  [52] = 52,
  [53] = 46,
  [54] = 46,
  [55] = 46,
  [56] = 46,
  [57] = 46,
  [58] = 42,
  [59] = 42,
  [60] = 44,
  [61] = 61,
  [62] = 45,
  [63] = 43,
  [64] = 64,
  [65] = 41,
  [66] = 41,
  [67] = 67,
  [68] = 44,
  [69] = 45,
  [70] = 43,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 76,
  [78] = 78,
  [79] = 79,
  [80] = 74,
  [81] = 81,
  [82] = 76,
  [83] = 67,
  [84] = 61,
  [85] = 64,
  [86] = 86,
  [87] = 87,
  [88] = 61,
  [89] = 67,
  [90] = 64,
  [91] = 91,
  [92] = 64,
  [93] = 93,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 73,
  [98] = 71,
  [99] = 61,
  [100] = 67,
  [101] = 101,
  [102] = 102,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 107,
  [108] = 93,
  [109] = 109,
  [110] = 110,
  [111] = 111,
  [112] = 112,
  [113] = 109,
  [114] = 109,
  [115] = 91,
  [116] = 93,
  [117] = 109,
  [118] = 118,
  [119] = 72,
  [120] = 104,
  [121] = 111,
  [122] = 122,
  [123] = 93,
  [124] = 112,
  [125] = 125,
  [126] = 72,
  [127] = 73,
  [128] = 128,
  [129] = 91,
  [130] = 130,
  [131] = 131,
  [132] = 71,
  [133] = 104,
  [134] = 134,
  [135] = 73,
  [136] = 136,
  [137] = 71,
  [138] = 111,
  [139] = 112,
  [140] = 140,
  [141] = 104,
  [142] = 74,
  [143] = 81,
  [144] = 79,
  [145] = 75,
  [146] = 74,
  [147] = 75,
  [148] = 78,
  [149] = 74,
  [150] = 74,
  [151] = 72,
  [152] = 81,
  [153] = 79,
  [154] = 78,
  [155] = 86,
  [156] = 75,
  [157] = 87,
  [158] = 79,
  [159] = 81,
  [160] = 86,
  [161] = 78,
  [162] = 87,
  [163] = 105,
  [164] = 130,
  [165] = 134,
  [166] = 110,
  [167] = 110,
  [168] = 107,
  [169] = 106,
  [170] = 102,
  [171] = 101,
  [172] = 134,
  [173] = 107,
  [174] = 96,
  [175] = 95,
  [176] = 94,
  [177] = 136,
  [178] = 125,
  [179] = 140,
  [180] = 131,
  [181] = 136,
  [182] = 128,
  [183] = 183,
  [184] = 128,
  [185] = 130,
  [186] = 131,
  [187] = 125,
  [188] = 140,
  [189] = 103,
  [190] = 122,
  [191] = 94,
  [192] = 103,
  [193] = 95,
  [194] = 106,
  [195] = 105,
  [196] = 102,
  [197] = 101,
  [198] = 122,
  [199] = 96,
  [200] = 102,
  [201] = 94,
  [202] = 103,
  [203] = 95,
  [204] = 105,
  [205] = 96,
  [206] = 101,
  [207] = 128,
  [208] = 110,
  [209] = 130,
  [210] = 131,
  [211] = 140,
  [212] = 134,
  [213] = 136,
  [214] = 107,
  [215] = 106,
  [216] = 216,
  [217] = 217,
  [218] = 218,
  [219] = 217,
  [220] = 217,
  [221] = 221,
  [222] = 222,
  [223] = 217,
  [224] = 224,
  [225] = 225,
  [226] = 67,
  [227] = 64,
  [228] = 61,
  [229] = 229,
  [230] = 230,
  [231] = 231,
  [232] = 232,
  [233] = 221,
  [234] = 67,
  [235] = 225,
  [236] = 61,
  [237] = 218,
  [238] = 224,
  [239] = 222,
  [240] = 72,
  [241] = 224,
  [242] = 216,
  [243] = 64,
  [244] = 216,
  [245] = 71,
  [246] = 218,
  [247] = 74,
  [248] = 73,
  [249] = 222,
  [250] = 221,
  [251] = 225,
  [252] = 252,
  [253] = 136,
  [254] = 128,
  [255] = 105,
  [256] = 78,
  [257] = 96,
  [258] = 95,
  [259] = 106,
  [260] = 130,
  [261] = 94,
  [262] = 134,
  [263] = 103,
  [264] = 79,
  [265] = 75,
  [266] = 266,
  [267] = 131,
  [268] = 81,
  [269] = 269,
  [270] = 102,
  [271] = 110,
  [272] = 73,
  [273] = 273,
  [274] = 107,
  [275] = 275,
  [276] = 72,
  [277] = 277,
  [278] = 140,
  [279] = 279,
  [280] = 71,
  [281] = 101,
  [282] = 229,
  [283] = 283,
  [284] = 67,
  [285] = 67,
  [286] = 64,
  [287] = 61,
  [288] = 61,
  [289] = 232,
  [290] = 64,
  [291] = 74,
  [292] = 231,
  [293] = 230,
  [294] = 229,
  [295] = 230,
  [296] = 61,
  [297] = 64,
  [298] = 232,
  [299] = 231,
  [300] = 67,
  [301] = 301,
  [302] = 107,
  [303] = 303,
  [304] = 72,
  [305] = 61,
  [306] = 128,
  [307] = 61,
  [308] = 130,
  [309] = 131,
  [310] = 140,
  [311] = 311,
  [312] = 312,
  [313] = 94,
  [314] = 314,
  [315] = 315,
  [316] = 316,
  [317] = 95,
  [318] = 96,
  [319] = 64,
  [320] = 320,
  [321] = 101,
  [322] = 322,
  [323] = 323,
  [324] = 102,
  [325] = 105,
  [326] = 106,
  [327] = 327,
  [328] = 328,
  [329] = 329,
  [330] = 71,
  [331] = 110,
  [332] = 73,
  [333] = 67,
  [334] = 71,
  [335] = 67,
  [336] = 336,
  [337] = 337,
  [338] = 134,
  [339] = 64,
  [340] = 136,
  [341] = 79,
  [342] = 81,
  [343] = 343,
  [344] = 75,
  [345] = 345,
  [346] = 73,
  [347] = 71,
  [348] = 348,
  [349] = 349,
  [350] = 350,
  [351] = 351,
  [352] = 352,
  [353] = 78,
  [354] = 103,
  [355] = 72,
  [356] = 266,
  [357] = 357,
  [358] = 358,
  [359] = 73,
  [360] = 72,
  [361] = 275,
  [362] = 79,
  [363] = 275,
  [364] = 252,
  [365] = 273,
  [366] = 279,
  [367] = 269,
  [368] = 73,
  [369] = 79,
  [370] = 128,
  [371] = 71,
  [372] = 266,
  [373] = 81,
  [374] = 252,
  [375] = 136,
  [376] = 134,
  [377] = 277,
  [378] = 78,
  [379] = 110,
  [380] = 107,
  [381] = 106,
  [382] = 105,
  [383] = 102,
  [384] = 101,
  [385] = 96,
  [386] = 95,
  [387] = 94,
  [388] = 75,
  [389] = 140,
  [390] = 131,
  [391] = 130,
  [392] = 128,
  [393] = 81,
  [394] = 277,
  [395] = 136,
  [396] = 134,
  [397] = 78,
  [398] = 110,
  [399] = 107,
  [400] = 106,
  [401] = 105,
  [402] = 102,
  [403] = 101,
  [404] = 96,
  [405] = 95,
  [406] = 94,
  [407] = 75,
  [408] = 140,
  [409] = 72,
  [410] = 131,
  [411] = 103,
  [412] = 130,
  [413] = 103,
  [414] = 266,
  [415] = 72,
  [416] = 73,
  [417] = 273,
  [418] = 71,
  [419] = 269,
  [420] = 279,
  [421] = 283,
  [422] = 422,
  [423] = 423,
  [424] = 423,
  [425] = 283,
  [426] = 426,
  [427] = 423,
  [428] = 423,
  [429] = 327,
  [430] = 266,
  [431] = 94,
  [432] = 79,
  [433] = 81,
  [434] = 311,
  [435] = 312,
  [436] = 345,
  [437] = 315,
  [438] = 348,
  [439] = 316,
  [440] = 75,
  [441] = 322,
  [442] = 329,
  [443] = 349,
  [444] = 328,
  [445] = 327,
  [446] = 301,
  [447] = 350,
  [448] = 316,
  [449] = 315,
  [450] = 351,
  [451] = 78,
  [452] = 311,
  [453] = 328,
  [454] = 266,
  [455] = 136,
  [456] = 134,
  [457] = 343,
  [458] = 345,
  [459] = 348,
  [460] = 349,
  [461] = 352,
  [462] = 350,
  [463] = 351,
  [464] = 357,
  [465] = 352,
  [466] = 329,
  [467] = 357,
  [468] = 358,
  [469] = 322,
  [470] = 358,
  [471] = 320,
  [472] = 323,
  [473] = 337,
  [474] = 320,
  [475] = 110,
  [476] = 312,
  [477] = 103,
  [478] = 107,
  [479] = 79,
  [480] = 81,
  [481] = 106,
  [482] = 105,
  [483] = 102,
  [484] = 101,
  [485] = 106,
  [486] = 336,
  [487] = 303,
  [488] = 96,
  [489] = 95,
  [490] = 105,
  [491] = 323,
  [492] = 107,
  [493] = 102,
  [494] = 78,
  [495] = 101,
  [496] = 134,
  [497] = 343,
  [498] = 103,
  [499] = 110,
  [500] = 301,
  [501] = 128,
  [502] = 96,
  [503] = 130,
  [504] = 337,
  [505] = 303,
  [506] = 131,
  [507] = 336,
  [508] = 140,
  [509] = 75,
  [510] = 128,
  [511] = 136,
  [512] = 140,
  [513] = 131,
  [514] = 130,
  [515] = 95,
  [516] = 94,
  [517] = 517,
  [518] = 517,
  [519] = 517,
  [520] = 517,
  [521] = 517,
  [522] = 517,
  [523] = 517,
  [524] = 517,
  [525] = 517,
  [526] = 517,
  [527] = 517,
  [528] = 528,
  [529] = 529,
  [530] = 529,
  [531] = 529,
  [532] = 528,
  [533] = 528,
  [534] = 528,
  [535] = 528,
  [536] = 528,
  [537] = 528,
  [538] = 529,
  [539] = 528,
  [540] = 528,
  [541] = 528,
  [542] = 528,
  [543] = 543,
  [544] = 543,
  [545] = 543,
  [546] = 543,
  [547] = 222,
  [548] = 224,
  [549] = 543,
  [550] = 543,
  [551] = 543,
  [552] = 543,
  [553] = 543,
  [554] = 221,
  [555] = 555,
  [556] = 555,
  [557] = 557,
  [558] = 557,
  [559] = 559,
  [560] = 560,
  [561] = 557,
  [562] = 555,
  [563] = 560,
  [564] = 560,
  [565] = 565,
  [566] = 566,
  [567] = 230,
  [568] = 566,
  [569] = 566,
  [570] = 565,
  [571] = 229,
  [572] = 572,
  [573] = 565,
  [574] = 574,
  [575] = 574,
  [576] = 574,
  [577] = 566,
  [578] = 565,
  [579] = 231,
  [580] = 232,
  [581] = 566,
  [582] = 565,
  [583] = 565,
  [584] = 565,
  [585] = 565,
  [586] = 566,
  [587] = 566,
  [588] = 566,
  [589] = 566,
  [590] = 565,
  [591] = 565,
  [592] = 565,
  [593] = 566,
  [594] = 566,
  [595] = 595,
  [596] = 595,
  [597] = 597,
  [598] = 598,
  [599] = 597,
  [600] = 598,
  [601] = 595,
  [602] = 597,
  [603] = 595,
  [604] = 595,
  [605] = 598,
  [606] = 598,
  [607] = 607,
  [608] = 597,
  [609] = 609,
  [610] = 595,
  [611] = 597,
  [612] = 597,
  [613] = 598,
  [614] = 609,
  [615] = 598,
  [616] = 598,
  [617] = 595,
  [618] = 595,
  [619] = 597,
  [620] = 607,
  [621] = 621,
  [622] = 595,
  [623] = 607,
  [624] = 609,
  [625] = 598,
  [626] = 598,
  [627] = 597,
  [628] = 598,
  [629] = 598,
  [630] = 597,
  [631] = 631,
  [632] = 597,
  [633] = 631,
  [634] = 631,
  [635] = 595,
  [636] = 597,
  [637] = 637,
  [638] = 595,
  [639] = 134,
  [640] = 640,
  [641] = 266,
  [642] = 269,
  [643] = 277,
  [644] = 644,
  [645] = 645,
  [646] = 252,
  [647] = 647,
  [648] = 640,
  [649] = 640,
  [650] = 640,
  [651] = 647,
  [652] = 640,
  [653] = 640,
  [654] = 279,
  [655] = 266,
  [656] = 273,
  [657] = 128,
  [658] = 130,
  [659] = 275,
  [660] = 131,
  [661] = 140,
  [662] = 640,
  [663] = 94,
  [664] = 640,
  [665] = 95,
  [666] = 96,
  [667] = 647,
  [668] = 640,
  [669] = 640,
  [670] = 101,
  [671] = 102,
  [672] = 640,
  [673] = 640,
  [674] = 107,
  [675] = 136,
  [676] = 106,
  [677] = 110,
  [678] = 105,
  [679] = 679,
  [680] = 67,
  [681] = 681,
  [682] = 679,
  [683] = 683,
  [684] = 64,
  [685] = 685,
  [686] = 686,
  [687] = 679,
  [688] = 683,
  [689] = 685,
  [690] = 686,
  [691] = 679,
  [692] = 683,
  [693] = 683,
  [694] = 694,
  [695] = 61,
  [696] = 679,
  [697] = 679,
  [698] = 683,
  [699] = 699,
  [700] = 700,
  [701] = 683,
  [702] = 699,
  [703] = 679,
  [704] = 683,
  [705] = 679,
  [706] = 699,
  [707] = 683,
  [708] = 683,
  [709] = 679,
  [710] = 683,
  [711] = 679,
  [712] = 712,
  [713] = 686,
  [714] = 685,
  [715] = 679,
  [716] = 683,
  [717] = 717,
  [718] = 73,
  [719] = 71,
  [720] = 72,
  [721] = 717,
  [722] = 717,
  [723] = 723,
  [724] = 75,
  [725] = 79,
  [726] = 726,
  [727] = 727,
  [728] = 728,
  [729] = 726,
  [730] = 730,
  [731] = 728,
  [732] = 723,
  [733] = 723,
  [734] = 734,
  [735] = 735,
  [736] = 726,
  [737] = 728,
  [738] = 726,
  [739] = 739,
  [740] = 103,
  [741] = 78,
  [742] = 81,
  [743] = 743,
  [744] = 744,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(240);
      ADVANCE_MAP(
        '!', 26,
        '"', 270,
        '(', 244,
        ')', 245,
        ',', 265,
        '.', 262,
        ':', 267,
        '<', 252,
        '=', 248,
        '>', 251,
        'E', 356,
        '[', 241,
        '\\', 232,
        ']', 242,
        'a', 554,
        'b', 503,
        'c', 709,
        'd', 504,
        'e', 846,
        'f', 458,
        'i', 556,
        'l', 514,
        'm', 461,
        'n', 712,
        'o', 558,
        's', 520,
        't', 730,
        'v', 463,
        '{', 264,
        '}', 266,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(234);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(263);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(18);
      if (lookahead == '"') ADVANCE(269);
      if (lookahead == 'E') ADVANCE(275);
      if (lookahead == '\\') ADVANCE(232);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(271);
      if (lookahead != 0) ADVANCE(295);
      END_STATE();
    case 2:
      ADVANCE_MAP(
        '!', 26,
        '"', 270,
        '(', 243,
        ')', 245,
        ',', 265,
        '.', 262,
        ':', 267,
        '<', 252,
        '=', 248,
        '>', 251,
        'E', 40,
        '[', 241,
        ']', 242,
        'a', 112,
        'b', 96,
        'c', 171,
        'e', 229,
        'f', 172,
        'i', 153,
        'm', 72,
        'o', 177,
        '}', 266,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(263);
      END_STATE();
    case 3:
      ADVANCE_MAP(
        '!', 26,
        ')', 245,
        ',', 265,
        ':', 267,
        '<', 252,
        '=', 27,
        '>', 251,
        'E', 46,
        ']', 242,
        'a', 112,
        'b', 96,
        'c', 171,
        'e', 229,
        'f', 172,
        'm', 72,
        'o', 177,
        '}', 266,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      END_STATE();
    case 4:
      ADVANCE_MAP(
        '!', 26,
        ')', 245,
        '.', 262,
        '<', 252,
        '=', 27,
        '>', 251,
        'E', 390,
        'a', 554,
        'b', 503,
        'c', 709,
        'd', 504,
        'e', 846,
        'f', 710,
        'i', 557,
        'l', 514,
        'm', 461,
        'o', 558,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 5:
      ADVANCE_MAP(
        '!', 26,
        ')', 245,
        '<', 252,
        '=', 27,
        '>', 251,
        'E', 390,
        'a', 555,
        'b', 503,
        'c', 709,
        'd', 504,
        'e', 846,
        'f', 710,
        'i', 557,
        'l', 514,
        'm', 461,
        'o', 559,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(5);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 6:
      ADVANCE_MAP(
        '!', 26,
        '.', 262,
        '<', 252,
        '=', 27,
        '>', 251,
        'E', 388,
        ']', 242,
        'a', 554,
        'b', 503,
        'c', 709,
        'd', 504,
        'e', 846,
        'f', 710,
        'i', 557,
        'l', 514,
        'm', 461,
        'o', 558,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 7:
      ADVANCE_MAP(
        '!', 26,
        '<', 252,
        '=', 27,
        '>', 251,
        'E', 388,
        ']', 242,
        'a', 555,
        'b', 503,
        'c', 709,
        'd', 504,
        'e', 846,
        'f', 710,
        'i', 557,
        'l', 514,
        'm', 461,
        'o', 559,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(7);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 8:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '.', 262,
        '0', 297,
        'E', 392,
        '[', 241,
        'f', 459,
        'n', 829,
        't', 730,
        'v', 463,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(8);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 9:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '0', 297,
        '=', 247,
        'E', 374,
        '[', 241,
        'f', 458,
        'n', 712,
        't', 730,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(9);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 10:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '0', 297,
        'E', 376,
        '[', 241,
        'f', 459,
        'n', 712,
        't', 730,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(10);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 11:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '0', 297,
        'E', 378,
        '[', 241,
        'f', 459,
        'n', 712,
        't', 730,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(11);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 12:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '0', 297,
        'E', 380,
        '[', 241,
        ']', 242,
        'f', 458,
        'n', 829,
        't', 730,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(12);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 13:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '0', 297,
        'E', 382,
        '[', 241,
        'f', 459,
        'n', 712,
        't', 730,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(13);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 14:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '0', 297,
        'E', 386,
        '[', 241,
        'f', 458,
        'n', 829,
        't', 730,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(14);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 15:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '0', 297,
        'E', 392,
        '[', 241,
        'f', 459,
        'n', 829,
        't', 730,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(15);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 16:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '0', 297,
        'E', 394,
        '[', 241,
        ']', 242,
        'f', 459,
        'n', 829,
        't', 730,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(16);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 17:
      ADVANCE_MAP(
        '"', 270,
        '(', 243,
        '-', 25,
        '0', 297,
        'E', 396,
        '[', 241,
        'f', 459,
        'n', 829,
        't', 730,
        '{', 264,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(17);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 18:
      if (lookahead == '"') ADVANCE(269);
      if (lookahead == 'E') ADVANCE(50);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(18);
      END_STATE();
    case 19:
      ADVANCE_MAP(
        '(', 22,
        ')', 245,
        '.', 262,
        'E', 390,
        'a', 723,
        'd', 504,
        'f', 710,
        'i', 557,
        'l', 514,
        'o', 559,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(19);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 20:
      ADVANCE_MAP(
        '(', 22,
        '.', 262,
        'E', 388,
        ']', 242,
        'a', 723,
        'd', 504,
        'f', 710,
        'i', 557,
        'l', 514,
        'o', 559,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(20);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 21:
      ADVANCE_MAP(
        ')', 245,
        '.', 262,
        'E', 390,
        'a', 674,
        'd', 504,
        'f', 710,
        'i', 557,
        'l', 514,
        'o', 558,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(21);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 22:
      if (lookahead == ')') ADVANCE(246);
      END_STATE();
    case 23:
      if (lookahead == '-') ADVANCE(233);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(300);
      END_STATE();
    case 24:
      ADVANCE_MAP(
        '.', 262,
        'E', 388,
        ']', 242,
        'a', 674,
        'd', 504,
        'f', 710,
        'i', 557,
        'l', 514,
        'o', 558,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(24);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 25:
      if (lookahead == '0') ADVANCE(297);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(298);
      END_STATE();
    case 26:
      if (lookahead == '=') ADVANCE(250);
      END_STATE();
    case 27:
      if (lookahead == '=') ADVANCE(249);
      END_STATE();
    case 28:
      if (lookahead == '=') ADVANCE(247);
      if (lookahead == 'E') ADVANCE(52);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(28);
      END_STATE();
    case 29:
      if (lookahead == 'E') ADVANCE(398);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(29);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 30:
      if (lookahead == 'E') ADVANCE(400);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(30);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 31:
      if (lookahead == 'E') ADVANCE(402);
      if (lookahead == '[') ADVANCE(241);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(31);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 32:
      if (lookahead == 'E') ADVANCE(404);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(32);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 33:
      if (lookahead == 'O') ADVANCE(39);
      END_STATE();
    case 34:
      if (lookahead == 'O') ADVANCE(41);
      END_STATE();
    case 35:
      if (lookahead == 'O') ADVANCE(42);
      END_STATE();
    case 36:
      if (lookahead == 'O') ADVANCE(43);
      END_STATE();
    case 37:
      if (lookahead == 'O') ADVANCE(44);
      END_STATE();
    case 38:
      if (lookahead == 'R') ADVANCE(33);
      END_STATE();
    case 39:
      if (lookahead == 'R') ADVANCE(53);
      END_STATE();
    case 40:
      if (lookahead == 'R') ADVANCE(38);
      END_STATE();
    case 41:
      if (lookahead == 'R') ADVANCE(67);
      END_STATE();
    case 42:
      if (lookahead == 'R') ADVANCE(68);
      END_STATE();
    case 43:
      if (lookahead == 'R') ADVANCE(69);
      END_STATE();
    case 44:
      if (lookahead == 'R') ADVANCE(70);
      END_STATE();
    case 45:
      if (lookahead == 'R') ADVANCE(34);
      END_STATE();
    case 46:
      if (lookahead == 'R') ADVANCE(45);
      END_STATE();
    case 47:
      if (lookahead == 'R') ADVANCE(35);
      END_STATE();
    case 48:
      if (lookahead == 'R') ADVANCE(47);
      END_STATE();
    case 49:
      if (lookahead == 'R') ADVANCE(36);
      END_STATE();
    case 50:
      if (lookahead == 'R') ADVANCE(49);
      END_STATE();
    case 51:
      if (lookahead == 'R') ADVANCE(37);
      END_STATE();
    case 52:
      if (lookahead == 'R') ADVANCE(51);
      END_STATE();
    case 53:
      if (lookahead == '_') ADVANCE(148);
      END_STATE();
    case 54:
      if (lookahead == '_') ADVANCE(77);
      END_STATE();
    case 55:
      if (lookahead == '_') ADVANCE(226);
      END_STATE();
    case 56:
      if (lookahead == '_') ADVANCE(78);
      END_STATE();
    case 57:
      if (lookahead == '_') ADVANCE(79);
      END_STATE();
    case 58:
      if (lookahead == '_') ADVANCE(137);
      END_STATE();
    case 59:
      if (lookahead == '_') ADVANCE(102);
      END_STATE();
    case 60:
      if (lookahead == '_') ADVANCE(103);
      END_STATE();
    case 61:
      if (lookahead == '_') ADVANCE(105);
      END_STATE();
    case 62:
      if (lookahead == '_') ADVANCE(107);
      END_STATE();
    case 63:
      if (lookahead == '_') ADVANCE(97);
      END_STATE();
    case 64:
      if (lookahead == '_') ADVANCE(197);
      END_STATE();
    case 65:
      if (lookahead == '_') ADVANCE(195);
      END_STATE();
    case 66:
      if (lookahead == '_') ADVANCE(227);
      END_STATE();
    case 67:
      if (lookahead == '_') ADVANCE(149);
      END_STATE();
    case 68:
      if (lookahead == '_') ADVANCE(150);
      END_STATE();
    case 69:
      if (lookahead == '_') ADVANCE(151);
      END_STATE();
    case 70:
      if (lookahead == '_') ADVANCE(152);
      END_STATE();
    case 71:
      if (lookahead == 'a') ADVANCE(230);
      END_STATE();
    case 72:
      if (lookahead == 'a') ADVANCE(211);
      END_STATE();
    case 73:
      if (lookahead == 'a') ADVANCE(127);
      END_STATE();
    case 74:
      if (lookahead == 'a') ADVANCE(86);
      END_STATE();
    case 75:
      if (lookahead == 'a') ADVANCE(143);
      END_STATE();
    case 76:
      if (lookahead == 'a') ADVANCE(145);
      END_STATE();
    case 77:
      ADVANCE_MAP(
        'a', 185,
        'b', 182,
        'c', 170,
        'e', 176,
        'l', 126,
        'm', 83,
        'o', 114,
        'p', 80,
        'q', 225,
        's', 216,
      );
      END_STATE();
    case 78:
      if (lookahead == 'a') ADVANCE(185);
      if (lookahead == 'b') ADVANCE(182);
      if (lookahead == 'c') ADVANCE(170);
      if (lookahead == 'm') ADVANCE(83);
      if (lookahead == 'p') ADVANCE(80);
      END_STATE();
    case 79:
      if (lookahead == 'a') ADVANCE(185);
      if (lookahead == 'b') ADVANCE(182);
      if (lookahead == 'm') ADVANCE(83);
      if (lookahead == 'p') ADVANCE(80);
      END_STATE();
    case 80:
      if (lookahead == 'a') ADVANCE(184);
      END_STATE();
    case 81:
      if (lookahead == 'a') ADVANCE(220);
      END_STATE();
    case 82:
      if (lookahead == 'a') ADVANCE(186);
      END_STATE();
    case 83:
      if (lookahead == 'a') ADVANCE(130);
      END_STATE();
    case 84:
      if (lookahead == 'a') ADVANCE(146);
      END_STATE();
    case 85:
      if (lookahead == 'c') ADVANCE(123);
      END_STATE();
    case 86:
      if (lookahead == 'c') ADVANCE(110);
      END_STATE();
    case 87:
      if (lookahead == 'd') ADVANCE(327);
      END_STATE();
    case 88:
      if (lookahead == 'd') ADVANCE(318);
      END_STATE();
    case 89:
      if (lookahead == 'd') ADVANCE(317);
      END_STATE();
    case 90:
      if (lookahead == 'd') ADVANCE(320);
      END_STATE();
    case 91:
      if (lookahead == 'd') ADVANCE(319);
      END_STATE();
    case 92:
      if (lookahead == 'd') ADVANCE(259);
      END_STATE();
    case 93:
      if (lookahead == 'e') ADVANCE(257);
      END_STATE();
    case 94:
      if (lookahead == 'e') ADVANCE(311);
      END_STATE();
    case 95:
      if (lookahead == 'e') ADVANCE(310);
      END_STATE();
    case 96:
      if (lookahead == 'e') ADVANCE(116);
      END_STATE();
    case 97:
      if (lookahead == 'e') ADVANCE(176);
      END_STATE();
    case 98:
      if (lookahead == 'e') ADVANCE(154);
      END_STATE();
    case 99:
      if (lookahead == 'e') ADVANCE(179);
      END_STATE();
    case 100:
      if (lookahead == 'e') ADVANCE(191);
      END_STATE();
    case 101:
      if (lookahead == 'e') ADVANCE(98);
      END_STATE();
    case 102:
      if (lookahead == 'e') ADVANCE(157);
      END_STATE();
    case 103:
      if (lookahead == 'e') ADVANCE(159);
      END_STATE();
    case 104:
      if (lookahead == 'e') ADVANCE(200);
      END_STATE();
    case 105:
      if (lookahead == 'e') ADVANCE(161);
      END_STATE();
    case 106:
      if (lookahead == 'e') ADVANCE(188);
      END_STATE();
    case 107:
      if (lookahead == 'e') ADVANCE(163);
      END_STATE();
    case 108:
      if (lookahead == 'e') ADVANCE(187);
      END_STATE();
    case 109:
      if (lookahead == 'e') ADVANCE(164);
      END_STATE();
    case 110:
      if (lookahead == 'e') ADVANCE(60);
      END_STATE();
    case 111:
      if (lookahead == 'e') ADVANCE(221);
      END_STATE();
    case 112:
      if (lookahead == 'f') ADVANCE(212);
      if (lookahead == 'n') ADVANCE(87);
      END_STATE();
    case 113:
      if (lookahead == 'f') ADVANCE(212);
      if (lookahead == 'n') ADVANCE(92);
      END_STATE();
    case 114:
      if (lookahead == 'f') ADVANCE(115);
      END_STATE();
    case 115:
      if (lookahead == 'f') ADVANCE(198);
      END_STATE();
    case 116:
      if (lookahead == 'f') ADVANCE(173);
      if (lookahead == 't') ADVANCE(228);
      END_STATE();
    case 117:
      if (lookahead == 'g') ADVANCE(54);
      END_STATE();
    case 118:
      if (lookahead == 'g') ADVANCE(56);
      END_STATE();
    case 119:
      if (lookahead == 'g') ADVANCE(57);
      END_STATE();
    case 120:
      if (lookahead == 'g') ADVANCE(61);
      END_STATE();
    case 121:
      if (lookahead == 'g') ADVANCE(63);
      END_STATE();
    case 122:
      if (lookahead == 'g') ADVANCE(65);
      END_STATE();
    case 123:
      if (lookahead == 'h') ADVANCE(100);
      END_STATE();
    case 124:
      if (lookahead == 'h') ADVANCE(104);
      END_STATE();
    case 125:
      if (lookahead == 'i') ADVANCE(194);
      END_STATE();
    case 126:
      if (lookahead == 'i') ADVANCE(147);
      END_STATE();
    case 127:
      if (lookahead == 'i') ADVANCE(162);
      END_STATE();
    case 128:
      if (lookahead == 'i') ADVANCE(156);
      END_STATE();
    case 129:
      if (lookahead == 'i') ADVANCE(196);
      END_STATE();
    case 130:
      if (lookahead == 'i') ADVANCE(160);
      END_STATE();
    case 131:
      if (lookahead == 'i') ADVANCE(215);
      END_STATE();
    case 132:
      if (lookahead == 'i') ADVANCE(201);
      END_STATE();
    case 133:
      if (lookahead == 'i') ADVANCE(165);
      END_STATE();
    case 134:
      if (lookahead == 'i') ADVANCE(166);
      END_STATE();
    case 135:
      if (lookahead == 'i') ADVANCE(167);
      END_STATE();
    case 136:
      if (lookahead == 'i') ADVANCE(168);
      END_STATE();
    case 137:
      if (lookahead == 'i') ADVANCE(219);
      END_STATE();
    case 138:
      if (lookahead == 'i') ADVANCE(169);
      END_STATE();
    case 139:
      if (lookahead == 'i') ADVANCE(205);
      END_STATE();
    case 140:
      if (lookahead == 'i') ADVANCE(207);
      END_STATE();
    case 141:
      if (lookahead == 'i') ADVANCE(208);
      END_STATE();
    case 142:
      if (lookahead == 'i') ADVANCE(209);
      END_STATE();
    case 143:
      if (lookahead == 'l') ADVANCE(193);
      END_STATE();
    case 144:
      if (lookahead == 'l') ADVANCE(174);
      END_STATE();
    case 145:
      if (lookahead == 'l') ADVANCE(223);
      END_STATE();
    case 146:
      if (lookahead == 'l') ADVANCE(224);
      END_STATE();
    case 147:
      if (lookahead == 'm') ADVANCE(131);
      END_STATE();
    case 148:
      if (lookahead == 'm') ADVANCE(129);
      END_STATE();
    case 149:
      if (lookahead == 'm') ADVANCE(139);
      END_STATE();
    case 150:
      if (lookahead == 'm') ADVANCE(140);
      END_STATE();
    case 151:
      if (lookahead == 'm') ADVANCE(141);
      END_STATE();
    case 152:
      if (lookahead == 'm') ADVANCE(142);
      END_STATE();
    case 153:
      if (lookahead == 'n') ADVANCE(323);
      END_STATE();
    case 154:
      if (lookahead == 'n') ADVANCE(258);
      END_STATE();
    case 155:
      if (lookahead == 'n') ADVANCE(315);
      END_STATE();
    case 156:
      if (lookahead == 'n') ADVANCE(117);
      END_STATE();
    case 157:
      if (lookahead == 'n') ADVANCE(88);
      END_STATE();
    case 158:
      if (lookahead == 'n') ADVANCE(213);
      END_STATE();
    case 159:
      if (lookahead == 'n') ADVANCE(89);
      END_STATE();
    case 160:
      if (lookahead == 'n') ADVANCE(58);
      END_STATE();
    case 161:
      if (lookahead == 'n') ADVANCE(90);
      END_STATE();
    case 162:
      if (lookahead == 'n') ADVANCE(192);
      END_STATE();
    case 163:
      if (lookahead == 'n') ADVANCE(91);
      END_STATE();
    case 164:
      if (lookahead == 'n') ADVANCE(217);
      END_STATE();
    case 165:
      if (lookahead == 'n') ADVANCE(120);
      END_STATE();
    case 166:
      if (lookahead == 'n') ADVANCE(118);
      END_STATE();
    case 167:
      if (lookahead == 'n') ADVANCE(119);
      END_STATE();
    case 168:
      if (lookahead == 'n') ADVANCE(122);
      END_STATE();
    case 169:
      if (lookahead == 'n') ADVANCE(121);
      END_STATE();
    case 170:
      if (lookahead == 'o') ADVANCE(144);
      END_STATE();
    case 171:
      if (lookahead == 'o') ADVANCE(158);
      END_STATE();
    case 172:
      if (lookahead == 'o') ADVANCE(178);
      END_STATE();
    case 173:
      if (lookahead == 'o') ADVANCE(181);
      END_STATE();
    case 174:
      if (lookahead == 'o') ADVANCE(155);
      END_STATE();
    case 175:
      if (lookahead == 'o') ADVANCE(180);
      END_STATE();
    case 176:
      if (lookahead == 'q') ADVANCE(222);
      END_STATE();
    case 177:
      if (lookahead == 'r') ADVANCE(328);
      END_STATE();
    case 178:
      if (lookahead == 'r') ADVANCE(321);
      END_STATE();
    case 179:
      if (lookahead == 'r') ADVANCE(256);
      END_STATE();
    case 180:
      if (lookahead == 'r') ADVANCE(303);
      END_STATE();
    case 181:
      if (lookahead == 'r') ADVANCE(93);
      END_STATE();
    case 182:
      if (lookahead == 'r') ADVANCE(74);
      END_STATE();
    case 183:
      if (lookahead == 'r') ADVANCE(71);
      END_STATE();
    case 184:
      if (lookahead == 'r') ADVANCE(109);
      END_STATE();
    case 185:
      if (lookahead == 'r') ADVANCE(183);
      END_STATE();
    case 186:
      if (lookahead == 'r') ADVANCE(210);
      END_STATE();
    case 187:
      if (lookahead == 'r') ADVANCE(81);
      END_STATE();
    case 188:
      if (lookahead == 'r') ADVANCE(231);
      END_STATE();
    case 189:
      if (lookahead == 'r') ADVANCE(133);
      END_STATE();
    case 190:
      if (lookahead == 's') ADVANCE(261);
      END_STATE();
    case 191:
      if (lookahead == 's') ADVANCE(255);
      END_STATE();
    case 192:
      if (lookahead == 's') ADVANCE(260);
      END_STATE();
    case 193:
      if (lookahead == 's') ADVANCE(314);
      END_STATE();
    case 194:
      if (lookahead == 's') ADVANCE(214);
      END_STATE();
    case 195:
      if (lookahead == 's') ADVANCE(216);
      END_STATE();
    case 196:
      if (lookahead == 's') ADVANCE(199);
      END_STATE();
    case 197:
      if (lookahead == 's') ADVANCE(218);
      END_STATE();
    case 198:
      if (lookahead == 's') ADVANCE(111);
      END_STATE();
    case 199:
      if (lookahead == 's') ADVANCE(128);
      END_STATE();
    case 200:
      if (lookahead == 's') ADVANCE(132);
      END_STATE();
    case 201:
      if (lookahead == 's') ADVANCE(62);
      END_STATE();
    case 202:
      if (lookahead == 's') ADVANCE(134);
      END_STATE();
    case 203:
      if (lookahead == 's') ADVANCE(135);
      END_STATE();
    case 204:
      if (lookahead == 's') ADVANCE(136);
      END_STATE();
    case 205:
      if (lookahead == 's') ADVANCE(202);
      END_STATE();
    case 206:
      if (lookahead == 's') ADVANCE(138);
      END_STATE();
    case 207:
      if (lookahead == 's') ADVANCE(203);
      END_STATE();
    case 208:
      if (lookahead == 's') ADVANCE(204);
      END_STATE();
    case 209:
      if (lookahead == 's') ADVANCE(206);
      END_STATE();
    case 210:
      if (lookahead == 't') ADVANCE(301);
      END_STATE();
    case 211:
      if (lookahead == 't') ADVANCE(85);
      END_STATE();
    case 212:
      if (lookahead == 't') ADVANCE(99);
      END_STATE();
    case 213:
      if (lookahead == 't') ADVANCE(73);
      END_STATE();
    case 214:
      if (lookahead == 't') ADVANCE(190);
      END_STATE();
    case 215:
      if (lookahead == 't') ADVANCE(55);
      END_STATE();
    case 216:
      if (lookahead == 't') ADVANCE(189);
      END_STATE();
    case 217:
      if (lookahead == 't') ADVANCE(124);
      END_STATE();
    case 218:
      if (lookahead == 't') ADVANCE(82);
      END_STATE();
    case 219:
      if (lookahead == 't') ADVANCE(108);
      END_STATE();
    case 220:
      if (lookahead == 't') ADVANCE(175);
      END_STATE();
    case 221:
      if (lookahead == 't') ADVANCE(66);
      END_STATE();
    case 222:
      if (lookahead == 'u') ADVANCE(75);
      END_STATE();
    case 223:
      if (lookahead == 'u') ADVANCE(94);
      END_STATE();
    case 224:
      if (lookahead == 'u') ADVANCE(95);
      END_STATE();
    case 225:
      if (lookahead == 'u') ADVANCE(106);
      END_STATE();
    case 226:
      if (lookahead == 'v') ADVANCE(76);
      END_STATE();
    case 227:
      if (lookahead == 'v') ADVANCE(84);
      END_STATE();
    case 228:
      if (lookahead == 'w') ADVANCE(101);
      END_STATE();
    case 229:
      if (lookahead == 'x') ADVANCE(125);
      END_STATE();
    case 230:
      if (lookahead == 'y') ADVANCE(59);
      END_STATE();
    case 231:
      if (lookahead == 'y') ADVANCE(64);
      END_STATE();
    case 232:
      ADVANCE_MAP(
        '"', 296,
        '/', 296,
        '\\', 296,
        'b', 296,
        'f', 296,
        'n', 296,
        'r', 296,
        't', 296,
        'u', 296,
      );
      END_STATE();
    case 233:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(300);
      END_STATE();
    case 234:
      if (eof) ADVANCE(240);
      ADVANCE_MAP(
        '!', 26,
        '"', 270,
        '(', 244,
        ')', 245,
        ',', 265,
        '.', 262,
        ':', 267,
        '<', 252,
        '=', 248,
        '>', 251,
        'E', 356,
        '[', 241,
        ']', 242,
        'a', 554,
        'b', 503,
        'c', 709,
        'd', 504,
        'e', 846,
        'f', 458,
        'i', 556,
        'l', 514,
        'm', 461,
        'n', 712,
        'o', 558,
        's', 520,
        't', 730,
        'v', 463,
        '{', 264,
        '}', 266,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(234);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(263);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 235:
      if (eof) ADVANCE(240);
      ADVANCE_MAP(
        '!', 26,
        ')', 245,
        ',', 265,
        '.', 262,
        '<', 252,
        '=', 27,
        '>', 251,
        'E', 48,
        ']', 242,
        'a', 113,
        'b', 96,
        'c', 171,
        'e', 229,
        'f', 172,
        'm', 72,
        '}', 266,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(235);
      END_STATE();
    case 236:
      if (eof) ADVANCE(240);
      ADVANCE_MAP(
        '!', 26,
        ')', 245,
        '.', 262,
        '<', 252,
        '=', 27,
        '>', 251,
        'E', 384,
        ']', 242,
        'a', 554,
        'b', 503,
        'c', 709,
        'd', 504,
        'e', 846,
        'f', 710,
        'i', 557,
        'l', 514,
        'm', 461,
        'o', 558,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(236);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 237:
      if (eof) ADVANCE(240);
      ADVANCE_MAP(
        '!', 26,
        ')', 245,
        '<', 252,
        '=', 27,
        '>', 251,
        'E', 384,
        ']', 242,
        'a', 555,
        'b', 503,
        'c', 709,
        'd', 504,
        'e', 846,
        'f', 710,
        'i', 557,
        'l', 514,
        'm', 461,
        'o', 559,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(237);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 238:
      if (eof) ADVANCE(240);
      ADVANCE_MAP(
        '(', 22,
        ')', 245,
        '.', 262,
        'E', 384,
        ']', 242,
        'a', 723,
        'd', 504,
        'f', 710,
        'i', 557,
        'l', 514,
        'o', 559,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(238);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 239:
      if (eof) ADVANCE(240);
      ADVANCE_MAP(
        ')', 245,
        '.', 262,
        'E', 384,
        ']', 242,
        'a', 674,
        'd', 504,
        'f', 710,
        'i', 557,
        'l', 514,
        'o', 558,
        's', 520,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(239);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == ')') ADVANCE(246);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(anon_sym_LPAREN_RPAREN);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(249);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(253);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(254);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(anon_sym_matches);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(anon_sym_after);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(anon_sym_before);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(anon_sym_between);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(anon_sym_and);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(anon_sym_contains);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(anon_sym_exists);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(sym_pos_int);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(263);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(anon_sym_DQUOTE_DQUOTE);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      if (lookahead == '"') ADVANCE(268);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'E') ADVANCE(275);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(271);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'O') ADVANCE(274);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'R') ADVANCE(272);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'R') ADVANCE(276);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'R') ADVANCE(273);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '_') ADVANCE(286);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '_') ADVANCE(280);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '_') ADVANCE(291);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'd') ADVANCE(295);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'e') ADVANCE(288);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'g') ADVANCE(278);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'g') ADVANCE(277);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'i') ADVANCE(293);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'i') ADVANCE(287);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'i') ADVANCE(289);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'm') ADVANCE(283);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'n') ADVANCE(281);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'n') ADVANCE(279);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'n') ADVANCE(282);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'r') ADVANCE(285);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 's') ADVANCE(294);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 's') ADVANCE(284);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 's') ADVANCE(292);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 't') ADVANCE(290);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(295);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(299);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(23);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(299);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(23);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(298);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(23);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(299);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(300);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_query_start);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_query_body);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_main_iterator);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_array_query_end);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_element_query_end);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_iterator);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_update_field);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_delete_field);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_filter_expression);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_offset_value);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_limit_value);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_expression);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_bool_value);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_equals);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_colon);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_value);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_brace_end);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_array_end);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_parenthesis_end);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_string_end);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(anon_sym_for);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(anon_sym_let);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(anon_sym_in);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(sym_false);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(sym_null);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(anon_sym_and2);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(anon_sym_or);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(anon_sym_not);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(anon_sym_set);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(anon_sym_delete);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(anon_sym_offset);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(anon_sym_limit);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(anon_sym_append);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(anon_sym_values);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(355);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(357);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(358);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(359);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(360);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(361);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(362);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(363);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(364);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(365);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(366);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(367);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(368);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 350:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(369);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 351:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(370);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 352:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(371);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 353:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(372);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(337);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 355:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(426);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 356:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(354);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 357:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(439);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 358:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(441);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 359:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(443);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 360:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(444);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 361:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(445);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 362:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(446);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 363:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(447);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 364:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(448);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 365:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(449);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 366:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(450);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 367:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(451);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 368:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(452);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 369:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(453);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 370:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(454);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 371:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(455);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 372:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(456);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 373:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(338);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 374:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(373);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 375:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(339);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 376:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(375);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 377:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(340);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 378:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(377);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 379:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(341);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 380:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(379);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 381:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(342);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 382:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(381);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 383:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(343);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 384:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(383);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 385:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(344);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 386:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(385);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 387:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(345);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 388:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(387);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 389:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(346);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 390:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(389);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 391:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(347);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 392:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(391);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 393:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(348);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 394:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(393);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 395:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(349);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 396:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(395);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 397:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(350);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 398:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(397);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 399:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(351);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 400:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(399);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 401:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(352);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 402:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(401);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 403:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(353);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 404:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(403);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 405:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(464);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 406:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(842);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 407:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(524);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 408:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(482);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 409:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(729);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 410:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(486);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 411:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(483);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 412:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(484);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 413:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(485);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 414:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(472);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 415:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(487);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 416:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(477);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 417:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(656);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 418:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(478);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 419:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(541);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 420:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(552);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 421:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(473);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 422:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(763);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 423:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(828);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 424:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(502);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 425:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(599);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 426:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(654);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 427:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(561);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 428:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(619);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 429:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(529);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 430:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(513);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 431:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(532);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 432:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(536);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 433:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(537);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 434:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(538);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 435:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(525);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 436:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(563);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 437:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(728);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 438:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(843);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 439:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(658);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 440:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(844);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 441:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(659);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 442:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(841);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 443:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(660);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 444:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(661);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 445:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(662);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 446:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(663);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 447:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(664);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 448:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(665);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 449:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(666);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 450:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(667);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 451:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(668);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 452:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(669);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 453:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(670);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 454:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(671);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 455:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(672);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 456:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(673);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 457:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(850);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 458:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(636);
      if (lookahead == 'o') ADVANCE(731);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 459:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(636);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 460:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(489);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 461:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(805);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 462:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(587);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 463:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(646);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 464:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      ADVANCE_MAP(
        'a', 736,
        'b', 721,
        'c', 714,
        'd', 550,
        'e', 643,
        'f', 590,
        'i', 817,
        'l', 617,
        'm', 469,
        'o', 565,
        'p', 468,
        'q', 832,
        's', 814,
        'u', 724,
        'v', 471,
      );
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 465:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(738);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 466:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(821);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 467:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(642);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 468:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(739);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 469:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(589);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 470:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(856);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 471:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(648);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 472:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(743);
      if (lookahead == 'm') ADVANCE(469);
      if (lookahead == 'q') ADVANCE(840);
      if (lookahead == 's') ADVANCE(814);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 473:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(743);
      if (lookahead == 's') ADVANCE(814);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 474:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(823);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 475:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(824);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 476:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(649);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 477:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(750);
      if (lookahead == 'e') ADVANCE(644);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 478:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(750);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 479:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(855);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 480:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(650);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 481:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(651);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 482:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(713);
      if (lookahead == 's') ADVANCE(822);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 483:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(713);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 484:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(722);
      if (lookahead == 'e') ADVANCE(847);
      if (lookahead == 's') ADVANCE(814);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 485:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(722);
      if (lookahead == 'f') ADVANCE(590);
      if (lookahead == 's') ADVANCE(814);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 486:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(722);
      if (lookahead == 'm') ADVANCE(469);
      if (lookahead == 'q') ADVANCE(840);
      if (lookahead == 's') ADVANCE(814);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 487:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(722);
      if (lookahead == 's') ADVANCE(814);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 488:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'c') ADVANCE(584);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 489:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'c') ADVANCE(522);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 490:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(327);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 491:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(335);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 492:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(318);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 493:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(317);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 494:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(320);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 495:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(308);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 496:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(307);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 497:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(304);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 498:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(319);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 499:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(305);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 500:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(849);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 501:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(475);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 502:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(550);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 503:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(560);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 504:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(639);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 505:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(324);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 506:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(325);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 507:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(257);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 508:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(332);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 509:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(316);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 510:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(313);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 511:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(311);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 512:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(310);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 513:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(848);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 514:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(804);
      if (lookahead == 'i') ADVANCE(653);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 515:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(680);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 516:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(732);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 517:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 518:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(657);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 519:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(755);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 520:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(807);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 521:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(756);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 522:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(429);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 523:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(745);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 524:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(681);
      if (lookahead == 'q') ADVANCE(838);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 525:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(681);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 526:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(427);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 527:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(741);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 528:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(809);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 529:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(683);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 530:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(640);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 531:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(744);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 532:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(686);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 533:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(641);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 534:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(767);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 535:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(517);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 536:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(687);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 537:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(688);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 538:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(689);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 539:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(816);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 540:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(690);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 541:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(644);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 542:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(764);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 543:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(691);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 544:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(819);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 545:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(436);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 546:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(746);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 547:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(788);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 548:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(752);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 549:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(747);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 550:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(652);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 551:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(751);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 552:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(847);
      if (lookahead == 's') ADVANCE(814);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 553:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(827);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 554:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(813);
      if (lookahead == 'n') ADVANCE(490);
      if (lookahead == 'p') ADVANCE(725);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 555:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(813);
      if (lookahead == 'p') ADVANCE(725);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 556:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(330);
      if (lookahead == 'n') ADVANCE(323);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 557:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(330);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 558:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(562);
      if (lookahead == 'r') ADVANCE(328);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 559:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(562);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 560:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(711);
      if (lookahead == 't') ADVANCE(845);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 561:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(595);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 562:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(765);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 563:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(596);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 564:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(768);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 565:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(564);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 566:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(405);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 567:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(410);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 568:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(412);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 569:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(413);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 570:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(414);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 571:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(415);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 572:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(416);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 573:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(417);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 574:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(418);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 575:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(419);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 576:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(420);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 577:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(421);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 578:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(422);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 579:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(423);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 580:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(424);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 581:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(425);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 582:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(431);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 583:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(442);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 584:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'h') ADVANCE(521);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 585:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'h') ADVANCE(534);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 586:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(759);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 587:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(685);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 588:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(676);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 589:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(682);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 590:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(647);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 591:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(761);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 592:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(808);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 593:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(826);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 594:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(770);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 595:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(530);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 596:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(533);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 597:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(692);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 598:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(718);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 599:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(817);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 600:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(693);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 601:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(720);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 602:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(694);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 603:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(695);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 604:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(696);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 605:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(697);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 606:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(698);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 607:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(699);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 608:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(700);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 609:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(701);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 610:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(702);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 611:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(703);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 612:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(704);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 613:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(705);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 614:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(706);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 615:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(707);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 616:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(708);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 617:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(655);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 618:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(787);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 619:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(825);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 620:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(789);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 621:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(790);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 622:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(791);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 623:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(792);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 624:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(793);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 625:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(794);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 626:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(795);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 627:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(796);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 628:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(797);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 629:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(798);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 630:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(799);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 631:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(800);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 632:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(801);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 633:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(802);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 634:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(803);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 635:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(326);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 636:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(762);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 637:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(406);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 638:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(635);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 639:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(539);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 640:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(495);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 641:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(496);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 642:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(758);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 643:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(518);
      if (lookahead == 'q') ADVANCE(837);
      if (lookahead == 'x') ADVANCE(726);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 644:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(518);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 645:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(715);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 646:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(831);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 647:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(818);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 648:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(833);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 649:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(834);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 650:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(835);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 651:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(836);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 652:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(544);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 653:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(592);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 654:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(591);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 655:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(593);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 656:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(469);
      if (lookahead == 'q') ADVANCE(840);
      if (lookahead == 's') ADVANCE(814);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 657:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(543);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 658:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(618);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 659:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(620);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 660:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(621);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 661:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(622);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 662:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(623);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 663:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(624);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 664:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(625);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 665:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(626);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 666:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(627);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 667:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(628);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 668:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(629);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 669:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(630);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 670:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(631);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 671:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(632);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 672:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(633);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 673:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(634);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 674:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(490);
      if (lookahead == 'p') ADVANCE(725);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 675:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(258);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 676:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(566);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 677:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(315);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 678:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(312);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 679:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(309);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 680:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(491);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 681:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(492);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 682:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(428);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 683:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(493);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 684:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(811);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 685:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(757);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 686:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(494);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 687:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(497);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 688:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(498);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 689:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(499);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 690:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(820);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 691:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(815);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 692:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(582);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 693:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(567);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 694:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(568);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 695:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(569);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 696:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(570);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 697:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(571);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 698:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(572);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 699:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(573);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 700:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(574);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 701:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(575);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 702:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(576);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 703:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(577);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 704:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(578);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 705:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(579);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 706:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(580);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 707:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(583);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 708:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(581);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 709:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(684);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 710:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(731);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 711:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(737);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 712:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(806);
      if (lookahead == 'u') ADVANCE(638);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 713:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(500);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 714:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(645);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 715:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(677);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 716:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(637);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 717:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(733);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 718:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(678);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 719:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(734);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 720:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(679);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 721:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(716);
      if (lookahead == 'r') ADVANCE(460);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 722:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(716);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 723:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'p') ADVANCE(725);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 724:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'p') ADVANCE(501);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 725:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'p') ADVANCE(515);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 726:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'p') ADVANCE(740);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 727:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'p') ADVANCE(753);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 728:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'q') ADVANCE(838);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 729:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'q') ADVANCE(839);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 730:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(830);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 731:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(321);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 732:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(256);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 733:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(306);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 734:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(303);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 735:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(457);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 736:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(735);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 737:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(507);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 738:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(810);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 739:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(540);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 740:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(542);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 741:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(851);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 742:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(479);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 743:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(742);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 744:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(430);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 745:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(466);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 746:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(853);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 747:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(852);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 748:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(597);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 749:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(470);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 750:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(749);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 751:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(474);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 752:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(854);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 753:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(547);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 754:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(261);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 755:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(336);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 756:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 757:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(260);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 758:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(314);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 759:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(812);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 760:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(598);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 761:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(766);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 762:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(506);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 763:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(814);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 764:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(760);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 765:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(528);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 766:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(588);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 767:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(594);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 768:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(553);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 769:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(600);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 770:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(433);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 771:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(602);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 772:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(603);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 773:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(604);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 774:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(605);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 775:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(606);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 776:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(607);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 777:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(608);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 778:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(609);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 779:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(610);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 780:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(611);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 781:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(612);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 782:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(613);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 783:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(614);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 784:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(615);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 785:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(616);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 786:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(601);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 787:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(769);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 788:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(786);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 789:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(771);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 790:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(772);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 791:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(773);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 792:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(774);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 793:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(775);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 794:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(776);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 795:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(777);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 796:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(778);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 797:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(779);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 798:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(780);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 799:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(781);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 800:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(782);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 801:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(783);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 802:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(784);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 803:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(785);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 804:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(322);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 805:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(488);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 806:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(329);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 807:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(331);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 808:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(334);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 809:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(333);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 810:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(301);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 811:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(462);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 812:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(754);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 813:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(516);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 814:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(748);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 815:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(409);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 816:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(508);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 817:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(523);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 818:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(531);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 819:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 820:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(585);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 821:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(717);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 822:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(465);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 823:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(719);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 824:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(545);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 825:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(551);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 826:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(438);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 827:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(440);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 828:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(724);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 829:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(638);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 830:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(505);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 831:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(519);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 832:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(527);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 833:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(509);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 834:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(510);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 835:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(511);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 836:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(512);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 837:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(467);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 838:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(546);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 839:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(548);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 840:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(549);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 841:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'v') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 842:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'v') ADVANCE(476);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 843:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'v') ADVANCE(480);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 844:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'v') ADVANCE(481);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 845:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'w') ADVANCE(535);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 846:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'x') ADVANCE(586);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 847:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'x') ADVANCE(726);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 848:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'x') ADVANCE(727);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 849:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(302);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 850:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(407);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 851:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(408);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 852:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(411);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 853:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(432);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 854:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(434);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 855:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(435);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 856:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(437);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    case 857:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(857);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 2},
  [2] = {.lex_state = 9},
  [3] = {.lex_state = 9},
  [4] = {.lex_state = 9},
  [5] = {.lex_state = 9},
  [6] = {.lex_state = 9},
  [7] = {.lex_state = 9},
  [8] = {.lex_state = 9},
  [9] = {.lex_state = 10},
  [10] = {.lex_state = 10},
  [11] = {.lex_state = 10},
  [12] = {.lex_state = 10},
  [13] = {.lex_state = 10},
  [14] = {.lex_state = 11},
  [15] = {.lex_state = 11},
  [16] = {.lex_state = 11},
  [17] = {.lex_state = 10},
  [18] = {.lex_state = 12},
  [19] = {.lex_state = 12},
  [20] = {.lex_state = 13},
  [21] = {.lex_state = 13},
  [22] = {.lex_state = 13},
  [23] = {.lex_state = 12},
  [24] = {.lex_state = 13},
  [25] = {.lex_state = 12},
  [26] = {.lex_state = 12},
  [27] = {.lex_state = 12},
  [28] = {.lex_state = 13},
  [29] = {.lex_state = 13},
  [30] = {.lex_state = 13},
  [31] = {.lex_state = 13},
  [32] = {.lex_state = 12},
  [33] = {.lex_state = 13},
  [34] = {.lex_state = 13},
  [35] = {.lex_state = 13},
  [36] = {.lex_state = 13},
  [37] = {.lex_state = 12},
  [38] = {.lex_state = 12},
  [39] = {.lex_state = 12},
  [40] = {.lex_state = 12},
  [41] = {.lex_state = 238},
  [42] = {.lex_state = 238},
  [43] = {.lex_state = 238},
  [44] = {.lex_state = 238},
  [45] = {.lex_state = 238},
  [46] = {.lex_state = 14},
  [47] = {.lex_state = 14},
  [48] = {.lex_state = 14},
  [49] = {.lex_state = 14},
  [50] = {.lex_state = 14},
  [51] = {.lex_state = 14},
  [52] = {.lex_state = 14},
  [53] = {.lex_state = 14},
  [54] = {.lex_state = 14},
  [55] = {.lex_state = 14},
  [56] = {.lex_state = 14},
  [57] = {.lex_state = 14},
  [58] = {.lex_state = 20},
  [59] = {.lex_state = 19},
  [60] = {.lex_state = 19},
  [61] = {.lex_state = 236},
  [62] = {.lex_state = 19},
  [63] = {.lex_state = 19},
  [64] = {.lex_state = 236},
  [65] = {.lex_state = 19},
  [66] = {.lex_state = 20},
  [67] = {.lex_state = 236},
  [68] = {.lex_state = 20},
  [69] = {.lex_state = 20},
  [70] = {.lex_state = 20},
  [71] = {.lex_state = 236},
  [72] = {.lex_state = 236},
  [73] = {.lex_state = 236},
  [74] = {.lex_state = 236},
  [75] = {.lex_state = 236},
  [76] = {.lex_state = 8},
  [77] = {.lex_state = 8},
  [78] = {.lex_state = 236},
  [79] = {.lex_state = 236},
  [80] = {.lex_state = 236},
  [81] = {.lex_state = 236},
  [82] = {.lex_state = 8},
  [83] = {.lex_state = 6},
  [84] = {.lex_state = 4},
  [85] = {.lex_state = 6},
  [86] = {.lex_state = 237},
  [87] = {.lex_state = 237},
  [88] = {.lex_state = 6},
  [89] = {.lex_state = 4},
  [90] = {.lex_state = 4},
  [91] = {.lex_state = 16},
  [92] = {.lex_state = 2},
  [93] = {.lex_state = 15},
  [94] = {.lex_state = 237},
  [95] = {.lex_state = 237},
  [96] = {.lex_state = 237},
  [97] = {.lex_state = 2},
  [98] = {.lex_state = 2},
  [99] = {.lex_state = 2},
  [100] = {.lex_state = 2},
  [101] = {.lex_state = 237},
  [102] = {.lex_state = 237},
  [103] = {.lex_state = 237},
  [104] = {.lex_state = 15},
  [105] = {.lex_state = 237},
  [106] = {.lex_state = 237},
  [107] = {.lex_state = 237},
  [108] = {.lex_state = 15},
  [109] = {.lex_state = 15},
  [110] = {.lex_state = 237},
  [111] = {.lex_state = 15},
  [112] = {.lex_state = 15},
  [113] = {.lex_state = 15},
  [114] = {.lex_state = 15},
  [115] = {.lex_state = 16},
  [116] = {.lex_state = 15},
  [117] = {.lex_state = 15},
  [118] = {.lex_state = 15},
  [119] = {.lex_state = 6},
  [120] = {.lex_state = 15},
  [121] = {.lex_state = 15},
  [122] = {.lex_state = 237},
  [123] = {.lex_state = 15},
  [124] = {.lex_state = 15},
  [125] = {.lex_state = 237},
  [126] = {.lex_state = 4},
  [127] = {.lex_state = 4},
  [128] = {.lex_state = 237},
  [129] = {.lex_state = 16},
  [130] = {.lex_state = 237},
  [131] = {.lex_state = 237},
  [132] = {.lex_state = 4},
  [133] = {.lex_state = 15},
  [134] = {.lex_state = 237},
  [135] = {.lex_state = 6},
  [136] = {.lex_state = 237},
  [137] = {.lex_state = 6},
  [138] = {.lex_state = 15},
  [139] = {.lex_state = 15},
  [140] = {.lex_state = 237},
  [141] = {.lex_state = 15},
  [142] = {.lex_state = 4},
  [143] = {.lex_state = 6},
  [144] = {.lex_state = 6},
  [145] = {.lex_state = 4},
  [146] = {.lex_state = 6},
  [147] = {.lex_state = 6},
  [148] = {.lex_state = 4},
  [149] = {.lex_state = 6},
  [150] = {.lex_state = 4},
  [151] = {.lex_state = 2},
  [152] = {.lex_state = 4},
  [153] = {.lex_state = 4},
  [154] = {.lex_state = 6},
  [155] = {.lex_state = 7},
  [156] = {.lex_state = 3},
  [157] = {.lex_state = 5},
  [158] = {.lex_state = 3},
  [159] = {.lex_state = 3},
  [160] = {.lex_state = 5},
  [161] = {.lex_state = 3},
  [162] = {.lex_state = 7},
  [163] = {.lex_state = 7},
  [164] = {.lex_state = 7},
  [165] = {.lex_state = 7},
  [166] = {.lex_state = 5},
  [167] = {.lex_state = 7},
  [168] = {.lex_state = 7},
  [169] = {.lex_state = 7},
  [170] = {.lex_state = 7},
  [171] = {.lex_state = 7},
  [172] = {.lex_state = 5},
  [173] = {.lex_state = 5},
  [174] = {.lex_state = 7},
  [175] = {.lex_state = 7},
  [176] = {.lex_state = 7},
  [177] = {.lex_state = 5},
  [178] = {.lex_state = 7},
  [179] = {.lex_state = 7},
  [180] = {.lex_state = 7},
  [181] = {.lex_state = 7},
  [182] = {.lex_state = 7},
  [183] = {.lex_state = 17},
  [184] = {.lex_state = 5},
  [185] = {.lex_state = 5},
  [186] = {.lex_state = 5},
  [187] = {.lex_state = 5},
  [188] = {.lex_state = 5},
  [189] = {.lex_state = 7},
  [190] = {.lex_state = 5},
  [191] = {.lex_state = 5},
  [192] = {.lex_state = 5},
  [193] = {.lex_state = 5},
  [194] = {.lex_state = 5},
  [195] = {.lex_state = 5},
  [196] = {.lex_state = 5},
  [197] = {.lex_state = 5},
  [198] = {.lex_state = 7},
  [199] = {.lex_state = 5},
  [200] = {.lex_state = 235},
  [201] = {.lex_state = 235},
  [202] = {.lex_state = 3},
  [203] = {.lex_state = 235},
  [204] = {.lex_state = 235},
  [205] = {.lex_state = 235},
  [206] = {.lex_state = 235},
  [207] = {.lex_state = 235},
  [208] = {.lex_state = 235},
  [209] = {.lex_state = 235},
  [210] = {.lex_state = 235},
  [211] = {.lex_state = 235},
  [212] = {.lex_state = 235},
  [213] = {.lex_state = 235},
  [214] = {.lex_state = 235},
  [215] = {.lex_state = 235},
  [216] = {.lex_state = 239},
  [217] = {.lex_state = 3},
  [218] = {.lex_state = 239},
  [219] = {.lex_state = 3},
  [220] = {.lex_state = 3},
  [221] = {.lex_state = 239},
  [222] = {.lex_state = 239},
  [223] = {.lex_state = 3},
  [224] = {.lex_state = 239},
  [225] = {.lex_state = 239},
  [226] = {.lex_state = 239},
  [227] = {.lex_state = 239},
  [228] = {.lex_state = 239},
  [229] = {.lex_state = 239},
  [230] = {.lex_state = 239},
  [231] = {.lex_state = 239},
  [232] = {.lex_state = 239},
  [233] = {.lex_state = 21},
  [234] = {.lex_state = 238},
  [235] = {.lex_state = 21},
  [236] = {.lex_state = 238},
  [237] = {.lex_state = 24},
  [238] = {.lex_state = 21},
  [239] = {.lex_state = 21},
  [240] = {.lex_state = 239},
  [241] = {.lex_state = 24},
  [242] = {.lex_state = 24},
  [243] = {.lex_state = 238},
  [244] = {.lex_state = 21},
  [245] = {.lex_state = 239},
  [246] = {.lex_state = 21},
  [247] = {.lex_state = 3},
  [248] = {.lex_state = 239},
  [249] = {.lex_state = 24},
  [250] = {.lex_state = 24},
  [251] = {.lex_state = 24},
  [252] = {.lex_state = 239},
  [253] = {.lex_state = 239},
  [254] = {.lex_state = 239},
  [255] = {.lex_state = 239},
  [256] = {.lex_state = 239},
  [257] = {.lex_state = 239},
  [258] = {.lex_state = 239},
  [259] = {.lex_state = 239},
  [260] = {.lex_state = 239},
  [261] = {.lex_state = 239},
  [262] = {.lex_state = 239},
  [263] = {.lex_state = 239},
  [264] = {.lex_state = 239},
  [265] = {.lex_state = 239},
  [266] = {.lex_state = 239},
  [267] = {.lex_state = 239},
  [268] = {.lex_state = 239},
  [269] = {.lex_state = 239},
  [270] = {.lex_state = 239},
  [271] = {.lex_state = 239},
  [272] = {.lex_state = 238},
  [273] = {.lex_state = 239},
  [274] = {.lex_state = 239},
  [275] = {.lex_state = 239},
  [276] = {.lex_state = 238},
  [277] = {.lex_state = 239},
  [278] = {.lex_state = 239},
  [279] = {.lex_state = 239},
  [280] = {.lex_state = 238},
  [281] = {.lex_state = 239},
  [282] = {.lex_state = 24},
  [283] = {.lex_state = 238},
  [284] = {.lex_state = 24},
  [285] = {.lex_state = 8},
  [286] = {.lex_state = 24},
  [287] = {.lex_state = 21},
  [288] = {.lex_state = 24},
  [289] = {.lex_state = 24},
  [290] = {.lex_state = 8},
  [291] = {.lex_state = 3},
  [292] = {.lex_state = 24},
  [293] = {.lex_state = 24},
  [294] = {.lex_state = 21},
  [295] = {.lex_state = 21},
  [296] = {.lex_state = 8},
  [297] = {.lex_state = 21},
  [298] = {.lex_state = 21},
  [299] = {.lex_state = 21},
  [300] = {.lex_state = 21},
  [301] = {.lex_state = 238},
  [302] = {.lex_state = 238},
  [303] = {.lex_state = 238},
  [304] = {.lex_state = 21},
  [305] = {.lex_state = 19},
  [306] = {.lex_state = 238},
  [307] = {.lex_state = 20},
  [308] = {.lex_state = 238},
  [309] = {.lex_state = 238},
  [310] = {.lex_state = 238},
  [311] = {.lex_state = 238},
  [312] = {.lex_state = 238},
  [313] = {.lex_state = 238},
  [314] = {.lex_state = 14},
  [315] = {.lex_state = 238},
  [316] = {.lex_state = 238},
  [317] = {.lex_state = 238},
  [318] = {.lex_state = 238},
  [319] = {.lex_state = 19},
  [320] = {.lex_state = 238},
  [321] = {.lex_state = 238},
  [322] = {.lex_state = 238},
  [323] = {.lex_state = 238},
  [324] = {.lex_state = 238},
  [325] = {.lex_state = 238},
  [326] = {.lex_state = 238},
  [327] = {.lex_state = 238},
  [328] = {.lex_state = 238},
  [329] = {.lex_state = 238},
  [330] = {.lex_state = 21},
  [331] = {.lex_state = 238},
  [332] = {.lex_state = 8},
  [333] = {.lex_state = 19},
  [334] = {.lex_state = 8},
  [335] = {.lex_state = 20},
  [336] = {.lex_state = 238},
  [337] = {.lex_state = 238},
  [338] = {.lex_state = 238},
  [339] = {.lex_state = 20},
  [340] = {.lex_state = 238},
  [341] = {.lex_state = 238},
  [342] = {.lex_state = 238},
  [343] = {.lex_state = 238},
  [344] = {.lex_state = 238},
  [345] = {.lex_state = 238},
  [346] = {.lex_state = 24},
  [347] = {.lex_state = 24},
  [348] = {.lex_state = 238},
  [349] = {.lex_state = 238},
  [350] = {.lex_state = 238},
  [351] = {.lex_state = 238},
  [352] = {.lex_state = 238},
  [353] = {.lex_state = 238},
  [354] = {.lex_state = 238},
  [355] = {.lex_state = 24},
  [356] = {.lex_state = 238},
  [357] = {.lex_state = 238},
  [358] = {.lex_state = 238},
  [359] = {.lex_state = 21},
  [360] = {.lex_state = 8},
  [361] = {.lex_state = 21},
  [362] = {.lex_state = 21},
  [363] = {.lex_state = 24},
  [364] = {.lex_state = 24},
  [365] = {.lex_state = 24},
  [366] = {.lex_state = 24},
  [367] = {.lex_state = 24},
  [368] = {.lex_state = 20},
  [369] = {.lex_state = 24},
  [370] = {.lex_state = 24},
  [371] = {.lex_state = 20},
  [372] = {.lex_state = 21},
  [373] = {.lex_state = 24},
  [374] = {.lex_state = 21},
  [375] = {.lex_state = 21},
  [376] = {.lex_state = 21},
  [377] = {.lex_state = 24},
  [378] = {.lex_state = 21},
  [379] = {.lex_state = 21},
  [380] = {.lex_state = 21},
  [381] = {.lex_state = 21},
  [382] = {.lex_state = 21},
  [383] = {.lex_state = 21},
  [384] = {.lex_state = 21},
  [385] = {.lex_state = 21},
  [386] = {.lex_state = 21},
  [387] = {.lex_state = 21},
  [388] = {.lex_state = 21},
  [389] = {.lex_state = 21},
  [390] = {.lex_state = 21},
  [391] = {.lex_state = 21},
  [392] = {.lex_state = 21},
  [393] = {.lex_state = 21},
  [394] = {.lex_state = 21},
  [395] = {.lex_state = 24},
  [396] = {.lex_state = 24},
  [397] = {.lex_state = 24},
  [398] = {.lex_state = 24},
  [399] = {.lex_state = 24},
  [400] = {.lex_state = 24},
  [401] = {.lex_state = 24},
  [402] = {.lex_state = 24},
  [403] = {.lex_state = 24},
  [404] = {.lex_state = 24},
  [405] = {.lex_state = 24},
  [406] = {.lex_state = 24},
  [407] = {.lex_state = 24},
  [408] = {.lex_state = 24},
  [409] = {.lex_state = 20},
  [410] = {.lex_state = 24},
  [411] = {.lex_state = 21},
  [412] = {.lex_state = 24},
  [413] = {.lex_state = 24},
  [414] = {.lex_state = 24},
  [415] = {.lex_state = 19},
  [416] = {.lex_state = 19},
  [417] = {.lex_state = 21},
  [418] = {.lex_state = 19},
  [419] = {.lex_state = 21},
  [420] = {.lex_state = 21},
  [421] = {.lex_state = 20},
  [422] = {.lex_state = 15},
  [423] = {.lex_state = 236},
  [424] = {.lex_state = 236},
  [425] = {.lex_state = 19},
  [426] = {.lex_state = 15},
  [427] = {.lex_state = 236},
  [428] = {.lex_state = 236},
  [429] = {.lex_state = 20},
  [430] = {.lex_state = 19},
  [431] = {.lex_state = 20},
  [432] = {.lex_state = 19},
  [433] = {.lex_state = 19},
  [434] = {.lex_state = 20},
  [435] = {.lex_state = 20},
  [436] = {.lex_state = 20},
  [437] = {.lex_state = 20},
  [438] = {.lex_state = 20},
  [439] = {.lex_state = 20},
  [440] = {.lex_state = 19},
  [441] = {.lex_state = 20},
  [442] = {.lex_state = 19},
  [443] = {.lex_state = 20},
  [444] = {.lex_state = 19},
  [445] = {.lex_state = 19},
  [446] = {.lex_state = 19},
  [447] = {.lex_state = 20},
  [448] = {.lex_state = 19},
  [449] = {.lex_state = 19},
  [450] = {.lex_state = 20},
  [451] = {.lex_state = 19},
  [452] = {.lex_state = 19},
  [453] = {.lex_state = 20},
  [454] = {.lex_state = 20},
  [455] = {.lex_state = 20},
  [456] = {.lex_state = 20},
  [457] = {.lex_state = 19},
  [458] = {.lex_state = 19},
  [459] = {.lex_state = 19},
  [460] = {.lex_state = 19},
  [461] = {.lex_state = 20},
  [462] = {.lex_state = 19},
  [463] = {.lex_state = 19},
  [464] = {.lex_state = 20},
  [465] = {.lex_state = 19},
  [466] = {.lex_state = 20},
  [467] = {.lex_state = 19},
  [468] = {.lex_state = 19},
  [469] = {.lex_state = 19},
  [470] = {.lex_state = 20},
  [471] = {.lex_state = 19},
  [472] = {.lex_state = 19},
  [473] = {.lex_state = 19},
  [474] = {.lex_state = 20},
  [475] = {.lex_state = 20},
  [476] = {.lex_state = 19},
  [477] = {.lex_state = 19},
  [478] = {.lex_state = 20},
  [479] = {.lex_state = 20},
  [480] = {.lex_state = 20},
  [481] = {.lex_state = 20},
  [482] = {.lex_state = 20},
  [483] = {.lex_state = 20},
  [484] = {.lex_state = 20},
  [485] = {.lex_state = 19},
  [486] = {.lex_state = 19},
  [487] = {.lex_state = 19},
  [488] = {.lex_state = 20},
  [489] = {.lex_state = 20},
  [490] = {.lex_state = 19},
  [491] = {.lex_state = 20},
  [492] = {.lex_state = 19},
  [493] = {.lex_state = 19},
  [494] = {.lex_state = 20},
  [495] = {.lex_state = 19},
  [496] = {.lex_state = 19},
  [497] = {.lex_state = 20},
  [498] = {.lex_state = 20},
  [499] = {.lex_state = 19},
  [500] = {.lex_state = 20},
  [501] = {.lex_state = 19},
  [502] = {.lex_state = 19},
  [503] = {.lex_state = 19},
  [504] = {.lex_state = 20},
  [505] = {.lex_state = 20},
  [506] = {.lex_state = 19},
  [507] = {.lex_state = 20},
  [508] = {.lex_state = 19},
  [509] = {.lex_state = 20},
  [510] = {.lex_state = 20},
  [511] = {.lex_state = 19},
  [512] = {.lex_state = 20},
  [513] = {.lex_state = 20},
  [514] = {.lex_state = 20},
  [515] = {.lex_state = 19},
  [516] = {.lex_state = 19},
  [517] = {.lex_state = 0},
  [518] = {.lex_state = 0},
  [519] = {.lex_state = 0},
  [520] = {.lex_state = 0},
  [521] = {.lex_state = 0},
  [522] = {.lex_state = 0},
  [523] = {.lex_state = 0},
  [524] = {.lex_state = 0},
  [525] = {.lex_state = 0},
  [526] = {.lex_state = 0},
  [527] = {.lex_state = 0},
  [528] = {.lex_state = 2},
  [529] = {.lex_state = 2},
  [530] = {.lex_state = 2},
  [531] = {.lex_state = 2},
  [532] = {.lex_state = 2},
  [533] = {.lex_state = 2},
  [534] = {.lex_state = 2},
  [535] = {.lex_state = 2},
  [536] = {.lex_state = 2},
  [537] = {.lex_state = 2},
  [538] = {.lex_state = 2},
  [539] = {.lex_state = 2},
  [540] = {.lex_state = 2},
  [541] = {.lex_state = 2},
  [542] = {.lex_state = 2},
  [543] = {.lex_state = 2},
  [544] = {.lex_state = 2},
  [545] = {.lex_state = 2},
  [546] = {.lex_state = 2},
  [547] = {.lex_state = 2},
  [548] = {.lex_state = 2},
  [549] = {.lex_state = 2},
  [550] = {.lex_state = 2},
  [551] = {.lex_state = 2},
  [552] = {.lex_state = 2},
  [553] = {.lex_state = 2},
  [554] = {.lex_state = 2},
  [555] = {.lex_state = 29},
  [556] = {.lex_state = 29},
  [557] = {.lex_state = 30},
  [558] = {.lex_state = 30},
  [559] = {.lex_state = 0},
  [560] = {.lex_state = 31},
  [561] = {.lex_state = 30},
  [562] = {.lex_state = 29},
  [563] = {.lex_state = 31},
  [564] = {.lex_state = 31},
  [565] = {.lex_state = 1},
  [566] = {.lex_state = 1},
  [567] = {.lex_state = 2},
  [568] = {.lex_state = 1},
  [569] = {.lex_state = 1},
  [570] = {.lex_state = 1},
  [571] = {.lex_state = 2},
  [572] = {.lex_state = 0},
  [573] = {.lex_state = 1},
  [574] = {.lex_state = 32},
  [575] = {.lex_state = 32},
  [576] = {.lex_state = 32},
  [577] = {.lex_state = 1},
  [578] = {.lex_state = 1},
  [579] = {.lex_state = 2},
  [580] = {.lex_state = 2},
  [581] = {.lex_state = 1},
  [582] = {.lex_state = 1},
  [583] = {.lex_state = 1},
  [584] = {.lex_state = 1},
  [585] = {.lex_state = 1},
  [586] = {.lex_state = 1},
  [587] = {.lex_state = 1},
  [588] = {.lex_state = 1},
  [589] = {.lex_state = 1},
  [590] = {.lex_state = 1},
  [591] = {.lex_state = 1},
  [592] = {.lex_state = 1},
  [593] = {.lex_state = 1},
  [594] = {.lex_state = 1},
  [595] = {.lex_state = 2},
  [596] = {.lex_state = 2},
  [597] = {.lex_state = 0},
  [598] = {.lex_state = 2},
  [599] = {.lex_state = 0},
  [600] = {.lex_state = 2},
  [601] = {.lex_state = 2},
  [602] = {.lex_state = 0},
  [603] = {.lex_state = 2},
  [604] = {.lex_state = 2},
  [605] = {.lex_state = 2},
  [606] = {.lex_state = 2},
  [607] = {.lex_state = 31},
  [608] = {.lex_state = 0},
  [609] = {.lex_state = 0},
  [610] = {.lex_state = 2},
  [611] = {.lex_state = 0},
  [612] = {.lex_state = 0},
  [613] = {.lex_state = 2},
  [614] = {.lex_state = 0},
  [615] = {.lex_state = 2},
  [616] = {.lex_state = 2},
  [617] = {.lex_state = 2},
  [618] = {.lex_state = 2},
  [619] = {.lex_state = 0},
  [620] = {.lex_state = 31},
  [621] = {.lex_state = 1},
  [622] = {.lex_state = 2},
  [623] = {.lex_state = 31},
  [624] = {.lex_state = 0},
  [625] = {.lex_state = 2},
  [626] = {.lex_state = 2},
  [627] = {.lex_state = 0},
  [628] = {.lex_state = 2},
  [629] = {.lex_state = 2},
  [630] = {.lex_state = 0},
  [631] = {.lex_state = 0},
  [632] = {.lex_state = 0},
  [633] = {.lex_state = 0},
  [634] = {.lex_state = 0},
  [635] = {.lex_state = 2},
  [636] = {.lex_state = 0},
  [637] = {.lex_state = 0},
  [638] = {.lex_state = 2},
  [639] = {.lex_state = 2},
  [640] = {.lex_state = 31},
  [641] = {.lex_state = 235},
  [642] = {.lex_state = 2},
  [643] = {.lex_state = 2},
  [644] = {.lex_state = 2},
  [645] = {.lex_state = 0},
  [646] = {.lex_state = 2},
  [647] = {.lex_state = 31},
  [648] = {.lex_state = 31},
  [649] = {.lex_state = 31},
  [650] = {.lex_state = 31},
  [651] = {.lex_state = 31},
  [652] = {.lex_state = 31},
  [653] = {.lex_state = 31},
  [654] = {.lex_state = 2},
  [655] = {.lex_state = 2},
  [656] = {.lex_state = 2},
  [657] = {.lex_state = 2},
  [658] = {.lex_state = 2},
  [659] = {.lex_state = 2},
  [660] = {.lex_state = 2},
  [661] = {.lex_state = 2},
  [662] = {.lex_state = 31},
  [663] = {.lex_state = 2},
  [664] = {.lex_state = 31},
  [665] = {.lex_state = 2},
  [666] = {.lex_state = 2},
  [667] = {.lex_state = 31},
  [668] = {.lex_state = 31},
  [669] = {.lex_state = 31},
  [670] = {.lex_state = 2},
  [671] = {.lex_state = 2},
  [672] = {.lex_state = 31},
  [673] = {.lex_state = 31},
  [674] = {.lex_state = 2},
  [675] = {.lex_state = 2},
  [676] = {.lex_state = 2},
  [677] = {.lex_state = 2},
  [678] = {.lex_state = 2},
  [679] = {.lex_state = 0},
  [680] = {.lex_state = 235},
  [681] = {.lex_state = 2},
  [682] = {.lex_state = 0},
  [683] = {.lex_state = 0},
  [684] = {.lex_state = 235},
  [685] = {.lex_state = 2},
  [686] = {.lex_state = 2},
  [687] = {.lex_state = 0},
  [688] = {.lex_state = 0},
  [689] = {.lex_state = 2},
  [690] = {.lex_state = 2},
  [691] = {.lex_state = 0},
  [692] = {.lex_state = 0},
  [693] = {.lex_state = 0},
  [694] = {.lex_state = 2},
  [695] = {.lex_state = 235},
  [696] = {.lex_state = 0},
  [697] = {.lex_state = 0},
  [698] = {.lex_state = 0},
  [699] = {.lex_state = 28},
  [700] = {.lex_state = 0},
  [701] = {.lex_state = 0},
  [702] = {.lex_state = 28},
  [703] = {.lex_state = 0},
  [704] = {.lex_state = 0},
  [705] = {.lex_state = 0},
  [706] = {.lex_state = 28},
  [707] = {.lex_state = 0},
  [708] = {.lex_state = 0},
  [709] = {.lex_state = 0},
  [710] = {.lex_state = 0},
  [711] = {.lex_state = 0},
  [712] = {.lex_state = 2},
  [713] = {.lex_state = 2},
  [714] = {.lex_state = 2},
  [715] = {.lex_state = 0},
  [716] = {.lex_state = 0},
  [717] = {.lex_state = 2},
  [718] = {.lex_state = 235},
  [719] = {.lex_state = 235},
  [720] = {.lex_state = 235},
  [721] = {.lex_state = 2},
  [722] = {.lex_state = 2},
  [723] = {.lex_state = 9},
  [724] = {.lex_state = 235},
  [725] = {.lex_state = 235},
  [726] = {.lex_state = 235},
  [727] = {.lex_state = 0},
  [728] = {.lex_state = 9},
  [729] = {.lex_state = 235},
  [730] = {.lex_state = 0},
  [731] = {.lex_state = 9},
  [732] = {.lex_state = 9},
  [733] = {.lex_state = 9},
  [734] = {.lex_state = 0},
  [735] = {.lex_state = 0},
  [736] = {.lex_state = 235},
  [737] = {.lex_state = 9},
  [738] = {.lex_state = 235},
  [739] = {.lex_state = 0},
  [740] = {.lex_state = 235},
  [741] = {.lex_state = 235},
  [742] = {.lex_state = 235},
  [743] = {.lex_state = 0},
  [744] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_LPAREN_RPAREN] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [anon_sym_matches] = ACTIONS(1),
    [anon_sym_after] = ACTIONS(1),
    [anon_sym_before] = ACTIONS(1),
    [anon_sym_between] = ACTIONS(1),
    [anon_sym_and] = ACTIONS(1),
    [anon_sym_contains] = ACTIONS(1),
    [anon_sym_exists] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [sym_pos_int] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_DQUOTE_DQUOTE] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [anon_sym_ERROR_missing_query_start] = ACTIONS(1),
    [anon_sym_ERROR_missing_query_body] = ACTIONS(1),
    [anon_sym_ERROR_missing_main_iterator] = ACTIONS(1),
    [anon_sym_ERROR_missing_array_query_end] = ACTIONS(1),
    [anon_sym_ERROR_missing_element_query_end] = ACTIONS(1),
    [anon_sym_ERROR_missing_iterator] = ACTIONS(1),
    [anon_sym_ERROR_missing_update_field] = ACTIONS(1),
    [anon_sym_ERROR_missing_delete_field] = ACTIONS(1),
    [anon_sym_ERROR_missing_filter_expression] = ACTIONS(1),
    [anon_sym_ERROR_missing_offset_value] = ACTIONS(1),
    [anon_sym_ERROR_missing_limit_value] = ACTIONS(1),
    [anon_sym_ERROR_missing_expression] = ACTIONS(1),
    [anon_sym_ERROR_missing_bool_value] = ACTIONS(1),
    [anon_sym_ERROR_missing_equals] = ACTIONS(1),
    [anon_sym_ERROR_missing_colon] = ACTIONS(1),
    [anon_sym_ERROR_missing_value] = ACTIONS(1),
    [anon_sym_ERROR_missing_brace_end] = ACTIONS(1),
    [anon_sym_ERROR_missing_array_end] = ACTIONS(1),
    [anon_sym_ERROR_missing_parenthesis_end] = ACTIONS(1),
    [anon_sym_ERROR_missing_string_end] = ACTIONS(1),
    [anon_sym_for] = ACTIONS(1),
    [anon_sym_let] = ACTIONS(1),
    [anon_sym_in] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
    [sym_null] = ACTIONS(1),
    [anon_sym_and2] = ACTIONS(1),
    [anon_sym_or] = ACTIONS(1),
    [anon_sym_not] = ACTIONS(1),
    [anon_sym_if] = ACTIONS(1),
    [anon_sym_set] = ACTIONS(1),
    [anon_sym_delete] = ACTIONS(1),
    [anon_sym_offset] = ACTIONS(1),
    [anon_sym_limit] = ACTIONS(1),
    [anon_sym_append] = ACTIONS(1),
    [anon_sym_values] = ACTIONS(1),
    [aux_sym_ident_token1] = ACTIONS(1),
  },
  [1] = {
    [sym_start] = STATE(734),
    [sym__query] = STATE(744),
    [sym_array_query] = STATE(744),
    [sym_element_query] = STATE(744),
    [sym__missing_query] = STATE(743),
    [sym_missing_query_start] = STATE(47),
    [anon_sym_LBRACK] = ACTIONS(3),
    [anon_sym_LPAREN] = ACTIONS(5),
    [anon_sym_ERROR_missing_query_start] = ACTIONS(7),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 24,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(247), 2,
      sym_path,
      sym_string,
    STATE(688), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(219), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(530), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [92] = 24,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(247), 2,
      sym_path,
      sym_string,
    STATE(701), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(217), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(538), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [184] = 24,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(247), 2,
      sym_path,
      sym_string,
    STATE(701), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(217), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(529), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [276] = 24,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(247), 2,
      sym_path,
      sym_string,
    STATE(701), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(217), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(531), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [368] = 24,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(247), 2,
      sym_path,
      sym_string,
    STATE(701), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(217), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(530), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [460] = 24,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(247), 2,
      sym_path,
      sym_string,
    STATE(698), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(220), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(529), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [552] = 24,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(247), 2,
      sym_path,
      sym_string,
    STATE(707), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(223), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(531), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [644] = 21,
    ACTIONS(37), 1,
      anon_sym_LBRACK,
    ACTIONS(39), 1,
      anon_sym_LPAREN,
    ACTIONS(41), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    ACTIONS(49), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(51), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(53), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(55), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(57), 1,
      anon_sym_not,
    ACTIONS(59), 1,
      aux_sym_ident_token1,
    STATE(22), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(132), 1,
      sym_missing_identifier,
    STATE(153), 1,
      sym_missing_string_end,
    STATE(449), 1,
      sym_missing_expression,
    STATE(150), 2,
      sym_path,
      sym_string,
    STATE(190), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(47), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(160), 4,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(244), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [724] = 21,
    ACTIONS(37), 1,
      anon_sym_LBRACK,
    ACTIONS(39), 1,
      anon_sym_LPAREN,
    ACTIONS(41), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    ACTIONS(49), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(51), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(53), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(55), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(57), 1,
      anon_sym_not,
    ACTIONS(59), 1,
      aux_sym_ident_token1,
    STATE(22), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(132), 1,
      sym_missing_identifier,
    STATE(153), 1,
      sym_missing_string_end,
    STATE(446), 1,
      sym_missing_expression,
    STATE(150), 2,
      sym_path,
      sym_string,
    STATE(187), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(47), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(157), 4,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(235), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [804] = 21,
    ACTIONS(61), 1,
      anon_sym_LBRACK,
    ACTIONS(63), 1,
      anon_sym_LPAREN,
    ACTIONS(65), 1,
      anon_sym_LBRACE,
    ACTIONS(67), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(73), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(75), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(77), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(79), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(81), 1,
      anon_sym_not,
    ACTIONS(83), 1,
      aux_sym_ident_token1,
    STATE(24), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(137), 1,
      sym_missing_identifier,
    STATE(144), 1,
      sym_missing_string_end,
    STATE(500), 1,
      sym_missing_expression,
    STATE(146), 2,
      sym_path,
      sym_string,
    STATE(178), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(71), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(162), 4,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(251), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [884] = 21,
    ACTIONS(61), 1,
      anon_sym_LBRACK,
    ACTIONS(63), 1,
      anon_sym_LPAREN,
    ACTIONS(65), 1,
      anon_sym_LBRACE,
    ACTIONS(67), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(73), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(75), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(77), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(79), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(81), 1,
      anon_sym_not,
    ACTIONS(83), 1,
      aux_sym_ident_token1,
    STATE(24), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(137), 1,
      sym_missing_identifier,
    STATE(144), 1,
      sym_missing_string_end,
    STATE(437), 1,
      sym_missing_expression,
    STATE(146), 2,
      sym_path,
      sym_string,
    STATE(198), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(71), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(155), 4,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(242), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [964] = 21,
    ACTIONS(85), 1,
      anon_sym_LBRACK,
    ACTIONS(87), 1,
      anon_sym_LPAREN,
    ACTIONS(89), 1,
      anon_sym_LBRACE,
    ACTIONS(91), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(93), 1,
      anon_sym_DQUOTE,
    ACTIONS(97), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(99), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(101), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(103), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(105), 1,
      anon_sym_not,
    ACTIONS(107), 1,
      aux_sym_ident_token1,
    STATE(21), 1,
      sym__not,
    STATE(61), 1,
      sym_ident,
    STATE(71), 1,
      sym_missing_identifier,
    STATE(79), 1,
      sym_missing_string_end,
    STATE(315), 1,
      sym_missing_expression,
    STATE(74), 2,
      sym_path,
      sym_string,
    STATE(122), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(95), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(86), 4,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(216), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1044] = 20,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    ACTIONS(51), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(53), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(55), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(57), 1,
      anon_sym_not,
    ACTIONS(59), 1,
      aux_sym_ident_token1,
    ACTIONS(109), 1,
      anon_sym_LPAREN,
    ACTIONS(113), 1,
      anon_sym_ERROR_missing_filter_expression,
    STATE(22), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(132), 1,
      sym_missing_identifier,
    STATE(153), 1,
      sym_missing_string_end,
    STATE(472), 1,
      sym_missing_filter_expression,
    STATE(142), 2,
      sym_path,
      sym_string,
    ACTIONS(111), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(423), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(246), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1122] = 20,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(91), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(93), 1,
      anon_sym_DQUOTE,
    ACTIONS(99), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(101), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(103), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(105), 1,
      anon_sym_not,
    ACTIONS(107), 1,
      aux_sym_ident_token1,
    ACTIONS(115), 1,
      anon_sym_LPAREN,
    ACTIONS(119), 1,
      anon_sym_ERROR_missing_filter_expression,
    STATE(21), 1,
      sym__not,
    STATE(61), 1,
      sym_ident,
    STATE(71), 1,
      sym_missing_identifier,
    STATE(79), 1,
      sym_missing_string_end,
    STATE(323), 1,
      sym_missing_filter_expression,
    STATE(80), 2,
      sym_path,
      sym_string,
    ACTIONS(117), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(427), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(218), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1200] = 20,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(67), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(75), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(77), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(79), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(81), 1,
      anon_sym_not,
    ACTIONS(83), 1,
      aux_sym_ident_token1,
    ACTIONS(121), 1,
      anon_sym_LPAREN,
    ACTIONS(125), 1,
      anon_sym_ERROR_missing_filter_expression,
    STATE(24), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(137), 1,
      sym_missing_identifier,
    STATE(144), 1,
      sym_missing_string_end,
    STATE(491), 1,
      sym_missing_filter_expression,
    STATE(149), 2,
      sym_path,
      sym_string,
    ACTIONS(123), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(424), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(237), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1278] = 21,
    ACTIONS(85), 1,
      anon_sym_LBRACK,
    ACTIONS(87), 1,
      anon_sym_LPAREN,
    ACTIONS(89), 1,
      anon_sym_LBRACE,
    ACTIONS(91), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(93), 1,
      anon_sym_DQUOTE,
    ACTIONS(97), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(99), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(101), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(103), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(105), 1,
      anon_sym_not,
    ACTIONS(107), 1,
      aux_sym_ident_token1,
    STATE(21), 1,
      sym__not,
    STATE(61), 1,
      sym_ident,
    STATE(71), 1,
      sym_missing_identifier,
    STATE(79), 1,
      sym_missing_string_end,
    STATE(301), 1,
      sym_missing_expression,
    STATE(74), 2,
      sym_path,
      sym_string,
    STATE(125), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(95), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(87), 4,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(225), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1358] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(127), 1,
      anon_sym_RBRACK,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(135), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(137), 1,
      anon_sym_for,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(128), 1,
      sym_missing_array_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(697), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(131), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(526), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [1438] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(139), 1,
      anon_sym_RBRACK,
    ACTIONS(143), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(574), 1,
      sym__for,
    STATE(657), 1,
      sym_missing_array_end,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(711), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(141), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(523), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [1518] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(291), 2,
      sym_path,
      sym_string,
    ACTIONS(145), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(428), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(547), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1590] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(91), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(93), 1,
      anon_sym_DQUOTE,
    ACTIONS(99), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(101), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(103), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(105), 1,
      anon_sym_not,
    ACTIONS(107), 1,
      aux_sym_ident_token1,
    ACTIONS(115), 1,
      anon_sym_LPAREN,
    STATE(21), 1,
      sym__not,
    STATE(61), 1,
      sym_ident,
    STATE(71), 1,
      sym_missing_identifier,
    STATE(79), 1,
      sym_missing_string_end,
    STATE(80), 2,
      sym_path,
      sym_string,
    ACTIONS(117), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(427), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(222), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1662] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    ACTIONS(51), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(53), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(55), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(57), 1,
      anon_sym_not,
    ACTIONS(59), 1,
      aux_sym_ident_token1,
    ACTIONS(109), 1,
      anon_sym_LPAREN,
    STATE(22), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(132), 1,
      sym_missing_identifier,
    STATE(153), 1,
      sym_missing_string_end,
    STATE(142), 2,
      sym_path,
      sym_string,
    ACTIONS(111), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(423), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(239), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1734] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(147), 1,
      anon_sym_RBRACK,
    ACTIONS(151), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(510), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(691), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(149), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(518), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [1814] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(67), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(75), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(77), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(79), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(81), 1,
      anon_sym_not,
    ACTIONS(83), 1,
      aux_sym_ident_token1,
    ACTIONS(121), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(137), 1,
      sym_missing_identifier,
    STATE(144), 1,
      sym_missing_string_end,
    STATE(149), 2,
      sym_path,
      sym_string,
    ACTIONS(123), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(424), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(249), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1886] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(153), 1,
      anon_sym_RBRACK,
    ACTIONS(157), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(306), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(679), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(155), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(520), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [1966] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(159), 1,
      anon_sym_RBRACK,
    ACTIONS(163), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(370), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(703), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(161), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(527), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2046] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(165), 1,
      anon_sym_RBRACK,
    ACTIONS(169), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(501), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(682), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(167), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(525), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2126] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    ACTIONS(51), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(53), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(55), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(57), 1,
      anon_sym_not,
    ACTIONS(59), 1,
      aux_sym_ident_token1,
    ACTIONS(109), 1,
      anon_sym_LPAREN,
    STATE(22), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(132), 1,
      sym_missing_identifier,
    STATE(153), 1,
      sym_missing_string_end,
    STATE(142), 2,
      sym_path,
      sym_string,
    ACTIONS(111), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(423), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(238), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2198] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(45), 1,
      anon_sym_DQUOTE,
    ACTIONS(51), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(53), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(55), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(57), 1,
      anon_sym_not,
    ACTIONS(59), 1,
      aux_sym_ident_token1,
    ACTIONS(109), 1,
      anon_sym_LPAREN,
    STATE(22), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(132), 1,
      sym_missing_identifier,
    STATE(153), 1,
      sym_missing_string_end,
    STATE(142), 2,
      sym_path,
      sym_string,
    ACTIONS(111), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(423), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(233), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2270] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(67), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(75), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(77), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(79), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(81), 1,
      anon_sym_not,
    ACTIONS(83), 1,
      aux_sym_ident_token1,
    ACTIONS(121), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(137), 1,
      sym_missing_identifier,
    STATE(144), 1,
      sym_missing_string_end,
    STATE(149), 2,
      sym_path,
      sym_string,
    ACTIONS(123), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(424), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(250), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2342] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(67), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(69), 1,
      anon_sym_DQUOTE,
    ACTIONS(75), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(77), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(79), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(81), 1,
      anon_sym_not,
    ACTIONS(83), 1,
      aux_sym_ident_token1,
    ACTIONS(121), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(137), 1,
      sym_missing_identifier,
    STATE(144), 1,
      sym_missing_string_end,
    STATE(149), 2,
      sym_path,
      sym_string,
    ACTIONS(123), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(424), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(241), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2414] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(171), 1,
      anon_sym_RBRACK,
    ACTIONS(175), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(392), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(709), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(173), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(524), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2494] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(91), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(93), 1,
      anon_sym_DQUOTE,
    ACTIONS(99), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(101), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(103), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(105), 1,
      anon_sym_not,
    ACTIONS(107), 1,
      aux_sym_ident_token1,
    ACTIONS(115), 1,
      anon_sym_LPAREN,
    STATE(21), 1,
      sym__not,
    STATE(61), 1,
      sym_ident,
    STATE(71), 1,
      sym_missing_identifier,
    STATE(79), 1,
      sym_missing_string_end,
    STATE(80), 2,
      sym_path,
      sym_string,
    ACTIONS(117), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(427), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(221), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2566] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(291), 2,
      sym_path,
      sym_string,
    ACTIONS(145), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(428), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(554), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2638] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(25), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(33), 1,
      anon_sym_not,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__not,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(291), 2,
      sym_path,
      sym_string,
    ACTIONS(145), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(428), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(548), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2710] = 18,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(91), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(93), 1,
      anon_sym_DQUOTE,
    ACTIONS(99), 1,
      anon_sym_ERROR_missing_bool_value,
    ACTIONS(101), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(103), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(105), 1,
      anon_sym_not,
    ACTIONS(107), 1,
      aux_sym_ident_token1,
    ACTIONS(115), 1,
      anon_sym_LPAREN,
    STATE(21), 1,
      sym__not,
    STATE(61), 1,
      sym_ident,
    STATE(71), 1,
      sym_missing_identifier,
    STATE(79), 1,
      sym_missing_string_end,
    STATE(80), 2,
      sym_path,
      sym_string,
    ACTIONS(117), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(427), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(224), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2782] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(177), 1,
      anon_sym_RBRACK,
    ACTIONS(181), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(184), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(687), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(179), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(517), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2862] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(183), 1,
      anon_sym_RBRACK,
    ACTIONS(187), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(182), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(705), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(185), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(519), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2942] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(189), 1,
      anon_sym_RBRACK,
    ACTIONS(193), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(207), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(696), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(191), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(521), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3022] = 22,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(195), 1,
      anon_sym_RBRACK,
    ACTIONS(199), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(254), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(715), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(197), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(522), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3102] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(203), 1,
      anon_sym_for,
    ACTIONS(205), 1,
      anon_sym_let,
    ACTIONS(207), 1,
      anon_sym_if,
    ACTIONS(209), 1,
      anon_sym_set,
    ACTIONS(211), 1,
      anon_sym_delete,
    ACTIONS(213), 1,
      anon_sym_offset,
    ACTIONS(215), 1,
      anon_sym_limit,
    ACTIONS(217), 1,
      anon_sym_append,
    STATE(15), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(555), 1,
      sym__set,
    STATE(561), 1,
      sym__delete,
    STATE(575), 1,
      sym__for,
    STATE(623), 1,
      sym__append,
    STATE(647), 1,
      sym__let,
    STATE(713), 1,
      sym__offset,
    STATE(714), 1,
      sym__limit,
    STATE(731), 1,
      sym_ident,
    ACTIONS(201), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(45), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [3181] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(203), 1,
      anon_sym_for,
    ACTIONS(205), 1,
      anon_sym_let,
    ACTIONS(207), 1,
      anon_sym_if,
    ACTIONS(209), 1,
      anon_sym_set,
    ACTIONS(211), 1,
      anon_sym_delete,
    ACTIONS(213), 1,
      anon_sym_offset,
    ACTIONS(215), 1,
      anon_sym_limit,
    ACTIONS(217), 1,
      anon_sym_append,
    STATE(15), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(555), 1,
      sym__set,
    STATE(561), 1,
      sym__delete,
    STATE(575), 1,
      sym__for,
    STATE(623), 1,
      sym__append,
    STATE(647), 1,
      sym__let,
    STATE(713), 1,
      sym__offset,
    STATE(714), 1,
      sym__limit,
    STATE(731), 1,
      sym_ident,
    ACTIONS(219), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(41), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [3260] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(203), 1,
      anon_sym_for,
    ACTIONS(205), 1,
      anon_sym_let,
    ACTIONS(207), 1,
      anon_sym_if,
    ACTIONS(209), 1,
      anon_sym_set,
    ACTIONS(211), 1,
      anon_sym_delete,
    ACTIONS(213), 1,
      anon_sym_offset,
    ACTIONS(215), 1,
      anon_sym_limit,
    ACTIONS(217), 1,
      anon_sym_append,
    STATE(15), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(555), 1,
      sym__set,
    STATE(561), 1,
      sym__delete,
    STATE(575), 1,
      sym__for,
    STATE(623), 1,
      sym__append,
    STATE(647), 1,
      sym__let,
    STATE(713), 1,
      sym__offset,
    STATE(714), 1,
      sym__limit,
    STATE(731), 1,
      sym_ident,
    ACTIONS(221), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(44), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [3339] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(203), 1,
      anon_sym_for,
    ACTIONS(205), 1,
      anon_sym_let,
    ACTIONS(207), 1,
      anon_sym_if,
    ACTIONS(209), 1,
      anon_sym_set,
    ACTIONS(211), 1,
      anon_sym_delete,
    ACTIONS(213), 1,
      anon_sym_offset,
    ACTIONS(215), 1,
      anon_sym_limit,
    ACTIONS(217), 1,
      anon_sym_append,
    STATE(15), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(555), 1,
      sym__set,
    STATE(561), 1,
      sym__delete,
    STATE(575), 1,
      sym__for,
    STATE(623), 1,
      sym__append,
    STATE(647), 1,
      sym__let,
    STATE(713), 1,
      sym__offset,
    STATE(714), 1,
      sym__limit,
    STATE(731), 1,
      sym_ident,
    ACTIONS(223), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(45), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [3418] = 22,
    ACTIONS(227), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(230), 1,
      anon_sym_for,
    ACTIONS(233), 1,
      anon_sym_let,
    ACTIONS(236), 1,
      anon_sym_if,
    ACTIONS(239), 1,
      anon_sym_set,
    ACTIONS(242), 1,
      anon_sym_delete,
    ACTIONS(245), 1,
      anon_sym_offset,
    ACTIONS(248), 1,
      anon_sym_limit,
    ACTIONS(251), 1,
      anon_sym_append,
    ACTIONS(254), 1,
      aux_sym_ident_token1,
    STATE(15), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(555), 1,
      sym__set,
    STATE(561), 1,
      sym__delete,
    STATE(575), 1,
      sym__for,
    STATE(623), 1,
      sym__append,
    STATE(647), 1,
      sym__let,
    STATE(713), 1,
      sym__offset,
    STATE(714), 1,
      sym__limit,
    STATE(731), 1,
      sym_ident,
    ACTIONS(225), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(45), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [3497] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(693), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(257), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(549), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3568] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(203), 1,
      anon_sym_for,
    ACTIONS(261), 1,
      anon_sym_ERROR_missing_main_iterator,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(575), 1,
      sym__for,
    STATE(43), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(559), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(259), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(633), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3639] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(701), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(263), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(552), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3710] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(708), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(265), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(551), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3781] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(683), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(267), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(543), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3852] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(701), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(269), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(634), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3923] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(574), 1,
      sym__for,
    STATE(70), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(696), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(271), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(631), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3994] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(692), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(273), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(550), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [4065] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(710), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(275), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(553), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [4136] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(716), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(277), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(546), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [4207] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(704), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(279), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(545), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [4278] = 19,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(21), 1,
      anon_sym_ERROR_missing_query_body,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(576), 1,
      sym__for,
    STATE(63), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(701), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(281), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(544), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [4349] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(283), 1,
      anon_sym_let,
    ACTIONS(285), 1,
      anon_sym_if,
    ACTIONS(287), 1,
      anon_sym_set,
    ACTIONS(289), 1,
      anon_sym_delete,
    ACTIONS(291), 1,
      anon_sym_offset,
    ACTIONS(293), 1,
      anon_sym_limit,
    ACTIONS(295), 1,
      anon_sym_append,
    STATE(16), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(556), 1,
      sym__set,
    STATE(557), 1,
      sym__delete,
    STATE(574), 1,
      sym__for,
    STATE(607), 1,
      sym__append,
    STATE(667), 1,
      sym__let,
    STATE(685), 1,
      sym__limit,
    STATE(690), 1,
      sym__offset,
    STATE(728), 1,
      sym_ident,
    ACTIONS(219), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(66), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4425] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(297), 1,
      anon_sym_let,
    ACTIONS(299), 1,
      anon_sym_if,
    ACTIONS(301), 1,
      anon_sym_set,
    ACTIONS(303), 1,
      anon_sym_delete,
    ACTIONS(305), 1,
      anon_sym_offset,
    ACTIONS(307), 1,
      anon_sym_limit,
    ACTIONS(309), 1,
      anon_sym_append,
    STATE(14), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(558), 1,
      sym__delete,
    STATE(562), 1,
      sym__set,
    STATE(576), 1,
      sym__for,
    STATE(620), 1,
      sym__append,
    STATE(651), 1,
      sym__let,
    STATE(686), 1,
      sym__offset,
    STATE(689), 1,
      sym__limit,
    STATE(737), 1,
      sym_ident,
    ACTIONS(219), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(65), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4501] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(297), 1,
      anon_sym_let,
    ACTIONS(299), 1,
      anon_sym_if,
    ACTIONS(301), 1,
      anon_sym_set,
    ACTIONS(303), 1,
      anon_sym_delete,
    ACTIONS(305), 1,
      anon_sym_offset,
    ACTIONS(307), 1,
      anon_sym_limit,
    ACTIONS(309), 1,
      anon_sym_append,
    STATE(14), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(558), 1,
      sym__delete,
    STATE(562), 1,
      sym__set,
    STATE(576), 1,
      sym__for,
    STATE(620), 1,
      sym__append,
    STATE(651), 1,
      sym__let,
    STATE(686), 1,
      sym__offset,
    STATE(689), 1,
      sym__limit,
    STATE(737), 1,
      sym_ident,
    ACTIONS(223), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(62), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4577] = 4,
    ACTIONS(315), 1,
      anon_sym_DOT,
    STATE(64), 1,
      aux_sym_path_repeat1,
    ACTIONS(313), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(311), 26,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [4617] = 22,
    ACTIONS(227), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(254), 1,
      aux_sym_ident_token1,
    ACTIONS(317), 1,
      anon_sym_for,
    ACTIONS(320), 1,
      anon_sym_let,
    ACTIONS(323), 1,
      anon_sym_if,
    ACTIONS(326), 1,
      anon_sym_set,
    ACTIONS(329), 1,
      anon_sym_delete,
    ACTIONS(332), 1,
      anon_sym_offset,
    ACTIONS(335), 1,
      anon_sym_limit,
    ACTIONS(338), 1,
      anon_sym_append,
    STATE(14), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(558), 1,
      sym__delete,
    STATE(562), 1,
      sym__set,
    STATE(576), 1,
      sym__for,
    STATE(620), 1,
      sym__append,
    STATE(651), 1,
      sym__let,
    STATE(686), 1,
      sym__offset,
    STATE(689), 1,
      sym__limit,
    STATE(737), 1,
      sym_ident,
    ACTIONS(225), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(62), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4693] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(297), 1,
      anon_sym_let,
    ACTIONS(299), 1,
      anon_sym_if,
    ACTIONS(301), 1,
      anon_sym_set,
    ACTIONS(303), 1,
      anon_sym_delete,
    ACTIONS(305), 1,
      anon_sym_offset,
    ACTIONS(307), 1,
      anon_sym_limit,
    ACTIONS(309), 1,
      anon_sym_append,
    STATE(14), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(558), 1,
      sym__delete,
    STATE(562), 1,
      sym__set,
    STATE(576), 1,
      sym__for,
    STATE(620), 1,
      sym__append,
    STATE(651), 1,
      sym__let,
    STATE(686), 1,
      sym__offset,
    STATE(689), 1,
      sym__limit,
    STATE(737), 1,
      sym_ident,
    ACTIONS(221), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(60), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4769] = 4,
    ACTIONS(315), 1,
      anon_sym_DOT,
    STATE(67), 1,
      aux_sym_path_repeat1,
    ACTIONS(343), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(341), 26,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [4809] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(297), 1,
      anon_sym_let,
    ACTIONS(299), 1,
      anon_sym_if,
    ACTIONS(301), 1,
      anon_sym_set,
    ACTIONS(303), 1,
      anon_sym_delete,
    ACTIONS(305), 1,
      anon_sym_offset,
    ACTIONS(307), 1,
      anon_sym_limit,
    ACTIONS(309), 1,
      anon_sym_append,
    STATE(14), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(558), 1,
      sym__delete,
    STATE(562), 1,
      sym__set,
    STATE(576), 1,
      sym__for,
    STATE(620), 1,
      sym__append,
    STATE(651), 1,
      sym__let,
    STATE(686), 1,
      sym__offset,
    STATE(689), 1,
      sym__limit,
    STATE(737), 1,
      sym_ident,
    ACTIONS(201), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(62), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4885] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(283), 1,
      anon_sym_let,
    ACTIONS(285), 1,
      anon_sym_if,
    ACTIONS(287), 1,
      anon_sym_set,
    ACTIONS(289), 1,
      anon_sym_delete,
    ACTIONS(291), 1,
      anon_sym_offset,
    ACTIONS(293), 1,
      anon_sym_limit,
    ACTIONS(295), 1,
      anon_sym_append,
    STATE(16), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(556), 1,
      sym__set,
    STATE(557), 1,
      sym__delete,
    STATE(574), 1,
      sym__for,
    STATE(607), 1,
      sym__append,
    STATE(667), 1,
      sym__let,
    STATE(685), 1,
      sym__limit,
    STATE(690), 1,
      sym__offset,
    STATE(728), 1,
      sym_ident,
    ACTIONS(201), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(69), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4961] = 4,
    ACTIONS(349), 1,
      anon_sym_DOT,
    STATE(67), 1,
      aux_sym_path_repeat1,
    ACTIONS(347), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(345), 26,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5001] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(283), 1,
      anon_sym_let,
    ACTIONS(285), 1,
      anon_sym_if,
    ACTIONS(287), 1,
      anon_sym_set,
    ACTIONS(289), 1,
      anon_sym_delete,
    ACTIONS(291), 1,
      anon_sym_offset,
    ACTIONS(293), 1,
      anon_sym_limit,
    ACTIONS(295), 1,
      anon_sym_append,
    STATE(16), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(556), 1,
      sym__set,
    STATE(557), 1,
      sym__delete,
    STATE(574), 1,
      sym__for,
    STATE(607), 1,
      sym__append,
    STATE(667), 1,
      sym__let,
    STATE(685), 1,
      sym__limit,
    STATE(690), 1,
      sym__offset,
    STATE(728), 1,
      sym_ident,
    ACTIONS(223), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(69), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [5077] = 22,
    ACTIONS(227), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(254), 1,
      aux_sym_ident_token1,
    ACTIONS(352), 1,
      anon_sym_for,
    ACTIONS(355), 1,
      anon_sym_let,
    ACTIONS(358), 1,
      anon_sym_if,
    ACTIONS(361), 1,
      anon_sym_set,
    ACTIONS(364), 1,
      anon_sym_delete,
    ACTIONS(367), 1,
      anon_sym_offset,
    ACTIONS(370), 1,
      anon_sym_limit,
    ACTIONS(373), 1,
      anon_sym_append,
    STATE(16), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(556), 1,
      sym__set,
    STATE(557), 1,
      sym__delete,
    STATE(574), 1,
      sym__for,
    STATE(607), 1,
      sym__append,
    STATE(667), 1,
      sym__let,
    STATE(685), 1,
      sym__limit,
    STATE(690), 1,
      sym__offset,
    STATE(728), 1,
      sym_ident,
    ACTIONS(225), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(69), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [5153] = 22,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(283), 1,
      anon_sym_let,
    ACTIONS(285), 1,
      anon_sym_if,
    ACTIONS(287), 1,
      anon_sym_set,
    ACTIONS(289), 1,
      anon_sym_delete,
    ACTIONS(291), 1,
      anon_sym_offset,
    ACTIONS(293), 1,
      anon_sym_limit,
    ACTIONS(295), 1,
      anon_sym_append,
    STATE(16), 1,
      sym__if,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(556), 1,
      sym__set,
    STATE(557), 1,
      sym__delete,
    STATE(574), 1,
      sym__for,
    STATE(607), 1,
      sym__append,
    STATE(667), 1,
      sym__let,
    STATE(685), 1,
      sym__limit,
    STATE(690), 1,
      sym__offset,
    STATE(728), 1,
      sym_ident,
    ACTIONS(221), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(68), 9,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_append_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [5229] = 2,
    ACTIONS(378), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(376), 27,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5264] = 2,
    ACTIONS(347), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(345), 27,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5299] = 2,
    ACTIONS(382), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(380), 27,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5334] = 5,
    ACTIONS(393), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(391), 2,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(384), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5374] = 2,
    ACTIONS(398), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(396), 26,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5408] = 16,
    ACTIONS(49), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(400), 1,
      anon_sym_LBRACK,
    ACTIONS(402), 1,
      anon_sym_LPAREN,
    ACTIONS(404), 1,
      anon_sym_LBRACE,
    ACTIONS(406), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(408), 1,
      anon_sym_DQUOTE,
    ACTIONS(412), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(414), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(416), 1,
      anon_sym_values,
    ACTIONS(418), 1,
      aux_sym_ident_token1,
    STATE(112), 1,
      sym__values,
    STATE(305), 1,
      sym_ident,
    STATE(418), 1,
      sym_missing_identifier,
    STATE(432), 1,
      sym_missing_string_end,
    ACTIONS(410), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(452), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [5470] = 16,
    ACTIONS(97), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(420), 1,
      anon_sym_LBRACK,
    ACTIONS(422), 1,
      anon_sym_LPAREN,
    ACTIONS(424), 1,
      anon_sym_LBRACE,
    ACTIONS(426), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(428), 1,
      anon_sym_DQUOTE,
    ACTIONS(432), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(434), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(436), 1,
      anon_sym_values,
    ACTIONS(438), 1,
      aux_sym_ident_token1,
    STATE(139), 1,
      sym__values,
    STATE(236), 1,
      sym_ident,
    STATE(280), 1,
      sym_missing_identifier,
    STATE(341), 1,
      sym_missing_string_end,
    ACTIONS(430), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(311), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [5532] = 2,
    ACTIONS(442), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(440), 26,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5566] = 2,
    ACTIONS(446), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(444), 26,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5600] = 4,
    ACTIONS(448), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(391), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5638] = 2,
    ACTIONS(452), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(450), 26,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5672] = 16,
    ACTIONS(73), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(454), 1,
      anon_sym_LBRACK,
    ACTIONS(456), 1,
      anon_sym_LPAREN,
    ACTIONS(458), 1,
      anon_sym_LBRACE,
    ACTIONS(460), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(462), 1,
      anon_sym_DQUOTE,
    ACTIONS(466), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(468), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(470), 1,
      anon_sym_values,
    ACTIONS(472), 1,
      aux_sym_ident_token1,
    STATE(124), 1,
      sym__values,
    STATE(307), 1,
      sym_ident,
    STATE(371), 1,
      sym_missing_identifier,
    STATE(479), 1,
      sym_missing_string_end,
    ACTIONS(464), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(434), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [5734] = 4,
    ACTIONS(474), 1,
      anon_sym_DOT,
    STATE(83), 1,
      aux_sym_path_repeat1,
    ACTIONS(347), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(345), 23,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5771] = 4,
    ACTIONS(477), 1,
      anon_sym_DOT,
    STATE(90), 1,
      aux_sym_path_repeat1,
    ACTIONS(313), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(311), 23,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5808] = 4,
    ACTIONS(479), 1,
      anon_sym_DOT,
    STATE(83), 1,
      aux_sym_path_repeat1,
    ACTIONS(343), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(341), 23,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5845] = 7,
    ACTIONS(487), 1,
      anon_sym_between,
    ACTIONS(489), 1,
      anon_sym_exists,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    STATE(273), 1,
      sym_comparator,
    ACTIONS(485), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(483), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(481), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5888] = 7,
    ACTIONS(487), 1,
      anon_sym_between,
    ACTIONS(489), 1,
      anon_sym_exists,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    STATE(273), 1,
      sym_comparator,
    ACTIONS(485), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(483), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(493), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5931] = 4,
    ACTIONS(479), 1,
      anon_sym_DOT,
    STATE(85), 1,
      aux_sym_path_repeat1,
    ACTIONS(313), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(311), 23,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [5968] = 4,
    ACTIONS(497), 1,
      anon_sym_DOT,
    STATE(89), 1,
      aux_sym_path_repeat1,
    ACTIONS(347), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(345), 23,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6005] = 4,
    ACTIONS(477), 1,
      anon_sym_DOT,
    STATE(89), 1,
      aux_sym_path_repeat1,
    ACTIONS(343), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(341), 23,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6042] = 16,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(153), 1,
      anon_sym_RBRACK,
    ACTIONS(157), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(306), 1,
      sym_missing_array_end,
    ACTIONS(500), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(614), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [6102] = 4,
    ACTIONS(502), 1,
      anon_sym_DOT,
    STATE(100), 1,
      aux_sym_path_repeat1,
    ACTIONS(343), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(341), 22,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_equals,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_and2,
      anon_sym_or,
  [6138] = 14,
    ACTIONS(504), 1,
      anon_sym_LBRACK,
    ACTIONS(506), 1,
      anon_sym_LPAREN,
    ACTIONS(508), 1,
      anon_sym_LBRACE,
    ACTIONS(510), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(512), 1,
      anon_sym_DQUOTE,
    ACTIONS(516), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(518), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(520), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(522), 1,
      aux_sym_ident_token1,
    STATE(287), 1,
      sym_ident,
    STATE(330), 1,
      sym_missing_identifier,
    STATE(362), 1,
      sym_missing_string_end,
    ACTIONS(514), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(419), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [6194] = 2,
    ACTIONS(526), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(524), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6226] = 2,
    ACTIONS(530), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(528), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6258] = 2,
    ACTIONS(526), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(524), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6290] = 2,
    ACTIONS(382), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(380), 24,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_equals,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_in,
      anon_sym_and2,
      anon_sym_or,
  [6322] = 2,
    ACTIONS(378), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(376), 24,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_equals,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_in,
      anon_sym_and2,
      anon_sym_or,
  [6354] = 4,
    ACTIONS(502), 1,
      anon_sym_DOT,
    STATE(92), 1,
      aux_sym_path_repeat1,
    ACTIONS(313), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(311), 22,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_equals,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_and2,
      anon_sym_or,
  [6390] = 4,
    ACTIONS(532), 1,
      anon_sym_DOT,
    STATE(100), 1,
      aux_sym_path_repeat1,
    ACTIONS(347), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(345), 22,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_equals,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_and2,
      anon_sym_or,
  [6426] = 2,
    ACTIONS(537), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(535), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6458] = 2,
    ACTIONS(541), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(539), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6490] = 2,
    ACTIONS(545), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(543), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6522] = 14,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(547), 1,
      anon_sym_LBRACK,
    ACTIONS(549), 1,
      anon_sym_LPAREN,
    ACTIONS(551), 1,
      anon_sym_LBRACE,
    ACTIONS(555), 1,
      anon_sym_ERROR_missing_expression,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    ACTIONS(553), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(643), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [6578] = 2,
    ACTIONS(537), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(535), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6610] = 2,
    ACTIONS(559), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(557), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6642] = 2,
    ACTIONS(563), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(561), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6674] = 14,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(547), 1,
      anon_sym_LBRACK,
    ACTIONS(549), 1,
      anon_sym_LPAREN,
    ACTIONS(551), 1,
      anon_sym_LBRACE,
    ACTIONS(555), 1,
      anon_sym_ERROR_missing_expression,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    ACTIONS(565), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(642), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [6730] = 14,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(567), 1,
      anon_sym_LPAREN,
    ACTIONS(569), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(571), 1,
      anon_sym_DQUOTE,
    ACTIONS(575), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(577), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(579), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(581), 1,
      aux_sym_ident_token1,
    STATE(695), 1,
      sym_ident,
    STATE(719), 1,
      sym_missing_identifier,
    STATE(725), 1,
      sym_missing_string_end,
    ACTIONS(573), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(729), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [6786] = 2,
    ACTIONS(585), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(583), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [6818] = 14,
    ACTIONS(49), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(400), 1,
      anon_sym_LBRACK,
    ACTIONS(402), 1,
      anon_sym_LPAREN,
    ACTIONS(404), 1,
      anon_sym_LBRACE,
    ACTIONS(406), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(408), 1,
      anon_sym_DQUOTE,
    ACTIONS(412), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(414), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(418), 1,
      aux_sym_ident_token1,
    STATE(305), 1,
      sym_ident,
    STATE(418), 1,
      sym_missing_identifier,
    STATE(432), 1,
      sym_missing_string_end,
    ACTIONS(587), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(445), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [6874] = 14,
    ACTIONS(49), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(400), 1,
      anon_sym_LBRACK,
    ACTIONS(402), 1,
      anon_sym_LPAREN,
    ACTIONS(404), 1,
      anon_sym_LBRACE,
    ACTIONS(406), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(408), 1,
      anon_sym_DQUOTE,
    ACTIONS(412), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(414), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(418), 1,
      aux_sym_ident_token1,
    STATE(305), 1,
      sym_ident,
    STATE(418), 1,
      sym_missing_identifier,
    STATE(432), 1,
      sym_missing_string_end,
    ACTIONS(589), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(444), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [6930] = 14,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(567), 1,
      anon_sym_LPAREN,
    ACTIONS(569), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(571), 1,
      anon_sym_DQUOTE,
    ACTIONS(575), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(577), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(579), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(581), 1,
      aux_sym_ident_token1,
    STATE(695), 1,
      sym_ident,
    STATE(719), 1,
      sym_missing_identifier,
    STATE(725), 1,
      sym_missing_string_end,
    ACTIONS(591), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(726), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [6986] = 14,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(567), 1,
      anon_sym_LPAREN,
    ACTIONS(569), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(571), 1,
      anon_sym_DQUOTE,
    ACTIONS(575), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(577), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(579), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(581), 1,
      aux_sym_ident_token1,
    STATE(695), 1,
      sym_ident,
    STATE(719), 1,
      sym_missing_identifier,
    STATE(725), 1,
      sym_missing_string_end,
    ACTIONS(593), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(736), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [7042] = 16,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(165), 1,
      anon_sym_RBRACK,
    ACTIONS(169), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(501), 1,
      sym_missing_array_end,
    ACTIONS(595), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(624), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [7102] = 14,
    ACTIONS(597), 1,
      anon_sym_LBRACK,
    ACTIONS(599), 1,
      anon_sym_LPAREN,
    ACTIONS(601), 1,
      anon_sym_LBRACE,
    ACTIONS(603), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(605), 1,
      anon_sym_DQUOTE,
    ACTIONS(609), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(611), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(613), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(615), 1,
      aux_sym_ident_token1,
    STATE(288), 1,
      sym_ident,
    STATE(347), 1,
      sym_missing_identifier,
    STATE(369), 1,
      sym_missing_string_end,
    ACTIONS(607), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(367), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [7158] = 14,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(567), 1,
      anon_sym_LPAREN,
    ACTIONS(569), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(571), 1,
      anon_sym_DQUOTE,
    ACTIONS(575), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(577), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(579), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(581), 1,
      aux_sym_ident_token1,
    STATE(695), 1,
      sym_ident,
    STATE(719), 1,
      sym_missing_identifier,
    STATE(725), 1,
      sym_missing_string_end,
    ACTIONS(617), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(738), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [7214] = 14,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(575), 1,
      anon_sym_ERROR_missing_expression,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    ACTIONS(619), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(681), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [7270] = 2,
    ACTIONS(347), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(345), 24,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7302] = 14,
    ACTIONS(504), 1,
      anon_sym_LBRACK,
    ACTIONS(506), 1,
      anon_sym_LPAREN,
    ACTIONS(508), 1,
      anon_sym_LBRACE,
    ACTIONS(510), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(512), 1,
      anon_sym_DQUOTE,
    ACTIONS(516), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(518), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(520), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(522), 1,
      aux_sym_ident_token1,
    STATE(287), 1,
      sym_ident,
    STATE(330), 1,
      sym_missing_identifier,
    STATE(362), 1,
      sym_missing_string_end,
    ACTIONS(621), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(394), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [7358] = 14,
    ACTIONS(73), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(454), 1,
      anon_sym_LBRACK,
    ACTIONS(456), 1,
      anon_sym_LPAREN,
    ACTIONS(458), 1,
      anon_sym_LBRACE,
    ACTIONS(460), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(462), 1,
      anon_sym_DQUOTE,
    ACTIONS(466), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(468), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(472), 1,
      aux_sym_ident_token1,
    STATE(307), 1,
      sym_ident,
    STATE(371), 1,
      sym_missing_identifier,
    STATE(479), 1,
      sym_missing_string_end,
    ACTIONS(623), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(429), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [7414] = 4,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(481), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7450] = 14,
    ACTIONS(625), 1,
      anon_sym_LBRACK,
    ACTIONS(627), 1,
      anon_sym_LPAREN,
    ACTIONS(629), 1,
      anon_sym_LBRACE,
    ACTIONS(631), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(633), 1,
      anon_sym_DQUOTE,
    ACTIONS(637), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(639), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(641), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(643), 1,
      aux_sym_ident_token1,
    STATE(228), 1,
      sym_ident,
    STATE(245), 1,
      sym_missing_identifier,
    STATE(264), 1,
      sym_missing_string_end,
    ACTIONS(635), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(269), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [7506] = 14,
    ACTIONS(73), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(454), 1,
      anon_sym_LBRACK,
    ACTIONS(456), 1,
      anon_sym_LPAREN,
    ACTIONS(458), 1,
      anon_sym_LBRACE,
    ACTIONS(460), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(462), 1,
      anon_sym_DQUOTE,
    ACTIONS(466), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(468), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(472), 1,
      aux_sym_ident_token1,
    STATE(307), 1,
      sym_ident,
    STATE(371), 1,
      sym_missing_identifier,
    STATE(479), 1,
      sym_missing_string_end,
    ACTIONS(645), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(453), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [7562] = 4,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(493), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7598] = 2,
    ACTIONS(347), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(345), 24,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7630] = 2,
    ACTIONS(382), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(380), 24,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7662] = 2,
    ACTIONS(649), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(647), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7694] = 16,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(147), 1,
      anon_sym_RBRACK,
    ACTIONS(151), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(510), 1,
      sym_missing_array_end,
    ACTIONS(651), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(609), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [7754] = 2,
    ACTIONS(655), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(653), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7786] = 2,
    ACTIONS(659), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(657), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7818] = 2,
    ACTIONS(378), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(376), 24,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7850] = 14,
    ACTIONS(597), 1,
      anon_sym_LBRACK,
    ACTIONS(599), 1,
      anon_sym_LPAREN,
    ACTIONS(601), 1,
      anon_sym_LBRACE,
    ACTIONS(603), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(605), 1,
      anon_sym_DQUOTE,
    ACTIONS(609), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(611), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(613), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(615), 1,
      aux_sym_ident_token1,
    STATE(288), 1,
      sym_ident,
    STATE(347), 1,
      sym_missing_identifier,
    STATE(369), 1,
      sym_missing_string_end,
    ACTIONS(661), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(377), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [7906] = 2,
    ACTIONS(665), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(663), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7938] = 2,
    ACTIONS(382), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(380), 24,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [7970] = 2,
    ACTIONS(669), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(667), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8002] = 2,
    ACTIONS(378), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(376), 24,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8034] = 14,
    ACTIONS(97), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(420), 1,
      anon_sym_LBRACK,
    ACTIONS(422), 1,
      anon_sym_LPAREN,
    ACTIONS(424), 1,
      anon_sym_LBRACE,
    ACTIONS(426), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(428), 1,
      anon_sym_DQUOTE,
    ACTIONS(432), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(434), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(438), 1,
      aux_sym_ident_token1,
    STATE(236), 1,
      sym_ident,
    STATE(280), 1,
      sym_missing_identifier,
    STATE(341), 1,
      sym_missing_string_end,
    ACTIONS(671), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(327), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [8090] = 14,
    ACTIONS(97), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(420), 1,
      anon_sym_LBRACK,
    ACTIONS(422), 1,
      anon_sym_LPAREN,
    ACTIONS(424), 1,
      anon_sym_LBRACE,
    ACTIONS(426), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(428), 1,
      anon_sym_DQUOTE,
    ACTIONS(432), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(434), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(438), 1,
      aux_sym_ident_token1,
    STATE(236), 1,
      sym_ident,
    STATE(280), 1,
      sym_missing_identifier,
    STATE(341), 1,
      sym_missing_string_end,
    ACTIONS(673), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(328), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [8146] = 2,
    ACTIONS(677), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(675), 24,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8178] = 14,
    ACTIONS(625), 1,
      anon_sym_LBRACK,
    ACTIONS(627), 1,
      anon_sym_LPAREN,
    ACTIONS(629), 1,
      anon_sym_LBRACE,
    ACTIONS(631), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(633), 1,
      anon_sym_DQUOTE,
    ACTIONS(637), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(639), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(641), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(643), 1,
      aux_sym_ident_token1,
    STATE(228), 1,
      sym_ident,
    STATE(245), 1,
      sym_missing_identifier,
    STATE(264), 1,
      sym_missing_string_end,
    ACTIONS(679), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(277), 11,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
      sym__expected_expression,
      sym_missing_expression,
  [8234] = 4,
    ACTIONS(448), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(391), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8269] = 2,
    ACTIONS(452), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(450), 23,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8300] = 2,
    ACTIONS(446), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(444), 23,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8331] = 2,
    ACTIONS(398), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(396), 23,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8362] = 5,
    ACTIONS(393), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(391), 2,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(384), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8399] = 2,
    ACTIONS(398), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(396), 23,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8430] = 2,
    ACTIONS(442), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(440), 23,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8461] = 4,
    ACTIONS(448), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(391), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8496] = 5,
    ACTIONS(393), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(391), 2,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(384), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8533] = 2,
    ACTIONS(347), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(345), 23,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_DOT,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_equals,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_and2,
      anon_sym_or,
  [8564] = 2,
    ACTIONS(452), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(450), 23,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8595] = 2,
    ACTIONS(446), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(444), 23,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8626] = 2,
    ACTIONS(442), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(440), 23,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8657] = 7,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(685), 1,
      anon_sym_between,
    ACTIONS(687), 1,
      anon_sym_exists,
    STATE(365), 1,
      sym_comparator,
    ACTIONS(683), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(681), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(481), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8697] = 2,
    ACTIONS(398), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(396), 23,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_colon,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_and2,
      anon_sym_or,
  [8727] = 7,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(693), 1,
      anon_sym_between,
    ACTIONS(695), 1,
      anon_sym_exists,
    STATE(417), 1,
      sym_comparator,
    ACTIONS(691), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(689), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(493), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8767] = 2,
    ACTIONS(446), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(444), 23,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_colon,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_and2,
      anon_sym_or,
  [8797] = 2,
    ACTIONS(452), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(450), 23,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_colon,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_and2,
      anon_sym_or,
  [8827] = 7,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(693), 1,
      anon_sym_between,
    ACTIONS(695), 1,
      anon_sym_exists,
    STATE(417), 1,
      sym_comparator,
    ACTIONS(691), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(689), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(481), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8867] = 2,
    ACTIONS(442), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(440), 23,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_colon,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_and2,
      anon_sym_or,
  [8897] = 7,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(685), 1,
      anon_sym_between,
    ACTIONS(687), 1,
      anon_sym_exists,
    STATE(365), 1,
      sym_comparator,
    ACTIONS(683), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(681), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(493), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8937] = 2,
    ACTIONS(537), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(535), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8966] = 2,
    ACTIONS(655), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(653), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [8995] = 2,
    ACTIONS(665), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(663), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9024] = 2,
    ACTIONS(585), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(583), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9053] = 2,
    ACTIONS(585), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(583), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9082] = 2,
    ACTIONS(563), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(561), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9111] = 2,
    ACTIONS(559), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(557), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9140] = 2,
    ACTIONS(541), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(539), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9169] = 2,
    ACTIONS(537), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(535), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9198] = 2,
    ACTIONS(665), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(663), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9227] = 2,
    ACTIONS(563), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(561), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9256] = 2,
    ACTIONS(526), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(524), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9285] = 2,
    ACTIONS(530), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(528), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9314] = 2,
    ACTIONS(526), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(524), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9343] = 2,
    ACTIONS(669), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(667), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9372] = 4,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(493), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9405] = 2,
    ACTIONS(677), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(675), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9434] = 2,
    ACTIONS(659), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(657), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9463] = 2,
    ACTIONS(669), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(667), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9492] = 2,
    ACTIONS(649), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(647), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9521] = 13,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(158), 1,
      sym_missing_string_end,
    ACTIONS(697), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(700), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [9572] = 2,
    ACTIONS(649), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(647), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9601] = 2,
    ACTIONS(655), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(653), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9630] = 2,
    ACTIONS(659), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(657), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9659] = 4,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(493), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9692] = 2,
    ACTIONS(677), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(675), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9721] = 2,
    ACTIONS(545), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(543), 21,
      anon_sym_RBRACK,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9750] = 4,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(481), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9783] = 2,
    ACTIONS(526), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(524), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9812] = 2,
    ACTIONS(545), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(543), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9841] = 2,
    ACTIONS(530), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(528), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9870] = 2,
    ACTIONS(559), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(557), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9899] = 2,
    ACTIONS(537), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(535), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9928] = 2,
    ACTIONS(541), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(539), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9957] = 2,
    ACTIONS(537), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(535), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [9986] = 4,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
    ACTIONS(481), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10019] = 2,
    ACTIONS(526), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(524), 21,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10048] = 2,
    ACTIONS(541), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(539), 21,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10076] = 2,
    ACTIONS(526), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(524), 21,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10104] = 2,
    ACTIONS(545), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(543), 21,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
      anon_sym_and2,
      anon_sym_or,
  [10132] = 2,
    ACTIONS(530), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(528), 21,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10160] = 2,
    ACTIONS(537), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(535), 21,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10188] = 2,
    ACTIONS(526), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(524), 21,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10216] = 2,
    ACTIONS(537), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(535), 21,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10244] = 2,
    ACTIONS(649), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(647), 20,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10271] = 2,
    ACTIONS(585), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(583), 20,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10298] = 2,
    ACTIONS(655), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(653), 20,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10325] = 2,
    ACTIONS(659), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(657), 20,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10352] = 2,
    ACTIONS(677), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(675), 20,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10379] = 2,
    ACTIONS(665), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(663), 20,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10406] = 2,
    ACTIONS(669), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(667), 20,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10433] = 2,
    ACTIONS(563), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(561), 20,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10460] = 2,
    ACTIONS(559), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(557), 20,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_and,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_brace_end,
      anon_sym_ERROR_missing_array_end,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_for,
  [10487] = 8,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(699), 1,
      anon_sym_and2,
    ACTIONS(701), 1,
      anon_sym_or,
    STATE(33), 1,
      sym__and,
    STATE(36), 1,
      sym__or,
    STATE(229), 1,
      aux_sym_and_expression_repeat1,
    STATE(230), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(481), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10525] = 12,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(703), 1,
      anon_sym_RPAREN,
    ACTIONS(709), 1,
      anon_sym_between,
    ACTIONS(711), 1,
      anon_sym_exists,
    ACTIONS(713), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(214), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(656), 1,
      sym_comparator,
    ACTIONS(707), 2,
      anon_sym_GT,
      anon_sym_LT,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    ACTIONS(705), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [10571] = 8,
    ACTIONS(699), 1,
      anon_sym_and2,
    ACTIONS(701), 1,
      anon_sym_or,
    ACTIONS(717), 1,
      aux_sym_ident_token1,
    STATE(33), 1,
      sym__and,
    STATE(36), 1,
      sym__or,
    STATE(229), 1,
      aux_sym_and_expression_repeat1,
    STATE(230), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(715), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10609] = 12,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(709), 1,
      anon_sym_between,
    ACTIONS(711), 1,
      anon_sym_exists,
    ACTIONS(719), 1,
      anon_sym_RPAREN,
    ACTIONS(721), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(173), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(656), 1,
      sym_comparator,
    ACTIONS(707), 2,
      anon_sym_GT,
      anon_sym_LT,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    ACTIONS(705), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [10655] = 12,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(709), 1,
      anon_sym_between,
    ACTIONS(711), 1,
      anon_sym_exists,
    ACTIONS(723), 1,
      anon_sym_RPAREN,
    ACTIONS(725), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(107), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(656), 1,
      sym_comparator,
    ACTIONS(707), 2,
      anon_sym_GT,
      anon_sym_LT,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    ACTIONS(705), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [10701] = 8,
    ACTIONS(699), 1,
      anon_sym_and2,
    ACTIONS(701), 1,
      anon_sym_or,
    ACTIONS(729), 1,
      aux_sym_ident_token1,
    STATE(33), 1,
      sym__and,
    STATE(36), 1,
      sym__or,
    STATE(229), 1,
      aux_sym_and_expression_repeat1,
    STATE(230), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(727), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10739] = 6,
    ACTIONS(733), 1,
      aux_sym_ident_token1,
    STATE(33), 1,
      sym__and,
    STATE(36), 1,
      sym__or,
    STATE(229), 1,
      aux_sym_and_expression_repeat1,
    STATE(230), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(731), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10773] = 12,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(709), 1,
      anon_sym_between,
    ACTIONS(711), 1,
      anon_sym_exists,
    ACTIONS(735), 1,
      anon_sym_RPAREN,
    ACTIONS(737), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(168), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(656), 1,
      sym_comparator,
    ACTIONS(707), 2,
      anon_sym_GT,
      anon_sym_LT,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    ACTIONS(705), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [10819] = 8,
    ACTIONS(699), 1,
      anon_sym_and2,
    ACTIONS(701), 1,
      anon_sym_or,
    ACTIONS(741), 1,
      aux_sym_ident_token1,
    STATE(33), 1,
      sym__and,
    STATE(36), 1,
      sym__or,
    STATE(229), 1,
      aux_sym_and_expression_repeat1,
    STATE(230), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(739), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10857] = 8,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(699), 1,
      anon_sym_and2,
    ACTIONS(701), 1,
      anon_sym_or,
    STATE(33), 1,
      sym__and,
    STATE(36), 1,
      sym__or,
    STATE(229), 1,
      aux_sym_and_expression_repeat1,
    STATE(230), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(493), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10895] = 4,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(743), 1,
      anon_sym_DOT,
    STATE(226), 1,
      aux_sym_path_repeat1,
    ACTIONS(345), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10923] = 4,
    ACTIONS(343), 1,
      aux_sym_ident_token1,
    ACTIONS(746), 1,
      anon_sym_DOT,
    STATE(226), 1,
      aux_sym_path_repeat1,
    ACTIONS(341), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10951] = 4,
    ACTIONS(313), 1,
      aux_sym_ident_token1,
    ACTIONS(746), 1,
      anon_sym_DOT,
    STATE(227), 1,
      aux_sym_path_repeat1,
    ACTIONS(311), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [10979] = 4,
    ACTIONS(750), 1,
      aux_sym_ident_token1,
    STATE(33), 1,
      sym__and,
    STATE(232), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(748), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11007] = 4,
    ACTIONS(754), 1,
      aux_sym_ident_token1,
    STATE(36), 1,
      sym__or,
    STATE(231), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(752), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11035] = 5,
    ACTIONS(741), 1,
      aux_sym_ident_token1,
    ACTIONS(756), 1,
      anon_sym_or,
    STATE(36), 1,
      sym__or,
    STATE(231), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(739), 15,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11065] = 5,
    ACTIONS(729), 1,
      aux_sym_ident_token1,
    ACTIONS(759), 1,
      anon_sym_and2,
    STATE(33), 1,
      sym__and,
    STATE(232), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(727), 15,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11095] = 8,
    ACTIONS(729), 1,
      aux_sym_ident_token1,
    ACTIONS(762), 1,
      anon_sym_and2,
    ACTIONS(764), 1,
      anon_sym_or,
    STATE(28), 1,
      sym__or,
    STATE(29), 1,
      sym__and,
    STATE(294), 1,
      aux_sym_and_expression_repeat1,
    STATE(295), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(727), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11130] = 4,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(766), 1,
      anon_sym_DOT,
    STATE(234), 1,
      aux_sym_path_repeat1,
    ACTIONS(345), 15,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11157] = 8,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(762), 1,
      anon_sym_and2,
    ACTIONS(764), 1,
      anon_sym_or,
    STATE(28), 1,
      sym__or,
    STATE(29), 1,
      sym__and,
    STATE(294), 1,
      aux_sym_and_expression_repeat1,
    STATE(295), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(493), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11192] = 4,
    ACTIONS(313), 1,
      aux_sym_ident_token1,
    ACTIONS(769), 1,
      anon_sym_DOT,
    STATE(243), 1,
      aux_sym_path_repeat1,
    ACTIONS(311), 15,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11219] = 8,
    ACTIONS(717), 1,
      aux_sym_ident_token1,
    ACTIONS(771), 1,
      anon_sym_and2,
    ACTIONS(773), 1,
      anon_sym_or,
    STATE(30), 1,
      sym__and,
    STATE(31), 1,
      sym__or,
    STATE(282), 1,
      aux_sym_and_expression_repeat1,
    STATE(293), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(715), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11254] = 8,
    ACTIONS(741), 1,
      aux_sym_ident_token1,
    ACTIONS(762), 1,
      anon_sym_and2,
    ACTIONS(764), 1,
      anon_sym_or,
    STATE(28), 1,
      sym__or,
    STATE(29), 1,
      sym__and,
    STATE(294), 1,
      aux_sym_and_expression_repeat1,
    STATE(295), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(739), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11289] = 6,
    ACTIONS(733), 1,
      aux_sym_ident_token1,
    STATE(28), 1,
      sym__or,
    STATE(29), 1,
      sym__and,
    STATE(294), 1,
      aux_sym_and_expression_repeat1,
    STATE(295), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(731), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11320] = 2,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(345), 17,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11343] = 8,
    ACTIONS(741), 1,
      aux_sym_ident_token1,
    ACTIONS(771), 1,
      anon_sym_and2,
    ACTIONS(773), 1,
      anon_sym_or,
    STATE(30), 1,
      sym__and,
    STATE(31), 1,
      sym__or,
    STATE(282), 1,
      aux_sym_and_expression_repeat1,
    STATE(293), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(739), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11378] = 8,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(771), 1,
      anon_sym_and2,
    ACTIONS(773), 1,
      anon_sym_or,
    STATE(30), 1,
      sym__and,
    STATE(31), 1,
      sym__or,
    STATE(282), 1,
      aux_sym_and_expression_repeat1,
    STATE(293), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(481), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11413] = 4,
    ACTIONS(343), 1,
      aux_sym_ident_token1,
    ACTIONS(769), 1,
      anon_sym_DOT,
    STATE(234), 1,
      aux_sym_path_repeat1,
    ACTIONS(341), 15,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11440] = 8,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(762), 1,
      anon_sym_and2,
    ACTIONS(764), 1,
      anon_sym_or,
    STATE(28), 1,
      sym__or,
    STATE(29), 1,
      sym__and,
    STATE(294), 1,
      aux_sym_and_expression_repeat1,
    STATE(295), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(481), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11475] = 2,
    ACTIONS(378), 1,
      aux_sym_ident_token1,
    ACTIONS(376), 17,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11498] = 8,
    ACTIONS(717), 1,
      aux_sym_ident_token1,
    ACTIONS(762), 1,
      anon_sym_and2,
    ACTIONS(764), 1,
      anon_sym_or,
    STATE(28), 1,
      sym__or,
    STATE(29), 1,
      sym__and,
    STATE(294), 1,
      aux_sym_and_expression_repeat1,
    STATE(295), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(715), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11533] = 4,
    ACTIONS(384), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(391), 2,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(387), 12,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_for,
  [11560] = 2,
    ACTIONS(382), 1,
      aux_sym_ident_token1,
    ACTIONS(380), 17,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11583] = 6,
    ACTIONS(733), 1,
      aux_sym_ident_token1,
    STATE(30), 1,
      sym__and,
    STATE(31), 1,
      sym__or,
    STATE(282), 1,
      aux_sym_and_expression_repeat1,
    STATE(293), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(731), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11614] = 8,
    ACTIONS(729), 1,
      aux_sym_ident_token1,
    ACTIONS(771), 1,
      anon_sym_and2,
    ACTIONS(773), 1,
      anon_sym_or,
    STATE(30), 1,
      sym__and,
    STATE(31), 1,
      sym__or,
    STATE(282), 1,
      aux_sym_and_expression_repeat1,
    STATE(293), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(727), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11649] = 8,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(771), 1,
      anon_sym_and2,
    ACTIONS(773), 1,
      anon_sym_or,
    STATE(30), 1,
      sym__and,
    STATE(31), 1,
      sym__or,
    STATE(282), 1,
      aux_sym_and_expression_repeat1,
    STATE(293), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(493), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11684] = 2,
    ACTIONS(777), 1,
      aux_sym_ident_token1,
    ACTIONS(775), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11706] = 2,
    ACTIONS(669), 1,
      aux_sym_ident_token1,
    ACTIONS(667), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11728] = 2,
    ACTIONS(649), 1,
      aux_sym_ident_token1,
    ACTIONS(647), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11750] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11772] = 2,
    ACTIONS(442), 1,
      aux_sym_ident_token1,
    ACTIONS(440), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11794] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11816] = 2,
    ACTIONS(530), 1,
      aux_sym_ident_token1,
    ACTIONS(528), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11838] = 2,
    ACTIONS(559), 1,
      aux_sym_ident_token1,
    ACTIONS(557), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11860] = 2,
    ACTIONS(655), 1,
      aux_sym_ident_token1,
    ACTIONS(653), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11882] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11904] = 2,
    ACTIONS(665), 1,
      aux_sym_ident_token1,
    ACTIONS(663), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11926] = 2,
    ACTIONS(545), 1,
      aux_sym_ident_token1,
    ACTIONS(543), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11948] = 2,
    ACTIONS(446), 1,
      aux_sym_ident_token1,
    ACTIONS(444), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11970] = 2,
    ACTIONS(398), 1,
      aux_sym_ident_token1,
    ACTIONS(396), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [11992] = 2,
    ACTIONS(781), 1,
      aux_sym_ident_token1,
    ACTIONS(779), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12014] = 2,
    ACTIONS(659), 1,
      aux_sym_ident_token1,
    ACTIONS(657), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12036] = 2,
    ACTIONS(452), 1,
      aux_sym_ident_token1,
    ACTIONS(450), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12058] = 2,
    ACTIONS(785), 1,
      aux_sym_ident_token1,
    ACTIONS(783), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12080] = 2,
    ACTIONS(541), 1,
      aux_sym_ident_token1,
    ACTIONS(539), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12102] = 2,
    ACTIONS(585), 1,
      aux_sym_ident_token1,
    ACTIONS(583), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12124] = 2,
    ACTIONS(382), 1,
      aux_sym_ident_token1,
    ACTIONS(380), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12146] = 2,
    ACTIONS(789), 1,
      aux_sym_ident_token1,
    ACTIONS(787), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12168] = 2,
    ACTIONS(563), 1,
      aux_sym_ident_token1,
    ACTIONS(561), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12190] = 2,
    ACTIONS(793), 1,
      aux_sym_ident_token1,
    ACTIONS(791), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12212] = 2,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(345), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12234] = 2,
    ACTIONS(797), 1,
      aux_sym_ident_token1,
    ACTIONS(795), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12256] = 2,
    ACTIONS(677), 1,
      aux_sym_ident_token1,
    ACTIONS(675), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12278] = 2,
    ACTIONS(801), 1,
      aux_sym_ident_token1,
    ACTIONS(799), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12300] = 2,
    ACTIONS(378), 1,
      aux_sym_ident_token1,
    ACTIONS(376), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12322] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 16,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12344] = 4,
    ACTIONS(750), 1,
      aux_sym_ident_token1,
    STATE(30), 1,
      sym__and,
    STATE(289), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(748), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12369] = 3,
    ACTIONS(805), 1,
      anon_sym_LPAREN_RPAREN,
    ACTIONS(807), 1,
      aux_sym_ident_token1,
    ACTIONS(803), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12392] = 4,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(809), 1,
      anon_sym_DOT,
    STATE(284), 1,
      aux_sym_path_repeat1,
    ACTIONS(345), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12417] = 4,
    ACTIONS(812), 1,
      anon_sym_DOT,
    STATE(285), 1,
      aux_sym_path_repeat1,
    ACTIONS(347), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(345), 12,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_DQUOTE_DQUOTE,
      sym_number,
      anon_sym_ERROR_missing_expression,
      anon_sym_ERROR_missing_value,
      anon_sym_ERROR_missing_string_end,
      sym_true,
      sym_false,
      sym_null,
      anon_sym_values,
  [12442] = 4,
    ACTIONS(343), 1,
      aux_sym_ident_token1,
    ACTIONS(815), 1,
      anon_sym_DOT,
    STATE(284), 1,
      aux_sym_path_repeat1,
    ACTIONS(341), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12467] = 4,
    ACTIONS(313), 1,
      aux_sym_ident_token1,
    ACTIONS(817), 1,
      anon_sym_DOT,
    STATE(297), 1,
      aux_sym_path_repeat1,
    ACTIONS(311), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12492] = 4,
    ACTIONS(313), 1,
      aux_sym_ident_token1,
    ACTIONS(815), 1,
      anon_sym_DOT,
    STATE(286), 1,
      aux_sym_path_repeat1,
    ACTIONS(311), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12517] = 5,
    ACTIONS(729), 1,
      aux_sym_ident_token1,
    ACTIONS(819), 1,
      anon_sym_and2,
    STATE(30), 1,
      sym__and,
    STATE(289), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(727), 12,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12544] = 4,
    ACTIONS(822), 1,
      anon_sym_DOT,
    STATE(285), 1,
      aux_sym_path_repeat1,
    ACTIONS(343), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(341), 12,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_DQUOTE_DQUOTE,
      sym_number,
      anon_sym_ERROR_missing_expression,
      anon_sym_ERROR_missing_value,
      anon_sym_ERROR_missing_string_end,
      sym_true,
      sym_false,
      sym_null,
      anon_sym_values,
  [12569] = 3,
    ACTIONS(389), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(391), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(387), 10,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_between,
      anon_sym_contains,
      anon_sym_exists,
  [12592] = 5,
    ACTIONS(741), 1,
      aux_sym_ident_token1,
    ACTIONS(824), 1,
      anon_sym_or,
    STATE(31), 1,
      sym__or,
    STATE(292), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(739), 12,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12619] = 4,
    ACTIONS(754), 1,
      aux_sym_ident_token1,
    STATE(31), 1,
      sym__or,
    STATE(292), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(752), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12644] = 4,
    ACTIONS(750), 1,
      aux_sym_ident_token1,
    STATE(29), 1,
      sym__and,
    STATE(298), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(748), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12669] = 4,
    ACTIONS(754), 1,
      aux_sym_ident_token1,
    STATE(28), 1,
      sym__or,
    STATE(299), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(752), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12694] = 4,
    ACTIONS(822), 1,
      anon_sym_DOT,
    STATE(290), 1,
      aux_sym_path_repeat1,
    ACTIONS(313), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(311), 12,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_DQUOTE_DQUOTE,
      sym_number,
      anon_sym_ERROR_missing_expression,
      anon_sym_ERROR_missing_value,
      anon_sym_ERROR_missing_string_end,
      sym_true,
      sym_false,
      sym_null,
      anon_sym_values,
  [12719] = 4,
    ACTIONS(343), 1,
      aux_sym_ident_token1,
    ACTIONS(817), 1,
      anon_sym_DOT,
    STATE(300), 1,
      aux_sym_path_repeat1,
    ACTIONS(341), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12744] = 5,
    ACTIONS(729), 1,
      aux_sym_ident_token1,
    ACTIONS(827), 1,
      anon_sym_and2,
    STATE(29), 1,
      sym__and,
    STATE(298), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(727), 12,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12771] = 5,
    ACTIONS(741), 1,
      aux_sym_ident_token1,
    ACTIONS(830), 1,
      anon_sym_or,
    STATE(28), 1,
      sym__or,
    STATE(299), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(739), 12,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12798] = 4,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(833), 1,
      anon_sym_DOT,
    STATE(300), 1,
      aux_sym_path_repeat1,
    ACTIONS(345), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12823] = 2,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(493), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12843] = 2,
    ACTIONS(563), 1,
      aux_sym_ident_token1,
    ACTIONS(561), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12863] = 2,
    ACTIONS(838), 1,
      aux_sym_ident_token1,
    ACTIONS(836), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12883] = 2,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(345), 14,
      anon_sym_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12903] = 4,
    ACTIONS(313), 1,
      aux_sym_ident_token1,
    ACTIONS(840), 1,
      anon_sym_DOT,
    STATE(319), 1,
      aux_sym_path_repeat1,
    ACTIONS(311), 12,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12927] = 2,
    ACTIONS(649), 1,
      aux_sym_ident_token1,
    ACTIONS(647), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12947] = 4,
    ACTIONS(313), 1,
      aux_sym_ident_token1,
    ACTIONS(842), 1,
      anon_sym_DOT,
    STATE(339), 1,
      aux_sym_path_repeat1,
    ACTIONS(311), 12,
      anon_sym_RBRACK,
      anon_sym_LPAREN_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12971] = 2,
    ACTIONS(655), 1,
      aux_sym_ident_token1,
    ACTIONS(653), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [12991] = 2,
    ACTIONS(659), 1,
      aux_sym_ident_token1,
    ACTIONS(657), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13011] = 2,
    ACTIONS(677), 1,
      aux_sym_ident_token1,
    ACTIONS(675), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13031] = 2,
    ACTIONS(846), 1,
      aux_sym_ident_token1,
    ACTIONS(844), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13051] = 2,
    ACTIONS(850), 1,
      aux_sym_ident_token1,
    ACTIONS(848), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13071] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13091] = 2,
    ACTIONS(854), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(852), 13,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_DQUOTE_DQUOTE,
      sym_number,
      anon_sym_ERROR_missing_query_body,
      anon_sym_ERROR_missing_main_iterator,
      anon_sym_ERROR_missing_value,
      anon_sym_ERROR_missing_string_end,
      anon_sym_for,
      sym_true,
      sym_false,
      sym_null,
  [13111] = 2,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(481), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13131] = 2,
    ACTIONS(807), 1,
      aux_sym_ident_token1,
    ACTIONS(803), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13151] = 2,
    ACTIONS(530), 1,
      aux_sym_ident_token1,
    ACTIONS(528), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13171] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13191] = 4,
    ACTIONS(343), 1,
      aux_sym_ident_token1,
    ACTIONS(840), 1,
      anon_sym_DOT,
    STATE(333), 1,
      aux_sym_path_repeat1,
    ACTIONS(341), 12,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13215] = 2,
    ACTIONS(858), 1,
      aux_sym_ident_token1,
    ACTIONS(856), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13235] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13255] = 2,
    ACTIONS(862), 1,
      aux_sym_ident_token1,
    ACTIONS(860), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13275] = 2,
    ACTIONS(866), 1,
      aux_sym_ident_token1,
    ACTIONS(864), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13295] = 2,
    ACTIONS(541), 1,
      aux_sym_ident_token1,
    ACTIONS(539), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13315] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13335] = 2,
    ACTIONS(559), 1,
      aux_sym_ident_token1,
    ACTIONS(557), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13355] = 2,
    ACTIONS(870), 1,
      aux_sym_ident_token1,
    ACTIONS(868), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13375] = 2,
    ACTIONS(874), 1,
      aux_sym_ident_token1,
    ACTIONS(872), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13395] = 2,
    ACTIONS(878), 1,
      aux_sym_ident_token1,
    ACTIONS(876), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13415] = 2,
    ACTIONS(378), 1,
      aux_sym_ident_token1,
    ACTIONS(376), 14,
      anon_sym_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13435] = 2,
    ACTIONS(585), 1,
      aux_sym_ident_token1,
    ACTIONS(583), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13455] = 2,
    ACTIONS(382), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(380), 13,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_DOT,
      anon_sym_LBRACE,
      anon_sym_DQUOTE_DQUOTE,
      sym_number,
      anon_sym_ERROR_missing_expression,
      anon_sym_ERROR_missing_value,
      anon_sym_ERROR_missing_string_end,
      sym_true,
      sym_false,
      sym_null,
      anon_sym_values,
  [13475] = 4,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(880), 1,
      anon_sym_DOT,
    STATE(333), 1,
      aux_sym_path_repeat1,
    ACTIONS(345), 12,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13499] = 2,
    ACTIONS(378), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(376), 13,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_DOT,
      anon_sym_LBRACE,
      anon_sym_DQUOTE_DQUOTE,
      sym_number,
      anon_sym_ERROR_missing_expression,
      anon_sym_ERROR_missing_value,
      anon_sym_ERROR_missing_string_end,
      sym_true,
      sym_false,
      sym_null,
      anon_sym_values,
  [13519] = 4,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(883), 1,
      anon_sym_DOT,
    STATE(335), 1,
      aux_sym_path_repeat1,
    ACTIONS(345), 12,
      anon_sym_RBRACK,
      anon_sym_LPAREN_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13543] = 2,
    ACTIONS(888), 1,
      aux_sym_ident_token1,
    ACTIONS(886), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13563] = 2,
    ACTIONS(892), 1,
      aux_sym_ident_token1,
    ACTIONS(890), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13583] = 2,
    ACTIONS(665), 1,
      aux_sym_ident_token1,
    ACTIONS(663), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13603] = 4,
    ACTIONS(343), 1,
      aux_sym_ident_token1,
    ACTIONS(842), 1,
      anon_sym_DOT,
    STATE(335), 1,
      aux_sym_path_repeat1,
    ACTIONS(341), 12,
      anon_sym_RBRACK,
      anon_sym_LPAREN_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13627] = 2,
    ACTIONS(669), 1,
      aux_sym_ident_token1,
    ACTIONS(667), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13647] = 2,
    ACTIONS(446), 1,
      aux_sym_ident_token1,
    ACTIONS(444), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13667] = 2,
    ACTIONS(452), 1,
      aux_sym_ident_token1,
    ACTIONS(450), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13687] = 2,
    ACTIONS(896), 1,
      aux_sym_ident_token1,
    ACTIONS(894), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13707] = 2,
    ACTIONS(398), 1,
      aux_sym_ident_token1,
    ACTIONS(396), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13727] = 2,
    ACTIONS(900), 1,
      aux_sym_ident_token1,
    ACTIONS(898), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13747] = 2,
    ACTIONS(382), 1,
      aux_sym_ident_token1,
    ACTIONS(380), 14,
      anon_sym_RBRACK,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13767] = 2,
    ACTIONS(378), 1,
      aux_sym_ident_token1,
    ACTIONS(376), 14,
      anon_sym_RBRACK,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13787] = 2,
    ACTIONS(904), 1,
      aux_sym_ident_token1,
    ACTIONS(902), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13807] = 2,
    ACTIONS(908), 1,
      aux_sym_ident_token1,
    ACTIONS(906), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13827] = 2,
    ACTIONS(912), 1,
      aux_sym_ident_token1,
    ACTIONS(910), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13847] = 2,
    ACTIONS(916), 1,
      aux_sym_ident_token1,
    ACTIONS(914), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13867] = 2,
    ACTIONS(920), 1,
      aux_sym_ident_token1,
    ACTIONS(918), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13887] = 2,
    ACTIONS(442), 1,
      aux_sym_ident_token1,
    ACTIONS(440), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13907] = 2,
    ACTIONS(545), 1,
      aux_sym_ident_token1,
    ACTIONS(543), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13927] = 2,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(345), 14,
      anon_sym_RBRACK,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13947] = 2,
    ACTIONS(781), 1,
      aux_sym_ident_token1,
    ACTIONS(779), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13967] = 2,
    ACTIONS(924), 1,
      aux_sym_ident_token1,
    ACTIONS(922), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [13987] = 2,
    ACTIONS(928), 1,
      aux_sym_ident_token1,
    ACTIONS(926), 14,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14007] = 2,
    ACTIONS(382), 1,
      aux_sym_ident_token1,
    ACTIONS(380), 14,
      anon_sym_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14027] = 2,
    ACTIONS(347), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(345), 13,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_DOT,
      anon_sym_LBRACE,
      anon_sym_DQUOTE_DQUOTE,
      sym_number,
      anon_sym_ERROR_missing_expression,
      anon_sym_ERROR_missing_value,
      anon_sym_ERROR_missing_string_end,
      sym_true,
      sym_false,
      sym_null,
      anon_sym_values,
  [14047] = 2,
    ACTIONS(793), 1,
      aux_sym_ident_token1,
    ACTIONS(791), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14066] = 2,
    ACTIONS(446), 1,
      aux_sym_ident_token1,
    ACTIONS(444), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14085] = 2,
    ACTIONS(793), 1,
      aux_sym_ident_token1,
    ACTIONS(791), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14104] = 2,
    ACTIONS(777), 1,
      aux_sym_ident_token1,
    ACTIONS(775), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14123] = 2,
    ACTIONS(789), 1,
      aux_sym_ident_token1,
    ACTIONS(787), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14142] = 2,
    ACTIONS(801), 1,
      aux_sym_ident_token1,
    ACTIONS(799), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14161] = 2,
    ACTIONS(785), 1,
      aux_sym_ident_token1,
    ACTIONS(783), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14180] = 2,
    ACTIONS(382), 1,
      aux_sym_ident_token1,
    ACTIONS(380), 13,
      anon_sym_RBRACK,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14199] = 2,
    ACTIONS(446), 1,
      aux_sym_ident_token1,
    ACTIONS(444), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14218] = 2,
    ACTIONS(649), 1,
      aux_sym_ident_token1,
    ACTIONS(647), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14237] = 2,
    ACTIONS(378), 1,
      aux_sym_ident_token1,
    ACTIONS(376), 13,
      anon_sym_RBRACK,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14256] = 2,
    ACTIONS(781), 1,
      aux_sym_ident_token1,
    ACTIONS(779), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14275] = 2,
    ACTIONS(452), 1,
      aux_sym_ident_token1,
    ACTIONS(450), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14294] = 2,
    ACTIONS(777), 1,
      aux_sym_ident_token1,
    ACTIONS(775), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14313] = 2,
    ACTIONS(669), 1,
      aux_sym_ident_token1,
    ACTIONS(667), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14332] = 2,
    ACTIONS(665), 1,
      aux_sym_ident_token1,
    ACTIONS(663), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14351] = 2,
    ACTIONS(797), 1,
      aux_sym_ident_token1,
    ACTIONS(795), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14370] = 2,
    ACTIONS(442), 1,
      aux_sym_ident_token1,
    ACTIONS(440), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14389] = 2,
    ACTIONS(585), 1,
      aux_sym_ident_token1,
    ACTIONS(583), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14408] = 2,
    ACTIONS(563), 1,
      aux_sym_ident_token1,
    ACTIONS(561), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14427] = 2,
    ACTIONS(559), 1,
      aux_sym_ident_token1,
    ACTIONS(557), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14446] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14465] = 2,
    ACTIONS(541), 1,
      aux_sym_ident_token1,
    ACTIONS(539), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14484] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14503] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14522] = 2,
    ACTIONS(530), 1,
      aux_sym_ident_token1,
    ACTIONS(528), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14541] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14560] = 2,
    ACTIONS(398), 1,
      aux_sym_ident_token1,
    ACTIONS(396), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14579] = 2,
    ACTIONS(677), 1,
      aux_sym_ident_token1,
    ACTIONS(675), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14598] = 2,
    ACTIONS(659), 1,
      aux_sym_ident_token1,
    ACTIONS(657), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14617] = 2,
    ACTIONS(655), 1,
      aux_sym_ident_token1,
    ACTIONS(653), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14636] = 2,
    ACTIONS(649), 1,
      aux_sym_ident_token1,
    ACTIONS(647), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14655] = 2,
    ACTIONS(452), 1,
      aux_sym_ident_token1,
    ACTIONS(450), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14674] = 2,
    ACTIONS(797), 1,
      aux_sym_ident_token1,
    ACTIONS(795), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14693] = 2,
    ACTIONS(669), 1,
      aux_sym_ident_token1,
    ACTIONS(667), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14712] = 2,
    ACTIONS(665), 1,
      aux_sym_ident_token1,
    ACTIONS(663), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14731] = 2,
    ACTIONS(442), 1,
      aux_sym_ident_token1,
    ACTIONS(440), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14750] = 2,
    ACTIONS(585), 1,
      aux_sym_ident_token1,
    ACTIONS(583), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14769] = 2,
    ACTIONS(563), 1,
      aux_sym_ident_token1,
    ACTIONS(561), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14788] = 2,
    ACTIONS(559), 1,
      aux_sym_ident_token1,
    ACTIONS(557), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14807] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14826] = 2,
    ACTIONS(541), 1,
      aux_sym_ident_token1,
    ACTIONS(539), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14845] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14864] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14883] = 2,
    ACTIONS(530), 1,
      aux_sym_ident_token1,
    ACTIONS(528), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14902] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14921] = 2,
    ACTIONS(398), 1,
      aux_sym_ident_token1,
    ACTIONS(396), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14940] = 2,
    ACTIONS(677), 1,
      aux_sym_ident_token1,
    ACTIONS(675), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14959] = 2,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(345), 13,
      anon_sym_RBRACK,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14978] = 2,
    ACTIONS(659), 1,
      aux_sym_ident_token1,
    ACTIONS(657), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [14997] = 2,
    ACTIONS(545), 1,
      aux_sym_ident_token1,
    ACTIONS(543), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15016] = 2,
    ACTIONS(655), 1,
      aux_sym_ident_token1,
    ACTIONS(653), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15035] = 2,
    ACTIONS(545), 1,
      aux_sym_ident_token1,
    ACTIONS(543), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15054] = 2,
    ACTIONS(781), 1,
      aux_sym_ident_token1,
    ACTIONS(779), 13,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15073] = 2,
    ACTIONS(347), 1,
      aux_sym_ident_token1,
    ACTIONS(345), 13,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15092] = 2,
    ACTIONS(382), 1,
      aux_sym_ident_token1,
    ACTIONS(380), 13,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15111] = 2,
    ACTIONS(789), 1,
      aux_sym_ident_token1,
    ACTIONS(787), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15130] = 2,
    ACTIONS(378), 1,
      aux_sym_ident_token1,
    ACTIONS(376), 13,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15149] = 2,
    ACTIONS(785), 1,
      aux_sym_ident_token1,
    ACTIONS(783), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15168] = 2,
    ACTIONS(801), 1,
      aux_sym_ident_token1,
    ACTIONS(799), 13,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_and2,
      anon_sym_or,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15187] = 3,
    ACTIONS(807), 1,
      aux_sym_ident_token1,
    ACTIONS(930), 1,
      anon_sym_LPAREN_RPAREN,
    ACTIONS(803), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15207] = 2,
    ACTIONS(934), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(932), 11,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_DQUOTE_DQUOTE,
      sym_number,
      anon_sym_ERROR_missing_expression,
      anon_sym_ERROR_missing_value,
      anon_sym_ERROR_missing_string_end,
      sym_true,
      sym_false,
      sym_null,
  [15225] = 5,
    ACTIONS(693), 1,
      anon_sym_between,
    ACTIONS(695), 1,
      anon_sym_exists,
    STATE(417), 1,
      sym_comparator,
    ACTIONS(691), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(689), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [15249] = 5,
    ACTIONS(685), 1,
      anon_sym_between,
    ACTIONS(687), 1,
      anon_sym_exists,
    STATE(365), 1,
      sym_comparator,
    ACTIONS(683), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(681), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [15273] = 3,
    ACTIONS(807), 1,
      aux_sym_ident_token1,
    ACTIONS(936), 1,
      anon_sym_LPAREN_RPAREN,
    ACTIONS(803), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15293] = 2,
    ACTIONS(940), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(938), 11,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_DQUOTE_DQUOTE,
      sym_number,
      anon_sym_ERROR_missing_expression,
      anon_sym_ERROR_missing_value,
      anon_sym_ERROR_missing_string_end,
      sym_true,
      sym_false,
      sym_null,
  [15311] = 5,
    ACTIONS(487), 1,
      anon_sym_between,
    ACTIONS(489), 1,
      anon_sym_exists,
    STATE(273), 1,
      sym_comparator,
    ACTIONS(485), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(483), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [15335] = 5,
    ACTIONS(709), 1,
      anon_sym_between,
    ACTIONS(711), 1,
      anon_sym_exists,
    STATE(656), 1,
      sym_comparator,
    ACTIONS(707), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(705), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [15359] = 2,
    ACTIONS(870), 1,
      aux_sym_ident_token1,
    ACTIONS(868), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15376] = 2,
    ACTIONS(781), 1,
      aux_sym_ident_token1,
    ACTIONS(779), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15393] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15410] = 2,
    ACTIONS(446), 1,
      aux_sym_ident_token1,
    ACTIONS(444), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15427] = 2,
    ACTIONS(452), 1,
      aux_sym_ident_token1,
    ACTIONS(450), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15444] = 2,
    ACTIONS(846), 1,
      aux_sym_ident_token1,
    ACTIONS(844), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15461] = 2,
    ACTIONS(850), 1,
      aux_sym_ident_token1,
    ACTIONS(848), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15478] = 2,
    ACTIONS(900), 1,
      aux_sym_ident_token1,
    ACTIONS(898), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15495] = 2,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(481), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15512] = 2,
    ACTIONS(904), 1,
      aux_sym_ident_token1,
    ACTIONS(902), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15529] = 2,
    ACTIONS(807), 1,
      aux_sym_ident_token1,
    ACTIONS(803), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15546] = 2,
    ACTIONS(398), 1,
      aux_sym_ident_token1,
    ACTIONS(396), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15563] = 2,
    ACTIONS(862), 1,
      aux_sym_ident_token1,
    ACTIONS(860), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15580] = 2,
    ACTIONS(878), 1,
      aux_sym_ident_token1,
    ACTIONS(876), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15597] = 2,
    ACTIONS(908), 1,
      aux_sym_ident_token1,
    ACTIONS(906), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15614] = 2,
    ACTIONS(874), 1,
      aux_sym_ident_token1,
    ACTIONS(872), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15631] = 2,
    ACTIONS(870), 1,
      aux_sym_ident_token1,
    ACTIONS(868), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15648] = 2,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(493), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15665] = 2,
    ACTIONS(912), 1,
      aux_sym_ident_token1,
    ACTIONS(910), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15682] = 2,
    ACTIONS(807), 1,
      aux_sym_ident_token1,
    ACTIONS(803), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15699] = 2,
    ACTIONS(491), 1,
      aux_sym_ident_token1,
    ACTIONS(481), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15716] = 2,
    ACTIONS(916), 1,
      aux_sym_ident_token1,
    ACTIONS(914), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15733] = 2,
    ACTIONS(442), 1,
      aux_sym_ident_token1,
    ACTIONS(440), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15750] = 2,
    ACTIONS(846), 1,
      aux_sym_ident_token1,
    ACTIONS(844), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15767] = 2,
    ACTIONS(874), 1,
      aux_sym_ident_token1,
    ACTIONS(872), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15784] = 2,
    ACTIONS(781), 1,
      aux_sym_ident_token1,
    ACTIONS(779), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15801] = 2,
    ACTIONS(669), 1,
      aux_sym_ident_token1,
    ACTIONS(667), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15818] = 2,
    ACTIONS(665), 1,
      aux_sym_ident_token1,
    ACTIONS(663), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15835] = 2,
    ACTIONS(896), 1,
      aux_sym_ident_token1,
    ACTIONS(894), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15852] = 2,
    ACTIONS(900), 1,
      aux_sym_ident_token1,
    ACTIONS(898), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15869] = 2,
    ACTIONS(904), 1,
      aux_sym_ident_token1,
    ACTIONS(902), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15886] = 2,
    ACTIONS(908), 1,
      aux_sym_ident_token1,
    ACTIONS(906), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15903] = 2,
    ACTIONS(920), 1,
      aux_sym_ident_token1,
    ACTIONS(918), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15920] = 2,
    ACTIONS(912), 1,
      aux_sym_ident_token1,
    ACTIONS(910), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15937] = 2,
    ACTIONS(916), 1,
      aux_sym_ident_token1,
    ACTIONS(914), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15954] = 2,
    ACTIONS(924), 1,
      aux_sym_ident_token1,
    ACTIONS(922), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15971] = 2,
    ACTIONS(920), 1,
      aux_sym_ident_token1,
    ACTIONS(918), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [15988] = 2,
    ACTIONS(878), 1,
      aux_sym_ident_token1,
    ACTIONS(876), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16005] = 2,
    ACTIONS(924), 1,
      aux_sym_ident_token1,
    ACTIONS(922), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16022] = 2,
    ACTIONS(928), 1,
      aux_sym_ident_token1,
    ACTIONS(926), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16039] = 2,
    ACTIONS(862), 1,
      aux_sym_ident_token1,
    ACTIONS(860), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16056] = 2,
    ACTIONS(928), 1,
      aux_sym_ident_token1,
    ACTIONS(926), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16073] = 2,
    ACTIONS(858), 1,
      aux_sym_ident_token1,
    ACTIONS(856), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16090] = 2,
    ACTIONS(866), 1,
      aux_sym_ident_token1,
    ACTIONS(864), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16107] = 2,
    ACTIONS(892), 1,
      aux_sym_ident_token1,
    ACTIONS(890), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16124] = 2,
    ACTIONS(858), 1,
      aux_sym_ident_token1,
    ACTIONS(856), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16141] = 2,
    ACTIONS(585), 1,
      aux_sym_ident_token1,
    ACTIONS(583), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16158] = 2,
    ACTIONS(850), 1,
      aux_sym_ident_token1,
    ACTIONS(848), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16175] = 2,
    ACTIONS(545), 1,
      aux_sym_ident_token1,
    ACTIONS(543), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16192] = 2,
    ACTIONS(563), 1,
      aux_sym_ident_token1,
    ACTIONS(561), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16209] = 2,
    ACTIONS(446), 1,
      aux_sym_ident_token1,
    ACTIONS(444), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16226] = 2,
    ACTIONS(452), 1,
      aux_sym_ident_token1,
    ACTIONS(450), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16243] = 2,
    ACTIONS(559), 1,
      aux_sym_ident_token1,
    ACTIONS(557), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16260] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16277] = 2,
    ACTIONS(541), 1,
      aux_sym_ident_token1,
    ACTIONS(539), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16294] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16311] = 2,
    ACTIONS(559), 1,
      aux_sym_ident_token1,
    ACTIONS(557), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16328] = 2,
    ACTIONS(888), 1,
      aux_sym_ident_token1,
    ACTIONS(886), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16345] = 2,
    ACTIONS(838), 1,
      aux_sym_ident_token1,
    ACTIONS(836), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16362] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16379] = 2,
    ACTIONS(530), 1,
      aux_sym_ident_token1,
    ACTIONS(528), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16396] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16413] = 2,
    ACTIONS(866), 1,
      aux_sym_ident_token1,
    ACTIONS(864), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16430] = 2,
    ACTIONS(563), 1,
      aux_sym_ident_token1,
    ACTIONS(561), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16447] = 2,
    ACTIONS(541), 1,
      aux_sym_ident_token1,
    ACTIONS(539), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16464] = 2,
    ACTIONS(442), 1,
      aux_sym_ident_token1,
    ACTIONS(440), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16481] = 2,
    ACTIONS(537), 1,
      aux_sym_ident_token1,
    ACTIONS(535), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16498] = 2,
    ACTIONS(665), 1,
      aux_sym_ident_token1,
    ACTIONS(663), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16515] = 2,
    ACTIONS(896), 1,
      aux_sym_ident_token1,
    ACTIONS(894), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16532] = 2,
    ACTIONS(545), 1,
      aux_sym_ident_token1,
    ACTIONS(543), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16549] = 2,
    ACTIONS(585), 1,
      aux_sym_ident_token1,
    ACTIONS(583), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16566] = 2,
    ACTIONS(495), 1,
      aux_sym_ident_token1,
    ACTIONS(493), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16583] = 2,
    ACTIONS(649), 1,
      aux_sym_ident_token1,
    ACTIONS(647), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16600] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16617] = 2,
    ACTIONS(655), 1,
      aux_sym_ident_token1,
    ACTIONS(653), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16634] = 2,
    ACTIONS(892), 1,
      aux_sym_ident_token1,
    ACTIONS(890), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16651] = 2,
    ACTIONS(838), 1,
      aux_sym_ident_token1,
    ACTIONS(836), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16668] = 2,
    ACTIONS(659), 1,
      aux_sym_ident_token1,
    ACTIONS(657), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16685] = 2,
    ACTIONS(888), 1,
      aux_sym_ident_token1,
    ACTIONS(886), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16702] = 2,
    ACTIONS(677), 1,
      aux_sym_ident_token1,
    ACTIONS(675), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16719] = 2,
    ACTIONS(398), 1,
      aux_sym_ident_token1,
    ACTIONS(396), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16736] = 2,
    ACTIONS(649), 1,
      aux_sym_ident_token1,
    ACTIONS(647), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16753] = 2,
    ACTIONS(669), 1,
      aux_sym_ident_token1,
    ACTIONS(667), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16770] = 2,
    ACTIONS(677), 1,
      aux_sym_ident_token1,
    ACTIONS(675), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16787] = 2,
    ACTIONS(659), 1,
      aux_sym_ident_token1,
    ACTIONS(657), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16804] = 2,
    ACTIONS(655), 1,
      aux_sym_ident_token1,
    ACTIONS(653), 11,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16821] = 2,
    ACTIONS(530), 1,
      aux_sym_ident_token1,
    ACTIONS(528), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16838] = 2,
    ACTIONS(526), 1,
      aux_sym_ident_token1,
    ACTIONS(524), 11,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
      anon_sym_ERROR_missing_value,
      anon_sym_for,
      anon_sym_let,
      anon_sym_if,
      anon_sym_set,
      anon_sym_delete,
      anon_sym_offset,
      anon_sym_limit,
      anon_sym_append,
  [16855] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(181), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(942), 1,
      anon_sym_RBRACK,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    STATE(194), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(608), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16884] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(151), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(946), 1,
      anon_sym_RBRACK,
    STATE(481), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(599), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16913] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(187), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(948), 1,
      anon_sym_RBRACK,
    STATE(169), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(612), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16942] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(157), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(950), 1,
      anon_sym_RBRACK,
    STATE(326), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(619), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16971] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(193), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(952), 1,
      anon_sym_RBRACK,
    STATE(215), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(630), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17000] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(199), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(954), 1,
      anon_sym_RBRACK,
    STATE(259), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(636), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17029] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(143), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(956), 1,
      anon_sym_RBRACK,
    STATE(574), 1,
      sym__for,
    STATE(602), 1,
      aux_sym_array_repeat1,
    STATE(676), 1,
      sym_missing_array_end,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17058] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(175), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(958), 1,
      anon_sym_RBRACK,
    STATE(381), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(627), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17087] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(169), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(960), 1,
      anon_sym_RBRACK,
    STATE(485), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(632), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17116] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(135), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(962), 1,
      anon_sym_RBRACK,
    STATE(106), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(597), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17145] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(163), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(964), 1,
      anon_sym_RBRACK,
    STATE(400), 1,
      sym_missing_array_end,
    STATE(574), 1,
      sym__for,
    STATE(611), 1,
      aux_sym_array_repeat1,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17174] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(966), 1,
      anon_sym_RBRACE,
    ACTIONS(968), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(267), 1,
      sym_missing_brace_end,
    STATE(595), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17202] = 9,
    ACTIONS(970), 1,
      anon_sym_RPAREN,
    ACTIONS(972), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(974), 1,
      anon_sym_and2,
    ACTIONS(976), 1,
      anon_sym_or,
    STATE(34), 1,
      sym__and,
    STATE(35), 1,
      sym__or,
    STATE(279), 1,
      sym_missing_parenthesis_end,
    STATE(567), 1,
      aux_sym_or_expression_repeat1,
    STATE(571), 1,
      aux_sym_and_expression_repeat1,
  [17230] = 9,
    ACTIONS(974), 1,
      anon_sym_and2,
    ACTIONS(976), 1,
      anon_sym_or,
    ACTIONS(978), 1,
      anon_sym_RPAREN,
    ACTIONS(980), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(34), 1,
      sym__and,
    STATE(35), 1,
      sym__or,
    STATE(420), 1,
      sym_missing_parenthesis_end,
    STATE(567), 1,
      aux_sym_or_expression_repeat1,
    STATE(571), 1,
      aux_sym_and_expression_repeat1,
  [17258] = 9,
    ACTIONS(974), 1,
      anon_sym_and2,
    ACTIONS(976), 1,
      anon_sym_or,
    ACTIONS(982), 1,
      anon_sym_RPAREN,
    ACTIONS(984), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(34), 1,
      sym__and,
    STATE(35), 1,
      sym__or,
    STATE(366), 1,
      sym_missing_parenthesis_end,
    STATE(567), 1,
      aux_sym_or_expression_repeat1,
    STATE(571), 1,
      aux_sym_and_expression_repeat1,
  [17286] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(986), 1,
      anon_sym_RBRACE,
    ACTIONS(988), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(186), 1,
      sym_missing_brace_end,
    STATE(635), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17314] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(990), 1,
      anon_sym_RBRACE,
    ACTIONS(992), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(210), 1,
      sym_missing_brace_end,
    STATE(618), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17342] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(994), 1,
      anon_sym_RBRACE,
    ACTIONS(996), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(180), 1,
      sym_missing_brace_end,
    STATE(603), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17370] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(998), 1,
      anon_sym_RBRACE,
    ACTIONS(1000), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(604), 1,
      sym_pair,
    STATE(660), 1,
      sym_missing_brace_end,
    STATE(712), 1,
      sym_string,
  [17398] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1002), 1,
      anon_sym_RBRACE,
    ACTIONS(1004), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(309), 1,
      sym_missing_brace_end,
    STATE(622), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17426] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1006), 1,
      anon_sym_RBRACE,
    ACTIONS(1008), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(506), 1,
      sym_missing_brace_end,
    STATE(596), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17454] = 9,
    ACTIONS(713), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(974), 1,
      anon_sym_and2,
    ACTIONS(976), 1,
      anon_sym_or,
    ACTIONS(1010), 1,
      anon_sym_RPAREN,
    STATE(34), 1,
      sym__and,
    STATE(35), 1,
      sym__or,
    STATE(567), 1,
      aux_sym_or_expression_repeat1,
    STATE(571), 1,
      aux_sym_and_expression_repeat1,
    STATE(654), 1,
      sym_missing_parenthesis_end,
  [17482] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1012), 1,
      anon_sym_RBRACE,
    ACTIONS(1014), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(390), 1,
      sym_missing_brace_end,
    STATE(638), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17510] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1016), 1,
      anon_sym_RBRACE,
    ACTIONS(1018), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(410), 1,
      sym_missing_brace_end,
    STATE(601), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17538] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1020), 1,
      anon_sym_RBRACE,
    ACTIONS(1022), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(131), 1,
      sym_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(610), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17566] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1024), 1,
      anon_sym_RBRACE,
    ACTIONS(1026), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(513), 1,
      sym_missing_brace_end,
    STATE(617), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [17594] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(1028), 1,
      anon_sym_RPAREN,
    ACTIONS(1030), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(492), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17617] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(703), 1,
      anon_sym_RPAREN,
    ACTIONS(1032), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(214), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17640] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(984), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(1034), 1,
      anon_sym_RPAREN,
    STATE(399), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17663] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(972), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(1036), 1,
      anon_sym_RPAREN,
    STATE(274), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17686] = 5,
    STATE(34), 1,
      sym__and,
    STATE(35), 1,
      sym__or,
    STATE(567), 1,
      aux_sym_or_expression_repeat1,
    STATE(571), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(731), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [17705] = 7,
    ACTIONS(974), 1,
      anon_sym_and2,
    ACTIONS(976), 1,
      anon_sym_or,
    STATE(34), 1,
      sym__and,
    STATE(35), 1,
      sym__or,
    STATE(567), 1,
      aux_sym_or_expression_repeat1,
    STATE(571), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(739), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
  [17728] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(1038), 1,
      anon_sym_RPAREN,
    ACTIONS(1040), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(478), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17751] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(1042), 1,
      anon_sym_RPAREN,
    ACTIONS(1044), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(302), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17774] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(713), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(1046), 1,
      anon_sym_RPAREN,
    STATE(576), 1,
      sym__for,
    STATE(674), 1,
      sym_missing_parenthesis_end,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17797] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(703), 1,
      anon_sym_RPAREN,
    ACTIONS(713), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(214), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17820] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(980), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(1048), 1,
      anon_sym_RPAREN,
    STATE(380), 1,
      sym_missing_parenthesis_end,
    STATE(576), 1,
      sym__for,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17843] = 7,
    ACTIONS(974), 1,
      anon_sym_and2,
    ACTIONS(976), 1,
      anon_sym_or,
    STATE(34), 1,
      sym__and,
    STATE(35), 1,
      sym__or,
    STATE(567), 1,
      aux_sym_or_expression_repeat1,
    STATE(571), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(727), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
  [17866] = 7,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1050), 1,
      anon_sym_ERROR_missing_update_field,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(322), 1,
      sym_missing_update_field,
    STATE(699), 1,
      sym_path,
  [17888] = 7,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1052), 1,
      anon_sym_ERROR_missing_update_field,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(441), 1,
      sym_missing_update_field,
    STATE(706), 1,
      sym_path,
  [17910] = 7,
    ACTIONS(466), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(472), 1,
      aux_sym_ident_token1,
    ACTIONS(1054), 1,
      anon_sym_ERROR_missing_delete_field,
    STATE(307), 1,
      sym_ident,
    STATE(371), 1,
      sym_missing_identifier,
    STATE(461), 1,
      sym_missing_delete_field,
    STATE(464), 1,
      sym_path,
  [17932] = 7,
    ACTIONS(412), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(418), 1,
      aux_sym_ident_token1,
    ACTIONS(1056), 1,
      anon_sym_ERROR_missing_delete_field,
    STATE(305), 1,
      sym_ident,
    STATE(418), 1,
      sym_missing_identifier,
    STATE(465), 1,
      sym_missing_delete_field,
    STATE(467), 1,
      sym_path,
  [17954] = 7,
    ACTIONS(1058), 1,
      ts_builtin_sym_end,
    ACTIONS(1060), 1,
      anon_sym_RBRACK,
    ACTIONS(1062), 1,
      anon_sym_RPAREN,
    ACTIONS(1064), 1,
      anon_sym_ERROR_missing_array_query_end,
    ACTIONS(1066), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(735), 1,
      sym_missing_array_query_end,
    STATE(739), 1,
      sym_missing_element_query_end,
  [17976] = 7,
    ACTIONS(432), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(438), 1,
      aux_sym_ident_token1,
    ACTIONS(1068), 1,
      anon_sym_LBRACK,
    STATE(236), 1,
      sym_ident,
    STATE(280), 1,
      sym_missing_identifier,
    STATE(283), 1,
      sym_path,
    STATE(316), 1,
      sym_array,
  [17998] = 7,
    ACTIONS(432), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(438), 1,
      aux_sym_ident_token1,
    ACTIONS(1070), 1,
      anon_sym_ERROR_missing_delete_field,
    STATE(236), 1,
      sym_ident,
    STATE(280), 1,
      sym_missing_identifier,
    STATE(352), 1,
      sym_missing_delete_field,
    STATE(357), 1,
      sym_path,
  [18020] = 7,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1072), 1,
      anon_sym_ERROR_missing_update_field,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(99), 1,
      sym_ident,
    STATE(469), 1,
      sym_missing_update_field,
    STATE(702), 1,
      sym_path,
  [18042] = 7,
    ACTIONS(412), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(418), 1,
      aux_sym_ident_token1,
    ACTIONS(1074), 1,
      anon_sym_LBRACK,
    STATE(305), 1,
      sym_ident,
    STATE(418), 1,
      sym_missing_identifier,
    STATE(425), 1,
      sym_path,
    STATE(448), 1,
      sym_array,
  [18064] = 7,
    ACTIONS(466), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(472), 1,
      aux_sym_ident_token1,
    ACTIONS(1076), 1,
      anon_sym_LBRACK,
    STATE(307), 1,
      sym_ident,
    STATE(371), 1,
      sym_missing_identifier,
    STATE(421), 1,
      sym_path,
    STATE(439), 1,
      sym_array,
  [18086] = 5,
    ACTIONS(1078), 1,
      anon_sym_DQUOTE,
    ACTIONS(1082), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(154), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18103] = 5,
    ACTIONS(1084), 1,
      anon_sym_DQUOTE,
    ACTIONS(1088), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(440), 1,
      sym_missing_string_end,
    STATE(578), 1,
      aux_sym__string_content,
    ACTIONS(1086), 2,
      sym_string_content,
      sym_escape_sequence,
  [18120] = 3,
    STATE(35), 1,
      sym__or,
    STATE(579), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(752), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18133] = 5,
    ACTIONS(1090), 1,
      anon_sym_DQUOTE,
    ACTIONS(1094), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(145), 1,
      sym_missing_string_end,
    STATE(585), 1,
      aux_sym__string_content,
    ACTIONS(1092), 2,
      sym_string_content,
      sym_escape_sequence,
  [18150] = 5,
    ACTIONS(1096), 1,
      anon_sym_DQUOTE,
    ACTIONS(1100), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(156), 1,
      sym_missing_string_end,
    STATE(592), 1,
      aux_sym__string_content,
    ACTIONS(1098), 2,
      sym_string_content,
      sym_escape_sequence,
  [18167] = 5,
    ACTIONS(1102), 1,
      anon_sym_DQUOTE,
    ACTIONS(1104), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    STATE(741), 1,
      sym_missing_string_end,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18184] = 3,
    STATE(34), 1,
      sym__and,
    STATE(580), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(748), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18197] = 6,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(158), 1,
      sym_missing_string_end,
    STATE(694), 1,
      sym_pair,
    STATE(712), 1,
      sym_string,
  [18216] = 5,
    ACTIONS(1106), 1,
      anon_sym_DQUOTE,
    ACTIONS(1108), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(256), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18233] = 6,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1110), 1,
      anon_sym_ERROR_missing_iterator,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(507), 1,
      sym_missing_iterator,
    STATE(721), 1,
      sym_ident,
  [18252] = 6,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1112), 1,
      anon_sym_ERROR_missing_iterator,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(336), 1,
      sym_missing_iterator,
    STATE(722), 1,
      sym_ident,
  [18271] = 6,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1114), 1,
      anon_sym_ERROR_missing_iterator,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(486), 1,
      sym_missing_iterator,
    STATE(717), 1,
      sym_ident,
  [18290] = 5,
    ACTIONS(1082), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1116), 1,
      anon_sym_DQUOTE,
    STATE(147), 1,
      sym_missing_string_end,
    STATE(565), 1,
      aux_sym__string_content,
    ACTIONS(1118), 2,
      sym_string_content,
      sym_escape_sequence,
  [18307] = 5,
    ACTIONS(1088), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1120), 1,
      anon_sym_DQUOTE,
    STATE(451), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18324] = 4,
    ACTIONS(1122), 1,
      anon_sym_or,
    STATE(35), 1,
      sym__or,
    STATE(579), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(739), 3,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
  [18339] = 4,
    ACTIONS(1125), 1,
      anon_sym_and2,
    STATE(34), 1,
      sym__and,
    STATE(580), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(727), 3,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_or,
  [18354] = 5,
    ACTIONS(1108), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1128), 1,
      anon_sym_DQUOTE,
    STATE(265), 1,
      sym_missing_string_end,
    STATE(573), 1,
      aux_sym__string_content,
    ACTIONS(1130), 2,
      sym_string_content,
      sym_escape_sequence,
  [18371] = 5,
    ACTIONS(1132), 1,
      anon_sym_DQUOTE,
    ACTIONS(1134), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(378), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18388] = 5,
    ACTIONS(1136), 1,
      anon_sym_DQUOTE,
    ACTIONS(1138), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(78), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18405] = 5,
    ACTIONS(1140), 1,
      anon_sym_DQUOTE,
    ACTIONS(1142), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(494), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18422] = 5,
    ACTIONS(1094), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1144), 1,
      anon_sym_DQUOTE,
    STATE(148), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18439] = 5,
    ACTIONS(1134), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1146), 1,
      anon_sym_DQUOTE,
    STATE(388), 1,
      sym_missing_string_end,
    STATE(582), 1,
      aux_sym__string_content,
    ACTIONS(1148), 2,
      sym_string_content,
      sym_escape_sequence,
  [18456] = 5,
    ACTIONS(1138), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1150), 1,
      anon_sym_DQUOTE,
    STATE(75), 1,
      sym_missing_string_end,
    STATE(583), 1,
      aux_sym__string_content,
    ACTIONS(1152), 2,
      sym_string_content,
      sym_escape_sequence,
  [18473] = 5,
    ACTIONS(1142), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1154), 1,
      anon_sym_DQUOTE,
    STATE(509), 1,
      sym_missing_string_end,
    STATE(584), 1,
      aux_sym__string_content,
    ACTIONS(1156), 2,
      sym_string_content,
      sym_escape_sequence,
  [18490] = 5,
    ACTIONS(1104), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1158), 1,
      anon_sym_DQUOTE,
    STATE(570), 1,
      aux_sym__string_content,
    STATE(724), 1,
      sym_missing_string_end,
    ACTIONS(1160), 2,
      sym_string_content,
      sym_escape_sequence,
  [18507] = 5,
    ACTIONS(1162), 1,
      anon_sym_DQUOTE,
    ACTIONS(1164), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(353), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18524] = 5,
    ACTIONS(1166), 1,
      anon_sym_DQUOTE,
    ACTIONS(1168), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(397), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18541] = 5,
    ACTIONS(1100), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1170), 1,
      anon_sym_DQUOTE,
    STATE(161), 1,
      sym_missing_string_end,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1080), 2,
      sym_string_content,
      sym_escape_sequence,
  [18558] = 5,
    ACTIONS(1168), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1172), 1,
      anon_sym_DQUOTE,
    STATE(407), 1,
      sym_missing_string_end,
    STATE(591), 1,
      aux_sym__string_content,
    ACTIONS(1174), 2,
      sym_string_content,
      sym_escape_sequence,
  [18575] = 5,
    ACTIONS(1164), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1176), 1,
      anon_sym_DQUOTE,
    STATE(344), 1,
      sym_missing_string_end,
    STATE(590), 1,
      aux_sym__string_content,
    ACTIONS(1178), 2,
      sym_string_content,
      sym_escape_sequence,
  [18592] = 5,
    ACTIONS(968), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1182), 1,
      anon_sym_RBRACE,
    STATE(271), 1,
      sym_missing_brace_end,
    STATE(629), 1,
      aux_sym_object_repeat1,
  [18608] = 5,
    ACTIONS(1008), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1184), 1,
      anon_sym_RBRACE,
    STATE(499), 1,
      sym_missing_brace_end,
    STATE(626), 1,
      aux_sym_object_repeat1,
  [18624] = 5,
    ACTIONS(135), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1186), 1,
      anon_sym_RBRACK,
    STATE(134), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [18640] = 5,
    ACTIONS(1022), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1188), 1,
      anon_sym_RBRACE,
    STATE(136), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [18656] = 5,
    ACTIONS(151), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1190), 1,
      anon_sym_RBRACK,
    STATE(456), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [18672] = 5,
    ACTIONS(996), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1192), 1,
      anon_sym_RBRACE,
    STATE(181), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [18688] = 5,
    ACTIONS(1018), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1194), 1,
      anon_sym_RBRACE,
    STATE(398), 1,
      sym_missing_brace_end,
    STATE(613), 1,
      aux_sym_object_repeat1,
  [18704] = 5,
    ACTIONS(143), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1196), 1,
      anon_sym_RBRACK,
    STATE(639), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [18720] = 5,
    ACTIONS(996), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1198), 1,
      anon_sym_RBRACE,
    STATE(167), 1,
      sym_missing_brace_end,
    STATE(600), 1,
      aux_sym_object_repeat1,
  [18736] = 5,
    ACTIONS(1000), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1200), 1,
      anon_sym_RBRACE,
    STATE(606), 1,
      aux_sym_object_repeat1,
    STATE(677), 1,
      sym_missing_brace_end,
  [18752] = 5,
    ACTIONS(988), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1202), 1,
      anon_sym_RBRACE,
    STATE(177), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [18768] = 5,
    ACTIONS(1000), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1204), 1,
      anon_sym_RBRACE,
    STATE(644), 1,
      aux_sym_object_repeat1,
    STATE(675), 1,
      sym_missing_brace_end,
  [18784] = 5,
    ACTIONS(1206), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(1208), 1,
      aux_sym_ident_token1,
    STATE(82), 1,
      sym_path,
    STATE(296), 1,
      sym_ident,
    STATE(334), 1,
      sym_missing_identifier,
  [18800] = 5,
    ACTIONS(181), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1210), 1,
      anon_sym_RBRACK,
    STATE(172), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [18816] = 5,
    ACTIONS(151), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(946), 1,
      anon_sym_RBRACK,
    STATE(481), 1,
      sym_missing_array_end,
    STATE(599), 1,
      aux_sym_array_repeat1,
  [18832] = 5,
    ACTIONS(1022), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1212), 1,
      anon_sym_RBRACE,
    STATE(110), 1,
      sym_missing_brace_end,
    STATE(598), 1,
      aux_sym_object_repeat1,
  [18848] = 5,
    ACTIONS(163), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1214), 1,
      anon_sym_RBRACK,
    STATE(396), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [18864] = 5,
    ACTIONS(187), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1216), 1,
      anon_sym_RBRACK,
    STATE(165), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [18880] = 5,
    ACTIONS(1018), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1218), 1,
      anon_sym_RBRACE,
    STATE(395), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [18896] = 5,
    ACTIONS(157), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(950), 1,
      anon_sym_RBRACK,
    STATE(326), 1,
      sym_missing_array_end,
    STATE(619), 1,
      aux_sym_array_repeat1,
  [18912] = 5,
    ACTIONS(1004), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1220), 1,
      anon_sym_RBRACE,
    STATE(340), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [18928] = 5,
    ACTIONS(1026), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1222), 1,
      anon_sym_RBRACE,
    STATE(455), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [18944] = 5,
    ACTIONS(1026), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1224), 1,
      anon_sym_RBRACE,
    STATE(475), 1,
      sym_missing_brace_end,
    STATE(616), 1,
      aux_sym_object_repeat1,
  [18960] = 5,
    ACTIONS(992), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1226), 1,
      anon_sym_RBRACE,
    STATE(208), 1,
      sym_missing_brace_end,
    STATE(628), 1,
      aux_sym_object_repeat1,
  [18976] = 5,
    ACTIONS(157), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1228), 1,
      anon_sym_RBRACK,
    STATE(338), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [18992] = 5,
    ACTIONS(1206), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(1208), 1,
      aux_sym_ident_token1,
    STATE(76), 1,
      sym_path,
    STATE(296), 1,
      sym_ident,
    STATE(334), 1,
      sym_missing_identifier,
  [19008] = 3,
    STATE(621), 1,
      aux_sym__string_content,
    ACTIONS(1230), 2,
      anon_sym_DQUOTE,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1232), 2,
      sym_string_content,
      sym_escape_sequence,
  [19020] = 5,
    ACTIONS(1004), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1235), 1,
      anon_sym_RBRACE,
    STATE(331), 1,
      sym_missing_brace_end,
    STATE(615), 1,
      aux_sym_object_repeat1,
  [19036] = 5,
    ACTIONS(1206), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(1208), 1,
      aux_sym_ident_token1,
    STATE(77), 1,
      sym_path,
    STATE(296), 1,
      sym_ident,
    STATE(334), 1,
      sym_missing_identifier,
  [19052] = 5,
    ACTIONS(169), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(960), 1,
      anon_sym_RBRACK,
    STATE(485), 1,
      sym_missing_array_end,
    STATE(632), 1,
      aux_sym_array_repeat1,
  [19068] = 5,
    ACTIONS(1014), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1237), 1,
      anon_sym_RBRACE,
    STATE(375), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [19084] = 5,
    ACTIONS(1008), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1239), 1,
      anon_sym_RBRACE,
    STATE(511), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [19100] = 5,
    ACTIONS(175), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1241), 1,
      anon_sym_RBRACK,
    STATE(376), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [19116] = 5,
    ACTIONS(992), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1243), 1,
      anon_sym_RBRACE,
    STATE(213), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [19132] = 5,
    ACTIONS(968), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1245), 1,
      anon_sym_RBRACE,
    STATE(253), 1,
      sym_missing_brace_end,
    STATE(644), 1,
      aux_sym_object_repeat1,
  [19148] = 5,
    ACTIONS(193), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1247), 1,
      anon_sym_RBRACK,
    STATE(212), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [19164] = 4,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    STATE(574), 1,
      sym__for,
    STATE(58), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [19178] = 5,
    ACTIONS(169), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1249), 1,
      anon_sym_RBRACK,
    STATE(496), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [19194] = 4,
    ACTIONS(203), 1,
      anon_sym_for,
    ACTIONS(261), 1,
      anon_sym_ERROR_missing_main_iterator,
    STATE(575), 1,
      sym__for,
    STATE(42), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [19208] = 4,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    STATE(576), 1,
      sym__for,
    STATE(59), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [19222] = 5,
    ACTIONS(988), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1251), 1,
      anon_sym_RBRACE,
    STATE(166), 1,
      sym_missing_brace_end,
    STATE(605), 1,
      aux_sym_object_repeat1,
  [19238] = 5,
    ACTIONS(199), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(944), 1,
      anon_sym_COMMA,
    ACTIONS(1253), 1,
      anon_sym_RBRACK,
    STATE(262), 1,
      sym_missing_array_end,
    STATE(645), 1,
      aux_sym_array_repeat1,
  [19254] = 1,
    ACTIONS(1255), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
  [19262] = 5,
    ACTIONS(1014), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1180), 1,
      anon_sym_COMMA,
    ACTIONS(1257), 1,
      anon_sym_RBRACE,
    STATE(379), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [19278] = 1,
    ACTIONS(663), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19285] = 4,
    ACTIONS(466), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(472), 1,
      aux_sym_ident_token1,
    STATE(371), 1,
      sym_missing_identifier,
    STATE(409), 1,
      sym_ident,
  [19298] = 1,
    ACTIONS(779), 4,
      anon_sym_and,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_brace_end,
  [19305] = 1,
    ACTIONS(783), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19312] = 1,
    ACTIONS(795), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19319] = 3,
    ACTIONS(1259), 1,
      anon_sym_COMMA,
    STATE(644), 1,
      aux_sym_object_repeat1,
    ACTIONS(1262), 2,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_brace_end,
  [19330] = 3,
    ACTIONS(1266), 1,
      anon_sym_COMMA,
    STATE(645), 1,
      aux_sym_array_repeat1,
    ACTIONS(1264), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_end,
  [19341] = 1,
    ACTIONS(775), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19348] = 4,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(733), 1,
      sym_ident,
  [19361] = 4,
    ACTIONS(611), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(615), 1,
      aux_sym_ident_token1,
    STATE(347), 1,
      sym_missing_identifier,
    STATE(355), 1,
      sym_ident,
  [19374] = 4,
    ACTIONS(1206), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(1208), 1,
      aux_sym_ident_token1,
    STATE(334), 1,
      sym_missing_identifier,
    STATE(360), 1,
      sym_ident,
  [19387] = 4,
    ACTIONS(577), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(581), 1,
      aux_sym_ident_token1,
    STATE(719), 1,
      sym_missing_identifier,
    STATE(720), 1,
      sym_ident,
  [19400] = 4,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(732), 1,
      sym_ident,
  [19413] = 4,
    ACTIONS(639), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(643), 1,
      aux_sym_ident_token1,
    STATE(240), 1,
      sym_ident,
    STATE(245), 1,
      sym_missing_identifier,
  [19426] = 4,
    ACTIONS(412), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(418), 1,
      aux_sym_ident_token1,
    STATE(415), 1,
      sym_ident,
    STATE(418), 1,
      sym_missing_identifier,
  [19439] = 1,
    ACTIONS(799), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19446] = 1,
    ACTIONS(779), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19453] = 1,
    ACTIONS(787), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19460] = 1,
    ACTIONS(647), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19467] = 1,
    ACTIONS(653), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19474] = 1,
    ACTIONS(791), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19481] = 1,
    ACTIONS(657), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19488] = 1,
    ACTIONS(675), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19495] = 4,
    ACTIONS(53), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(59), 1,
      aux_sym_ident_token1,
    STATE(126), 1,
      sym_ident,
    STATE(132), 1,
      sym_missing_identifier,
  [19508] = 1,
    ACTIONS(524), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19515] = 4,
    ACTIONS(101), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(107), 1,
      aux_sym_ident_token1,
    STATE(71), 1,
      sym_missing_identifier,
    STATE(72), 1,
      sym_ident,
  [19528] = 1,
    ACTIONS(528), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19535] = 1,
    ACTIONS(524), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19542] = 4,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(723), 1,
      sym_ident,
  [19555] = 4,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(98), 1,
      sym_missing_identifier,
    STATE(151), 1,
      sym_ident,
  [19568] = 4,
    ACTIONS(518), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(522), 1,
      aux_sym_ident_token1,
    STATE(304), 1,
      sym_ident,
    STATE(330), 1,
      sym_missing_identifier,
  [19581] = 1,
    ACTIONS(535), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19588] = 1,
    ACTIONS(539), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19595] = 4,
    ACTIONS(77), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(83), 1,
      aux_sym_ident_token1,
    STATE(119), 1,
      sym_ident,
    STATE(137), 1,
      sym_missing_identifier,
  [19608] = 4,
    ACTIONS(432), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(438), 1,
      aux_sym_ident_token1,
    STATE(276), 1,
      sym_ident,
    STATE(280), 1,
      sym_missing_identifier,
  [19621] = 1,
    ACTIONS(561), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19628] = 1,
    ACTIONS(667), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19635] = 1,
    ACTIONS(557), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19642] = 1,
    ACTIONS(583), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19649] = 1,
    ACTIONS(535), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [19656] = 3,
    ACTIONS(1269), 1,
      anon_sym_RBRACK,
    ACTIONS(1271), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(318), 1,
      sym_missing_array_query_end,
  [19666] = 3,
    ACTIONS(345), 1,
      anon_sym_and,
    ACTIONS(1273), 1,
      anon_sym_DOT,
    STATE(680), 1,
      aux_sym_path_repeat1,
  [19676] = 1,
    ACTIONS(1276), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_brace_end,
  [19682] = 3,
    ACTIONS(1278), 1,
      anon_sym_RBRACK,
    ACTIONS(1280), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(502), 1,
      sym_missing_array_query_end,
  [19692] = 3,
    ACTIONS(1282), 1,
      anon_sym_RPAREN,
    ACTIONS(1284), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(490), 1,
      sym_missing_element_query_end,
  [19702] = 3,
    ACTIONS(341), 1,
      anon_sym_and,
    ACTIONS(1286), 1,
      anon_sym_DOT,
    STATE(680), 1,
      aux_sym_path_repeat1,
  [19712] = 3,
    ACTIONS(1288), 1,
      sym_pos_int,
    ACTIONS(1290), 1,
      anon_sym_ERROR_missing_limit_value,
    STATE(497), 1,
      sym_missing_limit_value,
  [19722] = 3,
    ACTIONS(1292), 1,
      sym_pos_int,
    ACTIONS(1294), 1,
      anon_sym_ERROR_missing_offset_value,
    STATE(460), 1,
      sym_missing_offset_value,
  [19732] = 3,
    ACTIONS(1296), 1,
      anon_sym_RBRACK,
    ACTIONS(1298), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(199), 1,
      sym_missing_array_query_end,
  [19742] = 3,
    ACTIONS(1300), 1,
      anon_sym_RPAREN,
    ACTIONS(1302), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(195), 1,
      sym_missing_element_query_end,
  [19752] = 3,
    ACTIONS(1304), 1,
      sym_pos_int,
    ACTIONS(1306), 1,
      anon_sym_ERROR_missing_limit_value,
    STATE(457), 1,
      sym_missing_limit_value,
  [19762] = 3,
    ACTIONS(1308), 1,
      sym_pos_int,
    ACTIONS(1310), 1,
      anon_sym_ERROR_missing_offset_value,
    STATE(443), 1,
      sym_missing_offset_value,
  [19772] = 3,
    ACTIONS(1312), 1,
      anon_sym_RBRACK,
    ACTIONS(1314), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(488), 1,
      sym_missing_array_query_end,
  [19782] = 3,
    ACTIONS(1316), 1,
      anon_sym_RPAREN,
    ACTIONS(1318), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(325), 1,
      sym_missing_element_query_end,
  [19792] = 3,
    ACTIONS(1320), 1,
      anon_sym_RPAREN,
    ACTIONS(1322), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(482), 1,
      sym_missing_element_query_end,
  [19802] = 1,
    ACTIONS(1262), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_brace_end,
  [19808] = 3,
    ACTIONS(311), 1,
      anon_sym_and,
    ACTIONS(1286), 1,
      anon_sym_DOT,
    STATE(684), 1,
      aux_sym_path_repeat1,
  [19818] = 3,
    ACTIONS(1064), 1,
      anon_sym_ERROR_missing_array_query_end,
    ACTIONS(1324), 1,
      anon_sym_RBRACK,
    STATE(205), 1,
      sym_missing_array_query_end,
  [19828] = 3,
    ACTIONS(1326), 1,
      anon_sym_RBRACK,
    ACTIONS(1328), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(96), 1,
      sym_missing_array_query_end,
  [19838] = 3,
    ACTIONS(1330), 1,
      anon_sym_RPAREN,
    ACTIONS(1332), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(105), 1,
      sym_missing_element_query_end,
  [19848] = 3,
    ACTIONS(1334), 1,
      anon_sym_EQ,
    ACTIONS(1336), 1,
      anon_sym_ERROR_missing_equals,
    STATE(138), 1,
      sym_missing_equals,
  [19858] = 1,
    ACTIONS(1264), 3,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      anon_sym_ERROR_missing_array_end,
  [19864] = 3,
    ACTIONS(1066), 1,
      anon_sym_ERROR_missing_element_query_end,
    ACTIONS(1338), 1,
      anon_sym_RPAREN,
    STATE(204), 1,
      sym_missing_element_query_end,
  [19874] = 3,
    ACTIONS(1336), 1,
      anon_sym_ERROR_missing_equals,
    ACTIONS(1340), 1,
      anon_sym_EQ,
    STATE(111), 1,
      sym_missing_equals,
  [19884] = 3,
    ACTIONS(1342), 1,
      anon_sym_RBRACK,
    ACTIONS(1344), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(404), 1,
      sym_missing_array_query_end,
  [19894] = 3,
    ACTIONS(1346), 1,
      anon_sym_RPAREN,
    ACTIONS(1348), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(401), 1,
      sym_missing_element_query_end,
  [19904] = 3,
    ACTIONS(1350), 1,
      anon_sym_RBRACK,
    ACTIONS(1352), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(174), 1,
      sym_missing_array_query_end,
  [19914] = 3,
    ACTIONS(1336), 1,
      anon_sym_ERROR_missing_equals,
    ACTIONS(1354), 1,
      anon_sym_EQ,
    STATE(121), 1,
      sym_missing_equals,
  [19924] = 3,
    ACTIONS(1356), 1,
      anon_sym_RPAREN,
    ACTIONS(1358), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(163), 1,
      sym_missing_element_query_end,
  [19934] = 3,
    ACTIONS(1360), 1,
      anon_sym_RPAREN,
    ACTIONS(1362), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(678), 1,
      sym_missing_element_query_end,
  [19944] = 3,
    ACTIONS(1364), 1,
      anon_sym_RBRACK,
    ACTIONS(1366), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(385), 1,
      sym_missing_array_query_end,
  [19954] = 3,
    ACTIONS(1368), 1,
      anon_sym_RPAREN,
    ACTIONS(1370), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(382), 1,
      sym_missing_element_query_end,
  [19964] = 3,
    ACTIONS(1372), 1,
      anon_sym_RBRACK,
    ACTIONS(1374), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(666), 1,
      sym_missing_array_query_end,
  [19974] = 3,
    ACTIONS(1376), 1,
      anon_sym_COLON,
    ACTIONS(1378), 1,
      anon_sym_ERROR_missing_colon,
    STATE(118), 1,
      sym_missing_colon,
  [19984] = 3,
    ACTIONS(1380), 1,
      sym_pos_int,
    ACTIONS(1382), 1,
      anon_sym_ERROR_missing_offset_value,
    STATE(349), 1,
      sym_missing_offset_value,
  [19994] = 3,
    ACTIONS(1384), 1,
      sym_pos_int,
    ACTIONS(1386), 1,
      anon_sym_ERROR_missing_limit_value,
    STATE(343), 1,
      sym_missing_limit_value,
  [20004] = 3,
    ACTIONS(1388), 1,
      anon_sym_RBRACK,
    ACTIONS(1390), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(257), 1,
      sym_missing_array_query_end,
  [20014] = 3,
    ACTIONS(1392), 1,
      anon_sym_RPAREN,
    ACTIONS(1394), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(255), 1,
      sym_missing_element_query_end,
  [20024] = 2,
    ACTIONS(1396), 1,
      anon_sym_in,
    STATE(563), 1,
      sym__in,
  [20031] = 1,
    ACTIONS(380), 2,
      anon_sym_and,
      anon_sym_DOT,
  [20036] = 1,
    ACTIONS(376), 2,
      anon_sym_and,
      anon_sym_DOT,
  [20041] = 1,
    ACTIONS(345), 2,
      anon_sym_and,
      anon_sym_DOT,
  [20046] = 2,
    ACTIONS(1398), 1,
      anon_sym_in,
    STATE(564), 1,
      sym__in,
  [20053] = 2,
    ACTIONS(1400), 1,
      anon_sym_in,
    STATE(560), 1,
      sym__in,
  [20060] = 1,
    ACTIONS(1402), 1,
      anon_sym_EQ,
  [20064] = 1,
    ACTIONS(396), 1,
      anon_sym_and,
  [20068] = 1,
    ACTIONS(444), 1,
      anon_sym_and,
  [20072] = 1,
    ACTIONS(1404), 1,
      anon_sym_and,
  [20076] = 1,
    ACTIONS(1406), 1,
      ts_builtin_sym_end,
  [20080] = 1,
    ACTIONS(1408), 1,
      anon_sym_EQ,
  [20084] = 1,
    ACTIONS(1410), 1,
      anon_sym_and,
  [20088] = 1,
    ACTIONS(1406), 1,
      ts_builtin_sym_end,
  [20092] = 1,
    ACTIONS(1412), 1,
      anon_sym_EQ,
  [20096] = 1,
    ACTIONS(1414), 1,
      anon_sym_EQ,
  [20100] = 1,
    ACTIONS(1416), 1,
      anon_sym_EQ,
  [20104] = 1,
    ACTIONS(1418), 1,
      ts_builtin_sym_end,
  [20108] = 1,
    ACTIONS(1406), 1,
      ts_builtin_sym_end,
  [20112] = 1,
    ACTIONS(1420), 1,
      anon_sym_and,
  [20116] = 1,
    ACTIONS(1422), 1,
      anon_sym_EQ,
  [20120] = 1,
    ACTIONS(1424), 1,
      anon_sym_and,
  [20124] = 1,
    ACTIONS(1406), 1,
      ts_builtin_sym_end,
  [20128] = 1,
    ACTIONS(543), 1,
      anon_sym_and,
  [20132] = 1,
    ACTIONS(440), 1,
      anon_sym_and,
  [20136] = 1,
    ACTIONS(450), 1,
      anon_sym_and,
  [20140] = 1,
    ACTIONS(1426), 1,
      ts_builtin_sym_end,
  [20144] = 1,
    ACTIONS(1428), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 92,
  [SMALL_STATE(4)] = 184,
  [SMALL_STATE(5)] = 276,
  [SMALL_STATE(6)] = 368,
  [SMALL_STATE(7)] = 460,
  [SMALL_STATE(8)] = 552,
  [SMALL_STATE(9)] = 644,
  [SMALL_STATE(10)] = 724,
  [SMALL_STATE(11)] = 804,
  [SMALL_STATE(12)] = 884,
  [SMALL_STATE(13)] = 964,
  [SMALL_STATE(14)] = 1044,
  [SMALL_STATE(15)] = 1122,
  [SMALL_STATE(16)] = 1200,
  [SMALL_STATE(17)] = 1278,
  [SMALL_STATE(18)] = 1358,
  [SMALL_STATE(19)] = 1438,
  [SMALL_STATE(20)] = 1518,
  [SMALL_STATE(21)] = 1590,
  [SMALL_STATE(22)] = 1662,
  [SMALL_STATE(23)] = 1734,
  [SMALL_STATE(24)] = 1814,
  [SMALL_STATE(25)] = 1886,
  [SMALL_STATE(26)] = 1966,
  [SMALL_STATE(27)] = 2046,
  [SMALL_STATE(28)] = 2126,
  [SMALL_STATE(29)] = 2198,
  [SMALL_STATE(30)] = 2270,
  [SMALL_STATE(31)] = 2342,
  [SMALL_STATE(32)] = 2414,
  [SMALL_STATE(33)] = 2494,
  [SMALL_STATE(34)] = 2566,
  [SMALL_STATE(35)] = 2638,
  [SMALL_STATE(36)] = 2710,
  [SMALL_STATE(37)] = 2782,
  [SMALL_STATE(38)] = 2862,
  [SMALL_STATE(39)] = 2942,
  [SMALL_STATE(40)] = 3022,
  [SMALL_STATE(41)] = 3102,
  [SMALL_STATE(42)] = 3181,
  [SMALL_STATE(43)] = 3260,
  [SMALL_STATE(44)] = 3339,
  [SMALL_STATE(45)] = 3418,
  [SMALL_STATE(46)] = 3497,
  [SMALL_STATE(47)] = 3568,
  [SMALL_STATE(48)] = 3639,
  [SMALL_STATE(49)] = 3710,
  [SMALL_STATE(50)] = 3781,
  [SMALL_STATE(51)] = 3852,
  [SMALL_STATE(52)] = 3923,
  [SMALL_STATE(53)] = 3994,
  [SMALL_STATE(54)] = 4065,
  [SMALL_STATE(55)] = 4136,
  [SMALL_STATE(56)] = 4207,
  [SMALL_STATE(57)] = 4278,
  [SMALL_STATE(58)] = 4349,
  [SMALL_STATE(59)] = 4425,
  [SMALL_STATE(60)] = 4501,
  [SMALL_STATE(61)] = 4577,
  [SMALL_STATE(62)] = 4617,
  [SMALL_STATE(63)] = 4693,
  [SMALL_STATE(64)] = 4769,
  [SMALL_STATE(65)] = 4809,
  [SMALL_STATE(66)] = 4885,
  [SMALL_STATE(67)] = 4961,
  [SMALL_STATE(68)] = 5001,
  [SMALL_STATE(69)] = 5077,
  [SMALL_STATE(70)] = 5153,
  [SMALL_STATE(71)] = 5229,
  [SMALL_STATE(72)] = 5264,
  [SMALL_STATE(73)] = 5299,
  [SMALL_STATE(74)] = 5334,
  [SMALL_STATE(75)] = 5374,
  [SMALL_STATE(76)] = 5408,
  [SMALL_STATE(77)] = 5470,
  [SMALL_STATE(78)] = 5532,
  [SMALL_STATE(79)] = 5566,
  [SMALL_STATE(80)] = 5600,
  [SMALL_STATE(81)] = 5638,
  [SMALL_STATE(82)] = 5672,
  [SMALL_STATE(83)] = 5734,
  [SMALL_STATE(84)] = 5771,
  [SMALL_STATE(85)] = 5808,
  [SMALL_STATE(86)] = 5845,
  [SMALL_STATE(87)] = 5888,
  [SMALL_STATE(88)] = 5931,
  [SMALL_STATE(89)] = 5968,
  [SMALL_STATE(90)] = 6005,
  [SMALL_STATE(91)] = 6042,
  [SMALL_STATE(92)] = 6102,
  [SMALL_STATE(93)] = 6138,
  [SMALL_STATE(94)] = 6194,
  [SMALL_STATE(95)] = 6226,
  [SMALL_STATE(96)] = 6258,
  [SMALL_STATE(97)] = 6290,
  [SMALL_STATE(98)] = 6322,
  [SMALL_STATE(99)] = 6354,
  [SMALL_STATE(100)] = 6390,
  [SMALL_STATE(101)] = 6426,
  [SMALL_STATE(102)] = 6458,
  [SMALL_STATE(103)] = 6490,
  [SMALL_STATE(104)] = 6522,
  [SMALL_STATE(105)] = 6578,
  [SMALL_STATE(106)] = 6610,
  [SMALL_STATE(107)] = 6642,
  [SMALL_STATE(108)] = 6674,
  [SMALL_STATE(109)] = 6730,
  [SMALL_STATE(110)] = 6786,
  [SMALL_STATE(111)] = 6818,
  [SMALL_STATE(112)] = 6874,
  [SMALL_STATE(113)] = 6930,
  [SMALL_STATE(114)] = 6986,
  [SMALL_STATE(115)] = 7042,
  [SMALL_STATE(116)] = 7102,
  [SMALL_STATE(117)] = 7158,
  [SMALL_STATE(118)] = 7214,
  [SMALL_STATE(119)] = 7270,
  [SMALL_STATE(120)] = 7302,
  [SMALL_STATE(121)] = 7358,
  [SMALL_STATE(122)] = 7414,
  [SMALL_STATE(123)] = 7450,
  [SMALL_STATE(124)] = 7506,
  [SMALL_STATE(125)] = 7562,
  [SMALL_STATE(126)] = 7598,
  [SMALL_STATE(127)] = 7630,
  [SMALL_STATE(128)] = 7662,
  [SMALL_STATE(129)] = 7694,
  [SMALL_STATE(130)] = 7754,
  [SMALL_STATE(131)] = 7786,
  [SMALL_STATE(132)] = 7818,
  [SMALL_STATE(133)] = 7850,
  [SMALL_STATE(134)] = 7906,
  [SMALL_STATE(135)] = 7938,
  [SMALL_STATE(136)] = 7970,
  [SMALL_STATE(137)] = 8002,
  [SMALL_STATE(138)] = 8034,
  [SMALL_STATE(139)] = 8090,
  [SMALL_STATE(140)] = 8146,
  [SMALL_STATE(141)] = 8178,
  [SMALL_STATE(142)] = 8234,
  [SMALL_STATE(143)] = 8269,
  [SMALL_STATE(144)] = 8300,
  [SMALL_STATE(145)] = 8331,
  [SMALL_STATE(146)] = 8362,
  [SMALL_STATE(147)] = 8399,
  [SMALL_STATE(148)] = 8430,
  [SMALL_STATE(149)] = 8461,
  [SMALL_STATE(150)] = 8496,
  [SMALL_STATE(151)] = 8533,
  [SMALL_STATE(152)] = 8564,
  [SMALL_STATE(153)] = 8595,
  [SMALL_STATE(154)] = 8626,
  [SMALL_STATE(155)] = 8657,
  [SMALL_STATE(156)] = 8697,
  [SMALL_STATE(157)] = 8727,
  [SMALL_STATE(158)] = 8767,
  [SMALL_STATE(159)] = 8797,
  [SMALL_STATE(160)] = 8827,
  [SMALL_STATE(161)] = 8867,
  [SMALL_STATE(162)] = 8897,
  [SMALL_STATE(163)] = 8937,
  [SMALL_STATE(164)] = 8966,
  [SMALL_STATE(165)] = 8995,
  [SMALL_STATE(166)] = 9024,
  [SMALL_STATE(167)] = 9053,
  [SMALL_STATE(168)] = 9082,
  [SMALL_STATE(169)] = 9111,
  [SMALL_STATE(170)] = 9140,
  [SMALL_STATE(171)] = 9169,
  [SMALL_STATE(172)] = 9198,
  [SMALL_STATE(173)] = 9227,
  [SMALL_STATE(174)] = 9256,
  [SMALL_STATE(175)] = 9285,
  [SMALL_STATE(176)] = 9314,
  [SMALL_STATE(177)] = 9343,
  [SMALL_STATE(178)] = 9372,
  [SMALL_STATE(179)] = 9405,
  [SMALL_STATE(180)] = 9434,
  [SMALL_STATE(181)] = 9463,
  [SMALL_STATE(182)] = 9492,
  [SMALL_STATE(183)] = 9521,
  [SMALL_STATE(184)] = 9572,
  [SMALL_STATE(185)] = 9601,
  [SMALL_STATE(186)] = 9630,
  [SMALL_STATE(187)] = 9659,
  [SMALL_STATE(188)] = 9692,
  [SMALL_STATE(189)] = 9721,
  [SMALL_STATE(190)] = 9750,
  [SMALL_STATE(191)] = 9783,
  [SMALL_STATE(192)] = 9812,
  [SMALL_STATE(193)] = 9841,
  [SMALL_STATE(194)] = 9870,
  [SMALL_STATE(195)] = 9899,
  [SMALL_STATE(196)] = 9928,
  [SMALL_STATE(197)] = 9957,
  [SMALL_STATE(198)] = 9986,
  [SMALL_STATE(199)] = 10019,
  [SMALL_STATE(200)] = 10048,
  [SMALL_STATE(201)] = 10076,
  [SMALL_STATE(202)] = 10104,
  [SMALL_STATE(203)] = 10132,
  [SMALL_STATE(204)] = 10160,
  [SMALL_STATE(205)] = 10188,
  [SMALL_STATE(206)] = 10216,
  [SMALL_STATE(207)] = 10244,
  [SMALL_STATE(208)] = 10271,
  [SMALL_STATE(209)] = 10298,
  [SMALL_STATE(210)] = 10325,
  [SMALL_STATE(211)] = 10352,
  [SMALL_STATE(212)] = 10379,
  [SMALL_STATE(213)] = 10406,
  [SMALL_STATE(214)] = 10433,
  [SMALL_STATE(215)] = 10460,
  [SMALL_STATE(216)] = 10487,
  [SMALL_STATE(217)] = 10525,
  [SMALL_STATE(218)] = 10571,
  [SMALL_STATE(219)] = 10609,
  [SMALL_STATE(220)] = 10655,
  [SMALL_STATE(221)] = 10701,
  [SMALL_STATE(222)] = 10739,
  [SMALL_STATE(223)] = 10773,
  [SMALL_STATE(224)] = 10819,
  [SMALL_STATE(225)] = 10857,
  [SMALL_STATE(226)] = 10895,
  [SMALL_STATE(227)] = 10923,
  [SMALL_STATE(228)] = 10951,
  [SMALL_STATE(229)] = 10979,
  [SMALL_STATE(230)] = 11007,
  [SMALL_STATE(231)] = 11035,
  [SMALL_STATE(232)] = 11065,
  [SMALL_STATE(233)] = 11095,
  [SMALL_STATE(234)] = 11130,
  [SMALL_STATE(235)] = 11157,
  [SMALL_STATE(236)] = 11192,
  [SMALL_STATE(237)] = 11219,
  [SMALL_STATE(238)] = 11254,
  [SMALL_STATE(239)] = 11289,
  [SMALL_STATE(240)] = 11320,
  [SMALL_STATE(241)] = 11343,
  [SMALL_STATE(242)] = 11378,
  [SMALL_STATE(243)] = 11413,
  [SMALL_STATE(244)] = 11440,
  [SMALL_STATE(245)] = 11475,
  [SMALL_STATE(246)] = 11498,
  [SMALL_STATE(247)] = 11533,
  [SMALL_STATE(248)] = 11560,
  [SMALL_STATE(249)] = 11583,
  [SMALL_STATE(250)] = 11614,
  [SMALL_STATE(251)] = 11649,
  [SMALL_STATE(252)] = 11684,
  [SMALL_STATE(253)] = 11706,
  [SMALL_STATE(254)] = 11728,
  [SMALL_STATE(255)] = 11750,
  [SMALL_STATE(256)] = 11772,
  [SMALL_STATE(257)] = 11794,
  [SMALL_STATE(258)] = 11816,
  [SMALL_STATE(259)] = 11838,
  [SMALL_STATE(260)] = 11860,
  [SMALL_STATE(261)] = 11882,
  [SMALL_STATE(262)] = 11904,
  [SMALL_STATE(263)] = 11926,
  [SMALL_STATE(264)] = 11948,
  [SMALL_STATE(265)] = 11970,
  [SMALL_STATE(266)] = 11992,
  [SMALL_STATE(267)] = 12014,
  [SMALL_STATE(268)] = 12036,
  [SMALL_STATE(269)] = 12058,
  [SMALL_STATE(270)] = 12080,
  [SMALL_STATE(271)] = 12102,
  [SMALL_STATE(272)] = 12124,
  [SMALL_STATE(273)] = 12146,
  [SMALL_STATE(274)] = 12168,
  [SMALL_STATE(275)] = 12190,
  [SMALL_STATE(276)] = 12212,
  [SMALL_STATE(277)] = 12234,
  [SMALL_STATE(278)] = 12256,
  [SMALL_STATE(279)] = 12278,
  [SMALL_STATE(280)] = 12300,
  [SMALL_STATE(281)] = 12322,
  [SMALL_STATE(282)] = 12344,
  [SMALL_STATE(283)] = 12369,
  [SMALL_STATE(284)] = 12392,
  [SMALL_STATE(285)] = 12417,
  [SMALL_STATE(286)] = 12442,
  [SMALL_STATE(287)] = 12467,
  [SMALL_STATE(288)] = 12492,
  [SMALL_STATE(289)] = 12517,
  [SMALL_STATE(290)] = 12544,
  [SMALL_STATE(291)] = 12569,
  [SMALL_STATE(292)] = 12592,
  [SMALL_STATE(293)] = 12619,
  [SMALL_STATE(294)] = 12644,
  [SMALL_STATE(295)] = 12669,
  [SMALL_STATE(296)] = 12694,
  [SMALL_STATE(297)] = 12719,
  [SMALL_STATE(298)] = 12744,
  [SMALL_STATE(299)] = 12771,
  [SMALL_STATE(300)] = 12798,
  [SMALL_STATE(301)] = 12823,
  [SMALL_STATE(302)] = 12843,
  [SMALL_STATE(303)] = 12863,
  [SMALL_STATE(304)] = 12883,
  [SMALL_STATE(305)] = 12903,
  [SMALL_STATE(306)] = 12927,
  [SMALL_STATE(307)] = 12947,
  [SMALL_STATE(308)] = 12971,
  [SMALL_STATE(309)] = 12991,
  [SMALL_STATE(310)] = 13011,
  [SMALL_STATE(311)] = 13031,
  [SMALL_STATE(312)] = 13051,
  [SMALL_STATE(313)] = 13071,
  [SMALL_STATE(314)] = 13091,
  [SMALL_STATE(315)] = 13111,
  [SMALL_STATE(316)] = 13131,
  [SMALL_STATE(317)] = 13151,
  [SMALL_STATE(318)] = 13171,
  [SMALL_STATE(319)] = 13191,
  [SMALL_STATE(320)] = 13215,
  [SMALL_STATE(321)] = 13235,
  [SMALL_STATE(322)] = 13255,
  [SMALL_STATE(323)] = 13275,
  [SMALL_STATE(324)] = 13295,
  [SMALL_STATE(325)] = 13315,
  [SMALL_STATE(326)] = 13335,
  [SMALL_STATE(327)] = 13355,
  [SMALL_STATE(328)] = 13375,
  [SMALL_STATE(329)] = 13395,
  [SMALL_STATE(330)] = 13415,
  [SMALL_STATE(331)] = 13435,
  [SMALL_STATE(332)] = 13455,
  [SMALL_STATE(333)] = 13475,
  [SMALL_STATE(334)] = 13499,
  [SMALL_STATE(335)] = 13519,
  [SMALL_STATE(336)] = 13543,
  [SMALL_STATE(337)] = 13563,
  [SMALL_STATE(338)] = 13583,
  [SMALL_STATE(339)] = 13603,
  [SMALL_STATE(340)] = 13627,
  [SMALL_STATE(341)] = 13647,
  [SMALL_STATE(342)] = 13667,
  [SMALL_STATE(343)] = 13687,
  [SMALL_STATE(344)] = 13707,
  [SMALL_STATE(345)] = 13727,
  [SMALL_STATE(346)] = 13747,
  [SMALL_STATE(347)] = 13767,
  [SMALL_STATE(348)] = 13787,
  [SMALL_STATE(349)] = 13807,
  [SMALL_STATE(350)] = 13827,
  [SMALL_STATE(351)] = 13847,
  [SMALL_STATE(352)] = 13867,
  [SMALL_STATE(353)] = 13887,
  [SMALL_STATE(354)] = 13907,
  [SMALL_STATE(355)] = 13927,
  [SMALL_STATE(356)] = 13947,
  [SMALL_STATE(357)] = 13967,
  [SMALL_STATE(358)] = 13987,
  [SMALL_STATE(359)] = 14007,
  [SMALL_STATE(360)] = 14027,
  [SMALL_STATE(361)] = 14047,
  [SMALL_STATE(362)] = 14066,
  [SMALL_STATE(363)] = 14085,
  [SMALL_STATE(364)] = 14104,
  [SMALL_STATE(365)] = 14123,
  [SMALL_STATE(366)] = 14142,
  [SMALL_STATE(367)] = 14161,
  [SMALL_STATE(368)] = 14180,
  [SMALL_STATE(369)] = 14199,
  [SMALL_STATE(370)] = 14218,
  [SMALL_STATE(371)] = 14237,
  [SMALL_STATE(372)] = 14256,
  [SMALL_STATE(373)] = 14275,
  [SMALL_STATE(374)] = 14294,
  [SMALL_STATE(375)] = 14313,
  [SMALL_STATE(376)] = 14332,
  [SMALL_STATE(377)] = 14351,
  [SMALL_STATE(378)] = 14370,
  [SMALL_STATE(379)] = 14389,
  [SMALL_STATE(380)] = 14408,
  [SMALL_STATE(381)] = 14427,
  [SMALL_STATE(382)] = 14446,
  [SMALL_STATE(383)] = 14465,
  [SMALL_STATE(384)] = 14484,
  [SMALL_STATE(385)] = 14503,
  [SMALL_STATE(386)] = 14522,
  [SMALL_STATE(387)] = 14541,
  [SMALL_STATE(388)] = 14560,
  [SMALL_STATE(389)] = 14579,
  [SMALL_STATE(390)] = 14598,
  [SMALL_STATE(391)] = 14617,
  [SMALL_STATE(392)] = 14636,
  [SMALL_STATE(393)] = 14655,
  [SMALL_STATE(394)] = 14674,
  [SMALL_STATE(395)] = 14693,
  [SMALL_STATE(396)] = 14712,
  [SMALL_STATE(397)] = 14731,
  [SMALL_STATE(398)] = 14750,
  [SMALL_STATE(399)] = 14769,
  [SMALL_STATE(400)] = 14788,
  [SMALL_STATE(401)] = 14807,
  [SMALL_STATE(402)] = 14826,
  [SMALL_STATE(403)] = 14845,
  [SMALL_STATE(404)] = 14864,
  [SMALL_STATE(405)] = 14883,
  [SMALL_STATE(406)] = 14902,
  [SMALL_STATE(407)] = 14921,
  [SMALL_STATE(408)] = 14940,
  [SMALL_STATE(409)] = 14959,
  [SMALL_STATE(410)] = 14978,
  [SMALL_STATE(411)] = 14997,
  [SMALL_STATE(412)] = 15016,
  [SMALL_STATE(413)] = 15035,
  [SMALL_STATE(414)] = 15054,
  [SMALL_STATE(415)] = 15073,
  [SMALL_STATE(416)] = 15092,
  [SMALL_STATE(417)] = 15111,
  [SMALL_STATE(418)] = 15130,
  [SMALL_STATE(419)] = 15149,
  [SMALL_STATE(420)] = 15168,
  [SMALL_STATE(421)] = 15187,
  [SMALL_STATE(422)] = 15207,
  [SMALL_STATE(423)] = 15225,
  [SMALL_STATE(424)] = 15249,
  [SMALL_STATE(425)] = 15273,
  [SMALL_STATE(426)] = 15293,
  [SMALL_STATE(427)] = 15311,
  [SMALL_STATE(428)] = 15335,
  [SMALL_STATE(429)] = 15359,
  [SMALL_STATE(430)] = 15376,
  [SMALL_STATE(431)] = 15393,
  [SMALL_STATE(432)] = 15410,
  [SMALL_STATE(433)] = 15427,
  [SMALL_STATE(434)] = 15444,
  [SMALL_STATE(435)] = 15461,
  [SMALL_STATE(436)] = 15478,
  [SMALL_STATE(437)] = 15495,
  [SMALL_STATE(438)] = 15512,
  [SMALL_STATE(439)] = 15529,
  [SMALL_STATE(440)] = 15546,
  [SMALL_STATE(441)] = 15563,
  [SMALL_STATE(442)] = 15580,
  [SMALL_STATE(443)] = 15597,
  [SMALL_STATE(444)] = 15614,
  [SMALL_STATE(445)] = 15631,
  [SMALL_STATE(446)] = 15648,
  [SMALL_STATE(447)] = 15665,
  [SMALL_STATE(448)] = 15682,
  [SMALL_STATE(449)] = 15699,
  [SMALL_STATE(450)] = 15716,
  [SMALL_STATE(451)] = 15733,
  [SMALL_STATE(452)] = 15750,
  [SMALL_STATE(453)] = 15767,
  [SMALL_STATE(454)] = 15784,
  [SMALL_STATE(455)] = 15801,
  [SMALL_STATE(456)] = 15818,
  [SMALL_STATE(457)] = 15835,
  [SMALL_STATE(458)] = 15852,
  [SMALL_STATE(459)] = 15869,
  [SMALL_STATE(460)] = 15886,
  [SMALL_STATE(461)] = 15903,
  [SMALL_STATE(462)] = 15920,
  [SMALL_STATE(463)] = 15937,
  [SMALL_STATE(464)] = 15954,
  [SMALL_STATE(465)] = 15971,
  [SMALL_STATE(466)] = 15988,
  [SMALL_STATE(467)] = 16005,
  [SMALL_STATE(468)] = 16022,
  [SMALL_STATE(469)] = 16039,
  [SMALL_STATE(470)] = 16056,
  [SMALL_STATE(471)] = 16073,
  [SMALL_STATE(472)] = 16090,
  [SMALL_STATE(473)] = 16107,
  [SMALL_STATE(474)] = 16124,
  [SMALL_STATE(475)] = 16141,
  [SMALL_STATE(476)] = 16158,
  [SMALL_STATE(477)] = 16175,
  [SMALL_STATE(478)] = 16192,
  [SMALL_STATE(479)] = 16209,
  [SMALL_STATE(480)] = 16226,
  [SMALL_STATE(481)] = 16243,
  [SMALL_STATE(482)] = 16260,
  [SMALL_STATE(483)] = 16277,
  [SMALL_STATE(484)] = 16294,
  [SMALL_STATE(485)] = 16311,
  [SMALL_STATE(486)] = 16328,
  [SMALL_STATE(487)] = 16345,
  [SMALL_STATE(488)] = 16362,
  [SMALL_STATE(489)] = 16379,
  [SMALL_STATE(490)] = 16396,
  [SMALL_STATE(491)] = 16413,
  [SMALL_STATE(492)] = 16430,
  [SMALL_STATE(493)] = 16447,
  [SMALL_STATE(494)] = 16464,
  [SMALL_STATE(495)] = 16481,
  [SMALL_STATE(496)] = 16498,
  [SMALL_STATE(497)] = 16515,
  [SMALL_STATE(498)] = 16532,
  [SMALL_STATE(499)] = 16549,
  [SMALL_STATE(500)] = 16566,
  [SMALL_STATE(501)] = 16583,
  [SMALL_STATE(502)] = 16600,
  [SMALL_STATE(503)] = 16617,
  [SMALL_STATE(504)] = 16634,
  [SMALL_STATE(505)] = 16651,
  [SMALL_STATE(506)] = 16668,
  [SMALL_STATE(507)] = 16685,
  [SMALL_STATE(508)] = 16702,
  [SMALL_STATE(509)] = 16719,
  [SMALL_STATE(510)] = 16736,
  [SMALL_STATE(511)] = 16753,
  [SMALL_STATE(512)] = 16770,
  [SMALL_STATE(513)] = 16787,
  [SMALL_STATE(514)] = 16804,
  [SMALL_STATE(515)] = 16821,
  [SMALL_STATE(516)] = 16838,
  [SMALL_STATE(517)] = 16855,
  [SMALL_STATE(518)] = 16884,
  [SMALL_STATE(519)] = 16913,
  [SMALL_STATE(520)] = 16942,
  [SMALL_STATE(521)] = 16971,
  [SMALL_STATE(522)] = 17000,
  [SMALL_STATE(523)] = 17029,
  [SMALL_STATE(524)] = 17058,
  [SMALL_STATE(525)] = 17087,
  [SMALL_STATE(526)] = 17116,
  [SMALL_STATE(527)] = 17145,
  [SMALL_STATE(528)] = 17174,
  [SMALL_STATE(529)] = 17202,
  [SMALL_STATE(530)] = 17230,
  [SMALL_STATE(531)] = 17258,
  [SMALL_STATE(532)] = 17286,
  [SMALL_STATE(533)] = 17314,
  [SMALL_STATE(534)] = 17342,
  [SMALL_STATE(535)] = 17370,
  [SMALL_STATE(536)] = 17398,
  [SMALL_STATE(537)] = 17426,
  [SMALL_STATE(538)] = 17454,
  [SMALL_STATE(539)] = 17482,
  [SMALL_STATE(540)] = 17510,
  [SMALL_STATE(541)] = 17538,
  [SMALL_STATE(542)] = 17566,
  [SMALL_STATE(543)] = 17594,
  [SMALL_STATE(544)] = 17617,
  [SMALL_STATE(545)] = 17640,
  [SMALL_STATE(546)] = 17663,
  [SMALL_STATE(547)] = 17686,
  [SMALL_STATE(548)] = 17705,
  [SMALL_STATE(549)] = 17728,
  [SMALL_STATE(550)] = 17751,
  [SMALL_STATE(551)] = 17774,
  [SMALL_STATE(552)] = 17797,
  [SMALL_STATE(553)] = 17820,
  [SMALL_STATE(554)] = 17843,
  [SMALL_STATE(555)] = 17866,
  [SMALL_STATE(556)] = 17888,
  [SMALL_STATE(557)] = 17910,
  [SMALL_STATE(558)] = 17932,
  [SMALL_STATE(559)] = 17954,
  [SMALL_STATE(560)] = 17976,
  [SMALL_STATE(561)] = 17998,
  [SMALL_STATE(562)] = 18020,
  [SMALL_STATE(563)] = 18042,
  [SMALL_STATE(564)] = 18064,
  [SMALL_STATE(565)] = 18086,
  [SMALL_STATE(566)] = 18103,
  [SMALL_STATE(567)] = 18120,
  [SMALL_STATE(568)] = 18133,
  [SMALL_STATE(569)] = 18150,
  [SMALL_STATE(570)] = 18167,
  [SMALL_STATE(571)] = 18184,
  [SMALL_STATE(572)] = 18197,
  [SMALL_STATE(573)] = 18216,
  [SMALL_STATE(574)] = 18233,
  [SMALL_STATE(575)] = 18252,
  [SMALL_STATE(576)] = 18271,
  [SMALL_STATE(577)] = 18290,
  [SMALL_STATE(578)] = 18307,
  [SMALL_STATE(579)] = 18324,
  [SMALL_STATE(580)] = 18339,
  [SMALL_STATE(581)] = 18354,
  [SMALL_STATE(582)] = 18371,
  [SMALL_STATE(583)] = 18388,
  [SMALL_STATE(584)] = 18405,
  [SMALL_STATE(585)] = 18422,
  [SMALL_STATE(586)] = 18439,
  [SMALL_STATE(587)] = 18456,
  [SMALL_STATE(588)] = 18473,
  [SMALL_STATE(589)] = 18490,
  [SMALL_STATE(590)] = 18507,
  [SMALL_STATE(591)] = 18524,
  [SMALL_STATE(592)] = 18541,
  [SMALL_STATE(593)] = 18558,
  [SMALL_STATE(594)] = 18575,
  [SMALL_STATE(595)] = 18592,
  [SMALL_STATE(596)] = 18608,
  [SMALL_STATE(597)] = 18624,
  [SMALL_STATE(598)] = 18640,
  [SMALL_STATE(599)] = 18656,
  [SMALL_STATE(600)] = 18672,
  [SMALL_STATE(601)] = 18688,
  [SMALL_STATE(602)] = 18704,
  [SMALL_STATE(603)] = 18720,
  [SMALL_STATE(604)] = 18736,
  [SMALL_STATE(605)] = 18752,
  [SMALL_STATE(606)] = 18768,
  [SMALL_STATE(607)] = 18784,
  [SMALL_STATE(608)] = 18800,
  [SMALL_STATE(609)] = 18816,
  [SMALL_STATE(610)] = 18832,
  [SMALL_STATE(611)] = 18848,
  [SMALL_STATE(612)] = 18864,
  [SMALL_STATE(613)] = 18880,
  [SMALL_STATE(614)] = 18896,
  [SMALL_STATE(615)] = 18912,
  [SMALL_STATE(616)] = 18928,
  [SMALL_STATE(617)] = 18944,
  [SMALL_STATE(618)] = 18960,
  [SMALL_STATE(619)] = 18976,
  [SMALL_STATE(620)] = 18992,
  [SMALL_STATE(621)] = 19008,
  [SMALL_STATE(622)] = 19020,
  [SMALL_STATE(623)] = 19036,
  [SMALL_STATE(624)] = 19052,
  [SMALL_STATE(625)] = 19068,
  [SMALL_STATE(626)] = 19084,
  [SMALL_STATE(627)] = 19100,
  [SMALL_STATE(628)] = 19116,
  [SMALL_STATE(629)] = 19132,
  [SMALL_STATE(630)] = 19148,
  [SMALL_STATE(631)] = 19164,
  [SMALL_STATE(632)] = 19178,
  [SMALL_STATE(633)] = 19194,
  [SMALL_STATE(634)] = 19208,
  [SMALL_STATE(635)] = 19222,
  [SMALL_STATE(636)] = 19238,
  [SMALL_STATE(637)] = 19254,
  [SMALL_STATE(638)] = 19262,
  [SMALL_STATE(639)] = 19278,
  [SMALL_STATE(640)] = 19285,
  [SMALL_STATE(641)] = 19298,
  [SMALL_STATE(642)] = 19305,
  [SMALL_STATE(643)] = 19312,
  [SMALL_STATE(644)] = 19319,
  [SMALL_STATE(645)] = 19330,
  [SMALL_STATE(646)] = 19341,
  [SMALL_STATE(647)] = 19348,
  [SMALL_STATE(648)] = 19361,
  [SMALL_STATE(649)] = 19374,
  [SMALL_STATE(650)] = 19387,
  [SMALL_STATE(651)] = 19400,
  [SMALL_STATE(652)] = 19413,
  [SMALL_STATE(653)] = 19426,
  [SMALL_STATE(654)] = 19439,
  [SMALL_STATE(655)] = 19446,
  [SMALL_STATE(656)] = 19453,
  [SMALL_STATE(657)] = 19460,
  [SMALL_STATE(658)] = 19467,
  [SMALL_STATE(659)] = 19474,
  [SMALL_STATE(660)] = 19481,
  [SMALL_STATE(661)] = 19488,
  [SMALL_STATE(662)] = 19495,
  [SMALL_STATE(663)] = 19508,
  [SMALL_STATE(664)] = 19515,
  [SMALL_STATE(665)] = 19528,
  [SMALL_STATE(666)] = 19535,
  [SMALL_STATE(667)] = 19542,
  [SMALL_STATE(668)] = 19555,
  [SMALL_STATE(669)] = 19568,
  [SMALL_STATE(670)] = 19581,
  [SMALL_STATE(671)] = 19588,
  [SMALL_STATE(672)] = 19595,
  [SMALL_STATE(673)] = 19608,
  [SMALL_STATE(674)] = 19621,
  [SMALL_STATE(675)] = 19628,
  [SMALL_STATE(676)] = 19635,
  [SMALL_STATE(677)] = 19642,
  [SMALL_STATE(678)] = 19649,
  [SMALL_STATE(679)] = 19656,
  [SMALL_STATE(680)] = 19666,
  [SMALL_STATE(681)] = 19676,
  [SMALL_STATE(682)] = 19682,
  [SMALL_STATE(683)] = 19692,
  [SMALL_STATE(684)] = 19702,
  [SMALL_STATE(685)] = 19712,
  [SMALL_STATE(686)] = 19722,
  [SMALL_STATE(687)] = 19732,
  [SMALL_STATE(688)] = 19742,
  [SMALL_STATE(689)] = 19752,
  [SMALL_STATE(690)] = 19762,
  [SMALL_STATE(691)] = 19772,
  [SMALL_STATE(692)] = 19782,
  [SMALL_STATE(693)] = 19792,
  [SMALL_STATE(694)] = 19802,
  [SMALL_STATE(695)] = 19808,
  [SMALL_STATE(696)] = 19818,
  [SMALL_STATE(697)] = 19828,
  [SMALL_STATE(698)] = 19838,
  [SMALL_STATE(699)] = 19848,
  [SMALL_STATE(700)] = 19858,
  [SMALL_STATE(701)] = 19864,
  [SMALL_STATE(702)] = 19874,
  [SMALL_STATE(703)] = 19884,
  [SMALL_STATE(704)] = 19894,
  [SMALL_STATE(705)] = 19904,
  [SMALL_STATE(706)] = 19914,
  [SMALL_STATE(707)] = 19924,
  [SMALL_STATE(708)] = 19934,
  [SMALL_STATE(709)] = 19944,
  [SMALL_STATE(710)] = 19954,
  [SMALL_STATE(711)] = 19964,
  [SMALL_STATE(712)] = 19974,
  [SMALL_STATE(713)] = 19984,
  [SMALL_STATE(714)] = 19994,
  [SMALL_STATE(715)] = 20004,
  [SMALL_STATE(716)] = 20014,
  [SMALL_STATE(717)] = 20024,
  [SMALL_STATE(718)] = 20031,
  [SMALL_STATE(719)] = 20036,
  [SMALL_STATE(720)] = 20041,
  [SMALL_STATE(721)] = 20046,
  [SMALL_STATE(722)] = 20053,
  [SMALL_STATE(723)] = 20060,
  [SMALL_STATE(724)] = 20064,
  [SMALL_STATE(725)] = 20068,
  [SMALL_STATE(726)] = 20072,
  [SMALL_STATE(727)] = 20076,
  [SMALL_STATE(728)] = 20080,
  [SMALL_STATE(729)] = 20084,
  [SMALL_STATE(730)] = 20088,
  [SMALL_STATE(731)] = 20092,
  [SMALL_STATE(732)] = 20096,
  [SMALL_STATE(733)] = 20100,
  [SMALL_STATE(734)] = 20104,
  [SMALL_STATE(735)] = 20108,
  [SMALL_STATE(736)] = 20112,
  [SMALL_STATE(737)] = 20116,
  [SMALL_STATE(738)] = 20120,
  [SMALL_STATE(739)] = 20124,
  [SMALL_STATE(740)] = 20128,
  [SMALL_STATE(741)] = 20132,
  [SMALL_STATE(742)] = 20136,
  [SMALL_STATE(743)] = 20140,
  [SMALL_STATE(744)] = 20144,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(314),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(533),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(569),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(247),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(637),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(476),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(659),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(576),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(98),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(532),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(568),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(430),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(361),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [55] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(132),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(534),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [69] = {.entry = {.count = 1, .reusable = false}}, SHIFT(577),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(454),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(363),
  [77] = {.entry = {.count = 1, .reusable = true}}, SHIFT(135),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [83] = {.entry = {.count = 1, .reusable = false}}, SHIFT(137),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(541),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [93] = {.entry = {.count = 1, .reusable = false}}, SHIFT(587),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(356),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(275),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [107] = {.entry = {.count = 1, .reusable = false}}, SHIFT(71),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(473),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(337),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(504),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [131] = {.entry = {.count = 1, .reusable = true}}, SHIFT(526),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(435),
  [135] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(574),
  [139] = {.entry = {.count = 1, .reusable = true}}, SHIFT(657),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(523),
  [143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(658),
  [145] = {.entry = {.count = 1, .reusable = true}}, SHIFT(291),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(510),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(518),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(514),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(306),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(520),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(308),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(370),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(527),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(412),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(501),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(525),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(503),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(392),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(524),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(391),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(184),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(517),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(185),
  [183] = {.entry = {.count = 1, .reusable = true}}, SHIFT(182),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(519),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(207),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(521),
  [193] = {.entry = {.count = 1, .reusable = true}}, SHIFT(209),
  [195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(254),
  [197] = {.entry = {.count = 1, .reusable = true}}, SHIFT(522),
  [199] = {.entry = {.count = 1, .reusable = true}}, SHIFT(260),
  [201] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 3, 0, 10),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(575),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(647),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(555),
  [211] = {.entry = {.count = 1, .reusable = true}}, SHIFT(561),
  [213] = {.entry = {.count = 1, .reusable = true}}, SHIFT(713),
  [215] = {.entry = {.count = 1, .reusable = true}}, SHIFT(714),
  [217] = {.entry = {.count = 1, .reusable = true}}, SHIFT(623),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 2, 0, 5),
  [221] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 1, 0, 2),
  [223] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 2, 0, 4),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0),
  [227] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(97),
  [230] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(575),
  [233] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(647),
  [236] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(15),
  [239] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(555),
  [242] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(561),
  [245] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(713),
  [248] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(714),
  [251] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(623),
  [254] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(98),
  [257] = {.entry = {.count = 1, .reusable = true}}, SHIFT(549),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(633),
  [261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(312),
  [263] = {.entry = {.count = 1, .reusable = true}}, SHIFT(552),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(551),
  [267] = {.entry = {.count = 1, .reusable = true}}, SHIFT(543),
  [269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(634),
  [271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(631),
  [273] = {.entry = {.count = 1, .reusable = true}}, SHIFT(550),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(553),
  [277] = {.entry = {.count = 1, .reusable = true}}, SHIFT(546),
  [279] = {.entry = {.count = 1, .reusable = true}}, SHIFT(545),
  [281] = {.entry = {.count = 1, .reusable = true}}, SHIFT(544),
  [283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(667),
  [285] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [287] = {.entry = {.count = 1, .reusable = true}}, SHIFT(556),
  [289] = {.entry = {.count = 1, .reusable = true}}, SHIFT(557),
  [291] = {.entry = {.count = 1, .reusable = true}}, SHIFT(690),
  [293] = {.entry = {.count = 1, .reusable = true}}, SHIFT(685),
  [295] = {.entry = {.count = 1, .reusable = true}}, SHIFT(607),
  [297] = {.entry = {.count = 1, .reusable = true}}, SHIFT(651),
  [299] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(562),
  [303] = {.entry = {.count = 1, .reusable = true}}, SHIFT(558),
  [305] = {.entry = {.count = 1, .reusable = true}}, SHIFT(686),
  [307] = {.entry = {.count = 1, .reusable = true}}, SHIFT(689),
  [309] = {.entry = {.count = 1, .reusable = true}}, SHIFT(620),
  [311] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 1, 0, 0),
  [313] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 1, 0, 0),
  [315] = {.entry = {.count = 1, .reusable = true}}, SHIFT(664),
  [317] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(576),
  [320] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(651),
  [323] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(14),
  [326] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(562),
  [329] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(558),
  [332] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(686),
  [335] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(689),
  [338] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(620),
  [341] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 2, 0, 0),
  [343] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 2, 0, 0),
  [345] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0),
  [347] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0),
  [349] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(664),
  [352] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(574),
  [355] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(667),
  [358] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(16),
  [361] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(556),
  [364] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(557),
  [367] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(690),
  [370] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(685),
  [373] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(607),
  [376] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ident, 1, 0, 0),
  [378] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ident, 1, 0, 0),
  [380] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_identifier, 1, 0, 0),
  [382] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_identifier, 1, 0, 0),
  [384] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym__bool_value, 1, 0, 0), REDUCE(sym__expression, 1, 0, 0),
  [387] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression, 1, 0, 0),
  [389] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__expression, 1, 0, 0),
  [391] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bool_value, 1, 0, 0),
  [393] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym__bool_value, 1, 0, 0), REDUCE(sym__expression, 1, 0, 0),
  [396] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2, 0, 0),
  [398] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 2, 0, 0),
  [400] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(537),
  [406] = {.entry = {.count = 1, .reusable = true}}, SHIFT(432),
  [408] = {.entry = {.count = 1, .reusable = false}}, SHIFT(566),
  [410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(452),
  [412] = {.entry = {.count = 1, .reusable = true}}, SHIFT(416),
  [414] = {.entry = {.count = 1, .reusable = true}}, SHIFT(433),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [418] = {.entry = {.count = 1, .reusable = false}}, SHIFT(418),
  [420] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [422] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [424] = {.entry = {.count = 1, .reusable = true}}, SHIFT(536),
  [426] = {.entry = {.count = 1, .reusable = true}}, SHIFT(341),
  [428] = {.entry = {.count = 1, .reusable = false}}, SHIFT(594),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(311),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(272),
  [434] = {.entry = {.count = 1, .reusable = true}}, SHIFT(342),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [438] = {.entry = {.count = 1, .reusable = false}}, SHIFT(280),
  [440] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3, 0, 0),
  [442] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3, 0, 0),
  [444] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 1, 0, 0),
  [446] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 1, 0, 0),
  [448] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__bool_value, 1, 0, 0),
  [450] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_string_end, 1, 0, 0),
  [452] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_string_end, 1, 0, 0),
  [454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [458] = {.entry = {.count = 1, .reusable = true}}, SHIFT(542),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(479),
  [462] = {.entry = {.count = 1, .reusable = false}}, SHIFT(588),
  [464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(434),
  [466] = {.entry = {.count = 1, .reusable = true}}, SHIFT(368),
  [468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(480),
  [470] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [472] = {.entry = {.count = 1, .reusable = false}}, SHIFT(371),
  [474] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(672),
  [477] = {.entry = {.count = 1, .reusable = true}}, SHIFT(662),
  [479] = {.entry = {.count = 1, .reusable = true}}, SHIFT(672),
  [481] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment, 3, 0, 14),
  [483] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [485] = {.entry = {.count = 1, .reusable = false}}, SHIFT(123),
  [487] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [489] = {.entry = {.count = 1, .reusable = true}}, SHIFT(252),
  [491] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assignment, 3, 0, 14),
  [493] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment, 4, 0, 16),
  [495] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assignment, 4, 0, 16),
  [497] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(662),
  [500] = {.entry = {.count = 1, .reusable = true}}, SHIFT(614),
  [502] = {.entry = {.count = 1, .reusable = true}}, SHIFT(668),
  [504] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [506] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [508] = {.entry = {.count = 1, .reusable = true}}, SHIFT(539),
  [510] = {.entry = {.count = 1, .reusable = true}}, SHIFT(362),
  [512] = {.entry = {.count = 1, .reusable = false}}, SHIFT(586),
  [514] = {.entry = {.count = 1, .reusable = true}}, SHIFT(419),
  [516] = {.entry = {.count = 1, .reusable = true}}, SHIFT(372),
  [518] = {.entry = {.count = 1, .reusable = true}}, SHIFT(359),
  [520] = {.entry = {.count = 1, .reusable = true}}, SHIFT(393),
  [522] = {.entry = {.count = 1, .reusable = false}}, SHIFT(330),
  [524] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array_query, 3, 0, 3),
  [526] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array_query, 3, 0, 3),
  [528] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_array_query_end, 1, 0, 0),
  [530] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_array_query_end, 1, 0, 0),
  [532] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(668),
  [535] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_query, 3, 0, 3),
  [537] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_element_query, 3, 0, 3),
  [539] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_element_query_end, 1, 0, 0),
  [541] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_element_query_end, 1, 0, 0),
  [543] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_parenthesis_end, 1, 0, 0),
  [545] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_parenthesis_end, 1, 0, 0),
  [547] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [549] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [551] = {.entry = {.count = 1, .reusable = true}}, SHIFT(535),
  [553] = {.entry = {.count = 1, .reusable = true}}, SHIFT(643),
  [555] = {.entry = {.count = 1, .reusable = true}}, SHIFT(655),
  [557] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 3, 0, 0),
  [559] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 3, 0, 0),
  [561] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parenthesized_expression, 3, 0, 0),
  [563] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__parenthesized_expression, 3, 0, 0),
  [565] = {.entry = {.count = 1, .reusable = true}}, SHIFT(642),
  [567] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [569] = {.entry = {.count = 1, .reusable = true}}, SHIFT(725),
  [571] = {.entry = {.count = 1, .reusable = false}}, SHIFT(589),
  [573] = {.entry = {.count = 1, .reusable = true}}, SHIFT(729),
  [575] = {.entry = {.count = 1, .reusable = true}}, SHIFT(641),
  [577] = {.entry = {.count = 1, .reusable = true}}, SHIFT(718),
  [579] = {.entry = {.count = 1, .reusable = true}}, SHIFT(742),
  [581] = {.entry = {.count = 1, .reusable = false}}, SHIFT(719),
  [583] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 3, 0, 0),
  [585] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object, 3, 0, 0),
  [587] = {.entry = {.count = 1, .reusable = true}}, SHIFT(445),
  [589] = {.entry = {.count = 1, .reusable = true}}, SHIFT(444),
  [591] = {.entry = {.count = 1, .reusable = true}}, SHIFT(726),
  [593] = {.entry = {.count = 1, .reusable = true}}, SHIFT(736),
  [595] = {.entry = {.count = 1, .reusable = true}}, SHIFT(624),
  [597] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [599] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [601] = {.entry = {.count = 1, .reusable = true}}, SHIFT(540),
  [603] = {.entry = {.count = 1, .reusable = true}}, SHIFT(369),
  [605] = {.entry = {.count = 1, .reusable = false}}, SHIFT(593),
  [607] = {.entry = {.count = 1, .reusable = true}}, SHIFT(367),
  [609] = {.entry = {.count = 1, .reusable = true}}, SHIFT(414),
  [611] = {.entry = {.count = 1, .reusable = true}}, SHIFT(346),
  [613] = {.entry = {.count = 1, .reusable = true}}, SHIFT(373),
  [615] = {.entry = {.count = 1, .reusable = false}}, SHIFT(347),
  [617] = {.entry = {.count = 1, .reusable = true}}, SHIFT(738),
  [619] = {.entry = {.count = 1, .reusable = true}}, SHIFT(681),
  [621] = {.entry = {.count = 1, .reusable = true}}, SHIFT(394),
  [623] = {.entry = {.count = 1, .reusable = true}}, SHIFT(429),
  [625] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [627] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [629] = {.entry = {.count = 1, .reusable = true}}, SHIFT(528),
  [631] = {.entry = {.count = 1, .reusable = true}}, SHIFT(264),
  [633] = {.entry = {.count = 1, .reusable = false}}, SHIFT(581),
  [635] = {.entry = {.count = 1, .reusable = true}}, SHIFT(269),
  [637] = {.entry = {.count = 1, .reusable = true}}, SHIFT(266),
  [639] = {.entry = {.count = 1, .reusable = true}}, SHIFT(248),
  [641] = {.entry = {.count = 1, .reusable = true}}, SHIFT(268),
  [643] = {.entry = {.count = 1, .reusable = false}}, SHIFT(245),
  [645] = {.entry = {.count = 1, .reusable = true}}, SHIFT(453),
  [647] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 2, 0, 0),
  [649] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 2, 0, 0),
  [651] = {.entry = {.count = 1, .reusable = true}}, SHIFT(609),
  [653] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_array_end, 1, 0, 0),
  [655] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_array_end, 1, 0, 0),
  [657] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 2, 0, 0),
  [659] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object, 2, 0, 0),
  [661] = {.entry = {.count = 1, .reusable = true}}, SHIFT(377),
  [663] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 4, 0, 0),
  [665] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 4, 0, 0),
  [667] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 4, 0, 0),
  [669] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object, 4, 0, 0),
  [671] = {.entry = {.count = 1, .reusable = true}}, SHIFT(327),
  [673] = {.entry = {.count = 1, .reusable = true}}, SHIFT(328),
  [675] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_brace_end, 1, 0, 0),
  [677] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_brace_end, 1, 0, 0),
  [679] = {.entry = {.count = 1, .reusable = true}}, SHIFT(277),
  [681] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [683] = {.entry = {.count = 1, .reusable = false}}, SHIFT(116),
  [685] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [687] = {.entry = {.count = 1, .reusable = true}}, SHIFT(364),
  [689] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [691] = {.entry = {.count = 1, .reusable = false}}, SHIFT(93),
  [693] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [695] = {.entry = {.count = 1, .reusable = true}}, SHIFT(374),
  [697] = {.entry = {.count = 1, .reusable = true}}, SHIFT(700),
  [699] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [701] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [703] = {.entry = {.count = 1, .reusable = true}}, SHIFT(214),
  [705] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [707] = {.entry = {.count = 1, .reusable = false}}, SHIFT(108),
  [709] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [711] = {.entry = {.count = 1, .reusable = true}}, SHIFT(646),
  [713] = {.entry = {.count = 1, .reusable = true}}, SHIFT(202),
  [715] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_stmt, 2, 0, 6),
  [717] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_filter_stmt, 2, 0, 6),
  [719] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [721] = {.entry = {.count = 1, .reusable = true}}, SHIFT(192),
  [723] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [725] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [727] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0),
  [729] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0),
  [731] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_not_expression, 2, 0, 0),
  [733] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_not_expression, 2, 0, 0),
  [735] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [737] = {.entry = {.count = 1, .reusable = true}}, SHIFT(189),
  [739] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0),
  [741] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0),
  [743] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(652),
  [746] = {.entry = {.count = 1, .reusable = true}}, SHIFT(652),
  [748] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_and_expression, 2, 0, 0),
  [750] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_and_expression, 2, 0, 0),
  [752] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_or_expression, 2, 0, 0),
  [754] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_or_expression, 2, 0, 0),
  [756] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(36),
  [759] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(33),
  [762] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [764] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [766] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(673),
  [769] = {.entry = {.count = 1, .reusable = true}}, SHIFT(673),
  [771] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [773] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [775] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparator, 1, 0, 0),
  [777] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparator, 1, 0, 0),
  [779] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_expression, 1, 0, 0),
  [781] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_expression, 1, 0, 0),
  [783] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparator, 2, 0, 17),
  [785] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparator, 2, 0, 17),
  [787] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison, 2, 0, 12),
  [789] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison, 2, 0, 12),
  [791] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_bool_value, 1, 0, 0),
  [793] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_bool_value, 1, 0, 0),
  [795] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparator, 4, 0, 21),
  [797] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparator, 4, 0, 21),
  [799] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parenthesized_bool_expression, 3, 0, 0),
  [801] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__parenthesized_bool_expression, 3, 0, 0),
  [803] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_iterator_stmt, 4, 0, 15),
  [805] = {.entry = {.count = 1, .reusable = true}}, SHIFT(329),
  [807] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_iterator_stmt, 4, 0, 15),
  [809] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(648),
  [812] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(649),
  [815] = {.entry = {.count = 1, .reusable = true}}, SHIFT(648),
  [817] = {.entry = {.count = 1, .reusable = true}}, SHIFT(669),
  [819] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(30),
  [822] = {.entry = {.count = 1, .reusable = true}}, SHIFT(649),
  [824] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(31),
  [827] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(29),
  [830] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(28),
  [833] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(669),
  [836] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_iterator, 1, 0, 0),
  [838] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_iterator, 1, 0, 0),
  [840] = {.entry = {.count = 1, .reusable = true}}, SHIFT(653),
  [842] = {.entry = {.count = 1, .reusable = true}}, SHIFT(640),
  [844] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_append_stmt, 3, 0, 13),
  [846] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_append_stmt, 3, 0, 13),
  [848] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_main_iterator, 1, 0, 0),
  [850] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_main_iterator, 1, 0, 0),
  [852] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_query_start, 1, 0, 0),
  [854] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_query_start, 1, 0, 0),
  [856] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_update_field, 1, 0, 0),
  [858] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_update_field, 1, 0, 0),
  [860] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_stmt, 2, 0, 0),
  [862] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_update_stmt, 2, 0, 0),
  [864] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_stmt, 2, 0, 0),
  [866] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_filter_stmt, 2, 0, 0),
  [868] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_stmt, 4, 0, 18),
  [870] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_update_stmt, 4, 0, 18),
  [872] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_append_stmt, 4, 0, 19),
  [874] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_append_stmt, 4, 0, 19),
  [876] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_iterator_stmt, 5, 0, 20),
  [878] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_iterator_stmt, 5, 0, 20),
  [880] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(653),
  [883] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(640),
  [886] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_iterator_stmt, 2, 0, 0),
  [888] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_iterator_stmt, 2, 0, 0),
  [890] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_filter_expression, 1, 0, 0),
  [892] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_filter_expression, 1, 0, 0),
  [894] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_limit_stmt, 2, 0, 0),
  [896] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_limit_stmt, 2, 0, 0),
  [898] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_limit_value, 1, 0, 0),
  [900] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_limit_value, 1, 0, 0),
  [902] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_limit_stmt, 2, 0, 9),
  [904] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_limit_stmt, 2, 0, 9),
  [906] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_offset_stmt, 2, 0, 0),
  [908] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_offset_stmt, 2, 0, 0),
  [910] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_offset_value, 1, 0, 0),
  [912] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_offset_value, 1, 0, 0),
  [914] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_offset_stmt, 2, 0, 8),
  [916] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_offset_stmt, 2, 0, 8),
  [918] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_stmt, 2, 0, 0),
  [920] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_delete_stmt, 2, 0, 0),
  [922] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_stmt, 2, 0, 7),
  [924] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_delete_stmt, 2, 0, 7),
  [926] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_delete_field, 1, 0, 0),
  [928] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_delete_field, 1, 0, 0),
  [930] = {.entry = {.count = 1, .reusable = true}}, SHIFT(466),
  [932] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_equals, 1, 0, 0),
  [934] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_equals, 1, 0, 0),
  [936] = {.entry = {.count = 1, .reusable = true}}, SHIFT(442),
  [938] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_colon, 1, 0, 0),
  [940] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_colon, 1, 0, 0),
  [942] = {.entry = {.count = 1, .reusable = true}}, SHIFT(194),
  [944] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [946] = {.entry = {.count = 1, .reusable = true}}, SHIFT(481),
  [948] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [950] = {.entry = {.count = 1, .reusable = true}}, SHIFT(326),
  [952] = {.entry = {.count = 1, .reusable = true}}, SHIFT(215),
  [954] = {.entry = {.count = 1, .reusable = true}}, SHIFT(259),
  [956] = {.entry = {.count = 1, .reusable = true}}, SHIFT(676),
  [958] = {.entry = {.count = 1, .reusable = true}}, SHIFT(381),
  [960] = {.entry = {.count = 1, .reusable = true}}, SHIFT(485),
  [962] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [964] = {.entry = {.count = 1, .reusable = true}}, SHIFT(400),
  [966] = {.entry = {.count = 1, .reusable = true}}, SHIFT(267),
  [968] = {.entry = {.count = 1, .reusable = true}}, SHIFT(278),
  [970] = {.entry = {.count = 1, .reusable = true}}, SHIFT(279),
  [972] = {.entry = {.count = 1, .reusable = true}}, SHIFT(263),
  [974] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [976] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [978] = {.entry = {.count = 1, .reusable = true}}, SHIFT(420),
  [980] = {.entry = {.count = 1, .reusable = true}}, SHIFT(411),
  [982] = {.entry = {.count = 1, .reusable = true}}, SHIFT(366),
  [984] = {.entry = {.count = 1, .reusable = true}}, SHIFT(413),
  [986] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [988] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [990] = {.entry = {.count = 1, .reusable = true}}, SHIFT(210),
  [992] = {.entry = {.count = 1, .reusable = true}}, SHIFT(211),
  [994] = {.entry = {.count = 1, .reusable = true}}, SHIFT(180),
  [996] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [998] = {.entry = {.count = 1, .reusable = true}}, SHIFT(660),
  [1000] = {.entry = {.count = 1, .reusable = true}}, SHIFT(661),
  [1002] = {.entry = {.count = 1, .reusable = true}}, SHIFT(309),
  [1004] = {.entry = {.count = 1, .reusable = true}}, SHIFT(310),
  [1006] = {.entry = {.count = 1, .reusable = true}}, SHIFT(506),
  [1008] = {.entry = {.count = 1, .reusable = true}}, SHIFT(508),
  [1010] = {.entry = {.count = 1, .reusable = true}}, SHIFT(654),
  [1012] = {.entry = {.count = 1, .reusable = true}}, SHIFT(390),
  [1014] = {.entry = {.count = 1, .reusable = true}}, SHIFT(389),
  [1016] = {.entry = {.count = 1, .reusable = true}}, SHIFT(410),
  [1018] = {.entry = {.count = 1, .reusable = true}}, SHIFT(408),
  [1020] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [1022] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [1024] = {.entry = {.count = 1, .reusable = true}}, SHIFT(513),
  [1026] = {.entry = {.count = 1, .reusable = true}}, SHIFT(512),
  [1028] = {.entry = {.count = 1, .reusable = true}}, SHIFT(492),
  [1030] = {.entry = {.count = 1, .reusable = true}}, SHIFT(477),
  [1032] = {.entry = {.count = 1, .reusable = true}}, SHIFT(740),
  [1034] = {.entry = {.count = 1, .reusable = true}}, SHIFT(399),
  [1036] = {.entry = {.count = 1, .reusable = true}}, SHIFT(274),
  [1038] = {.entry = {.count = 1, .reusable = true}}, SHIFT(478),
  [1040] = {.entry = {.count = 1, .reusable = true}}, SHIFT(498),
  [1042] = {.entry = {.count = 1, .reusable = true}}, SHIFT(302),
  [1044] = {.entry = {.count = 1, .reusable = true}}, SHIFT(354),
  [1046] = {.entry = {.count = 1, .reusable = true}}, SHIFT(674),
  [1048] = {.entry = {.count = 1, .reusable = true}}, SHIFT(380),
  [1050] = {.entry = {.count = 1, .reusable = true}}, SHIFT(320),
  [1052] = {.entry = {.count = 1, .reusable = true}}, SHIFT(474),
  [1054] = {.entry = {.count = 1, .reusable = true}}, SHIFT(470),
  [1056] = {.entry = {.count = 1, .reusable = true}}, SHIFT(468),
  [1058] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__missing_query, 2, 0, 3),
  [1060] = {.entry = {.count = 1, .reusable = true}}, SHIFT(730),
  [1062] = {.entry = {.count = 1, .reusable = true}}, SHIFT(727),
  [1064] = {.entry = {.count = 1, .reusable = true}}, SHIFT(203),
  [1066] = {.entry = {.count = 1, .reusable = true}}, SHIFT(200),
  [1068] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [1070] = {.entry = {.count = 1, .reusable = true}}, SHIFT(358),
  [1072] = {.entry = {.count = 1, .reusable = true}}, SHIFT(471),
  [1074] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [1076] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [1078] = {.entry = {.count = 1, .reusable = false}}, SHIFT(154),
  [1080] = {.entry = {.count = 1, .reusable = true}}, SHIFT(621),
  [1082] = {.entry = {.count = 1, .reusable = false}}, SHIFT(143),
  [1084] = {.entry = {.count = 1, .reusable = false}}, SHIFT(440),
  [1086] = {.entry = {.count = 1, .reusable = true}}, SHIFT(578),
  [1088] = {.entry = {.count = 1, .reusable = false}}, SHIFT(433),
  [1090] = {.entry = {.count = 1, .reusable = false}}, SHIFT(145),
  [1092] = {.entry = {.count = 1, .reusable = true}}, SHIFT(585),
  [1094] = {.entry = {.count = 1, .reusable = false}}, SHIFT(152),
  [1096] = {.entry = {.count = 1, .reusable = false}}, SHIFT(156),
  [1098] = {.entry = {.count = 1, .reusable = true}}, SHIFT(592),
  [1100] = {.entry = {.count = 1, .reusable = false}}, SHIFT(159),
  [1102] = {.entry = {.count = 1, .reusable = false}}, SHIFT(741),
  [1104] = {.entry = {.count = 1, .reusable = false}}, SHIFT(742),
  [1106] = {.entry = {.count = 1, .reusable = false}}, SHIFT(256),
  [1108] = {.entry = {.count = 1, .reusable = false}}, SHIFT(268),
  [1110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(505),
  [1112] = {.entry = {.count = 1, .reusable = true}}, SHIFT(303),
  [1114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(487),
  [1116] = {.entry = {.count = 1, .reusable = false}}, SHIFT(147),
  [1118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(565),
  [1120] = {.entry = {.count = 1, .reusable = false}}, SHIFT(451),
  [1122] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(35),
  [1125] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(34),
  [1128] = {.entry = {.count = 1, .reusable = false}}, SHIFT(265),
  [1130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(573),
  [1132] = {.entry = {.count = 1, .reusable = false}}, SHIFT(378),
  [1134] = {.entry = {.count = 1, .reusable = false}}, SHIFT(393),
  [1136] = {.entry = {.count = 1, .reusable = false}}, SHIFT(78),
  [1138] = {.entry = {.count = 1, .reusable = false}}, SHIFT(81),
  [1140] = {.entry = {.count = 1, .reusable = false}}, SHIFT(494),
  [1142] = {.entry = {.count = 1, .reusable = false}}, SHIFT(480),
  [1144] = {.entry = {.count = 1, .reusable = false}}, SHIFT(148),
  [1146] = {.entry = {.count = 1, .reusable = false}}, SHIFT(388),
  [1148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(582),
  [1150] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [1152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(583),
  [1154] = {.entry = {.count = 1, .reusable = false}}, SHIFT(509),
  [1156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(584),
  [1158] = {.entry = {.count = 1, .reusable = false}}, SHIFT(724),
  [1160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(570),
  [1162] = {.entry = {.count = 1, .reusable = false}}, SHIFT(353),
  [1164] = {.entry = {.count = 1, .reusable = false}}, SHIFT(342),
  [1166] = {.entry = {.count = 1, .reusable = false}}, SHIFT(397),
  [1168] = {.entry = {.count = 1, .reusable = false}}, SHIFT(373),
  [1170] = {.entry = {.count = 1, .reusable = false}}, SHIFT(161),
  [1172] = {.entry = {.count = 1, .reusable = false}}, SHIFT(407),
  [1174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(591),
  [1176] = {.entry = {.count = 1, .reusable = false}}, SHIFT(344),
  [1178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(590),
  [1180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(572),
  [1182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(271),
  [1184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(499),
  [1186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(134),
  [1188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [1190] = {.entry = {.count = 1, .reusable = true}}, SHIFT(456),
  [1192] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [1194] = {.entry = {.count = 1, .reusable = true}}, SHIFT(398),
  [1196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(639),
  [1198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [1200] = {.entry = {.count = 1, .reusable = true}}, SHIFT(677),
  [1202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [1204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(675),
  [1206] = {.entry = {.count = 1, .reusable = true}}, SHIFT(332),
  [1208] = {.entry = {.count = 1, .reusable = false}}, SHIFT(334),
  [1210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [1212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [1214] = {.entry = {.count = 1, .reusable = true}}, SHIFT(396),
  [1216] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [1218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(395),
  [1220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(340),
  [1222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(455),
  [1224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(475),
  [1226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(208),
  [1228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(338),
  [1230] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__string_content, 2, 0, 0),
  [1232] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__string_content, 2, 0, 0), SHIFT_REPEAT(621),
  [1235] = {.entry = {.count = 1, .reusable = true}}, SHIFT(331),
  [1237] = {.entry = {.count = 1, .reusable = true}}, SHIFT(375),
  [1239] = {.entry = {.count = 1, .reusable = true}}, SHIFT(511),
  [1241] = {.entry = {.count = 1, .reusable = true}}, SHIFT(376),
  [1243] = {.entry = {.count = 1, .reusable = true}}, SHIFT(213),
  [1245] = {.entry = {.count = 1, .reusable = true}}, SHIFT(253),
  [1247] = {.entry = {.count = 1, .reusable = true}}, SHIFT(212),
  [1249] = {.entry = {.count = 1, .reusable = true}}, SHIFT(496),
  [1251] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [1253] = {.entry = {.count = 1, .reusable = true}}, SHIFT(262),
  [1255] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_query_body, 1, 0, 0),
  [1257] = {.entry = {.count = 1, .reusable = true}}, SHIFT(379),
  [1259] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 0), SHIFT_REPEAT(572),
  [1262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 0),
  [1264] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0),
  [1266] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0), SHIFT_REPEAT(183),
  [1269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(313),
  [1271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(317),
  [1273] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(650),
  [1276] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pair, 3, 0, 11),
  [1278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(516),
  [1280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(515),
  [1282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(495),
  [1284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(493),
  [1286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(650),
  [1288] = {.entry = {.count = 1, .reusable = true}}, SHIFT(438),
  [1290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(436),
  [1292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(463),
  [1294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(462),
  [1296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(191),
  [1298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(193),
  [1300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(197),
  [1302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(196),
  [1304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(459),
  [1306] = {.entry = {.count = 1, .reusable = true}}, SHIFT(458),
  [1308] = {.entry = {.count = 1, .reusable = true}}, SHIFT(450),
  [1310] = {.entry = {.count = 1, .reusable = true}}, SHIFT(447),
  [1312] = {.entry = {.count = 1, .reusable = true}}, SHIFT(431),
  [1314] = {.entry = {.count = 1, .reusable = true}}, SHIFT(489),
  [1316] = {.entry = {.count = 1, .reusable = true}}, SHIFT(321),
  [1318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(324),
  [1320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(484),
  [1322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(483),
  [1324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(201),
  [1326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [1328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [1330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [1332] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [1334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [1336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(422),
  [1338] = {.entry = {.count = 1, .reusable = true}}, SHIFT(206),
  [1340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [1342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(406),
  [1344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(405),
  [1346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(403),
  [1348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(402),
  [1350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(176),
  [1352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(175),
  [1354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [1356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [1358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [1360] = {.entry = {.count = 1, .reusable = true}}, SHIFT(670),
  [1362] = {.entry = {.count = 1, .reusable = true}}, SHIFT(671),
  [1364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(387),
  [1366] = {.entry = {.count = 1, .reusable = true}}, SHIFT(386),
  [1368] = {.entry = {.count = 1, .reusable = true}}, SHIFT(384),
  [1370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(383),
  [1372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(663),
  [1374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(665),
  [1376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [1378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(426),
  [1380] = {.entry = {.count = 1, .reusable = true}}, SHIFT(351),
  [1382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(350),
  [1384] = {.entry = {.count = 1, .reusable = true}}, SHIFT(348),
  [1386] = {.entry = {.count = 1, .reusable = true}}, SHIFT(345),
  [1388] = {.entry = {.count = 1, .reusable = true}}, SHIFT(261),
  [1390] = {.entry = {.count = 1, .reusable = true}}, SHIFT(258),
  [1392] = {.entry = {.count = 1, .reusable = true}}, SHIFT(281),
  [1394] = {.entry = {.count = 1, .reusable = true}}, SHIFT(270),
  [1396] = {.entry = {.count = 1, .reusable = true}}, SHIFT(563),
  [1398] = {.entry = {.count = 1, .reusable = true}}, SHIFT(564),
  [1400] = {.entry = {.count = 1, .reusable = true}}, SHIFT(560),
  [1402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [1404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [1406] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__missing_query, 3, 0, 3),
  [1408] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [1410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [1412] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [1414] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [1416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [1418] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [1420] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [1422] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [1424] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [1426] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_start, 1, 0, 1),
  [1428] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_start, 1, 0, 0),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_mee_ql(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
