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
          path: './content',
          sidebarPath: './sidebars.js',
          editUrl: 'https://github.com/lkimuk/gmp/tree/main/docs/',
        },
        blog: false,
        theme: {
          customCss: './src/css/custom.css',
        },
      },
    ],
  ],
  themeConfig: {
    colorMode: {
      respectPrefersColorScheme: true,
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
          sidebarId: 'guideSidebar',
          position: 'left',
          label: 'Docs',
        },
        {
          to: '/api/',
          label: 'API',
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
      style: 'dark',
      links: [
        {
          title: 'Docs',
          items: [
            {
              label: 'Documentation',
              to: '/docs/',
            },
            {
              label: 'API Reference',
              to: '/api/',
            },
          ],
        },
        {
          title: 'Community',
          items: [
            {
              label: 'GitHub',
              href: 'https://github.com/lkimuk/gmp',
            },
            {
              label: 'Issues',
              href: 'https://github.com/lkimuk/gmp/issues',
            },
          ],
        },
      ],
      copyright: `Copyright © ${new Date().getFullYear()} Miles Li. Built with Docusaurus.`,
    },
    prism: {
      theme: prismThemes.github,
      darkTheme: prismThemes.dracula,
    },
  },
};

export default config;
