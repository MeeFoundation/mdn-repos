#[macro_export]
macro_rules! cargo_target_level_filename {
    ($filename:expr) => {{
        let cargo_manifest_dir = env!("CARGO_MANIFEST_DIR");
        let local_target = format!("{}/target", cargo_manifest_dir);

        let cargo_target = if std::fs::exists(&local_target).unwrap() {
            local_target
        } else {
            format!("{}/../target", cargo_manifest_dir)
        };

        let filepath = format!("{cargo_target}/{}", $filename);

        filepath
    }};
}
