import { api_services } from "mdn_client_sdk";

export const anotherProviderAgentApiService =
  api_services.createProviderAgentApiService(
    import.meta.env.VITE_MDN_ANOTHER_PROVIDER_API_PORT,
    import.meta.env.VITE_MDN_ANOTHER_PROVIDER_API_HOST,
  );

export const hasAnotherProviderInfo =
  import.meta.env.VITE_MDN_ANOTHER_PROVIDER_API_PORT !== undefined;