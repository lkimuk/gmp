# API Guide

This section explains how the generated API reference is integrated into the documentation site.

## Browse the Generated Reference

- [Open the generated API reference](reference/index.html)

## Local Generation

If Doxygen is installed, configure the project with `BUILD_DOCS=ON` and build the `docs` target:

```bash
cmake -B build -DBUILD_DOCS=ON
cmake --build build --target docs
```

The generated HTML is written to `docs/api/reference/`.

## Integration Files

- `cmake/Doxyfile.in`
- `docs/doxygen/mainpage.md`
- `CMakeLists.txt` option `BUILD_DOCS`
- `.github/workflows/docs.yml`

## Deployment Model

- Hand-written guides live in `docs/`
- Doxygen output is generated into `docs/api/reference/`
- GitHub Actions builds and deploys the whole site to GitHub Pages

## Related Guides

- [Documentation home](../index.md)
- [Getting Started](../getting-started.md)
- [Macro Metaprogramming](../macro-metaprogramming.md)
- [Reflection Metaprogramming](../reflection.md)
- [Named Operators](../named-operators.md)
- [Generic Design Patterns](../design-patterns.md)
