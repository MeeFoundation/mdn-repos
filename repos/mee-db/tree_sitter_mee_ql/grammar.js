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
    key_word: 1000,
};

module.exports = grammar({
    name: 'mee_ql',

    extras: $ => [
        /\s/
    ],


    rules: {

        start: $ => $._query,

        _query: $ => prec.left(PREC.instruction, choice(
            $.array_query,
            $.element_query
        )),

        array_query: $ => prec.left(PREC.instruction, seq('[', field('body', $._query_body), ']')),
        element_query: $ => prec.left(PREC.instruction, seq('(', field('body', $._query_body), ')')),

        _query_body: $ => prec.left(PREC.instruction, seq(
            optional(field('result', $._value)),
            field('iterators', repeat1($.iterator_stmt)),
            field('updates', repeat($.update_stmt)),
            field('deletes', repeat($.delete_stmt)),
        )),

        iterator_stmt: $ => prec.left(PREC.instruction, seq(
            $._for, field('item', $.ident), $._in, field('source', choice(seq($.path, optional('()')), $.array)),
            field('assignments', repeat($.assignment)),
            optional(seq($._if, field('filter', $._bool_expression))),
            optional(seq($._offset, field('offset', $.pos_int))),
            optional(seq($._limit, field('limit', $.pos_int))),
        )),

        assignment: $ => prec.right(PREC.instruction, seq(
            field('var', $.ident), '=', field('expr', $._expression)
        )),

        update_stmt: $ => prec.right(PREC.instruction, seq(
            $._set, field('field', $.path), '=', field('expr', $._expression)
        )),

        delete_stmt: $ => prec.left(PREC.instruction, seq(
            $._delete, optional(field('field', $.path))
        )),

        _expression: $ => prec.left(PREC.expression, choice($._value, $._query, $._bool_expression)),

        path: $ => seq(
            $.ident,
            repeat(seq('.', $.ident))
        ),

        _parenthesized_bool_expression: $ => prec.left(PREC.parenthesized_expression, seq(
            '(',
            $._bool_expression,
            ')'
        )),

        not_expression: $ => prec.right(PREC.not, seq(
            $._not,
            choice($._bool_value, $._parenthesized_bool_expression)
        )),

        and_expression: $ => prec.left(PREC.and, seq(
            choice($._bool_value),
            repeat1(seq($._and, $._bool_value))
        )),

        or_expression: $ => prec.left(PREC.or, seq(
            choice($._bool_value, $.and_expression),
            repeat1(seq('or', choice($._bool_value, $.and_expression)))
        )),

        _bool_value: $ => choice($.true, $.false, $.path, $._parenthesized_bool_expression, $.not_expression, $.comparison),
        _bool_expression: $ => prec.left(PREC.bool_expression, choice($.and_expression, $.or_expression, $._bool_value)),

        comparison: $ => prec.right(PREC.compare, seq(
            field('val', $._value),
            field('comparator', $.comparator)
        )),

        comparator: $ => prec.left(PREC.compare, choice(
            seq('==', field('right', $._expression)),
            seq('!=', field('right', $._expression)),
            seq('>', field('right', $._expression)),
            seq('<', field('right', $._expression)),
            seq('>=', field('right', $._expression)),
            seq('<=', field('right', $._expression)),
            seq('matches', field('right', $._expression)),
            'exists'
        )),

        pos_int: $ => /\d+/,

        _value: $ => prec.left(PREC.value, choice(
            $.path,
            $.object,
            $.array,
            $.number,
            $.string,
            $.null,
            $.true,
            $.false,
        )),

        object: $ => seq(
            '{', $.pair, repeat(seq(',', $.pair)), '}'
        ),

        pair: $ => seq(
            field('key', $.string),
            ':',
            field('value', $._value),
        ),

        array: $ => seq(
            '[', $._value, repeat(seq(',', $._value)), ']'
        ),

        string: $ => choice(
            '""',
            seq('"', $._string_content, '"')
        ),

        _string_content: $ => repeat1(choice(
            $.string_content,
            $.escape_sequence,
        )),

        string_content: _ => token.immediate(prec(1, /[^\\"\n]+/)),

        escape_sequence: _ => token.immediate(seq(
            '\\',
            /(\"|\\|\/|b|f|n|r|t|u)/,
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

        _for: _ => prec.left(PREC.key_word, 'for'),

        _in: _ => prec.left(PREC.key_word, 'in'),

        true: _ => prec.left(PREC.key_word, 'true'),

        false: _ => prec.left(PREC.key_word, 'false'),

        null: _ => prec.left(PREC.key_word, 'null'),

        _and: _ => prec.left(PREC.key_word, 'and'),

        _or: _ => prec.left(PREC.key_word, 'or'),

        _not: _ => prec.left(PREC.key_word, 'not'),

        _if: _ => prec.left(PREC.key_word, 'if'),

        _set: _ => prec.left(PREC.key_word, 'set'),

        _delete: _ => prec.left(PREC.key_word, 'delete'),

        ident: $ => /[a-zA-Z_][a-zA-Z0-9_]*/,

        _offset: _ => prec.left(PREC.key_word, 'offset'),

        _limit: _ => prec.left(PREC.key_word, 'limit'),
    }
});

module.exports.PREC = PREC;