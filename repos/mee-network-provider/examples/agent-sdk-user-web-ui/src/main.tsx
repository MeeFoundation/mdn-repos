import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import App from './App.tsx'
import './index.css'
import { ConfigProvider, theme } from 'antd'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <ConfigProvider
      theme={{
        algorithm: theme.darkAlgorithm,
        token: {
          fontSize: 16,
          colorPrimary: "#4f868e",
        }
      }}
    >
      <App />
    </ConfigProvider>
  </StrictMode>,
)
