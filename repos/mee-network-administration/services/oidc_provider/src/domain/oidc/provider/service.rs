use crate::domain::oidc::{
    grants::service::OidcProviderGrantsService,
    issuer::service::OidcProviderIssuerService,
    oxide_async_endpoint::{Generic, Vacant},
    registrar::service::OidcProviderRegistrarService,
};
use oxide_auth_async::primitives::{Authorizer, Issuer, Registrar};

#[derive(Clone)]
pub struct OidcProviderService<'a> {
    pub registrar: OidcProviderRegistrarService<'a>,
    authorizer: OidcProviderGrantsService<'a>,
    issuer: OidcProviderIssuerService<'a>,
}

impl<'a> OidcProviderService<'a> {
    pub fn new(
        registrar: OidcProviderRegistrarService<'a>,
        authorizer: OidcProviderGrantsService<'a>,
        issuer: OidcProviderIssuerService<'a>,
    ) -> Self {
        Self {
            registrar,
            authorizer,
            issuer,
        }
    }

    pub fn endpoint(
        &self,
    ) -> Generic<
        impl Registrar + Sync + Send + 'a,
        impl Authorizer + Sync + Send + 'a,
        impl Issuer + Sync + Send + 'a,
    > {
        Generic {
            registrar: self.registrar.clone(),
            authorizer: self.authorizer.clone(),
            issuer: self.issuer.clone(),
            // Solicitor configured later.
            solicitor: Vacant,
            // Scope configured later.
            scopes: Vacant,
            response: Vacant,
        }
    }
}
