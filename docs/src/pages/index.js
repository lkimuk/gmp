import clsx from 'clsx';
import {useState} from 'react';
import {FontAwesomeIcon} from '@fortawesome/react-fontawesome';
import {
  faCube,
  faCubes,
  faCode,
  faArrowRight,
  faArrowUpRightFromSquare,
  faMagnifyingGlass,
  faShapes,
  faBoxesStacked,
  faCodeBranch,
  faPlus,
  faCopy,
  faWandMagicSparkles,
  faShieldHalved,
  faBookOpen,
  faTrophy,
  faCheck,
} from '@fortawesome/free-solid-svg-icons';
import Link from '@docusaurus/Link';
import Layout from '@theme/Layout';
import CodeBlock from '@theme/CodeBlock';
import Heading from '@theme/Heading';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import {Highlight, themes} from 'prism-react-renderer';
import styles from './index.module.css';

function homeContent(locale) {
  const zh = locale === 'zh-Hans';

  return {
    heroEyebrow: zh ? 'Generative Metaprogramming' : 'Generative Metaprogramming',
    heroTitle: zh ? 'GMP 文档中心' : 'GMP Documentation',
    heroSubtitle: zh
      ? '面向编译时代码生成的 C++ 元编程库，帮助你用更清晰的方式组织宏、反射、命名操作符与通用基础设施。'
      : 'A modern C++ metaprogramming library for compile-time code generation.',
    heroBadges: [
      {icon: 'cube', label: zh ? 'Header-only' : 'Header-only'},
      {icon: 'cplusplus', label: zh ? 'C++20' : 'C++20'},
      {icon: 'sparkles', label: zh ? 'Reflection' : 'Reflection'},
      {icon: 'shield', label: zh ? 'MIT' : 'MIT'},
    ],
    primaryAction: zh ? '阅读文档' : 'Read the Docs',
    secondaryAction: zh ? '查看 API' : 'Browse API',
    capabilitiesTitle: zh ? '核心能力' : 'Core Capabilities',
    capabilitiesSubtitle: zh
      ? '围绕表达力与编译期生成效率构建的元编程基础模块。'
      : 'Building blocks for expressive compile-time metaprogramming.',
    features: [
      {
        accent: 'blue',
        icon: 'hex',
        title: zh ? '宏元编程' : 'Macro Metaprogramming',
        text: zh
          ? '提供布尔逻辑、算术、tuple 操作、循环与宏重载分发等预处理器工具。'
          : 'Preprocessor utilities for boolean logic, arithmetic, tuple manipulation, loops, and overload dispatch.',
      },
      {
        accent: 'mint',
        icon: 'search',
        title: zh ? '反射元编程' : 'Reflection Metaprogramming',
        text: zh
          ? '在 C++20 下提供固定字符串、类型与枚举反射等编译期反射能力。'
          : 'C++20 features for fixed strings plus type and enum reflection at compile time.',
      },
      {
        accent: 'violet',
        icon: 'slash',
        title: zh ? '命名操作符' : 'Named Operators',
        text: zh
          ? '提供更具表达力的中缀 DSL 风格命名操作符，提升模板与元编程代码可读性。'
          : 'Expressive infix-style named operators for clearer template and metaprogramming code.',
      },
      {
        accent: 'amber',
        icon: 'spark',
        title: zh ? '通用设计模式' : 'Generic Design Patterns',
        text: zh
          ? '包含单例、spin lock 与对象工厂等轻量基础设施组件。'
          : 'Lightweight infrastructure helpers including singleton, spin lock, and object factory utilities.',
      },
    ],
    examplesTitle: zh ? '实践代码' : 'Code in Practice',
    examplesSubtitle: zh
      ? '用几个真实片段快速感受 GMP 在项目里的使用方式。'
      : 'Explore GMP features with real-world examples.',
    copyAction: zh ? '复制' : 'Copy',
    copiedAction: zh ? '已复制' : 'Copied',
    examples: [
      {
        id: 'macro',
        icon: '</>',
        label: zh ? '宏' : 'Macro',
        code:
          '#define PRINT(x) std::cout << x << " ";\n'
          + 'GMP_FOR_EACH(PRINT, 1, 2, 3)                    // Expands to: std::cout << 1 << " "; std::cout << 2 << " "; std::cout << 3 << " ";\n\n'
          + '#define Bar(arg1, arg2) bar(arg1, arg2);\n'
          + 'GMP_REPEAT(Bar, 3, 1, "arg2")                   // Expands to: bar(1, "arg2"); bar(2, "arg2"); bar(3, "arg2");\n\n'
          + 'GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, X, Y, Z) // expands to: "OVERLOAD_FUNCTION_X_Y_Z"\n\n'
          + 'GMP_MAKE_INDEX_SEQUENCE(5)                      // expands to: 0, 1, 2, 3, 4\n'
          + 'GMP_RANGE(5, 10)                                // expands to: 5, 6, 7, 8, 9\n\n'
          + 'GMP_GENERATE_NAMESPACES_BEGIN(mylib, parser)    // expands to: namespace mylib { namespace parser {\n'
          + 'GMP_GENERATE_NAMESPACES_END(mylib, parser)      // expands to: } }',
      },
      {
        id: 'reflection',
        icon: 'Q',
        label: zh ? '反射' : 'Reflection',
        code:
          'struct person {\n'
          + '  std::string name;\n'
          + '  int age;\n'
          + '};\n'
          + 'enum class color { red, green, blue };\n\n'
          + 'constexpr auto names = gmp::member_names<person>();\n'
          + 'constexpr auto value = gmp::enum_cast<color>("green");',
      },
      {
        id: 'operators',
        icon: '+',
        label: zh ? '操作符' : 'Operators',
        code:
          'auto _ = gmp::make_named_operator([](int x, int y) { return x + y; });\n'
          + 'auto o = gmp::make_named_operator([](int x, int y) { return x * y; });\n\n'
          + 'assert((10 ^_^ 3) == 13);\n'
          + 'assert((10 <_> 3) == 13);\n'
          + 'assert((10 +_+ 3) == 13);\n'
          + 'assert((10 *_* 3) == 13);\n'
          + 'assert((10 -_- 3) == 13);\n'
          + 'assert((10 |_| 3) == 13);\n'
          + 'assert((10 *_^ 3) == 13);\n'
          + 'assert((10 ^o^ 3) == 30);',
      },
      {
        id: 'patterns',
        icon: '*',
        label: zh ? '模式' : 'Patterns',
        code:
          'struct logger : gmp::singleton<logger> {\n'
          + '  GMP_DISABLE_CONSTRUCTION(logger)\n'
          + '};\n'
          + 'auto& log = logger::instance();\n\n'
          + 'GMP_FACTORY_REGISTER(shape, (), circle, square)\n'
          + 'gmp::object_factory<shape> factory;\n'
          + 'auto p = factory.create_unique("circle");',
      },
    ],
    ctaTitle: zh ? '为什么选择 GMP？' : 'Why GMP?',
    ctaText: zh
      ? 'Header-only、零运行时开销，并且为现代 C++ 项目里的编译期表达力而设计。'
      : 'Header-only, zero-runtime overhead, and designed for modern C++.',
    ctaPrimary: zh ? '快速开始' : 'Get Started',
    ctaSecondary: zh ? '在 GitHub 查看' : 'View on GitHub',
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

function IconMark({type}) {
  const iconByType = {
    hex: faCubes,
    search: faMagnifyingGlass,
    slash: faCode,
    spark: faShapes,
  };

  return <FontAwesomeIcon icon={iconByType[type]} className={styles.featureGlyph} aria-hidden="true" />;
}

function ExampleGlyph({type}) {
  const iconByType = {
    macro: faBoxesStacked,
    reflection: faMagnifyingGlass,
    operators: faPlus,
    patterns: faCodeBranch,
  };

  return <FontAwesomeIcon icon={iconByType[type]} className={styles.exampleTabIcon} aria-hidden="true" />;
}

function BadgeGlyph({type}) {
  const iconByType = {
    cube: faCube,
    cplusplus: faCode,
    sparkles: faWandMagicSparkles,
    shield: faShieldHalved,
  };

  return <FontAwesomeIcon icon={iconByType[type]} className={styles.badgeIcon} aria-hidden="true" />;
}

const heroSnippet =
  'struct Person {\n'
  + '  std::string name;\n'
  + '  int age;\n'
  + '};\n\n'
  + 'static_assert(gmp::type_name<Person>() == "Person");\n'
  + 'static_assert(gmp::member_count<Person>() == 2);\n'
  + 'static_assert(gmp::member_name<0, Person>() == "name");\n'
  + 'static_assert(gmp::member_name<1, Person>() == "age");';

function HeroCodeSnippet() {
  return (
    <Highlight theme={themes.dracula} code={heroSnippet} language="cpp">
      {({className, style, tokens, getLineProps, getTokenProps}) => (
        <pre className={clsx(className, styles.heroCodePre)} style={style}>
          <code className={styles.heroCodeInner}>
            {tokens.map((line, index) => {
              const lineProps = getLineProps({line});

              return (
                <div key={index} {...lineProps} className={styles.heroCodeLine}>
                  {line.map((token, tokenIndex) => (
                    <span key={tokenIndex} {...getTokenProps({token})} />
                  ))}
                </div>
              );
            })}
          </code>
        </pre>
      )}
    </Highlight>
  );
}

export default function Home() {
  const {siteConfig, i18n} = useDocusaurusContext();
  const content = homeContent(i18n.currentLocale);
  const [activeExample, setActiveExample] = useState(content.examples[0].id);
  const [copiedExample, setCopiedExample] = useState('');
  const [heroCopied, setHeroCopied] = useState(false);
  const currentExample = content.examples.find((example) => example.id === activeExample) ?? content.examples[0];

  async function handleCopy() {
    if (typeof navigator === 'undefined' || !navigator.clipboard) {
      return;
    }

    await navigator.clipboard.writeText(currentExample.code);
    setCopiedExample(currentExample.id);
    window.setTimeout(() => {
      setCopiedExample((value) => (value === currentExample.id ? '' : value));
    }, 1400);
  }

  async function handleHeroCopy() {
    if (typeof navigator === 'undefined' || !navigator.clipboard) {
      return;
    }

    await navigator.clipboard.writeText(heroSnippet);
    setHeroCopied(true);
    window.setTimeout(() => {
      setHeroCopied(false);
    }, 1400);
  }

  return (
    <Layout title={content.heroTitle} description={siteConfig.tagline}>
      <main className={styles.page}>
        <section className={styles.heroShell}>
          <div className={clsx('container', styles.heroGrid)}>
            <div className={styles.heroCopy}>
              <span className={styles.heroEyebrow}>{content.heroEyebrow}</span>
              <Heading as="h1" className={styles.heroTitle}>
                {content.heroTitle}
              </Heading>
              <p className={styles.heroSubtitle}>{content.heroSubtitle}</p>
              <div className={styles.heroBadges}>
                {content.heroBadges.map((badge) => (
                  <span key={badge.label} className={styles.badgeChip}>
                    <BadgeGlyph type={badge.icon} />
                    {badge.label}
                  </span>
                ))}
              </div>
              <div className={styles.actions}>
                <Link className={clsx('button button--primary', styles.primaryAction)} to={docsHref(siteConfig.baseUrl)}>
                  <FontAwesomeIcon icon={faBookOpen} className={styles.actionIcon} aria-hidden="true" />
                  {content.primaryAction}
                </Link>
                <Link
                  className={clsx('button button--secondary', styles.secondaryAction)}
                  href={apiHref(siteConfig.url, siteConfig.baseUrl, i18n.currentLocale, i18n.defaultLocale)}>
                  <FontAwesomeIcon icon={faCodeBranch} className={styles.actionIcon} aria-hidden="true" />
                  {content.secondaryAction}
                </Link>
              </div>
            </div>
            <div className={styles.codeWindow}>
              <div className={styles.codeWindowBar}>
                <div className={styles.windowDots}>
                  <span />
                  <span />
                  <span />
                </div>
                <div className={styles.codeWindowMeta}>
                  <span className={styles.codeWindowFile}>example.cpp</span>
                  <button
                    type="button"
                    className={styles.heroCopyButton}
                    onClick={() => void handleHeroCopy()}
                    aria-label={heroCopied ? 'Copied code' : 'Copy code'}>
                    <FontAwesomeIcon icon={heroCopied ? faCheck : faCopy} />
                  </button>
                </div>
              </div>
              <div className={styles.heroCode}>
                <HeroCodeSnippet />
              </div>
            </div>
          </div>
        </section>

        <section className={clsx('container', styles.sectionBlock)}>
          <div className={styles.sectionHeading}>
            <Heading as="h2">{content.capabilitiesTitle}</Heading>
            <p>{content.capabilitiesSubtitle}</p>
          </div>
          <div className={styles.featureGrid}>
            {content.features.map((feature) => (
              <article key={feature.title} className={styles.featureCard}>
                <div className={styles.featureHead}>
                  <div className={clsx(styles.featureIcon, styles[`featureIcon${feature.accent}`])}>
                    <IconMark type={feature.icon} />
                  </div>
                  <Heading as="h3">{feature.title}</Heading>
                </div>
                <p>{feature.text}</p>
                <FontAwesomeIcon icon={faArrowRight} className={styles.featureArrow} aria-hidden="true" />
              </article>
            ))}
          </div>
        </section>

        <section className={clsx('container', styles.sectionBlock)}>
          <div className={styles.sectionHeading}>
            <Heading as="h2">{content.examplesTitle}</Heading>
            <p>{content.examplesSubtitle}</p>
          </div>
          <div className={styles.examplePanel}>
            <div className={styles.exampleMenu} role="tablist" aria-label={content.examplesTitle}>
              {content.examples.map((example) => {
                const isActive = example.id === currentExample.id;
                return (
                  <button
                    key={example.id}
                    type="button"
                    role="tab"
                    aria-selected={isActive}
                    className={clsx(styles.exampleTab, isActive && styles.exampleTabActive)}
                    onClick={() => setActiveExample(example.id)}>
                    <ExampleGlyph type={example.id} />
                    <span>{example.label}</span>
                  </button>
                );
              })}
            </div>
            <div className={styles.exampleCodePanel}>
              <div className={styles.exampleCodeHeader}>
                <button type="button" className={styles.copyButton} onClick={() => void handleCopy()}>
                  <FontAwesomeIcon icon={faCopy} className={styles.copyButtonIcon} aria-hidden="true" />
                  {copiedExample === currentExample.id ? content.copiedAction : content.copyAction}
                </button>
              </div>
              <CodeBlock language="cpp" className={styles.exampleCode} showLineNumbers>
                {currentExample.code}
              </CodeBlock>
            </div>
          </div>
        </section>

        <section className={clsx('container', styles.sectionBlock)}>
          <div className={styles.ctaBand}>
            <div className={styles.ctaCopy}>
              <div className={styles.ctaIcon} aria-hidden="true">
                <FontAwesomeIcon icon={faTrophy} />
              </div>
              <div>
                <Heading as="h2">{content.ctaTitle}</Heading>
                <p>{content.ctaText}</p>
              </div>
            </div>
            <div className={styles.ctaActions}>
              <Link className={clsx('button button--primary', styles.ctaPrimary)} to={docsHref(siteConfig.baseUrl)}>
                {content.ctaPrimary}
                <FontAwesomeIcon icon={faArrowRight} className={styles.ctaButtonIcon} aria-hidden="true" />
              </Link>
              <Link className={clsx('button button--secondary', styles.ctaSecondary)} href="https://github.com/lkimuk/gmp">
                {content.ctaSecondary}
                <FontAwesomeIcon icon={faArrowUpRightFromSquare} className={styles.ctaButtonIcon} aria-hidden="true" />
              </Link>
            </div>
          </div>
        </section>
      </main>
    </Layout>
  );
}
