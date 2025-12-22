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

export interface PipelineStartResponse {
  success: boolean;
  message: string;
  pipeline_id?: string;
}

export interface PipelineStopResponse {
  success: boolean;
  message: string;
}

export const pipelineApi = {
  /**
   * Start pipeline execution
   * POST /lego/startpipeline
   */
  start: async (pipelineJson: BackendPipelineRequest): Promise<ApiResponse<PipelineStartResponse>> => {
    try {
      const response = await apiClient.post<PipelineStartResponse>(
        '/lego/startpipeline',
        pipelineJson
      );

      return {
        success: true,
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
   */
  stop: async (): Promise<ApiResponse<PipelineStopResponse>> => {
    try {
      const response = await apiClient.post<PipelineStopResponse>('/lego/stoppipeline');

      return {
        success: true,
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
