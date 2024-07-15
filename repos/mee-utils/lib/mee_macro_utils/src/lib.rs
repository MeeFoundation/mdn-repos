pub mod error;

#[macro_export]
macro_rules! let_clone {
    ($clonnable: ident) => {
        let $clonnable = $clonnable.clone();
    };
}
