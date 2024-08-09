pub type SchemaName = String;
pub type FieldName = String;
pub type ObjectIdType = String;

#[derive(Debug)]
#[allow(unused)]
pub struct Schema {
    pub path: SchemaName,
    pub fields: Vec<Field>,
}

#[derive(Debug)]
#[allow(unused)]
pub struct Field {
    pub name: FieldName,
    pub _type: FieldType,
    pub required: bool,
}

#[derive(Debug)]
#[allow(unused)]
pub enum FieldType {
    Bool,
    Number,
    String,
    Array(Box<FieldType>),
    Embedded(Schema),
    Link(String, Schema),
}

#[derive(Debug)]
#[allow(unused)]
pub struct ObjectId {
    pub id: ObjectIdType,
    pub schema: SchemaName,
}
