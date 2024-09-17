import { notification } from "antd";

export function notifyServerError(e: unknown) {
  notification.error({
    description: (e as object).toString(),
    message: 'Server error',
  });
}