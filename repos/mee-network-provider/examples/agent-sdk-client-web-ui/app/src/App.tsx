import './App.css';
import {
  AuditOutlined, DatabaseOutlined,
  LeftCircleOutlined, RightCircleOutlined
} from '@ant-design/icons';
import { Button, Layout, Menu, theme } from 'antd';
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
}, {
  key: NavMenuItem.Capabilities,
  label: NavMenuItem.Capabilities,
  icon: <AuditOutlined />,
}];

function App() {
  const {
    token: { colorBgContainer, borderRadiusLG },
  } = theme.useToken();

  const [navItem, setNavItem] = useState<string[]>([NavMenuItem.Store]);
  const [navCollapsed, setNavCollapsed] = useState(false);

  return (
    <Layout style={{
      height: "100%",
      gap: styling.spacing.md,
      padding: styling.spacing.md,
    }}>
      <Head style={{
        padding: `0 ${styling.spacing.md}px`,
        borderRadius: borderRadiusLG
      }}>
        <Header />
      </Head>
      <Layout style={{ gap: styling.spacing.md }}>
        <Sider
          collapsed={navCollapsed}
          style={{
            padding: `${styling.spacing.md}px ${styling.spacing.sm}px`,
            borderRadius: borderRadiusLG,
          }}>
          <div style={{
            height: "100%",
            display: "flex",
            flexDirection: 'column',
            justifyContent: 'space-between'
          }}>
            <Menu
              theme="dark"
              selectedKeys={navItem}
              onSelect={e => setNavItem(e.selectedKeys)}
              items={items}
            />
            <Button
              type='text'
              block
              onClick={() => setNavCollapsed(prev => !prev)}
              icon={!navCollapsed
                ? <LeftCircleOutlined />
                : <RightCircleOutlined />
              }
            />
          </div>
        </Sider>
        <Content style={{
          overflow: 'scroll',
          padding: styling.spacing.md,
          display: "grid",
          gap: styling.spacing.md,
          background: colorBgContainer,
          borderRadius: borderRadiusLG,
        }}>
          {navItem[0] === NavMenuItem.Store && <Store />}
          {navItem[0] === NavMenuItem.Capabilities && <Capabilities />}
        </Content>
      </Layout>
    </Layout>
  )
}

export default App
