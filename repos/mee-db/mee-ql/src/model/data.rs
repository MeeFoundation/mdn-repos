use super::schema::{Field, FieldType, ObjectId, Schema};

#[derive(Debug)]
pub struct FieldValue<'a> {
    pub field: &'a Field,
    pub value: Option<Vec<u8>>,
}

#[derive(Debug)]
pub struct Column {
    pub name: String,
    pub _type: FieldType,
}

#[derive(Debug)]
pub struct Records {
    pub fields: Vec<Column>,
    pub values: Vec<Option<Vec<u8>>>,
}

#[derive(Debug)]
pub struct ObjectFieldSet<'a> {
    pub schema: &'a Schema,
    pub id: ObjectId,
    pub values: Vec<FieldValue<'a>>,
}

#[derive(Debug)]
pub struct NewObjectFieldSet<'a> {
    pub schema: &'a Schema,
    pub values: Vec<FieldValue<'a>>,
}
