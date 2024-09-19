import './App.css';
import { AuditOutlined, DatabaseOutlined } from '@ant-design/icons';
import { Layout, Menu, theme } from 'antd';
import { MenuItemType } from 'antd/es/menu/interface';
import { useState } from 'react';
import { Store } from './components/domain/pages/Store';
import { Capabilities } from './components/domain/pages/Capabilities';
import { styling } from './components/ui/theme';
import { Header } from './components/control/nav/Header';

const { Header: Head, Content, Sider } = Layout;

enum NavMenuItem {
  Store = "Store",
  Capabilities = "Capabilities",
}

const items: MenuItemType[] = [{
  key: NavMenuItem.Store,
  label: NavMenuItem.Store,
  icon: <DatabaseOutlined />,
  style: { paddingLeft: styling.spacing.md },
}, {
  key: NavMenuItem.Capabilities,
  label: NavMenuItem.Capabilities,
  icon: <AuditOutlined />,
  style: { paddingLeft: styling.spacing.md },
}];

function App() {
  const {
    token: { colorBgContainer, borderRadiusLG },
  } = theme.useToken();

  const [navItem, setNavItem] = useState<string[]>([NavMenuItem.Store]);

  return (
    <Layout style={{ height: "100%" }}>
      <Head style={{ padding: `0 ${styling.spacing.md}px` }}>
        <Header />
      </Head>
      <Layout>
        <Sider >
          <Menu
            theme="dark"
            mode="inline"
            selectedKeys={navItem}
            onSelect={e => setNavItem(e.selectedKeys)}
            items={items}
          />
        </Sider>
        <Content style={{ display: "grid", overflow: 'scroll' }}>
          <div
            style={{
              margin: styling.spacing.md,
              padding: styling.spacing.md,
              display: "grid",
              gap: styling.spacing.md,
              background: colorBgContainer,
              borderRadius: borderRadiusLG,
            }}
          >
            {navItem[0] === NavMenuItem.Store && <Store />}
            {navItem[0] === NavMenuItem.Capabilities && <Capabilities />}
          </div>
        </Content>
      </Layout>
    </Layout>
  )
}

export default App
