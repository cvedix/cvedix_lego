import { useQuery } from '@tanstack/react-query';
import { nodesApi } from '@/api';

export const useNodeSchemas = () => {
  return useQuery({
    queryKey: ['node-schemas'],
    queryFn: async () => {
      const response = await nodesApi.getNodeSchemas();
      if (!response.success || !response.data) {
        throw new Error(response.error || 'Failed to fetch node schemas');
      }
      return response.data;
    },
    staleTime: Infinity, // Node schemas rarely change
  });
};
