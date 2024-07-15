use crate::error::{MeeCryptoErr, MeeCryptoResult};
use base64::Engine;
use password_hash::{
    PasswordHash, PasswordHasher, PasswordVerifier, SaltString,
};
use pbkdf2::Pbkdf2;

pub trait PasswdHasher<Kdf: PasswordHasher> {
    fn hash_passwd(
        &self,
        password: &[u8],
        salt: &str,
    ) -> MeeCryptoResult<PasswdHasherOutput>;
}

#[derive(Clone)]
pub struct PasswdHasherOutput {
    pub hash_bytes: Vec<u8>,
    pub b64_salt: String,
    pub b64_hash: String,
    pub phc: String,
}

impl<'a> TryFrom<PasswordHash<'a>> for PasswdHasherOutput {
    type Error = MeeCryptoErr;

    fn try_from(value: PasswordHash) -> Result<Self, Self::Error> {
        let b64_hash = value
            .hash
            .ok_or(MeeCryptoErr::kdf_error_from_string("Empty Pbkdf2 hash"))?
            .to_string();

        let b64_salt = value
            .salt
            .ok_or(MeeCryptoErr::kdf_error_from_string("Empty Pbkdf2 salt"))?
            .to_string();

        let phc = value.to_string();

        let hash_bytes = base64::engine::general_purpose::STANDARD_NO_PAD
            .decode(&b64_hash)
            .map_err(MeeCryptoErr::kdf_error_from_string)?;

        Ok(PasswdHasherOutput {
            hash_bytes,
            b64_salt,
            b64_hash,
            phc,
        })
    }
}

impl PasswdHasherOutput {
    pub fn try_from_password_hash(hash: &str) -> MeeCryptoResult<Self> {
        let phc = PasswordHash::parse(hash, password_hash::Encoding::B64)
            .map_err(MeeCryptoErr::kdf_error_from_string)?;

        Ok(phc.try_into()?)
    }
}

impl PasswdHasher<Pbkdf2> for Pbkdf2 {
    fn hash_passwd(
        &self,
        password: &[u8],
        salt: &str,
    ) -> MeeCryptoResult<PasswdHasherOutput> {
        let salt = SaltString::from_b64(salt)
            .map_err(MeeCryptoErr::kdf_error_from_string)?;

        let password_hash = Pbkdf2
            .hash_password_customized(
                password,
                Default::default(),
                Default::default(),
                pbkdf2::Params {
                    rounds: 10_000,
                    output_length: 64,
                },
                &salt,
            )
            .map_err(MeeCryptoErr::kdf_error_from_string)?
            .to_string();

        let parsed_hash = PasswordHash::new(&password_hash)
            .map_err(MeeCryptoErr::kdf_error_from_string)?;

        Pbkdf2
            .verify_password(password, &parsed_hash)
            .map_err(MeeCryptoErr::kdf_error_from_string)?;

        Ok(parsed_hash.try_into()?)
    }
}
