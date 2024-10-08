import { styling } from "../../ui/theme";
import type { FormProps } from 'antd';
import { Button, Form, Input } from 'antd';
import {
  DelegateReadAccessRequest,
  DelegateReadAccessResponse,
  ownProviderAgentApiService,
} from "../../../api/services";
import { useCallback, useState } from "react";
import { useServerResponseErrorNotification } from "../../../utils/error";

const onFinishFailed: FormProps<DelegateReadAccessRequest>['onFinishFailed'] =
  (errorInfo) => {
    console.log('Failed:', errorInfo);
  };

const formInputLabelStyle = { width: 110 };

export const ExportCaps: React.FC = () => {
  const [
    capPack,
    setCapPack,
  ] = useState<DelegateReadAccessResponse | null>(null);

  const [
    notifyServerError, notifierContext
  ] = useServerResponseErrorNotification();

  const onFinish = useCallback(
    async (values: DelegateReadAccessRequest) => {
      ownProviderAgentApiService
        .delegateReadAccessToProvider(values)
        .then(setCapPack)
        .catch(notifyServerError);
    }, [notifyServerError]
  );

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
        <Form
          name="export_caps"
          onFinish={onFinish}
          onFinishFailed={onFinishFailed}
          autoComplete="off"
        >
          <Form.Item<DelegateReadAccessRequest>
            label="Data path"
            labelAlign="left"
            labelCol={{ style: formInputLabelStyle }}
            name="data_path"
            rules={[{
              required: true,
              message: 'Please input your data_path!'
            }]}
            initialValue="alice/address"
          >
            <Input />
          </Form.Item>

          <Form.Item<DelegateReadAccessRequest>
            label="Provider ID"
            labelAlign="left"
            labelCol={{ style: formInputLabelStyle }}
            name="provider_id"
            rules={[{
              required: true,
              message: 'Please input your provider_id!'
            }]}
          >
            <Input />
          </Form.Item>

          <Form.Item>
            <Button type="primary" htmlType="submit">
              EXPORT
            </Button>
          </Form.Item>
        </Form>

        <Input.TextArea
          style={{ height: 150 }}
          value={capPack ? JSON.stringify(capPack) : ""}
          placeholder="Capability package will appear here..."
        />
      </div>
    </div >
  );
};