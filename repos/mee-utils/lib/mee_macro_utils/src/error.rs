#[macro_export]
macro_rules! from_external_error_to_string_error {
    ($from:path, $for:path, $to:ident) => {
        impl From<$from> for $for {
            fn from(value: $from) -> Self {
                Self::$to {
                    error: value.to_string(),
                }
            }
        }
    };
}
