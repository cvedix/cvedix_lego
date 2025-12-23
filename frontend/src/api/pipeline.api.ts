import { apiClient } from './client';
import { ApiResponse } from '@/models';

// Backend pipeline JSON structure
export interface BackendNodeConfig {
  type: string;
  config: Record<string, any>;
}

export interface BackendPipelineRequest {
  nodes: BackendNodeConfig[];
}

// Backend response structure for POST /lego/startpipeline
// Returns: {"status": "started"}
export interface PipelineStartResponse {
  status: string;
}

// Backend response structure for POST /lego/stoppipeline
// Returns: {"status": "stopped"} or {"status": "not running"}
export interface PipelineStopResponse {
  status: string;
}

export const pipelineApi = {
  /**
   * Start pipeline execution
   * POST /lego/startpipeline
   * Backend returns: {"status": "started"}
   */
  start: async (pipelineJson: BackendPipelineRequest): Promise<ApiResponse<PipelineStartResponse>> => {
    try {
      const response = await apiClient.post<PipelineStartResponse>(
        '/lego/startpipeline',
        pipelineJson
      );

      return {
        success: response.data.status === 'started',
        data: response.data,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Failed to start pipeline',
      };
    }
  },

  /**
   * Stop pipeline execution
   * POST /lego/stoppipeline
   * Backend returns: {"status": "stopped"} or {"status": "not running"}
   */
  stop: async (): Promise<ApiResponse<PipelineStopResponse>> => {
    try {
      const response = await apiClient.post<PipelineStopResponse>('/lego/stoppipeline');

      return {
        success: response.data.status === 'stopped' || response.data.status === 'not running',
        data: response.data,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Failed to stop pipeline',
      };
    }
  },
};
