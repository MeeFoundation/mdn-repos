use futures::TryStreamExt;
use std::collections::HashSet;

pub fn try_stream_dedup<E, T>(
    stream: impl TryStreamExt<Ok = T, Error = E>,
) -> impl TryStreamExt<Item = Result<T, E>>
where
    T: std::hash::Hash,
    T: Eq,
    T: Clone,
{
    let mut dedupa = HashSet::new();

    stream.try_filter_map(move |e| {
        let res = if !dedupa.contains(&e) {
            dedupa.insert(e.clone());

            Some(e)
        } else {
            None
        };

        async { Ok(res) }
    })
}

#[macro_export]
/// Assigns an expression in sync block to a variable and then move the variable into async block
macro_rules! async_move {
    ($exp:expr) => {{
        let e = $exp;
        async move { e }
    }};
}
