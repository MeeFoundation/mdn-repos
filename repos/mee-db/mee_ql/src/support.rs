pub fn unescape(s: &str) -> String {
    match s {
        r#"\\"# => r#"\"#.to_string(),
        r#"\""# => r#"""#.to_string(),
        r#"\/""# => r#"/"#.to_string(),
        r#"\b"# => "\u{0008}".to_string(),
        r#"\f"# => "\u{000C}".to_string(),
        r#"\n"# => "\n".to_string(),
        r#"\r"# => "\r".to_string(),
        r#"\t"# => "\t".to_string(),
        str if str.starts_with(r#"\u"#) => {
            let hex_digits = str.get(2..6).unwrap();
            let unicode_value = u32::from_str_radix(&hex_digits, 16).unwrap();
            char::from_u32(unicode_value).unwrap().to_string()
        }
        _ => String::new(),
    }
}
