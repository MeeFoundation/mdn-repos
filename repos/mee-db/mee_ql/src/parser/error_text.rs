const MISSING: &str = "Required element is missing";
const MISSING_QUERY_START: &str = "Expected '[' or '(' as start of query";
const MISSING_QUERY_BODY: &str = "Expected query body";
const MISSING_MAIN_ITERATOR: &str = "Expected main iterator";
const MISSING_ARRAY_QUERY_END: &str = "Expected ']' as end of array";
const MISSING_ELEMENT_QUERY_END: &str = "Expected ')' as end of element query";
const MISSING_ITERATOR: &str = "Expected iterator";
const MISSING_UPDATE_FIELD: &str = "Expected update field";
const MISSING_DELETE_FIELD: &str = "Expected delete field";
const MISSING_FILTER_EXPRESSION: &str = "Expected filter expression";
const MISSING_OFFSET_VALUE: &str = "Expected offset value";
const MISSING_LIMIT_VALUE: &str = "Expected limit value";
const MISSING_EXPRESSION: &str = "Expected expression";
const MISSING_COMPARATOR: &str = "Expected comparator";
const MISSING_BOOL_VALUE: &str = "Expected boolean value";
const MISSING_EQUALS: &str = "Expected '=='";
const MISSING_COLON: &str = "Expected ':'";
const MISSING_VALUE: &str = "Expected value";
const MISSING_BRACE_END: &str = "Expected '}' as end of brace";
const MISSING_ARRAY_END: &str = "Expected ']' as end of array";
const MISSING_PARENT_END: &str = "Expected ')' as end of parenthesis";
const MISSING_STRING_END: &str = "Expected string end";
const UNKNOWN_SYNTAX_ERROR: &str = "Syntax error";

pub fn error_text(error_kind: &str) -> &str {
    match error_kind {
        "missing_query_start" => MISSING_QUERY_START,
        "missing_query_body" => MISSING_QUERY_BODY,
        "missing_main_iterator" => MISSING_MAIN_ITERATOR,
        "missing_array_query_end" => MISSING_ARRAY_QUERY_END,
        "missing_element_query_end" => MISSING_ELEMENT_QUERY_END,
        "missing_iterator" => MISSING_ITERATOR,
        "missing_update_field" => MISSING_UPDATE_FIELD,
        "missing_delete_field" => MISSING_DELETE_FIELD,
        "missing_filter_expression" => MISSING_FILTER_EXPRESSION,
        "missing_offset_value" => MISSING_OFFSET_VALUE,
        "missing_limit_value" => MISSING_LIMIT_VALUE,
        "missing_expression" => MISSING_EXPRESSION,
        "missing_comparator" => MISSING_COMPARATOR,
        "missing_bool_value" => MISSING_BOOL_VALUE,
        "missing_equals" => MISSING_EQUALS,
        "missing_colon" => MISSING_COLON,
        "missing_value" => MISSING_VALUE,
        "missing_brace_end" => MISSING_BRACE_END,
        "missing_array_end" => MISSING_ARRAY_END,
        "missing_parenthesis_end" => MISSING_PARENT_END,
        "missing_string_end" => MISSING_STRING_END,
        "MISSING" => MISSING,
        _ => UNKNOWN_SYNTAX_ERROR,
    }
}
