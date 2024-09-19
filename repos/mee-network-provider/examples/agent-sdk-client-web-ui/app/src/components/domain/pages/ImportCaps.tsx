import { CloudSyncOutlined } from '@ant-design/icons';
import { Button, Input, Table } from "antd";
import { styling } from "../../ui/theme";
import { useCallback, useState } from "react";
import {
  DelegateReadAccessResponse,
  getImportedCaps,
  importCapabilitiesFromProvider,
  ImportedCapability
} from "../../../api/services";
import useSWR from "swr";
import { ColumnsType } from 'antd/es/table';
import { useServerResponseErrorNotification } from '../../../utils/error';

const columns: ColumnsType<ImportedCapability> = [
  {
    dataIndex: "namespace",
    title: "Namespace",
    render: (v: string | undefined) => (v || "").slice(0, 16),
  },
  {
    dataIndex: "owner",
    title: "Data owner",
    render: (v: string | undefined) => (v || "").slice(0, 16),
  },
  {
    dataIndex: "granted_data_path",
    title: "Granted data path",
  },
  {
    dataIndex: "granted_until",
    title: "Expires",
  },
];

export const ImportCaps: React.FC = () => {
  const [
    capPack,
    setCapPack,
  ] = useState("");

  const [
    notifyServerError, notifierContext
  ] = useServerResponseErrorNotification();

  const {
    data: importedCaps,
    mutate: setImportedCaps,
  } = useSWR(
    'getImportedCaps',
    getImportedCaps,
    { onError: notifyServerError, }
  );

  const refreshImportedCaps = useCallback(() => {
    getImportedCaps().then(setImportedCaps);
  }, [setImportedCaps]);

  const handleImport = useCallback(async () => {
    try {
      const pack: DelegateReadAccessResponse = JSON.parse(capPack);
      await importCapabilitiesFromProvider(pack);

      setCapPack("");
      refreshImportedCaps();
    } catch (e: unknown) {
      notifyServerError(e);
    }
  }, [capPack, notifyServerError, refreshImportedCaps]);

  return (
    <div style={{
      display: "flex",
      flexDirection: 'column',
      gap: styling.spacing.md
    }}>
      {notifierContext}
      <div style={{
        display: "grid",
        gridTemplateColumns: "1fr 1fr",
        gap: styling.spacing.md,
      }}>
        <div style={{ display: "grid", gap: styling.spacing.md }}>
          <Input.TextArea
            style={{ height: 150 }}
            onChange={e => setCapPack(e.target.value)}
            value={capPack}
            placeholder="Put your capability package here..."
          />
          <Button
            type="primary"
            disabled={capPack === ''}
            onClick={handleImport}
          >IMPORT</Button>
        </div>
      </div>

      <Table
        title={() => (
          <Button
            icon={<CloudSyncOutlined />}
            onClick={refreshImportedCaps}>REFRESH
          </Button>
        )}
        size="small"
        columns={columns}
        bordered
        dataSource={importedCaps ?? []}
      />
    </div>
  );
};