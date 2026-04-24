import {themes as prismThemes} from 'prism-react-renderer';

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: 'GMP',
  tagline: 'Generative Metaprogramming library for C++',
  favicon: 'img/favicon.png',
  future: {
    v4: true,
  },
  url: 'https://lkimuk.github.io',
  baseUrl: '/gmp/',
  organizationName: 'lkimuk',
  projectName: 'gmp',
  onBrokenLinks: 'throw',
  markdown: {
    hooks: {
      onBrokenMarkdownLinks: 'throw',
    },
  },
  i18n: {
    defaultLocale: 'en',
    locales: ['en', 'zh-Hans'],
    localeConfigs: {
      en: {
        label: 'English',
        htmlLang: 'en',
      },
      'zh-Hans': {
        label: '简体中文',
        htmlLang: 'zh-CN',
      },
    },
  },
  presets: [
    [
      'classic',
      {
        docs: {
          id: 'default',
          path: './content/docs',
          routeBasePath: 'docs',
          sidebarPath: './sidebarsDocs.js',
          editUrl: 'https://github.com/lkimuk/gmp/tree/main/docs/',
        },
        blog: false,
        theme: {
          customCss: './src/css/custom.css',
        },
      },
    ],
  ],
  plugins: [
    [
      '@docusaurus/plugin-content-docs',
      {
        id: 'guides',
        path: './content/guides',
        routeBasePath: 'guides',
        sidebarPath: './sidebarsGuides.js',
        editUrl: 'https://github.com/lkimuk/gmp/tree/main/docs/',
      },
    ],
    [
      '@docusaurus/plugin-content-docs',
      {
        id: 'examples',
        path: './content/examples',
        routeBasePath: 'examples',
        sidebarPath: './sidebarsExamples.js',
        editUrl: 'https://github.com/lkimuk/gmp/tree/main/docs/',
      },
    ],
  ],
  themeConfig: {
    colorMode: {
      respectPrefersColorScheme: false,
    },
    navbar: {
      logo: {
        alt: 'GMP Logo',
        src: 'img/logo-primary.svg',
        srcDark: 'img/logo-primary-dark.svg',
        href: '/',
      },
      items: [
        {
          type: 'docSidebar',
          sidebarId: 'docsSidebar',
          docsPluginId: 'default',
          position: 'left',
          label: 'Docs',
        },
        {
          type: 'docSidebar',
          sidebarId: 'guidesSidebar',
          docsPluginId: 'guides',
          position: 'left',
          label: 'Guides',
        },
        {
          to: '/api/',
          label: 'API',
          position: 'left',
        },
        {
          type: 'docSidebar',
          sidebarId: 'examplesSidebar',
          docsPluginId: 'examples',
          label: 'Examples',
          position: 'left',
        },
        {
          type: 'localeDropdown',
          position: 'right',
        },
        {
          href: 'https://github.com/lkimuk/gmp',
          label: 'GitHub',
          position: 'right',
        },
      ],
    },
    footer: {
      links: [
        {
          title: 'Contribute',
          items: [
            {
              label: 'Issues',
              href: 'https://github.com/lkimuk/gmp/issues',
            },
            {
              label: 'Pull Requests',
              href: 'https://github.com/lkimuk/gmp/pulls',
            },
          ],
        },
        {
          title: 'Community',
          items: [
            {
              label: 'Releases',
              href: 'https://github.com/lkimuk/gmp/releases',
            },
            {
              label: 'Changelog',
              href: 'https://github.com/lkimuk/gmp/commits/main',
            },
            {
              label: 'CppMore',
              href: 'https://www.cppmore.com',
            },
          ],
        },
        {
          title: 'Contact',
          items: [
            {
              label: 'lkimuk@cppmore.com',
              href: 'mailto:lkimuk@cppmore.com',
            },
            {
              label: 'cppmore.com',
              href: 'https://www.cppmore.com',
            },
          ],
        },
      ],
      copyright: `Copyright © ${new Date().getFullYear()} Miles Li. Built with Docusaurus.`,
    },
    prism: {
      theme: prismThemes.oneLight,
      darkTheme: prismThemes.dracula,
    },
  },
};

export default config;
