import { notification } from "antd";
import { AxiosError } from "axios";

export function useServerResponseErrorNotification() {
  const [notifier, notifierContextHolder] = notification.useNotification();

  return [(err: unknown) => {
    if (err instanceof AxiosError) {
      const respData = err.response?.data;

      const description = typeof respData === 'string'
        ? respData
        : err.message;

      const message = err.response?.status && err.response?.statusText
        ? `${err.response?.status} ${err.response?.statusText}`
        : "Response error";

      notifier.error({
        description,
        message,
      });
    } else {
      notifier.error({
        description: (err as object).toString(),
        message: "Other error",
      });
    }
  }, notifierContextHolder] as const;
}