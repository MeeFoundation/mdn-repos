/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

const PREC = {
    expression: 1,
    value: 2,
    bool_expression: 3,
    or: 10,
    and: 11,
    not: 12,
    compare: 13,
    parenthesized_expression: 14,
    instruction: 100,
    assignment: 101,
    update_stmt: 102,
    // unknown_stmt: -1, // Remove or keep for potential future use
    pair: 103,
    key_word: 1000,
    ident: -1,
};

module.exports = grammar({
    name: 'mee_ql',

    extras: $ => [
        /\s/,
    ],

    rules: {
        start: $ => choice(
            $._query,
            $._missing_query, // For cases without a starting symbol
        ),

        _query: $ => choice(
            $.array_query,
            $.element_query,
        ),

        array_query: $ => seq(
            '[',
            field('body', $._query_body),
            choice(']', $.missing_array_query_end)
        ),

        element_query: $ => seq(
            '(',
            field('body', $._query_body),
            choice(')', $.missing_element_query_end)
        ),

        _missing_query: $ => seq(
            $.missing_query_start,
            field('body', $._query_body),
            optional(choice(']', ')', $.missing_array_query_end, $.missing_element_query_end))
        ),

        _query_body: $ => choice(
            $.missing_query_body,
            seq(
                optional(field('result', $._expression)),
                field('main_iterator', choice($.iterator_stmt, $.missing_main_iterator)),
                field('statements', repeat(choice(
                    $.iterator_stmt,
                    $.assignment,
                    $.update_stmt,
                    $.delete_stmt,
                    $.filter_stmt,
                    $.offset_stmt,
                    $.limit_stmt,
                    // Removed $.unknown_stmt
                ))),
            )
        ),

        iterator_stmt: $ => seq(
            $._for,
            choice(
                seq(
                    field('item', $.ident),
                    $._in,
                    field('source', choice(seq($.path, optional('()')), $.array))
                ),
                $.missing_iterator
            )
        ),

        assignment: $ => prec.left(PREC.assignment, seq(
            optional($._let),
            field('var', $.ident),
            '=', // Requires an explicit '='
            field('expr', choice($._bool_expression, $._expression, $._query, $.missing_expression))
        )),

        update_stmt: $ => prec.left(PREC.update_stmt, seq(
            $._set,
            choice(
                seq(
                    field('field', $.path),
                    choice('=', $.missing_equals),
                    field('expr', $._expected_expression)
                ),
                $.missing_update_field
            )
        )),

        delete_stmt: $ => seq(
            $._delete,
            choice(field('field', $.path), $.missing_delete_field)
        ),

        filter_stmt: $ => seq(
            $._if,
            choice(field('filter', $._bool_expression), $.missing_filter_expression)
        ),

        offset_stmt: $ => seq(
            $._offset,
            choice(field('offset', $.pos_int), $.missing_offset_value)
        ),

        limit_stmt: $ => seq(
            $._limit,
            choice(field('limit', $.pos_int), $.missing_limit_value)
        ),

        // Remove unknown_stmt and ERROR_unknown_element rules

        _bool_expression: $ => choice(
            $.comparison,
            $.not_expression,
            $.and_expression,
            $.or_expression,
            $._bool_value,
        ),

        comparison: $ => prec.right(PREC.compare, seq(
            field('val', $._expression),
            field('comparator', $.comparator)
        )),

        comparator: $ => prec.left(PREC.compare, choice(
            seq('==', field('right', $._expected_expression)),
            seq('!=', field('right', $._expected_expression)),
            seq('>', field('right', $._expected_expression)),
            seq('<', field('right', $._expected_expression)),
            seq('>=', field('right', $._expected_expression)),
            seq('<=', field('right', $._expected_expression)),
            seq('matches', field('right', $._expected_expression)),
            seq('after', field('right', $._expected_expression)),
            seq('before', field('right', $._expected_expression)),
            seq('between', field('from', $._expected_expression), 'and', field('to', $._expected_expression)),
            seq('contains', field('right', $._expected_expression)),
            'exists'
        )),


        not_expression: $ => prec.right(PREC.not, seq(
            $._not,
            $._bool_expression
        )),

        and_expression: $ => prec.left(PREC.and, seq(
            $._bool_expression,
            repeat1(seq($._and, $._bool_expression))
        )),

        or_expression: $ => prec.left(PREC.or, seq(
            $._bool_expression,
            repeat1(seq($._or, $._bool_expression))
        )),

        _bool_value: $ => choice(
            $.true,
            $.false,
            $.null,
            $._parenthesized_bool_expression,
            $.path,
            $.number,
            $.string,
            $.missing_bool_value
        ),

        _parenthesized_bool_expression: $ => seq(
            '(',
            $._bool_expression,
            choice(')', $.missing_parenthesis_end)
        ),

        _expression: $ => choice(
            $._parenthesized_expression,
            $.number,
            $.string,
            $.path,
            $.object,
            $.array,
            $.null,
            $.true,
            $.false,
            $._query,
        ),

        _parenthesized_expression: $ => seq(
            '(',
            $._expression,
            choice(')', $.missing_parenthesis_end)
        ),

        path: $ => seq(
            $.ident,
            repeat(seq('.', $.ident))
        ),

        pos_int: $ => /\d+/,

        object: $ => seq(
            '{',
            optional(seq($.pair, repeat(seq(',', $.pair)))),
            choice('}', $.missing_brace_end)
        ),

        pair: $ => prec.left(PREC.pair, seq(
            field('key', $.string),
            choice(':', $.missing_colon),
            field('value', $._expected_expression)
        )),

        array: $ => seq(
            '[',
            optional(seq($._expression, repeat(seq(',', $._expression)))),
            choice(']', $.missing_array_end)
        ),

        string: $ => choice(
            '""',
            seq('"', optional($._string_content), choice('"', $.missing_string_end)),
            $.missing_string_end
        ),

        _string_content: $ => repeat1(choice(
            $.string_content,
            $.escape_sequence,
        )),

        string_content: _ => token.immediate(prec(1, /[^\\"\n]+/)),

        escape_sequence: _ => token.immediate(seq(
            '\\',
            /("|\\|\/|b|f|n|r|t|u)/
        )),

        number: _ => {
            const decimalDigits = /\d+/;
            const signedInteger = seq(optional('-'), decimalDigits);
            const exponentPart = seq(choice('e', 'E'), signedInteger);

            const decimalIntegerLiteral = seq(
                optional('-'),
                choice(
                    '0',
                    seq(/[1-9]/, optional(decimalDigits)),
                ),
            );

            const decimalLiteral = choice(
                seq(decimalIntegerLiteral, '.', optional(decimalDigits), optional(exponentPart)),
                seq(decimalIntegerLiteral, optional(exponentPart)),
            );

            return token(decimalLiteral);
        },

        _expected_expression: $ => choice($._expression, $.missing_expression),

        // Missing elements and error handling nodes
        missing_query_start: $ => prec(-1, 'ERROR_missing_query_start'),
        missing_query_body: $ => prec(-1, 'ERROR_missing_query_body'),
        missing_main_iterator: $ => prec(-1, 'ERROR_missing_main_iterator'),
        missing_array_query_end: $ => prec(-1, 'ERROR_missing_array_query_end'),
        missing_element_query_end: $ => prec(-1, 'ERROR_missing_element_query_end'),
        missing_iterator: $ => prec(-1, 'ERROR_missing_iterator'),
        missing_update_field: $ => prec(-1, 'ERROR_missing_update_field'),
        missing_delete_field: $ => prec(-1, 'ERROR_missing_delete_field'),
        missing_filter_expression: $ => prec(-1, 'ERROR_missing_filter_expression'),
        missing_offset_value: $ => prec(-1, 'ERROR_missing_offset_value'),
        missing_limit_value: $ => prec(-1, 'ERROR_missing_limit_value'),
        missing_expression: $ => prec(-1, 'ERROR_missing_expression'),
        missing_comparator: $ => prec(-1, 'ERROR_missing_comparator'),
        missing_bool_value: $ => prec(-1, 'ERROR_missing_bool_value'),
        missing_equals: $ => prec(-1, 'ERROR_missing_equals'),
        missing_colon: $ => prec(-1, 'ERROR_missing_colon'),
        missing_value: $ => prec(-1, 'ERROR_missing_value'),
        missing_identifier: $ => prec(-1, 'ERROR_missing_value'),
        missing_brace_end: $ => prec(-1, 'ERROR_missing_brace_end'),
        missing_array_end: $ => prec(-1, 'ERROR_missing_array_end'),
        missing_parenthesis_end: $ => prec(-1, 'ERROR_missing_parenthesis_end'),
        missing_string_end: $ => prec(-1, 'ERROR_missing_string_end'),

        // Keywords and identifiers
        _for: $ => token(prec(PREC.key_word, 'for')),
        _let: $ => token(prec(PREC.key_word, 'let')),
        _in: $ => token(prec(PREC.key_word, 'in')),
        true: $ => token(prec(PREC.key_word, 'true')),
        false: $ => token(prec(PREC.key_word, 'false')),
        null: $ => token(prec(PREC.key_word, 'null')),
        _and: $ => token(prec(PREC.key_word, 'and')),
        _or: $ => token(prec(PREC.key_word, 'or')),
        _not: $ => token(prec(PREC.key_word, 'not')),
        _if: $ => token(prec(PREC.key_word, 'if')),
        _set: $ => token(prec(PREC.key_word, 'set')),
        _delete: $ => token(prec(PREC.key_word, 'delete')),
        _offset: $ => token(prec(PREC.key_word, 'offset')),
        _limit: $ => token(prec(PREC.key_word, 'limit')),

        ident: $ => choice(token(prec(PREC.ident, /[a-zA-Z_][a-zA-Z0-9_]*/)), $.missing_identifier),
    },

    conflicts: $ => [
        [$._bool_value, $._expression],
        [$.assignment, $._bool_expression],
    ],
});

module.exports.PREC = PREC;