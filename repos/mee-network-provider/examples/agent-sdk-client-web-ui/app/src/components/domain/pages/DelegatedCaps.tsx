import { Button, Modal, Table } from "antd";
import { styling } from "../../ui/theme";
import { CloudSyncOutlined, RedoOutlined } from '@ant-design/icons';
import { ColumnsType } from "antd/es/table";
import {
  DelegatedCapInfo,
  getDelegatedCaps,
  revokeDelegatedCap,
} from "../../../api/services";
import useSWR from "swr";
import { notifyServerError } from "../../../utils/error";
import { useCallback, useMemo } from "react";
import { HookAPI } from "antd/es/modal/useModal";

const useColumns = (
  modal: HookAPI,
  onRevoke: (cap: DelegatedCapInfo) => void
) => {

  const columns = useMemo<ColumnsType<DelegatedCapInfo>>(() => [
    {
      dataIndex: "cap_receiver",
      title: "Receiver (short)",
      render: (v: string | undefined) => (v || "").slice(0, 16),
    },
    {
      dataIndex: "shared_data_path",
      title: "Shared data path",
    },
    {
      render: (_, record) => (
        <Button
          onClick={() => {
            modal.confirm({
              title: "Capability revocation warning",
              content: "Are you sure to revoke capability?",
              onOk: () => onRevoke(record),
            });
          }}
          danger
          icon={<RedoOutlined />}
        >REVOKE</Button>
      ),
    }
  ], [modal, onRevoke]);

  return columns;
};


export const DelegatedCaps: React.FC = () => {
  const [modal, modalContextHolder] = Modal.useModal();

  const {
    data: delegatedCaps,
    mutate: setDelegatedCaps,
  } = useSWR(
    'getDelegatedCaps',
    getDelegatedCaps,
    { onError: notifyServerError, }
  );

  const getCaps = useCallback(() => {
    getDelegatedCaps()
      .then(setDelegatedCaps)
      .catch(notifyServerError);
  }, [setDelegatedCaps]);

  const columns = useColumns(modal, useCallback((cap: DelegatedCapInfo) => {
    revokeDelegatedCap(cap)
      .then(() => setTimeout(getCaps, 5000))
      .catch(notifyServerError);
  }, [getCaps]));

  return (
    <div style={{
      display: "flex",
      flexDirection: 'column',
      gap: styling.spacing.md
    }}>
      {modalContextHolder}
      <Table
        rowKey="capability_id"
        title={() => (
          <Button
            icon={<CloudSyncOutlined />}
            onClick={getCaps}>REFRESH
          </Button>
        )}
        size="small"
        columns={columns}
        bordered
        dataSource={delegatedCaps ?? []}
      />
    </div>
  );
};