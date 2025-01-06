#[macro_export]
/// Assigns an expression in sync block to a variable and then move the variable into async block
macro_rules! async_move {
    ($exp:expr) => {{
        let e = $exp;
        async move { e }
    }};
}
