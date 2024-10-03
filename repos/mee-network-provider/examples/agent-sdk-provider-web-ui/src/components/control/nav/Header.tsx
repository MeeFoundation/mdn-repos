import { Tag } from "antd";
import { ClusterOutlined } from '@ant-design/icons';
import useSWR from "swr";
import { ownProviderAgentApiService } from "../../../api/services";
import { styling } from "../../ui/theme";
import { useServerResponseErrorNotification } from "../../../utils/error";
import { useEffect } from "react";

const HEADER_TITLE = `${import.meta.env.VITE_MDN_PROVIDER_NAME} - Admin UI`;

const DOCUMENT_TITLE = import.meta.env.VITE_MDN_PROVIDER_NAME
  .split(" ")
  .reduce((acc, v) => `${acc}${v.charAt(0)}`, "") + " - Admin UI";

export const Header: React.FC = () => {
  const [
    notifyServerError, notifierContext
  ] = useServerResponseErrorNotification();

  const { data: nodeId } = useSWR(
    "getWillowNodeId",
    ownProviderAgentApiService.getWillowNodeId,
    { onError: notifyServerError }
  );

  useEffect(() => {
    document.title = DOCUMENT_TITLE;
  }, []);

  return (
    <div
      style={{
        display: "flex",
        justifyContent: 'space-between',
        alignItems: 'center'
      }}>
      {notifierContext}
      <div>{HEADER_TITLE}</div>
      <Tag
        style={{ fontSize: styling.font.md }}
        icon={<ClusterOutlined />}
      >{nodeId ?? "N/A"}</Tag>
    </div>
  );
};