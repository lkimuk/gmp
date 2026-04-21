import clsx from 'clsx';
import Link from '@docusaurus/Link';
import Layout from '@theme/Layout';
import Heading from '@theme/Heading';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import styles from './index.module.css';

function homeContent(locale) {
  const zh = locale === 'zh-Hans';
  return {
    heroTitle: zh ? 'GMP 文档中心' : 'GMP Documentation',
    heroSubtitle: zh
      ? '面向编译时代码生成的 C++ 元编程库'
      : 'A C++ metaprogramming library tailored for compile-time code generation',
    primaryAction: zh ? '阅读文档' : 'Read the Docs',
    secondaryAction: zh ? '查看 API（英文）' : 'Browse API',
    languageNote: zh
      ? '手写指南提供英文与简体中文，API Reference 当前仅提供英文。'
      : 'Guides are available in English and Simplified Chinese. The API reference is currently English-only.',
    features: [
      {
        title: zh ? '宏元编程' : 'Macro Metaprogramming',
        text: zh
          ? '提供布尔逻辑、算术、tuple 操作、循环与宏重载分发等预处理器工具。'
          : 'Preprocessor utilities for boolean logic, arithmetic, tuple manipulation, loops, and overload dispatch.',
      },
      {
        title: zh ? '反射与命名操作符' : 'Reflection and Named Operators',
        text: zh
          ? '在 C++20 下提供固定字符串、类型与枚举反射，以及中缀 DSL 风格操作符。'
          : 'C++20 features for fixed strings, type and enum reflection, and expressive infix-style operators.',
      },
      {
        title: zh ? '通用设计模式' : 'Generic Design Patterns',
        text: zh
          ? '包含单例、spin lock 与对象工厂等轻量基础设施组件。'
          : 'Lightweight infrastructure helpers including singleton, spin lock, and object factory utilities.',
      },
    ],
  };
}

function rootBaseUrl(baseUrl, locale, defaultLocale) {
  return locale === defaultLocale ? baseUrl : baseUrl.replace(`${locale}/`, '');
}

function apiHref(url, baseUrl, locale, defaultLocale) {
  return `${url}${rootBaseUrl(baseUrl, locale, defaultLocale)}api/`;
}

function docsHref(baseUrl) {
  return `${baseUrl}docs/`;
}

export default function Home() {
  const {siteConfig, i18n} = useDocusaurusContext();
  const content = homeContent(i18n.currentLocale);

  return (
    <Layout title={content.heroTitle} description={siteConfig.tagline}>
      <header className={clsx('hero hero--primary', styles.heroBanner)}>
        <div className="container">
          <Heading as="h1" className="hero__title">
            {content.heroTitle}
          </Heading>
          <p className="hero__subtitle">{content.heroSubtitle}</p>
          <div className={styles.actions}>
            <Link className="button button--light button--lg" to={docsHref(siteConfig.baseUrl)}>
              {content.primaryAction}
            </Link>
            <Link
              className="button button--secondary button--lg"
              href={apiHref(siteConfig.url, siteConfig.baseUrl, i18n.currentLocale, i18n.defaultLocale)}>
              {content.secondaryAction}
            </Link>
          </div>
          <p className={styles.languageNote}>{content.languageNote}</p>
        </div>
      </header>
      <main className={styles.main}>
        <section className="container">
          <div className={styles.featureGrid}>
            {content.features.map((feature) => (
              <article key={feature.title} className={styles.featureCard}>
                <Heading as="h2">{feature.title}</Heading>
                <p>{feature.text}</p>
              </article>
            ))}
          </div>
        </section>
      </main>
    </Layout>
  );
}
