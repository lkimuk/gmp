# API Reference

This section is intended to hold Doxygen-generated API documentation.

## Generate the Reference Locally

If Doxygen is installed, configure the project with `BUILD_DOCS=ON` and build the `docs` target:

```bash
cmake -B build -DBUILD_DOCS=ON
cmake --build build --target docs
```

The generated HTML will be written to `docs/api/reference/`.

## Files Added for the Integration

- `cmake/Doxyfile.in`
- `docs/doxygen/mainpage.md`
- `CMakeLists.txt` option `BUILD_DOCS`

## Recommended Workflow

- Use the hand-written guides for learning and examples
- Use generated API pages for symbol lookup and header navigation
- Regenerate `docs/api/reference/` whenever the public API changes

## GitHub Actions Deployment

This repository can also generate and deploy the API reference on GitHub without requiring a local Doxygen installation. The Pages workflow builds Doxygen output into `docs/api/reference/`, runs Jekyll for the hand-written guides, and publishes the final site artifact.

## Related Guides

- [Documentation home](../index.md)
- [Getting Started](../getting-started.md)
- [Macro Metaprogramming](../macro-metaprogramming.md)
- [Reflection Metaprogramming](../reflection.md)
- [Named Operators](../named-operators.md)
- [Generic Design Patterns](../design-patterns.md)
