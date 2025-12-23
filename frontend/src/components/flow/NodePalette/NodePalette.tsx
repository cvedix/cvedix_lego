import React, { DragEvent } from 'react';
import { useNodeRegistry } from '@/hooks/useNodeRegistry';
import { NodeCategory } from '@/models';
import { cn } from '@/lib/utils';
import { NODE_COLORS } from '@/utils/constants';

export const NodePalette: React.FC = () => {
  const { nodeSchemas, isLoading } = useNodeRegistry();

  const onDragStart = (event: DragEvent, nodeType: string) => {
    event.dataTransfer.setData('application/reactflow', nodeType);
    event.dataTransfer.effectAllowed = 'move';
  };

  // Filter out hidden nodes and group by category
  const groupedNodes = nodeSchemas
    .filter((schema) => schema.category !== NodeCategory.HIDDEN)
    .reduce((acc, schema) => {
      if (!acc[schema.category]) {
        acc[schema.category] = [];
      }
      acc[schema.category].push(schema);
      return acc;
    }, {} as Record<NodeCategory, typeof nodeSchemas>);

  const categoryLabels = {
    [NodeCategory.SOURCE]: 'Source Nodes',
    [NodeCategory.PROCESSING]: 'Processing Nodes',
    [NodeCategory.OUTPUT]: 'Output Nodes',
    [NodeCategory.HIDDEN]: 'Hidden Nodes',
  };

  if (isLoading) {
    return (
      <div className="w-64 bg-white border-r-2 border-border p-4">
        <div className="text-sm text-muted-foreground">Loading nodes...</div>
      </div>
    );
  }

  return (
    <div className="w-64 bg-white border-r-2 border-border overflow-y-auto">
      <div className="p-4">
        <h2 className="text-sm font-bold uppercase tracking-wide text-gray-700 mb-4 pb-2 border-b-2 border-gray-200">
          Component Palette
        </h2>

        {Object.entries(groupedNodes).map(([category, schemas]) => {
          const categoryColors = NODE_COLORS[category as NodeCategory];

          return (
            <div key={category} className="mb-4">
              <h3 className={cn('text-xs font-bold uppercase tracking-wide mb-2 px-1', categoryColors.text)}>
                {categoryLabels[category as NodeCategory]}
              </h3>

              <div className="space-y-1.5">
                {schemas.map((schema) => (
                  <div
                    key={schema.type}
                    draggable
                    onDragStart={(e) => onDragStart(e, schema.type)}
                    className={cn(
                      'px-2.5 py-2 rounded border-2 cursor-move transition-all hover:shadow-sm bg-white',
                      categoryColors.border,
                      'hover:bg-gray-50'
                    )}
                  >
                    <div className="flex items-start gap-2">
                      <div className="flex-1 min-w-0">
                        <div className={cn('font-semibold text-xs', categoryColors.text)}>
                          {schema.name}
                        </div>
                        <div className="text-[10px] text-gray-500 truncate mt-0.5">
                          {schema.description}
                        </div>
                      </div>
                    </div>
                  </div>
                ))}
              </div>
            </div>
          );
        })}
      </div>
    </div>
  );
};
