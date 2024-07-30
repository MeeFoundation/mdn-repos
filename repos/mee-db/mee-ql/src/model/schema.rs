pub type SchemaName = String;
pub type FieldName = String;
pub type ObjectIdType = String;

#[derive(Debug)]
pub struct Schema {
    pub path: SchemaName,
    pub fields: Vec<Field>,
}

#[derive(Debug)]
pub struct Field {
    pub name: FieldName,
    pub _type: FieldType,
    pub required: bool,
}

#[derive(Debug)]
pub enum FieldType {
    String,
    Int,
    Float,
    Bool,
    Date,
    Array(Box<FieldType>),
    Object(Schema),
    Id(Schema),
}

#[derive(Debug)]
pub struct ObjectId {
    pub id: ObjectIdType,
    pub schema: SchemaName,
}


