import { useCallback } from 'react';
import { useNodeSchemas } from '@/service/node.service';
import { NodeSchema, NodeInstance, NodeCategory } from '@/models';
import { v4 as uuidv4 } from 'uuid';

export const useNodeRegistry = () => {
  const { data: nodeSchemas, isLoading, error } = useNodeSchemas();

  const getNodeSchema = useCallback(
    (type: string): NodeSchema | undefined => {
      return nodeSchemas?.find((schema) => schema.type === type);
    },
    [nodeSchemas]
  );

  const createNodeInstance = useCallback(
    (type: string, position: { x: number; y: number }): NodeInstance | null => {
      const schema = getNodeSchema(type);
      if (!schema) {
        console.error(`Unknown node type: ${type}`);
        return null;
      }

      const nodeInstance: NodeInstance = {
        id: `${type}-${uuidv4().slice(0, 8)}`,
        type,
        category: schema.category,
        position,
        data: {
          label: schema.name,
          schema,
          config: { ...schema.defaultConfig },
        },
      };

      return nodeInstance;
    },
    [getNodeSchema]
  );

  const getNodesByCategory = useCallback(
    (category: NodeCategory): NodeSchema[] => {
      return nodeSchemas?.filter((schema) => schema.category === category) || [];
    },
    [nodeSchemas]
  );

  return {
    nodeSchemas: nodeSchemas || [],
    isLoading,
    error,
    getNodeSchema,
    createNodeInstance,
    getNodesByCategory,
  };
};
