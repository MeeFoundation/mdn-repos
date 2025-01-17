/// <reference types="vite/client" />

interface ImportMetaEnv {
  readonly VITE_MDN_PROVIDER_NAME: string,
  readonly VITE_MDN_PROVIDER_API_PORT: string,
  readonly VITE_MDN_PROVIDER_API_HOST: string,
  // more env variables...
}

interface ImportMeta {
  readonly env: ImportMetaEnv
}