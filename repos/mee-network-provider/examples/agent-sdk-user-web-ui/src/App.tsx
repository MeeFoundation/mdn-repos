import { useEffect } from "react";
import "./App.css"
import { PaymentForm } from "./components/domain/payment-form";
import { Layout, theme } from "antd";

const { Content } = Layout;

const HEADER_TITLE = `${import.meta.env.VITE_MDN_PROVIDER_NAME} - Client UI`;

const DOCUMENT_TITLE = import.meta.env.VITE_MDN_PROVIDER_NAME
  .split(" ")
  .reduce((acc, v) => `${acc}${v.charAt(0)}`, "") + " - Client UI";

function App() {
  const {
    token: { colorBgContainer },
  } = theme.useToken();

  useEffect(() => {
    document.title = DOCUMENT_TITLE;
  }, []);

  return (
    <Layout style={{
      display: "grid",
      height: "100%",
      gap: 16,
      padding: 16,
      background: colorBgContainer,
    }}>
      <Content>
        <h1>{HEADER_TITLE}</h1>
        <PaymentForm />
      </Content>
    </Layout>
  )
}

export default App
