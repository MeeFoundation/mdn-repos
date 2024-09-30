/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
    name: 'mee_ql',

    extras: $ => [
        /\s|\\n|\\r|\\t/
    ],

    rules: {

        query: $ => choice(
            $.array_query,
            $.element_query
        ),

        array_query: $ => seq('[', $._query_body, ']'),
        element_query: $ => seq('(', $._query_body, ')'),

        _query_body: $ => seq(
            choice($.iterator, seq(optional($._value), $.iterator)),
            repeat(choice($.iterator, $.assignment, $.condition)),
            optional($.limit),
            optional($.offset),
            optional($.update_assignment)
        ),

        iterator: $ => seq(
            'for', field('item', $.ident), 'in', field('source', $._source)
        ),

        _expression: $ => choice($._value, $.query),

        assignment: $ => seq(
            field('var', $.ident), '=', field('expr', $._expression)
        ),

        update_assignment: $ => seq(
            'set', field('field', $.path), '=', field('expr', $._expression)
        ),

        _source: $ => seq(
            $.path, optional('()'),
            optional($.array)
        ),

        condition: $ => seq(
            'if', $.comparison
        ),

        comparison: $ => seq(
            choice(seq(field('left', $._value), field('right', optional($.comparator))), seq('(', $.comparison, ')')),
            optional(seq($.logical_op, $.comparison))
        ),

        path: $ => seq(
            $.ident,
            repeat(seq('.', $.ident))
        ),

        comparator: $ => choice(
            seq(field('op', '=='), field('expr', $._expression)),
            seq(field('op', '!='), field('expr', $._expression)),
            seq(field('op', '>'), field('expr', $._expression)),
            seq(field('op', '<'), field('expr', $._expression)),
            seq(field('op', '>='), field('expr', $._expression)),
            seq(field('op', '<='), field('expr', $._expression)),
            seq(field('op', 'matches'), field('expr', $._expression)),
            field('op', 'exists')
        ),

        logical_op: $ => choice('and', 'or'),

        limit: $ => seq('limit', $.pos_int),
        offset: $ => seq('offset', $.pos_int),

        pos_int: $ => /\d+/,

        _value: $ => choice(
            $.path,
            $.object,
            $.array,
            $.number,
            $.string,
            $.true,
            $.false,
            $.null,
        ),

        object: $ => seq(
            '{', seq($.pair, repeat(seq(',', $.pair))), '}',
        ),

        pair: $ => seq(
            field('key', $.string),
            ':',
            field('value', $._value),
        ),

        array: $ => seq(
            '[', seq($._value, repeat(seq(',', $._value))), ']',
        ),

        string: $ => choice(
            seq('"', '"'),
            seq('"', $._string_content, '"'),
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

        true: _ => 'true',

        false: _ => 'false',

        null: _ => 'null',

        ident: $ => /[a-zA-Z_][a-zA-Z0-9_]*/
    }
});