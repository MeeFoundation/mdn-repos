use nom::{
    bytes::complete::{is_not, tag},
    character::complete::{char, digit1, space0},
    combinator::{map, opt},
    multi::{many0, separated_list0},
    sequence::{delimited, preceded, terminated, tuple},
    IResult,
};

#[derive(Debug)]
pub enum JsonValue {
    Number(i64),
    String(String),
    Object(Vec<(String, JsonValue)>),
    Array(Vec<JsonValue>),
    Boolean(bool),
    Null,
}

fn parse_number(input: &str) -> IResult<&str, JsonValue> {
    let (input, num_str) = digit1(input)?;
    let number = num_str.parse::<i64>().unwrap();
    Ok((input, JsonValue::Number(number)))
}

fn parse_string(input: &str) -> IResult<&str, JsonValue> {
    let (input, string) = delimited(char('"'), is_not("\""), char('"'))(input)?;
    Ok((input, JsonValue::String(string.to_string())))
}

fn parse_value(input: &str) -> IResult<&str, JsonValue> {
    let (input, value) = alt((
        parse_string,
        parse_number,
        parse_object,
        parse_array,
        parse_boolean,
        parse_null,
    ))(input)?;
    Ok((input, value))
}

fn parse_object(input: &str) -> IResult<&str, JsonValue> {
    let (input, pairs) = delimited(
        char('{'),
        separated_list0(terminated(char(','), space0), parse_pair),
        char('}'),
    )(input)?;
    Ok((input, JsonValue::Object(pairs)))
}

fn parse_pair(input: &str) -> IResult<&str, (String, JsonValue)> {
    let (input, (key, _, value)) =
        tuple((parse_string, preceded(space0, char(':')), parse_value))(input)?;
    if let JsonValue::String(key_str) = key {
        Ok((input, (key_str, value)))
    } else {
        unreachable!()
    }
}

fn parse_array(input: &str) -> IResult<&str, JsonValue> {
    let (input, values) = delimited(
        char('['),
        separated_list0(terminated(char(','), space0), parse_value),
        char(']'),
    )(input)?;
    Ok((input, JsonValue::Array(values)))
}

fn parse_boolean(input: &str) -> IResult<&str, JsonValue> {
    let (input, _) = tag("true")(input)
        .map(|(i, _)| (i, JsonValue::Boolean(true)))
        .or_else(|_| {
            let (i, _) = tag("false")(input)?;
            Ok((i, JsonValue::Boolean(false)))
        })?;
    Ok((input, JsonValue::Boolean(false)))
}

fn parse_null(input: &str) -> IResult<&str, JsonValue> {
    let (input, _) = tag("null")(input)?;
    Ok((input, JsonValue::Null))
}

fn main() {
    let json_input = r#"{"key": "value", "array": [1, 2, 3], "bool": true, "null": null}"#;
    match parse_object(json_input) {
        Ok((remaining, parsed)) => {
            println!("Parsed JSON: {:?}", parsed);
            println!("Remaining: {}", remaining);
        }
        Err(err) => {
            println!("Error parsing JSON: {:?}", err);
        }
    }
}
