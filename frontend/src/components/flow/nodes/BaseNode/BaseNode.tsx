import React from 'react';
import { Handle, Position, NodeProps } from 'reactflow';
import { NodeInstance } from '@/models';
import { cn } from '@/lib/utils';
import { NODE_COLORS } from '@/utils/constants';
import { Trash2, Settings } from 'lucide-react';
import { useAppDispatch } from '@/store';
import { removeNode, selectNode } from '@/store';

interface BaseNodeProps extends NodeProps {
  data: NodeInstance['data'];
}

export const BaseNode: React.FC<BaseNodeProps> = ({ id, data, selected }) => {
  const dispatch = useAppDispatch();
  const { schema, config, label } = data;

  const categoryColors = NODE_COLORS[schema.category as keyof typeof NODE_COLORS];

  const handleConfigure = (e: React.MouseEvent) => {
    e.stopPropagation();
    dispatch(selectNode(id));
  };

  const handleDelete = (e: React.MouseEvent) => {
    e.stopPropagation();
    dispatch(removeNode(id));
  };

  return (
    <div
      className={cn(
        'min-w-[200px] rounded border-2 bg-white shadow-md transition-all',
        selected ? 'ring-2 ring-primary ring-offset-1' : '',
        categoryColors.border
      )}
    >
      {/* Header - Industrial accent bar */}
      <div className={cn('flex items-center justify-between px-3 py-1.5 border-b-2', categoryColors.accent, categoryColors.border)}>
        <div className="flex items-center gap-2 flex-1 min-w-0">
          <div className="flex-1 min-w-0">
            <div className="font-semibold text-sm text-white truncate">{label}</div>
            <div className="text-[10px] text-white/80 uppercase tracking-wide">{schema.type}</div>
          </div>
        </div>
        <div className="flex gap-0.5">
          <button
            onClick={handleConfigure}
            className="p-1 hover:bg-white/20 rounded-sm transition-colors"
            title="Configure"
          >
            <Settings className="w-3.5 h-3.5 text-white" />
          </button>
          <button
            onClick={handleDelete}
            className="p-1 hover:bg-white/20 rounded-sm transition-colors"
            title="Delete"
          >
            <Trash2 className="w-3.5 h-3.5 text-white" />
          </button>
        </div>
      </div>

      {/* Input Ports - Mechanical connectors */}
      {schema.inputs.map((port, index) => (
        <Handle
          key={port.id}
          type="target"
          position={Position.Left}
          id={port.id}
          style={{
            top: `${((index + 1) / (schema.inputs.length + 1)) * 100}%`,
            width: '12px',
            height: '12px',
            borderRadius: '2px',
          }}
          className="!bg-white border-2 !border-gray-400 hover:!border-primary hover:!bg-blue-50 transition-colors"
        />
      ))}

      {/* Body - Technical parameter display */}
      <div className="px-3 py-2 space-y-0.5 bg-gray-50/50">
        {Object.entries(config)
          .slice(0, 2)
          .map(([key, value]) => (
            <div key={key} className="flex justify-between text-[11px] gap-2">
              <span className="text-gray-600 font-medium truncate">{key}</span>
              <span className="font-mono text-gray-800 truncate">{String(value)}</span>
            </div>
          ))}
        {Object.keys(config).length > 2 && (
          <div className="text-[10px] text-gray-500 text-center pt-0.5">
            +{Object.keys(config).length - 2} parameters
          </div>
        )}
        {Object.keys(config).length === 0 && (
          <div className="text-[10px] text-gray-400 text-center py-1">
            No configuration
          </div>
        )}
      </div>

      {/* Output Ports - Mechanical connectors */}
      {schema.outputs.map((port, index) => (
        <Handle
          key={port.id}
          type="source"
          position={Position.Right}
          id={port.id}
          style={{
            top: `${((index + 1) / (schema.outputs.length + 1)) * 100}%`,
            width: '12px',
            height: '12px',
            borderRadius: '2px',
          }}
          className="!bg-white border-2 !border-gray-400 hover:!border-accent hover:!bg-cyan-50 transition-colors"
        />
      ))}
    </div>
  );
};
