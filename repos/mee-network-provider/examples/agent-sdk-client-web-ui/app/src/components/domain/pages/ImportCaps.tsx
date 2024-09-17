import { Button, Input } from "antd";
import { styling } from "../../ui/theme";
import { useCallback, useState } from "react";
import {
  DelegateReadAccessResponse,
  importCapabilitiesFromProvider
} from "../../../api/services";
import { notifyServerError } from "../../../utils/error";

export const ImportCaps: React.FC = () => {
  const [
    capPack,
    setCapPack,
  ] = useState("");

  const handleImport = useCallback(async () => {
    try {
      const pack: DelegateReadAccessResponse = JSON.parse(capPack);
      const res = await importCapabilitiesFromProvider(pack);

      setCapPack(res);
    } catch (e: unknown) {
      notifyServerError(e);
    }
  }, [capPack]);

  return (
    <div style={{
      display: "flex",
      flexDirection: 'column',
      gap: styling.spacing.md
    }}>
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
    </div>
  );
};