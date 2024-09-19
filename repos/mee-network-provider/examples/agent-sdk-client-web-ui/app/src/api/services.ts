import axios from "axios";

export const ProviderAgentApiServiceFactory =
  axios.create({
    baseURL: "".concat(
      "http://127.0.0.1:",
      import.meta.env.VITE_MDN_PROVIDER_API_PORT,
      "/api/v1/provider_agent")
  });

export const ProviderAgentCapsApiServiceFactory =
  (path: string) => axios.create({
    baseURL: "".concat(
      ProviderAgentApiServiceFactory.defaults.baseURL || "",
      "/capabilities/",
      path)
  });

export const ProviderAgentNodeApiServiceFactory =
  (path: string) => axios.create({
    baseURL: "".concat(
      ProviderAgentApiServiceFactory.defaults.baseURL || "",
      "/node/",
      path)
  });

export const ProviderAgentPersonaApiServiceFactory =
  (path: string) => axios.create({
    baseURL: "".concat(
      ProviderAgentApiServiceFactory.defaults.baseURL || "",
      "/persona/",
      path)
  });

export const ProviderAgentDelegatedCapsApiService =
  ProviderAgentCapsApiServiceFactory("delegated_caps");

export const ProviderAgentImportedCapsApiService =
  ProviderAgentCapsApiServiceFactory("imported_caps");

export const ProviderAgentRevokeCapApiService =
  ProviderAgentCapsApiServiceFactory("revoke_shared_access_from_provider");

export const ProviderAgentDelegateReadCapApiService =
  ProviderAgentCapsApiServiceFactory("delegate_read_access_to_provider");

export const ProviderAgentImportReadCapApiService =
  ProviderAgentCapsApiServiceFactory("import_capabilities_from_provider");

export const ProviderAgentWillowIdApiService =
  ProviderAgentNodeApiServiceFactory("willow_id");

export const ProviderAgentGetAttributesApiService =
  ProviderAgentPersonaApiServiceFactory("get_attributes");

export const ProviderAgentSetAttributesApiService =
  ProviderAgentPersonaApiServiceFactory("set_attributes");

export const ProviderAgentDelAttributesApiService =
  ProviderAgentPersonaApiServiceFactory("del_attributes");

export type DelegatedCapInfo = {
  cap_receiver: string,
  capability_id: string,
  shared_data_path: string
};

export type PersonaAttribute = {
  key: string,
  value: string,
};

export type DelegateReadAccessResponse = {
  caps: Record<string, unknown>,
  provider_node_ticket: string
};

export type DelegateReadAccessRequest = {
  data_path: string,
  provider_id: string,
};

export type ImportedCapability = {
  namespace_kind: string,
  namespace: string,
  owner: string,
  receiver: string,
  granted_data_path: string,
  granted_until?: string,
}

export const getDelegatedCaps = () => ProviderAgentDelegatedCapsApiService
  .get<DelegatedCapInfo[]>("")
  .then(d => d.data);

export const getImportedCaps = () => ProviderAgentImportedCapsApiService
  .get<ImportedCapability[]>("")
  .then(d => d.data);

export const revokeDelegatedCap =
  (cap: DelegatedCapInfo) => ProviderAgentRevokeCapApiService
    .post("", cap)
    .then(d => d.data);


export const delegateReadAccessToProvider =
  (payload: DelegateReadAccessRequest) => ProviderAgentDelegateReadCapApiService
    .post<DelegateReadAccessResponse>("", payload)
    .then(d => d.data);

export const importCapabilitiesFromProvider =
  (payload: DelegateReadAccessResponse) => ProviderAgentImportReadCapApiService
    .post("", payload)
    .then(d => d.data);

export const getWillowNodeId = () => ProviderAgentWillowIdApiService
  .get<string | null>("")
  .then(d => d.data);

export const getPersonaAttributes =
  (key: string) => ProviderAgentGetAttributesApiService
    .post<PersonaAttribute[]>("", { key })
    .then(d => d.data)

export const setPersonaAttributes =
  (key: string, value: string) => ProviderAgentSetAttributesApiService
    .post<PersonaAttribute[]>("", { key, value })
    .then(d => d.data)

export const delPersonaAttributes =
  (key: string) => ProviderAgentDelAttributesApiService
    .post("", { key })
    .then(d => d.data)