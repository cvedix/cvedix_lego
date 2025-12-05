import { Pipeline, PipelineStatus } from '@/models';

// In-memory storage for mock pipelines during session
export const mockPipelines: Map<string, Pipeline> = new Map();

// Mock execution status
export const mockExecutionStatus: Map<string, PipelineStatus> = new Map();
