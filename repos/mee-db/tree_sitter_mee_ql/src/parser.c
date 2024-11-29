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
#define STATE_COUNT 723
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 134
#define ALIAS_COUNT 0
#define TOKEN_COUNT 66
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 19
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 20

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
  aux_sym_ident_token1 = 65,
  sym_start = 66,
  sym__query = 67,
  sym_array_query = 68,
  sym_element_query = 69,
  sym__missing_query = 70,
  sym__query_body = 71,
  sym_iterator_stmt = 72,
  sym_assignment = 73,
  sym_update_stmt = 74,
  sym_delete_stmt = 75,
  sym_filter_stmt = 76,
  sym_offset_stmt = 77,
  sym_limit_stmt = 78,
  sym__bool_expression = 79,
  sym_comparison = 80,
  sym_comparator = 81,
  sym_not_expression = 82,
  sym_and_expression = 83,
  sym_or_expression = 84,
  sym__bool_value = 85,
  sym__parenthesized_bool_expression = 86,
  sym__expression = 87,
  sym__parenthesized_expression = 88,
  sym_path = 89,
  sym_object = 90,
  sym_pair = 91,
  sym_array = 92,
  sym_string = 93,
  aux_sym__string_content = 94,
  sym__expected_expression = 95,
  sym_missing_query_start = 96,
  sym_missing_query_body = 97,
  sym_missing_main_iterator = 98,
  sym_missing_array_query_end = 99,
  sym_missing_element_query_end = 100,
  sym_missing_iterator = 101,
  sym_missing_update_field = 102,
  sym_missing_delete_field = 103,
  sym_missing_filter_expression = 104,
  sym_missing_offset_value = 105,
  sym_missing_limit_value = 106,
  sym_missing_expression = 107,
  sym_missing_bool_value = 108,
  sym_missing_equals = 109,
  sym_missing_colon = 110,
  sym_missing_identifier = 111,
  sym_missing_brace_end = 112,
  sym_missing_array_end = 113,
  sym_missing_parenthesis_end = 114,
  sym_missing_string_end = 115,
  sym__for = 116,
  sym__let = 117,
  sym__in = 118,
  sym__and = 119,
  sym__or = 120,
  sym__not = 121,
  sym__if = 122,
  sym__set = 123,
  sym__delete = 124,
  sym__offset = 125,
  sym__limit = 126,
  sym_ident = 127,
  aux_sym__query_body_repeat1 = 128,
  aux_sym_and_expression_repeat1 = 129,
  aux_sym_or_expression_repeat1 = 130,
  aux_sym_path_repeat1 = 131,
  aux_sym_object_repeat1 = 132,
  aux_sym_array_repeat1 = 133,
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
  field_var = 19,
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
  [16] = {.index = 30, .length = 1},
  [17] = {.index = 31, .length = 2},
  [18] = {.index = 33, .length = 3},
  [19] = {.index = 36, .length = 2},
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
    {field_expr, 2},
    {field_var, 0},
  [26] =
    {field_item, 1},
    {field_source, 3},
  [28] =
    {field_expr, 3},
    {field_var, 1},
  [30] =
    {field_right, 1},
  [31] =
    {field_expr, 3},
    {field_field, 1},
  [33] =
    {field_item, 1},
    {field_source, 3},
    {field_source, 4},
  [36] =
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
  [15] = 10,
  [16] = 14,
  [17] = 14,
  [18] = 18,
  [19] = 19,
  [20] = 18,
  [21] = 21,
  [22] = 21,
  [23] = 19,
  [24] = 21,
  [25] = 19,
  [26] = 19,
  [27] = 21,
  [28] = 19,
  [29] = 29,
  [30] = 18,
  [31] = 19,
  [32] = 19,
  [33] = 19,
  [34] = 29,
  [35] = 18,
  [36] = 19,
  [37] = 19,
  [38] = 29,
  [39] = 19,
  [40] = 29,
  [41] = 41,
  [42] = 41,
  [43] = 41,
  [44] = 41,
  [45] = 45,
  [46] = 41,
  [47] = 41,
  [48] = 48,
  [49] = 41,
  [50] = 41,
  [51] = 51,
  [52] = 41,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 54,
  [65] = 57,
  [66] = 55,
  [67] = 56,
  [68] = 54,
  [69] = 69,
  [70] = 57,
  [71] = 71,
  [72] = 72,
  [73] = 55,
  [74] = 74,
  [75] = 53,
  [76] = 53,
  [77] = 71,
  [78] = 78,
  [79] = 56,
  [80] = 60,
  [81] = 81,
  [82] = 60,
  [83] = 83,
  [84] = 58,
  [85] = 62,
  [86] = 86,
  [87] = 86,
  [88] = 58,
  [89] = 61,
  [90] = 58,
  [91] = 60,
  [92] = 92,
  [93] = 59,
  [94] = 83,
  [95] = 95,
  [96] = 59,
  [97] = 97,
  [98] = 59,
  [99] = 99,
  [100] = 95,
  [101] = 97,
  [102] = 83,
  [103] = 86,
  [104] = 86,
  [105] = 97,
  [106] = 95,
  [107] = 95,
  [108] = 99,
  [109] = 109,
  [110] = 83,
  [111] = 99,
  [112] = 112,
  [113] = 113,
  [114] = 114,
  [115] = 115,
  [116] = 116,
  [117] = 63,
  [118] = 118,
  [119] = 119,
  [120] = 120,
  [121] = 121,
  [122] = 122,
  [123] = 123,
  [124] = 61,
  [125] = 62,
  [126] = 63,
  [127] = 63,
  [128] = 61,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
  [133] = 62,
  [134] = 134,
  [135] = 135,
  [136] = 136,
  [137] = 71,
  [138] = 78,
  [139] = 78,
  [140] = 72,
  [141] = 69,
  [142] = 69,
  [143] = 74,
  [144] = 71,
  [145] = 72,
  [146] = 74,
  [147] = 69,
  [148] = 78,
  [149] = 71,
  [150] = 71,
  [151] = 72,
  [152] = 74,
  [153] = 153,
  [154] = 81,
  [155] = 81,
  [156] = 109,
  [157] = 109,
  [158] = 118,
  [159] = 120,
  [160] = 122,
  [161] = 123,
  [162] = 129,
  [163] = 131,
  [164] = 116,
  [165] = 121,
  [166] = 112,
  [167] = 114,
  [168] = 129,
  [169] = 132,
  [170] = 134,
  [171] = 135,
  [172] = 131,
  [173] = 114,
  [174] = 136,
  [175] = 123,
  [176] = 113,
  [177] = 122,
  [178] = 122,
  [179] = 123,
  [180] = 119,
  [181] = 130,
  [182] = 121,
  [183] = 132,
  [184] = 129,
  [185] = 134,
  [186] = 132,
  [187] = 135,
  [188] = 116,
  [189] = 136,
  [190] = 113,
  [191] = 134,
  [192] = 135,
  [193] = 115,
  [194] = 119,
  [195] = 115,
  [196] = 118,
  [197] = 120,
  [198] = 112,
  [199] = 115,
  [200] = 130,
  [201] = 136,
  [202] = 130,
  [203] = 114,
  [204] = 112,
  [205] = 116,
  [206] = 121,
  [207] = 120,
  [208] = 131,
  [209] = 113,
  [210] = 210,
  [211] = 210,
  [212] = 210,
  [213] = 210,
  [214] = 214,
  [215] = 215,
  [216] = 216,
  [217] = 217,
  [218] = 218,
  [219] = 219,
  [220] = 220,
  [221] = 71,
  [222] = 222,
  [223] = 59,
  [224] = 224,
  [225] = 60,
  [226] = 226,
  [227] = 58,
  [228] = 217,
  [229] = 219,
  [230] = 219,
  [231] = 63,
  [232] = 218,
  [233] = 214,
  [234] = 58,
  [235] = 217,
  [236] = 215,
  [237] = 218,
  [238] = 216,
  [239] = 216,
  [240] = 62,
  [241] = 61,
  [242] = 59,
  [243] = 215,
  [244] = 60,
  [245] = 214,
  [246] = 114,
  [247] = 69,
  [248] = 130,
  [249] = 131,
  [250] = 61,
  [251] = 112,
  [252] = 62,
  [253] = 253,
  [254] = 120,
  [255] = 255,
  [256] = 256,
  [257] = 63,
  [258] = 74,
  [259] = 259,
  [260] = 113,
  [261] = 261,
  [262] = 136,
  [263] = 135,
  [264] = 134,
  [265] = 132,
  [266] = 129,
  [267] = 123,
  [268] = 122,
  [269] = 78,
  [270] = 270,
  [271] = 115,
  [272] = 272,
  [273] = 71,
  [274] = 116,
  [275] = 121,
  [276] = 72,
  [277] = 222,
  [278] = 58,
  [279] = 226,
  [280] = 220,
  [281] = 222,
  [282] = 59,
  [283] = 224,
  [284] = 284,
  [285] = 60,
  [286] = 59,
  [287] = 287,
  [288] = 226,
  [289] = 220,
  [290] = 58,
  [291] = 224,
  [292] = 60,
  [293] = 123,
  [294] = 294,
  [295] = 295,
  [296] = 296,
  [297] = 297,
  [298] = 62,
  [299] = 59,
  [300] = 61,
  [301] = 63,
  [302] = 121,
  [303] = 122,
  [304] = 304,
  [305] = 62,
  [306] = 61,
  [307] = 307,
  [308] = 308,
  [309] = 309,
  [310] = 130,
  [311] = 60,
  [312] = 312,
  [313] = 313,
  [314] = 314,
  [315] = 129,
  [316] = 316,
  [317] = 131,
  [318] = 132,
  [319] = 319,
  [320] = 320,
  [321] = 321,
  [322] = 63,
  [323] = 134,
  [324] = 112,
  [325] = 114,
  [326] = 69,
  [327] = 72,
  [328] = 135,
  [329] = 58,
  [330] = 136,
  [331] = 115,
  [332] = 113,
  [333] = 333,
  [334] = 74,
  [335] = 59,
  [336] = 336,
  [337] = 337,
  [338] = 338,
  [339] = 116,
  [340] = 78,
  [341] = 60,
  [342] = 120,
  [343] = 58,
  [344] = 344,
  [345] = 259,
  [346] = 346,
  [347] = 132,
  [348] = 72,
  [349] = 349,
  [350] = 130,
  [351] = 255,
  [352] = 349,
  [353] = 253,
  [354] = 131,
  [355] = 115,
  [356] = 255,
  [357] = 256,
  [358] = 112,
  [359] = 359,
  [360] = 261,
  [361] = 270,
  [362] = 272,
  [363] = 114,
  [364] = 63,
  [365] = 61,
  [366] = 130,
  [367] = 261,
  [368] = 270,
  [369] = 131,
  [370] = 112,
  [371] = 114,
  [372] = 120,
  [373] = 74,
  [374] = 69,
  [375] = 61,
  [376] = 72,
  [377] = 62,
  [378] = 113,
  [379] = 136,
  [380] = 135,
  [381] = 116,
  [382] = 121,
  [383] = 134,
  [384] = 78,
  [385] = 132,
  [386] = 122,
  [387] = 123,
  [388] = 129,
  [389] = 129,
  [390] = 123,
  [391] = 253,
  [392] = 134,
  [393] = 135,
  [394] = 122,
  [395] = 256,
  [396] = 136,
  [397] = 78,
  [398] = 113,
  [399] = 272,
  [400] = 74,
  [401] = 121,
  [402] = 63,
  [403] = 116,
  [404] = 115,
  [405] = 120,
  [406] = 259,
  [407] = 349,
  [408] = 69,
  [409] = 259,
  [410] = 410,
  [411] = 349,
  [412] = 62,
  [413] = 287,
  [414] = 287,
  [415] = 72,
  [416] = 129,
  [417] = 78,
  [418] = 319,
  [419] = 122,
  [420] = 123,
  [421] = 295,
  [422] = 114,
  [423] = 314,
  [424] = 132,
  [425] = 134,
  [426] = 135,
  [427] = 112,
  [428] = 312,
  [429] = 136,
  [430] = 314,
  [431] = 113,
  [432] = 316,
  [433] = 296,
  [434] = 297,
  [435] = 296,
  [436] = 295,
  [437] = 320,
  [438] = 120,
  [439] = 72,
  [440] = 346,
  [441] = 69,
  [442] = 294,
  [443] = 130,
  [444] = 333,
  [445] = 307,
  [446] = 304,
  [447] = 304,
  [448] = 307,
  [449] = 319,
  [450] = 115,
  [451] = 312,
  [452] = 131,
  [453] = 321,
  [454] = 131,
  [455] = 338,
  [456] = 336,
  [457] = 321,
  [458] = 313,
  [459] = 112,
  [460] = 316,
  [461] = 346,
  [462] = 114,
  [463] = 337,
  [464] = 294,
  [465] = 344,
  [466] = 309,
  [467] = 338,
  [468] = 337,
  [469] = 344,
  [470] = 336,
  [471] = 121,
  [472] = 333,
  [473] = 313,
  [474] = 320,
  [475] = 69,
  [476] = 309,
  [477] = 74,
  [478] = 308,
  [479] = 116,
  [480] = 116,
  [481] = 121,
  [482] = 297,
  [483] = 78,
  [484] = 122,
  [485] = 123,
  [486] = 129,
  [487] = 130,
  [488] = 259,
  [489] = 132,
  [490] = 134,
  [491] = 135,
  [492] = 308,
  [493] = 136,
  [494] = 115,
  [495] = 113,
  [496] = 74,
  [497] = 259,
  [498] = 120,
  [499] = 499,
  [500] = 499,
  [501] = 499,
  [502] = 499,
  [503] = 499,
  [504] = 499,
  [505] = 499,
  [506] = 499,
  [507] = 499,
  [508] = 499,
  [509] = 499,
  [510] = 510,
  [511] = 510,
  [512] = 510,
  [513] = 513,
  [514] = 513,
  [515] = 513,
  [516] = 513,
  [517] = 513,
  [518] = 510,
  [519] = 513,
  [520] = 513,
  [521] = 513,
  [522] = 513,
  [523] = 513,
  [524] = 513,
  [525] = 214,
  [526] = 526,
  [527] = 526,
  [528] = 526,
  [529] = 526,
  [530] = 219,
  [531] = 526,
  [532] = 526,
  [533] = 215,
  [534] = 526,
  [535] = 526,
  [536] = 526,
  [537] = 537,
  [538] = 538,
  [539] = 537,
  [540] = 538,
  [541] = 541,
  [542] = 537,
  [543] = 538,
  [544] = 541,
  [545] = 545,
  [546] = 541,
  [547] = 547,
  [548] = 548,
  [549] = 547,
  [550] = 547,
  [551] = 551,
  [552] = 551,
  [553] = 548,
  [554] = 551,
  [555] = 547,
  [556] = 547,
  [557] = 557,
  [558] = 551,
  [559] = 551,
  [560] = 551,
  [561] = 547,
  [562] = 548,
  [563] = 551,
  [564] = 547,
  [565] = 551,
  [566] = 547,
  [567] = 547,
  [568] = 547,
  [569] = 222,
  [570] = 551,
  [571] = 551,
  [572] = 226,
  [573] = 547,
  [574] = 220,
  [575] = 224,
  [576] = 551,
  [577] = 577,
  [578] = 577,
  [579] = 579,
  [580] = 577,
  [581] = 581,
  [582] = 577,
  [583] = 577,
  [584] = 584,
  [585] = 584,
  [586] = 581,
  [587] = 587,
  [588] = 581,
  [589] = 589,
  [590] = 587,
  [591] = 579,
  [592] = 577,
  [593] = 579,
  [594] = 577,
  [595] = 581,
  [596] = 584,
  [597] = 584,
  [598] = 584,
  [599] = 577,
  [600] = 584,
  [601] = 581,
  [602] = 584,
  [603] = 581,
  [604] = 584,
  [605] = 584,
  [606] = 587,
  [607] = 581,
  [608] = 581,
  [609] = 581,
  [610] = 577,
  [611] = 584,
  [612] = 584,
  [613] = 581,
  [614] = 581,
  [615] = 615,
  [616] = 577,
  [617] = 577,
  [618] = 261,
  [619] = 123,
  [620] = 620,
  [621] = 620,
  [622] = 130,
  [623] = 120,
  [624] = 259,
  [625] = 625,
  [626] = 620,
  [627] = 620,
  [628] = 272,
  [629] = 629,
  [630] = 620,
  [631] = 620,
  [632] = 259,
  [633] = 620,
  [634] = 620,
  [635] = 270,
  [636] = 636,
  [637] = 256,
  [638] = 636,
  [639] = 620,
  [640] = 114,
  [641] = 255,
  [642] = 620,
  [643] = 636,
  [644] = 253,
  [645] = 113,
  [646] = 112,
  [647] = 116,
  [648] = 136,
  [649] = 121,
  [650] = 620,
  [651] = 131,
  [652] = 122,
  [653] = 135,
  [654] = 134,
  [655] = 132,
  [656] = 129,
  [657] = 657,
  [658] = 59,
  [659] = 659,
  [660] = 660,
  [661] = 661,
  [662] = 660,
  [663] = 659,
  [664] = 659,
  [665] = 660,
  [666] = 60,
  [667] = 58,
  [668] = 659,
  [669] = 660,
  [670] = 660,
  [671] = 660,
  [672] = 659,
  [673] = 660,
  [674] = 657,
  [675] = 675,
  [676] = 676,
  [677] = 657,
  [678] = 659,
  [679] = 659,
  [680] = 660,
  [681] = 661,
  [682] = 676,
  [683] = 683,
  [684] = 661,
  [685] = 685,
  [686] = 659,
  [687] = 660,
  [688] = 676,
  [689] = 660,
  [690] = 690,
  [691] = 659,
  [692] = 659,
  [693] = 660,
  [694] = 659,
  [695] = 62,
  [696] = 696,
  [697] = 61,
  [698] = 696,
  [699] = 696,
  [700] = 63,
  [701] = 701,
  [702] = 701,
  [703] = 703,
  [704] = 74,
  [705] = 69,
  [706] = 706,
  [707] = 78,
  [708] = 72,
  [709] = 709,
  [710] = 703,
  [711] = 711,
  [712] = 115,
  [713] = 713,
  [714] = 701,
  [715] = 706,
  [716] = 703,
  [717] = 701,
  [718] = 718,
  [719] = 706,
  [720] = 720,
  [721] = 721,
  [722] = 722,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(239);
      ADVANCE_MAP(
        '!', 25,
        '"', 269,
        '(', 243,
        ')', 244,
        ',', 264,
        '.', 261,
        ':', 266,
        '<', 251,
        '=', 247,
        '>', 250,
        'E', 353,
        '[', 240,
        '\\', 231,
        ']', 241,
        'a', 547,
        'b', 498,
        'c', 700,
        'd', 499,
        'e', 833,
        'f', 455,
        'i', 549,
        'l', 509,
        'm', 458,
        'n', 703,
        'o', 551,
        's', 514,
        't', 719,
        '{', 263,
        '}', 265,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(233);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(262);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(17);
      if (lookahead == '"') ADVANCE(268);
      if (lookahead == 'E') ADVANCE(274);
      if (lookahead == '\\') ADVANCE(231);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(270);
      if (lookahead != 0) ADVANCE(294);
      END_STATE();
    case 2:
      ADVANCE_MAP(
        '!', 25,
        '"', 269,
        '(', 242,
        ')', 244,
        ',', 264,
        '.', 261,
        ':', 266,
        '<', 251,
        '=', 247,
        '>', 250,
        'E', 39,
        '[', 240,
        ']', 241,
        'a', 111,
        'b', 95,
        'c', 170,
        'e', 228,
        'f', 171,
        'i', 152,
        'm', 71,
        'o', 176,
        '}', 265,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(262);
      END_STATE();
    case 3:
      ADVANCE_MAP(
        '!', 25,
        ')', 244,
        ',', 264,
        ':', 266,
        '<', 251,
        '=', 26,
        '>', 250,
        'E', 45,
        ']', 241,
        'a', 111,
        'b', 95,
        'c', 170,
        'e', 228,
        'f', 171,
        'm', 71,
        'o', 176,
        '}', 265,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      END_STATE();
    case 4:
      ADVANCE_MAP(
        '!', 25,
        ')', 244,
        '.', 261,
        '<', 251,
        '=', 26,
        '>', 250,
        'E', 385,
        'a', 547,
        'b', 498,
        'c', 700,
        'd', 499,
        'e', 833,
        'f', 701,
        'i', 550,
        'l', 509,
        'm', 458,
        'o', 551,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 5:
      ADVANCE_MAP(
        '!', 25,
        ')', 244,
        '<', 251,
        '=', 26,
        '>', 250,
        'E', 385,
        'a', 548,
        'b', 498,
        'c', 700,
        'd', 499,
        'e', 833,
        'f', 701,
        'i', 550,
        'l', 509,
        'm', 458,
        'o', 552,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(5);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 6:
      ADVANCE_MAP(
        '!', 25,
        '.', 261,
        '<', 251,
        '=', 26,
        '>', 250,
        'E', 387,
        ']', 241,
        'a', 547,
        'b', 498,
        'c', 700,
        'd', 499,
        'e', 833,
        'f', 701,
        'i', 550,
        'l', 509,
        'm', 458,
        'o', 551,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 7:
      ADVANCE_MAP(
        '!', 25,
        '<', 251,
        '=', 26,
        '>', 250,
        'E', 387,
        ']', 241,
        'a', 548,
        'b', 498,
        'c', 700,
        'd', 499,
        'e', 833,
        'f', 701,
        'i', 550,
        'l', 509,
        'm', 458,
        'o', 552,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(7);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 8:
      ADVANCE_MAP(
        '"', 269,
        '(', 242,
        '-', 24,
        '0', 296,
        '=', 246,
        'E', 371,
        '[', 240,
        'f', 455,
        'n', 703,
        't', 719,
        '{', 263,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(8);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 9:
      ADVANCE_MAP(
        '"', 269,
        '(', 242,
        '-', 24,
        '0', 296,
        'E', 373,
        '[', 240,
        'f', 456,
        'n', 703,
        't', 719,
        '{', 263,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(9);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 10:
      ADVANCE_MAP(
        '"', 269,
        '(', 242,
        '-', 24,
        '0', 296,
        'E', 375,
        '[', 240,
        'f', 456,
        'n', 703,
        't', 719,
        '{', 263,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(10);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 11:
      ADVANCE_MAP(
        '"', 269,
        '(', 242,
        '-', 24,
        '0', 296,
        'E', 377,
        '[', 240,
        'f', 456,
        'n', 703,
        't', 719,
        '{', 263,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(11);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 12:
      ADVANCE_MAP(
        '"', 269,
        '(', 242,
        '-', 24,
        '0', 296,
        'E', 379,
        '[', 240,
        ']', 241,
        'f', 455,
        'n', 817,
        't', 719,
        '{', 263,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(12);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 13:
      ADVANCE_MAP(
        '"', 269,
        '(', 242,
        '-', 24,
        '0', 296,
        'E', 381,
        '[', 240,
        'f', 455,
        'n', 817,
        't', 719,
        '{', 263,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(13);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 14:
      ADVANCE_MAP(
        '"', 269,
        '(', 242,
        '-', 24,
        '0', 296,
        'E', 389,
        '[', 240,
        'f', 456,
        'n', 817,
        't', 719,
        '{', 263,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(14);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 15:
      ADVANCE_MAP(
        '"', 269,
        '(', 242,
        '-', 24,
        '0', 296,
        'E', 391,
        '[', 240,
        ']', 241,
        'f', 456,
        'n', 817,
        't', 719,
        '{', 263,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(15);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 16:
      ADVANCE_MAP(
        '"', 269,
        '(', 242,
        '-', 24,
        '0', 296,
        'E', 393,
        '[', 240,
        'f', 456,
        'n', 817,
        't', 719,
        '{', 263,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(16);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 17:
      if (lookahead == '"') ADVANCE(268);
      if (lookahead == 'E') ADVANCE(49);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(17);
      END_STATE();
    case 18:
      ADVANCE_MAP(
        '(', 21,
        ')', 244,
        '.', 261,
        'E', 385,
        'd', 499,
        'f', 701,
        'i', 550,
        'l', 509,
        'o', 552,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(18);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 19:
      ADVANCE_MAP(
        '(', 21,
        '.', 261,
        'E', 387,
        ']', 241,
        'd', 499,
        'f', 701,
        'i', 550,
        'l', 509,
        'o', 552,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(19);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 20:
      ADVANCE_MAP(
        ')', 244,
        '.', 261,
        'E', 385,
        'a', 666,
        'd', 499,
        'f', 701,
        'i', 550,
        'l', 509,
        'o', 551,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(20);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 21:
      if (lookahead == ')') ADVANCE(245);
      END_STATE();
    case 22:
      if (lookahead == '-') ADVANCE(232);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(299);
      END_STATE();
    case 23:
      ADVANCE_MAP(
        '.', 261,
        'E', 387,
        ']', 241,
        'a', 666,
        'd', 499,
        'f', 701,
        'i', 550,
        'l', 509,
        'o', 551,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(23);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 24:
      if (lookahead == '0') ADVANCE(296);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(297);
      END_STATE();
    case 25:
      if (lookahead == '=') ADVANCE(249);
      END_STATE();
    case 26:
      if (lookahead == '=') ADVANCE(248);
      END_STATE();
    case 27:
      if (lookahead == '=') ADVANCE(246);
      if (lookahead == 'E') ADVANCE(51);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(27);
      END_STATE();
    case 28:
      if (lookahead == 'E') ADVANCE(395);
      if (lookahead == '[') ADVANCE(240);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(28);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 29:
      if (lookahead == 'E') ADVANCE(397);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(29);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 30:
      if (lookahead == 'E') ADVANCE(399);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(30);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 31:
      if (lookahead == 'E') ADVANCE(401);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(31);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 32:
      if (lookahead == 'O') ADVANCE(38);
      END_STATE();
    case 33:
      if (lookahead == 'O') ADVANCE(40);
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
      if (lookahead == 'R') ADVANCE(32);
      END_STATE();
    case 38:
      if (lookahead == 'R') ADVANCE(52);
      END_STATE();
    case 39:
      if (lookahead == 'R') ADVANCE(37);
      END_STATE();
    case 40:
      if (lookahead == 'R') ADVANCE(66);
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
      if (lookahead == 'R') ADVANCE(33);
      END_STATE();
    case 45:
      if (lookahead == 'R') ADVANCE(44);
      END_STATE();
    case 46:
      if (lookahead == 'R') ADVANCE(34);
      END_STATE();
    case 47:
      if (lookahead == 'R') ADVANCE(46);
      END_STATE();
    case 48:
      if (lookahead == 'R') ADVANCE(35);
      END_STATE();
    case 49:
      if (lookahead == 'R') ADVANCE(48);
      END_STATE();
    case 50:
      if (lookahead == 'R') ADVANCE(36);
      END_STATE();
    case 51:
      if (lookahead == 'R') ADVANCE(50);
      END_STATE();
    case 52:
      if (lookahead == '_') ADVANCE(147);
      END_STATE();
    case 53:
      if (lookahead == '_') ADVANCE(76);
      END_STATE();
    case 54:
      if (lookahead == '_') ADVANCE(225);
      END_STATE();
    case 55:
      if (lookahead == '_') ADVANCE(77);
      END_STATE();
    case 56:
      if (lookahead == '_') ADVANCE(78);
      END_STATE();
    case 57:
      if (lookahead == '_') ADVANCE(136);
      END_STATE();
    case 58:
      if (lookahead == '_') ADVANCE(101);
      END_STATE();
    case 59:
      if (lookahead == '_') ADVANCE(102);
      END_STATE();
    case 60:
      if (lookahead == '_') ADVANCE(104);
      END_STATE();
    case 61:
      if (lookahead == '_') ADVANCE(106);
      END_STATE();
    case 62:
      if (lookahead == '_') ADVANCE(96);
      END_STATE();
    case 63:
      if (lookahead == '_') ADVANCE(196);
      END_STATE();
    case 64:
      if (lookahead == '_') ADVANCE(194);
      END_STATE();
    case 65:
      if (lookahead == '_') ADVANCE(226);
      END_STATE();
    case 66:
      if (lookahead == '_') ADVANCE(148);
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
      if (lookahead == 'a') ADVANCE(229);
      END_STATE();
    case 71:
      if (lookahead == 'a') ADVANCE(210);
      END_STATE();
    case 72:
      if (lookahead == 'a') ADVANCE(126);
      END_STATE();
    case 73:
      if (lookahead == 'a') ADVANCE(85);
      END_STATE();
    case 74:
      if (lookahead == 'a') ADVANCE(142);
      END_STATE();
    case 75:
      if (lookahead == 'a') ADVANCE(144);
      END_STATE();
    case 76:
      ADVANCE_MAP(
        'a', 184,
        'b', 181,
        'c', 169,
        'e', 175,
        'l', 125,
        'm', 82,
        'o', 113,
        'p', 79,
        'q', 224,
        's', 215,
      );
      END_STATE();
    case 77:
      if (lookahead == 'a') ADVANCE(184);
      if (lookahead == 'b') ADVANCE(181);
      if (lookahead == 'c') ADVANCE(169);
      if (lookahead == 'm') ADVANCE(82);
      if (lookahead == 'p') ADVANCE(79);
      END_STATE();
    case 78:
      if (lookahead == 'a') ADVANCE(184);
      if (lookahead == 'b') ADVANCE(181);
      if (lookahead == 'm') ADVANCE(82);
      if (lookahead == 'p') ADVANCE(79);
      END_STATE();
    case 79:
      if (lookahead == 'a') ADVANCE(183);
      END_STATE();
    case 80:
      if (lookahead == 'a') ADVANCE(219);
      END_STATE();
    case 81:
      if (lookahead == 'a') ADVANCE(185);
      END_STATE();
    case 82:
      if (lookahead == 'a') ADVANCE(129);
      END_STATE();
    case 83:
      if (lookahead == 'a') ADVANCE(145);
      END_STATE();
    case 84:
      if (lookahead == 'c') ADVANCE(122);
      END_STATE();
    case 85:
      if (lookahead == 'c') ADVANCE(109);
      END_STATE();
    case 86:
      if (lookahead == 'd') ADVANCE(326);
      END_STATE();
    case 87:
      if (lookahead == 'd') ADVANCE(317);
      END_STATE();
    case 88:
      if (lookahead == 'd') ADVANCE(316);
      END_STATE();
    case 89:
      if (lookahead == 'd') ADVANCE(319);
      END_STATE();
    case 90:
      if (lookahead == 'd') ADVANCE(318);
      END_STATE();
    case 91:
      if (lookahead == 'd') ADVANCE(258);
      END_STATE();
    case 92:
      if (lookahead == 'e') ADVANCE(256);
      END_STATE();
    case 93:
      if (lookahead == 'e') ADVANCE(310);
      END_STATE();
    case 94:
      if (lookahead == 'e') ADVANCE(309);
      END_STATE();
    case 95:
      if (lookahead == 'e') ADVANCE(115);
      END_STATE();
    case 96:
      if (lookahead == 'e') ADVANCE(175);
      END_STATE();
    case 97:
      if (lookahead == 'e') ADVANCE(153);
      END_STATE();
    case 98:
      if (lookahead == 'e') ADVANCE(178);
      END_STATE();
    case 99:
      if (lookahead == 'e') ADVANCE(190);
      END_STATE();
    case 100:
      if (lookahead == 'e') ADVANCE(97);
      END_STATE();
    case 101:
      if (lookahead == 'e') ADVANCE(156);
      END_STATE();
    case 102:
      if (lookahead == 'e') ADVANCE(158);
      END_STATE();
    case 103:
      if (lookahead == 'e') ADVANCE(199);
      END_STATE();
    case 104:
      if (lookahead == 'e') ADVANCE(160);
      END_STATE();
    case 105:
      if (lookahead == 'e') ADVANCE(187);
      END_STATE();
    case 106:
      if (lookahead == 'e') ADVANCE(162);
      END_STATE();
    case 107:
      if (lookahead == 'e') ADVANCE(186);
      END_STATE();
    case 108:
      if (lookahead == 'e') ADVANCE(163);
      END_STATE();
    case 109:
      if (lookahead == 'e') ADVANCE(59);
      END_STATE();
    case 110:
      if (lookahead == 'e') ADVANCE(220);
      END_STATE();
    case 111:
      if (lookahead == 'f') ADVANCE(211);
      if (lookahead == 'n') ADVANCE(86);
      END_STATE();
    case 112:
      if (lookahead == 'f') ADVANCE(211);
      if (lookahead == 'n') ADVANCE(91);
      END_STATE();
    case 113:
      if (lookahead == 'f') ADVANCE(114);
      END_STATE();
    case 114:
      if (lookahead == 'f') ADVANCE(197);
      END_STATE();
    case 115:
      if (lookahead == 'f') ADVANCE(172);
      if (lookahead == 't') ADVANCE(227);
      END_STATE();
    case 116:
      if (lookahead == 'g') ADVANCE(53);
      END_STATE();
    case 117:
      if (lookahead == 'g') ADVANCE(55);
      END_STATE();
    case 118:
      if (lookahead == 'g') ADVANCE(56);
      END_STATE();
    case 119:
      if (lookahead == 'g') ADVANCE(60);
      END_STATE();
    case 120:
      if (lookahead == 'g') ADVANCE(62);
      END_STATE();
    case 121:
      if (lookahead == 'g') ADVANCE(64);
      END_STATE();
    case 122:
      if (lookahead == 'h') ADVANCE(99);
      END_STATE();
    case 123:
      if (lookahead == 'h') ADVANCE(103);
      END_STATE();
    case 124:
      if (lookahead == 'i') ADVANCE(193);
      END_STATE();
    case 125:
      if (lookahead == 'i') ADVANCE(146);
      END_STATE();
    case 126:
      if (lookahead == 'i') ADVANCE(161);
      END_STATE();
    case 127:
      if (lookahead == 'i') ADVANCE(155);
      END_STATE();
    case 128:
      if (lookahead == 'i') ADVANCE(195);
      END_STATE();
    case 129:
      if (lookahead == 'i') ADVANCE(159);
      END_STATE();
    case 130:
      if (lookahead == 'i') ADVANCE(214);
      END_STATE();
    case 131:
      if (lookahead == 'i') ADVANCE(200);
      END_STATE();
    case 132:
      if (lookahead == 'i') ADVANCE(164);
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
      if (lookahead == 'i') ADVANCE(218);
      END_STATE();
    case 137:
      if (lookahead == 'i') ADVANCE(168);
      END_STATE();
    case 138:
      if (lookahead == 'i') ADVANCE(204);
      END_STATE();
    case 139:
      if (lookahead == 'i') ADVANCE(206);
      END_STATE();
    case 140:
      if (lookahead == 'i') ADVANCE(207);
      END_STATE();
    case 141:
      if (lookahead == 'i') ADVANCE(208);
      END_STATE();
    case 142:
      if (lookahead == 'l') ADVANCE(192);
      END_STATE();
    case 143:
      if (lookahead == 'l') ADVANCE(173);
      END_STATE();
    case 144:
      if (lookahead == 'l') ADVANCE(222);
      END_STATE();
    case 145:
      if (lookahead == 'l') ADVANCE(223);
      END_STATE();
    case 146:
      if (lookahead == 'm') ADVANCE(130);
      END_STATE();
    case 147:
      if (lookahead == 'm') ADVANCE(128);
      END_STATE();
    case 148:
      if (lookahead == 'm') ADVANCE(138);
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
      if (lookahead == 'n') ADVANCE(322);
      END_STATE();
    case 153:
      if (lookahead == 'n') ADVANCE(257);
      END_STATE();
    case 154:
      if (lookahead == 'n') ADVANCE(314);
      END_STATE();
    case 155:
      if (lookahead == 'n') ADVANCE(116);
      END_STATE();
    case 156:
      if (lookahead == 'n') ADVANCE(87);
      END_STATE();
    case 157:
      if (lookahead == 'n') ADVANCE(212);
      END_STATE();
    case 158:
      if (lookahead == 'n') ADVANCE(88);
      END_STATE();
    case 159:
      if (lookahead == 'n') ADVANCE(57);
      END_STATE();
    case 160:
      if (lookahead == 'n') ADVANCE(89);
      END_STATE();
    case 161:
      if (lookahead == 'n') ADVANCE(191);
      END_STATE();
    case 162:
      if (lookahead == 'n') ADVANCE(90);
      END_STATE();
    case 163:
      if (lookahead == 'n') ADVANCE(216);
      END_STATE();
    case 164:
      if (lookahead == 'n') ADVANCE(119);
      END_STATE();
    case 165:
      if (lookahead == 'n') ADVANCE(117);
      END_STATE();
    case 166:
      if (lookahead == 'n') ADVANCE(118);
      END_STATE();
    case 167:
      if (lookahead == 'n') ADVANCE(121);
      END_STATE();
    case 168:
      if (lookahead == 'n') ADVANCE(120);
      END_STATE();
    case 169:
      if (lookahead == 'o') ADVANCE(143);
      END_STATE();
    case 170:
      if (lookahead == 'o') ADVANCE(157);
      END_STATE();
    case 171:
      if (lookahead == 'o') ADVANCE(177);
      END_STATE();
    case 172:
      if (lookahead == 'o') ADVANCE(180);
      END_STATE();
    case 173:
      if (lookahead == 'o') ADVANCE(154);
      END_STATE();
    case 174:
      if (lookahead == 'o') ADVANCE(179);
      END_STATE();
    case 175:
      if (lookahead == 'q') ADVANCE(221);
      END_STATE();
    case 176:
      if (lookahead == 'r') ADVANCE(327);
      END_STATE();
    case 177:
      if (lookahead == 'r') ADVANCE(320);
      END_STATE();
    case 178:
      if (lookahead == 'r') ADVANCE(255);
      END_STATE();
    case 179:
      if (lookahead == 'r') ADVANCE(302);
      END_STATE();
    case 180:
      if (lookahead == 'r') ADVANCE(92);
      END_STATE();
    case 181:
      if (lookahead == 'r') ADVANCE(73);
      END_STATE();
    case 182:
      if (lookahead == 'r') ADVANCE(70);
      END_STATE();
    case 183:
      if (lookahead == 'r') ADVANCE(108);
      END_STATE();
    case 184:
      if (lookahead == 'r') ADVANCE(182);
      END_STATE();
    case 185:
      if (lookahead == 'r') ADVANCE(209);
      END_STATE();
    case 186:
      if (lookahead == 'r') ADVANCE(80);
      END_STATE();
    case 187:
      if (lookahead == 'r') ADVANCE(230);
      END_STATE();
    case 188:
      if (lookahead == 'r') ADVANCE(132);
      END_STATE();
    case 189:
      if (lookahead == 's') ADVANCE(260);
      END_STATE();
    case 190:
      if (lookahead == 's') ADVANCE(254);
      END_STATE();
    case 191:
      if (lookahead == 's') ADVANCE(259);
      END_STATE();
    case 192:
      if (lookahead == 's') ADVANCE(313);
      END_STATE();
    case 193:
      if (lookahead == 's') ADVANCE(213);
      END_STATE();
    case 194:
      if (lookahead == 's') ADVANCE(215);
      END_STATE();
    case 195:
      if (lookahead == 's') ADVANCE(198);
      END_STATE();
    case 196:
      if (lookahead == 's') ADVANCE(217);
      END_STATE();
    case 197:
      if (lookahead == 's') ADVANCE(110);
      END_STATE();
    case 198:
      if (lookahead == 's') ADVANCE(127);
      END_STATE();
    case 199:
      if (lookahead == 's') ADVANCE(131);
      END_STATE();
    case 200:
      if (lookahead == 's') ADVANCE(61);
      END_STATE();
    case 201:
      if (lookahead == 's') ADVANCE(133);
      END_STATE();
    case 202:
      if (lookahead == 's') ADVANCE(134);
      END_STATE();
    case 203:
      if (lookahead == 's') ADVANCE(135);
      END_STATE();
    case 204:
      if (lookahead == 's') ADVANCE(201);
      END_STATE();
    case 205:
      if (lookahead == 's') ADVANCE(137);
      END_STATE();
    case 206:
      if (lookahead == 's') ADVANCE(202);
      END_STATE();
    case 207:
      if (lookahead == 's') ADVANCE(203);
      END_STATE();
    case 208:
      if (lookahead == 's') ADVANCE(205);
      END_STATE();
    case 209:
      if (lookahead == 't') ADVANCE(300);
      END_STATE();
    case 210:
      if (lookahead == 't') ADVANCE(84);
      END_STATE();
    case 211:
      if (lookahead == 't') ADVANCE(98);
      END_STATE();
    case 212:
      if (lookahead == 't') ADVANCE(72);
      END_STATE();
    case 213:
      if (lookahead == 't') ADVANCE(189);
      END_STATE();
    case 214:
      if (lookahead == 't') ADVANCE(54);
      END_STATE();
    case 215:
      if (lookahead == 't') ADVANCE(188);
      END_STATE();
    case 216:
      if (lookahead == 't') ADVANCE(123);
      END_STATE();
    case 217:
      if (lookahead == 't') ADVANCE(81);
      END_STATE();
    case 218:
      if (lookahead == 't') ADVANCE(107);
      END_STATE();
    case 219:
      if (lookahead == 't') ADVANCE(174);
      END_STATE();
    case 220:
      if (lookahead == 't') ADVANCE(65);
      END_STATE();
    case 221:
      if (lookahead == 'u') ADVANCE(74);
      END_STATE();
    case 222:
      if (lookahead == 'u') ADVANCE(93);
      END_STATE();
    case 223:
      if (lookahead == 'u') ADVANCE(94);
      END_STATE();
    case 224:
      if (lookahead == 'u') ADVANCE(105);
      END_STATE();
    case 225:
      if (lookahead == 'v') ADVANCE(75);
      END_STATE();
    case 226:
      if (lookahead == 'v') ADVANCE(83);
      END_STATE();
    case 227:
      if (lookahead == 'w') ADVANCE(100);
      END_STATE();
    case 228:
      if (lookahead == 'x') ADVANCE(124);
      END_STATE();
    case 229:
      if (lookahead == 'y') ADVANCE(58);
      END_STATE();
    case 230:
      if (lookahead == 'y') ADVANCE(63);
      END_STATE();
    case 231:
      ADVANCE_MAP(
        '"', 295,
        '/', 295,
        '\\', 295,
        'b', 295,
        'f', 295,
        'n', 295,
        'r', 295,
        't', 295,
        'u', 295,
      );
      END_STATE();
    case 232:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(299);
      END_STATE();
    case 233:
      if (eof) ADVANCE(239);
      ADVANCE_MAP(
        '!', 25,
        '"', 269,
        '(', 243,
        ')', 244,
        ',', 264,
        '.', 261,
        ':', 266,
        '<', 251,
        '=', 247,
        '>', 250,
        'E', 353,
        '[', 240,
        ']', 241,
        'a', 547,
        'b', 498,
        'c', 700,
        'd', 499,
        'e', 833,
        'f', 455,
        'i', 549,
        'l', 509,
        'm', 458,
        'n', 703,
        'o', 551,
        's', 514,
        't', 719,
        '{', 263,
        '}', 265,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(233);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(262);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 234:
      if (eof) ADVANCE(239);
      ADVANCE_MAP(
        '!', 25,
        ')', 244,
        ',', 264,
        '.', 261,
        '<', 251,
        '=', 26,
        '>', 250,
        'E', 47,
        ']', 241,
        'a', 112,
        'b', 95,
        'c', 170,
        'e', 228,
        'f', 171,
        'm', 71,
        '}', 265,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(234);
      END_STATE();
    case 235:
      if (eof) ADVANCE(239);
      ADVANCE_MAP(
        '!', 25,
        ')', 244,
        '.', 261,
        '<', 251,
        '=', 26,
        '>', 250,
        'E', 383,
        ']', 241,
        'a', 547,
        'b', 498,
        'c', 700,
        'd', 499,
        'e', 833,
        'f', 701,
        'i', 550,
        'l', 509,
        'm', 458,
        'o', 551,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(235);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 236:
      if (eof) ADVANCE(239);
      ADVANCE_MAP(
        '!', 25,
        ')', 244,
        '<', 251,
        '=', 26,
        '>', 250,
        'E', 383,
        ']', 241,
        'a', 548,
        'b', 498,
        'c', 700,
        'd', 499,
        'e', 833,
        'f', 701,
        'i', 550,
        'l', 509,
        'm', 458,
        'o', 552,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(236);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 237:
      if (eof) ADVANCE(239);
      ADVANCE_MAP(
        '(', 21,
        ')', 244,
        '.', 261,
        'E', 383,
        ']', 241,
        'd', 499,
        'f', 701,
        'i', 550,
        'l', 509,
        'o', 552,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(237);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 238:
      if (eof) ADVANCE(239);
      ADVANCE_MAP(
        ')', 244,
        '.', 261,
        'E', 383,
        ']', 241,
        'a', 666,
        'd', 499,
        'f', 701,
        'i', 550,
        'l', 509,
        'o', 551,
        's', 514,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(238);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == ')') ADVANCE(245);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(anon_sym_LPAREN_RPAREN);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(248);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(252);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(253);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(anon_sym_matches);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(anon_sym_after);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(anon_sym_before);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(anon_sym_between);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(anon_sym_and);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(anon_sym_contains);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(anon_sym_exists);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(sym_pos_int);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(262);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(anon_sym_DQUOTE_DQUOTE);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      if (lookahead == '"') ADVANCE(267);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'E') ADVANCE(274);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(270);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'O') ADVANCE(273);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'R') ADVANCE(271);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'R') ADVANCE(275);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'R') ADVANCE(272);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '_') ADVANCE(285);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '_') ADVANCE(279);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '_') ADVANCE(290);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'd') ADVANCE(294);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'e') ADVANCE(287);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'g') ADVANCE(277);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'g') ADVANCE(276);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'i') ADVANCE(292);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'i') ADVANCE(286);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'i') ADVANCE(288);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'm') ADVANCE(282);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'n') ADVANCE(280);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'n') ADVANCE(278);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'n') ADVANCE(281);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 'r') ADVANCE(284);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 's') ADVANCE(293);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 's') ADVANCE(283);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 's') ADVANCE(291);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == 't') ADVANCE(289);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(294);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(298);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(22);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(298);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(22);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(297);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(22);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(298);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(299);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_query_start);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_query_body);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_main_iterator);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_array_query_end);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_element_query_end);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_iterator);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_update_field);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_delete_field);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_filter_expression);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_offset_value);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_limit_value);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_expression);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_bool_value);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_equals);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_colon);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_value);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_brace_end);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_array_end);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_parenthesis_end);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(anon_sym_ERROR_missing_string_end);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(anon_sym_for);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(anon_sym_let);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(anon_sym_in);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(sym_false);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(sym_null);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(anon_sym_and2);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(anon_sym_or);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(anon_sym_not);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(anon_sym_set);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(anon_sym_delete);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(anon_sym_offset);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(anon_sym_limit);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(352);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(354);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(355);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(356);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(357);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(358);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(359);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(360);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(361);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(362);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(363);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(364);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(365);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(366);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(367);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(368);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 350:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'O') ADVANCE(369);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 351:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(334);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 352:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(423);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 353:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(351);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(435);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 355:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(436);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 356:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(437);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 357:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(438);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 358:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(439);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 359:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(440);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 360:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(441);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 361:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(442);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 362:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(443);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 363:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(444);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 364:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(445);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 365:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(446);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 366:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(447);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 367:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(448);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 368:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(449);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 369:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(450);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 370:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(335);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 371:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(370);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 372:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(336);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 373:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(372);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 374:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(337);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 375:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(374);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 376:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(338);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 377:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(376);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 378:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(339);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 379:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(378);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 380:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(340);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 381:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(380);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 382:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(341);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 383:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(382);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 384:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(342);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 385:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(384);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 386:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(343);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 387:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(386);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 388:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(344);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 389:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(388);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 390:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(345);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 391:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(390);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 392:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(346);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 393:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(392);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 394:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(347);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 395:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(394);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 396:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(348);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 397:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(396);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 398:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(349);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 399:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(398);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 400:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(350);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 401:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'R') ADVANCE(400);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 402:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(460);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 403:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(829);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 404:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(516);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 405:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(478);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 406:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(718);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 407:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(482);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 408:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(479);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 409:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(480);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 410:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(481);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 411:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(483);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 412:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(468);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 413:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(647);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 414:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(473);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 415:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(534);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 416:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(474);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 417:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(545);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 418:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(469);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 419:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(753);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 420:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(497);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 421:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(816);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 422:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(592);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 423:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(646);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 424:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(554);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 425:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(627);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 426:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(519);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 427:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(508);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 428:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(523);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 429:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(529);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 430:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(530);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 431:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(531);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 432:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(517);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 433:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(556);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 434:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(717);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 435:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(650);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 436:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(651);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 437:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(652);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 438:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(653);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 439:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(654);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 440:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(655);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 441:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(656);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 442:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(657);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 443:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(658);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 444:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(659);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 445:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(660);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 446:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(661);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 447:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(662);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 448:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(663);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 449:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(664);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 450:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(665);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 451:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(830);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 452:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(831);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 453:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == '_') ADVANCE(828);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 454:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(837);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 455:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(629);
      if (lookahead == 'o') ADVANCE(720);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 456:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(629);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 457:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(485);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 458:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(793);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 459:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(580);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 460:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      ADVANCE_MAP(
        'a', 725,
        'b', 712,
        'c', 705,
        'd', 543,
        'e', 636,
        'f', 583,
        'i', 805,
        'l', 610,
        'm', 462,
        'o', 558,
        'p', 466,
        'q', 820,
        's', 802,
        'u', 714,
        'v', 461,
      );
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 461:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(639);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 462:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(582);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 463:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(728);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 464:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(809);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 465:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(635);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 466:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(727);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 467:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(843);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 468:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(733);
      if (lookahead == 'm') ADVANCE(462);
      if (lookahead == 'q') ADVANCE(827);
      if (lookahead == 's') ADVANCE(802);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 469:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(733);
      if (lookahead == 's') ADVANCE(802);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 470:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(641);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 471:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(811);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 472:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(812);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 473:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(739);
      if (lookahead == 'e') ADVANCE(637);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 474:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(739);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 475:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(642);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 476:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(842);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 477:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'a') ADVANCE(643);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 478:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(704);
      if (lookahead == 's') ADVANCE(810);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 479:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(704);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 480:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(713);
      if (lookahead == 'e') ADVANCE(834);
      if (lookahead == 's') ADVANCE(802);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 481:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(713);
      if (lookahead == 'f') ADVANCE(583);
      if (lookahead == 's') ADVANCE(802);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 482:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(713);
      if (lookahead == 'm') ADVANCE(462);
      if (lookahead == 'q') ADVANCE(827);
      if (lookahead == 's') ADVANCE(802);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 483:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'b') ADVANCE(713);
      if (lookahead == 's') ADVANCE(802);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 484:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'c') ADVANCE(577);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 485:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'c') ADVANCE(515);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 486:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(326);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 487:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(317);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 488:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(316);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 489:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(319);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 490:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(307);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 491:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(306);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 492:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(303);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 493:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(318);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 494:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(304);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 495:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(836);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 496:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(472);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 497:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'd') ADVANCE(543);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 498:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(553);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 499:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(632);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 500:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(323);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 501:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(324);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 502:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(256);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 503:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(331);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 504:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(315);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 505:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(312);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 506:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(310);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 507:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(309);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 508:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(835);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 509:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(792);
      if (lookahead == 'i') ADVANCE(645);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 510:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(667);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 511:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(721);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 512:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(649);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 513:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(744);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 514:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(795);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 515:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(426);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 516:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(672);
      if (lookahead == 'q') ADVANCE(825);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 517:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(672);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 518:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(735);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 519:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(673);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 520:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(424);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 521:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(730);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 522:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(797);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 523:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(677);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 524:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(633);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 525:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(510);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 526:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(734);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 527:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(634);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 528:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(756);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 529:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(678);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 530:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(679);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 531:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(680);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 532:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(804);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 533:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(681);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 534:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(637);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 535:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(752);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 536:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(682);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 537:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(807);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 538:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(433);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 539:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(736);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 540:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(776);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 541:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(741);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 542:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(737);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 543:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(644);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 544:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(740);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 545:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(834);
      if (lookahead == 's') ADVANCE(802);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 546:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'e') ADVANCE(815);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 547:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(801);
      if (lookahead == 'n') ADVANCE(486);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 548:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(801);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 549:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(329);
      if (lookahead == 'n') ADVANCE(322);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 550:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(329);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 551:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(555);
      if (lookahead == 'r') ADVANCE(327);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 552:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(555);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 553:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(702);
      if (lookahead == 't') ADVANCE(832);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 554:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(588);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 555:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(754);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 556:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(589);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 557:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(757);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 558:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'f') ADVANCE(557);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 559:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(402);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 560:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(407);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 561:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(409);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 562:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(410);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 563:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(411);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 564:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(412);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 565:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(413);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 566:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(414);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 567:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(415);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 568:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(416);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 569:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(417);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 570:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(418);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 571:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(419);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 572:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(420);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 573:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(421);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 574:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(422);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 575:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(428);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 576:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'g') ADVANCE(453);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 577:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'h') ADVANCE(513);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 578:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'h') ADVANCE(528);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 579:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(748);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 580:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(675);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 581:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(668);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 582:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(674);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 583:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(640);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 584:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(749);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 585:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(796);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 586:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(814);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 587:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(761);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 588:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(524);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 589:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(527);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 590:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(683);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 591:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(708);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 592:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(805);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 593:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(684);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 594:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(711);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 595:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(685);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 596:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(686);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 597:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(687);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 598:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(688);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 599:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(689);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 600:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(690);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 601:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(691);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 602:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(692);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 603:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(693);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 604:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(694);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 605:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(695);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 606:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(696);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 607:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(697);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 608:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(698);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 609:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(699);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 610:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(648);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 611:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(755);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 612:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(777);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 613:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(778);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 614:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(779);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 615:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(780);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 616:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(781);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 617:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(782);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 618:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(783);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 619:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(784);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 620:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(785);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 621:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(786);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 622:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(787);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 623:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(788);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 624:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(789);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 625:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(790);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 626:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(791);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 627:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'i') ADVANCE(813);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 628:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(325);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 629:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(750);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 630:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(403);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 631:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(628);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 632:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(532);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 633:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(490);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 634:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(491);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 635:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(746);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 636:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(512);
      if (lookahead == 'q') ADVANCE(819);
      if (lookahead == 'x') ADVANCE(715);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 637:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(512);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 638:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(706);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 639:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(821);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 640:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(806);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 641:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(822);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 642:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(823);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 643:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(824);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 644:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'l') ADVANCE(537);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 645:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(585);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 646:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(584);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 647:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(462);
      if (lookahead == 'q') ADVANCE(827);
      if (lookahead == 's') ADVANCE(802);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 648:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(586);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 649:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(536);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 650:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(611);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 651:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(612);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 652:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(613);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 653:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(614);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 654:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(615);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 655:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(616);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 656:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(617);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 657:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(618);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 658:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(619);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 659:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(620);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 660:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(621);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 661:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(622);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 662:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(623);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 663:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(624);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 664:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(625);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 665:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'm') ADVANCE(626);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 666:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(486);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 667:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(257);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 668:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(559);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 669:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(314);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 670:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(311);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 671:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(308);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 672:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(487);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 673:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(488);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 674:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(425);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 675:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(745);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 676:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(799);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 677:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(489);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 678:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(492);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 679:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(493);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 680:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(494);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 681:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(808);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 682:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(803);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 683:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(575);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 684:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(560);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 685:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(561);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 686:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(562);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 687:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(563);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 688:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(564);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 689:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(565);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 690:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(566);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 691:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(567);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 692:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(568);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 693:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(569);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 694:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(570);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 695:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(571);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 696:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(576);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 697:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(572);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 698:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(573);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 699:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'n') ADVANCE(574);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 700:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(676);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 701:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(720);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 702:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(726);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 703:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(794);
      if (lookahead == 'u') ADVANCE(631);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 704:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(495);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 705:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(638);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 706:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(669);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 707:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(630);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 708:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(670);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 709:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(722);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 710:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(723);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 711:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(671);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 712:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(707);
      if (lookahead == 'r') ADVANCE(457);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 713:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'o') ADVANCE(707);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 714:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'p') ADVANCE(496);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 715:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'p') ADVANCE(729);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 716:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'p') ADVANCE(742);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 717:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'q') ADVANCE(825);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 718:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'q') ADVANCE(826);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 719:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(818);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 720:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(320);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 721:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 722:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(305);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 723:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(302);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 724:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(454);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 725:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(724);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 726:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(502);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 727:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(533);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 728:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(798);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 729:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(535);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 730:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(838);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 731:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(590);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 732:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(476);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 733:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(732);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 734:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(427);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 735:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(464);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 736:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(840);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 737:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(839);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 738:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(467);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 739:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(738);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 740:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(471);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 741:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(841);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 742:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'r') ADVANCE(540);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 743:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(260);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 744:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(254);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 745:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(259);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 746:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(313);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 747:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(581);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 748:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(800);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 749:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(747);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 750:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(501);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 751:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(591);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 752:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(751);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 753:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(802);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 754:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(522);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 755:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(758);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 756:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(587);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 757:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(546);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 758:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(593);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 759:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(595);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 760:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(596);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 761:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(430);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 762:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(597);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 763:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(598);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 764:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(599);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 765:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(600);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 766:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(601);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 767:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(602);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 768:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(603);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 769:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(604);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 770:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(605);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 771:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(606);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 772:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(607);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 773:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(608);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 774:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(609);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 775:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(594);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 776:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(775);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 777:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(759);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 778:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(760);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 779:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(762);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 780:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(763);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 781:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(764);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 782:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(765);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 783:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(766);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 784:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(767);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 785:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(768);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 786:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(769);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 787:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(770);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 788:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(771);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 789:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(772);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 790:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(773);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 791:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 's') ADVANCE(774);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 792:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(321);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 793:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(484);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 794:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(328);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 795:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(330);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 796:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(333);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 797:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(332);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 798:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(300);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 799:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(459);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 800:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(743);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 801:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(511);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 802:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(731);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 803:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(406);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 804:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(503);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 805:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(518);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 806:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(526);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 807:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(520);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 808:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(578);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 809:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(709);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 810:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(463);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 811:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(710);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 812:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(538);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 813:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(544);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 814:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(451);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 815:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 't') ADVANCE(452);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 816:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(714);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 817:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(631);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 818:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(500);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 819:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(465);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 820:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(521);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 821:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(504);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 822:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(505);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 823:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(506);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 824:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(507);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 825:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(539);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 826:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(541);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 827:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'u') ADVANCE(542);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 828:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'v') ADVANCE(461);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 829:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'v') ADVANCE(470);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 830:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'v') ADVANCE(475);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 831:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'v') ADVANCE(477);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 832:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'w') ADVANCE(525);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 833:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'x') ADVANCE(579);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 834:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'x') ADVANCE(715);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 835:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'x') ADVANCE(716);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 836:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(301);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 837:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(404);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 838:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(405);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 839:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(408);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 840:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(429);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 841:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(431);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 842:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(432);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 843:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (lookahead == 'y') ADVANCE(434);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    case 844:
      ACCEPT_TOKEN(aux_sym_ident_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(844);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 2},
  [2] = {.lex_state = 8},
  [3] = {.lex_state = 8},
  [4] = {.lex_state = 8},
  [5] = {.lex_state = 8},
  [6] = {.lex_state = 8},
  [7] = {.lex_state = 8},
  [8] = {.lex_state = 8},
  [9] = {.lex_state = 9},
  [10] = {.lex_state = 9},
  [11] = {.lex_state = 9},
  [12] = {.lex_state = 9},
  [13] = {.lex_state = 9},
  [14] = {.lex_state = 10},
  [15] = {.lex_state = 9},
  [16] = {.lex_state = 10},
  [17] = {.lex_state = 10},
  [18] = {.lex_state = 11},
  [19] = {.lex_state = 12},
  [20] = {.lex_state = 11},
  [21] = {.lex_state = 11},
  [22] = {.lex_state = 11},
  [23] = {.lex_state = 12},
  [24] = {.lex_state = 11},
  [25] = {.lex_state = 12},
  [26] = {.lex_state = 12},
  [27] = {.lex_state = 11},
  [28] = {.lex_state = 12},
  [29] = {.lex_state = 11},
  [30] = {.lex_state = 11},
  [31] = {.lex_state = 12},
  [32] = {.lex_state = 12},
  [33] = {.lex_state = 12},
  [34] = {.lex_state = 11},
  [35] = {.lex_state = 11},
  [36] = {.lex_state = 12},
  [37] = {.lex_state = 12},
  [38] = {.lex_state = 11},
  [39] = {.lex_state = 12},
  [40] = {.lex_state = 11},
  [41] = {.lex_state = 13},
  [42] = {.lex_state = 13},
  [43] = {.lex_state = 13},
  [44] = {.lex_state = 13},
  [45] = {.lex_state = 13},
  [46] = {.lex_state = 13},
  [47] = {.lex_state = 13},
  [48] = {.lex_state = 13},
  [49] = {.lex_state = 13},
  [50] = {.lex_state = 13},
  [51] = {.lex_state = 13},
  [52] = {.lex_state = 13},
  [53] = {.lex_state = 237},
  [54] = {.lex_state = 237},
  [55] = {.lex_state = 237},
  [56] = {.lex_state = 237},
  [57] = {.lex_state = 237},
  [58] = {.lex_state = 235},
  [59] = {.lex_state = 235},
  [60] = {.lex_state = 235},
  [61] = {.lex_state = 235},
  [62] = {.lex_state = 235},
  [63] = {.lex_state = 235},
  [64] = {.lex_state = 18},
  [65] = {.lex_state = 18},
  [66] = {.lex_state = 18},
  [67] = {.lex_state = 19},
  [68] = {.lex_state = 19},
  [69] = {.lex_state = 235},
  [70] = {.lex_state = 19},
  [71] = {.lex_state = 235},
  [72] = {.lex_state = 235},
  [73] = {.lex_state = 19},
  [74] = {.lex_state = 235},
  [75] = {.lex_state = 18},
  [76] = {.lex_state = 19},
  [77] = {.lex_state = 235},
  [78] = {.lex_state = 235},
  [79] = {.lex_state = 18},
  [80] = {.lex_state = 2},
  [81] = {.lex_state = 236},
  [82] = {.lex_state = 6},
  [83] = {.lex_state = 14},
  [84] = {.lex_state = 4},
  [85] = {.lex_state = 2},
  [86] = {.lex_state = 14},
  [87] = {.lex_state = 14},
  [88] = {.lex_state = 6},
  [89] = {.lex_state = 2},
  [90] = {.lex_state = 2},
  [91] = {.lex_state = 4},
  [92] = {.lex_state = 14},
  [93] = {.lex_state = 6},
  [94] = {.lex_state = 14},
  [95] = {.lex_state = 14},
  [96] = {.lex_state = 4},
  [97] = {.lex_state = 15},
  [98] = {.lex_state = 2},
  [99] = {.lex_state = 14},
  [100] = {.lex_state = 14},
  [101] = {.lex_state = 15},
  [102] = {.lex_state = 14},
  [103] = {.lex_state = 14},
  [104] = {.lex_state = 14},
  [105] = {.lex_state = 15},
  [106] = {.lex_state = 14},
  [107] = {.lex_state = 14},
  [108] = {.lex_state = 14},
  [109] = {.lex_state = 236},
  [110] = {.lex_state = 14},
  [111] = {.lex_state = 14},
  [112] = {.lex_state = 236},
  [113] = {.lex_state = 236},
  [114] = {.lex_state = 236},
  [115] = {.lex_state = 236},
  [116] = {.lex_state = 236},
  [117] = {.lex_state = 2},
  [118] = {.lex_state = 236},
  [119] = {.lex_state = 236},
  [120] = {.lex_state = 236},
  [121] = {.lex_state = 236},
  [122] = {.lex_state = 236},
  [123] = {.lex_state = 236},
  [124] = {.lex_state = 4},
  [125] = {.lex_state = 6},
  [126] = {.lex_state = 6},
  [127] = {.lex_state = 4},
  [128] = {.lex_state = 6},
  [129] = {.lex_state = 236},
  [130] = {.lex_state = 236},
  [131] = {.lex_state = 236},
  [132] = {.lex_state = 236},
  [133] = {.lex_state = 4},
  [134] = {.lex_state = 236},
  [135] = {.lex_state = 236},
  [136] = {.lex_state = 236},
  [137] = {.lex_state = 4},
  [138] = {.lex_state = 4},
  [139] = {.lex_state = 3},
  [140] = {.lex_state = 4},
  [141] = {.lex_state = 3},
  [142] = {.lex_state = 6},
  [143] = {.lex_state = 6},
  [144] = {.lex_state = 4},
  [145] = {.lex_state = 6},
  [146] = {.lex_state = 3},
  [147] = {.lex_state = 4},
  [148] = {.lex_state = 6},
  [149] = {.lex_state = 6},
  [150] = {.lex_state = 6},
  [151] = {.lex_state = 3},
  [152] = {.lex_state = 4},
  [153] = {.lex_state = 16},
  [154] = {.lex_state = 5},
  [155] = {.lex_state = 7},
  [156] = {.lex_state = 7},
  [157] = {.lex_state = 5},
  [158] = {.lex_state = 7},
  [159] = {.lex_state = 7},
  [160] = {.lex_state = 7},
  [161] = {.lex_state = 7},
  [162] = {.lex_state = 7},
  [163] = {.lex_state = 5},
  [164] = {.lex_state = 7},
  [165] = {.lex_state = 7},
  [166] = {.lex_state = 5},
  [167] = {.lex_state = 5},
  [168] = {.lex_state = 5},
  [169] = {.lex_state = 7},
  [170] = {.lex_state = 7},
  [171] = {.lex_state = 7},
  [172] = {.lex_state = 7},
  [173] = {.lex_state = 7},
  [174] = {.lex_state = 7},
  [175] = {.lex_state = 5},
  [176] = {.lex_state = 7},
  [177] = {.lex_state = 5},
  [178] = {.lex_state = 234},
  [179] = {.lex_state = 234},
  [180] = {.lex_state = 7},
  [181] = {.lex_state = 5},
  [182] = {.lex_state = 5},
  [183] = {.lex_state = 5},
  [184] = {.lex_state = 234},
  [185] = {.lex_state = 5},
  [186] = {.lex_state = 234},
  [187] = {.lex_state = 5},
  [188] = {.lex_state = 5},
  [189] = {.lex_state = 5},
  [190] = {.lex_state = 5},
  [191] = {.lex_state = 234},
  [192] = {.lex_state = 234},
  [193] = {.lex_state = 7},
  [194] = {.lex_state = 5},
  [195] = {.lex_state = 3},
  [196] = {.lex_state = 5},
  [197] = {.lex_state = 5},
  [198] = {.lex_state = 7},
  [199] = {.lex_state = 5},
  [200] = {.lex_state = 7},
  [201] = {.lex_state = 234},
  [202] = {.lex_state = 234},
  [203] = {.lex_state = 234},
  [204] = {.lex_state = 234},
  [205] = {.lex_state = 234},
  [206] = {.lex_state = 234},
  [207] = {.lex_state = 234},
  [208] = {.lex_state = 234},
  [209] = {.lex_state = 234},
  [210] = {.lex_state = 3},
  [211] = {.lex_state = 3},
  [212] = {.lex_state = 3},
  [213] = {.lex_state = 3},
  [214] = {.lex_state = 238},
  [215] = {.lex_state = 238},
  [216] = {.lex_state = 238},
  [217] = {.lex_state = 238},
  [218] = {.lex_state = 238},
  [219] = {.lex_state = 238},
  [220] = {.lex_state = 238},
  [221] = {.lex_state = 3},
  [222] = {.lex_state = 238},
  [223] = {.lex_state = 238},
  [224] = {.lex_state = 238},
  [225] = {.lex_state = 238},
  [226] = {.lex_state = 238},
  [227] = {.lex_state = 238},
  [228] = {.lex_state = 20},
  [229] = {.lex_state = 20},
  [230] = {.lex_state = 23},
  [231] = {.lex_state = 238},
  [232] = {.lex_state = 23},
  [233] = {.lex_state = 20},
  [234] = {.lex_state = 237},
  [235] = {.lex_state = 23},
  [236] = {.lex_state = 20},
  [237] = {.lex_state = 20},
  [238] = {.lex_state = 23},
  [239] = {.lex_state = 20},
  [240] = {.lex_state = 238},
  [241] = {.lex_state = 238},
  [242] = {.lex_state = 237},
  [243] = {.lex_state = 23},
  [244] = {.lex_state = 237},
  [245] = {.lex_state = 23},
  [246] = {.lex_state = 238},
  [247] = {.lex_state = 238},
  [248] = {.lex_state = 238},
  [249] = {.lex_state = 238},
  [250] = {.lex_state = 237},
  [251] = {.lex_state = 238},
  [252] = {.lex_state = 237},
  [253] = {.lex_state = 238},
  [254] = {.lex_state = 238},
  [255] = {.lex_state = 238},
  [256] = {.lex_state = 238},
  [257] = {.lex_state = 237},
  [258] = {.lex_state = 238},
  [259] = {.lex_state = 238},
  [260] = {.lex_state = 238},
  [261] = {.lex_state = 238},
  [262] = {.lex_state = 238},
  [263] = {.lex_state = 238},
  [264] = {.lex_state = 238},
  [265] = {.lex_state = 238},
  [266] = {.lex_state = 238},
  [267] = {.lex_state = 238},
  [268] = {.lex_state = 238},
  [269] = {.lex_state = 238},
  [270] = {.lex_state = 238},
  [271] = {.lex_state = 238},
  [272] = {.lex_state = 238},
  [273] = {.lex_state = 3},
  [274] = {.lex_state = 238},
  [275] = {.lex_state = 238},
  [276] = {.lex_state = 238},
  [277] = {.lex_state = 20},
  [278] = {.lex_state = 23},
  [279] = {.lex_state = 23},
  [280] = {.lex_state = 23},
  [281] = {.lex_state = 23},
  [282] = {.lex_state = 20},
  [283] = {.lex_state = 23},
  [284] = {.lex_state = 13},
  [285] = {.lex_state = 20},
  [286] = {.lex_state = 23},
  [287] = {.lex_state = 237},
  [288] = {.lex_state = 20},
  [289] = {.lex_state = 20},
  [290] = {.lex_state = 20},
  [291] = {.lex_state = 20},
  [292] = {.lex_state = 23},
  [293] = {.lex_state = 237},
  [294] = {.lex_state = 237},
  [295] = {.lex_state = 237},
  [296] = {.lex_state = 237},
  [297] = {.lex_state = 237},
  [298] = {.lex_state = 20},
  [299] = {.lex_state = 19},
  [300] = {.lex_state = 20},
  [301] = {.lex_state = 23},
  [302] = {.lex_state = 237},
  [303] = {.lex_state = 237},
  [304] = {.lex_state = 237},
  [305] = {.lex_state = 23},
  [306] = {.lex_state = 23},
  [307] = {.lex_state = 237},
  [308] = {.lex_state = 237},
  [309] = {.lex_state = 237},
  [310] = {.lex_state = 237},
  [311] = {.lex_state = 19},
  [312] = {.lex_state = 237},
  [313] = {.lex_state = 237},
  [314] = {.lex_state = 237},
  [315] = {.lex_state = 237},
  [316] = {.lex_state = 237},
  [317] = {.lex_state = 237},
  [318] = {.lex_state = 237},
  [319] = {.lex_state = 237},
  [320] = {.lex_state = 237},
  [321] = {.lex_state = 237},
  [322] = {.lex_state = 20},
  [323] = {.lex_state = 237},
  [324] = {.lex_state = 237},
  [325] = {.lex_state = 237},
  [326] = {.lex_state = 237},
  [327] = {.lex_state = 237},
  [328] = {.lex_state = 237},
  [329] = {.lex_state = 19},
  [330] = {.lex_state = 237},
  [331] = {.lex_state = 237},
  [332] = {.lex_state = 237},
  [333] = {.lex_state = 237},
  [334] = {.lex_state = 237},
  [335] = {.lex_state = 18},
  [336] = {.lex_state = 237},
  [337] = {.lex_state = 237},
  [338] = {.lex_state = 237},
  [339] = {.lex_state = 237},
  [340] = {.lex_state = 237},
  [341] = {.lex_state = 18},
  [342] = {.lex_state = 237},
  [343] = {.lex_state = 18},
  [344] = {.lex_state = 237},
  [345] = {.lex_state = 237},
  [346] = {.lex_state = 237},
  [347] = {.lex_state = 23},
  [348] = {.lex_state = 20},
  [349] = {.lex_state = 235},
  [350] = {.lex_state = 20},
  [351] = {.lex_state = 23},
  [352] = {.lex_state = 235},
  [353] = {.lex_state = 20},
  [354] = {.lex_state = 20},
  [355] = {.lex_state = 20},
  [356] = {.lex_state = 20},
  [357] = {.lex_state = 20},
  [358] = {.lex_state = 20},
  [359] = {.lex_state = 14},
  [360] = {.lex_state = 23},
  [361] = {.lex_state = 23},
  [362] = {.lex_state = 23},
  [363] = {.lex_state = 20},
  [364] = {.lex_state = 19},
  [365] = {.lex_state = 19},
  [366] = {.lex_state = 23},
  [367] = {.lex_state = 20},
  [368] = {.lex_state = 20},
  [369] = {.lex_state = 23},
  [370] = {.lex_state = 23},
  [371] = {.lex_state = 23},
  [372] = {.lex_state = 20},
  [373] = {.lex_state = 20},
  [374] = {.lex_state = 23},
  [375] = {.lex_state = 18},
  [376] = {.lex_state = 23},
  [377] = {.lex_state = 18},
  [378] = {.lex_state = 20},
  [379] = {.lex_state = 20},
  [380] = {.lex_state = 20},
  [381] = {.lex_state = 23},
  [382] = {.lex_state = 23},
  [383] = {.lex_state = 20},
  [384] = {.lex_state = 23},
  [385] = {.lex_state = 20},
  [386] = {.lex_state = 23},
  [387] = {.lex_state = 23},
  [388] = {.lex_state = 23},
  [389] = {.lex_state = 20},
  [390] = {.lex_state = 20},
  [391] = {.lex_state = 23},
  [392] = {.lex_state = 23},
  [393] = {.lex_state = 23},
  [394] = {.lex_state = 20},
  [395] = {.lex_state = 23},
  [396] = {.lex_state = 23},
  [397] = {.lex_state = 20},
  [398] = {.lex_state = 23},
  [399] = {.lex_state = 20},
  [400] = {.lex_state = 23},
  [401] = {.lex_state = 20},
  [402] = {.lex_state = 18},
  [403] = {.lex_state = 20},
  [404] = {.lex_state = 23},
  [405] = {.lex_state = 23},
  [406] = {.lex_state = 23},
  [407] = {.lex_state = 235},
  [408] = {.lex_state = 20},
  [409] = {.lex_state = 20},
  [410] = {.lex_state = 14},
  [411] = {.lex_state = 235},
  [412] = {.lex_state = 19},
  [413] = {.lex_state = 18},
  [414] = {.lex_state = 19},
  [415] = {.lex_state = 18},
  [416] = {.lex_state = 19},
  [417] = {.lex_state = 19},
  [418] = {.lex_state = 18},
  [419] = {.lex_state = 19},
  [420] = {.lex_state = 19},
  [421] = {.lex_state = 18},
  [422] = {.lex_state = 19},
  [423] = {.lex_state = 18},
  [424] = {.lex_state = 19},
  [425] = {.lex_state = 19},
  [426] = {.lex_state = 19},
  [427] = {.lex_state = 19},
  [428] = {.lex_state = 19},
  [429] = {.lex_state = 19},
  [430] = {.lex_state = 19},
  [431] = {.lex_state = 19},
  [432] = {.lex_state = 19},
  [433] = {.lex_state = 18},
  [434] = {.lex_state = 19},
  [435] = {.lex_state = 19},
  [436] = {.lex_state = 19},
  [437] = {.lex_state = 19},
  [438] = {.lex_state = 19},
  [439] = {.lex_state = 19},
  [440] = {.lex_state = 19},
  [441] = {.lex_state = 19},
  [442] = {.lex_state = 19},
  [443] = {.lex_state = 18},
  [444] = {.lex_state = 19},
  [445] = {.lex_state = 19},
  [446] = {.lex_state = 18},
  [447] = {.lex_state = 19},
  [448] = {.lex_state = 18},
  [449] = {.lex_state = 19},
  [450] = {.lex_state = 18},
  [451] = {.lex_state = 18},
  [452] = {.lex_state = 18},
  [453] = {.lex_state = 19},
  [454] = {.lex_state = 19},
  [455] = {.lex_state = 19},
  [456] = {.lex_state = 19},
  [457] = {.lex_state = 18},
  [458] = {.lex_state = 19},
  [459] = {.lex_state = 18},
  [460] = {.lex_state = 18},
  [461] = {.lex_state = 18},
  [462] = {.lex_state = 18},
  [463] = {.lex_state = 19},
  [464] = {.lex_state = 18},
  [465] = {.lex_state = 18},
  [466] = {.lex_state = 19},
  [467] = {.lex_state = 18},
  [468] = {.lex_state = 18},
  [469] = {.lex_state = 19},
  [470] = {.lex_state = 18},
  [471] = {.lex_state = 19},
  [472] = {.lex_state = 18},
  [473] = {.lex_state = 18},
  [474] = {.lex_state = 18},
  [475] = {.lex_state = 18},
  [476] = {.lex_state = 18},
  [477] = {.lex_state = 19},
  [478] = {.lex_state = 19},
  [479] = {.lex_state = 19},
  [480] = {.lex_state = 18},
  [481] = {.lex_state = 18},
  [482] = {.lex_state = 18},
  [483] = {.lex_state = 18},
  [484] = {.lex_state = 18},
  [485] = {.lex_state = 18},
  [486] = {.lex_state = 18},
  [487] = {.lex_state = 19},
  [488] = {.lex_state = 19},
  [489] = {.lex_state = 18},
  [490] = {.lex_state = 18},
  [491] = {.lex_state = 18},
  [492] = {.lex_state = 18},
  [493] = {.lex_state = 18},
  [494] = {.lex_state = 19},
  [495] = {.lex_state = 18},
  [496] = {.lex_state = 18},
  [497] = {.lex_state = 18},
  [498] = {.lex_state = 18},
  [499] = {.lex_state = 0},
  [500] = {.lex_state = 0},
  [501] = {.lex_state = 0},
  [502] = {.lex_state = 0},
  [503] = {.lex_state = 0},
  [504] = {.lex_state = 0},
  [505] = {.lex_state = 0},
  [506] = {.lex_state = 0},
  [507] = {.lex_state = 0},
  [508] = {.lex_state = 0},
  [509] = {.lex_state = 0},
  [510] = {.lex_state = 2},
  [511] = {.lex_state = 2},
  [512] = {.lex_state = 2},
  [513] = {.lex_state = 2},
  [514] = {.lex_state = 2},
  [515] = {.lex_state = 2},
  [516] = {.lex_state = 2},
  [517] = {.lex_state = 2},
  [518] = {.lex_state = 2},
  [519] = {.lex_state = 2},
  [520] = {.lex_state = 2},
  [521] = {.lex_state = 2},
  [522] = {.lex_state = 2},
  [523] = {.lex_state = 2},
  [524] = {.lex_state = 2},
  [525] = {.lex_state = 2},
  [526] = {.lex_state = 2},
  [527] = {.lex_state = 2},
  [528] = {.lex_state = 2},
  [529] = {.lex_state = 2},
  [530] = {.lex_state = 2},
  [531] = {.lex_state = 2},
  [532] = {.lex_state = 2},
  [533] = {.lex_state = 2},
  [534] = {.lex_state = 2},
  [535] = {.lex_state = 2},
  [536] = {.lex_state = 2},
  [537] = {.lex_state = 28},
  [538] = {.lex_state = 29},
  [539] = {.lex_state = 28},
  [540] = {.lex_state = 29},
  [541] = {.lex_state = 30},
  [542] = {.lex_state = 28},
  [543] = {.lex_state = 29},
  [544] = {.lex_state = 30},
  [545] = {.lex_state = 0},
  [546] = {.lex_state = 30},
  [547] = {.lex_state = 1},
  [548] = {.lex_state = 31},
  [549] = {.lex_state = 1},
  [550] = {.lex_state = 1},
  [551] = {.lex_state = 1},
  [552] = {.lex_state = 1},
  [553] = {.lex_state = 31},
  [554] = {.lex_state = 1},
  [555] = {.lex_state = 1},
  [556] = {.lex_state = 1},
  [557] = {.lex_state = 0},
  [558] = {.lex_state = 1},
  [559] = {.lex_state = 1},
  [560] = {.lex_state = 1},
  [561] = {.lex_state = 1},
  [562] = {.lex_state = 31},
  [563] = {.lex_state = 1},
  [564] = {.lex_state = 1},
  [565] = {.lex_state = 1},
  [566] = {.lex_state = 1},
  [567] = {.lex_state = 1},
  [568] = {.lex_state = 1},
  [569] = {.lex_state = 2},
  [570] = {.lex_state = 1},
  [571] = {.lex_state = 1},
  [572] = {.lex_state = 2},
  [573] = {.lex_state = 1},
  [574] = {.lex_state = 2},
  [575] = {.lex_state = 2},
  [576] = {.lex_state = 1},
  [577] = {.lex_state = 2},
  [578] = {.lex_state = 2},
  [579] = {.lex_state = 0},
  [580] = {.lex_state = 2},
  [581] = {.lex_state = 2},
  [582] = {.lex_state = 2},
  [583] = {.lex_state = 2},
  [584] = {.lex_state = 0},
  [585] = {.lex_state = 0},
  [586] = {.lex_state = 2},
  [587] = {.lex_state = 0},
  [588] = {.lex_state = 2},
  [589] = {.lex_state = 0},
  [590] = {.lex_state = 0},
  [591] = {.lex_state = 0},
  [592] = {.lex_state = 2},
  [593] = {.lex_state = 0},
  [594] = {.lex_state = 2},
  [595] = {.lex_state = 2},
  [596] = {.lex_state = 0},
  [597] = {.lex_state = 0},
  [598] = {.lex_state = 0},
  [599] = {.lex_state = 2},
  [600] = {.lex_state = 0},
  [601] = {.lex_state = 2},
  [602] = {.lex_state = 0},
  [603] = {.lex_state = 2},
  [604] = {.lex_state = 0},
  [605] = {.lex_state = 0},
  [606] = {.lex_state = 0},
  [607] = {.lex_state = 2},
  [608] = {.lex_state = 2},
  [609] = {.lex_state = 2},
  [610] = {.lex_state = 2},
  [611] = {.lex_state = 0},
  [612] = {.lex_state = 0},
  [613] = {.lex_state = 2},
  [614] = {.lex_state = 2},
  [615] = {.lex_state = 1},
  [616] = {.lex_state = 2},
  [617] = {.lex_state = 2},
  [618] = {.lex_state = 2},
  [619] = {.lex_state = 2},
  [620] = {.lex_state = 28},
  [621] = {.lex_state = 28},
  [622] = {.lex_state = 2},
  [623] = {.lex_state = 2},
  [624] = {.lex_state = 234},
  [625] = {.lex_state = 2},
  [626] = {.lex_state = 28},
  [627] = {.lex_state = 28},
  [628] = {.lex_state = 2},
  [629] = {.lex_state = 0},
  [630] = {.lex_state = 28},
  [631] = {.lex_state = 28},
  [632] = {.lex_state = 2},
  [633] = {.lex_state = 28},
  [634] = {.lex_state = 28},
  [635] = {.lex_state = 2},
  [636] = {.lex_state = 28},
  [637] = {.lex_state = 2},
  [638] = {.lex_state = 28},
  [639] = {.lex_state = 28},
  [640] = {.lex_state = 2},
  [641] = {.lex_state = 2},
  [642] = {.lex_state = 28},
  [643] = {.lex_state = 28},
  [644] = {.lex_state = 2},
  [645] = {.lex_state = 2},
  [646] = {.lex_state = 2},
  [647] = {.lex_state = 2},
  [648] = {.lex_state = 2},
  [649] = {.lex_state = 2},
  [650] = {.lex_state = 28},
  [651] = {.lex_state = 2},
  [652] = {.lex_state = 2},
  [653] = {.lex_state = 2},
  [654] = {.lex_state = 2},
  [655] = {.lex_state = 2},
  [656] = {.lex_state = 2},
  [657] = {.lex_state = 27},
  [658] = {.lex_state = 234},
  [659] = {.lex_state = 0},
  [660] = {.lex_state = 0},
  [661] = {.lex_state = 2},
  [662] = {.lex_state = 0},
  [663] = {.lex_state = 0},
  [664] = {.lex_state = 0},
  [665] = {.lex_state = 0},
  [666] = {.lex_state = 234},
  [667] = {.lex_state = 234},
  [668] = {.lex_state = 0},
  [669] = {.lex_state = 0},
  [670] = {.lex_state = 0},
  [671] = {.lex_state = 0},
  [672] = {.lex_state = 0},
  [673] = {.lex_state = 0},
  [674] = {.lex_state = 27},
  [675] = {.lex_state = 2},
  [676] = {.lex_state = 2},
  [677] = {.lex_state = 27},
  [678] = {.lex_state = 0},
  [679] = {.lex_state = 0},
  [680] = {.lex_state = 0},
  [681] = {.lex_state = 2},
  [682] = {.lex_state = 2},
  [683] = {.lex_state = 2},
  [684] = {.lex_state = 2},
  [685] = {.lex_state = 0},
  [686] = {.lex_state = 0},
  [687] = {.lex_state = 0},
  [688] = {.lex_state = 2},
  [689] = {.lex_state = 0},
  [690] = {.lex_state = 2},
  [691] = {.lex_state = 0},
  [692] = {.lex_state = 0},
  [693] = {.lex_state = 0},
  [694] = {.lex_state = 0},
  [695] = {.lex_state = 234},
  [696] = {.lex_state = 2},
  [697] = {.lex_state = 234},
  [698] = {.lex_state = 2},
  [699] = {.lex_state = 2},
  [700] = {.lex_state = 234},
  [701] = {.lex_state = 234},
  [702] = {.lex_state = 234},
  [703] = {.lex_state = 8},
  [704] = {.lex_state = 234},
  [705] = {.lex_state = 234},
  [706] = {.lex_state = 8},
  [707] = {.lex_state = 234},
  [708] = {.lex_state = 234},
  [709] = {.lex_state = 0},
  [710] = {.lex_state = 8},
  [711] = {.lex_state = 0},
  [712] = {.lex_state = 234},
  [713] = {.lex_state = 0},
  [714] = {.lex_state = 234},
  [715] = {.lex_state = 8},
  [716] = {.lex_state = 8},
  [717] = {.lex_state = 234},
  [718] = {.lex_state = 0},
  [719] = {.lex_state = 8},
  [720] = {.lex_state = 0},
  [721] = {.lex_state = 0},
  [722] = {.lex_state = 0},
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
    [aux_sym_ident_token1] = ACTIONS(1),
  },
  [1] = {
    [sym_start] = STATE(722),
    [sym__query] = STATE(721),
    [sym_array_query] = STATE(721),
    [sym_element_query] = STATE(721),
    [sym__missing_query] = STATE(720),
    [sym_missing_query_start] = STATE(45),
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(221), 2,
      sym_path,
      sym_string,
    STATE(671), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(213), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(510), 8,
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(221), 2,
      sym_path,
      sym_string,
    STATE(671), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(213), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(511), 8,
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(221), 2,
      sym_path,
      sym_string,
    STATE(671), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(213), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(518), 8,
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(221), 2,
      sym_path,
      sym_string,
    STATE(671), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(213), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(512), 8,
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(221), 2,
      sym_path,
      sym_string,
    STATE(662), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(212), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(512), 8,
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(221), 2,
      sym_path,
      sym_string,
    STATE(670), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(210), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(511), 8,
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(221), 2,
      sym_path,
      sym_string,
    STATE(689), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(19), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(211), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(510), 8,
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
    STATE(34), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(125), 1,
      sym_missing_identifier,
    STATE(142), 1,
      sym_missing_string_end,
    STATE(458), 1,
      sym_missing_expression,
    STATE(150), 2,
      sym_path,
      sym_string,
    STATE(180), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(47), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(156), 4,
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
  [724] = 21,
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
    STATE(40), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(133), 1,
      sym_missing_identifier,
    STATE(147), 1,
      sym_missing_string_end,
    STATE(492), 1,
      sym_missing_expression,
    STATE(137), 2,
      sym_path,
      sym_string,
    STATE(196), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(71), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(154), 4,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(228), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [804] = 21,
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
    STATE(34), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(125), 1,
      sym_missing_identifier,
    STATE(142), 1,
      sym_missing_string_end,
    STATE(478), 1,
      sym_missing_expression,
    STATE(150), 2,
      sym_path,
      sym_string,
    STATE(158), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(47), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(155), 4,
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
    STATE(40), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(133), 1,
      sym_missing_identifier,
    STATE(147), 1,
      sym_missing_string_end,
    STATE(473), 1,
      sym_missing_expression,
    STATE(137), 2,
      sym_path,
      sym_string,
    STATE(194), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(71), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(157), 4,
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
    STATE(29), 1,
      sym__not,
    STATE(58), 1,
      sym_ident,
    STATE(62), 1,
      sym_missing_identifier,
    STATE(69), 1,
      sym_missing_string_end,
    STATE(313), 1,
      sym_missing_expression,
    STATE(77), 2,
      sym_path,
      sym_string,
    STATE(119), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(95), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(109), 4,
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
    ACTIONS(109), 1,
      anon_sym_LPAREN,
    ACTIONS(113), 1,
      anon_sym_ERROR_missing_filter_expression,
    STATE(40), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(133), 1,
      sym_missing_identifier,
    STATE(147), 1,
      sym_missing_string_end,
    STATE(451), 1,
      sym_missing_filter_expression,
    STATE(144), 2,
      sym_path,
      sym_string,
    ACTIONS(111), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(407), 7,
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
  [1122] = 21,
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
    STATE(29), 1,
      sym__not,
    STATE(58), 1,
      sym_ident,
    STATE(62), 1,
      sym_missing_identifier,
    STATE(69), 1,
      sym_missing_string_end,
    STATE(308), 1,
      sym_missing_expression,
    STATE(77), 2,
      sym_path,
      sym_string,
    STATE(118), 3,
      sym__query,
      sym_array_query,
      sym_element_query,
    ACTIONS(95), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(81), 4,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(217), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1202] = 20,
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
    STATE(29), 1,
      sym__not,
    STATE(58), 1,
      sym_ident,
    STATE(62), 1,
      sym_missing_identifier,
    STATE(69), 1,
      sym_missing_string_end,
    STATE(312), 1,
      sym_missing_filter_expression,
    STATE(71), 2,
      sym_path,
      sym_string,
    ACTIONS(117), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(349), 7,
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
  [1280] = 20,
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
    ACTIONS(121), 1,
      anon_sym_LPAREN,
    ACTIONS(125), 1,
      anon_sym_ERROR_missing_filter_expression,
    STATE(34), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(125), 1,
      sym_missing_identifier,
    STATE(142), 1,
      sym_missing_string_end,
    STATE(428), 1,
      sym_missing_filter_expression,
    STATE(149), 2,
      sym_path,
      sym_string,
    ACTIONS(123), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(411), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(232), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1358] = 18,
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
    STATE(29), 1,
      sym__not,
    STATE(58), 1,
      sym_ident,
    STATE(62), 1,
      sym_missing_identifier,
    STATE(69), 1,
      sym_missing_string_end,
    STATE(71), 2,
      sym_path,
      sym_string,
    ACTIONS(117), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(349), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(215), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1430] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(422), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(668), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(131), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(500), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [1510] = 18,
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
    ACTIONS(121), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(125), 1,
      sym_missing_identifier,
    STATE(142), 1,
      sym_missing_string_end,
    STATE(149), 2,
      sym_path,
      sym_string,
    ACTIONS(123), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(411), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(243), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1582] = 18,
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
    ACTIONS(121), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(125), 1,
      sym_missing_identifier,
    STATE(142), 1,
      sym_missing_string_end,
    STATE(149), 2,
      sym_path,
      sym_string,
    ACTIONS(123), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(411), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(245), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1654] = 18,
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
    ACTIONS(109), 1,
      anon_sym_LPAREN,
    STATE(40), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(133), 1,
      sym_missing_identifier,
    STATE(147), 1,
      sym_missing_string_end,
    STATE(144), 2,
      sym_path,
      sym_string,
    ACTIONS(111), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(407), 7,
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
  [1726] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(167), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(694), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(141), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(501), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [1806] = 18,
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(273), 2,
      sym_path,
      sym_string,
    ACTIONS(145), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(352), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(525), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [1878] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(114), 1,
      sym_missing_array_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(663), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(149), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(509), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [1958] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(371), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(659), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(155), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(506), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2038] = 18,
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
    STATE(29), 1,
      sym__not,
    STATE(58), 1,
      sym_ident,
    STATE(62), 1,
      sym_missing_identifier,
    STATE(69), 1,
      sym_missing_string_end,
    STATE(71), 2,
      sym_path,
      sym_string,
    ACTIONS(117), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(349), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(214), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2110] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(203), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(678), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(161), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(507), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2190] = 18,
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
    STATE(29), 1,
      sym__not,
    STATE(58), 1,
      sym_ident,
    STATE(62), 1,
      sym_missing_identifier,
    STATE(69), 1,
      sym_missing_string_end,
    STATE(71), 2,
      sym_path,
      sym_string,
    ACTIONS(117), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(349), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(219), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2262] = 18,
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
    ACTIONS(109), 1,
      anon_sym_LPAREN,
    STATE(40), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(133), 1,
      sym_missing_identifier,
    STATE(147), 1,
      sym_missing_string_end,
    STATE(144), 2,
      sym_path,
      sym_string,
    ACTIONS(111), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(407), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(236), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2334] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(173), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(691), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(167), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(503), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(548), 1,
      sym__for,
    STATE(640), 1,
      sym_missing_array_end,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(664), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(173), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(505), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2494] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(325), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(692), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(179), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(502), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2574] = 18,
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
    ACTIONS(121), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym__not,
    STATE(88), 1,
      sym_ident,
    STATE(125), 1,
      sym_missing_identifier,
    STATE(142), 1,
      sym_missing_string_end,
    STATE(149), 2,
      sym_path,
      sym_string,
    ACTIONS(123), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(411), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(230), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2646] = 18,
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(273), 2,
      sym_path,
      sym_string,
    ACTIONS(145), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(352), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(533), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [2718] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(246), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(686), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(185), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(508), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2798] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(462), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(679), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(191), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(499), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [2878] = 18,
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
    STATE(38), 1,
      sym__not,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(273), 2,
      sym_path,
      sym_string,
    ACTIONS(145), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(352), 7,
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
  [2950] = 22,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(363), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(672), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(197), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(504), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3030] = 18,
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
    ACTIONS(109), 1,
      anon_sym_LPAREN,
    STATE(40), 1,
      sym__not,
    STATE(84), 1,
      sym_ident,
    STATE(133), 1,
      sym_missing_identifier,
    STATE(147), 1,
      sym_missing_string_end,
    STATE(144), 2,
      sym_path,
      sym_string,
    ACTIONS(111), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(407), 7,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_object,
      sym_array,
    STATE(229), 8,
      sym__bool_expression,
      sym_comparison,
      sym_not_expression,
      sym_and_expression,
      sym_or_expression,
      sym__bool_value,
      sym__parenthesized_bool_expression,
      sym_missing_bool_value,
  [3102] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(687), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(201), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(531), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3173] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(671), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(203), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(532), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3244] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(660), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(205), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(534), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3315] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(671), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(207), 4,
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
  [3386] = 19,
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
    ACTIONS(211), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(213), 1,
      anon_sym_for,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(553), 1,
      sym__for,
    STATE(53), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(545), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(209), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(579), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3457] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(665), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(215), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(535), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3528] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(693), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(217), 4,
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
  [3599] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(548), 1,
      sym__for,
    STATE(76), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(678), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(219), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(593), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3670] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(669), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(221), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(528), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3741] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(673), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(223), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(529), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3812] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(671), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(225), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(591), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3883] = 19,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(562), 1,
      sym__for,
    STATE(75), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    STATE(680), 2,
      sym__query_body,
      sym_missing_query_body,
    ACTIONS(227), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(536), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [3954] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(213), 1,
      anon_sym_for,
    ACTIONS(231), 1,
      anon_sym_let,
    ACTIONS(233), 1,
      anon_sym_if,
    ACTIONS(235), 1,
      anon_sym_set,
    ACTIONS(237), 1,
      anon_sym_delete,
    ACTIONS(239), 1,
      anon_sym_offset,
    ACTIONS(241), 1,
      anon_sym_limit,
    STATE(16), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(540), 1,
      sym__delete,
    STATE(541), 1,
      sym__set,
    STATE(553), 1,
      sym__for,
    STATE(636), 1,
      sym__let,
    STATE(681), 1,
      sym__limit,
    STATE(682), 1,
      sym__offset,
    STATE(716), 1,
      sym_ident,
    ACTIONS(229), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(56), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4026] = 20,
    ACTIONS(245), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(248), 1,
      anon_sym_for,
    ACTIONS(251), 1,
      anon_sym_let,
    ACTIONS(254), 1,
      anon_sym_if,
    ACTIONS(257), 1,
      anon_sym_set,
    ACTIONS(260), 1,
      anon_sym_delete,
    ACTIONS(263), 1,
      anon_sym_offset,
    ACTIONS(266), 1,
      anon_sym_limit,
    ACTIONS(269), 1,
      aux_sym_ident_token1,
    STATE(16), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(540), 1,
      sym__delete,
    STATE(541), 1,
      sym__set,
    STATE(553), 1,
      sym__for,
    STATE(636), 1,
      sym__let,
    STATE(681), 1,
      sym__limit,
    STATE(682), 1,
      sym__offset,
    STATE(716), 1,
      sym_ident,
    ACTIONS(243), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(54), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4098] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(213), 1,
      anon_sym_for,
    ACTIONS(231), 1,
      anon_sym_let,
    ACTIONS(233), 1,
      anon_sym_if,
    ACTIONS(235), 1,
      anon_sym_set,
    ACTIONS(237), 1,
      anon_sym_delete,
    ACTIONS(239), 1,
      anon_sym_offset,
    ACTIONS(241), 1,
      anon_sym_limit,
    STATE(16), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(540), 1,
      sym__delete,
    STATE(541), 1,
      sym__set,
    STATE(553), 1,
      sym__for,
    STATE(636), 1,
      sym__let,
    STATE(681), 1,
      sym__limit,
    STATE(682), 1,
      sym__offset,
    STATE(716), 1,
      sym_ident,
    ACTIONS(272), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(57), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4170] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(213), 1,
      anon_sym_for,
    ACTIONS(231), 1,
      anon_sym_let,
    ACTIONS(233), 1,
      anon_sym_if,
    ACTIONS(235), 1,
      anon_sym_set,
    ACTIONS(237), 1,
      anon_sym_delete,
    ACTIONS(239), 1,
      anon_sym_offset,
    ACTIONS(241), 1,
      anon_sym_limit,
    STATE(16), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(540), 1,
      sym__delete,
    STATE(541), 1,
      sym__set,
    STATE(553), 1,
      sym__for,
    STATE(636), 1,
      sym__let,
    STATE(681), 1,
      sym__limit,
    STATE(682), 1,
      sym__offset,
    STATE(716), 1,
      sym_ident,
    ACTIONS(274), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(54), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4242] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(213), 1,
      anon_sym_for,
    ACTIONS(231), 1,
      anon_sym_let,
    ACTIONS(233), 1,
      anon_sym_if,
    ACTIONS(235), 1,
      anon_sym_set,
    ACTIONS(237), 1,
      anon_sym_delete,
    ACTIONS(239), 1,
      anon_sym_offset,
    ACTIONS(241), 1,
      anon_sym_limit,
    STATE(16), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(540), 1,
      sym__delete,
    STATE(541), 1,
      sym__set,
    STATE(553), 1,
      sym__for,
    STATE(636), 1,
      sym__let,
    STATE(681), 1,
      sym__limit,
    STATE(682), 1,
      sym__offset,
    STATE(716), 1,
      sym_ident,
    ACTIONS(276), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
    STATE(54), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4314] = 4,
    ACTIONS(282), 1,
      anon_sym_DOT,
    STATE(60), 1,
      aux_sym_path_repeat1,
    ACTIONS(280), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(278), 25,
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
  [4353] = 4,
    ACTIONS(288), 1,
      anon_sym_DOT,
    STATE(59), 1,
      aux_sym_path_repeat1,
    ACTIONS(286), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(284), 25,
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
  [4392] = 4,
    ACTIONS(282), 1,
      anon_sym_DOT,
    STATE(59), 1,
      aux_sym_path_repeat1,
    ACTIONS(293), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(291), 25,
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
  [4431] = 2,
    ACTIONS(297), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(295), 26,
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
  [4465] = 2,
    ACTIONS(301), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(299), 26,
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
  [4499] = 2,
    ACTIONS(286), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(284), 26,
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
  [4533] = 20,
    ACTIONS(245), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(269), 1,
      aux_sym_ident_token1,
    ACTIONS(303), 1,
      anon_sym_for,
    ACTIONS(306), 1,
      anon_sym_let,
    ACTIONS(309), 1,
      anon_sym_if,
    ACTIONS(312), 1,
      anon_sym_set,
    ACTIONS(315), 1,
      anon_sym_delete,
    ACTIONS(318), 1,
      anon_sym_offset,
    ACTIONS(321), 1,
      anon_sym_limit,
    STATE(14), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(543), 1,
      sym__delete,
    STATE(544), 1,
      sym__set,
    STATE(562), 1,
      sym__for,
    STATE(643), 1,
      sym__let,
    STATE(684), 1,
      sym__limit,
    STATE(688), 1,
      sym__offset,
    STATE(710), 1,
      sym_ident,
    ACTIONS(243), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(64), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4602] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(324), 1,
      anon_sym_let,
    ACTIONS(326), 1,
      anon_sym_if,
    ACTIONS(328), 1,
      anon_sym_set,
    ACTIONS(330), 1,
      anon_sym_delete,
    ACTIONS(332), 1,
      anon_sym_offset,
    ACTIONS(334), 1,
      anon_sym_limit,
    STATE(14), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(543), 1,
      sym__delete,
    STATE(544), 1,
      sym__set,
    STATE(562), 1,
      sym__for,
    STATE(643), 1,
      sym__let,
    STATE(684), 1,
      sym__limit,
    STATE(688), 1,
      sym__offset,
    STATE(710), 1,
      sym_ident,
    ACTIONS(276), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(64), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4671] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(324), 1,
      anon_sym_let,
    ACTIONS(326), 1,
      anon_sym_if,
    ACTIONS(328), 1,
      anon_sym_set,
    ACTIONS(330), 1,
      anon_sym_delete,
    ACTIONS(332), 1,
      anon_sym_offset,
    ACTIONS(334), 1,
      anon_sym_limit,
    STATE(14), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(543), 1,
      sym__delete,
    STATE(544), 1,
      sym__set,
    STATE(562), 1,
      sym__for,
    STATE(643), 1,
      sym__let,
    STATE(684), 1,
      sym__limit,
    STATE(688), 1,
      sym__offset,
    STATE(710), 1,
      sym_ident,
    ACTIONS(272), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(65), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4740] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(336), 1,
      anon_sym_let,
    ACTIONS(338), 1,
      anon_sym_if,
    ACTIONS(340), 1,
      anon_sym_set,
    ACTIONS(342), 1,
      anon_sym_delete,
    ACTIONS(344), 1,
      anon_sym_offset,
    ACTIONS(346), 1,
      anon_sym_limit,
    STATE(17), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(538), 1,
      sym__delete,
    STATE(546), 1,
      sym__set,
    STATE(548), 1,
      sym__for,
    STATE(638), 1,
      sym__let,
    STATE(661), 1,
      sym__limit,
    STATE(676), 1,
      sym__offset,
    STATE(703), 1,
      sym_ident,
    ACTIONS(274), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(68), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4809] = 20,
    ACTIONS(245), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(269), 1,
      aux_sym_ident_token1,
    ACTIONS(348), 1,
      anon_sym_for,
    ACTIONS(351), 1,
      anon_sym_let,
    ACTIONS(354), 1,
      anon_sym_if,
    ACTIONS(357), 1,
      anon_sym_set,
    ACTIONS(360), 1,
      anon_sym_delete,
    ACTIONS(363), 1,
      anon_sym_offset,
    ACTIONS(366), 1,
      anon_sym_limit,
    STATE(17), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(538), 1,
      sym__delete,
    STATE(546), 1,
      sym__set,
    STATE(548), 1,
      sym__for,
    STATE(638), 1,
      sym__let,
    STATE(661), 1,
      sym__limit,
    STATE(676), 1,
      sym__offset,
    STATE(703), 1,
      sym_ident,
    ACTIONS(243), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(68), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4878] = 2,
    ACTIONS(371), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(369), 25,
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
  [4911] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(336), 1,
      anon_sym_let,
    ACTIONS(338), 1,
      anon_sym_if,
    ACTIONS(340), 1,
      anon_sym_set,
    ACTIONS(342), 1,
      anon_sym_delete,
    ACTIONS(344), 1,
      anon_sym_offset,
    ACTIONS(346), 1,
      anon_sym_limit,
    STATE(17), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(538), 1,
      sym__delete,
    STATE(546), 1,
      sym__set,
    STATE(548), 1,
      sym__for,
    STATE(638), 1,
      sym__let,
    STATE(661), 1,
      sym__limit,
    STATE(676), 1,
      sym__offset,
    STATE(703), 1,
      sym_ident,
    ACTIONS(276), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(68), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [4980] = 4,
    ACTIONS(379), 1,
      aux_sym_ident_token1,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(373), 15,
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
  [5017] = 2,
    ACTIONS(383), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(381), 25,
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
  [5050] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(336), 1,
      anon_sym_let,
    ACTIONS(338), 1,
      anon_sym_if,
    ACTIONS(340), 1,
      anon_sym_set,
    ACTIONS(342), 1,
      anon_sym_delete,
    ACTIONS(344), 1,
      anon_sym_offset,
    ACTIONS(346), 1,
      anon_sym_limit,
    STATE(17), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(538), 1,
      sym__delete,
    STATE(546), 1,
      sym__set,
    STATE(548), 1,
      sym__for,
    STATE(638), 1,
      sym__let,
    STATE(661), 1,
      sym__limit,
    STATE(676), 1,
      sym__offset,
    STATE(703), 1,
      sym_ident,
    ACTIONS(272), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(70), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [5119] = 2,
    ACTIONS(387), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(385), 25,
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
  [5152] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(324), 1,
      anon_sym_let,
    ACTIONS(326), 1,
      anon_sym_if,
    ACTIONS(328), 1,
      anon_sym_set,
    ACTIONS(330), 1,
      anon_sym_delete,
    ACTIONS(332), 1,
      anon_sym_offset,
    ACTIONS(334), 1,
      anon_sym_limit,
    STATE(14), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(543), 1,
      sym__delete,
    STATE(544), 1,
      sym__set,
    STATE(562), 1,
      sym__for,
    STATE(643), 1,
      sym__let,
    STATE(684), 1,
      sym__limit,
    STATE(688), 1,
      sym__offset,
    STATE(710), 1,
      sym_ident,
    ACTIONS(229), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(79), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [5221] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(336), 1,
      anon_sym_let,
    ACTIONS(338), 1,
      anon_sym_if,
    ACTIONS(340), 1,
      anon_sym_set,
    ACTIONS(342), 1,
      anon_sym_delete,
    ACTIONS(344), 1,
      anon_sym_offset,
    ACTIONS(346), 1,
      anon_sym_limit,
    STATE(17), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(538), 1,
      sym__delete,
    STATE(546), 1,
      sym__set,
    STATE(548), 1,
      sym__for,
    STATE(638), 1,
      sym__let,
    STATE(661), 1,
      sym__limit,
    STATE(676), 1,
      sym__offset,
    STATE(703), 1,
      sym_ident,
    ACTIONS(229), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_query_end,
    STATE(67), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [5290] = 5,
    ACTIONS(392), 1,
      aux_sym_ident_token1,
    ACTIONS(373), 2,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(389), 13,
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
  [5329] = 2,
    ACTIONS(397), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(395), 25,
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
  [5362] = 20,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(324), 1,
      anon_sym_let,
    ACTIONS(326), 1,
      anon_sym_if,
    ACTIONS(328), 1,
      anon_sym_set,
    ACTIONS(330), 1,
      anon_sym_delete,
    ACTIONS(332), 1,
      anon_sym_offset,
    ACTIONS(334), 1,
      anon_sym_limit,
    STATE(14), 1,
      sym__if,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(543), 1,
      sym__delete,
    STATE(544), 1,
      sym__set,
    STATE(562), 1,
      sym__for,
    STATE(643), 1,
      sym__let,
    STATE(684), 1,
      sym__limit,
    STATE(688), 1,
      sym__offset,
    STATE(710), 1,
      sym_ident,
    ACTIONS(274), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_element_query_end,
    STATE(64), 8,
      sym_iterator_stmt,
      sym_assignment,
      sym_update_stmt,
      sym_delete_stmt,
      sym_filter_stmt,
      sym_offset_stmt,
      sym_limit_stmt,
      aux_sym__query_body_repeat1,
  [5431] = 4,
    ACTIONS(399), 1,
      anon_sym_DOT,
    STATE(98), 1,
      aux_sym_path_repeat1,
    ACTIONS(293), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(291), 22,
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
  [5467] = 7,
    ACTIONS(407), 1,
      anon_sym_between,
    ACTIONS(409), 1,
      anon_sym_exists,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    STATE(261), 1,
      sym_comparator,
    ACTIONS(405), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(403), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(401), 13,
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
  [5509] = 4,
    ACTIONS(413), 1,
      anon_sym_DOT,
    STATE(93), 1,
      aux_sym_path_repeat1,
    ACTIONS(293), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(291), 22,
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
  [5545] = 14,
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
    ACTIONS(415), 1,
      anon_sym_LBRACK,
    ACTIONS(417), 1,
      anon_sym_LPAREN,
    ACTIONS(419), 1,
      anon_sym_LBRACE,
    ACTIONS(423), 1,
      anon_sym_ERROR_missing_expression,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    ACTIONS(421), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(641), 11,
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
  [5601] = 4,
    ACTIONS(425), 1,
      anon_sym_DOT,
    STATE(91), 1,
      aux_sym_path_repeat1,
    ACTIONS(280), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(278), 22,
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
  [5637] = 2,
    ACTIONS(301), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(299), 24,
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
  [5669] = 14,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(427), 1,
      anon_sym_LPAREN,
    ACTIONS(429), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(431), 1,
      anon_sym_DQUOTE,
    ACTIONS(435), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(437), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(439), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(441), 1,
      aux_sym_ident_token1,
    STATE(667), 1,
      sym_ident,
    STATE(695), 1,
      sym_missing_identifier,
    STATE(705), 1,
      sym_missing_string_end,
    ACTIONS(433), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(701), 11,
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
  [5725] = 14,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(427), 1,
      anon_sym_LPAREN,
    ACTIONS(429), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(431), 1,
      anon_sym_DQUOTE,
    ACTIONS(435), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(437), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(439), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(441), 1,
      aux_sym_ident_token1,
    STATE(667), 1,
      sym_ident,
    STATE(695), 1,
      sym_missing_identifier,
    STATE(705), 1,
      sym_missing_string_end,
    ACTIONS(443), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(702), 11,
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
  [5781] = 4,
    ACTIONS(413), 1,
      anon_sym_DOT,
    STATE(82), 1,
      aux_sym_path_repeat1,
    ACTIONS(280), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(278), 22,
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
  [5817] = 2,
    ACTIONS(297), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(295), 24,
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
  [5849] = 4,
    ACTIONS(399), 1,
      anon_sym_DOT,
    STATE(80), 1,
      aux_sym_path_repeat1,
    ACTIONS(280), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(278), 22,
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
  [5885] = 4,
    ACTIONS(425), 1,
      anon_sym_DOT,
    STATE(96), 1,
      aux_sym_path_repeat1,
    ACTIONS(293), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(291), 22,
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
  [5921] = 14,
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
    ACTIONS(435), 1,
      anon_sym_ERROR_missing_expression,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    ACTIONS(445), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(675), 11,
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
  [5977] = 4,
    ACTIONS(447), 1,
      anon_sym_DOT,
    STATE(93), 1,
      aux_sym_path_repeat1,
    ACTIONS(286), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(284), 22,
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
  [6013] = 14,
    ACTIONS(450), 1,
      anon_sym_LBRACK,
    ACTIONS(452), 1,
      anon_sym_LPAREN,
    ACTIONS(454), 1,
      anon_sym_LBRACE,
    ACTIONS(456), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(458), 1,
      anon_sym_DQUOTE,
    ACTIONS(462), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(464), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(466), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(468), 1,
      aux_sym_ident_token1,
    STATE(290), 1,
      sym_ident,
    STATE(298), 1,
      sym_missing_identifier,
    STATE(408), 1,
      sym_missing_string_end,
    ACTIONS(460), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(356), 11,
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
  [6069] = 14,
    ACTIONS(470), 1,
      anon_sym_LBRACK,
    ACTIONS(472), 1,
      anon_sym_LPAREN,
    ACTIONS(474), 1,
      anon_sym_LBRACE,
    ACTIONS(476), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(478), 1,
      anon_sym_DQUOTE,
    ACTIONS(482), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(484), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(486), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(488), 1,
      aux_sym_ident_token1,
    STATE(278), 1,
      sym_ident,
    STATE(305), 1,
      sym_missing_identifier,
    STATE(374), 1,
      sym_missing_string_end,
    ACTIONS(480), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(391), 11,
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
  [6125] = 4,
    ACTIONS(490), 1,
      anon_sym_DOT,
    STATE(96), 1,
      aux_sym_path_repeat1,
    ACTIONS(286), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(284), 22,
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
  [6161] = 16,
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
    ACTIONS(127), 1,
      anon_sym_RBRACK,
    ACTIONS(129), 1,
      anon_sym_LPAREN,
    ACTIONS(135), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(422), 1,
      sym_missing_array_end,
    ACTIONS(493), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(587), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [6221] = 4,
    ACTIONS(495), 1,
      anon_sym_DOT,
    STATE(98), 1,
      aux_sym_path_repeat1,
    ACTIONS(286), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(284), 22,
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
  [6257] = 14,
    ACTIONS(73), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(498), 1,
      anon_sym_LBRACK,
    ACTIONS(500), 1,
      anon_sym_LPAREN,
    ACTIONS(502), 1,
      anon_sym_LBRACE,
    ACTIONS(504), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(506), 1,
      anon_sym_DQUOTE,
    ACTIONS(510), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(512), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(514), 1,
      aux_sym_ident_token1,
    STATE(343), 1,
      sym_ident,
    STATE(377), 1,
      sym_missing_identifier,
    STATE(475), 1,
      sym_missing_string_end,
    ACTIONS(508), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(464), 11,
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
  [6313] = 14,
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
    ACTIONS(415), 1,
      anon_sym_LBRACK,
    ACTIONS(417), 1,
      anon_sym_LPAREN,
    ACTIONS(419), 1,
      anon_sym_LBRACE,
    ACTIONS(423), 1,
      anon_sym_ERROR_missing_expression,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    ACTIONS(516), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(644), 11,
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
  [6369] = 16,
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
    ACTIONS(177), 1,
      anon_sym_RBRACK,
    ACTIONS(181), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(325), 1,
      sym_missing_array_end,
    ACTIONS(518), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(590), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [6429] = 14,
    ACTIONS(470), 1,
      anon_sym_LBRACK,
    ACTIONS(472), 1,
      anon_sym_LPAREN,
    ACTIONS(474), 1,
      anon_sym_LBRACE,
    ACTIONS(476), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(478), 1,
      anon_sym_DQUOTE,
    ACTIONS(482), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(484), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(486), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(488), 1,
      aux_sym_ident_token1,
    STATE(278), 1,
      sym_ident,
    STATE(305), 1,
      sym_missing_identifier,
    STATE(374), 1,
      sym_missing_string_end,
    ACTIONS(520), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(351), 11,
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
  [6485] = 14,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(427), 1,
      anon_sym_LPAREN,
    ACTIONS(429), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(431), 1,
      anon_sym_DQUOTE,
    ACTIONS(435), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(437), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(439), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(441), 1,
      aux_sym_ident_token1,
    STATE(667), 1,
      sym_ident,
    STATE(695), 1,
      sym_missing_identifier,
    STATE(705), 1,
      sym_missing_string_end,
    ACTIONS(522), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(714), 11,
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
  [6541] = 14,
    ACTIONS(9), 1,
      anon_sym_LBRACK,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(427), 1,
      anon_sym_LPAREN,
    ACTIONS(429), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(431), 1,
      anon_sym_DQUOTE,
    ACTIONS(435), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(437), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(439), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(441), 1,
      aux_sym_ident_token1,
    STATE(667), 1,
      sym_ident,
    STATE(695), 1,
      sym_missing_identifier,
    STATE(705), 1,
      sym_missing_string_end,
    ACTIONS(524), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(717), 11,
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
  [6597] = 16,
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
    ACTIONS(189), 1,
      anon_sym_RBRACK,
    ACTIONS(193), 1,
      anon_sym_ERROR_missing_array_end,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(462), 1,
      sym_missing_array_end,
    ACTIONS(526), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(606), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [6657] = 14,
    ACTIONS(450), 1,
      anon_sym_LBRACK,
    ACTIONS(452), 1,
      anon_sym_LPAREN,
    ACTIONS(454), 1,
      anon_sym_LBRACE,
    ACTIONS(456), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(458), 1,
      anon_sym_DQUOTE,
    ACTIONS(462), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(464), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(466), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(468), 1,
      aux_sym_ident_token1,
    STATE(290), 1,
      sym_ident,
    STATE(298), 1,
      sym_missing_identifier,
    STATE(408), 1,
      sym_missing_string_end,
    ACTIONS(528), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(353), 11,
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
  [6713] = 14,
    ACTIONS(530), 1,
      anon_sym_LBRACK,
    ACTIONS(532), 1,
      anon_sym_LPAREN,
    ACTIONS(534), 1,
      anon_sym_LBRACE,
    ACTIONS(536), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(538), 1,
      anon_sym_DQUOTE,
    ACTIONS(542), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(544), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(546), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(548), 1,
      aux_sym_ident_token1,
    STATE(227), 1,
      sym_ident,
    STATE(240), 1,
      sym_missing_identifier,
    STATE(247), 1,
      sym_missing_string_end,
    ACTIONS(540), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(253), 11,
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
  [6769] = 14,
    ACTIONS(49), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(550), 1,
      anon_sym_LBRACK,
    ACTIONS(552), 1,
      anon_sym_LPAREN,
    ACTIONS(554), 1,
      anon_sym_LBRACE,
    ACTIONS(556), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(558), 1,
      anon_sym_DQUOTE,
    ACTIONS(562), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(564), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(566), 1,
      aux_sym_ident_token1,
    STATE(329), 1,
      sym_ident,
    STATE(412), 1,
      sym_missing_identifier,
    STATE(441), 1,
      sym_missing_string_end,
    ACTIONS(560), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(442), 11,
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
  [6825] = 7,
    ACTIONS(407), 1,
      anon_sym_between,
    ACTIONS(409), 1,
      anon_sym_exists,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    STATE(261), 1,
      sym_comparator,
    ACTIONS(405), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(403), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(568), 13,
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
  [6867] = 14,
    ACTIONS(530), 1,
      anon_sym_LBRACK,
    ACTIONS(532), 1,
      anon_sym_LPAREN,
    ACTIONS(534), 1,
      anon_sym_LBRACE,
    ACTIONS(536), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(538), 1,
      anon_sym_DQUOTE,
    ACTIONS(542), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(544), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(546), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(548), 1,
      aux_sym_ident_token1,
    STATE(227), 1,
      sym_ident,
    STATE(240), 1,
      sym_missing_identifier,
    STATE(247), 1,
      sym_missing_string_end,
    ACTIONS(572), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(255), 11,
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
  [6923] = 14,
    ACTIONS(97), 1,
      anon_sym_ERROR_missing_expression,
    ACTIONS(574), 1,
      anon_sym_LBRACK,
    ACTIONS(576), 1,
      anon_sym_LPAREN,
    ACTIONS(578), 1,
      anon_sym_LBRACE,
    ACTIONS(580), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(582), 1,
      anon_sym_DQUOTE,
    ACTIONS(586), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(588), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(590), 1,
      aux_sym_ident_token1,
    STATE(234), 1,
      sym_ident,
    STATE(252), 1,
      sym_missing_identifier,
    STATE(326), 1,
      sym_missing_string_end,
    ACTIONS(584), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(294), 11,
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
  [6979] = 2,
    ACTIONS(594), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(592), 23,
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
  [7010] = 2,
    ACTIONS(598), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(596), 23,
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
  [7041] = 2,
    ACTIONS(602), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(600), 23,
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
  [7072] = 2,
    ACTIONS(606), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(604), 23,
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
  [7103] = 2,
    ACTIONS(610), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(608), 23,
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
  [7134] = 2,
    ACTIONS(286), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(284), 23,
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
  [7165] = 4,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(401), 13,
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
  [7200] = 4,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(568), 13,
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
  [7235] = 2,
    ACTIONS(614), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(612), 23,
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
  [7266] = 2,
    ACTIONS(618), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(616), 23,
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
  [7297] = 2,
    ACTIONS(622), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(620), 23,
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
  [7328] = 2,
    ACTIONS(626), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(624), 23,
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
  [7359] = 2,
    ACTIONS(297), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(295), 23,
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
  [7390] = 2,
    ACTIONS(301), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(299), 23,
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
  [7421] = 2,
    ACTIONS(286), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(284), 23,
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
  [7452] = 2,
    ACTIONS(286), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(284), 23,
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
  [7483] = 2,
    ACTIONS(297), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(295), 23,
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
  [7514] = 2,
    ACTIONS(622), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(620), 23,
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
  [7545] = 2,
    ACTIONS(630), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(628), 23,
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
  [7576] = 2,
    ACTIONS(634), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(632), 23,
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
  [7607] = 2,
    ACTIONS(638), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(636), 23,
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
  [7638] = 2,
    ACTIONS(301), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(299), 23,
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
  [7669] = 2,
    ACTIONS(642), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(640), 23,
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
  [7700] = 2,
    ACTIONS(638), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(636), 23,
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
  [7731] = 2,
    ACTIONS(646), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(644), 23,
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
  [7762] = 5,
    ACTIONS(392), 1,
      aux_sym_ident_token1,
    ACTIONS(373), 2,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(389), 10,
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
  [7798] = 2,
    ACTIONS(397), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(395), 22,
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
  [7828] = 2,
    ACTIONS(397), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(395), 23,
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
  [7858] = 2,
    ACTIONS(383), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(381), 22,
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
  [7888] = 2,
    ACTIONS(371), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(369), 23,
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
  [7918] = 2,
    ACTIONS(371), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(369), 22,
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
  [7948] = 2,
    ACTIONS(387), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(385), 22,
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
  [7978] = 4,
    ACTIONS(379), 1,
      aux_sym_ident_token1,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(373), 12,
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
  [8012] = 2,
    ACTIONS(383), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(381), 22,
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
  [8042] = 2,
    ACTIONS(387), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(385), 23,
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
  [8072] = 2,
    ACTIONS(371), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(369), 22,
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
  [8102] = 2,
    ACTIONS(397), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(395), 22,
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
  [8132] = 4,
    ACTIONS(379), 1,
      aux_sym_ident_token1,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(373), 12,
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
  [8166] = 5,
    ACTIONS(392), 1,
      aux_sym_ident_token1,
    ACTIONS(373), 2,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(389), 10,
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
  [8202] = 2,
    ACTIONS(383), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(381), 23,
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
  [8232] = 2,
    ACTIONS(387), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(385), 22,
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
  [8262] = 13,
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
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(141), 1,
      sym_missing_string_end,
    ACTIONS(648), 4,
      sym_number,
      sym_true,
      sym_false,
      sym_null,
    STATE(685), 9,
      sym__query,
      sym_array_query,
      sym_element_query,
      sym__expression,
      sym__parenthesized_expression,
      sym_path,
      sym_object,
      sym_array,
      sym_string,
  [8313] = 7,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(654), 1,
      anon_sym_between,
    ACTIONS(656), 1,
      anon_sym_exists,
    STATE(367), 1,
      sym_comparator,
    ACTIONS(652), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(650), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(401), 10,
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
  [8352] = 7,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(662), 1,
      anon_sym_between,
    ACTIONS(664), 1,
      anon_sym_exists,
    STATE(360), 1,
      sym_comparator,
    ACTIONS(660), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(658), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(401), 10,
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
  [8391] = 7,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(662), 1,
      anon_sym_between,
    ACTIONS(664), 1,
      anon_sym_exists,
    STATE(360), 1,
      sym_comparator,
    ACTIONS(660), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(658), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(568), 10,
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
  [8430] = 7,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(654), 1,
      anon_sym_between,
    ACTIONS(656), 1,
      anon_sym_exists,
    STATE(367), 1,
      sym_comparator,
    ACTIONS(652), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(650), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
    ACTIONS(568), 10,
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
  [8469] = 4,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(401), 10,
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
  [8501] = 2,
    ACTIONS(614), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(612), 20,
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
  [8529] = 2,
    ACTIONS(622), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(620), 20,
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
  [8557] = 2,
    ACTIONS(626), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(624), 20,
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
  [8585] = 2,
    ACTIONS(622), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(620), 20,
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
  [8613] = 2,
    ACTIONS(634), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(632), 20,
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
  [8641] = 2,
    ACTIONS(610), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(608), 20,
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
  [8669] = 2,
    ACTIONS(618), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(616), 20,
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
  [8697] = 2,
    ACTIONS(594), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(592), 20,
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
  [8725] = 2,
    ACTIONS(602), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(600), 20,
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
  [8753] = 2,
    ACTIONS(622), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(620), 20,
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
  [8781] = 2,
    ACTIONS(638), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(636), 20,
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
  [8809] = 2,
    ACTIONS(642), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(640), 20,
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
  [8837] = 2,
    ACTIONS(638), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(636), 20,
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
  [8865] = 2,
    ACTIONS(634), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(632), 20,
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
  [8893] = 2,
    ACTIONS(602), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(600), 20,
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
  [8921] = 2,
    ACTIONS(646), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(644), 20,
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
  [8949] = 2,
    ACTIONS(626), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(624), 20,
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
  [8977] = 2,
    ACTIONS(598), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(596), 20,
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
  [9005] = 2,
    ACTIONS(622), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(620), 20,
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
  [9033] = 2,
    ACTIONS(622), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(620), 21,
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
  [9061] = 2,
    ACTIONS(626), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(624), 21,
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
  [9089] = 4,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(568), 10,
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
  [9121] = 2,
    ACTIONS(630), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(628), 20,
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
  [9149] = 2,
    ACTIONS(618), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(616), 20,
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
  [9177] = 2,
    ACTIONS(638), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(636), 20,
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
  [9205] = 2,
    ACTIONS(622), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(620), 21,
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
  [9233] = 2,
    ACTIONS(642), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(640), 20,
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
  [9261] = 2,
    ACTIONS(638), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(636), 21,
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
  [9289] = 2,
    ACTIONS(638), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(636), 20,
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
  [9317] = 2,
    ACTIONS(610), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(608), 20,
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
  [9345] = 2,
    ACTIONS(646), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(644), 20,
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
  [9373] = 2,
    ACTIONS(598), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(596), 20,
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
  [9401] = 2,
    ACTIONS(642), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(640), 21,
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
  [9429] = 2,
    ACTIONS(638), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(636), 21,
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
  [9457] = 2,
    ACTIONS(606), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(604), 20,
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
  [9485] = 4,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(568), 10,
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
  [9517] = 2,
    ACTIONS(606), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(604), 21,
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
  [9545] = 4,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(375), 10,
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
    ACTIONS(401), 10,
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
  [9577] = 2,
    ACTIONS(614), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(612), 20,
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
  [9605] = 2,
    ACTIONS(594), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(592), 20,
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
  [9633] = 2,
    ACTIONS(606), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(604), 20,
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
  [9661] = 2,
    ACTIONS(630), 3,
      anon_sym_GT,
      anon_sym_LT,
      aux_sym_ident_token1,
    ACTIONS(628), 20,
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
  [9689] = 2,
    ACTIONS(646), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(644), 20,
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
  [9716] = 2,
    ACTIONS(630), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(628), 20,
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
  [9743] = 2,
    ACTIONS(602), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(600), 20,
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
  [9770] = 2,
    ACTIONS(594), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(592), 20,
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
  [9797] = 2,
    ACTIONS(610), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(608), 20,
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
  [9824] = 2,
    ACTIONS(618), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(616), 20,
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
  [9851] = 2,
    ACTIONS(614), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(612), 20,
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
  [9878] = 2,
    ACTIONS(634), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(632), 20,
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
  [9905] = 2,
    ACTIONS(598), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(596), 20,
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
  [9932] = 12,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(666), 1,
      anon_sym_RPAREN,
    ACTIONS(672), 1,
      anon_sym_between,
    ACTIONS(674), 1,
      anon_sym_exists,
    ACTIONS(676), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(174), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(618), 1,
      sym_comparator,
    ACTIONS(670), 2,
      anon_sym_GT,
      anon_sym_LT,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    ACTIONS(668), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [9978] = 12,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(672), 1,
      anon_sym_between,
    ACTIONS(674), 1,
      anon_sym_exists,
    ACTIONS(678), 1,
      anon_sym_RPAREN,
    ACTIONS(680), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(189), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(618), 1,
      sym_comparator,
    ACTIONS(670), 2,
      anon_sym_GT,
      anon_sym_LT,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    ACTIONS(668), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [10024] = 12,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(672), 1,
      anon_sym_between,
    ACTIONS(674), 1,
      anon_sym_exists,
    ACTIONS(682), 1,
      anon_sym_RPAREN,
    ACTIONS(684), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(136), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(618), 1,
      sym_comparator,
    ACTIONS(670), 2,
      anon_sym_GT,
      anon_sym_LT,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    ACTIONS(668), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [10070] = 12,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(672), 1,
      anon_sym_between,
    ACTIONS(674), 1,
      anon_sym_exists,
    ACTIONS(686), 1,
      anon_sym_RPAREN,
    ACTIONS(688), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(201), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(618), 1,
      sym_comparator,
    ACTIONS(670), 2,
      anon_sym_GT,
      anon_sym_LT,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
    ACTIONS(668), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [10116] = 8,
    ACTIONS(692), 1,
      anon_sym_and2,
    ACTIONS(694), 1,
      anon_sym_or,
    ACTIONS(696), 1,
      aux_sym_ident_token1,
    STATE(18), 1,
      sym__and,
    STATE(27), 1,
      sym__or,
    STATE(222), 1,
      aux_sym_or_expression_repeat1,
    STATE(224), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(690), 13,
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
  [10153] = 8,
    ACTIONS(692), 1,
      anon_sym_and2,
    ACTIONS(694), 1,
      anon_sym_or,
    ACTIONS(700), 1,
      aux_sym_ident_token1,
    STATE(18), 1,
      sym__and,
    STATE(27), 1,
      sym__or,
    STATE(222), 1,
      aux_sym_or_expression_repeat1,
    STATE(224), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(698), 13,
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
  [10190] = 8,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(692), 1,
      anon_sym_and2,
    ACTIONS(694), 1,
      anon_sym_or,
    STATE(18), 1,
      sym__and,
    STATE(27), 1,
      sym__or,
    STATE(222), 1,
      aux_sym_or_expression_repeat1,
    STATE(224), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(568), 13,
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
  [10227] = 8,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(692), 1,
      anon_sym_and2,
    ACTIONS(694), 1,
      anon_sym_or,
    STATE(18), 1,
      sym__and,
    STATE(27), 1,
      sym__or,
    STATE(222), 1,
      aux_sym_or_expression_repeat1,
    STATE(224), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(401), 13,
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
  [10264] = 8,
    ACTIONS(692), 1,
      anon_sym_and2,
    ACTIONS(694), 1,
      anon_sym_or,
    ACTIONS(704), 1,
      aux_sym_ident_token1,
    STATE(18), 1,
      sym__and,
    STATE(27), 1,
      sym__or,
    STATE(222), 1,
      aux_sym_or_expression_repeat1,
    STATE(224), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(702), 13,
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
  [10301] = 6,
    ACTIONS(708), 1,
      aux_sym_ident_token1,
    STATE(18), 1,
      sym__and,
    STATE(27), 1,
      sym__or,
    STATE(222), 1,
      aux_sym_or_expression_repeat1,
    STATE(224), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(706), 15,
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
  [10334] = 5,
    ACTIONS(700), 1,
      aux_sym_ident_token1,
    ACTIONS(710), 1,
      anon_sym_and2,
    STATE(18), 1,
      sym__and,
    STATE(220), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(698), 14,
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
  [10363] = 4,
    ACTIONS(373), 2,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(389), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(375), 12,
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
  [10390] = 4,
    ACTIONS(715), 1,
      aux_sym_ident_token1,
    STATE(27), 1,
      sym__or,
    STATE(226), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(713), 15,
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
  [10417] = 4,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(717), 1,
      anon_sym_DOT,
    STATE(223), 1,
      aux_sym_path_repeat1,
    ACTIONS(284), 15,
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
  [10444] = 4,
    ACTIONS(722), 1,
      aux_sym_ident_token1,
    STATE(18), 1,
      sym__and,
    STATE(220), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(720), 15,
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
  [10471] = 4,
    ACTIONS(293), 1,
      aux_sym_ident_token1,
    ACTIONS(724), 1,
      anon_sym_DOT,
    STATE(223), 1,
      aux_sym_path_repeat1,
    ACTIONS(291), 15,
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
  [10498] = 5,
    ACTIONS(696), 1,
      aux_sym_ident_token1,
    ACTIONS(726), 1,
      anon_sym_or,
    STATE(27), 1,
      sym__or,
    STATE(226), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(690), 14,
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
  [10527] = 4,
    ACTIONS(280), 1,
      aux_sym_ident_token1,
    ACTIONS(724), 1,
      anon_sym_DOT,
    STATE(225), 1,
      aux_sym_path_repeat1,
    ACTIONS(278), 15,
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
  [10554] = 8,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(729), 1,
      anon_sym_and2,
    ACTIONS(731), 1,
      anon_sym_or,
    STATE(22), 1,
      sym__or,
    STATE(30), 1,
      sym__and,
    STATE(277), 1,
      aux_sym_or_expression_repeat1,
    STATE(291), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(401), 10,
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
  [10588] = 6,
    ACTIONS(708), 1,
      aux_sym_ident_token1,
    STATE(22), 1,
      sym__or,
    STATE(30), 1,
      sym__and,
    STATE(277), 1,
      aux_sym_or_expression_repeat1,
    STATE(291), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(706), 12,
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
  [10618] = 6,
    ACTIONS(708), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__and,
    STATE(21), 1,
      sym__or,
    STATE(281), 1,
      aux_sym_or_expression_repeat1,
    STATE(283), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(706), 12,
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
  [10648] = 2,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(284), 16,
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
  [10670] = 8,
    ACTIONS(704), 1,
      aux_sym_ident_token1,
    ACTIONS(733), 1,
      anon_sym_and2,
    ACTIONS(735), 1,
      anon_sym_or,
    STATE(20), 1,
      sym__and,
    STATE(21), 1,
      sym__or,
    STATE(281), 1,
      aux_sym_or_expression_repeat1,
    STATE(283), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(702), 10,
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
  [10704] = 8,
    ACTIONS(696), 1,
      aux_sym_ident_token1,
    ACTIONS(729), 1,
      anon_sym_and2,
    ACTIONS(731), 1,
      anon_sym_or,
    STATE(22), 1,
      sym__or,
    STATE(30), 1,
      sym__and,
    STATE(277), 1,
      aux_sym_or_expression_repeat1,
    STATE(291), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(690), 10,
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
  [10738] = 4,
    ACTIONS(280), 1,
      aux_sym_ident_token1,
    ACTIONS(737), 1,
      anon_sym_DOT,
    STATE(244), 1,
      aux_sym_path_repeat1,
    ACTIONS(278), 14,
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
  [10764] = 8,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(733), 1,
      anon_sym_and2,
    ACTIONS(735), 1,
      anon_sym_or,
    STATE(20), 1,
      sym__and,
    STATE(21), 1,
      sym__or,
    STATE(281), 1,
      aux_sym_or_expression_repeat1,
    STATE(283), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(401), 10,
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
  [10798] = 8,
    ACTIONS(700), 1,
      aux_sym_ident_token1,
    ACTIONS(729), 1,
      anon_sym_and2,
    ACTIONS(731), 1,
      anon_sym_or,
    STATE(22), 1,
      sym__or,
    STATE(30), 1,
      sym__and,
    STATE(277), 1,
      aux_sym_or_expression_repeat1,
    STATE(291), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(698), 10,
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
  [10832] = 8,
    ACTIONS(704), 1,
      aux_sym_ident_token1,
    ACTIONS(729), 1,
      anon_sym_and2,
    ACTIONS(731), 1,
      anon_sym_or,
    STATE(22), 1,
      sym__or,
    STATE(30), 1,
      sym__and,
    STATE(277), 1,
      aux_sym_or_expression_repeat1,
    STATE(291), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(702), 10,
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
  [10866] = 8,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(733), 1,
      anon_sym_and2,
    ACTIONS(735), 1,
      anon_sym_or,
    STATE(20), 1,
      sym__and,
    STATE(21), 1,
      sym__or,
    STATE(281), 1,
      aux_sym_or_expression_repeat1,
    STATE(283), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(568), 10,
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
  [10900] = 8,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(729), 1,
      anon_sym_and2,
    ACTIONS(731), 1,
      anon_sym_or,
    STATE(22), 1,
      sym__or,
    STATE(30), 1,
      sym__and,
    STATE(277), 1,
      aux_sym_or_expression_repeat1,
    STATE(291), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(568), 10,
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
  [10934] = 2,
    ACTIONS(301), 1,
      aux_sym_ident_token1,
    ACTIONS(299), 16,
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
  [10956] = 2,
    ACTIONS(297), 1,
      aux_sym_ident_token1,
    ACTIONS(295), 16,
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
  [10978] = 4,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(739), 1,
      anon_sym_DOT,
    STATE(242), 1,
      aux_sym_path_repeat1,
    ACTIONS(284), 14,
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
  [11004] = 8,
    ACTIONS(700), 1,
      aux_sym_ident_token1,
    ACTIONS(733), 1,
      anon_sym_and2,
    ACTIONS(735), 1,
      anon_sym_or,
    STATE(20), 1,
      sym__and,
    STATE(21), 1,
      sym__or,
    STATE(281), 1,
      aux_sym_or_expression_repeat1,
    STATE(283), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(698), 10,
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
  [11038] = 4,
    ACTIONS(293), 1,
      aux_sym_ident_token1,
    ACTIONS(737), 1,
      anon_sym_DOT,
    STATE(242), 1,
      aux_sym_path_repeat1,
    ACTIONS(291), 14,
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
  [11064] = 8,
    ACTIONS(696), 1,
      aux_sym_ident_token1,
    ACTIONS(733), 1,
      anon_sym_and2,
    ACTIONS(735), 1,
      anon_sym_or,
    STATE(20), 1,
      sym__and,
    STATE(21), 1,
      sym__or,
    STATE(281), 1,
      aux_sym_or_expression_repeat1,
    STATE(283), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(690), 10,
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
  [11098] = 2,
    ACTIONS(602), 1,
      aux_sym_ident_token1,
    ACTIONS(600), 15,
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
  [11119] = 2,
    ACTIONS(371), 1,
      aux_sym_ident_token1,
    ACTIONS(369), 15,
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
  [11140] = 2,
    ACTIONS(630), 1,
      aux_sym_ident_token1,
    ACTIONS(628), 15,
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
  [11161] = 2,
    ACTIONS(634), 1,
      aux_sym_ident_token1,
    ACTIONS(632), 15,
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
  [11182] = 2,
    ACTIONS(297), 1,
      aux_sym_ident_token1,
    ACTIONS(295), 15,
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
  [11203] = 2,
    ACTIONS(594), 1,
      aux_sym_ident_token1,
    ACTIONS(592), 15,
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
  [11224] = 2,
    ACTIONS(301), 1,
      aux_sym_ident_token1,
    ACTIONS(299), 15,
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
  [11245] = 2,
    ACTIONS(744), 1,
      aux_sym_ident_token1,
    ACTIONS(742), 15,
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
  [11266] = 2,
    ACTIONS(614), 1,
      aux_sym_ident_token1,
    ACTIONS(612), 15,
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
  [11287] = 2,
    ACTIONS(748), 1,
      aux_sym_ident_token1,
    ACTIONS(746), 15,
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
  [11308] = 2,
    ACTIONS(752), 1,
      aux_sym_ident_token1,
    ACTIONS(750), 15,
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
  [11329] = 2,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(284), 15,
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
  [11350] = 2,
    ACTIONS(387), 1,
      aux_sym_ident_token1,
    ACTIONS(385), 15,
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
  [11371] = 2,
    ACTIONS(756), 1,
      aux_sym_ident_token1,
    ACTIONS(754), 15,
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
  [11392] = 2,
    ACTIONS(598), 1,
      aux_sym_ident_token1,
    ACTIONS(596), 15,
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
  [11413] = 2,
    ACTIONS(760), 1,
      aux_sym_ident_token1,
    ACTIONS(758), 15,
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
  [11434] = 2,
    ACTIONS(646), 1,
      aux_sym_ident_token1,
    ACTIONS(644), 15,
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
  [11455] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 15,
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
  [11476] = 2,
    ACTIONS(642), 1,
      aux_sym_ident_token1,
    ACTIONS(640), 15,
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
  [11497] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 15,
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
  [11518] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 15,
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
  [11539] = 2,
    ACTIONS(626), 1,
      aux_sym_ident_token1,
    ACTIONS(624), 15,
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
  [11560] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 15,
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
  [11581] = 2,
    ACTIONS(397), 1,
      aux_sym_ident_token1,
    ACTIONS(395), 15,
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
  [11602] = 2,
    ACTIONS(764), 1,
      aux_sym_ident_token1,
    ACTIONS(762), 15,
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
  [11623] = 2,
    ACTIONS(606), 1,
      aux_sym_ident_token1,
    ACTIONS(604), 15,
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
  [11644] = 2,
    ACTIONS(768), 1,
      aux_sym_ident_token1,
    ACTIONS(766), 15,
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
  [11665] = 3,
    ACTIONS(377), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(373), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
    ACTIONS(375), 10,
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
  [11688] = 2,
    ACTIONS(610), 1,
      aux_sym_ident_token1,
    ACTIONS(608), 15,
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
  [11709] = 2,
    ACTIONS(618), 1,
      aux_sym_ident_token1,
    ACTIONS(616), 15,
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
  [11730] = 2,
    ACTIONS(383), 1,
      aux_sym_ident_token1,
    ACTIONS(381), 15,
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
  [11751] = 4,
    ACTIONS(715), 1,
      aux_sym_ident_token1,
    STATE(22), 1,
      sym__or,
    STATE(288), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(713), 12,
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
  [11775] = 4,
    ACTIONS(280), 1,
      aux_sym_ident_token1,
    ACTIONS(770), 1,
      anon_sym_DOT,
    STATE(292), 1,
      aux_sym_path_repeat1,
    ACTIONS(278), 12,
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
  [11799] = 5,
    ACTIONS(696), 1,
      aux_sym_ident_token1,
    ACTIONS(772), 1,
      anon_sym_or,
    STATE(21), 1,
      sym__or,
    STATE(279), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(690), 11,
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
  [11825] = 5,
    ACTIONS(700), 1,
      aux_sym_ident_token1,
    ACTIONS(775), 1,
      anon_sym_and2,
    STATE(20), 1,
      sym__and,
    STATE(280), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(698), 11,
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
  [11851] = 4,
    ACTIONS(715), 1,
      aux_sym_ident_token1,
    STATE(21), 1,
      sym__or,
    STATE(279), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(713), 12,
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
  [11875] = 4,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(778), 1,
      anon_sym_DOT,
    STATE(282), 1,
      aux_sym_path_repeat1,
    ACTIONS(284), 12,
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
  [11899] = 4,
    ACTIONS(722), 1,
      aux_sym_ident_token1,
    STATE(20), 1,
      sym__and,
    STATE(280), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(720), 12,
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
  [11923] = 2,
    ACTIONS(783), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(781), 13,
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
  [11943] = 4,
    ACTIONS(293), 1,
      aux_sym_ident_token1,
    ACTIONS(785), 1,
      anon_sym_DOT,
    STATE(282), 1,
      aux_sym_path_repeat1,
    ACTIONS(291), 12,
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
  [11967] = 4,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(787), 1,
      anon_sym_DOT,
    STATE(286), 1,
      aux_sym_path_repeat1,
    ACTIONS(284), 12,
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
  [11991] = 3,
    ACTIONS(792), 1,
      anon_sym_LPAREN_RPAREN,
    ACTIONS(794), 1,
      aux_sym_ident_token1,
    ACTIONS(790), 13,
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
  [12013] = 5,
    ACTIONS(696), 1,
      aux_sym_ident_token1,
    ACTIONS(796), 1,
      anon_sym_or,
    STATE(22), 1,
      sym__or,
    STATE(288), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(690), 11,
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
  [12039] = 5,
    ACTIONS(700), 1,
      aux_sym_ident_token1,
    ACTIONS(799), 1,
      anon_sym_and2,
    STATE(30), 1,
      sym__and,
    STATE(289), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(698), 11,
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
  [12065] = 4,
    ACTIONS(280), 1,
      aux_sym_ident_token1,
    ACTIONS(785), 1,
      anon_sym_DOT,
    STATE(285), 1,
      aux_sym_path_repeat1,
    ACTIONS(278), 12,
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
  [12089] = 4,
    ACTIONS(722), 1,
      aux_sym_ident_token1,
    STATE(30), 1,
      sym__and,
    STATE(289), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(720), 12,
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
  [12113] = 4,
    ACTIONS(293), 1,
      aux_sym_ident_token1,
    ACTIONS(770), 1,
      anon_sym_DOT,
    STATE(286), 1,
      aux_sym_path_repeat1,
    ACTIONS(291), 12,
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
  [12137] = 2,
    ACTIONS(626), 1,
      aux_sym_ident_token1,
    ACTIONS(624), 13,
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
  [12156] = 2,
    ACTIONS(804), 1,
      aux_sym_ident_token1,
    ACTIONS(802), 13,
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
  [12175] = 2,
    ACTIONS(808), 1,
      aux_sym_ident_token1,
    ACTIONS(806), 13,
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
  [12194] = 2,
    ACTIONS(812), 1,
      aux_sym_ident_token1,
    ACTIONS(810), 13,
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
  [12213] = 2,
    ACTIONS(816), 1,
      aux_sym_ident_token1,
    ACTIONS(814), 13,
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
  [12232] = 2,
    ACTIONS(301), 1,
      aux_sym_ident_token1,
    ACTIONS(299), 13,
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
  [12251] = 4,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(818), 1,
      anon_sym_DOT,
    STATE(299), 1,
      aux_sym_path_repeat1,
    ACTIONS(284), 11,
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
  [12274] = 2,
    ACTIONS(297), 1,
      aux_sym_ident_token1,
    ACTIONS(295), 13,
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
  [12293] = 2,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(284), 13,
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
  [12312] = 2,
    ACTIONS(618), 1,
      aux_sym_ident_token1,
    ACTIONS(616), 13,
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
  [12331] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 13,
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
  [12350] = 2,
    ACTIONS(823), 1,
      aux_sym_ident_token1,
    ACTIONS(821), 13,
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
  [12369] = 2,
    ACTIONS(301), 1,
      aux_sym_ident_token1,
    ACTIONS(299), 13,
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
  [12388] = 2,
    ACTIONS(297), 1,
      aux_sym_ident_token1,
    ACTIONS(295), 13,
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
  [12407] = 2,
    ACTIONS(827), 1,
      aux_sym_ident_token1,
    ACTIONS(825), 13,
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
  [12426] = 2,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(401), 13,
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
  [12445] = 2,
    ACTIONS(794), 1,
      aux_sym_ident_token1,
    ACTIONS(790), 13,
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
  [12464] = 2,
    ACTIONS(630), 1,
      aux_sym_ident_token1,
    ACTIONS(628), 13,
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
  [12483] = 4,
    ACTIONS(293), 1,
      aux_sym_ident_token1,
    ACTIONS(829), 1,
      anon_sym_DOT,
    STATE(299), 1,
      aux_sym_path_repeat1,
    ACTIONS(291), 11,
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
  [12506] = 2,
    ACTIONS(833), 1,
      aux_sym_ident_token1,
    ACTIONS(831), 13,
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
  [12525] = 2,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(568), 13,
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
  [12544] = 2,
    ACTIONS(837), 1,
      aux_sym_ident_token1,
    ACTIONS(835), 13,
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
  [12563] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 13,
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
  [12582] = 2,
    ACTIONS(841), 1,
      aux_sym_ident_token1,
    ACTIONS(839), 13,
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
  [12601] = 2,
    ACTIONS(634), 1,
      aux_sym_ident_token1,
    ACTIONS(632), 13,
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
  [12620] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 13,
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
  [12639] = 2,
    ACTIONS(845), 1,
      aux_sym_ident_token1,
    ACTIONS(843), 13,
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
  [12658] = 2,
    ACTIONS(849), 1,
      aux_sym_ident_token1,
    ACTIONS(847), 13,
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
  [12677] = 2,
    ACTIONS(853), 1,
      aux_sym_ident_token1,
    ACTIONS(851), 13,
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
  [12696] = 2,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(284), 13,
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
  [12715] = 2,
    ACTIONS(642), 1,
      aux_sym_ident_token1,
    ACTIONS(640), 13,
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
  [12734] = 2,
    ACTIONS(594), 1,
      aux_sym_ident_token1,
    ACTIONS(592), 13,
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
  [12753] = 2,
    ACTIONS(602), 1,
      aux_sym_ident_token1,
    ACTIONS(600), 13,
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
  [12772] = 2,
    ACTIONS(371), 1,
      aux_sym_ident_token1,
    ACTIONS(369), 13,
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
  [12791] = 2,
    ACTIONS(383), 1,
      aux_sym_ident_token1,
    ACTIONS(381), 13,
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
  [12810] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 13,
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
  [12829] = 4,
    ACTIONS(280), 1,
      aux_sym_ident_token1,
    ACTIONS(829), 1,
      anon_sym_DOT,
    STATE(311), 1,
      aux_sym_path_repeat1,
    ACTIONS(278), 11,
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
  [12852] = 2,
    ACTIONS(646), 1,
      aux_sym_ident_token1,
    ACTIONS(644), 13,
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
  [12871] = 2,
    ACTIONS(606), 1,
      aux_sym_ident_token1,
    ACTIONS(604), 13,
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
  [12890] = 2,
    ACTIONS(598), 1,
      aux_sym_ident_token1,
    ACTIONS(596), 13,
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
  [12909] = 2,
    ACTIONS(857), 1,
      aux_sym_ident_token1,
    ACTIONS(855), 13,
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
  [12928] = 2,
    ACTIONS(387), 1,
      aux_sym_ident_token1,
    ACTIONS(385), 13,
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
  [12947] = 4,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(859), 1,
      anon_sym_DOT,
    STATE(335), 1,
      aux_sym_path_repeat1,
    ACTIONS(284), 11,
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
  [12970] = 2,
    ACTIONS(864), 1,
      aux_sym_ident_token1,
    ACTIONS(862), 13,
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
  [12989] = 2,
    ACTIONS(868), 1,
      aux_sym_ident_token1,
    ACTIONS(866), 13,
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
  [13008] = 2,
    ACTIONS(872), 1,
      aux_sym_ident_token1,
    ACTIONS(870), 13,
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
  [13027] = 2,
    ACTIONS(610), 1,
      aux_sym_ident_token1,
    ACTIONS(608), 13,
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
  [13046] = 2,
    ACTIONS(397), 1,
      aux_sym_ident_token1,
    ACTIONS(395), 13,
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
  [13065] = 4,
    ACTIONS(293), 1,
      aux_sym_ident_token1,
    ACTIONS(874), 1,
      anon_sym_DOT,
    STATE(335), 1,
      aux_sym_path_repeat1,
    ACTIONS(291), 11,
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
  [13088] = 2,
    ACTIONS(614), 1,
      aux_sym_ident_token1,
    ACTIONS(612), 13,
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
  [13107] = 4,
    ACTIONS(280), 1,
      aux_sym_ident_token1,
    ACTIONS(874), 1,
      anon_sym_DOT,
    STATE(341), 1,
      aux_sym_path_repeat1,
    ACTIONS(278), 11,
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
  [13130] = 2,
    ACTIONS(878), 1,
      aux_sym_ident_token1,
    ACTIONS(876), 13,
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
  [13149] = 2,
    ACTIONS(756), 1,
      aux_sym_ident_token1,
    ACTIONS(754), 13,
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
  [13168] = 2,
    ACTIONS(882), 1,
      aux_sym_ident_token1,
    ACTIONS(880), 13,
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
  [13187] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 12,
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
  [13205] = 2,
    ACTIONS(383), 1,
      aux_sym_ident_token1,
    ACTIONS(381), 12,
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
  [13223] = 5,
    ACTIONS(407), 1,
      anon_sym_between,
    ACTIONS(409), 1,
      anon_sym_exists,
    STATE(261), 1,
      sym_comparator,
    ACTIONS(405), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(403), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [13247] = 2,
    ACTIONS(630), 1,
      aux_sym_ident_token1,
    ACTIONS(628), 12,
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
  [13265] = 2,
    ACTIONS(748), 1,
      aux_sym_ident_token1,
    ACTIONS(746), 12,
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
  [13283] = 5,
    ACTIONS(672), 1,
      anon_sym_between,
    ACTIONS(674), 1,
      anon_sym_exists,
    STATE(618), 1,
      sym_comparator,
    ACTIONS(670), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(668), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [13307] = 2,
    ACTIONS(744), 1,
      aux_sym_ident_token1,
    ACTIONS(742), 12,
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
  [13325] = 2,
    ACTIONS(634), 1,
      aux_sym_ident_token1,
    ACTIONS(632), 12,
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
  [13343] = 2,
    ACTIONS(606), 1,
      aux_sym_ident_token1,
    ACTIONS(604), 12,
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
  [13361] = 2,
    ACTIONS(748), 1,
      aux_sym_ident_token1,
    ACTIONS(746), 12,
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
  [13379] = 2,
    ACTIONS(752), 1,
      aux_sym_ident_token1,
    ACTIONS(750), 12,
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
  [13397] = 2,
    ACTIONS(594), 1,
      aux_sym_ident_token1,
    ACTIONS(592), 12,
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
  [13415] = 2,
    ACTIONS(886), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(884), 11,
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
  [13433] = 2,
    ACTIONS(760), 1,
      aux_sym_ident_token1,
    ACTIONS(758), 12,
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
  [13451] = 2,
    ACTIONS(764), 1,
      aux_sym_ident_token1,
    ACTIONS(762), 12,
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
  [13469] = 2,
    ACTIONS(768), 1,
      aux_sym_ident_token1,
    ACTIONS(766), 12,
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
  [13487] = 2,
    ACTIONS(602), 1,
      aux_sym_ident_token1,
    ACTIONS(600), 12,
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
  [13505] = 2,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(284), 12,
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
  [13523] = 2,
    ACTIONS(297), 1,
      aux_sym_ident_token1,
    ACTIONS(295), 12,
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
  [13541] = 2,
    ACTIONS(630), 1,
      aux_sym_ident_token1,
    ACTIONS(628), 12,
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
  [13559] = 2,
    ACTIONS(760), 1,
      aux_sym_ident_token1,
    ACTIONS(758), 12,
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
  [13577] = 2,
    ACTIONS(764), 1,
      aux_sym_ident_token1,
    ACTIONS(762), 12,
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
  [13595] = 2,
    ACTIONS(634), 1,
      aux_sym_ident_token1,
    ACTIONS(632), 12,
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
  [13613] = 2,
    ACTIONS(594), 1,
      aux_sym_ident_token1,
    ACTIONS(592), 12,
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
  [13631] = 2,
    ACTIONS(602), 1,
      aux_sym_ident_token1,
    ACTIONS(600), 12,
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
  [13649] = 2,
    ACTIONS(614), 1,
      aux_sym_ident_token1,
    ACTIONS(612), 12,
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
  [13667] = 2,
    ACTIONS(387), 1,
      aux_sym_ident_token1,
    ACTIONS(385), 12,
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
  [13685] = 2,
    ACTIONS(371), 1,
      aux_sym_ident_token1,
    ACTIONS(369), 12,
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
  [13703] = 2,
    ACTIONS(297), 1,
      aux_sym_ident_token1,
    ACTIONS(295), 12,
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
  [13721] = 2,
    ACTIONS(383), 1,
      aux_sym_ident_token1,
    ACTIONS(381), 12,
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
  [13739] = 2,
    ACTIONS(301), 1,
      aux_sym_ident_token1,
    ACTIONS(299), 12,
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
  [13757] = 2,
    ACTIONS(598), 1,
      aux_sym_ident_token1,
    ACTIONS(596), 12,
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
  [13775] = 2,
    ACTIONS(646), 1,
      aux_sym_ident_token1,
    ACTIONS(644), 12,
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
  [13793] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 12,
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
  [13811] = 2,
    ACTIONS(610), 1,
      aux_sym_ident_token1,
    ACTIONS(608), 12,
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
  [13829] = 2,
    ACTIONS(618), 1,
      aux_sym_ident_token1,
    ACTIONS(616), 12,
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
  [13847] = 2,
    ACTIONS(642), 1,
      aux_sym_ident_token1,
    ACTIONS(640), 12,
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
  [13865] = 2,
    ACTIONS(397), 1,
      aux_sym_ident_token1,
    ACTIONS(395), 12,
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
  [13883] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 12,
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
  [13901] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 12,
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
  [13919] = 2,
    ACTIONS(626), 1,
      aux_sym_ident_token1,
    ACTIONS(624), 12,
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
  [13937] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 12,
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
  [13955] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 12,
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
  [13973] = 2,
    ACTIONS(626), 1,
      aux_sym_ident_token1,
    ACTIONS(624), 12,
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
  [13991] = 2,
    ACTIONS(744), 1,
      aux_sym_ident_token1,
    ACTIONS(742), 12,
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
  [14009] = 2,
    ACTIONS(642), 1,
      aux_sym_ident_token1,
    ACTIONS(640), 12,
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
  [14027] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 12,
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
  [14045] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 12,
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
  [14063] = 2,
    ACTIONS(752), 1,
      aux_sym_ident_token1,
    ACTIONS(750), 12,
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
  [14081] = 2,
    ACTIONS(646), 1,
      aux_sym_ident_token1,
    ACTIONS(644), 12,
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
  [14099] = 2,
    ACTIONS(397), 1,
      aux_sym_ident_token1,
    ACTIONS(395), 12,
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
  [14117] = 2,
    ACTIONS(598), 1,
      aux_sym_ident_token1,
    ACTIONS(596), 12,
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
  [14135] = 2,
    ACTIONS(768), 1,
      aux_sym_ident_token1,
    ACTIONS(766), 12,
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
  [14153] = 2,
    ACTIONS(387), 1,
      aux_sym_ident_token1,
    ACTIONS(385), 12,
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
  [14171] = 2,
    ACTIONS(618), 1,
      aux_sym_ident_token1,
    ACTIONS(616), 12,
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
  [14189] = 2,
    ACTIONS(286), 1,
      aux_sym_ident_token1,
    ACTIONS(284), 12,
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
  [14207] = 2,
    ACTIONS(610), 1,
      aux_sym_ident_token1,
    ACTIONS(608), 12,
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
  [14225] = 2,
    ACTIONS(606), 1,
      aux_sym_ident_token1,
    ACTIONS(604), 12,
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
  [14243] = 2,
    ACTIONS(614), 1,
      aux_sym_ident_token1,
    ACTIONS(612), 12,
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
  [14261] = 2,
    ACTIONS(756), 1,
      aux_sym_ident_token1,
    ACTIONS(754), 12,
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
  [14279] = 5,
    ACTIONS(654), 1,
      anon_sym_between,
    ACTIONS(656), 1,
      anon_sym_exists,
    STATE(367), 1,
      sym_comparator,
    ACTIONS(652), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(650), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [14303] = 2,
    ACTIONS(371), 1,
      aux_sym_ident_token1,
    ACTIONS(369), 12,
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
  [14321] = 2,
    ACTIONS(756), 1,
      aux_sym_ident_token1,
    ACTIONS(754), 12,
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
  [14339] = 2,
    ACTIONS(890), 2,
      anon_sym_DQUOTE,
      aux_sym_ident_token1,
    ACTIONS(888), 11,
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
  [14357] = 5,
    ACTIONS(662), 1,
      anon_sym_between,
    ACTIONS(664), 1,
      anon_sym_exists,
    STATE(360), 1,
      sym_comparator,
    ACTIONS(660), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(658), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_after,
      anon_sym_before,
      anon_sym_contains,
  [14381] = 2,
    ACTIONS(301), 1,
      aux_sym_ident_token1,
    ACTIONS(299), 12,
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
  [14399] = 3,
    ACTIONS(794), 1,
      aux_sym_ident_token1,
    ACTIONS(892), 1,
      anon_sym_LPAREN_RPAREN,
    ACTIONS(790), 10,
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
  [14418] = 3,
    ACTIONS(794), 1,
      aux_sym_ident_token1,
    ACTIONS(894), 1,
      anon_sym_LPAREN_RPAREN,
    ACTIONS(790), 10,
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
  [14437] = 2,
    ACTIONS(383), 1,
      aux_sym_ident_token1,
    ACTIONS(381), 10,
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
  [14453] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 10,
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
  [14469] = 2,
    ACTIONS(397), 1,
      aux_sym_ident_token1,
    ACTIONS(395), 10,
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
  [14485] = 2,
    ACTIONS(845), 1,
      aux_sym_ident_token1,
    ACTIONS(843), 10,
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
  [14501] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 10,
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
  [14517] = 2,
    ACTIONS(626), 1,
      aux_sym_ident_token1,
    ACTIONS(624), 10,
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
  [14533] = 2,
    ACTIONS(808), 1,
      aux_sym_ident_token1,
    ACTIONS(806), 10,
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
  [14549] = 2,
    ACTIONS(602), 1,
      aux_sym_ident_token1,
    ACTIONS(600), 10,
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
  [14565] = 2,
    ACTIONS(837), 1,
      aux_sym_ident_token1,
    ACTIONS(835), 10,
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
  [14581] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 10,
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
  [14597] = 2,
    ACTIONS(642), 1,
      aux_sym_ident_token1,
    ACTIONS(640), 10,
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
  [14613] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 10,
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
  [14629] = 2,
    ACTIONS(594), 1,
      aux_sym_ident_token1,
    ACTIONS(592), 10,
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
  [14645] = 2,
    ACTIONS(833), 1,
      aux_sym_ident_token1,
    ACTIONS(831), 10,
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
  [14661] = 2,
    ACTIONS(646), 1,
      aux_sym_ident_token1,
    ACTIONS(644), 10,
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
  [14677] = 2,
    ACTIONS(837), 1,
      aux_sym_ident_token1,
    ACTIONS(835), 10,
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
  [14693] = 2,
    ACTIONS(598), 1,
      aux_sym_ident_token1,
    ACTIONS(596), 10,
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
  [14709] = 2,
    ACTIONS(841), 1,
      aux_sym_ident_token1,
    ACTIONS(839), 10,
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
  [14725] = 2,
    ACTIONS(812), 1,
      aux_sym_ident_token1,
    ACTIONS(810), 10,
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
  [14741] = 2,
    ACTIONS(816), 1,
      aux_sym_ident_token1,
    ACTIONS(814), 10,
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
  [14757] = 2,
    ACTIONS(812), 1,
      aux_sym_ident_token1,
    ACTIONS(810), 10,
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
  [14773] = 2,
    ACTIONS(808), 1,
      aux_sym_ident_token1,
    ACTIONS(806), 10,
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
  [14789] = 2,
    ACTIONS(849), 1,
      aux_sym_ident_token1,
    ACTIONS(847), 10,
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
  [14805] = 2,
    ACTIONS(614), 1,
      aux_sym_ident_token1,
    ACTIONS(612), 10,
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
  [14821] = 2,
    ACTIONS(383), 1,
      aux_sym_ident_token1,
    ACTIONS(381), 10,
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
  [14837] = 2,
    ACTIONS(882), 1,
      aux_sym_ident_token1,
    ACTIONS(880), 10,
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
  [14853] = 2,
    ACTIONS(371), 1,
      aux_sym_ident_token1,
    ACTIONS(369), 10,
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
  [14869] = 2,
    ACTIONS(804), 1,
      aux_sym_ident_token1,
    ACTIONS(802), 10,
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
  [14885] = 2,
    ACTIONS(630), 1,
      aux_sym_ident_token1,
    ACTIONS(628), 10,
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
  [14901] = 2,
    ACTIONS(857), 1,
      aux_sym_ident_token1,
    ACTIONS(855), 10,
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
  [14917] = 2,
    ACTIONS(827), 1,
      aux_sym_ident_token1,
    ACTIONS(825), 10,
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
  [14933] = 2,
    ACTIONS(823), 1,
      aux_sym_ident_token1,
    ACTIONS(821), 10,
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
  [14949] = 2,
    ACTIONS(823), 1,
      aux_sym_ident_token1,
    ACTIONS(821), 10,
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
  [14965] = 2,
    ACTIONS(827), 1,
      aux_sym_ident_token1,
    ACTIONS(825), 10,
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
  [14981] = 2,
    ACTIONS(845), 1,
      aux_sym_ident_token1,
    ACTIONS(843), 10,
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
  [14997] = 2,
    ACTIONS(606), 1,
      aux_sym_ident_token1,
    ACTIONS(604), 10,
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
  [15013] = 2,
    ACTIONS(833), 1,
      aux_sym_ident_token1,
    ACTIONS(831), 10,
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
  [15029] = 2,
    ACTIONS(634), 1,
      aux_sym_ident_token1,
    ACTIONS(632), 10,
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
  [15045] = 2,
    ACTIONS(853), 1,
      aux_sym_ident_token1,
    ACTIONS(851), 10,
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
  [15061] = 2,
    ACTIONS(634), 1,
      aux_sym_ident_token1,
    ACTIONS(632), 10,
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
  [15077] = 2,
    ACTIONS(872), 1,
      aux_sym_ident_token1,
    ACTIONS(870), 10,
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
  [15093] = 2,
    ACTIONS(864), 1,
      aux_sym_ident_token1,
    ACTIONS(862), 10,
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
  [15109] = 2,
    ACTIONS(853), 1,
      aux_sym_ident_token1,
    ACTIONS(851), 10,
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
  [15125] = 2,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(568), 10,
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
  [15141] = 2,
    ACTIONS(594), 1,
      aux_sym_ident_token1,
    ACTIONS(592), 10,
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
  [15157] = 2,
    ACTIONS(841), 1,
      aux_sym_ident_token1,
    ACTIONS(839), 10,
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
  [15173] = 2,
    ACTIONS(882), 1,
      aux_sym_ident_token1,
    ACTIONS(880), 10,
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
  [15189] = 2,
    ACTIONS(602), 1,
      aux_sym_ident_token1,
    ACTIONS(600), 10,
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
  [15205] = 2,
    ACTIONS(868), 1,
      aux_sym_ident_token1,
    ACTIONS(866), 10,
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
  [15221] = 2,
    ACTIONS(804), 1,
      aux_sym_ident_token1,
    ACTIONS(802), 10,
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
  [15237] = 2,
    ACTIONS(878), 1,
      aux_sym_ident_token1,
    ACTIONS(876), 10,
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
  [15253] = 2,
    ACTIONS(794), 1,
      aux_sym_ident_token1,
    ACTIONS(790), 10,
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
  [15269] = 2,
    ACTIONS(872), 1,
      aux_sym_ident_token1,
    ACTIONS(870), 10,
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
  [15285] = 2,
    ACTIONS(868), 1,
      aux_sym_ident_token1,
    ACTIONS(866), 10,
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
  [15301] = 2,
    ACTIONS(878), 1,
      aux_sym_ident_token1,
    ACTIONS(876), 10,
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
  [15317] = 2,
    ACTIONS(864), 1,
      aux_sym_ident_token1,
    ACTIONS(862), 10,
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
  [15333] = 2,
    ACTIONS(618), 1,
      aux_sym_ident_token1,
    ACTIONS(616), 10,
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
  [15349] = 2,
    ACTIONS(857), 1,
      aux_sym_ident_token1,
    ACTIONS(855), 10,
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
  [15365] = 2,
    ACTIONS(570), 1,
      aux_sym_ident_token1,
    ACTIONS(568), 10,
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
  [15381] = 2,
    ACTIONS(849), 1,
      aux_sym_ident_token1,
    ACTIONS(847), 10,
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
  [15397] = 2,
    ACTIONS(371), 1,
      aux_sym_ident_token1,
    ACTIONS(369), 10,
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
  [15413] = 2,
    ACTIONS(794), 1,
      aux_sym_ident_token1,
    ACTIONS(790), 10,
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
  [15429] = 2,
    ACTIONS(387), 1,
      aux_sym_ident_token1,
    ACTIONS(385), 10,
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
  [15445] = 2,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(401), 10,
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
  [15461] = 2,
    ACTIONS(610), 1,
      aux_sym_ident_token1,
    ACTIONS(608), 10,
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
  [15477] = 2,
    ACTIONS(610), 1,
      aux_sym_ident_token1,
    ACTIONS(608), 10,
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
  [15493] = 2,
    ACTIONS(618), 1,
      aux_sym_ident_token1,
    ACTIONS(616), 10,
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
  [15509] = 2,
    ACTIONS(816), 1,
      aux_sym_ident_token1,
    ACTIONS(814), 10,
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
  [15525] = 2,
    ACTIONS(397), 1,
      aux_sym_ident_token1,
    ACTIONS(395), 10,
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
  [15541] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 10,
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
  [15557] = 2,
    ACTIONS(626), 1,
      aux_sym_ident_token1,
    ACTIONS(624), 10,
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
  [15573] = 2,
    ACTIONS(622), 1,
      aux_sym_ident_token1,
    ACTIONS(620), 10,
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
  [15589] = 2,
    ACTIONS(630), 1,
      aux_sym_ident_token1,
    ACTIONS(628), 10,
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
  [15605] = 2,
    ACTIONS(756), 1,
      aux_sym_ident_token1,
    ACTIONS(754), 10,
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
  [15621] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 10,
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
  [15637] = 2,
    ACTIONS(642), 1,
      aux_sym_ident_token1,
    ACTIONS(640), 10,
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
  [15653] = 2,
    ACTIONS(638), 1,
      aux_sym_ident_token1,
    ACTIONS(636), 10,
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
  [15669] = 2,
    ACTIONS(411), 1,
      aux_sym_ident_token1,
    ACTIONS(401), 10,
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
  [15685] = 2,
    ACTIONS(646), 1,
      aux_sym_ident_token1,
    ACTIONS(644), 10,
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
  [15701] = 2,
    ACTIONS(606), 1,
      aux_sym_ident_token1,
    ACTIONS(604), 10,
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
  [15717] = 2,
    ACTIONS(598), 1,
      aux_sym_ident_token1,
    ACTIONS(596), 10,
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
  [15733] = 2,
    ACTIONS(387), 1,
      aux_sym_ident_token1,
    ACTIONS(385), 10,
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
  [15749] = 2,
    ACTIONS(756), 1,
      aux_sym_ident_token1,
    ACTIONS(754), 10,
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
  [15765] = 2,
    ACTIONS(614), 1,
      aux_sym_ident_token1,
    ACTIONS(612), 10,
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
  [15781] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(193), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(896), 1,
      anon_sym_RBRACK,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    STATE(452), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(598), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [15810] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(135), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(900), 1,
      anon_sym_RBRACK,
    STATE(454), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(612), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [15839] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(143), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(902), 1,
      anon_sym_RBRACK,
    STATE(163), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(585), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [15868] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(181), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(904), 1,
      anon_sym_RBRACK,
    STATE(317), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(611), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [15897] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(169), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(906), 1,
      anon_sym_RBRACK,
    STATE(172), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(602), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [15926] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(199), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(908), 1,
      anon_sym_RBRACK,
    STATE(354), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(597), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [15955] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(175), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(910), 1,
      anon_sym_RBRACK,
    STATE(548), 1,
      sym__for,
    STATE(584), 1,
      aux_sym_array_repeat1,
    STATE(651), 1,
      sym_missing_array_end,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [15984] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(157), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(912), 1,
      anon_sym_RBRACK,
    STATE(369), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(596), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16013] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(163), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(914), 1,
      anon_sym_RBRACK,
    STATE(208), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(605), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16042] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(187), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(916), 1,
      anon_sym_RBRACK,
    STATE(249), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(604), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16071] = 9,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    ACTIONS(151), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(918), 1,
      anon_sym_RBRACK,
    STATE(131), 1,
      sym_missing_array_end,
    STATE(548), 1,
      sym__for,
    STATE(600), 1,
      aux_sym_array_repeat1,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16100] = 9,
    ACTIONS(920), 1,
      anon_sym_RPAREN,
    ACTIONS(922), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(924), 1,
      anon_sym_and2,
    ACTIONS(926), 1,
      anon_sym_or,
    STATE(24), 1,
      sym__or,
    STATE(35), 1,
      sym__and,
    STATE(357), 1,
      sym_missing_parenthesis_end,
    STATE(569), 1,
      aux_sym_or_expression_repeat1,
    STATE(575), 1,
      aux_sym_and_expression_repeat1,
  [16128] = 9,
    ACTIONS(924), 1,
      anon_sym_and2,
    ACTIONS(926), 1,
      anon_sym_or,
    ACTIONS(928), 1,
      anon_sym_RPAREN,
    ACTIONS(930), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(24), 1,
      sym__or,
    STATE(35), 1,
      sym__and,
    STATE(395), 1,
      sym_missing_parenthesis_end,
    STATE(569), 1,
      aux_sym_or_expression_repeat1,
    STATE(575), 1,
      aux_sym_and_expression_repeat1,
  [16156] = 9,
    ACTIONS(924), 1,
      anon_sym_and2,
    ACTIONS(926), 1,
      anon_sym_or,
    ACTIONS(932), 1,
      anon_sym_RPAREN,
    ACTIONS(934), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(24), 1,
      sym__or,
    STATE(35), 1,
      sym__and,
    STATE(256), 1,
      sym_missing_parenthesis_end,
    STATE(569), 1,
      aux_sym_or_expression_repeat1,
    STATE(575), 1,
      aux_sym_and_expression_repeat1,
  [16184] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(936), 1,
      anon_sym_RBRACE,
    ACTIONS(938), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(274), 1,
      sym_missing_brace_end,
    STATE(582), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16212] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(940), 1,
      anon_sym_RBRACE,
    ACTIONS(942), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(339), 1,
      sym_missing_brace_end,
    STATE(578), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16240] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(944), 1,
      anon_sym_RBRACE,
    ACTIONS(946), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(116), 1,
      sym_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(599), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16268] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(948), 1,
      anon_sym_RBRACE,
    ACTIONS(950), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(480), 1,
      sym_missing_brace_end,
    STATE(616), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16296] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(952), 1,
      anon_sym_RBRACE,
    ACTIONS(954), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(164), 1,
      sym_missing_brace_end,
    STATE(592), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16324] = 9,
    ACTIONS(688), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(924), 1,
      anon_sym_and2,
    ACTIONS(926), 1,
      anon_sym_or,
    ACTIONS(956), 1,
      anon_sym_RPAREN,
    STATE(24), 1,
      sym__or,
    STATE(35), 1,
      sym__and,
    STATE(569), 1,
      aux_sym_or_expression_repeat1,
    STATE(575), 1,
      aux_sym_and_expression_repeat1,
    STATE(637), 1,
      sym_missing_parenthesis_end,
  [16352] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(958), 1,
      anon_sym_RBRACE,
    ACTIONS(960), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(479), 1,
      sym_missing_brace_end,
    STATE(594), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16380] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(962), 1,
      anon_sym_RBRACE,
    ACTIONS(964), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(580), 1,
      sym_pair,
    STATE(647), 1,
      sym_missing_brace_end,
    STATE(683), 1,
      sym_string,
  [16408] = 9,
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
    STATE(141), 1,
      sym_missing_string_end,
    STATE(188), 1,
      sym_missing_brace_end,
    STATE(617), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16436] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(970), 1,
      anon_sym_RBRACE,
    ACTIONS(972), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(381), 1,
      sym_missing_brace_end,
    STATE(583), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16464] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(974), 1,
      anon_sym_RBRACE,
    ACTIONS(976), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(403), 1,
      sym_missing_brace_end,
    STATE(610), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16492] = 9,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(978), 1,
      anon_sym_RBRACE,
    ACTIONS(980), 1,
      anon_sym_ERROR_missing_brace_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(205), 1,
      sym_missing_brace_end,
    STATE(577), 1,
      sym_pair,
    STATE(683), 1,
      sym_string,
  [16520] = 7,
    ACTIONS(924), 1,
      anon_sym_and2,
    ACTIONS(926), 1,
      anon_sym_or,
    STATE(24), 1,
      sym__or,
    STATE(35), 1,
      sym__and,
    STATE(569), 1,
      aux_sym_or_expression_repeat1,
    STATE(575), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(690), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
  [16543] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(982), 1,
      anon_sym_RPAREN,
    ACTIONS(984), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(330), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16566] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(686), 1,
      anon_sym_RPAREN,
    ACTIONS(986), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(201), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16589] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(988), 1,
      anon_sym_RPAREN,
    ACTIONS(990), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(429), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16612] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(922), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(992), 1,
      anon_sym_RPAREN,
    STATE(379), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16635] = 5,
    STATE(24), 1,
      sym__or,
    STATE(35), 1,
      sym__and,
    STATE(569), 1,
      aux_sym_or_expression_repeat1,
    STATE(575), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(706), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [16654] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(934), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(994), 1,
      anon_sym_RPAREN,
    STATE(262), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16677] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(686), 1,
      anon_sym_RPAREN,
    ACTIONS(688), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(201), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16700] = 7,
    ACTIONS(924), 1,
      anon_sym_and2,
    ACTIONS(926), 1,
      anon_sym_or,
    STATE(24), 1,
      sym__or,
    STATE(35), 1,
      sym__and,
    STATE(569), 1,
      aux_sym_or_expression_repeat1,
    STATE(575), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(698), 2,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
  [16723] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(930), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(996), 1,
      anon_sym_RPAREN,
    STATE(396), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16746] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(688), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    ACTIONS(998), 1,
      anon_sym_RPAREN,
    STATE(562), 1,
      sym__for,
    STATE(648), 1,
      sym_missing_parenthesis_end,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16769] = 7,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    ACTIONS(1000), 1,
      anon_sym_RPAREN,
    ACTIONS(1002), 1,
      anon_sym_ERROR_missing_parenthesis_end,
    STATE(493), 1,
      sym_missing_parenthesis_end,
    STATE(562), 1,
      sym__for,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [16792] = 7,
    ACTIONS(562), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(566), 1,
      aux_sym_ident_token1,
    ACTIONS(1004), 1,
      anon_sym_LBRACK,
    STATE(329), 1,
      sym_ident,
    STATE(412), 1,
      sym_missing_identifier,
    STATE(414), 1,
      sym_path,
    STATE(466), 1,
      sym_array,
  [16814] = 7,
    ACTIONS(562), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(566), 1,
      aux_sym_ident_token1,
    ACTIONS(1006), 1,
      anon_sym_ERROR_missing_delete_field,
    STATE(329), 1,
      sym_ident,
    STATE(412), 1,
      sym_missing_identifier,
    STATE(455), 1,
      sym_path,
    STATE(463), 1,
      sym_missing_delete_field,
  [16836] = 7,
    ACTIONS(586), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(590), 1,
      aux_sym_ident_token1,
    ACTIONS(1008), 1,
      anon_sym_LBRACK,
    STATE(234), 1,
      sym_ident,
    STATE(252), 1,
      sym_missing_identifier,
    STATE(287), 1,
      sym_path,
    STATE(309), 1,
      sym_array,
  [16858] = 7,
    ACTIONS(586), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(590), 1,
      aux_sym_ident_token1,
    ACTIONS(1010), 1,
      anon_sym_ERROR_missing_delete_field,
    STATE(234), 1,
      sym_ident,
    STATE(252), 1,
      sym_missing_identifier,
    STATE(337), 1,
      sym_missing_delete_field,
    STATE(338), 1,
      sym_path,
  [16880] = 7,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1012), 1,
      anon_sym_ERROR_missing_update_field,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(346), 1,
      sym_missing_update_field,
    STATE(674), 1,
      sym_path,
  [16902] = 7,
    ACTIONS(510), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(514), 1,
      aux_sym_ident_token1,
    ACTIONS(1014), 1,
      anon_sym_LBRACK,
    STATE(343), 1,
      sym_ident,
    STATE(377), 1,
      sym_missing_identifier,
    STATE(413), 1,
      sym_path,
    STATE(476), 1,
      sym_array,
  [16924] = 7,
    ACTIONS(510), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(514), 1,
      aux_sym_ident_token1,
    ACTIONS(1016), 1,
      anon_sym_ERROR_missing_delete_field,
    STATE(343), 1,
      sym_ident,
    STATE(377), 1,
      sym_missing_identifier,
    STATE(467), 1,
      sym_path,
    STATE(468), 1,
      sym_missing_delete_field,
  [16946] = 7,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1018), 1,
      anon_sym_ERROR_missing_update_field,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(461), 1,
      sym_missing_update_field,
    STATE(677), 1,
      sym_path,
  [16968] = 7,
    ACTIONS(1020), 1,
      ts_builtin_sym_end,
    ACTIONS(1022), 1,
      anon_sym_RBRACK,
    ACTIONS(1024), 1,
      anon_sym_RPAREN,
    ACTIONS(1026), 1,
      anon_sym_ERROR_missing_array_query_end,
    ACTIONS(1028), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(709), 1,
      sym_missing_element_query_end,
    STATE(711), 1,
      sym_missing_array_query_end,
  [16990] = 7,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1030), 1,
      anon_sym_ERROR_missing_update_field,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(90), 1,
      sym_ident,
    STATE(440), 1,
      sym_missing_update_field,
    STATE(657), 1,
      sym_path,
  [17012] = 5,
    ACTIONS(1032), 1,
      anon_sym_DQUOTE,
    ACTIONS(1036), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    STATE(704), 1,
      sym_missing_string_end,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17029] = 6,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1038), 1,
      anon_sym_ERROR_missing_iterator,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(430), 1,
      sym_missing_iterator,
    STATE(699), 1,
      sym_ident,
  [17048] = 5,
    ACTIONS(1040), 1,
      anon_sym_DQUOTE,
    ACTIONS(1042), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(146), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17065] = 5,
    ACTIONS(1044), 1,
      anon_sym_DQUOTE,
    ACTIONS(1046), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(152), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17082] = 5,
    ACTIONS(1048), 1,
      anon_sym_DQUOTE,
    ACTIONS(1052), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(397), 1,
      sym_missing_string_end,
    STATE(556), 1,
      aux_sym__string_content,
    ACTIONS(1050), 2,
      sym_string_content,
      sym_escape_sequence,
  [17099] = 5,
    ACTIONS(1054), 1,
      anon_sym_DQUOTE,
    ACTIONS(1058), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(417), 1,
      sym_missing_string_end,
    STATE(555), 1,
      aux_sym__string_content,
    ACTIONS(1056), 2,
      sym_string_content,
      sym_escape_sequence,
  [17116] = 6,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1060), 1,
      anon_sym_ERROR_missing_iterator,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(314), 1,
      sym_missing_iterator,
    STATE(698), 1,
      sym_ident,
  [17135] = 5,
    ACTIONS(1046), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1062), 1,
      anon_sym_DQUOTE,
    STATE(138), 1,
      sym_missing_string_end,
    STATE(550), 1,
      aux_sym__string_content,
    ACTIONS(1064), 2,
      sym_string_content,
      sym_escape_sequence,
  [17152] = 5,
    ACTIONS(1058), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1066), 1,
      anon_sym_DQUOTE,
    STATE(477), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17169] = 5,
    ACTIONS(1052), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1068), 1,
      anon_sym_DQUOTE,
    STATE(373), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17186] = 6,
    ACTIONS(15), 1,
      anon_sym_DQUOTE_DQUOTE,
    ACTIONS(17), 1,
      anon_sym_DQUOTE,
    ACTIONS(29), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(141), 1,
      sym_missing_string_end,
    STATE(683), 1,
      sym_string,
    STATE(690), 1,
      sym_pair,
  [17205] = 5,
    ACTIONS(1042), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1070), 1,
      anon_sym_DQUOTE,
    STATE(139), 1,
      sym_missing_string_end,
    STATE(549), 1,
      aux_sym__string_content,
    ACTIONS(1072), 2,
      sym_string_content,
      sym_escape_sequence,
  [17222] = 5,
    ACTIONS(1074), 1,
      anon_sym_DQUOTE,
    ACTIONS(1078), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(78), 1,
      sym_missing_string_end,
    STATE(561), 1,
      aux_sym__string_content,
    ACTIONS(1076), 2,
      sym_string_content,
      sym_escape_sequence,
  [17239] = 5,
    ACTIONS(1080), 1,
      anon_sym_DQUOTE,
    ACTIONS(1084), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(483), 1,
      sym_missing_string_end,
    STATE(564), 1,
      aux_sym__string_content,
    ACTIONS(1082), 2,
      sym_string_content,
      sym_escape_sequence,
  [17256] = 5,
    ACTIONS(1078), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1086), 1,
      anon_sym_DQUOTE,
    STATE(74), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17273] = 6,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    ACTIONS(1088), 1,
      anon_sym_ERROR_missing_iterator,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(423), 1,
      sym_missing_iterator,
    STATE(696), 1,
      sym_ident,
  [17292] = 5,
    ACTIONS(1090), 1,
      anon_sym_DQUOTE,
    ACTIONS(1094), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(148), 1,
      sym_missing_string_end,
    STATE(566), 1,
      aux_sym__string_content,
    ACTIONS(1092), 2,
      sym_string_content,
      sym_escape_sequence,
  [17309] = 5,
    ACTIONS(1084), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1096), 1,
      anon_sym_DQUOTE,
    STATE(496), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17326] = 5,
    ACTIONS(1098), 1,
      anon_sym_DQUOTE,
    ACTIONS(1102), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(269), 1,
      sym_missing_string_end,
    STATE(567), 1,
      aux_sym__string_content,
    ACTIONS(1100), 2,
      sym_string_content,
      sym_escape_sequence,
  [17343] = 5,
    ACTIONS(1094), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1104), 1,
      anon_sym_DQUOTE,
    STATE(143), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17360] = 5,
    ACTIONS(1102), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1106), 1,
      anon_sym_DQUOTE,
    STATE(258), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17377] = 5,
    ACTIONS(1108), 1,
      anon_sym_DQUOTE,
    ACTIONS(1110), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(400), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17394] = 3,
    STATE(24), 1,
      sym__or,
    STATE(572), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(713), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [17407] = 5,
    ACTIONS(1112), 1,
      anon_sym_DQUOTE,
    ACTIONS(1116), 1,
      anon_sym_ERROR_missing_string_end,
    STATE(340), 1,
      sym_missing_string_end,
    STATE(573), 1,
      aux_sym__string_content,
    ACTIONS(1114), 2,
      sym_string_content,
      sym_escape_sequence,
  [17424] = 5,
    ACTIONS(1036), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1118), 1,
      anon_sym_DQUOTE,
    STATE(547), 1,
      aux_sym__string_content,
    STATE(707), 1,
      sym_missing_string_end,
    ACTIONS(1120), 2,
      sym_string_content,
      sym_escape_sequence,
  [17441] = 4,
    ACTIONS(1122), 1,
      anon_sym_or,
    STATE(24), 1,
      sym__or,
    STATE(572), 1,
      aux_sym_or_expression_repeat1,
    ACTIONS(690), 3,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
  [17456] = 5,
    ACTIONS(1116), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1125), 1,
      anon_sym_DQUOTE,
    STATE(334), 1,
      sym_missing_string_end,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1034), 2,
      sym_string_content,
      sym_escape_sequence,
  [17473] = 4,
    ACTIONS(1127), 1,
      anon_sym_and2,
    STATE(35), 1,
      sym__and,
    STATE(574), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(698), 3,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_or,
  [17488] = 3,
    STATE(35), 1,
      sym__and,
    STATE(574), 1,
      aux_sym_and_expression_repeat1,
    ACTIONS(720), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [17501] = 5,
    ACTIONS(1110), 1,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1130), 1,
      anon_sym_DQUOTE,
    STATE(384), 1,
      sym_missing_string_end,
    STATE(568), 1,
      aux_sym__string_content,
    ACTIONS(1132), 2,
      sym_string_content,
      sym_escape_sequence,
  [17518] = 5,
    ACTIONS(980), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1136), 1,
      anon_sym_RBRACE,
    STATE(209), 1,
      sym_missing_brace_end,
    STATE(603), 1,
      aux_sym_object_repeat1,
  [17534] = 5,
    ACTIONS(942), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1138), 1,
      anon_sym_RBRACE,
    STATE(332), 1,
      sym_missing_brace_end,
    STATE(595), 1,
      aux_sym_object_repeat1,
  [17550] = 4,
    ACTIONS(211), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(213), 1,
      anon_sym_for,
    STATE(553), 1,
      sym__for,
    STATE(55), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17564] = 5,
    ACTIONS(964), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1140), 1,
      anon_sym_RBRACE,
    STATE(588), 1,
      aux_sym_object_repeat1,
    STATE(645), 1,
      sym_missing_brace_end,
  [17580] = 5,
    ACTIONS(946), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1142), 1,
      anon_sym_RBRACE,
    STATE(120), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [17596] = 5,
    ACTIONS(938), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1144), 1,
      anon_sym_RBRACE,
    STATE(260), 1,
      sym_missing_brace_end,
    STATE(601), 1,
      aux_sym_object_repeat1,
  [17612] = 5,
    ACTIONS(972), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1146), 1,
      anon_sym_RBRACE,
    STATE(398), 1,
      sym_missing_brace_end,
    STATE(586), 1,
      aux_sym_object_repeat1,
  [17628] = 5,
    ACTIONS(175), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1148), 1,
      anon_sym_RBRACK,
    STATE(622), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [17644] = 5,
    ACTIONS(143), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1150), 1,
      anon_sym_RBRACK,
    STATE(181), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [17660] = 5,
    ACTIONS(972), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1152), 1,
      anon_sym_RBRACE,
    STATE(405), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [17676] = 5,
    ACTIONS(135), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(900), 1,
      anon_sym_RBRACK,
    STATE(454), 1,
      sym_missing_array_end,
    STATE(612), 1,
      aux_sym_array_repeat1,
  [17692] = 5,
    ACTIONS(964), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1154), 1,
      anon_sym_RBRACE,
    STATE(623), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [17708] = 1,
    ACTIONS(1156), 5,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_array_query_end,
      anon_sym_ERROR_missing_element_query_end,
  [17716] = 5,
    ACTIONS(181), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(904), 1,
      anon_sym_RBRACK,
    STATE(317), 1,
      sym_missing_array_end,
    STATE(611), 1,
      aux_sym_array_repeat1,
  [17732] = 4,
    ACTIONS(23), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(31), 1,
      anon_sym_for,
    STATE(562), 1,
      sym__for,
    STATE(66), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17746] = 5,
    ACTIONS(954), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1158), 1,
      anon_sym_RBRACE,
    STATE(176), 1,
      sym_missing_brace_end,
    STATE(607), 1,
      aux_sym_object_repeat1,
  [17762] = 4,
    ACTIONS(133), 1,
      anon_sym_ERROR_missing_main_iterator,
    ACTIONS(137), 1,
      anon_sym_for,
    STATE(548), 1,
      sym__for,
    STATE(73), 2,
      sym_iterator_stmt,
      sym_missing_main_iterator,
  [17776] = 5,
    ACTIONS(960), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1160), 1,
      anon_sym_RBRACE,
    STATE(431), 1,
      sym_missing_brace_end,
    STATE(608), 1,
      aux_sym_object_repeat1,
  [17792] = 5,
    ACTIONS(942), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1162), 1,
      anon_sym_RBRACE,
    STATE(342), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [17808] = 5,
    ACTIONS(157), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1164), 1,
      anon_sym_RBRACK,
    STATE(366), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [17824] = 5,
    ACTIONS(199), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1166), 1,
      anon_sym_RBRACK,
    STATE(350), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [17840] = 5,
    ACTIONS(193), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1168), 1,
      anon_sym_RBRACK,
    STATE(443), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [17856] = 5,
    ACTIONS(946), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1170), 1,
      anon_sym_RBRACE,
    STATE(113), 1,
      sym_missing_brace_end,
    STATE(581), 1,
      aux_sym_object_repeat1,
  [17872] = 5,
    ACTIONS(151), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1172), 1,
      anon_sym_RBRACK,
    STATE(130), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [17888] = 5,
    ACTIONS(938), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1174), 1,
      anon_sym_RBRACE,
    STATE(254), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [17904] = 5,
    ACTIONS(169), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1176), 1,
      anon_sym_RBRACK,
    STATE(200), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [17920] = 5,
    ACTIONS(980), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1178), 1,
      anon_sym_RBRACE,
    STATE(207), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [17936] = 5,
    ACTIONS(187), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1180), 1,
      anon_sym_RBRACK,
    STATE(248), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [17952] = 5,
    ACTIONS(163), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1182), 1,
      anon_sym_RBRACK,
    STATE(202), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [17968] = 5,
    ACTIONS(193), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(896), 1,
      anon_sym_RBRACK,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    STATE(452), 1,
      sym_missing_array_end,
    STATE(598), 1,
      aux_sym_array_repeat1,
  [17984] = 5,
    ACTIONS(954), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1184), 1,
      anon_sym_RBRACE,
    STATE(159), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [18000] = 5,
    ACTIONS(960), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1186), 1,
      anon_sym_RBRACE,
    STATE(438), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [18016] = 5,
    ACTIONS(968), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1188), 1,
      anon_sym_RBRACE,
    STATE(197), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [18032] = 5,
    ACTIONS(976), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1190), 1,
      anon_sym_RBRACE,
    STATE(378), 1,
      sym_missing_brace_end,
    STATE(613), 1,
      aux_sym_object_repeat1,
  [18048] = 5,
    ACTIONS(181), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1192), 1,
      anon_sym_RBRACK,
    STATE(310), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [18064] = 5,
    ACTIONS(135), 1,
      anon_sym_ERROR_missing_array_end,
    ACTIONS(898), 1,
      anon_sym_COMMA,
    ACTIONS(1194), 1,
      anon_sym_RBRACK,
    STATE(487), 1,
      sym_missing_array_end,
    STATE(629), 1,
      aux_sym_array_repeat1,
  [18080] = 5,
    ACTIONS(976), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1196), 1,
      anon_sym_RBRACE,
    STATE(372), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [18096] = 5,
    ACTIONS(950), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1198), 1,
      anon_sym_RBRACE,
    STATE(498), 1,
      sym_missing_brace_end,
    STATE(625), 1,
      aux_sym_object_repeat1,
  [18112] = 3,
    STATE(615), 1,
      aux_sym__string_content,
    ACTIONS(1200), 2,
      anon_sym_DQUOTE,
      anon_sym_ERROR_missing_string_end,
    ACTIONS(1202), 2,
      sym_string_content,
      sym_escape_sequence,
  [18124] = 5,
    ACTIONS(950), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1205), 1,
      anon_sym_RBRACE,
    STATE(495), 1,
      sym_missing_brace_end,
    STATE(614), 1,
      aux_sym_object_repeat1,
  [18140] = 5,
    ACTIONS(968), 1,
      anon_sym_ERROR_missing_brace_end,
    ACTIONS(1134), 1,
      anon_sym_COMMA,
    ACTIONS(1207), 1,
      anon_sym_RBRACE,
    STATE(190), 1,
      sym_missing_brace_end,
    STATE(609), 1,
      aux_sym_object_repeat1,
  [18156] = 1,
    ACTIONS(758), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18163] = 1,
    ACTIONS(624), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18170] = 4,
    ACTIONS(544), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(548), 1,
      aux_sym_ident_token1,
    STATE(231), 1,
      sym_ident,
    STATE(240), 1,
      sym_missing_identifier,
  [18183] = 4,
    ACTIONS(53), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(59), 1,
      aux_sym_ident_token1,
    STATE(125), 1,
      sym_missing_identifier,
    STATE(126), 1,
      sym_ident,
  [18196] = 1,
    ACTIONS(628), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18203] = 1,
    ACTIONS(612), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18210] = 1,
    ACTIONS(754), 4,
      anon_sym_and,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_brace_end,
  [18217] = 3,
    ACTIONS(1209), 1,
      anon_sym_COMMA,
    STATE(625), 1,
      aux_sym_object_repeat1,
    ACTIONS(1212), 2,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_brace_end,
  [18228] = 4,
    ACTIONS(101), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(107), 1,
      aux_sym_ident_token1,
    STATE(62), 1,
      sym_missing_identifier,
    STATE(63), 1,
      sym_ident,
  [18241] = 4,
    ACTIONS(77), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(83), 1,
      aux_sym_ident_token1,
    STATE(127), 1,
      sym_ident,
    STATE(133), 1,
      sym_missing_identifier,
  [18254] = 1,
    ACTIONS(766), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18261] = 3,
    ACTIONS(1216), 1,
      anon_sym_COMMA,
    STATE(629), 1,
      aux_sym_array_repeat1,
    ACTIONS(1214), 2,
      anon_sym_RBRACK,
      anon_sym_ERROR_missing_array_end,
  [18272] = 4,
    ACTIONS(586), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(590), 1,
      aux_sym_ident_token1,
    STATE(252), 1,
      sym_missing_identifier,
    STATE(257), 1,
      sym_ident,
  [18285] = 4,
    ACTIONS(484), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(488), 1,
      aux_sym_ident_token1,
    STATE(301), 1,
      sym_ident,
    STATE(305), 1,
      sym_missing_identifier,
  [18298] = 1,
    ACTIONS(754), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18305] = 4,
    ACTIONS(510), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(514), 1,
      aux_sym_ident_token1,
    STATE(377), 1,
      sym_missing_identifier,
    STATE(402), 1,
      sym_ident,
  [18318] = 4,
    ACTIONS(464), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(468), 1,
      aux_sym_ident_token1,
    STATE(298), 1,
      sym_missing_identifier,
    STATE(322), 1,
      sym_ident,
  [18331] = 1,
    ACTIONS(762), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18338] = 4,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(715), 1,
      sym_ident,
  [18351] = 1,
    ACTIONS(750), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18358] = 4,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(719), 1,
      sym_ident,
  [18371] = 4,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(117), 1,
      sym_ident,
  [18384] = 1,
    ACTIONS(600), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18391] = 1,
    ACTIONS(746), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18398] = 4,
    ACTIONS(437), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(441), 1,
      aux_sym_ident_token1,
    STATE(695), 1,
      sym_missing_identifier,
    STATE(700), 1,
      sym_ident,
  [18411] = 4,
    ACTIONS(27), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(35), 1,
      aux_sym_ident_token1,
    STATE(85), 1,
      sym_missing_identifier,
    STATE(706), 1,
      sym_ident,
  [18424] = 1,
    ACTIONS(742), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18431] = 1,
    ACTIONS(596), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18438] = 1,
    ACTIONS(592), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18445] = 1,
    ACTIONS(608), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18452] = 1,
    ACTIONS(644), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18459] = 1,
    ACTIONS(616), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18466] = 4,
    ACTIONS(562), 1,
      anon_sym_ERROR_missing_value,
    ACTIONS(566), 1,
      aux_sym_ident_token1,
    STATE(364), 1,
      sym_ident,
    STATE(412), 1,
      sym_missing_identifier,
  [18479] = 1,
    ACTIONS(632), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18486] = 1,
    ACTIONS(620), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18493] = 1,
    ACTIONS(636), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18500] = 1,
    ACTIONS(640), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18507] = 1,
    ACTIONS(636), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18514] = 1,
    ACTIONS(620), 4,
      anon_sym_RPAREN,
      anon_sym_ERROR_missing_parenthesis_end,
      anon_sym_and2,
      anon_sym_or,
  [18521] = 3,
    ACTIONS(1219), 1,
      anon_sym_EQ,
    ACTIONS(1221), 1,
      anon_sym_ERROR_missing_equals,
    STATE(108), 1,
      sym_missing_equals,
  [18531] = 3,
    ACTIONS(284), 1,
      anon_sym_and,
    ACTIONS(1223), 1,
      anon_sym_DOT,
    STATE(658), 1,
      aux_sym_path_repeat1,
  [18541] = 3,
    ACTIONS(1226), 1,
      anon_sym_RBRACK,
    ACTIONS(1228), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(388), 1,
      sym_missing_array_query_end,
  [18551] = 3,
    ACTIONS(1230), 1,
      anon_sym_RPAREN,
    ACTIONS(1232), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(393), 1,
      sym_missing_element_query_end,
  [18561] = 3,
    ACTIONS(1234), 1,
      sym_pos_int,
    ACTIONS(1236), 1,
      anon_sym_ERROR_missing_limit_value,
    STATE(434), 1,
      sym_missing_limit_value,
  [18571] = 3,
    ACTIONS(1238), 1,
      anon_sym_RPAREN,
    ACTIONS(1240), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(135), 1,
      sym_missing_element_query_end,
  [18581] = 3,
    ACTIONS(1242), 1,
      anon_sym_RBRACK,
    ACTIONS(1244), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(129), 1,
      sym_missing_array_query_end,
  [18591] = 3,
    ACTIONS(1246), 1,
      anon_sym_RBRACK,
    ACTIONS(1248), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(656), 1,
      sym_missing_array_query_end,
  [18601] = 3,
    ACTIONS(1250), 1,
      anon_sym_RPAREN,
    ACTIONS(1252), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(653), 1,
      sym_missing_element_query_end,
  [18611] = 3,
    ACTIONS(291), 1,
      anon_sym_and,
    ACTIONS(1254), 1,
      anon_sym_DOT,
    STATE(658), 1,
      aux_sym_path_repeat1,
  [18621] = 3,
    ACTIONS(278), 1,
      anon_sym_and,
    ACTIONS(1254), 1,
      anon_sym_DOT,
    STATE(666), 1,
      aux_sym_path_repeat1,
  [18631] = 3,
    ACTIONS(1256), 1,
      anon_sym_RBRACK,
    ACTIONS(1258), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(416), 1,
      sym_missing_array_query_end,
  [18641] = 3,
    ACTIONS(1260), 1,
      anon_sym_RPAREN,
    ACTIONS(1262), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(426), 1,
      sym_missing_element_query_end,
  [18651] = 3,
    ACTIONS(1264), 1,
      anon_sym_RPAREN,
    ACTIONS(1266), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(171), 1,
      sym_missing_element_query_end,
  [18661] = 3,
    ACTIONS(1028), 1,
      anon_sym_ERROR_missing_element_query_end,
    ACTIONS(1268), 1,
      anon_sym_RPAREN,
    STATE(192), 1,
      sym_missing_element_query_end,
  [18671] = 3,
    ACTIONS(1270), 1,
      anon_sym_RBRACK,
    ACTIONS(1272), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(389), 1,
      sym_missing_array_query_end,
  [18681] = 3,
    ACTIONS(1274), 1,
      anon_sym_RPAREN,
    ACTIONS(1276), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(380), 1,
      sym_missing_element_query_end,
  [18691] = 3,
    ACTIONS(1221), 1,
      anon_sym_ERROR_missing_equals,
    ACTIONS(1278), 1,
      anon_sym_EQ,
    STATE(111), 1,
      sym_missing_equals,
  [18701] = 1,
    ACTIONS(1280), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_brace_end,
  [18707] = 3,
    ACTIONS(1282), 1,
      sym_pos_int,
    ACTIONS(1284), 1,
      anon_sym_ERROR_missing_offset_value,
    STATE(437), 1,
      sym_missing_offset_value,
  [18717] = 3,
    ACTIONS(1221), 1,
      anon_sym_ERROR_missing_equals,
    ACTIONS(1286), 1,
      anon_sym_EQ,
    STATE(99), 1,
      sym_missing_equals,
  [18727] = 3,
    ACTIONS(1026), 1,
      anon_sym_ERROR_missing_array_query_end,
    ACTIONS(1288), 1,
      anon_sym_RBRACK,
    STATE(184), 1,
      sym_missing_array_query_end,
  [18737] = 3,
    ACTIONS(1290), 1,
      anon_sym_RBRACK,
    ACTIONS(1292), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(486), 1,
      sym_missing_array_query_end,
  [18747] = 3,
    ACTIONS(1294), 1,
      anon_sym_RPAREN,
    ACTIONS(1296), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(491), 1,
      sym_missing_element_query_end,
  [18757] = 3,
    ACTIONS(1298), 1,
      sym_pos_int,
    ACTIONS(1300), 1,
      anon_sym_ERROR_missing_limit_value,
    STATE(297), 1,
      sym_missing_limit_value,
  [18767] = 3,
    ACTIONS(1302), 1,
      sym_pos_int,
    ACTIONS(1304), 1,
      anon_sym_ERROR_missing_offset_value,
    STATE(320), 1,
      sym_missing_offset_value,
  [18777] = 3,
    ACTIONS(1306), 1,
      anon_sym_COLON,
    ACTIONS(1308), 1,
      anon_sym_ERROR_missing_colon,
    STATE(92), 1,
      sym_missing_colon,
  [18787] = 3,
    ACTIONS(1310), 1,
      sym_pos_int,
    ACTIONS(1312), 1,
      anon_sym_ERROR_missing_limit_value,
    STATE(482), 1,
      sym_missing_limit_value,
  [18797] = 1,
    ACTIONS(1214), 3,
      anon_sym_RBRACK,
      anon_sym_COMMA,
      anon_sym_ERROR_missing_array_end,
  [18803] = 3,
    ACTIONS(1314), 1,
      anon_sym_RBRACK,
    ACTIONS(1316), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(266), 1,
      sym_missing_array_query_end,
  [18813] = 3,
    ACTIONS(1318), 1,
      anon_sym_RPAREN,
    ACTIONS(1320), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(263), 1,
      sym_missing_element_query_end,
  [18823] = 3,
    ACTIONS(1322), 1,
      sym_pos_int,
    ACTIONS(1324), 1,
      anon_sym_ERROR_missing_offset_value,
    STATE(474), 1,
      sym_missing_offset_value,
  [18833] = 3,
    ACTIONS(1326), 1,
      anon_sym_RPAREN,
    ACTIONS(1328), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(187), 1,
      sym_missing_element_query_end,
  [18843] = 1,
    ACTIONS(1212), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_ERROR_missing_brace_end,
  [18849] = 3,
    ACTIONS(1330), 1,
      anon_sym_RBRACK,
    ACTIONS(1332), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(162), 1,
      sym_missing_array_query_end,
  [18859] = 3,
    ACTIONS(1334), 1,
      anon_sym_RBRACK,
    ACTIONS(1336), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(315), 1,
      sym_missing_array_query_end,
  [18869] = 3,
    ACTIONS(1338), 1,
      anon_sym_RPAREN,
    ACTIONS(1340), 1,
      anon_sym_ERROR_missing_element_query_end,
    STATE(328), 1,
      sym_missing_element_query_end,
  [18879] = 3,
    ACTIONS(1342), 1,
      anon_sym_RBRACK,
    ACTIONS(1344), 1,
      anon_sym_ERROR_missing_array_query_end,
    STATE(168), 1,
      sym_missing_array_query_end,
  [18889] = 1,
    ACTIONS(299), 2,
      anon_sym_and,
      anon_sym_DOT,
  [18894] = 2,
    ACTIONS(1346), 1,
      anon_sym_in,
    STATE(542), 1,
      sym__in,
  [18901] = 1,
    ACTIONS(295), 2,
      anon_sym_and,
      anon_sym_DOT,
  [18906] = 2,
    ACTIONS(1348), 1,
      anon_sym_in,
    STATE(539), 1,
      sym__in,
  [18913] = 2,
    ACTIONS(1350), 1,
      anon_sym_in,
    STATE(537), 1,
      sym__in,
  [18920] = 1,
    ACTIONS(284), 2,
      anon_sym_and,
      anon_sym_DOT,
  [18925] = 1,
    ACTIONS(1352), 1,
      anon_sym_and,
  [18929] = 1,
    ACTIONS(1354), 1,
      anon_sym_and,
  [18933] = 1,
    ACTIONS(1356), 1,
      anon_sym_EQ,
  [18937] = 1,
    ACTIONS(385), 1,
      anon_sym_and,
  [18941] = 1,
    ACTIONS(369), 1,
      anon_sym_and,
  [18945] = 1,
    ACTIONS(1358), 1,
      anon_sym_EQ,
  [18949] = 1,
    ACTIONS(395), 1,
      anon_sym_and,
  [18953] = 1,
    ACTIONS(381), 1,
      anon_sym_and,
  [18957] = 1,
    ACTIONS(1360), 1,
      ts_builtin_sym_end,
  [18961] = 1,
    ACTIONS(1362), 1,
      anon_sym_EQ,
  [18965] = 1,
    ACTIONS(1360), 1,
      ts_builtin_sym_end,
  [18969] = 1,
    ACTIONS(604), 1,
      anon_sym_and,
  [18973] = 1,
    ACTIONS(1360), 1,
      ts_builtin_sym_end,
  [18977] = 1,
    ACTIONS(1364), 1,
      anon_sym_and,
  [18981] = 1,
    ACTIONS(1366), 1,
      anon_sym_EQ,
  [18985] = 1,
    ACTIONS(1368), 1,
      anon_sym_EQ,
  [18989] = 1,
    ACTIONS(1370), 1,
      anon_sym_and,
  [18993] = 1,
    ACTIONS(1360), 1,
      ts_builtin_sym_end,
  [18997] = 1,
    ACTIONS(1372), 1,
      anon_sym_EQ,
  [19001] = 1,
    ACTIONS(1374), 1,
      ts_builtin_sym_end,
  [19005] = 1,
    ACTIONS(1376), 1,
      ts_builtin_sym_end,
  [19009] = 1,
    ACTIONS(1378), 1,
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
  [SMALL_STATE(16)] = 1202,
  [SMALL_STATE(17)] = 1280,
  [SMALL_STATE(18)] = 1358,
  [SMALL_STATE(19)] = 1430,
  [SMALL_STATE(20)] = 1510,
  [SMALL_STATE(21)] = 1582,
  [SMALL_STATE(22)] = 1654,
  [SMALL_STATE(23)] = 1726,
  [SMALL_STATE(24)] = 1806,
  [SMALL_STATE(25)] = 1878,
  [SMALL_STATE(26)] = 1958,
  [SMALL_STATE(27)] = 2038,
  [SMALL_STATE(28)] = 2110,
  [SMALL_STATE(29)] = 2190,
  [SMALL_STATE(30)] = 2262,
  [SMALL_STATE(31)] = 2334,
  [SMALL_STATE(32)] = 2414,
  [SMALL_STATE(33)] = 2494,
  [SMALL_STATE(34)] = 2574,
  [SMALL_STATE(35)] = 2646,
  [SMALL_STATE(36)] = 2718,
  [SMALL_STATE(37)] = 2798,
  [SMALL_STATE(38)] = 2878,
  [SMALL_STATE(39)] = 2950,
  [SMALL_STATE(40)] = 3030,
  [SMALL_STATE(41)] = 3102,
  [SMALL_STATE(42)] = 3173,
  [SMALL_STATE(43)] = 3244,
  [SMALL_STATE(44)] = 3315,
  [SMALL_STATE(45)] = 3386,
  [SMALL_STATE(46)] = 3457,
  [SMALL_STATE(47)] = 3528,
  [SMALL_STATE(48)] = 3599,
  [SMALL_STATE(49)] = 3670,
  [SMALL_STATE(50)] = 3741,
  [SMALL_STATE(51)] = 3812,
  [SMALL_STATE(52)] = 3883,
  [SMALL_STATE(53)] = 3954,
  [SMALL_STATE(54)] = 4026,
  [SMALL_STATE(55)] = 4098,
  [SMALL_STATE(56)] = 4170,
  [SMALL_STATE(57)] = 4242,
  [SMALL_STATE(58)] = 4314,
  [SMALL_STATE(59)] = 4353,
  [SMALL_STATE(60)] = 4392,
  [SMALL_STATE(61)] = 4431,
  [SMALL_STATE(62)] = 4465,
  [SMALL_STATE(63)] = 4499,
  [SMALL_STATE(64)] = 4533,
  [SMALL_STATE(65)] = 4602,
  [SMALL_STATE(66)] = 4671,
  [SMALL_STATE(67)] = 4740,
  [SMALL_STATE(68)] = 4809,
  [SMALL_STATE(69)] = 4878,
  [SMALL_STATE(70)] = 4911,
  [SMALL_STATE(71)] = 4980,
  [SMALL_STATE(72)] = 5017,
  [SMALL_STATE(73)] = 5050,
  [SMALL_STATE(74)] = 5119,
  [SMALL_STATE(75)] = 5152,
  [SMALL_STATE(76)] = 5221,
  [SMALL_STATE(77)] = 5290,
  [SMALL_STATE(78)] = 5329,
  [SMALL_STATE(79)] = 5362,
  [SMALL_STATE(80)] = 5431,
  [SMALL_STATE(81)] = 5467,
  [SMALL_STATE(82)] = 5509,
  [SMALL_STATE(83)] = 5545,
  [SMALL_STATE(84)] = 5601,
  [SMALL_STATE(85)] = 5637,
  [SMALL_STATE(86)] = 5669,
  [SMALL_STATE(87)] = 5725,
  [SMALL_STATE(88)] = 5781,
  [SMALL_STATE(89)] = 5817,
  [SMALL_STATE(90)] = 5849,
  [SMALL_STATE(91)] = 5885,
  [SMALL_STATE(92)] = 5921,
  [SMALL_STATE(93)] = 5977,
  [SMALL_STATE(94)] = 6013,
  [SMALL_STATE(95)] = 6069,
  [SMALL_STATE(96)] = 6125,
  [SMALL_STATE(97)] = 6161,
  [SMALL_STATE(98)] = 6221,
  [SMALL_STATE(99)] = 6257,
  [SMALL_STATE(100)] = 6313,
  [SMALL_STATE(101)] = 6369,
  [SMALL_STATE(102)] = 6429,
  [SMALL_STATE(103)] = 6485,
  [SMALL_STATE(104)] = 6541,
  [SMALL_STATE(105)] = 6597,
  [SMALL_STATE(106)] = 6657,
  [SMALL_STATE(107)] = 6713,
  [SMALL_STATE(108)] = 6769,
  [SMALL_STATE(109)] = 6825,
  [SMALL_STATE(110)] = 6867,
  [SMALL_STATE(111)] = 6923,
  [SMALL_STATE(112)] = 6979,
  [SMALL_STATE(113)] = 7010,
  [SMALL_STATE(114)] = 7041,
  [SMALL_STATE(115)] = 7072,
  [SMALL_STATE(116)] = 7103,
  [SMALL_STATE(117)] = 7134,
  [SMALL_STATE(118)] = 7165,
  [SMALL_STATE(119)] = 7200,
  [SMALL_STATE(120)] = 7235,
  [SMALL_STATE(121)] = 7266,
  [SMALL_STATE(122)] = 7297,
  [SMALL_STATE(123)] = 7328,
  [SMALL_STATE(124)] = 7359,
  [SMALL_STATE(125)] = 7390,
  [SMALL_STATE(126)] = 7421,
  [SMALL_STATE(127)] = 7452,
  [SMALL_STATE(128)] = 7483,
  [SMALL_STATE(129)] = 7514,
  [SMALL_STATE(130)] = 7545,
  [SMALL_STATE(131)] = 7576,
  [SMALL_STATE(132)] = 7607,
  [SMALL_STATE(133)] = 7638,
  [SMALL_STATE(134)] = 7669,
  [SMALL_STATE(135)] = 7700,
  [SMALL_STATE(136)] = 7731,
  [SMALL_STATE(137)] = 7762,
  [SMALL_STATE(138)] = 7798,
  [SMALL_STATE(139)] = 7828,
  [SMALL_STATE(140)] = 7858,
  [SMALL_STATE(141)] = 7888,
  [SMALL_STATE(142)] = 7918,
  [SMALL_STATE(143)] = 7948,
  [SMALL_STATE(144)] = 7978,
  [SMALL_STATE(145)] = 8012,
  [SMALL_STATE(146)] = 8042,
  [SMALL_STATE(147)] = 8072,
  [SMALL_STATE(148)] = 8102,
  [SMALL_STATE(149)] = 8132,
  [SMALL_STATE(150)] = 8166,
  [SMALL_STATE(151)] = 8202,
  [SMALL_STATE(152)] = 8232,
  [SMALL_STATE(153)] = 8262,
  [SMALL_STATE(154)] = 8313,
  [SMALL_STATE(155)] = 8352,
  [SMALL_STATE(156)] = 8391,
  [SMALL_STATE(157)] = 8430,
  [SMALL_STATE(158)] = 8469,
  [SMALL_STATE(159)] = 8501,
  [SMALL_STATE(160)] = 8529,
  [SMALL_STATE(161)] = 8557,
  [SMALL_STATE(162)] = 8585,
  [SMALL_STATE(163)] = 8613,
  [SMALL_STATE(164)] = 8641,
  [SMALL_STATE(165)] = 8669,
  [SMALL_STATE(166)] = 8697,
  [SMALL_STATE(167)] = 8725,
  [SMALL_STATE(168)] = 8753,
  [SMALL_STATE(169)] = 8781,
  [SMALL_STATE(170)] = 8809,
  [SMALL_STATE(171)] = 8837,
  [SMALL_STATE(172)] = 8865,
  [SMALL_STATE(173)] = 8893,
  [SMALL_STATE(174)] = 8921,
  [SMALL_STATE(175)] = 8949,
  [SMALL_STATE(176)] = 8977,
  [SMALL_STATE(177)] = 9005,
  [SMALL_STATE(178)] = 9033,
  [SMALL_STATE(179)] = 9061,
  [SMALL_STATE(180)] = 9089,
  [SMALL_STATE(181)] = 9121,
  [SMALL_STATE(182)] = 9149,
  [SMALL_STATE(183)] = 9177,
  [SMALL_STATE(184)] = 9205,
  [SMALL_STATE(185)] = 9233,
  [SMALL_STATE(186)] = 9261,
  [SMALL_STATE(187)] = 9289,
  [SMALL_STATE(188)] = 9317,
  [SMALL_STATE(189)] = 9345,
  [SMALL_STATE(190)] = 9373,
  [SMALL_STATE(191)] = 9401,
  [SMALL_STATE(192)] = 9429,
  [SMALL_STATE(193)] = 9457,
  [SMALL_STATE(194)] = 9485,
  [SMALL_STATE(195)] = 9517,
  [SMALL_STATE(196)] = 9545,
  [SMALL_STATE(197)] = 9577,
  [SMALL_STATE(198)] = 9605,
  [SMALL_STATE(199)] = 9633,
  [SMALL_STATE(200)] = 9661,
  [SMALL_STATE(201)] = 9689,
  [SMALL_STATE(202)] = 9716,
  [SMALL_STATE(203)] = 9743,
  [SMALL_STATE(204)] = 9770,
  [SMALL_STATE(205)] = 9797,
  [SMALL_STATE(206)] = 9824,
  [SMALL_STATE(207)] = 9851,
  [SMALL_STATE(208)] = 9878,
  [SMALL_STATE(209)] = 9905,
  [SMALL_STATE(210)] = 9932,
  [SMALL_STATE(211)] = 9978,
  [SMALL_STATE(212)] = 10024,
  [SMALL_STATE(213)] = 10070,
  [SMALL_STATE(214)] = 10116,
  [SMALL_STATE(215)] = 10153,
  [SMALL_STATE(216)] = 10190,
  [SMALL_STATE(217)] = 10227,
  [SMALL_STATE(218)] = 10264,
  [SMALL_STATE(219)] = 10301,
  [SMALL_STATE(220)] = 10334,
  [SMALL_STATE(221)] = 10363,
  [SMALL_STATE(222)] = 10390,
  [SMALL_STATE(223)] = 10417,
  [SMALL_STATE(224)] = 10444,
  [SMALL_STATE(225)] = 10471,
  [SMALL_STATE(226)] = 10498,
  [SMALL_STATE(227)] = 10527,
  [SMALL_STATE(228)] = 10554,
  [SMALL_STATE(229)] = 10588,
  [SMALL_STATE(230)] = 10618,
  [SMALL_STATE(231)] = 10648,
  [SMALL_STATE(232)] = 10670,
  [SMALL_STATE(233)] = 10704,
  [SMALL_STATE(234)] = 10738,
  [SMALL_STATE(235)] = 10764,
  [SMALL_STATE(236)] = 10798,
  [SMALL_STATE(237)] = 10832,
  [SMALL_STATE(238)] = 10866,
  [SMALL_STATE(239)] = 10900,
  [SMALL_STATE(240)] = 10934,
  [SMALL_STATE(241)] = 10956,
  [SMALL_STATE(242)] = 10978,
  [SMALL_STATE(243)] = 11004,
  [SMALL_STATE(244)] = 11038,
  [SMALL_STATE(245)] = 11064,
  [SMALL_STATE(246)] = 11098,
  [SMALL_STATE(247)] = 11119,
  [SMALL_STATE(248)] = 11140,
  [SMALL_STATE(249)] = 11161,
  [SMALL_STATE(250)] = 11182,
  [SMALL_STATE(251)] = 11203,
  [SMALL_STATE(252)] = 11224,
  [SMALL_STATE(253)] = 11245,
  [SMALL_STATE(254)] = 11266,
  [SMALL_STATE(255)] = 11287,
  [SMALL_STATE(256)] = 11308,
  [SMALL_STATE(257)] = 11329,
  [SMALL_STATE(258)] = 11350,
  [SMALL_STATE(259)] = 11371,
  [SMALL_STATE(260)] = 11392,
  [SMALL_STATE(261)] = 11413,
  [SMALL_STATE(262)] = 11434,
  [SMALL_STATE(263)] = 11455,
  [SMALL_STATE(264)] = 11476,
  [SMALL_STATE(265)] = 11497,
  [SMALL_STATE(266)] = 11518,
  [SMALL_STATE(267)] = 11539,
  [SMALL_STATE(268)] = 11560,
  [SMALL_STATE(269)] = 11581,
  [SMALL_STATE(270)] = 11602,
  [SMALL_STATE(271)] = 11623,
  [SMALL_STATE(272)] = 11644,
  [SMALL_STATE(273)] = 11665,
  [SMALL_STATE(274)] = 11688,
  [SMALL_STATE(275)] = 11709,
  [SMALL_STATE(276)] = 11730,
  [SMALL_STATE(277)] = 11751,
  [SMALL_STATE(278)] = 11775,
  [SMALL_STATE(279)] = 11799,
  [SMALL_STATE(280)] = 11825,
  [SMALL_STATE(281)] = 11851,
  [SMALL_STATE(282)] = 11875,
  [SMALL_STATE(283)] = 11899,
  [SMALL_STATE(284)] = 11923,
  [SMALL_STATE(285)] = 11943,
  [SMALL_STATE(286)] = 11967,
  [SMALL_STATE(287)] = 11991,
  [SMALL_STATE(288)] = 12013,
  [SMALL_STATE(289)] = 12039,
  [SMALL_STATE(290)] = 12065,
  [SMALL_STATE(291)] = 12089,
  [SMALL_STATE(292)] = 12113,
  [SMALL_STATE(293)] = 12137,
  [SMALL_STATE(294)] = 12156,
  [SMALL_STATE(295)] = 12175,
  [SMALL_STATE(296)] = 12194,
  [SMALL_STATE(297)] = 12213,
  [SMALL_STATE(298)] = 12232,
  [SMALL_STATE(299)] = 12251,
  [SMALL_STATE(300)] = 12274,
  [SMALL_STATE(301)] = 12293,
  [SMALL_STATE(302)] = 12312,
  [SMALL_STATE(303)] = 12331,
  [SMALL_STATE(304)] = 12350,
  [SMALL_STATE(305)] = 12369,
  [SMALL_STATE(306)] = 12388,
  [SMALL_STATE(307)] = 12407,
  [SMALL_STATE(308)] = 12426,
  [SMALL_STATE(309)] = 12445,
  [SMALL_STATE(310)] = 12464,
  [SMALL_STATE(311)] = 12483,
  [SMALL_STATE(312)] = 12506,
  [SMALL_STATE(313)] = 12525,
  [SMALL_STATE(314)] = 12544,
  [SMALL_STATE(315)] = 12563,
  [SMALL_STATE(316)] = 12582,
  [SMALL_STATE(317)] = 12601,
  [SMALL_STATE(318)] = 12620,
  [SMALL_STATE(319)] = 12639,
  [SMALL_STATE(320)] = 12658,
  [SMALL_STATE(321)] = 12677,
  [SMALL_STATE(322)] = 12696,
  [SMALL_STATE(323)] = 12715,
  [SMALL_STATE(324)] = 12734,
  [SMALL_STATE(325)] = 12753,
  [SMALL_STATE(326)] = 12772,
  [SMALL_STATE(327)] = 12791,
  [SMALL_STATE(328)] = 12810,
  [SMALL_STATE(329)] = 12829,
  [SMALL_STATE(330)] = 12852,
  [SMALL_STATE(331)] = 12871,
  [SMALL_STATE(332)] = 12890,
  [SMALL_STATE(333)] = 12909,
  [SMALL_STATE(334)] = 12928,
  [SMALL_STATE(335)] = 12947,
  [SMALL_STATE(336)] = 12970,
  [SMALL_STATE(337)] = 12989,
  [SMALL_STATE(338)] = 13008,
  [SMALL_STATE(339)] = 13027,
  [SMALL_STATE(340)] = 13046,
  [SMALL_STATE(341)] = 13065,
  [SMALL_STATE(342)] = 13088,
  [SMALL_STATE(343)] = 13107,
  [SMALL_STATE(344)] = 13130,
  [SMALL_STATE(345)] = 13149,
  [SMALL_STATE(346)] = 13168,
  [SMALL_STATE(347)] = 13187,
  [SMALL_STATE(348)] = 13205,
  [SMALL_STATE(349)] = 13223,
  [SMALL_STATE(350)] = 13247,
  [SMALL_STATE(351)] = 13265,
  [SMALL_STATE(352)] = 13283,
  [SMALL_STATE(353)] = 13307,
  [SMALL_STATE(354)] = 13325,
  [SMALL_STATE(355)] = 13343,
  [SMALL_STATE(356)] = 13361,
  [SMALL_STATE(357)] = 13379,
  [SMALL_STATE(358)] = 13397,
  [SMALL_STATE(359)] = 13415,
  [SMALL_STATE(360)] = 13433,
  [SMALL_STATE(361)] = 13451,
  [SMALL_STATE(362)] = 13469,
  [SMALL_STATE(363)] = 13487,
  [SMALL_STATE(364)] = 13505,
  [SMALL_STATE(365)] = 13523,
  [SMALL_STATE(366)] = 13541,
  [SMALL_STATE(367)] = 13559,
  [SMALL_STATE(368)] = 13577,
  [SMALL_STATE(369)] = 13595,
  [SMALL_STATE(370)] = 13613,
  [SMALL_STATE(371)] = 13631,
  [SMALL_STATE(372)] = 13649,
  [SMALL_STATE(373)] = 13667,
  [SMALL_STATE(374)] = 13685,
  [SMALL_STATE(375)] = 13703,
  [SMALL_STATE(376)] = 13721,
  [SMALL_STATE(377)] = 13739,
  [SMALL_STATE(378)] = 13757,
  [SMALL_STATE(379)] = 13775,
  [SMALL_STATE(380)] = 13793,
  [SMALL_STATE(381)] = 13811,
  [SMALL_STATE(382)] = 13829,
  [SMALL_STATE(383)] = 13847,
  [SMALL_STATE(384)] = 13865,
  [SMALL_STATE(385)] = 13883,
  [SMALL_STATE(386)] = 13901,
  [SMALL_STATE(387)] = 13919,
  [SMALL_STATE(388)] = 13937,
  [SMALL_STATE(389)] = 13955,
  [SMALL_STATE(390)] = 13973,
  [SMALL_STATE(391)] = 13991,
  [SMALL_STATE(392)] = 14009,
  [SMALL_STATE(393)] = 14027,
  [SMALL_STATE(394)] = 14045,
  [SMALL_STATE(395)] = 14063,
  [SMALL_STATE(396)] = 14081,
  [SMALL_STATE(397)] = 14099,
  [SMALL_STATE(398)] = 14117,
  [SMALL_STATE(399)] = 14135,
  [SMALL_STATE(400)] = 14153,
  [SMALL_STATE(401)] = 14171,
  [SMALL_STATE(402)] = 14189,
  [SMALL_STATE(403)] = 14207,
  [SMALL_STATE(404)] = 14225,
  [SMALL_STATE(405)] = 14243,
  [SMALL_STATE(406)] = 14261,
  [SMALL_STATE(407)] = 14279,
  [SMALL_STATE(408)] = 14303,
  [SMALL_STATE(409)] = 14321,
  [SMALL_STATE(410)] = 14339,
  [SMALL_STATE(411)] = 14357,
  [SMALL_STATE(412)] = 14381,
  [SMALL_STATE(413)] = 14399,
  [SMALL_STATE(414)] = 14418,
  [SMALL_STATE(415)] = 14437,
  [SMALL_STATE(416)] = 14453,
  [SMALL_STATE(417)] = 14469,
  [SMALL_STATE(418)] = 14485,
  [SMALL_STATE(419)] = 14501,
  [SMALL_STATE(420)] = 14517,
  [SMALL_STATE(421)] = 14533,
  [SMALL_STATE(422)] = 14549,
  [SMALL_STATE(423)] = 14565,
  [SMALL_STATE(424)] = 14581,
  [SMALL_STATE(425)] = 14597,
  [SMALL_STATE(426)] = 14613,
  [SMALL_STATE(427)] = 14629,
  [SMALL_STATE(428)] = 14645,
  [SMALL_STATE(429)] = 14661,
  [SMALL_STATE(430)] = 14677,
  [SMALL_STATE(431)] = 14693,
  [SMALL_STATE(432)] = 14709,
  [SMALL_STATE(433)] = 14725,
  [SMALL_STATE(434)] = 14741,
  [SMALL_STATE(435)] = 14757,
  [SMALL_STATE(436)] = 14773,
  [SMALL_STATE(437)] = 14789,
  [SMALL_STATE(438)] = 14805,
  [SMALL_STATE(439)] = 14821,
  [SMALL_STATE(440)] = 14837,
  [SMALL_STATE(441)] = 14853,
  [SMALL_STATE(442)] = 14869,
  [SMALL_STATE(443)] = 14885,
  [SMALL_STATE(444)] = 14901,
  [SMALL_STATE(445)] = 14917,
  [SMALL_STATE(446)] = 14933,
  [SMALL_STATE(447)] = 14949,
  [SMALL_STATE(448)] = 14965,
  [SMALL_STATE(449)] = 14981,
  [SMALL_STATE(450)] = 14997,
  [SMALL_STATE(451)] = 15013,
  [SMALL_STATE(452)] = 15029,
  [SMALL_STATE(453)] = 15045,
  [SMALL_STATE(454)] = 15061,
  [SMALL_STATE(455)] = 15077,
  [SMALL_STATE(456)] = 15093,
  [SMALL_STATE(457)] = 15109,
  [SMALL_STATE(458)] = 15125,
  [SMALL_STATE(459)] = 15141,
  [SMALL_STATE(460)] = 15157,
  [SMALL_STATE(461)] = 15173,
  [SMALL_STATE(462)] = 15189,
  [SMALL_STATE(463)] = 15205,
  [SMALL_STATE(464)] = 15221,
  [SMALL_STATE(465)] = 15237,
  [SMALL_STATE(466)] = 15253,
  [SMALL_STATE(467)] = 15269,
  [SMALL_STATE(468)] = 15285,
  [SMALL_STATE(469)] = 15301,
  [SMALL_STATE(470)] = 15317,
  [SMALL_STATE(471)] = 15333,
  [SMALL_STATE(472)] = 15349,
  [SMALL_STATE(473)] = 15365,
  [SMALL_STATE(474)] = 15381,
  [SMALL_STATE(475)] = 15397,
  [SMALL_STATE(476)] = 15413,
  [SMALL_STATE(477)] = 15429,
  [SMALL_STATE(478)] = 15445,
  [SMALL_STATE(479)] = 15461,
  [SMALL_STATE(480)] = 15477,
  [SMALL_STATE(481)] = 15493,
  [SMALL_STATE(482)] = 15509,
  [SMALL_STATE(483)] = 15525,
  [SMALL_STATE(484)] = 15541,
  [SMALL_STATE(485)] = 15557,
  [SMALL_STATE(486)] = 15573,
  [SMALL_STATE(487)] = 15589,
  [SMALL_STATE(488)] = 15605,
  [SMALL_STATE(489)] = 15621,
  [SMALL_STATE(490)] = 15637,
  [SMALL_STATE(491)] = 15653,
  [SMALL_STATE(492)] = 15669,
  [SMALL_STATE(493)] = 15685,
  [SMALL_STATE(494)] = 15701,
  [SMALL_STATE(495)] = 15717,
  [SMALL_STATE(496)] = 15733,
  [SMALL_STATE(497)] = 15749,
  [SMALL_STATE(498)] = 15765,
  [SMALL_STATE(499)] = 15781,
  [SMALL_STATE(500)] = 15810,
  [SMALL_STATE(501)] = 15839,
  [SMALL_STATE(502)] = 15868,
  [SMALL_STATE(503)] = 15897,
  [SMALL_STATE(504)] = 15926,
  [SMALL_STATE(505)] = 15955,
  [SMALL_STATE(506)] = 15984,
  [SMALL_STATE(507)] = 16013,
  [SMALL_STATE(508)] = 16042,
  [SMALL_STATE(509)] = 16071,
  [SMALL_STATE(510)] = 16100,
  [SMALL_STATE(511)] = 16128,
  [SMALL_STATE(512)] = 16156,
  [SMALL_STATE(513)] = 16184,
  [SMALL_STATE(514)] = 16212,
  [SMALL_STATE(515)] = 16240,
  [SMALL_STATE(516)] = 16268,
  [SMALL_STATE(517)] = 16296,
  [SMALL_STATE(518)] = 16324,
  [SMALL_STATE(519)] = 16352,
  [SMALL_STATE(520)] = 16380,
  [SMALL_STATE(521)] = 16408,
  [SMALL_STATE(522)] = 16436,
  [SMALL_STATE(523)] = 16464,
  [SMALL_STATE(524)] = 16492,
  [SMALL_STATE(525)] = 16520,
  [SMALL_STATE(526)] = 16543,
  [SMALL_STATE(527)] = 16566,
  [SMALL_STATE(528)] = 16589,
  [SMALL_STATE(529)] = 16612,
  [SMALL_STATE(530)] = 16635,
  [SMALL_STATE(531)] = 16654,
  [SMALL_STATE(532)] = 16677,
  [SMALL_STATE(533)] = 16700,
  [SMALL_STATE(534)] = 16723,
  [SMALL_STATE(535)] = 16746,
  [SMALL_STATE(536)] = 16769,
  [SMALL_STATE(537)] = 16792,
  [SMALL_STATE(538)] = 16814,
  [SMALL_STATE(539)] = 16836,
  [SMALL_STATE(540)] = 16858,
  [SMALL_STATE(541)] = 16880,
  [SMALL_STATE(542)] = 16902,
  [SMALL_STATE(543)] = 16924,
  [SMALL_STATE(544)] = 16946,
  [SMALL_STATE(545)] = 16968,
  [SMALL_STATE(546)] = 16990,
  [SMALL_STATE(547)] = 17012,
  [SMALL_STATE(548)] = 17029,
  [SMALL_STATE(549)] = 17048,
  [SMALL_STATE(550)] = 17065,
  [SMALL_STATE(551)] = 17082,
  [SMALL_STATE(552)] = 17099,
  [SMALL_STATE(553)] = 17116,
  [SMALL_STATE(554)] = 17135,
  [SMALL_STATE(555)] = 17152,
  [SMALL_STATE(556)] = 17169,
  [SMALL_STATE(557)] = 17186,
  [SMALL_STATE(558)] = 17205,
  [SMALL_STATE(559)] = 17222,
  [SMALL_STATE(560)] = 17239,
  [SMALL_STATE(561)] = 17256,
  [SMALL_STATE(562)] = 17273,
  [SMALL_STATE(563)] = 17292,
  [SMALL_STATE(564)] = 17309,
  [SMALL_STATE(565)] = 17326,
  [SMALL_STATE(566)] = 17343,
  [SMALL_STATE(567)] = 17360,
  [SMALL_STATE(568)] = 17377,
  [SMALL_STATE(569)] = 17394,
  [SMALL_STATE(570)] = 17407,
  [SMALL_STATE(571)] = 17424,
  [SMALL_STATE(572)] = 17441,
  [SMALL_STATE(573)] = 17456,
  [SMALL_STATE(574)] = 17473,
  [SMALL_STATE(575)] = 17488,
  [SMALL_STATE(576)] = 17501,
  [SMALL_STATE(577)] = 17518,
  [SMALL_STATE(578)] = 17534,
  [SMALL_STATE(579)] = 17550,
  [SMALL_STATE(580)] = 17564,
  [SMALL_STATE(581)] = 17580,
  [SMALL_STATE(582)] = 17596,
  [SMALL_STATE(583)] = 17612,
  [SMALL_STATE(584)] = 17628,
  [SMALL_STATE(585)] = 17644,
  [SMALL_STATE(586)] = 17660,
  [SMALL_STATE(587)] = 17676,
  [SMALL_STATE(588)] = 17692,
  [SMALL_STATE(589)] = 17708,
  [SMALL_STATE(590)] = 17716,
  [SMALL_STATE(591)] = 17732,
  [SMALL_STATE(592)] = 17746,
  [SMALL_STATE(593)] = 17762,
  [SMALL_STATE(594)] = 17776,
  [SMALL_STATE(595)] = 17792,
  [SMALL_STATE(596)] = 17808,
  [SMALL_STATE(597)] = 17824,
  [SMALL_STATE(598)] = 17840,
  [SMALL_STATE(599)] = 17856,
  [SMALL_STATE(600)] = 17872,
  [SMALL_STATE(601)] = 17888,
  [SMALL_STATE(602)] = 17904,
  [SMALL_STATE(603)] = 17920,
  [SMALL_STATE(604)] = 17936,
  [SMALL_STATE(605)] = 17952,
  [SMALL_STATE(606)] = 17968,
  [SMALL_STATE(607)] = 17984,
  [SMALL_STATE(608)] = 18000,
  [SMALL_STATE(609)] = 18016,
  [SMALL_STATE(610)] = 18032,
  [SMALL_STATE(611)] = 18048,
  [SMALL_STATE(612)] = 18064,
  [SMALL_STATE(613)] = 18080,
  [SMALL_STATE(614)] = 18096,
  [SMALL_STATE(615)] = 18112,
  [SMALL_STATE(616)] = 18124,
  [SMALL_STATE(617)] = 18140,
  [SMALL_STATE(618)] = 18156,
  [SMALL_STATE(619)] = 18163,
  [SMALL_STATE(620)] = 18170,
  [SMALL_STATE(621)] = 18183,
  [SMALL_STATE(622)] = 18196,
  [SMALL_STATE(623)] = 18203,
  [SMALL_STATE(624)] = 18210,
  [SMALL_STATE(625)] = 18217,
  [SMALL_STATE(626)] = 18228,
  [SMALL_STATE(627)] = 18241,
  [SMALL_STATE(628)] = 18254,
  [SMALL_STATE(629)] = 18261,
  [SMALL_STATE(630)] = 18272,
  [SMALL_STATE(631)] = 18285,
  [SMALL_STATE(632)] = 18298,
  [SMALL_STATE(633)] = 18305,
  [SMALL_STATE(634)] = 18318,
  [SMALL_STATE(635)] = 18331,
  [SMALL_STATE(636)] = 18338,
  [SMALL_STATE(637)] = 18351,
  [SMALL_STATE(638)] = 18358,
  [SMALL_STATE(639)] = 18371,
  [SMALL_STATE(640)] = 18384,
  [SMALL_STATE(641)] = 18391,
  [SMALL_STATE(642)] = 18398,
  [SMALL_STATE(643)] = 18411,
  [SMALL_STATE(644)] = 18424,
  [SMALL_STATE(645)] = 18431,
  [SMALL_STATE(646)] = 18438,
  [SMALL_STATE(647)] = 18445,
  [SMALL_STATE(648)] = 18452,
  [SMALL_STATE(649)] = 18459,
  [SMALL_STATE(650)] = 18466,
  [SMALL_STATE(651)] = 18479,
  [SMALL_STATE(652)] = 18486,
  [SMALL_STATE(653)] = 18493,
  [SMALL_STATE(654)] = 18500,
  [SMALL_STATE(655)] = 18507,
  [SMALL_STATE(656)] = 18514,
  [SMALL_STATE(657)] = 18521,
  [SMALL_STATE(658)] = 18531,
  [SMALL_STATE(659)] = 18541,
  [SMALL_STATE(660)] = 18551,
  [SMALL_STATE(661)] = 18561,
  [SMALL_STATE(662)] = 18571,
  [SMALL_STATE(663)] = 18581,
  [SMALL_STATE(664)] = 18591,
  [SMALL_STATE(665)] = 18601,
  [SMALL_STATE(666)] = 18611,
  [SMALL_STATE(667)] = 18621,
  [SMALL_STATE(668)] = 18631,
  [SMALL_STATE(669)] = 18641,
  [SMALL_STATE(670)] = 18651,
  [SMALL_STATE(671)] = 18661,
  [SMALL_STATE(672)] = 18671,
  [SMALL_STATE(673)] = 18681,
  [SMALL_STATE(674)] = 18691,
  [SMALL_STATE(675)] = 18701,
  [SMALL_STATE(676)] = 18707,
  [SMALL_STATE(677)] = 18717,
  [SMALL_STATE(678)] = 18727,
  [SMALL_STATE(679)] = 18737,
  [SMALL_STATE(680)] = 18747,
  [SMALL_STATE(681)] = 18757,
  [SMALL_STATE(682)] = 18767,
  [SMALL_STATE(683)] = 18777,
  [SMALL_STATE(684)] = 18787,
  [SMALL_STATE(685)] = 18797,
  [SMALL_STATE(686)] = 18803,
  [SMALL_STATE(687)] = 18813,
  [SMALL_STATE(688)] = 18823,
  [SMALL_STATE(689)] = 18833,
  [SMALL_STATE(690)] = 18843,
  [SMALL_STATE(691)] = 18849,
  [SMALL_STATE(692)] = 18859,
  [SMALL_STATE(693)] = 18869,
  [SMALL_STATE(694)] = 18879,
  [SMALL_STATE(695)] = 18889,
  [SMALL_STATE(696)] = 18894,
  [SMALL_STATE(697)] = 18901,
  [SMALL_STATE(698)] = 18906,
  [SMALL_STATE(699)] = 18913,
  [SMALL_STATE(700)] = 18920,
  [SMALL_STATE(701)] = 18925,
  [SMALL_STATE(702)] = 18929,
  [SMALL_STATE(703)] = 18933,
  [SMALL_STATE(704)] = 18937,
  [SMALL_STATE(705)] = 18941,
  [SMALL_STATE(706)] = 18945,
  [SMALL_STATE(707)] = 18949,
  [SMALL_STATE(708)] = 18953,
  [SMALL_STATE(709)] = 18957,
  [SMALL_STATE(710)] = 18961,
  [SMALL_STATE(711)] = 18965,
  [SMALL_STATE(712)] = 18969,
  [SMALL_STATE(713)] = 18973,
  [SMALL_STATE(714)] = 18977,
  [SMALL_STATE(715)] = 18981,
  [SMALL_STATE(716)] = 18985,
  [SMALL_STATE(717)] = 18989,
  [SMALL_STATE(718)] = 18993,
  [SMALL_STATE(719)] = 18997,
  [SMALL_STATE(720)] = 19001,
  [SMALL_STATE(721)] = 19005,
  [SMALL_STATE(722)] = 19009,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(284),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(524),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(558),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(221),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(589),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(448),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(628),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(562),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(85),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(517),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(563),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(488),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(362),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [55] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(125),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(521),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [69] = {.entry = {.count = 1, .reusable = false}}, SHIFT(554),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(497),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(399),
  [77] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [83] = {.entry = {.count = 1, .reusable = false}}, SHIFT(133),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(515),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [93] = {.entry = {.count = 1, .reusable = false}}, SHIFT(559),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(345),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(272),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [107] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(446),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(304),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(447),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(422),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [131] = {.entry = {.count = 1, .reusable = true}}, SHIFT(500),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(445),
  [135] = {.entry = {.count = 1, .reusable = true}}, SHIFT(427),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(548),
  [139] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(501),
  [143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [145] = {.entry = {.count = 1, .reusable = true}}, SHIFT(273),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(509),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(371),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(506),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(370),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(203),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(507),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(204),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(503),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(198),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(640),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(505),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(646),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(325),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(502),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(324),
  [183] = {.entry = {.count = 1, .reusable = true}}, SHIFT(246),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(508),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(251),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(462),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(499),
  [193] = {.entry = {.count = 1, .reusable = true}}, SHIFT(459),
  [195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(363),
  [197] = {.entry = {.count = 1, .reusable = true}}, SHIFT(504),
  [199] = {.entry = {.count = 1, .reusable = true}}, SHIFT(358),
  [201] = {.entry = {.count = 1, .reusable = true}}, SHIFT(531),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(532),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(534),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(527),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(579),
  [211] = {.entry = {.count = 1, .reusable = true}}, SHIFT(307),
  [213] = {.entry = {.count = 1, .reusable = true}}, SHIFT(553),
  [215] = {.entry = {.count = 1, .reusable = true}}, SHIFT(535),
  [217] = {.entry = {.count = 1, .reusable = true}}, SHIFT(526),
  [219] = {.entry = {.count = 1, .reusable = true}}, SHIFT(593),
  [221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(528),
  [223] = {.entry = {.count = 1, .reusable = true}}, SHIFT(529),
  [225] = {.entry = {.count = 1, .reusable = true}}, SHIFT(591),
  [227] = {.entry = {.count = 1, .reusable = true}}, SHIFT(536),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 1, 0, 2),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(636),
  [233] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [235] = {.entry = {.count = 1, .reusable = true}}, SHIFT(541),
  [237] = {.entry = {.count = 1, .reusable = true}}, SHIFT(540),
  [239] = {.entry = {.count = 1, .reusable = true}}, SHIFT(682),
  [241] = {.entry = {.count = 1, .reusable = true}}, SHIFT(681),
  [243] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0),
  [245] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(89),
  [248] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(553),
  [251] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(636),
  [254] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(16),
  [257] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(541),
  [260] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(540),
  [263] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(682),
  [266] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(681),
  [269] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(85),
  [272] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 2, 0, 5),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 2, 0, 4),
  [276] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 3, 0, 10),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 1, 0, 0),
  [280] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 1, 0, 0),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(626),
  [284] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0),
  [286] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0),
  [288] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(626),
  [291] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 2, 0, 0),
  [293] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 2, 0, 0),
  [295] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_identifier, 1, 0, 0),
  [297] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_identifier, 1, 0, 0),
  [299] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_ident, 1, 0, 0),
  [301] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_ident, 1, 0, 0),
  [303] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(562),
  [306] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(643),
  [309] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(14),
  [312] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(544),
  [315] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(543),
  [318] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(688),
  [321] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(684),
  [324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(643),
  [326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(544),
  [330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(543),
  [332] = {.entry = {.count = 1, .reusable = true}}, SHIFT(688),
  [334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(684),
  [336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(638),
  [338] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(546),
  [342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(538),
  [344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(676),
  [346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(661),
  [348] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(548),
  [351] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(638),
  [354] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(17),
  [357] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(546),
  [360] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(538),
  [363] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(676),
  [366] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(661),
  [369] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 1, 0, 0),
  [371] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 1, 0, 0),
  [373] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bool_value, 1, 0, 0),
  [375] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression, 1, 0, 0),
  [377] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__expression, 1, 0, 0),
  [379] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__bool_value, 1, 0, 0),
  [381] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_string_end, 1, 0, 0),
  [383] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_string_end, 1, 0, 0),
  [385] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3, 0, 0),
  [387] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3, 0, 0),
  [389] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym__bool_value, 1, 0, 0), REDUCE(sym__expression, 1, 0, 0),
  [392] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym__bool_value, 1, 0, 0), REDUCE(sym__expression, 1, 0, 0),
  [395] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2, 0, 0),
  [397] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 2, 0, 0),
  [399] = {.entry = {.count = 1, .reusable = true}}, SHIFT(639),
  [401] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment, 3, 0, 13),
  [403] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [405] = {.entry = {.count = 1, .reusable = false}}, SHIFT(110),
  [407] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [409] = {.entry = {.count = 1, .reusable = true}}, SHIFT(270),
  [411] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assignment, 3, 0, 13),
  [413] = {.entry = {.count = 1, .reusable = true}}, SHIFT(621),
  [415] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [417] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [419] = {.entry = {.count = 1, .reusable = true}}, SHIFT(520),
  [421] = {.entry = {.count = 1, .reusable = true}}, SHIFT(641),
  [423] = {.entry = {.count = 1, .reusable = true}}, SHIFT(632),
  [425] = {.entry = {.count = 1, .reusable = true}}, SHIFT(627),
  [427] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [429] = {.entry = {.count = 1, .reusable = true}}, SHIFT(705),
  [431] = {.entry = {.count = 1, .reusable = false}}, SHIFT(571),
  [433] = {.entry = {.count = 1, .reusable = true}}, SHIFT(701),
  [435] = {.entry = {.count = 1, .reusable = true}}, SHIFT(624),
  [437] = {.entry = {.count = 1, .reusable = true}}, SHIFT(697),
  [439] = {.entry = {.count = 1, .reusable = true}}, SHIFT(708),
  [441] = {.entry = {.count = 1, .reusable = false}}, SHIFT(695),
  [443] = {.entry = {.count = 1, .reusable = true}}, SHIFT(702),
  [445] = {.entry = {.count = 1, .reusable = true}}, SHIFT(675),
  [447] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(621),
  [450] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [452] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(523),
  [456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(408),
  [458] = {.entry = {.count = 1, .reusable = false}}, SHIFT(551),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(356),
  [462] = {.entry = {.count = 1, .reusable = true}}, SHIFT(409),
  [464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(300),
  [466] = {.entry = {.count = 1, .reusable = true}}, SHIFT(348),
  [468] = {.entry = {.count = 1, .reusable = false}}, SHIFT(298),
  [470] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [472] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [474] = {.entry = {.count = 1, .reusable = true}}, SHIFT(522),
  [476] = {.entry = {.count = 1, .reusable = true}}, SHIFT(374),
  [478] = {.entry = {.count = 1, .reusable = false}}, SHIFT(576),
  [480] = {.entry = {.count = 1, .reusable = true}}, SHIFT(391),
  [482] = {.entry = {.count = 1, .reusable = true}}, SHIFT(406),
  [484] = {.entry = {.count = 1, .reusable = true}}, SHIFT(306),
  [486] = {.entry = {.count = 1, .reusable = true}}, SHIFT(376),
  [488] = {.entry = {.count = 1, .reusable = false}}, SHIFT(305),
  [490] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(627),
  [493] = {.entry = {.count = 1, .reusable = true}}, SHIFT(587),
  [495] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(639),
  [498] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [500] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [502] = {.entry = {.count = 1, .reusable = true}}, SHIFT(516),
  [504] = {.entry = {.count = 1, .reusable = true}}, SHIFT(475),
  [506] = {.entry = {.count = 1, .reusable = false}}, SHIFT(560),
  [508] = {.entry = {.count = 1, .reusable = true}}, SHIFT(464),
  [510] = {.entry = {.count = 1, .reusable = true}}, SHIFT(375),
  [512] = {.entry = {.count = 1, .reusable = true}}, SHIFT(415),
  [514] = {.entry = {.count = 1, .reusable = false}}, SHIFT(377),
  [516] = {.entry = {.count = 1, .reusable = true}}, SHIFT(644),
  [518] = {.entry = {.count = 1, .reusable = true}}, SHIFT(590),
  [520] = {.entry = {.count = 1, .reusable = true}}, SHIFT(351),
  [522] = {.entry = {.count = 1, .reusable = true}}, SHIFT(714),
  [524] = {.entry = {.count = 1, .reusable = true}}, SHIFT(717),
  [526] = {.entry = {.count = 1, .reusable = true}}, SHIFT(606),
  [528] = {.entry = {.count = 1, .reusable = true}}, SHIFT(353),
  [530] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [532] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [534] = {.entry = {.count = 1, .reusable = true}}, SHIFT(513),
  [536] = {.entry = {.count = 1, .reusable = true}}, SHIFT(247),
  [538] = {.entry = {.count = 1, .reusable = false}}, SHIFT(565),
  [540] = {.entry = {.count = 1, .reusable = true}}, SHIFT(253),
  [542] = {.entry = {.count = 1, .reusable = true}}, SHIFT(259),
  [544] = {.entry = {.count = 1, .reusable = true}}, SHIFT(241),
  [546] = {.entry = {.count = 1, .reusable = true}}, SHIFT(276),
  [548] = {.entry = {.count = 1, .reusable = false}}, SHIFT(240),
  [550] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [552] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [554] = {.entry = {.count = 1, .reusable = true}}, SHIFT(519),
  [556] = {.entry = {.count = 1, .reusable = true}}, SHIFT(441),
  [558] = {.entry = {.count = 1, .reusable = false}}, SHIFT(552),
  [560] = {.entry = {.count = 1, .reusable = true}}, SHIFT(442),
  [562] = {.entry = {.count = 1, .reusable = true}}, SHIFT(365),
  [564] = {.entry = {.count = 1, .reusable = true}}, SHIFT(439),
  [566] = {.entry = {.count = 1, .reusable = false}}, SHIFT(412),
  [568] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment, 4, 0, 15),
  [570] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assignment, 4, 0, 15),
  [572] = {.entry = {.count = 1, .reusable = true}}, SHIFT(255),
  [574] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [576] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [578] = {.entry = {.count = 1, .reusable = true}}, SHIFT(514),
  [580] = {.entry = {.count = 1, .reusable = true}}, SHIFT(326),
  [582] = {.entry = {.count = 1, .reusable = false}}, SHIFT(570),
  [584] = {.entry = {.count = 1, .reusable = true}}, SHIFT(294),
  [586] = {.entry = {.count = 1, .reusable = true}}, SHIFT(250),
  [588] = {.entry = {.count = 1, .reusable = true}}, SHIFT(327),
  [590] = {.entry = {.count = 1, .reusable = false}}, SHIFT(252),
  [592] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_array_end, 1, 0, 0),
  [594] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_array_end, 1, 0, 0),
  [596] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 3, 0, 0),
  [598] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object, 3, 0, 0),
  [600] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 2, 0, 0),
  [602] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 2, 0, 0),
  [604] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_parenthesis_end, 1, 0, 0),
  [606] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_parenthesis_end, 1, 0, 0),
  [608] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 2, 0, 0),
  [610] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object, 2, 0, 0),
  [612] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 4, 0, 0),
  [614] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object, 4, 0, 0),
  [616] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_brace_end, 1, 0, 0),
  [618] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_brace_end, 1, 0, 0),
  [620] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array_query, 3, 0, 3),
  [622] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array_query, 3, 0, 3),
  [624] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_array_query_end, 1, 0, 0),
  [626] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_array_query_end, 1, 0, 0),
  [628] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 4, 0, 0),
  [630] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 4, 0, 0),
  [632] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 3, 0, 0),
  [634] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 3, 0, 0),
  [636] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_query, 3, 0, 3),
  [638] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_element_query, 3, 0, 3),
  [640] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_element_query_end, 1, 0, 0),
  [642] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_element_query_end, 1, 0, 0),
  [644] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parenthesized_expression, 3, 0, 0),
  [646] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__parenthesized_expression, 3, 0, 0),
  [648] = {.entry = {.count = 1, .reusable = true}}, SHIFT(685),
  [650] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [652] = {.entry = {.count = 1, .reusable = false}}, SHIFT(94),
  [654] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [656] = {.entry = {.count = 1, .reusable = true}}, SHIFT(368),
  [658] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [660] = {.entry = {.count = 1, .reusable = false}}, SHIFT(102),
  [662] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(361),
  [666] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [668] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [670] = {.entry = {.count = 1, .reusable = false}}, SHIFT(83),
  [672] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [674] = {.entry = {.count = 1, .reusable = true}}, SHIFT(635),
  [676] = {.entry = {.count = 1, .reusable = true}}, SHIFT(193),
  [678] = {.entry = {.count = 1, .reusable = true}}, SHIFT(189),
  [680] = {.entry = {.count = 1, .reusable = true}}, SHIFT(199),
  [682] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [684] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [686] = {.entry = {.count = 1, .reusable = true}}, SHIFT(201),
  [688] = {.entry = {.count = 1, .reusable = true}}, SHIFT(195),
  [690] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0),
  [692] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [694] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [696] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0),
  [698] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0),
  [700] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0),
  [702] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_stmt, 2, 0, 6),
  [704] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_filter_stmt, 2, 0, 6),
  [706] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_not_expression, 2, 0, 0),
  [708] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_not_expression, 2, 0, 0),
  [710] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(18),
  [713] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_or_expression, 2, 0, 0),
  [715] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_or_expression, 2, 0, 0),
  [717] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(620),
  [720] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_and_expression, 2, 0, 0),
  [722] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_and_expression, 2, 0, 0),
  [724] = {.entry = {.count = 1, .reusable = true}}, SHIFT(620),
  [726] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(27),
  [729] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [731] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [733] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [735] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [737] = {.entry = {.count = 1, .reusable = true}}, SHIFT(630),
  [739] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(630),
  [742] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparator, 4, 0, 19),
  [744] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparator, 4, 0, 19),
  [746] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparator, 2, 0, 16),
  [748] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparator, 2, 0, 16),
  [750] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parenthesized_bool_expression, 3, 0, 0),
  [752] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__parenthesized_bool_expression, 3, 0, 0),
  [754] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_expression, 1, 0, 0),
  [756] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_expression, 1, 0, 0),
  [758] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison, 2, 0, 12),
  [760] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison, 2, 0, 12),
  [762] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparator, 1, 0, 0),
  [764] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparator, 1, 0, 0),
  [766] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_bool_value, 1, 0, 0),
  [768] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_bool_value, 1, 0, 0),
  [770] = {.entry = {.count = 1, .reusable = true}}, SHIFT(631),
  [772] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [775] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(20),
  [778] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(634),
  [781] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_query_start, 1, 0, 0),
  [783] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_query_start, 1, 0, 0),
  [785] = {.entry = {.count = 1, .reusable = true}}, SHIFT(634),
  [787] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(631),
  [790] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_iterator_stmt, 4, 0, 14),
  [792] = {.entry = {.count = 1, .reusable = true}}, SHIFT(321),
  [794] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_iterator_stmt, 4, 0, 14),
  [796] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(22),
  [799] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(30),
  [802] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_stmt, 4, 0, 17),
  [804] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_update_stmt, 4, 0, 17),
  [806] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_limit_stmt, 2, 0, 9),
  [808] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_limit_stmt, 2, 0, 9),
  [810] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_limit_value, 1, 0, 0),
  [812] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_limit_value, 1, 0, 0),
  [814] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_limit_stmt, 2, 0, 0),
  [816] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_limit_stmt, 2, 0, 0),
  [818] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(650),
  [821] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_filter_expression, 1, 0, 0),
  [823] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_filter_expression, 1, 0, 0),
  [825] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_main_iterator, 1, 0, 0),
  [827] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_main_iterator, 1, 0, 0),
  [829] = {.entry = {.count = 1, .reusable = true}}, SHIFT(650),
  [831] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_filter_stmt, 2, 0, 0),
  [833] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_filter_stmt, 2, 0, 0),
  [835] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_iterator_stmt, 2, 0, 0),
  [837] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_iterator_stmt, 2, 0, 0),
  [839] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_update_field, 1, 0, 0),
  [841] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_update_field, 1, 0, 0),
  [843] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_iterator, 1, 0, 0),
  [845] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_iterator, 1, 0, 0),
  [847] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_offset_stmt, 2, 0, 0),
  [849] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_offset_stmt, 2, 0, 0),
  [851] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_iterator_stmt, 5, 0, 18),
  [853] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_iterator_stmt, 5, 0, 18),
  [855] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_offset_value, 1, 0, 0),
  [857] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_offset_value, 1, 0, 0),
  [859] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(633),
  [862] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_offset_stmt, 2, 0, 8),
  [864] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_offset_stmt, 2, 0, 8),
  [866] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_stmt, 2, 0, 0),
  [868] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_delete_stmt, 2, 0, 0),
  [870] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_stmt, 2, 0, 7),
  [872] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_delete_stmt, 2, 0, 7),
  [874] = {.entry = {.count = 1, .reusable = true}}, SHIFT(633),
  [876] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_delete_field, 1, 0, 0),
  [878] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_delete_field, 1, 0, 0),
  [880] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_stmt, 2, 0, 0),
  [882] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_update_stmt, 2, 0, 0),
  [884] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_equals, 1, 0, 0),
  [886] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_equals, 1, 0, 0),
  [888] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_colon, 1, 0, 0),
  [890] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_missing_colon, 1, 0, 0),
  [892] = {.entry = {.count = 1, .reusable = true}}, SHIFT(457),
  [894] = {.entry = {.count = 1, .reusable = true}}, SHIFT(453),
  [896] = {.entry = {.count = 1, .reusable = true}}, SHIFT(452),
  [898] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [900] = {.entry = {.count = 1, .reusable = true}}, SHIFT(454),
  [902] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [904] = {.entry = {.count = 1, .reusable = true}}, SHIFT(317),
  [906] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [908] = {.entry = {.count = 1, .reusable = true}}, SHIFT(354),
  [910] = {.entry = {.count = 1, .reusable = true}}, SHIFT(651),
  [912] = {.entry = {.count = 1, .reusable = true}}, SHIFT(369),
  [914] = {.entry = {.count = 1, .reusable = true}}, SHIFT(208),
  [916] = {.entry = {.count = 1, .reusable = true}}, SHIFT(249),
  [918] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [920] = {.entry = {.count = 1, .reusable = true}}, SHIFT(357),
  [922] = {.entry = {.count = 1, .reusable = true}}, SHIFT(355),
  [924] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [926] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [928] = {.entry = {.count = 1, .reusable = true}}, SHIFT(395),
  [930] = {.entry = {.count = 1, .reusable = true}}, SHIFT(404),
  [932] = {.entry = {.count = 1, .reusable = true}}, SHIFT(256),
  [934] = {.entry = {.count = 1, .reusable = true}}, SHIFT(271),
  [936] = {.entry = {.count = 1, .reusable = true}}, SHIFT(274),
  [938] = {.entry = {.count = 1, .reusable = true}}, SHIFT(275),
  [940] = {.entry = {.count = 1, .reusable = true}}, SHIFT(339),
  [942] = {.entry = {.count = 1, .reusable = true}}, SHIFT(302),
  [944] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [946] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [948] = {.entry = {.count = 1, .reusable = true}}, SHIFT(480),
  [950] = {.entry = {.count = 1, .reusable = true}}, SHIFT(481),
  [952] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [954] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [956] = {.entry = {.count = 1, .reusable = true}}, SHIFT(637),
  [958] = {.entry = {.count = 1, .reusable = true}}, SHIFT(479),
  [960] = {.entry = {.count = 1, .reusable = true}}, SHIFT(471),
  [962] = {.entry = {.count = 1, .reusable = true}}, SHIFT(647),
  [964] = {.entry = {.count = 1, .reusable = true}}, SHIFT(649),
  [966] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [968] = {.entry = {.count = 1, .reusable = true}}, SHIFT(182),
  [970] = {.entry = {.count = 1, .reusable = true}}, SHIFT(381),
  [972] = {.entry = {.count = 1, .reusable = true}}, SHIFT(382),
  [974] = {.entry = {.count = 1, .reusable = true}}, SHIFT(403),
  [976] = {.entry = {.count = 1, .reusable = true}}, SHIFT(401),
  [978] = {.entry = {.count = 1, .reusable = true}}, SHIFT(205),
  [980] = {.entry = {.count = 1, .reusable = true}}, SHIFT(206),
  [982] = {.entry = {.count = 1, .reusable = true}}, SHIFT(330),
  [984] = {.entry = {.count = 1, .reusable = true}}, SHIFT(331),
  [986] = {.entry = {.count = 1, .reusable = true}}, SHIFT(712),
  [988] = {.entry = {.count = 1, .reusable = true}}, SHIFT(429),
  [990] = {.entry = {.count = 1, .reusable = true}}, SHIFT(494),
  [992] = {.entry = {.count = 1, .reusable = true}}, SHIFT(379),
  [994] = {.entry = {.count = 1, .reusable = true}}, SHIFT(262),
  [996] = {.entry = {.count = 1, .reusable = true}}, SHIFT(396),
  [998] = {.entry = {.count = 1, .reusable = true}}, SHIFT(648),
  [1000] = {.entry = {.count = 1, .reusable = true}}, SHIFT(493),
  [1002] = {.entry = {.count = 1, .reusable = true}}, SHIFT(450),
  [1004] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [1006] = {.entry = {.count = 1, .reusable = true}}, SHIFT(469),
  [1008] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [1010] = {.entry = {.count = 1, .reusable = true}}, SHIFT(344),
  [1012] = {.entry = {.count = 1, .reusable = true}}, SHIFT(316),
  [1014] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [1016] = {.entry = {.count = 1, .reusable = true}}, SHIFT(465),
  [1018] = {.entry = {.count = 1, .reusable = true}}, SHIFT(460),
  [1020] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__missing_query, 2, 0, 3),
  [1022] = {.entry = {.count = 1, .reusable = true}}, SHIFT(713),
  [1024] = {.entry = {.count = 1, .reusable = true}}, SHIFT(718),
  [1026] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [1028] = {.entry = {.count = 1, .reusable = true}}, SHIFT(191),
  [1030] = {.entry = {.count = 1, .reusable = true}}, SHIFT(432),
  [1032] = {.entry = {.count = 1, .reusable = false}}, SHIFT(704),
  [1034] = {.entry = {.count = 1, .reusable = true}}, SHIFT(615),
  [1036] = {.entry = {.count = 1, .reusable = false}}, SHIFT(708),
  [1038] = {.entry = {.count = 1, .reusable = true}}, SHIFT(449),
  [1040] = {.entry = {.count = 1, .reusable = false}}, SHIFT(146),
  [1042] = {.entry = {.count = 1, .reusable = false}}, SHIFT(151),
  [1044] = {.entry = {.count = 1, .reusable = false}}, SHIFT(152),
  [1046] = {.entry = {.count = 1, .reusable = false}}, SHIFT(140),
  [1048] = {.entry = {.count = 1, .reusable = false}}, SHIFT(397),
  [1050] = {.entry = {.count = 1, .reusable = true}}, SHIFT(556),
  [1052] = {.entry = {.count = 1, .reusable = false}}, SHIFT(348),
  [1054] = {.entry = {.count = 1, .reusable = false}}, SHIFT(417),
  [1056] = {.entry = {.count = 1, .reusable = true}}, SHIFT(555),
  [1058] = {.entry = {.count = 1, .reusable = false}}, SHIFT(439),
  [1060] = {.entry = {.count = 1, .reusable = true}}, SHIFT(319),
  [1062] = {.entry = {.count = 1, .reusable = false}}, SHIFT(138),
  [1064] = {.entry = {.count = 1, .reusable = true}}, SHIFT(550),
  [1066] = {.entry = {.count = 1, .reusable = false}}, SHIFT(477),
  [1068] = {.entry = {.count = 1, .reusable = false}}, SHIFT(373),
  [1070] = {.entry = {.count = 1, .reusable = false}}, SHIFT(139),
  [1072] = {.entry = {.count = 1, .reusable = true}}, SHIFT(549),
  [1074] = {.entry = {.count = 1, .reusable = false}}, SHIFT(78),
  [1076] = {.entry = {.count = 1, .reusable = true}}, SHIFT(561),
  [1078] = {.entry = {.count = 1, .reusable = false}}, SHIFT(72),
  [1080] = {.entry = {.count = 1, .reusable = false}}, SHIFT(483),
  [1082] = {.entry = {.count = 1, .reusable = true}}, SHIFT(564),
  [1084] = {.entry = {.count = 1, .reusable = false}}, SHIFT(415),
  [1086] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [1088] = {.entry = {.count = 1, .reusable = true}}, SHIFT(418),
  [1090] = {.entry = {.count = 1, .reusable = false}}, SHIFT(148),
  [1092] = {.entry = {.count = 1, .reusable = true}}, SHIFT(566),
  [1094] = {.entry = {.count = 1, .reusable = false}}, SHIFT(145),
  [1096] = {.entry = {.count = 1, .reusable = false}}, SHIFT(496),
  [1098] = {.entry = {.count = 1, .reusable = false}}, SHIFT(269),
  [1100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(567),
  [1102] = {.entry = {.count = 1, .reusable = false}}, SHIFT(276),
  [1104] = {.entry = {.count = 1, .reusable = false}}, SHIFT(143),
  [1106] = {.entry = {.count = 1, .reusable = false}}, SHIFT(258),
  [1108] = {.entry = {.count = 1, .reusable = false}}, SHIFT(400),
  [1110] = {.entry = {.count = 1, .reusable = false}}, SHIFT(376),
  [1112] = {.entry = {.count = 1, .reusable = false}}, SHIFT(340),
  [1114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(573),
  [1116] = {.entry = {.count = 1, .reusable = false}}, SHIFT(327),
  [1118] = {.entry = {.count = 1, .reusable = false}}, SHIFT(707),
  [1120] = {.entry = {.count = 1, .reusable = true}}, SHIFT(547),
  [1122] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_or_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(24),
  [1125] = {.entry = {.count = 1, .reusable = false}}, SHIFT(334),
  [1127] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_and_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(35),
  [1130] = {.entry = {.count = 1, .reusable = false}}, SHIFT(384),
  [1132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(568),
  [1134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(557),
  [1136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(209),
  [1138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(332),
  [1140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(645),
  [1142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [1144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(260),
  [1146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(398),
  [1148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(622),
  [1150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [1152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(405),
  [1154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(623),
  [1156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_missing_query_body, 1, 0, 0),
  [1158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(176),
  [1160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(431),
  [1162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(342),
  [1164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(366),
  [1166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(350),
  [1168] = {.entry = {.count = 1, .reusable = true}}, SHIFT(443),
  [1170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [1172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [1174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(254),
  [1176] = {.entry = {.count = 1, .reusable = true}}, SHIFT(200),
  [1178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(207),
  [1180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(248),
  [1182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(202),
  [1184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [1186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(438),
  [1188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(197),
  [1190] = {.entry = {.count = 1, .reusable = true}}, SHIFT(378),
  [1192] = {.entry = {.count = 1, .reusable = true}}, SHIFT(310),
  [1194] = {.entry = {.count = 1, .reusable = true}}, SHIFT(487),
  [1196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(372),
  [1198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(498),
  [1200] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__string_content, 2, 0, 0),
  [1202] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__string_content, 2, 0, 0), SHIFT_REPEAT(615),
  [1205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(495),
  [1207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [1209] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 0), SHIFT_REPEAT(557),
  [1212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 0),
  [1214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0),
  [1216] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0), SHIFT_REPEAT(153),
  [1219] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [1221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(359),
  [1223] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(642),
  [1226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(386),
  [1228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(387),
  [1230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(347),
  [1232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(392),
  [1234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(436),
  [1236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(435),
  [1238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [1240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(134),
  [1242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [1244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [1246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(652),
  [1248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(619),
  [1250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(655),
  [1252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(654),
  [1254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(642),
  [1256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(419),
  [1258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(420),
  [1260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(424),
  [1262] = {.entry = {.count = 1, .reusable = true}}, SHIFT(425),
  [1264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [1266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [1268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [1270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(394),
  [1272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(390),
  [1274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(385),
  [1276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(383),
  [1278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [1280] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pair, 3, 0, 11),
  [1282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(456),
  [1284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(444),
  [1286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [1288] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [1290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(484),
  [1292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(485),
  [1294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(489),
  [1296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(490),
  [1298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(295),
  [1300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(296),
  [1302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(336),
  [1304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(333),
  [1306] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [1308] = {.entry = {.count = 1, .reusable = true}}, SHIFT(410),
  [1310] = {.entry = {.count = 1, .reusable = true}}, SHIFT(421),
  [1312] = {.entry = {.count = 1, .reusable = true}}, SHIFT(433),
  [1314] = {.entry = {.count = 1, .reusable = true}}, SHIFT(268),
  [1316] = {.entry = {.count = 1, .reusable = true}}, SHIFT(267),
  [1318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(265),
  [1320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(264),
  [1322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(470),
  [1324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(472),
  [1326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [1328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(185),
  [1330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [1332] = {.entry = {.count = 1, .reusable = true}}, SHIFT(161),
  [1334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(303),
  [1336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(293),
  [1338] = {.entry = {.count = 1, .reusable = true}}, SHIFT(318),
  [1340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(323),
  [1342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [1344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(175),
  [1346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(542),
  [1348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(539),
  [1350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(537),
  [1352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [1354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [1356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [1358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [1360] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__missing_query, 3, 0, 3),
  [1362] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [1364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [1366] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [1368] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [1370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [1372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [1374] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_start, 1, 0, 1),
  [1376] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_start, 1, 0, 0),
  [1378] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
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
