import { NodeInstance } from './node.types';
import { Connection } from './connection.types';

export enum PipelineStatus {
  IDLE = 'idle',
  STARTING = 'starting',
  RUNNING = 'running',
  PAUSED = 'paused',
  STOPPING = 'stopping',
  STOPPED = 'stopped',
  ERROR = 'error',
}

export interface Pipeline {
  id: string;
  name: string;
  description?: string;
  nodes: NodeInstance[];
  connections: Connection[];
  createdAt: string;
  updatedAt: string;
  status: PipelineStatus;
  metadata?: {
    tags?: string[];
    author?: string;
    version?: string;
  };
}

export interface PipelineExecutionMetrics {
  fps: number;
  processedFrames: number;
  droppedFrames: number;
  cpuUsage: number;
  gpuUsage: number;
  memoryUsage: number;
  uptime: number;
}

export interface PipelineStatusUpdate {
  pipelineId: string;
  status: PipelineStatus;
  metrics?: PipelineExecutionMetrics;
  nodeStatuses?: Record<string, NodeExecutionStatus>;
  error?: string;
  timestamp: string;
}

export interface NodeExecutionStatus {
  nodeId: string;
  status: 'idle' | 'processing' | 'error';
  processedCount: number;
  errorCount: number;
  lastError?: string;
}
