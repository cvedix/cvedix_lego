import { NodeSchema, ApiResponse } from '@/models';
import { USE_MOCK_API } from './client';
import { mockNodeSchemas } from './mock/nodes.mock';

// Mock delay to simulate network latency
const mockDelay = (ms: number = 300) => new Promise((resolve) => setTimeout(resolve, ms));

export const nodesApi = {
  getNodeSchemas: async (): Promise<ApiResponse<NodeSchema[]>> => {
    if (USE_MOCK_API) {
      await mockDelay(400);
      return {
        success: true,
        data: mockNodeSchemas,
      };
    }

    // Real API call would go here
    // const response = await apiClient.get<ApiResponse<NodeSchema[]>>('/api/nodes');
    // return response.data;

    throw new Error('Real API not implemented yet');
  },
};
