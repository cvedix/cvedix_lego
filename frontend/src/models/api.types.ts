import { Pipeline } from './pipeline.types';
import { NodeInstance } from './node.types';
import { Connection } from './connection.types';

export interface ApiResponse<T> {
  success: boolean;
  data?: T;
  error?: string;
  message?: string;
}

export interface PaginatedResponse<T> {
  items: T[];
  total: number;
  page: number;
  pageSize: number;
}

// API request payloads
export interface CreatePipelineRequest {
  name: string;
  description?: string;
  nodes: NodeInstance[];
  connections: Connection[];
}

export interface UpdatePipelineRequest {
  name?: string;
  description?: string;
  nodes?: NodeInstance[];
  connections?: Connection[];
}

// Export type for full pipeline
export type PipelineResponse = ApiResponse<Pipeline>;
