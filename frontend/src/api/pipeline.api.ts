import { Pipeline, ApiResponse, CreatePipelineRequest, UpdatePipelineRequest, PipelineStatusUpdate, PipelineStatus } from '@/models';
import { USE_MOCK_API } from './client';
import { mockPipelines, mockExecutionStatus } from './mock/pipelines.mock';
import { v4 as uuidv4 } from 'uuid';

// Mock delay to simulate network latency
const mockDelay = (ms: number = 300) => new Promise((resolve) => setTimeout(resolve, ms));

export const pipelineApi = {
  create: async (data: CreatePipelineRequest): Promise<ApiResponse<Pipeline>> => {
    if (USE_MOCK_API) {
      await mockDelay(400);

      const pipeline: Pipeline = {
        id: uuidv4(),
        name: data.name,
        description: data.description,
        nodes: data.nodes,
        connections: data.connections,
        createdAt: new Date().toISOString(),
        updatedAt: new Date().toISOString(),
        status: PipelineStatus.IDLE,
      };

      mockPipelines.set(pipeline.id, pipeline);

      return {
        success: true,
        data: pipeline,
      };
    }

    // Real API call would go here
    throw new Error('Real API not implemented yet');
  },

  update: async (id: string, data: UpdatePipelineRequest): Promise<ApiResponse<Pipeline>> => {
    if (USE_MOCK_API) {
      await mockDelay(300);

      const pipeline = mockPipelines.get(id);
      if (!pipeline) {
        return {
          success: false,
          error: 'Pipeline not found',
        };
      }

      const updatedPipeline: Pipeline = {
        ...pipeline,
        ...(data.name && { name: data.name }),
        ...(data.description && { description: data.description }),
        ...(data.nodes && { nodes: data.nodes }),
        ...(data.connections && { connections: data.connections }),
        updatedAt: new Date().toISOString(),
      };

      mockPipelines.set(id, updatedPipeline);

      return {
        success: true,
        data: updatedPipeline,
      };
    }

    throw new Error('Real API not implemented yet');
  },

  start: async (id: string): Promise<ApiResponse<void>> => {
    if (USE_MOCK_API) {
      await mockDelay(500);

      mockExecutionStatus.set(id, PipelineStatus.RUNNING);

      const pipeline = mockPipelines.get(id);
      if (pipeline) {
        pipeline.status = PipelineStatus.RUNNING;
        pipeline.updatedAt = new Date().toISOString();
      }

      return {
        success: true,
        message: 'Pipeline started successfully',
      };
    }

    throw new Error('Real API not implemented yet');
  },

  stop: async (id: string): Promise<ApiResponse<void>> => {
    if (USE_MOCK_API) {
      await mockDelay(400);

      mockExecutionStatus.set(id, PipelineStatus.STOPPED);

      const pipeline = mockPipelines.get(id);
      if (pipeline) {
        pipeline.status = PipelineStatus.STOPPED;
        pipeline.updatedAt = new Date().toISOString();
      }

      return {
        success: true,
        message: 'Pipeline stopped successfully',
      };
    }

    throw new Error('Real API not implemented yet');
  },

  getStatus: async (id: string): Promise<ApiResponse<PipelineStatusUpdate>> => {
    if (USE_MOCK_API) {
      await mockDelay(200);

      const status = mockExecutionStatus.get(id) || PipelineStatus.IDLE;

      const statusUpdate: PipelineStatusUpdate = {
        pipelineId: id,
        status,
        ...(status === PipelineStatus.RUNNING && {
          metrics: {
            fps: 25 + Math.random() * 5,
            processedFrames: Math.floor(Date.now() / 100),
            droppedFrames: Math.floor(Math.random() * 5),
            cpuUsage: 40 + Math.random() * 20,
            gpuUsage: 30 + Math.random() * 30,
            memoryUsage: 1024 + Math.random() * 512,
            uptime: Date.now(),
          },
        }),
        timestamp: new Date().toISOString(),
      };

      return {
        success: true,
        data: statusUpdate,
      };
    }

    throw new Error('Real API not implemented yet');
  },
};
