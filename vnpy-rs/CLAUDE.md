# CLAUDE.md - vnpy-rs Native Extension

## Build Commands
- Build (Release): `PYO3_USE_ABI3_FORWARD_COMPATIBILITY=1 cargo build --release`
- Build (Develop): `maturin develop` (Requires Python env)

## Test Commands
- Rust Unit Tests: `cargo test`

## Native Engine Details
- Library: `disruptor-rs` v4.x
- Bindings: `pyo3`
- Event Translation: Zero-copy via `Arc<PyObject>`
- Main Producer: `InnerProducer` enum wrapping multiple wait strategies
- **Non-Blocking**: Native `try_publish()` support for deadlock-free telemetry and recursive calls.

## Coding Standards
- Style: Use `cargo fmt`
- Safety: Ensure all `unsafe` blocks are documented with `SAFETY:` comments
- GIL Management: Prefer `py.allow_threads` for long-running blocking operations
