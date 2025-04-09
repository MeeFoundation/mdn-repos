import axios from "axios";

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

export function createProviderAgentApiService(
  port = import.meta.env.VITE_MDN_PROVIDER_API_PORT,
  host = import.meta.env.VITE_MDN_PROVIDER_API_HOST,
  protocol = import.meta.env.VITE_MDN_PROVIDER_API_PROTOCOL
) {
  const ProviderAgentApiServiceFactory =
    axios.create({
      baseURL: `${protocol}://${host}:${port}/api/v1/provider_agent`
    });

  const ProviderAgentCapsApiServiceFactory =
    (path: string) => axios.create({
      baseURL: "".concat(
        ProviderAgentApiServiceFactory.defaults.baseURL || "",
        "/capabilities/",
        path)
    });

  const ProviderAgentNodeApiServiceFactory =
    (path: string) => axios.create({
      baseURL: "".concat(
        ProviderAgentApiServiceFactory.defaults.baseURL || "",
        "/node/",
        path)
    });

  const ProviderAgentPersonaApiServiceFactory =
    (path: string) => axios.create({
      baseURL: "".concat(
        ProviderAgentApiServiceFactory.defaults.baseURL || "",
        "/persona/",
        path)
    });

  const ProviderAgentDelegatedCapsApiService =
    ProviderAgentCapsApiServiceFactory("delegated_caps");

  const ProviderAgentImportedCapsApiService =
    ProviderAgentCapsApiServiceFactory("imported_caps");

  const ProviderAgentRevokeCapApiService =
    ProviderAgentCapsApiServiceFactory("revoke_shared_access_from_provider");

  const ProviderAgentDelegateReadCapApiService =
    ProviderAgentCapsApiServiceFactory("delegate_read_access_to_provider");

  const ProviderAgentImportReadCapApiService =
    ProviderAgentCapsApiServiceFactory("import_capabilities_from_provider");

  const ProviderAgentWillowIdApiService =
    ProviderAgentNodeApiServiceFactory("willow_id");

  const ProviderAgentGetAttributesApiService =
    ProviderAgentPersonaApiServiceFactory("get_attributes");

  const ProviderAgentSetAttributesApiService =
    ProviderAgentPersonaApiServiceFactory("set_attributes");

  const ProviderAgentDelAttributesApiService =
    ProviderAgentPersonaApiServiceFactory("del_attributes");



  const getDelegatedCaps = () => ProviderAgentDelegatedCapsApiService
    .get<DelegatedCapInfo[]>("")
    .then(d => d.data);

  const getImportedCaps = () => ProviderAgentImportedCapsApiService
    .get<ImportedCapability[]>("")
    .then(d => d.data);

  const revokeDelegatedCap =
    (cap: DelegatedCapInfo) => ProviderAgentRevokeCapApiService
      .post("", cap)
      .then(d => d.data);


  const delegateReadAccessToProvider =
    (payload: DelegateReadAccessRequest) =>
      ProviderAgentDelegateReadCapApiService
        .post<DelegateReadAccessResponse>("", payload)
        .then(d => d.data);

  const importCapabilitiesFromProvider =
    (payload: DelegateReadAccessResponse) =>
      ProviderAgentImportReadCapApiService
        .post("", payload)
        .then(d => d.data);

  const getWillowNodeId = () => ProviderAgentWillowIdApiService
    .get<string | null>("")
    .then(d => d.data);

  const getPersonaAttributes =
    (key: string) => ProviderAgentGetAttributesApiService
      .post<PersonaAttribute[]>("", { key })
      .then(d => d.data);

  const setPersonaAttributes =
    (key: string, value: string) => ProviderAgentSetAttributesApiService
      .post<PersonaAttribute[]>("", { key, value })
      .then(d => d.data);

  const delPersonaAttributes =
    (key: string) => ProviderAgentDelAttributesApiService
      .post("", { key })
      .then(d => d.data);

  return {
    getDelegatedCaps,
    getImportedCaps,
    revokeDelegatedCap,
    delegateReadAccessToProvider,
    importCapabilitiesFromProvider,
    getWillowNodeId,
    getPersonaAttributes,
    setPersonaAttributes,
    delPersonaAttributes,
  };
}

export const ownProviderAgentApiService = createProviderAgentApiService();
