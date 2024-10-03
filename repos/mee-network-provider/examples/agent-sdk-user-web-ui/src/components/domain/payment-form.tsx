import {
  useServerResponseErrorNotification,
} from "mdn_client_sdk/src/utils/error";
import { useCallback, useState } from "react";
import { Controller, useForm, UseFormReset } from "react-hook-form";
import {
  anotherProviderAgentApiService,
  hasAnotherProviderInfo
} from "../../api/services";
import useSWR from "swr";
import { Button, Form, Input, Modal } from "antd";
import {
  ownProviderAgentApiService,
  PersonaAttribute,
} from "mdn_client_sdk/src/api/services";

export const PAYMENT_CARD_PATH = "alice/card/0";
export const PAYMENT_CARD_NUMBER = `${PAYMENT_CARD_PATH}/number`;
export const PAYMENT_CARD_CVV = `${PAYMENT_CARD_PATH}/cvv`;
export const PAYMENT_CARD_EXPIRES = `${PAYMENT_CARD_PATH}/expires`;

export type PaymentFormData = {
  card_num: string,
  card_cvv: string,
  card_exp: string,
}

const paymentCardKeyMapper: Record<keyof PaymentFormData, string> = {
  card_cvv: PAYMENT_CARD_CVV,
  card_exp: PAYMENT_CARD_EXPIRES,
  card_num: PAYMENT_CARD_NUMBER,
};

function parsePaymentCard(attrs: PersonaAttribute[]) {
  const card: PaymentFormData = {
    card_cvv: "",
    card_exp: "",
    card_num: "",
  };

  for (const attr of attrs) {
    if (attr.key === PAYMENT_CARD_CVV) {
      card.card_cvv = attr.value;
    }
    if (attr.key === PAYMENT_CARD_NUMBER) {
      card.card_num = attr.value;
    }
    if (attr.key === PAYMENT_CARD_EXPIRES) {
      card.card_exp = attr.value;
    }
  }

  return card;
}

async function fetchPaymentCard() {
  const data = await ownProviderAgentApiService
    .getPersonaAttributes(PAYMENT_CARD_PATH);

  const card = parsePaymentCard(data);

  return card;
}

function useProviderDataSharing(
  onAutoFill: UseFormReset<PaymentFormData>
) {
  const [
    notifyServerError,
    notifierContext,
    notifier,
  ] = useServerResponseErrorNotification();

  const { data: ownNodeId } = useSWR(
    "getWillowNodeId",
    ownProviderAgentApiService.getWillowNodeId,
    { onError: notifyServerError }
  );

  const {
    data: importedCaps,
  } = useSWR(
    'getImportedCaps',
    ownProviderAgentApiService.getImportedCaps,
    { onError: notifyServerError }
  );

  const [consentModalOpened, setConsentModalOpened] = useState(false);
  const [dataSyncing, setDataSyncing] = useState(false);

  const onConsentCancel = useCallback(() => {
    setConsentModalOpened(false);
    setDataSyncing(false);
  }, []);

  const onConsentOk = useCallback(async () => {
    if (!ownNodeId) return;

    try {
      setDataSyncing(true);

      const caps = await anotherProviderAgentApiService
        .delegateReadAccessToProvider({
          data_path: PAYMENT_CARD_PATH,
          provider_id: ownNodeId,
        });

      await ownProviderAgentApiService
        .importCapabilitiesFromProvider(caps);

      const timerId = setInterval(async () => {
        try {
          const data = await ownProviderAgentApiService
            .getPersonaAttributes(PAYMENT_CARD_PATH);

          if (data.length) {
            const card = parsePaymentCard(data);
            onAutoFill(card);
            clearInterval(timerId);
            onConsentCancel();
          }

        } catch (e) {
          clearInterval(timerId);
          notifyServerError(e);
          setDataSyncing(false);
        }
      }, 1000);
    } catch (e) {
      notifyServerError(e);
      setDataSyncing(false);
    }
  }, [ownNodeId, onAutoFill, onConsentCancel, notifyServerError]);


  const handleUserConsent = useCallback(async () => {
    if (ownNodeId && importedCaps) {
      if (!importedCaps
        .some(cap => cap.granted_data_path === PAYMENT_CARD_PATH)
      ) {
        setConsentModalOpened(true);
      } else {
        try {
          const card = await fetchPaymentCard();
          onAutoFill(card);
        } catch (e) {
          notifyServerError(e);
        }
      }
    }

  }, [ownNodeId, importedCaps, onAutoFill, notifyServerError]);

  const onDataSubmit = useCallback(async (paymentData: PaymentFormData) => {
    const setters = Object.entries(paymentData)
      .reduce(
        (acc, [k, v]) => [
          ...acc,
          ownProviderAgentApiService.setPersonaAttributes(
            paymentCardKeyMapper[k as keyof PaymentFormData],
            v,
          )],
        [] as Promise<unknown>[],
      );

    try {
      await Promise.all(setters);
      notifier.success({
        message: "Success",
        description: "Data was successfully updated!",
      });
      onAutoFill({
        card_cvv: '',
        card_exp: '',
        card_num: '',
      });
    } catch (e) {
      notifyServerError(e);
    }
  }, [notifier, notifyServerError, onAutoFill]);

  return {
    consentButtonText: dataSyncing ? "Data syncing..." : "Share data",
    consentButtonDisabled: dataSyncing,
    notifierContext,
    onConsentOk,
    onConsentCancel,
    consentModalOpened,
    ownNodeId,
    importedCaps,
    handleUserConsent,
    onDataSubmit,
  };
}


export const PaymentForm: React.FC = () => {
  const {
    handleSubmit,
    reset,
    control,
  } = useForm<PaymentFormData>();

  const {
    notifierContext,
    handleUserConsent,
    onConsentOk,
    onConsentCancel,
    consentModalOpened,
    consentButtonText,
    consentButtonDisabled,
    onDataSubmit,
  } = useProviderDataSharing(reset);

  return (
    <>
      {notifierContext}
      <Modal
        open={consentModalOpened}
        okText={consentButtonText}
        okButtonProps={{ disabled: consentButtonDisabled }}
        onOk={onConsentOk}
        maskClosable={false}
        onCancel={onConsentCancel}
        onClose={onConsentCancel}
        title={"Mee data sharing consent"}
      >Are you sure to share requested data with the provider?
      </Modal>
      <h2>Payment information</h2>
      <Form style={{
        display: "grid",
        gap: 16,
        gridAutoColumns: "300px"
      }} onSubmitCapture={handleSubmit(onDataSubmit)}>
        <Controller
          name="card_num"
          control={control}
          rules={{ required: true }}
          render={({ field }) => (
            <Input
              placeholder="Card number"
              {...field}
              type="text"
            />
          )} />

        <Controller
          name="card_exp"
          control={control}
          rules={{ required: true }}
          render={({ field }) => (
            <Input
              {...field}
              type="text"
              placeholder="Expires"
            />
          )} />

        <Controller
          name="card_cvv"
          control={control}
          rules={{ required: true }}
          render={({ field }) => (
            <Input
              {...field}
              type="text"
              placeholder="CVV"
            />
          )} />

        <Button
          type="primary"
          onClick={handleUserConsent}
          disabled={!hasAnotherProviderInfo}
        >AUTOFILL WITH MEE</Button>
        <Button
          type="primary"
          htmlType="submit"
          disabled={hasAnotherProviderInfo}
        >SUBMIT
        </Button>
      </Form>
    </>
  );
};