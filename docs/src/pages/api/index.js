import {useEffect} from 'react';
import Layout from '@theme/Layout';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';

export default function ApiRedirect() {
  const {siteConfig} = useDocusaurusContext();
  const target = `${siteConfig.baseUrl}api/reference/index.html`;

  useEffect(() => {
    window.location.replace(target);
  }, [target]);

  return (
    <Layout title="API Reference">
      <main style={{padding: '4rem 1rem', textAlign: 'center'}}>
        <p>
          Redirecting to the generated API reference. If the page does not move,
          use <a href={target}>this direct link</a>.
        </p>
      </main>
    </Layout>
  );
}
