#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 178
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 63
#define ALIAS_COUNT 0
#define TOKEN_COUNT 37
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 10
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 9

enum ts_symbol_identifiers {
  anon_sym_LBRACK = 1,
  anon_sym_RBRACK = 2,
  anon_sym_LPAREN = 3,
  anon_sym_RPAREN = 4,
  anon_sym_for = 5,
  anon_sym_in = 6,
  anon_sym_EQ = 7,
  anon_sym_set = 8,
  anon_sym_LPAREN_RPAREN = 9,
  anon_sym_if = 10,
  anon_sym_DOT = 11,
  anon_sym_EQ_EQ = 12,
  anon_sym_BANG_EQ = 13,
  anon_sym_GT = 14,
  anon_sym_LT = 15,
  anon_sym_GT_EQ = 16,
  anon_sym_LT_EQ = 17,
  anon_sym_matches = 18,
  anon_sym_exists = 19,
  anon_sym_and = 20,
  anon_sym_or = 21,
  anon_sym_limit = 22,
  anon_sym_offset = 23,
  sym_pos_int = 24,
  anon_sym_LBRACE = 25,
  anon_sym_COMMA = 26,
  anon_sym_RBRACE = 27,
  anon_sym_COLON = 28,
  anon_sym_DQUOTE = 29,
  sym_string_content = 30,
  sym_escape_sequence = 31,
  sym_number = 32,
  sym_true = 33,
  sym_false = 34,
  sym_null = 35,
  sym_ident = 36,
  sym_query = 37,
  sym_array_query = 38,
  sym_element_query = 39,
  sym__query_body = 40,
  sym_iterator = 41,
  sym__expression = 42,
  sym_assignment = 43,
  sym_update_assignment = 44,
  sym__source = 45,
  sym_condition = 46,
  sym_comparison = 47,
  sym_path = 48,
  sym_comparator = 49,
  sym_logical_op = 50,
  sym_limit = 51,
  sym_offset = 52,
  sym__value = 53,
  sym_object = 54,
  sym_pair = 55,
  sym_array = 56,
  sym_string = 57,
  aux_sym__string_content = 58,
  aux_sym__query_body_repeat1 = 59,
  aux_sym_path_repeat1 = 60,
  aux_sym_object_repeat1 = 61,
  aux_sym_array_repeat1 = 62,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_for] = "for",
  [anon_sym_in] = "in",
  [anon_sym_EQ] = "=",
  [anon_sym_set] = "set",
  [anon_sym_LPAREN_RPAREN] = "()",
  [anon_sym_if] = "if",
  [anon_sym_DOT] = ".",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_GT] = ">",
  [anon_sym_LT] = "<",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_matches] = "matches",
  [anon_sym_exists] = "exists",
  [anon_sym_and] = "and",
  [anon_sym_or] = "or",
  [anon_sym_limit] = "limit",
  [anon_sym_offset] = "offset",
  [sym_pos_int] = "pos_int",
  [anon_sym_LBRACE] = "{",
  [anon_sym_COMMA] = ",",
  [anon_sym_RBRACE] = "}",
  [anon_sym_COLON] = ":",
  [anon_sym_DQUOTE] = "\"",
  [sym_string_content] = "string_content",
  [sym_escape_sequence] = "escape_sequence",
  [sym_number] = "number",
  [sym_true] = "true",
  [sym_false] = "false",
  [sym_null] = "null",
  [sym_ident] = "ident",
  [sym_query] = "query",
  [sym_array_query] = "array_query",
  [sym_element_query] = "element_query",
  [sym__query_body] = "_query_body",
  [sym_iterator] = "iterator",
  [sym__expression] = "_expression",
  [sym_assignment] = "assignment",
  [sym_update_assignment] = "update_assignment",
  [sym__source] = "_source",
  [sym_condition] = "condition",
  [sym_comparison] = "comparison",
  [sym_path] = "path",
  [sym_comparator] = "comparator",
  [sym_logical_op] = "logical_op",
  [sym_limit] = "limit",
  [sym_offset] = "offset",
  [sym__value] = "_value",
  [sym_object] = "object",
  [sym_pair] = "pair",
  [sym_array] = "array",
  [sym_string] = "string",
  [aux_sym__string_content] = "_string_content",
  [aux_sym__query_body_repeat1] = "_query_body_repeat1",
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
  [anon_sym_for] = anon_sym_for,
  [anon_sym_in] = anon_sym_in,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_set] = anon_sym_set,
  [anon_sym_LPAREN_RPAREN] = anon_sym_LPAREN_RPAREN,
  [anon_sym_if] = anon_sym_if,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [anon_sym_matches] = anon_sym_matches,
  [anon_sym_exists] = anon_sym_exists,
  [anon_sym_and] = anon_sym_and,
  [anon_sym_or] = anon_sym_or,
  [anon_sym_limit] = anon_sym_limit,
  [anon_sym_offset] = anon_sym_offset,
  [sym_pos_int] = sym_pos_int,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [sym_string_content] = sym_string_content,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_number] = sym_number,
  [sym_true] = sym_true,
  [sym_false] = sym_false,
  [sym_null] = sym_null,
  [sym_ident] = sym_ident,
  [sym_query] = sym_query,
  [sym_array_query] = sym_array_query,
  [sym_element_query] = sym_element_query,
  [sym__query_body] = sym__query_body,
  [sym_iterator] = sym_iterator,
  [sym__expression] = sym__expression,
  [sym_assignment] = sym_assignment,
  [sym_update_assignment] = sym_update_assignment,
  [sym__source] = sym__source,
  [sym_condition] = sym_condition,
  [sym_comparison] = sym_comparison,
  [sym_path] = sym_path,
  [sym_comparator] = sym_comparator,
  [sym_logical_op] = sym_logical_op,
  [sym_limit] = sym_limit,
  [sym_offset] = sym_offset,
  [sym__value] = sym__value,
  [sym_object] = sym_object,
  [sym_pair] = sym_pair,
  [sym_array] = sym_array,
  [sym_string] = sym_string,
  [aux_sym__string_content] = aux_sym__string_content,
  [aux_sym__query_body_repeat1] = aux_sym__query_body_repeat1,
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
  [anon_sym_for] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_in] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_set] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_if] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
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
  [anon_sym_exists] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_and] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_or] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_limit] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_offset] = {
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
  [sym_ident] = {
    .visible = true,
    .named = true,
  },
  [sym_query] = {
    .visible = true,
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
  [sym__query_body] = {
    .visible = false,
    .named = true,
  },
  [sym_iterator] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym_assignment] = {
    .visible = true,
    .named = true,
  },
  [sym_update_assignment] = {
    .visible = true,
    .named = true,
  },
  [sym__source] = {
    .visible = false,
    .named = true,
  },
  [sym_condition] = {
    .visible = true,
    .named = true,
  },
  [sym_comparison] = {
    .visible = true,
    .named = true,
  },
  [sym_path] = {
    .visible = true,
    .named = true,
  },
  [sym_comparator] = {
    .visible = true,
    .named = true,
  },
  [sym_logical_op] = {
    .visible = true,
    .named = true,
  },
  [sym_limit] = {
    .visible = true,
    .named = true,
  },
  [sym_offset] = {
    .visible = true,
    .named = true,
  },
  [sym__value] = {
    .visible = false,
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
  [aux_sym__query_body_repeat1] = {
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
  field_expr = 1,
  field_field = 2,
  field_item = 3,
  field_key = 4,
  field_left = 5,
  field_op = 6,
  field_right = 7,
  field_source = 8,
  field_value = 9,
  field_var = 10,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_expr] = "expr",
  [field_field] = "field",
  [field_item] = "item",
  [field_key] = "key",
  [field_left] = "left",
  [field_op] = "op",
  [field_right] = "right",
  [field_source] = "source",
  [field_value] = "value",
  [field_var] = "var",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 2},
  [4] = {.index = 5, .length = 1},
  [5] = {.index = 6, .length = 2},
  [6] = {.index = 8, .length = 2},
  [7] = {.index = 10, .length = 2},
  [8] = {.index = 12, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_left, 0},
  [1] =
    {field_item, 1},
    {field_source, 3},
  [3] =
    {field_key, 0},
    {field_value, 2},
  [5] =
    {field_op, 0},
  [6] =
    {field_left, 0},
    {field_right, 1},
  [8] =
    {field_expr, 2},
    {field_var, 0},
  [10] =
    {field_expr, 3},
    {field_field, 1},
  [12] =
    {field_expr, 1},
    {field_op, 0},
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
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 2,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 5,
  [17] = 17,
  [18] = 4,
  [19] = 8,
  [20] = 6,
  [21] = 21,
  [22] = 21,
  [23] = 23,
  [24] = 21,
  [25] = 9,
  [26] = 23,
  [27] = 13,
  [28] = 28,
  [29] = 21,
  [30] = 23,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 11,
  [36] = 32,
  [37] = 37,
  [38] = 37,
  [39] = 39,
  [40] = 12,
  [41] = 41,
  [42] = 17,
  [43] = 39,
  [44] = 10,
  [45] = 45,
  [46] = 46,
  [47] = 41,
  [48] = 48,
  [49] = 48,
  [50] = 48,
  [51] = 51,
  [52] = 3,
  [53] = 53,
  [54] = 5,
  [55] = 2,
  [56] = 5,
  [57] = 4,
  [58] = 2,
  [59] = 4,
  [60] = 60,
  [61] = 61,
  [62] = 6,
  [63] = 6,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 9,
  [70] = 11,
  [71] = 71,
  [72] = 12,
  [73] = 13,
  [74] = 10,
  [75] = 75,
  [76] = 17,
  [77] = 77,
  [78] = 68,
  [79] = 66,
  [80] = 80,
  [81] = 71,
  [82] = 82,
  [83] = 83,
  [84] = 11,
  [85] = 85,
  [86] = 86,
  [87] = 12,
  [88] = 13,
  [89] = 17,
  [90] = 10,
  [91] = 91,
  [92] = 92,
  [93] = 9,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 97,
  [98] = 98,
  [99] = 99,
  [100] = 99,
  [101] = 99,
  [102] = 102,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 107,
  [108] = 104,
  [109] = 109,
  [110] = 105,
  [111] = 61,
  [112] = 104,
  [113] = 64,
  [114] = 104,
  [115] = 105,
  [116] = 105,
  [117] = 117,
  [118] = 67,
  [119] = 119,
  [120] = 71,
  [121] = 119,
  [122] = 68,
  [123] = 66,
  [124] = 124,
  [125] = 125,
  [126] = 75,
  [127] = 124,
  [128] = 124,
  [129] = 124,
  [130] = 130,
  [131] = 119,
  [132] = 132,
  [133] = 133,
  [134] = 133,
  [135] = 135,
  [136] = 132,
  [137] = 119,
  [138] = 133,
  [139] = 139,
  [140] = 132,
  [141] = 141,
  [142] = 142,
  [143] = 141,
  [144] = 141,
  [145] = 132,
  [146] = 133,
  [147] = 147,
  [148] = 148,
  [149] = 149,
  [150] = 150,
  [151] = 151,
  [152] = 152,
  [153] = 153,
  [154] = 154,
  [155] = 155,
  [156] = 156,
  [157] = 157,
  [158] = 158,
  [159] = 159,
  [160] = 160,
  [161] = 161,
  [162] = 158,
  [163] = 161,
  [164] = 164,
  [165] = 159,
  [166] = 161,
  [167] = 158,
  [168] = 168,
  [169] = 169,
  [170] = 159,
  [171] = 171,
  [172] = 172,
  [173] = 173,
  [174] = 174,
  [175] = 175,
  [176] = 160,
  [177] = 161,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(64);
      ADVANCE_MAP(
        '!', 11,
        '"', 106,
        '(', 68,
        ')', 69,
        ',', 103,
        '-', 10,
        '.', 80,
        '0', 99,
        ':', 105,
        '<', 84,
        '=', 74,
        '>', 83,
        '[', 65,
      );
      if (lookahead == '\\') SKIP(62);
      if (lookahead == ']') ADVANCE(66);
      if (lookahead == 'a') ADVANCE(34);
      if (lookahead == 'e') ADVANCE(51);
      if (lookahead == 'f') ADVANCE(14);
      if (lookahead == 'i') ADVANCE(23);
      if (lookahead == 'l') ADVANCE(27);
      if (lookahead == 'm') ADVANCE(15);
      if (lookahead == 'n') ADVANCE(50);
      if (lookahead == 'o') ADVANCE(24);
      if (lookahead == 's') ADVANCE(20);
      if (lookahead == 't') ADVANCE(38);
      if (lookahead == '{') ADVANCE(102);
      if (lookahead == '}') ADVANCE(104);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(100);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(6);
      if (lookahead == '"') ADVANCE(106);
      if (lookahead == '\\') ADVANCE(58);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(107);
      if (lookahead != 0) ADVANCE(108);
      END_STATE();
    case 2:
      ADVANCE_MAP(
        '!', 11,
        '(', 67,
        ')', 69,
        '.', 80,
        '<', 84,
        '=', 12,
        '>', 83,
        '[', 65,
      );
      if (lookahead == '\\') SKIP(52);
      if (lookahead == ']') ADVANCE(66);
      if (lookahead == 'a') ADVANCE(142);
      if (lookahead == 'e') ADVANCE(158);
      if (lookahead == 'f') ADVANCE(143);
      if (lookahead == 'i') ADVANCE(130);
      if (lookahead == 'l') ADVANCE(135);
      if (lookahead == 'm') ADVANCE(120);
      if (lookahead == 'o') ADVANCE(131);
      if (lookahead == 's') ADVANCE(127);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(101);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 3:
      if (lookahead == '!') ADVANCE(11);
      if (lookahead == ')') ADVANCE(69);
      if (lookahead == ',') ADVANCE(103);
      if (lookahead == ':') ADVANCE(105);
      if (lookahead == '<') ADVANCE(84);
      if (lookahead == '=') ADVANCE(12);
      if (lookahead == '>') ADVANCE(83);
      if (lookahead == '\\') SKIP(55);
      if (lookahead == ']') ADVANCE(66);
      if (lookahead == 'a') ADVANCE(34);
      if (lookahead == 'e') ADVANCE(51);
      if (lookahead == 'f') ADVANCE(35);
      if (lookahead == 'm') ADVANCE(15);
      if (lookahead == 'o') ADVANCE(36);
      if (lookahead == '}') ADVANCE(104);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(106);
      if (lookahead == '(') ADVANCE(67);
      if (lookahead == '-') ADVANCE(10);
      if (lookahead == '0') ADVANCE(110);
      if (lookahead == '=') ADVANCE(73);
      if (lookahead == '[') ADVANCE(65);
      if (lookahead == '\\') SKIP(53);
      if (lookahead == 'f') ADVANCE(122);
      if (lookahead == 'n') ADVANCE(156);
      if (lookahead == 't') ADVANCE(145);
      if (lookahead == '{') ADVANCE(102);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(111);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(106);
      if (lookahead == '-') ADVANCE(10);
      if (lookahead == '0') ADVANCE(110);
      if (lookahead == '[') ADVANCE(65);
      if (lookahead == '\\') SKIP(54);
      if (lookahead == 'f') ADVANCE(121);
      if (lookahead == 'n') ADVANCE(156);
      if (lookahead == 't') ADVANCE(145);
      if (lookahead == '{') ADVANCE(102);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(5);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(111);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 6:
      if (lookahead == '"') ADVANCE(106);
      if (lookahead == '\\') SKIP(57);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6);
      END_STATE();
    case 7:
      if (lookahead == ')') ADVANCE(69);
      if (lookahead == '.') ADVANCE(80);
      if (lookahead == '\\') SKIP(56);
      if (lookahead == ']') ADVANCE(66);
      if (lookahead == 'a') ADVANCE(142);
      if (lookahead == 'f') ADVANCE(143);
      if (lookahead == 'i') ADVANCE(130);
      if (lookahead == 'l') ADVANCE(135);
      if (lookahead == 'o') ADVANCE(131);
      if (lookahead == 's') ADVANCE(127);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(7);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 8:
      if (lookahead == ')') ADVANCE(77);
      END_STATE();
    case 9:
      if (lookahead == '-') ADVANCE(60);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(113);
      END_STATE();
    case 10:
      if (lookahead == '0') ADVANCE(110);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(111);
      END_STATE();
    case 11:
      if (lookahead == '=') ADVANCE(82);
      END_STATE();
    case 12:
      if (lookahead == '=') ADVANCE(81);
      END_STATE();
    case 13:
      if (lookahead == '\\') SKIP(59);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(13);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 14:
      if (lookahead == 'a') ADVANCE(31);
      if (lookahead == 'o') ADVANCE(37);
      END_STATE();
    case 15:
      if (lookahead == 'a') ADVANCE(44);
      END_STATE();
    case 16:
      if (lookahead == 'c') ADVANCE(26);
      END_STATE();
    case 17:
      if (lookahead == 'd') ADVANCE(91);
      END_STATE();
    case 18:
      if (lookahead == 'e') ADVANCE(114);
      END_STATE();
    case 19:
      if (lookahead == 'e') ADVANCE(116);
      END_STATE();
    case 20:
      if (lookahead == 'e') ADVANCE(45);
      END_STATE();
    case 21:
      if (lookahead == 'e') ADVANCE(47);
      END_STATE();
    case 22:
      if (lookahead == 'e') ADVANCE(40);
      END_STATE();
    case 23:
      if (lookahead == 'f') ADVANCE(78);
      if (lookahead == 'n') ADVANCE(72);
      END_STATE();
    case 24:
      if (lookahead == 'f') ADVANCE(25);
      if (lookahead == 'r') ADVANCE(93);
      END_STATE();
    case 25:
      if (lookahead == 'f') ADVANCE(43);
      END_STATE();
    case 26:
      if (lookahead == 'h') ADVANCE(22);
      END_STATE();
    case 27:
      if (lookahead == 'i') ADVANCE(33);
      END_STATE();
    case 28:
      if (lookahead == 'i') ADVANCE(42);
      END_STATE();
    case 29:
      if (lookahead == 'i') ADVANCE(46);
      END_STATE();
    case 30:
      if (lookahead == 'l') ADVANCE(118);
      END_STATE();
    case 31:
      if (lookahead == 'l') ADVANCE(41);
      END_STATE();
    case 32:
      if (lookahead == 'l') ADVANCE(30);
      END_STATE();
    case 33:
      if (lookahead == 'm') ADVANCE(29);
      END_STATE();
    case 34:
      if (lookahead == 'n') ADVANCE(17);
      END_STATE();
    case 35:
      if (lookahead == 'o') ADVANCE(37);
      END_STATE();
    case 36:
      if (lookahead == 'r') ADVANCE(93);
      END_STATE();
    case 37:
      if (lookahead == 'r') ADVANCE(70);
      END_STATE();
    case 38:
      if (lookahead == 'r') ADVANCE(49);
      END_STATE();
    case 39:
      if (lookahead == 's') ADVANCE(89);
      END_STATE();
    case 40:
      if (lookahead == 's') ADVANCE(87);
      END_STATE();
    case 41:
      if (lookahead == 's') ADVANCE(19);
      END_STATE();
    case 42:
      if (lookahead == 's') ADVANCE(48);
      END_STATE();
    case 43:
      if (lookahead == 's') ADVANCE(21);
      END_STATE();
    case 44:
      if (lookahead == 't') ADVANCE(16);
      END_STATE();
    case 45:
      if (lookahead == 't') ADVANCE(75);
      END_STATE();
    case 46:
      if (lookahead == 't') ADVANCE(95);
      END_STATE();
    case 47:
      if (lookahead == 't') ADVANCE(97);
      END_STATE();
    case 48:
      if (lookahead == 't') ADVANCE(39);
      END_STATE();
    case 49:
      if (lookahead == 'u') ADVANCE(18);
      END_STATE();
    case 50:
      if (lookahead == 'u') ADVANCE(32);
      END_STATE();
    case 51:
      if (lookahead == 'x') ADVANCE(28);
      END_STATE();
    case 52:
      if (lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') SKIP(2);
      END_STATE();
    case 53:
      if (lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') SKIP(4);
      END_STATE();
    case 54:
      if (lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') SKIP(5);
      END_STATE();
    case 55:
      if (lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') SKIP(3);
      END_STATE();
    case 56:
      if (lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') SKIP(7);
      END_STATE();
    case 57:
      if (lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') SKIP(6);
      END_STATE();
    case 58:
      ADVANCE_MAP(
        'n', 109,
        'r', 109,
        't', 109,
        '"', 109,
        '/', 109,
        '\\', 109,
        'b', 109,
        'f', 109,
        'u', 109,
      );
      END_STATE();
    case 59:
      if (lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') SKIP(13);
      END_STATE();
    case 60:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(113);
      END_STATE();
    case 61:
      if (eof) ADVANCE(64);
      if (lookahead == '(') ADVANCE(8);
      if (lookahead == ')') ADVANCE(69);
      if (lookahead == '.') ADVANCE(80);
      if (lookahead == '[') ADVANCE(65);
      if (lookahead == '\\') SKIP(63);
      if (lookahead == ']') ADVANCE(66);
      if (lookahead == 'f') ADVANCE(143);
      if (lookahead == 'i') ADVANCE(130);
      if (lookahead == 'l') ADVANCE(135);
      if (lookahead == 'o') ADVANCE(132);
      if (lookahead == 's') ADVANCE(127);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(61);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 62:
      if (eof) ADVANCE(64);
      if (lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') SKIP(0);
      END_STATE();
    case 63:
      if (eof) ADVANCE(64);
      if (lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') SKIP(61);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == ')') ADVANCE(77);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_for);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_for);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_in);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(81);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_set);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_set);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_LPAREN_RPAREN);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_if);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(85);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(86);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_matches);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_matches);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_exists);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_exists);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_and);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_and);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_or);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_or);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_limit);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_limit);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_offset);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_offset);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_pos_int);
      if (lookahead == '.') ADVANCE(112);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(101);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_pos_int);
      if (lookahead == '.') ADVANCE(112);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(100);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_pos_int);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(101);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(107);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(108);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(sym_string_content);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(108);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(112);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(9);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(112);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(111);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(112);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(113);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(sym_true);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(sym_false);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym_false);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_null);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(sym_null);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'a') ADVANCE(151);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'a') ADVANCE(140);
      if (lookahead == 'o') ADVANCE(144);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'a') ADVANCE(140);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'c') ADVANCE(134);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'd') ADVANCE(92);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'e') ADVANCE(115);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'e') ADVANCE(117);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'e') ADVANCE(152);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'e') ADVANCE(147);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'e') ADVANCE(154);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'f') ADVANCE(79);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'f') ADVANCE(133);
      if (lookahead == 'r') ADVANCE(94);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'f') ADVANCE(133);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'f') ADVANCE(150);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'h') ADVANCE(128);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'i') ADVANCE(141);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'i') ADVANCE(148);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'i') ADVANCE(153);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'l') ADVANCE(119);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'l') ADVANCE(138);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'l') ADVANCE(149);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'm') ADVANCE(137);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'n') ADVANCE(124);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'o') ADVANCE(144);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'r') ADVANCE(71);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'r') ADVANCE(157);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 's') ADVANCE(90);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 's') ADVANCE(88);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 's') ADVANCE(155);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 's') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 's') ADVANCE(129);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 't') ADVANCE(123);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 't') ADVANCE(76);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 't') ADVANCE(96);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 't') ADVANCE(98);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 't') ADVANCE(146);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'u') ADVANCE(139);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'u') ADVANCE(125);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(sym_ident);
      if (lookahead == 'x') ADVANCE(136);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym_ident);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(159);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 2},
  [2] = {.lex_state = 2},
  [3] = {.lex_state = 2},
  [4] = {.lex_state = 2},
  [5] = {.lex_state = 2},
  [6] = {.lex_state = 2},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 4},
  [9] = {.lex_state = 2},
  [10] = {.lex_state = 2},
  [11] = {.lex_state = 2},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 2},
  [14] = {.lex_state = 4},
  [15] = {.lex_state = 4},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 4},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 5},
  [22] = {.lex_state = 5},
  [23] = {.lex_state = 5},
  [24] = {.lex_state = 5},
  [25] = {.lex_state = 3},
  [26] = {.lex_state = 5},
  [27] = {.lex_state = 3},
  [28] = {.lex_state = 5},
  [29] = {.lex_state = 5},
  [30] = {.lex_state = 5},
  [31] = {.lex_state = 61},
  [32] = {.lex_state = 4},
  [33] = {.lex_state = 61},
  [34] = {.lex_state = 61},
  [35] = {.lex_state = 3},
  [36] = {.lex_state = 4},
  [37] = {.lex_state = 4},
  [38] = {.lex_state = 4},
  [39] = {.lex_state = 4},
  [40] = {.lex_state = 3},
  [41] = {.lex_state = 4},
  [42] = {.lex_state = 3},
  [43] = {.lex_state = 4},
  [44] = {.lex_state = 3},
  [45] = {.lex_state = 4},
  [46] = {.lex_state = 61},
  [47] = {.lex_state = 4},
  [48] = {.lex_state = 4},
  [49] = {.lex_state = 4},
  [50] = {.lex_state = 4},
  [51] = {.lex_state = 4},
  [52] = {.lex_state = 3},
  [53] = {.lex_state = 4},
  [54] = {.lex_state = 7},
  [55] = {.lex_state = 61},
  [56] = {.lex_state = 61},
  [57] = {.lex_state = 61},
  [58] = {.lex_state = 7},
  [59] = {.lex_state = 7},
  [60] = {.lex_state = 61},
  [61] = {.lex_state = 7},
  [62] = {.lex_state = 61},
  [63] = {.lex_state = 7},
  [64] = {.lex_state = 7},
  [65] = {.lex_state = 61},
  [66] = {.lex_state = 7},
  [67] = {.lex_state = 7},
  [68] = {.lex_state = 7},
  [69] = {.lex_state = 7},
  [70] = {.lex_state = 7},
  [71] = {.lex_state = 7},
  [72] = {.lex_state = 7},
  [73] = {.lex_state = 7},
  [74] = {.lex_state = 7},
  [75] = {.lex_state = 7},
  [76] = {.lex_state = 7},
  [77] = {.lex_state = 61},
  [78] = {.lex_state = 61},
  [79] = {.lex_state = 61},
  [80] = {.lex_state = 4},
  [81] = {.lex_state = 61},
  [82] = {.lex_state = 61},
  [83] = {.lex_state = 61},
  [84] = {.lex_state = 61},
  [85] = {.lex_state = 61},
  [86] = {.lex_state = 61},
  [87] = {.lex_state = 61},
  [88] = {.lex_state = 61},
  [89] = {.lex_state = 61},
  [90] = {.lex_state = 61},
  [91] = {.lex_state = 61},
  [92] = {.lex_state = 61},
  [93] = {.lex_state = 61},
  [94] = {.lex_state = 61},
  [95] = {.lex_state = 61},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 1},
  [105] = {.lex_state = 1},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 0},
  [108] = {.lex_state = 1},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 1},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 1},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 1},
  [115] = {.lex_state = 1},
  [116] = {.lex_state = 1},
  [117] = {.lex_state = 1},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 0},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 0},
  [123] = {.lex_state = 0},
  [124] = {.lex_state = 0},
  [125] = {.lex_state = 0},
  [126] = {.lex_state = 0},
  [127] = {.lex_state = 0},
  [128] = {.lex_state = 0},
  [129] = {.lex_state = 0},
  [130] = {.lex_state = 0},
  [131] = {.lex_state = 0},
  [132] = {.lex_state = 0},
  [133] = {.lex_state = 0},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 13},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 0},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 0},
  [142] = {.lex_state = 0},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 0},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 0},
  [148] = {.lex_state = 0},
  [149] = {.lex_state = 13},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 0},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 0},
  [156] = {.lex_state = 0},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 0},
  [160] = {.lex_state = 0},
  [161] = {.lex_state = 13},
  [162] = {.lex_state = 0},
  [163] = {.lex_state = 13},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 0},
  [166] = {.lex_state = 13},
  [167] = {.lex_state = 0},
  [168] = {.lex_state = 0},
  [169] = {.lex_state = 0},
  [170] = {.lex_state = 0},
  [171] = {.lex_state = 4},
  [172] = {.lex_state = 2},
  [173] = {.lex_state = 2},
  [174] = {.lex_state = 13},
  [175] = {.lex_state = 4},
  [176] = {.lex_state = 0},
  [177] = {.lex_state = 13},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_for] = ACTIONS(1),
    [anon_sym_in] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_set] = ACTIONS(1),
    [anon_sym_LPAREN_RPAREN] = ACTIONS(1),
    [anon_sym_if] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [anon_sym_matches] = ACTIONS(1),
    [anon_sym_exists] = ACTIONS(1),
    [anon_sym_and] = ACTIONS(1),
    [anon_sym_or] = ACTIONS(1),
    [anon_sym_limit] = ACTIONS(1),
    [anon_sym_offset] = ACTIONS(1),
    [sym_pos_int] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
    [sym_null] = ACTIONS(1),
  },
  [1] = {
    [sym_query] = STATE(164),
    [sym_array_query] = STATE(81),
    [sym_element_query] = STATE(81),
    [anon_sym_LBRACK] = ACTIONS(3),
    [anon_sym_LPAREN] = ACTIONS(5),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 4,
    ACTIONS(11), 1,
      anon_sym_DOT,
    STATE(5), 1,
      aux_sym_path_repeat1,
    ACTIONS(7), 6,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(9), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [29] = 8,
    ACTIONS(21), 1,
      anon_sym_exists,
    STATE(32), 1,
      sym_logical_op,
    STATE(61), 1,
      sym_comparator,
    ACTIONS(13), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(23), 2,
      anon_sym_and,
      anon_sym_or,
    ACTIONS(19), 3,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
    ACTIONS(17), 4,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(15), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [66] = 4,
    ACTIONS(29), 1,
      anon_sym_DOT,
    STATE(4), 1,
      aux_sym_path_repeat1,
    ACTIONS(25), 6,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(27), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [95] = 4,
    ACTIONS(11), 1,
      anon_sym_DOT,
    STATE(4), 1,
      aux_sym_path_repeat1,
    ACTIONS(32), 6,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(34), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [124] = 2,
    ACTIONS(25), 7,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_DOT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(27), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [148] = 4,
    ACTIONS(36), 1,
      anon_sym_DOT,
    STATE(16), 1,
      aux_sym_path_repeat1,
    ACTIONS(9), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(7), 13,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [175] = 9,
    ACTIONS(38), 1,
      anon_sym_LBRACK,
    ACTIONS(40), 1,
      anon_sym_LPAREN,
    ACTIONS(42), 1,
      anon_sym_LBRACE,
    ACTIONS(44), 1,
      anon_sym_DQUOTE,
    ACTIONS(46), 1,
      sym_number,
    ACTIONS(50), 1,
      sym_ident,
    STATE(71), 2,
      sym_array_query,
      sym_element_query,
    ACTIONS(48), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(67), 7,
      sym_query,
      sym__expression,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [212] = 2,
    ACTIONS(52), 6,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(54), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [235] = 2,
    ACTIONS(56), 6,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(58), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [258] = 2,
    ACTIONS(60), 6,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(62), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [281] = 2,
    ACTIONS(64), 6,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(66), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [304] = 2,
    ACTIONS(68), 6,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(70), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [327] = 9,
    ACTIONS(5), 1,
      anon_sym_LPAREN,
    ACTIONS(72), 1,
      anon_sym_LBRACK,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(78), 1,
      sym_number,
    ACTIONS(82), 1,
      sym_ident,
    STATE(81), 2,
      sym_array_query,
      sym_element_query,
    ACTIONS(80), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(157), 7,
      sym_query,
      sym__expression,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [364] = 9,
    ACTIONS(5), 1,
      anon_sym_LPAREN,
    ACTIONS(84), 1,
      anon_sym_LBRACK,
    ACTIONS(86), 1,
      anon_sym_LBRACE,
    ACTIONS(88), 1,
      anon_sym_DQUOTE,
    ACTIONS(90), 1,
      sym_number,
    ACTIONS(94), 1,
      sym_ident,
    STATE(81), 2,
      sym_array_query,
      sym_element_query,
    ACTIONS(92), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(91), 7,
      sym_query,
      sym__expression,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [401] = 4,
    ACTIONS(36), 1,
      anon_sym_DOT,
    STATE(18), 1,
      aux_sym_path_repeat1,
    ACTIONS(34), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(32), 13,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [428] = 2,
    ACTIONS(96), 6,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(98), 12,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [451] = 4,
    ACTIONS(100), 1,
      anon_sym_DOT,
    STATE(18), 1,
      aux_sym_path_repeat1,
    ACTIONS(27), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(25), 13,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [478] = 9,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(103), 1,
      anon_sym_LBRACK,
    ACTIONS(105), 1,
      anon_sym_LPAREN,
    ACTIONS(107), 1,
      sym_number,
    STATE(120), 2,
      sym_array_query,
      sym_element_query,
    ACTIONS(109), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(118), 7,
      sym_query,
      sym__expression,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [515] = 2,
    ACTIONS(27), 3,
      anon_sym_EQ,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(25), 14,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_DOT,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [537] = 10,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(115), 1,
      sym_number,
    STATE(31), 1,
      sym_iterator,
    STATE(170), 1,
      sym__query_body,
    ACTIONS(117), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(99), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [574] = 10,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(115), 1,
      sym_number,
    STATE(31), 1,
      sym_iterator,
    STATE(165), 1,
      sym__query_body,
    ACTIONS(117), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(99), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [611] = 10,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(119), 1,
      sym_number,
    STATE(31), 1,
      sym_iterator,
    STATE(162), 1,
      sym__query_body,
    ACTIONS(121), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(150), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [648] = 10,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(123), 1,
      sym_number,
    STATE(31), 1,
      sym_iterator,
    STATE(170), 1,
      sym__query_body,
    ACTIONS(125), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(100), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [685] = 2,
    ACTIONS(54), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(52), 14,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
  [706] = 10,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(119), 1,
      sym_number,
    STATE(31), 1,
      sym_iterator,
    STATE(158), 1,
      sym__query_body,
    ACTIONS(121), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(150), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [743] = 2,
    ACTIONS(70), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(68), 14,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_COLON,
  [764] = 10,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(119), 1,
      sym_number,
    STATE(31), 1,
      sym_iterator,
    STATE(170), 1,
      sym__query_body,
    ACTIONS(121), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(150), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [801] = 10,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(127), 1,
      sym_number,
    STATE(31), 1,
      sym_iterator,
    STATE(159), 1,
      sym__query_body,
    ACTIONS(129), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(101), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [838] = 10,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(119), 1,
      sym_number,
    STATE(31), 1,
      sym_iterator,
    STATE(167), 1,
      sym__query_body,
    ACTIONS(121), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(150), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [875] = 11,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(133), 1,
      anon_sym_set,
    ACTIONS(135), 1,
      anon_sym_if,
    ACTIONS(137), 1,
      anon_sym_limit,
    ACTIONS(139), 1,
      anon_sym_offset,
    ACTIONS(141), 1,
      sym_ident,
    STATE(96), 1,
      sym_limit,
    STATE(103), 1,
      sym_offset,
    STATE(147), 1,
      sym_update_assignment,
    ACTIONS(131), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    STATE(33), 4,
      sym_iterator,
      sym_assignment,
      sym_condition,
      aux_sym__query_body_repeat1,
  [913] = 9,
    ACTIONS(143), 1,
      anon_sym_LBRACK,
    ACTIONS(145), 1,
      anon_sym_LPAREN,
    ACTIONS(147), 1,
      anon_sym_LBRACE,
    ACTIONS(149), 1,
      anon_sym_DQUOTE,
    ACTIONS(151), 1,
      sym_number,
    ACTIONS(155), 1,
      sym_ident,
    STATE(86), 1,
      sym_comparison,
    ACTIONS(153), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(3), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [947] = 11,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(133), 1,
      anon_sym_set,
    ACTIONS(135), 1,
      anon_sym_if,
    ACTIONS(137), 1,
      anon_sym_limit,
    ACTIONS(139), 1,
      anon_sym_offset,
    ACTIONS(141), 1,
      sym_ident,
    STATE(98), 1,
      sym_limit,
    STATE(109), 1,
      sym_offset,
    STATE(152), 1,
      sym_update_assignment,
    ACTIONS(157), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    STATE(60), 4,
      sym_iterator,
      sym_assignment,
      sym_condition,
      aux_sym__query_body_repeat1,
  [985] = 11,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(133), 1,
      anon_sym_set,
    ACTIONS(135), 1,
      anon_sym_if,
    ACTIONS(137), 1,
      anon_sym_limit,
    ACTIONS(139), 1,
      anon_sym_offset,
    ACTIONS(141), 1,
      sym_ident,
    STATE(98), 1,
      sym_limit,
    STATE(109), 1,
      sym_offset,
    STATE(152), 1,
      sym_update_assignment,
    ACTIONS(157), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    STATE(46), 4,
      sym_iterator,
      sym_assignment,
      sym_condition,
      aux_sym__query_body_repeat1,
  [1023] = 2,
    ACTIONS(62), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(60), 13,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1043] = 9,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(159), 1,
      anon_sym_LPAREN,
    ACTIONS(161), 1,
      sym_number,
    STATE(86), 1,
      sym_comparison,
    ACTIONS(163), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(52), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1077] = 9,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(159), 1,
      anon_sym_LPAREN,
    ACTIONS(161), 1,
      sym_number,
    STATE(94), 1,
      sym_comparison,
    ACTIONS(163), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(52), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1111] = 9,
    ACTIONS(143), 1,
      anon_sym_LBRACK,
    ACTIONS(145), 1,
      anon_sym_LPAREN,
    ACTIONS(147), 1,
      anon_sym_LBRACE,
    ACTIONS(149), 1,
      anon_sym_DQUOTE,
    ACTIONS(151), 1,
      sym_number,
    ACTIONS(155), 1,
      sym_ident,
    STATE(94), 1,
      sym_comparison,
    ACTIONS(153), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(3), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1145] = 9,
    ACTIONS(143), 1,
      anon_sym_LBRACK,
    ACTIONS(145), 1,
      anon_sym_LPAREN,
    ACTIONS(147), 1,
      anon_sym_LBRACE,
    ACTIONS(149), 1,
      anon_sym_DQUOTE,
    ACTIONS(151), 1,
      sym_number,
    ACTIONS(155), 1,
      sym_ident,
    STATE(92), 1,
      sym_comparison,
    ACTIONS(153), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(3), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1179] = 2,
    ACTIONS(66), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(64), 13,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1199] = 9,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(159), 1,
      anon_sym_LPAREN,
    ACTIONS(161), 1,
      sym_number,
    STATE(176), 1,
      sym_comparison,
    ACTIONS(163), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(52), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1233] = 2,
    ACTIONS(98), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(96), 13,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1253] = 9,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(159), 1,
      anon_sym_LPAREN,
    ACTIONS(161), 1,
      sym_number,
    STATE(92), 1,
      sym_comparison,
    ACTIONS(163), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(52), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1287] = 2,
    ACTIONS(58), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(56), 13,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_for,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
      anon_sym_exists,
      anon_sym_and,
      anon_sym_or,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1307] = 9,
    ACTIONS(143), 1,
      anon_sym_LBRACK,
    ACTIONS(145), 1,
      anon_sym_LPAREN,
    ACTIONS(147), 1,
      anon_sym_LBRACE,
    ACTIONS(149), 1,
      anon_sym_DQUOTE,
    ACTIONS(151), 1,
      sym_number,
    ACTIONS(155), 1,
      sym_ident,
    STATE(83), 1,
      sym_comparison,
    ACTIONS(153), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(3), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1341] = 11,
    ACTIONS(113), 1,
      anon_sym_for,
    ACTIONS(133), 1,
      anon_sym_set,
    ACTIONS(135), 1,
      anon_sym_if,
    ACTIONS(137), 1,
      anon_sym_limit,
    ACTIONS(139), 1,
      anon_sym_offset,
    ACTIONS(141), 1,
      sym_ident,
    STATE(97), 1,
      sym_limit,
    STATE(107), 1,
      sym_offset,
    STATE(148), 1,
      sym_update_assignment,
    ACTIONS(165), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    STATE(60), 4,
      sym_iterator,
      sym_assignment,
      sym_condition,
      aux_sym__query_body_repeat1,
  [1379] = 9,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(159), 1,
      anon_sym_LPAREN,
    ACTIONS(161), 1,
      sym_number,
    STATE(160), 1,
      sym_comparison,
    ACTIONS(163), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(52), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1413] = 7,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(167), 1,
      sym_number,
    ACTIONS(169), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(144), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1441] = 7,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(171), 1,
      sym_number,
    ACTIONS(173), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(143), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1469] = 7,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(175), 1,
      sym_number,
    ACTIONS(177), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(141), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1497] = 7,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(179), 1,
      sym_number,
    ACTIONS(181), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(154), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1525] = 7,
    ACTIONS(13), 1,
      anon_sym_RPAREN,
    ACTIONS(187), 1,
      anon_sym_exists,
    STATE(36), 1,
      sym_logical_op,
    STATE(111), 1,
      sym_comparator,
    ACTIONS(185), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(189), 2,
      anon_sym_and,
      anon_sym_or,
    ACTIONS(183), 5,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_matches,
  [1553] = 7,
    ACTIONS(74), 1,
      anon_sym_LBRACE,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    ACTIONS(82), 1,
      sym_ident,
    ACTIONS(111), 1,
      anon_sym_LBRACK,
    ACTIONS(191), 1,
      sym_number,
    ACTIONS(193), 3,
      sym_true,
      sym_false,
      sym_null,
    STATE(155), 5,
      sym_path,
      sym__value,
      sym_object,
      sym_array,
      sym_string,
  [1581] = 4,
    ACTIONS(195), 1,
      anon_sym_DOT,
    STATE(59), 1,
      aux_sym_path_repeat1,
    ACTIONS(32), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(34), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1602] = 4,
    ACTIONS(197), 1,
      anon_sym_DOT,
    STATE(56), 1,
      aux_sym_path_repeat1,
    ACTIONS(7), 4,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
    ACTIONS(9), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1623] = 4,
    ACTIONS(197), 1,
      anon_sym_DOT,
    STATE(57), 1,
      aux_sym_path_repeat1,
    ACTIONS(32), 4,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
    ACTIONS(34), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1644] = 4,
    ACTIONS(199), 1,
      anon_sym_DOT,
    STATE(57), 1,
      aux_sym_path_repeat1,
    ACTIONS(25), 4,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
    ACTIONS(27), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1665] = 4,
    ACTIONS(195), 1,
      anon_sym_DOT,
    STATE(54), 1,
      aux_sym_path_repeat1,
    ACTIONS(7), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(9), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1686] = 4,
    ACTIONS(202), 1,
      anon_sym_DOT,
    STATE(59), 1,
      aux_sym_path_repeat1,
    ACTIONS(25), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(27), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1707] = 6,
    ACTIONS(207), 1,
      anon_sym_for,
    ACTIONS(212), 1,
      anon_sym_if,
    ACTIONS(215), 1,
      sym_ident,
    ACTIONS(205), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(210), 3,
      anon_sym_set,
      anon_sym_limit,
      anon_sym_offset,
    STATE(60), 4,
      sym_iterator,
      sym_assignment,
      sym_condition,
      aux_sym__query_body_repeat1,
  [1732] = 4,
    STATE(39), 1,
      sym_logical_op,
    ACTIONS(23), 2,
      anon_sym_and,
      anon_sym_or,
    ACTIONS(218), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(220), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1752] = 2,
    ACTIONS(25), 5,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_LPAREN_RPAREN,
      anon_sym_DOT,
    ACTIONS(27), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1768] = 2,
    ACTIONS(25), 3,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_DOT,
    ACTIONS(27), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1784] = 4,
    STATE(38), 1,
      sym_logical_op,
    ACTIONS(23), 2,
      anon_sym_and,
      anon_sym_or,
    ACTIONS(222), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(224), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1804] = 5,
    ACTIONS(226), 1,
      anon_sym_LBRACK,
    ACTIONS(232), 1,
      anon_sym_LPAREN_RPAREN,
    STATE(85), 1,
      sym_array,
    ACTIONS(228), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(230), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1826] = 2,
    ACTIONS(234), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(236), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1841] = 2,
    ACTIONS(238), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(240), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1856] = 2,
    ACTIONS(242), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(244), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1871] = 2,
    ACTIONS(52), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(54), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1886] = 2,
    ACTIONS(60), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(62), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1901] = 2,
    ACTIONS(246), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(248), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1916] = 2,
    ACTIONS(64), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(66), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1931] = 2,
    ACTIONS(68), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(70), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1946] = 2,
    ACTIONS(56), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(58), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1961] = 2,
    ACTIONS(250), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(252), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1976] = 2,
    ACTIONS(96), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(98), 8,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_and,
      anon_sym_or,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [1991] = 4,
    ACTIONS(226), 1,
      anon_sym_LBRACK,
    STATE(82), 1,
      sym_array,
    ACTIONS(254), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(256), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2010] = 2,
    ACTIONS(242), 3,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(244), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2024] = 2,
    ACTIONS(234), 3,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(236), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2038] = 2,
    ACTIONS(260), 4,
      sym_true,
      sym_false,
      sym_null,
      sym_ident,
    ACTIONS(258), 5,
      anon_sym_LBRACK,
      anon_sym_LPAREN,
      anon_sym_LBRACE,
      anon_sym_DQUOTE,
      sym_number,
  [2052] = 2,
    ACTIONS(246), 3,
      ts_builtin_sym_end,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(248), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2066] = 2,
    ACTIONS(262), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(264), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2079] = 2,
    ACTIONS(266), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(268), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2092] = 2,
    ACTIONS(60), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(62), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2105] = 2,
    ACTIONS(254), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(256), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2118] = 2,
    ACTIONS(270), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(272), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2131] = 2,
    ACTIONS(64), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(66), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2144] = 2,
    ACTIONS(68), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(70), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2157] = 2,
    ACTIONS(96), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(98), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2170] = 2,
    ACTIONS(56), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(58), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2183] = 2,
    ACTIONS(274), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(276), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2196] = 2,
    ACTIONS(278), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(280), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2209] = 2,
    ACTIONS(52), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(54), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2222] = 2,
    ACTIONS(282), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(284), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2235] = 2,
    ACTIONS(286), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
    ACTIONS(288), 6,
      anon_sym_for,
      anon_sym_set,
      anon_sym_if,
      anon_sym_limit,
      anon_sym_offset,
      sym_ident,
  [2248] = 5,
    ACTIONS(290), 1,
      anon_sym_set,
    ACTIONS(292), 1,
      anon_sym_offset,
    STATE(109), 1,
      sym_offset,
    STATE(152), 1,
      sym_update_assignment,
    ACTIONS(157), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2265] = 5,
    ACTIONS(290), 1,
      anon_sym_set,
    ACTIONS(292), 1,
      anon_sym_offset,
    STATE(106), 1,
      sym_offset,
    STATE(156), 1,
      sym_update_assignment,
    ACTIONS(294), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2282] = 5,
    ACTIONS(290), 1,
      anon_sym_set,
    ACTIONS(292), 1,
      anon_sym_offset,
    STATE(107), 1,
      sym_offset,
    STATE(148), 1,
      sym_update_assignment,
    ACTIONS(165), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2299] = 5,
    ACTIONS(296), 1,
      anon_sym_RBRACK,
    ACTIONS(298), 1,
      anon_sym_for,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    STATE(34), 1,
      sym_iterator,
    STATE(134), 1,
      aux_sym_array_repeat1,
  [2315] = 5,
    ACTIONS(298), 1,
      anon_sym_for,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    ACTIONS(302), 1,
      anon_sym_RBRACK,
    STATE(34), 1,
      sym_iterator,
    STATE(138), 1,
      aux_sym_array_repeat1,
  [2331] = 5,
    ACTIONS(298), 1,
      anon_sym_for,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    ACTIONS(304), 1,
      anon_sym_RBRACK,
    STATE(34), 1,
      sym_iterator,
    STATE(133), 1,
      aux_sym_array_repeat1,
  [2347] = 1,
    ACTIONS(306), 4,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_set,
      anon_sym_offset,
  [2354] = 3,
    ACTIONS(290), 1,
      anon_sym_set,
    STATE(152), 1,
      sym_update_assignment,
    ACTIONS(157), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2365] = 3,
    ACTIONS(308), 1,
      anon_sym_DQUOTE,
    STATE(117), 1,
      aux_sym__string_content,
    ACTIONS(310), 2,
      sym_string_content,
      sym_escape_sequence,
  [2376] = 3,
    ACTIONS(312), 1,
      anon_sym_DQUOTE,
    STATE(104), 1,
      aux_sym__string_content,
    ACTIONS(314), 2,
      sym_string_content,
      sym_escape_sequence,
  [2387] = 3,
    ACTIONS(290), 1,
      anon_sym_set,
    STATE(151), 1,
      sym_update_assignment,
    ACTIONS(316), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2398] = 3,
    ACTIONS(290), 1,
      anon_sym_set,
    STATE(156), 1,
      sym_update_assignment,
    ACTIONS(294), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2409] = 3,
    ACTIONS(318), 1,
      anon_sym_DQUOTE,
    STATE(117), 1,
      aux_sym__string_content,
    ACTIONS(310), 2,
      sym_string_content,
      sym_escape_sequence,
  [2420] = 3,
    ACTIONS(290), 1,
      anon_sym_set,
    STATE(148), 1,
      sym_update_assignment,
    ACTIONS(165), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2431] = 3,
    ACTIONS(320), 1,
      anon_sym_DQUOTE,
    STATE(108), 1,
      aux_sym__string_content,
    ACTIONS(322), 2,
      sym_string_content,
      sym_escape_sequence,
  [2442] = 3,
    ACTIONS(218), 1,
      anon_sym_RPAREN,
    STATE(43), 1,
      sym_logical_op,
    ACTIONS(189), 2,
      anon_sym_and,
      anon_sym_or,
  [2453] = 3,
    ACTIONS(324), 1,
      anon_sym_DQUOTE,
    STATE(117), 1,
      aux_sym__string_content,
    ACTIONS(310), 2,
      sym_string_content,
      sym_escape_sequence,
  [2464] = 3,
    ACTIONS(222), 1,
      anon_sym_RPAREN,
    STATE(37), 1,
      sym_logical_op,
    ACTIONS(189), 2,
      anon_sym_and,
      anon_sym_or,
  [2475] = 3,
    ACTIONS(326), 1,
      anon_sym_DQUOTE,
    STATE(117), 1,
      aux_sym__string_content,
    ACTIONS(310), 2,
      sym_string_content,
      sym_escape_sequence,
  [2486] = 3,
    ACTIONS(328), 1,
      anon_sym_DQUOTE,
    STATE(112), 1,
      aux_sym__string_content,
    ACTIONS(330), 2,
      sym_string_content,
      sym_escape_sequence,
  [2497] = 3,
    ACTIONS(332), 1,
      anon_sym_DQUOTE,
    STATE(114), 1,
      aux_sym__string_content,
    ACTIONS(334), 2,
      sym_string_content,
      sym_escape_sequence,
  [2508] = 3,
    ACTIONS(336), 1,
      anon_sym_DQUOTE,
    STATE(117), 1,
      aux_sym__string_content,
    ACTIONS(338), 2,
      sym_string_content,
      sym_escape_sequence,
  [2519] = 1,
    ACTIONS(238), 3,
      anon_sym_RPAREN,
      anon_sym_and,
      anon_sym_or,
  [2525] = 3,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    ACTIONS(343), 1,
      anon_sym_RBRACE,
    STATE(142), 1,
      aux_sym_object_repeat1,
  [2535] = 1,
    ACTIONS(246), 3,
      anon_sym_RPAREN,
      anon_sym_and,
      anon_sym_or,
  [2541] = 3,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    ACTIONS(345), 1,
      anon_sym_RBRACE,
    STATE(142), 1,
      aux_sym_object_repeat1,
  [2551] = 1,
    ACTIONS(242), 3,
      anon_sym_RPAREN,
      anon_sym_and,
      anon_sym_or,
  [2557] = 1,
    ACTIONS(234), 3,
      anon_sym_RPAREN,
      anon_sym_and,
      anon_sym_or,
  [2563] = 3,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    STATE(136), 1,
      sym_pair,
    STATE(169), 1,
      sym_string,
  [2573] = 3,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    STATE(153), 1,
      sym_pair,
    STATE(169), 1,
      sym_string,
  [2583] = 1,
    ACTIONS(250), 3,
      anon_sym_RPAREN,
      anon_sym_and,
      anon_sym_or,
  [2589] = 3,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    STATE(140), 1,
      sym_pair,
    STATE(169), 1,
      sym_string,
  [2599] = 3,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    STATE(132), 1,
      sym_pair,
    STATE(169), 1,
      sym_string,
  [2609] = 3,
    ACTIONS(76), 1,
      anon_sym_DQUOTE,
    STATE(145), 1,
      sym_pair,
    STATE(169), 1,
      sym_string,
  [2619] = 1,
    ACTIONS(347), 3,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
      anon_sym_set,
  [2625] = 3,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    ACTIONS(349), 1,
      anon_sym_RBRACE,
    STATE(142), 1,
      aux_sym_object_repeat1,
  [2635] = 3,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    ACTIONS(351), 1,
      anon_sym_RBRACE,
    STATE(121), 1,
      aux_sym_object_repeat1,
  [2645] = 3,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    ACTIONS(353), 1,
      anon_sym_RBRACK,
    STATE(139), 1,
      aux_sym_array_repeat1,
  [2655] = 3,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    ACTIONS(355), 1,
      anon_sym_RBRACK,
    STATE(139), 1,
      aux_sym_array_repeat1,
  [2665] = 3,
    ACTIONS(357), 1,
      sym_ident,
    STATE(65), 1,
      sym_path,
    STATE(95), 1,
      sym__source,
  [2675] = 3,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    ACTIONS(359), 1,
      anon_sym_RBRACE,
    STATE(131), 1,
      aux_sym_object_repeat1,
  [2685] = 3,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    ACTIONS(361), 1,
      anon_sym_RBRACE,
    STATE(142), 1,
      aux_sym_object_repeat1,
  [2695] = 3,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    ACTIONS(363), 1,
      anon_sym_RBRACK,
    STATE(139), 1,
      aux_sym_array_repeat1,
  [2705] = 3,
    ACTIONS(365), 1,
      anon_sym_RBRACK,
    ACTIONS(367), 1,
      anon_sym_COMMA,
    STATE(139), 1,
      aux_sym_array_repeat1,
  [2715] = 3,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    ACTIONS(370), 1,
      anon_sym_RBRACE,
    STATE(137), 1,
      aux_sym_object_repeat1,
  [2725] = 3,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    ACTIONS(302), 1,
      anon_sym_RBRACK,
    STATE(138), 1,
      aux_sym_array_repeat1,
  [2735] = 3,
    ACTIONS(372), 1,
      anon_sym_COMMA,
    ACTIONS(375), 1,
      anon_sym_RBRACE,
    STATE(142), 1,
      aux_sym_object_repeat1,
  [2745] = 3,
    ACTIONS(296), 1,
      anon_sym_RBRACK,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    STATE(134), 1,
      aux_sym_array_repeat1,
  [2755] = 3,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    ACTIONS(377), 1,
      anon_sym_RBRACK,
    STATE(146), 1,
      aux_sym_array_repeat1,
  [2765] = 3,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    ACTIONS(379), 1,
      anon_sym_RBRACE,
    STATE(119), 1,
      aux_sym_object_repeat1,
  [2775] = 3,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    ACTIONS(381), 1,
      anon_sym_RBRACK,
    STATE(139), 1,
      aux_sym_array_repeat1,
  [2785] = 1,
    ACTIONS(157), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2790] = 1,
    ACTIONS(294), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2795] = 2,
    ACTIONS(383), 1,
      sym_ident,
    STATE(175), 1,
      sym_path,
  [2802] = 2,
    ACTIONS(298), 1,
      anon_sym_for,
    STATE(34), 1,
      sym_iterator,
  [2809] = 1,
    ACTIONS(385), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2814] = 1,
    ACTIONS(165), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2819] = 1,
    ACTIONS(375), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [2824] = 1,
    ACTIONS(365), 2,
      anon_sym_RBRACK,
      anon_sym_COMMA,
  [2829] = 1,
    ACTIONS(387), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [2834] = 1,
    ACTIONS(316), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2839] = 1,
    ACTIONS(389), 2,
      anon_sym_RBRACK,
      anon_sym_RPAREN,
  [2844] = 1,
    ACTIONS(391), 1,
      anon_sym_RPAREN,
  [2848] = 1,
    ACTIONS(393), 1,
      anon_sym_RBRACK,
  [2852] = 1,
    ACTIONS(395), 1,
      anon_sym_RPAREN,
  [2856] = 1,
    ACTIONS(397), 1,
      sym_ident,
  [2860] = 1,
    ACTIONS(399), 1,
      anon_sym_RPAREN,
  [2864] = 1,
    ACTIONS(401), 1,
      sym_ident,
  [2868] = 1,
    ACTIONS(403), 1,
      ts_builtin_sym_end,
  [2872] = 1,
    ACTIONS(405), 1,
      anon_sym_RBRACK,
  [2876] = 1,
    ACTIONS(407), 1,
      sym_ident,
  [2880] = 1,
    ACTIONS(409), 1,
      anon_sym_RPAREN,
  [2884] = 1,
    ACTIONS(411), 1,
      anon_sym_in,
  [2888] = 1,
    ACTIONS(413), 1,
      anon_sym_COLON,
  [2892] = 1,
    ACTIONS(415), 1,
      anon_sym_RBRACK,
  [2896] = 1,
    ACTIONS(417), 1,
      anon_sym_EQ,
  [2900] = 1,
    ACTIONS(419), 1,
      sym_pos_int,
  [2904] = 1,
    ACTIONS(421), 1,
      sym_pos_int,
  [2908] = 1,
    ACTIONS(423), 1,
      sym_ident,
  [2912] = 1,
    ACTIONS(425), 1,
      anon_sym_EQ,
  [2916] = 1,
    ACTIONS(427), 1,
      anon_sym_RPAREN,
  [2920] = 1,
    ACTIONS(429), 1,
      sym_ident,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 29,
  [SMALL_STATE(4)] = 66,
  [SMALL_STATE(5)] = 95,
  [SMALL_STATE(6)] = 124,
  [SMALL_STATE(7)] = 148,
  [SMALL_STATE(8)] = 175,
  [SMALL_STATE(9)] = 212,
  [SMALL_STATE(10)] = 235,
  [SMALL_STATE(11)] = 258,
  [SMALL_STATE(12)] = 281,
  [SMALL_STATE(13)] = 304,
  [SMALL_STATE(14)] = 327,
  [SMALL_STATE(15)] = 364,
  [SMALL_STATE(16)] = 401,
  [SMALL_STATE(17)] = 428,
  [SMALL_STATE(18)] = 451,
  [SMALL_STATE(19)] = 478,
  [SMALL_STATE(20)] = 515,
  [SMALL_STATE(21)] = 537,
  [SMALL_STATE(22)] = 574,
  [SMALL_STATE(23)] = 611,
  [SMALL_STATE(24)] = 648,
  [SMALL_STATE(25)] = 685,
  [SMALL_STATE(26)] = 706,
  [SMALL_STATE(27)] = 743,
  [SMALL_STATE(28)] = 764,
  [SMALL_STATE(29)] = 801,
  [SMALL_STATE(30)] = 838,
  [SMALL_STATE(31)] = 875,
  [SMALL_STATE(32)] = 913,
  [SMALL_STATE(33)] = 947,
  [SMALL_STATE(34)] = 985,
  [SMALL_STATE(35)] = 1023,
  [SMALL_STATE(36)] = 1043,
  [SMALL_STATE(37)] = 1077,
  [SMALL_STATE(38)] = 1111,
  [SMALL_STATE(39)] = 1145,
  [SMALL_STATE(40)] = 1179,
  [SMALL_STATE(41)] = 1199,
  [SMALL_STATE(42)] = 1233,
  [SMALL_STATE(43)] = 1253,
  [SMALL_STATE(44)] = 1287,
  [SMALL_STATE(45)] = 1307,
  [SMALL_STATE(46)] = 1341,
  [SMALL_STATE(47)] = 1379,
  [SMALL_STATE(48)] = 1413,
  [SMALL_STATE(49)] = 1441,
  [SMALL_STATE(50)] = 1469,
  [SMALL_STATE(51)] = 1497,
  [SMALL_STATE(52)] = 1525,
  [SMALL_STATE(53)] = 1553,
  [SMALL_STATE(54)] = 1581,
  [SMALL_STATE(55)] = 1602,
  [SMALL_STATE(56)] = 1623,
  [SMALL_STATE(57)] = 1644,
  [SMALL_STATE(58)] = 1665,
  [SMALL_STATE(59)] = 1686,
  [SMALL_STATE(60)] = 1707,
  [SMALL_STATE(61)] = 1732,
  [SMALL_STATE(62)] = 1752,
  [SMALL_STATE(63)] = 1768,
  [SMALL_STATE(64)] = 1784,
  [SMALL_STATE(65)] = 1804,
  [SMALL_STATE(66)] = 1826,
  [SMALL_STATE(67)] = 1841,
  [SMALL_STATE(68)] = 1856,
  [SMALL_STATE(69)] = 1871,
  [SMALL_STATE(70)] = 1886,
  [SMALL_STATE(71)] = 1901,
  [SMALL_STATE(72)] = 1916,
  [SMALL_STATE(73)] = 1931,
  [SMALL_STATE(74)] = 1946,
  [SMALL_STATE(75)] = 1961,
  [SMALL_STATE(76)] = 1976,
  [SMALL_STATE(77)] = 1991,
  [SMALL_STATE(78)] = 2010,
  [SMALL_STATE(79)] = 2024,
  [SMALL_STATE(80)] = 2038,
  [SMALL_STATE(81)] = 2052,
  [SMALL_STATE(82)] = 2066,
  [SMALL_STATE(83)] = 2079,
  [SMALL_STATE(84)] = 2092,
  [SMALL_STATE(85)] = 2105,
  [SMALL_STATE(86)] = 2118,
  [SMALL_STATE(87)] = 2131,
  [SMALL_STATE(88)] = 2144,
  [SMALL_STATE(89)] = 2157,
  [SMALL_STATE(90)] = 2170,
  [SMALL_STATE(91)] = 2183,
  [SMALL_STATE(92)] = 2196,
  [SMALL_STATE(93)] = 2209,
  [SMALL_STATE(94)] = 2222,
  [SMALL_STATE(95)] = 2235,
  [SMALL_STATE(96)] = 2248,
  [SMALL_STATE(97)] = 2265,
  [SMALL_STATE(98)] = 2282,
  [SMALL_STATE(99)] = 2299,
  [SMALL_STATE(100)] = 2315,
  [SMALL_STATE(101)] = 2331,
  [SMALL_STATE(102)] = 2347,
  [SMALL_STATE(103)] = 2354,
  [SMALL_STATE(104)] = 2365,
  [SMALL_STATE(105)] = 2376,
  [SMALL_STATE(106)] = 2387,
  [SMALL_STATE(107)] = 2398,
  [SMALL_STATE(108)] = 2409,
  [SMALL_STATE(109)] = 2420,
  [SMALL_STATE(110)] = 2431,
  [SMALL_STATE(111)] = 2442,
  [SMALL_STATE(112)] = 2453,
  [SMALL_STATE(113)] = 2464,
  [SMALL_STATE(114)] = 2475,
  [SMALL_STATE(115)] = 2486,
  [SMALL_STATE(116)] = 2497,
  [SMALL_STATE(117)] = 2508,
  [SMALL_STATE(118)] = 2519,
  [SMALL_STATE(119)] = 2525,
  [SMALL_STATE(120)] = 2535,
  [SMALL_STATE(121)] = 2541,
  [SMALL_STATE(122)] = 2551,
  [SMALL_STATE(123)] = 2557,
  [SMALL_STATE(124)] = 2563,
  [SMALL_STATE(125)] = 2573,
  [SMALL_STATE(126)] = 2583,
  [SMALL_STATE(127)] = 2589,
  [SMALL_STATE(128)] = 2599,
  [SMALL_STATE(129)] = 2609,
  [SMALL_STATE(130)] = 2619,
  [SMALL_STATE(131)] = 2625,
  [SMALL_STATE(132)] = 2635,
  [SMALL_STATE(133)] = 2645,
  [SMALL_STATE(134)] = 2655,
  [SMALL_STATE(135)] = 2665,
  [SMALL_STATE(136)] = 2675,
  [SMALL_STATE(137)] = 2685,
  [SMALL_STATE(138)] = 2695,
  [SMALL_STATE(139)] = 2705,
  [SMALL_STATE(140)] = 2715,
  [SMALL_STATE(141)] = 2725,
  [SMALL_STATE(142)] = 2735,
  [SMALL_STATE(143)] = 2745,
  [SMALL_STATE(144)] = 2755,
  [SMALL_STATE(145)] = 2765,
  [SMALL_STATE(146)] = 2775,
  [SMALL_STATE(147)] = 2785,
  [SMALL_STATE(148)] = 2790,
  [SMALL_STATE(149)] = 2795,
  [SMALL_STATE(150)] = 2802,
  [SMALL_STATE(151)] = 2809,
  [SMALL_STATE(152)] = 2814,
  [SMALL_STATE(153)] = 2819,
  [SMALL_STATE(154)] = 2824,
  [SMALL_STATE(155)] = 2829,
  [SMALL_STATE(156)] = 2834,
  [SMALL_STATE(157)] = 2839,
  [SMALL_STATE(158)] = 2844,
  [SMALL_STATE(159)] = 2848,
  [SMALL_STATE(160)] = 2852,
  [SMALL_STATE(161)] = 2856,
  [SMALL_STATE(162)] = 2860,
  [SMALL_STATE(163)] = 2864,
  [SMALL_STATE(164)] = 2868,
  [SMALL_STATE(165)] = 2872,
  [SMALL_STATE(166)] = 2876,
  [SMALL_STATE(167)] = 2880,
  [SMALL_STATE(168)] = 2884,
  [SMALL_STATE(169)] = 2888,
  [SMALL_STATE(170)] = 2892,
  [SMALL_STATE(171)] = 2896,
  [SMALL_STATE(172)] = 2900,
  [SMALL_STATE(173)] = 2904,
  [SMALL_STATE(174)] = 2908,
  [SMALL_STATE(175)] = 2912,
  [SMALL_STATE(176)] = 2916,
  [SMALL_STATE(177)] = 2920,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [7] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 1, 0, 0),
  [9] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 1, 0, 0),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison, 1, 0, 1),
  [15] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison, 1, 0, 1),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(80),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0),
  [27] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(163),
  [32] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 2, 0, 0),
  [34] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 2, 0, 0),
  [36] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [38] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [40] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [42] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [44] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [46] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [48] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [50] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 2, 0, 0),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 4, 0, 0),
  [58] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object, 4, 0, 0),
  [60] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 3, 0, 0),
  [62] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 3, 0, 0),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_object, 3, 0, 0),
  [66] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_object, 3, 0, 0),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3, 0, 0),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3, 0, 0),
  [72] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [74] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(157),
  [80] = {.entry = {.count = 1, .reusable = false}}, SHIFT(157),
  [82] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [88] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [90] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [92] = {.entry = {.count = 1, .reusable = false}}, SHIFT(91),
  [94] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array, 4, 0, 0),
  [98] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array, 4, 0, 0),
  [100] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(177),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [109] = {.entry = {.count = 1, .reusable = false}}, SHIFT(118),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [113] = {.entry = {.count = 1, .reusable = false}}, SHIFT(174),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [117] = {.entry = {.count = 1, .reusable = false}}, SHIFT(99),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [121] = {.entry = {.count = 1, .reusable = false}}, SHIFT(150),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [125] = {.entry = {.count = 1, .reusable = false}}, SHIFT(100),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [129] = {.entry = {.count = 1, .reusable = false}}, SHIFT(101),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 1, 0, 0),
  [133] = {.entry = {.count = 1, .reusable = false}}, SHIFT(149),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [137] = {.entry = {.count = 1, .reusable = false}}, SHIFT(173),
  [139] = {.entry = {.count = 1, .reusable = false}}, SHIFT(172),
  [141] = {.entry = {.count = 1, .reusable = false}}, SHIFT(171),
  [143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [145] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [153] = {.entry = {.count = 1, .reusable = false}}, SHIFT(3),
  [155] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 2, 0, 0),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [163] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 3, 0, 0),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [169] = {.entry = {.count = 1, .reusable = false}}, SHIFT(144),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [173] = {.entry = {.count = 1, .reusable = false}}, SHIFT(143),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [177] = {.entry = {.count = 1, .reusable = false}}, SHIFT(141),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [181] = {.entry = {.count = 1, .reusable = false}}, SHIFT(154),
  [183] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [185] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [193] = {.entry = {.count = 1, .reusable = false}}, SHIFT(155),
  [195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [197] = {.entry = {.count = 1, .reusable = true}}, SHIFT(161),
  [199] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(161),
  [202] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_path_repeat1, 2, 0, 0), SHIFT_REPEAT(166),
  [205] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0),
  [207] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(174),
  [210] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0),
  [212] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(45),
  [215] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__query_body_repeat1, 2, 0, 0), SHIFT_REPEAT(171),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison, 2, 0, 5),
  [220] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison, 2, 0, 5),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison, 3, 0, 0),
  [224] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison, 3, 0, 0),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__source, 1, 0, 0),
  [230] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__source, 1, 0, 0),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [234] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_element_query, 3, 0, 0),
  [236] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_element_query, 3, 0, 0),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparator, 2, 0, 8),
  [240] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparator, 2, 0, 8),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_array_query, 3, 0, 0),
  [244] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_array_query, 3, 0, 0),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 1, 0, 0),
  [248] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_query, 1, 0, 0),
  [250] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparator, 1, 0, 4),
  [252] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparator, 1, 0, 4),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__source, 2, 0, 0),
  [256] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__source, 2, 0, 0),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_logical_op, 1, 0, 0),
  [260] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_logical_op, 1, 0, 0),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__source, 3, 0, 0),
  [264] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__source, 3, 0, 0),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition, 2, 0, 0),
  [268] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_condition, 2, 0, 0),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison, 3, 0, 1),
  [272] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison, 3, 0, 1),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment, 3, 0, 6),
  [276] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assignment, 3, 0, 6),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison, 4, 0, 5),
  [280] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison, 4, 0, 5),
  [282] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparison, 5, 0, 0),
  [284] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comparison, 5, 0, 0),
  [286] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_iterator, 4, 0, 2),
  [288] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_iterator, 4, 0, 2),
  [290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [294] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 4, 0, 0),
  [296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [306] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_limit, 2, 0, 0),
  [308] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [310] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [312] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [314] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [316] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 5, 0, 0),
  [318] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [320] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [324] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [326] = {.entry = {.count = 1, .reusable = false}}, SHIFT(88),
  [328] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [332] = {.entry = {.count = 1, .reusable = false}}, SHIFT(93),
  [334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [336] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__string_content, 2, 0, 0),
  [338] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__string_content, 2, 0, 0), SHIFT_REPEAT(117),
  [341] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [343] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [345] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [347] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_offset, 2, 0, 0),
  [349] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [351] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [353] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [355] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [357] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [359] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [361] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [363] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [365] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0),
  [367] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_array_repeat1, 2, 0, 0), SHIFT_REPEAT(51),
  [370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [372] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 0), SHIFT_REPEAT(125),
  [375] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_object_repeat1, 2, 0, 0),
  [377] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [379] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [381] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [383] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [385] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 6, 0, 0),
  [387] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pair, 3, 0, 3),
  [389] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_assignment, 4, 0, 7),
  [391] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [393] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [395] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [397] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [399] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [401] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [403] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [405] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [407] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [409] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [411] = {.entry = {.count = 1, .reusable = true}}, SHIFT(135),
  [413] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [415] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [417] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [419] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [421] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [423] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [425] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [427] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [429] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
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
