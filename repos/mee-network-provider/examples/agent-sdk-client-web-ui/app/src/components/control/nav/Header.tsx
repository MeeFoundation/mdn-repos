import { Tag } from "antd";
import { ClusterOutlined } from '@ant-design/icons';
import useSWR from "swr";
import { getWillowNodeId } from "../../../api/services";
import { styling } from "../../ui/theme";
import { useServerResponseErrorNotification } from "../../../utils/error";

export const Header: React.FC = () => {
  const [
    notifyServerError, notifierContext
  ] = useServerResponseErrorNotification();

  const { data: nodeId } = useSWR(
    "getWillowNodeId",
    getWillowNodeId,
    { onError: notifyServerError }
  );

  return (
    <div
      style={{
        display: "flex",
        justifyContent: 'space-between',
        alignItems: 'center'
      }}>
      {notifierContext}
      <div> {import.meta.env.VITE_MDN_PROVIDER_NAME} - Admin UI</div>
      <Tag
        style={{ fontSize: styling.font.md }}
        icon={<ClusterOutlined />}
      >{nodeId ?? "N/A"}</Tag>
    </div>
  );
};