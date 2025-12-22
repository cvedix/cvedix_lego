import { NodeSchema, ApiResponse } from '@/models';
import { mockNodeSchemas } from './mock/nodes.mock';

// Mock delay to simulate network latency
const mockDelay = (ms: number = 300) => new Promise((resolve) => setTimeout(resolve, ms));

export const nodesApi = {
  getNodeSchemas: async (): Promise<ApiResponse<NodeSchema[]>> => {
    // Node schemas define the UI palette and are stored locally
    await mockDelay(400);
    return {
      success: true,
      data: mockNodeSchemas,
    };
  },
};
