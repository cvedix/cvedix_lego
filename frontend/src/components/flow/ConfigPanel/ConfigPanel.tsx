import React from 'react';
import { useAppSelector, useAppDispatch } from '@/store';
import { updateNodeConfig } from '@/store';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { Select, SelectContent, SelectItem, SelectTrigger, SelectValue } from '@/components/ui/select';
import { Switch } from '@/components/ui/switch';
import { ConfigFieldSchema, NodeConfig } from '@/models';

export const ConfigPanel: React.FC = () => {
  const dispatch = useAppDispatch();
  const selectedNodeId = useAppSelector((state) => state.ui.selectedNodeId);
  const node = useAppSelector((state) =>
    state.pipeline.pipeline.nodes.find((n) => n.id === selectedNodeId)
  );

  if (!selectedNodeId || !node) {
    return (
      <div className="w-80 bg-white border-l-2 border-border p-6">
        <div className="text-center text-gray-400">
          <p className="text-sm font-medium">No Component Selected</p>
          <p className="text-xs mt-2">Click on a component to configure</p>
        </div>
      </div>
    );
  }

  const { schema, config } = node.data;

  const handleConfigChange = (key: string, value: string | number | boolean) => {
    const newConfig: NodeConfig = { ...config, [key]: value };
    dispatch(updateNodeConfig({ nodeId: node.id, config: newConfig }));
  };

  const renderField = (field: ConfigFieldSchema) => {
    const value = config[field.key] ?? field.defaultValue;

    switch (field.type) {
      case 'text':
      case 'textarea':
        return (
          <div key={field.key} className="space-y-1.5">
            <Label htmlFor={field.key} className="text-xs font-semibold text-gray-700">{field.label}</Label>
            <Input
              id={field.key}
              type="text"
              value={String(value)}
              onChange={(e) => handleConfigChange(field.key, e.target.value)}
              placeholder={field.helpText}
              className="text-sm"
            />
            {field.helpText && (
              <p className="text-[10px] text-gray-500">{field.helpText}</p>
            )}
          </div>
        );

      case 'number':
        return (
          <div key={field.key} className="space-y-1.5">
            <Label htmlFor={field.key} className="text-xs font-semibold text-gray-700">{field.label}</Label>
            <Input
              id={field.key}
              type="number"
              value={Number(value)}
              onChange={(e) => handleConfigChange(field.key, parseFloat(e.target.value))}
              min={field.validation?.min}
              max={field.validation?.max}
              step={field.validation?.min !== undefined && field.validation.min < 1 ? 0.1 : 1}
              className="text-sm"
            />
            {field.helpText && (
              <p className="text-[10px] text-gray-500">{field.helpText}</p>
            )}
          </div>
        );

      case 'select':
        return (
          <div key={field.key} className="space-y-1.5">
            <Label htmlFor={field.key} className="text-xs font-semibold text-gray-700">{field.label}</Label>
            <Select
              value={String(value)}
              onValueChange={(newValue) => handleConfigChange(field.key, newValue)}
            >
              <SelectTrigger className="text-sm">
                <SelectValue />
              </SelectTrigger>
              <SelectContent>
                {field.options?.map((option) => (
                  <SelectItem key={String(option.value)} value={String(option.value)}>
                    {option.label}
                  </SelectItem>
                ))}
              </SelectContent>
            </Select>
            {field.helpText && (
              <p className="text-[10px] text-gray-500">{field.helpText}</p>
            )}
          </div>
        );

      case 'toggle':
        return (
          <div key={field.key} className="flex items-center justify-between py-2">
            <div className="space-y-0.5">
              <Label htmlFor={field.key} className="text-xs font-semibold text-gray-700">{field.label}</Label>
              {field.helpText && (
                <p className="text-[10px] text-gray-500">{field.helpText}</p>
              )}
            </div>
            <Switch
              id={field.key}
              checked={Boolean(value)}
              onCheckedChange={(checked) => handleConfigChange(field.key, checked)}
            />
          </div>
        );

      default:
        return null;
    }
  };

  return (
    <div className="w-80 bg-white border-l-2 border-border overflow-y-auto">
      <div className="p-5 space-y-5">
        <div className="pb-3 border-b-2 border-gray-200">
          <h2 className="text-sm font-bold uppercase tracking-wide text-gray-700 mb-1">Component Properties</h2>
          <h3 className="text-base font-bold text-gray-900">{schema.name}</h3>
          <p className="text-xs text-gray-600 mt-1">{schema.description}</p>
          <p className="text-[10px] text-gray-400 mt-1.5 font-mono">ID: {node.id.slice(0, 8)}</p>
        </div>

        <div className="space-y-3">
          <h3 className="text-xs font-bold uppercase tracking-wide text-gray-700">Parameters</h3>
          <div className="space-y-3">
            {schema.configSchema.map(renderField)}
          </div>
        </div>

        {schema.resourceRequirements && (
          <div className="pt-3 border-t-2 border-gray-200">
            <h3 className="text-xs font-bold uppercase tracking-wide text-gray-700 mb-2">System Requirements</h3>
            <div className="space-y-1 text-[11px] text-gray-600 bg-gray-50 p-2.5 rounded border border-gray-200">
              {schema.resourceRequirements.cpu && (
                <div className="flex justify-between">
                  <span className="font-medium">CPU:</span>
                  <span>{schema.resourceRequirements.cpu} cores</span>
                </div>
              )}
              {schema.resourceRequirements.gpu && (
                <div className="flex justify-between">
                  <span className="font-medium">GPU:</span>
                  <span>{schema.resourceRequirements.gpu} units</span>
                </div>
              )}
              {schema.resourceRequirements.memory && (
                <div className="flex justify-between">
                  <span className="font-medium">Memory:</span>
                  <span>{schema.resourceRequirements.memory} MB</span>
                </div>
              )}
            </div>
          </div>
        )}
      </div>
    </div>
  );
};
