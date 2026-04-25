# Documentation Workspace

This directory contains the complete documentation application for GMP.

The repository root remains focused on the C++ library itself. All documentation-site code, content, static assets, translations, and API-generation entry files live under `docs/`.

## Directory Layout

```text
docs/
├── content/        # English hand-written docs and examples
├── i18n/           # Localized documentation translations
├── src/            # Docusaurus pages and styling
├── static/         # Static assets and generated API output
├── doxygen/        # Doxygen main page sources
├── docusaurus.config.js
├── package.json
├── package-lock.json
└── sidebars.js
```

## Responsibilities

- `content/`: English source-of-truth documentation
- `i18n/zh-Hans/`: Simplified Chinese localized documentation
- `static/api/reference/`: Generated Doxygen HTML output
- `src/pages/api/`: Stable `/api/` redirect page inside the Docusaurus site
- `doxygen/mainpage.md`: Landing page for the generated API reference

## Local Development

Install dependencies:

```bash
cd docs
npm ci
```

Run the local preview server:

```bash
cd docs
npm start
```

This builds the full multilingual site and serves it locally, so the language switcher works the same way it does in production.

Run the fast development server:

```bash
cd docs
npm run dev
```

The Docusaurus development server serves one locale at a time. Use this when you want to edit the Simplified Chinese locale directly:

```bash
cd docs
npm run dev:zh
```

Create a production build:

```bash
cd docs
npm run build
```

Serve the production build locally:

```bash
cd docs
npm run serve
```

Preview all locales and test the language switcher locally:

```bash
cd docs
npm run preview
```

Use `npm start` or `npm run preview` when validating the language dropdown. `npm run dev` is faster for editing, but it does not serve every locale at once.

## API Generation

If Doxygen is available locally:

```bash
cmake -S . -B docs/build-docs -DBUILD_DOCS=ON
cmake --build docs/build-docs --target docs
```

This writes the generated API site into:

```text
docs/static/api/reference/
```

GitHub Actions also performs this generation automatically for Pages deployment.

## Language Policy

- English is the source of truth
- Hand-written docs may be translated
- API reference remains English-only until there is a clear need to translate code-level documentation

## Adding a New Language

1. Add the locale to `docs/docusaurus.config.js`
2. Create `docs/i18n/<locale>/docusaurus-plugin-content-docs/current/`
3. Translate the high-value docs set first:
   - `index.md`
   - `installation.md`
   - `getting-started.md`
   - core module docs
4. Keep API links pointing to the English `/gmp/api/`

## Design Principle

The documentation system is intentionally isolated inside `docs/` so it does not turn the repository root into a generic website project. The root stays library-centric; `docs/` is the documentation workspace.
