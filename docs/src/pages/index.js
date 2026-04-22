import clsx from 'clsx';
import Link from '@docusaurus/Link';
import Layout from '@theme/Layout';
import CodeBlock from '@theme/CodeBlock';
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
    snippetGroups: [
      {
        items: [
          {
            label: zh ? '宏元编程' : 'Macro Metaprogramming',
            code:
              '#define FIELD(type, name) type name;\n'
              + '#define PERSON_FIELDS(X) \\\n'
              + '  X(int, id)            \\\n'
              + '  X(int, age)           \\\n'
              + '  X(double, score)\n\n'
              + 'struct person {\n'
              + '  GMP_FOR_EACH(FIELD, PERSON_FIELDS)\n'
              + '};',
          },
          {
            label: zh ? '反射元编程' : 'Reflection Metaprogramming',
            code:
              'struct person { std::string name; int age; };\n'
              + 'enum class color { red, green, blue };\n\n'
              + 'constexpr auto names = gmp::member_names<person>();\n'
              + 'constexpr auto types = gmp::member_type_names<person>();\n'
              + 'constexpr auto value = gmp::enum_cast<color>("green");',
          },
        ],
      },
      {
        items: [
          {
            label: zh ? '命名操作符' : 'Named Operators',
            code:
              'auto _ = gmp::make_named_operator([](int x, int y) {\n'
              + '  return x + y;\n'
              + '});\n'
              + 'auto o = gmp::make_named_operator([](int x, int y) {\n'
              + '  return x * y;\n'
              + '});\n\n'
              + 'auto sum = 40 ^_^ 2;\n'
              + 'auto product = 6 ^o^ 7;',
          },
          {
            label: zh ? '通用设计模式' : 'Generic Design Patterns',
            code:
              'struct logger : gmp::singleton<logger> {\n'
              + '  GMP_DISABLE_CONSTRUCTION(logger)\n'
              + '};\n'
              + 'GMP_FACTORY_REGISTER(shape, (), circle, square)\n\n'
              + 'auto& log = logger::instance();\n'
              + 'auto p = gmp::object_factory<shape>::instance()\n'
              + '  .create_unique("circle");',
          },
        ],
      },
    ],
    features: [
      {
        title: zh ? '宏元编程' : 'Macro Metaprogramming',
        text: zh
          ? '提供布尔逻辑、算术、tuple 操作、循环与宏重载分发等预处理器工具。'
          : 'Preprocessor utilities for boolean logic, arithmetic, tuple manipulation, loops, and overload dispatch.',
      },
      {
        title: zh ? '反射元编程' : 'Reflection Metaprogramming',
        text: zh
          ? '在 C++20 下提供固定字符串、类型与枚举反射等编译期反射能力。'
          : 'C++20 features for fixed strings plus type and enum reflection at compile time.',
      },
      {
        title: zh ? '命名操作符' : 'Named Operators',
        text: zh
          ? '提供更具表达力的中缀 DSL 风格命名操作符，提升模板与元编程代码可读性。'
          : 'Expressive infix-style named operators for clearer template and metaprogramming code.',
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
        <div className={clsx('container', styles.heroContent)}>
          <Heading as="h1" className={clsx('hero__title', styles.heroTitle)}>
            {content.heroTitle}
          </Heading>
          <p className={clsx('hero__subtitle', styles.heroSubtitle)}>{content.heroSubtitle}</p>
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
          <section className={styles.snippetSection}>
            <div className={styles.snippetGrid}>
              {content.snippetGroups.map((group, index) => (
                <article key={index} className={styles.snippetGroup}>
                  {group.items.map((snippet) => (
                    <div key={snippet.label} className={styles.snippetEntry}>
                      <span className={styles.snippetLabel}>{snippet.label}</span>
                      <CodeBlock language="cpp" className={styles.snippetCodeBlock}>
                        {snippet.code}
                      </CodeBlock>
                    </div>
                  ))}
                </article>
              ))}
            </div>
          </section>
        </section>
      </main>
    </Layout>
  );
}
