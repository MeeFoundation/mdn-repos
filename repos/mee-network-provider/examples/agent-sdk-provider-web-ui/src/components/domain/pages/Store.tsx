import { Button, Input, Modal, Table } from "antd";
import { styling } from "../../ui/theme";
import { CSSProperties, useCallback, useMemo, useState } from "react";
import {
  ownProviderAgentApiService, PersonaAttribute
} from "../../../api/services";
import { ColumnsType } from "antd/es/table";
import useSWR from "swr";
import { HookAPI } from "antd/es/modal/useModal";
import { DeleteOutlined } from '@ant-design/icons';
import { useServerResponseErrorNotification } from "../../../utils/error";

const keyInputWidth = 250;

const inputsRowStyle: CSSProperties = {
  display: "flex",
  justifyContent: 'flex-start',
  gap: styling.spacing.md,
  flexWrap: 'wrap',
};


const useColumns = (
  modal: HookAPI,
  onDelete: (attr: PersonaAttribute) => void
) => {

  const columns = useMemo<ColumnsType<PersonaAttribute>>(() => [
    {
      dataIndex: "key",
      title: "Key",
    },
    {
      dataIndex: "value",
      title: "Value"
    },
    {
      width: "60px",
      align: 'center',
      render: (_, record) => (
        <Button
          onClick={() => {
            modal.confirm({
              title: "Attribute deletion warning",
              content: "Are you sure to delete the attribute?",
              onOk: () => onDelete(record),
            });
          }}
          danger
          icon={<DeleteOutlined />}
        />
      ),
    }
  ], [modal, onDelete]);

  return columns;
}

export const Store: React.FC = () => {
  const [readKey, setReadKey] = useState("");
  const [writeKey, setWriteKey] = useState("alice/card/0/number");
  const [writeValue, setWriteValue] = useState("777");
  const [
    notifyServerError, notifierContext
  ] = useServerResponseErrorNotification();

  const {
    data: readData,
    mutate: setReadData,
  } = useSWR('getPersonaAttributes',
    () => ownProviderAgentApiService.getPersonaAttributes(readKey),
    { onError: notifyServerError },
  );

  const getAttributes = useCallback(() => {
    ownProviderAgentApiService
      .getPersonaAttributes(readKey)
      .then(setReadData)
      .catch(notifyServerError);
  }, [notifyServerError, readKey, setReadData]);

  const setAttributes = useCallback(async () => {
    ownProviderAgentApiService
      .setPersonaAttributes(writeKey, writeValue)
      .then(getAttributes)
      .catch(notifyServerError);
  }, [getAttributes, notifyServerError, writeKey, writeValue]);

  const onEnter = useCallback(
    (callback: () => void) => (e: React.KeyboardEvent<HTMLInputElement>) => {
      if (e.key === 'Enter') {
        callback();
      }
    }, []);

  const [modal, modalContextHolder] = Modal.useModal();

  const columns = useColumns(modal, useCallback((attr: PersonaAttribute) => {
    ownProviderAgentApiService.
      delPersonaAttributes(attr.key)
      .then(getAttributes)
      .catch(notifyServerError);
  }, [getAttributes, notifyServerError]));

  return (
    <div style={{
      display: "flex",
      flexDirection: 'column',
      gap: styling.spacing.md
    }}>
      {notifierContext}
      {modalContextHolder}
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
