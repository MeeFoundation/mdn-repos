import { Button, Input, Table } from "antd";
import { styling } from "../../ui/theme";
import { CSSProperties, useCallback, useState } from "react";
import {
  getPersonaAttributes, PersonaAttribute, setPersonaAttributes
} from "../../../api/services";
import { ColumnsType } from "antd/es/table";
import useSWR from "swr";
import { notifyServerError } from "../../../utils/error";

const keyInputWidth = 250;

const inputsRowStyle: CSSProperties = {
  display: "flex",
  justifyContent: 'flex-start',
  gap: styling.spacing.md
};

const columns: ColumnsType<PersonaAttribute> = [
  {
    dataIndex: "key",
    title: "Key",
  },
  {
    dataIndex: "value",
    title: "Value"
  }
];

export const Store: React.FC = () => {
  const [readKey, setReadKey] = useState("");
  const [writeKey, setWriteKey] = useState("alice/address/0/city");
  const [writeValue, setWriteValue] = useState("Paris");

  const {
    data: readData,
    mutate: setReadData,
  } = useSWR('getPersonaAttributes',
    () => getPersonaAttributes(readKey),
    { onError: notifyServerError },
  );

  const getAttributes = useCallback(() => {
    getPersonaAttributes(readKey)
      .then(setReadData)
      .catch(notifyServerError);
  }, [readKey, setReadData]);

  const setAttributes = useCallback(async () => {
    setPersonaAttributes(writeKey, writeValue).catch(notifyServerError);
  }, [writeKey, writeValue]);

  const onEnter =
    (callback: () => void) => (e: React.KeyboardEvent<HTMLInputElement>) => {
      if (e.key === 'Enter') {
        callback();
      }
    };

  return (
    <div style={{
      display: "flex",
      flexDirection: 'column',
      gap: styling.spacing.md
    }}>
      <h1 style={{ marginTop: 0 }}>Personal data storage</h1>
      <div style={inputsRowStyle}>
        <Input
          value={readKey}
          onKeyDown={onEnter(getAttributes)}
          onChange={e => setReadKey(e.target.value)}
          placeholder="key"
          style={{ width: keyInputWidth }}
        />
        <Button
          onClick={getAttributes}
          type="primary"
        >QUERY</Button>
      </div>

      <div style={inputsRowStyle}>
        <Input
          value={writeKey}
          onChange={e => setWriteKey(e.target.value)}
          style={{ width: keyInputWidth }}
          placeholder="key"
          onKeyDown={onEnter(setAttributes)}
        />
        <Input
          value={writeValue}
          onChange={e => setWriteValue(e.target.value)}
          style={{ width: 150 }}
          placeholder="value"
          onKeyDown={onEnter(setAttributes)}
        />
        <Button
          onClick={setAttributes}
          type="primary"
          disabled={writeKey === '' || writeValue === ''}
        >WRITE</Button>
      </div>

      <Table
        size="small"
        columns={columns}
        bordered
        dataSource={readData ?? []}
      />
    </div>
  );
};
