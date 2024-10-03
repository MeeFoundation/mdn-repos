import { Tabs } from 'antd';
import type { TabsProps } from 'antd';
import { ImportCaps } from "./ImportCaps";
import { ExportCaps } from "./ExportCaps";
import { DelegatedCaps } from './DelegatedCaps';


enum CapsTabEnum {
  Import = 'Import caps',
  Export = 'Export caps',
  DelegatedCaps = 'Delegated caps',
}

const items: TabsProps['items'] = [
  {
    key: CapsTabEnum.Export,
    label: CapsTabEnum.Export,
    children: <ExportCaps />,
  },
  {
    key: CapsTabEnum.Import,
    label: CapsTabEnum.Import,
    children: <ImportCaps />,
  },
  {
    key: CapsTabEnum.DelegatedCaps,
    label: CapsTabEnum.DelegatedCaps,
    children: <DelegatedCaps />,
  },
];

export const Capabilities: React.FC = () => {
  return (
    <Tabs
      defaultActiveKey={CapsTabEnum.Export}
      items={items}
    />
  );
};
