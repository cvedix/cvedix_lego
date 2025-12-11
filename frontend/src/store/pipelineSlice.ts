import { createSlice, PayloadAction } from '@reduxjs/toolkit';
import { Pipeline, PipelineStatus, PipelineExecutionMetrics, NodeInstance, Connection, NodeConfig } from '@/models';
import { v4 as uuidv4 } from 'uuid';

interface PipelineState {
  pipeline: Pipeline;
  isLoading: boolean;
  error: string | null;
}

const createEmptyPipeline = (): Pipeline => ({
  id: uuidv4(),
  name: 'Untitled Pipeline',
  description: '',
  nodes: [],
  connections: [],
  createdAt: new Date().toISOString(),
  updatedAt: new Date().toISOString(),
  status: PipelineStatus.IDLE,
});

const initialState: PipelineState = {
  pipeline: createEmptyPipeline(),
  isLoading: false,
  error: null,
};

const pipelineSlice = createSlice({
  name: 'pipeline',
  initialState,
  reducers: {
    // Node management
    addNode: (state, action: PayloadAction<NodeInstance>) => {
      state.pipeline.nodes.push(action.payload);
      state.pipeline.updatedAt = new Date().toISOString();
    },

    removeNode: (state, action: PayloadAction<string>) => {
      const nodeId = action.payload;
      state.pipeline.nodes = state.pipeline.nodes.filter((n) => n.id !== nodeId);
      // Also remove connections involving this node
      state.pipeline.connections = state.pipeline.connections.filter(
        (c) => c.source !== nodeId && c.target !== nodeId
      );
      state.pipeline.updatedAt = new Date().toISOString();
    },

    updateNodeConfig: (state, action: PayloadAction<{ nodeId: string; config: NodeConfig }>) => {
      const { nodeId, config } = action.payload;
      const node = state.pipeline.nodes.find((n) => n.id === nodeId);
      if (node) {
        node.data.config = config;
        state.pipeline.updatedAt = new Date().toISOString();
      }
    },

    updateNodePosition: (state, action: PayloadAction<{ nodeId: string; position: { x: number; y: number } }>) => {
      const { nodeId, position } = action.payload;
      const node = state.pipeline.nodes.find((n) => n.id === nodeId);
      if (node) {
        node.position = position;
        state.pipeline.updatedAt = new Date().toISOString();
      }
    },

    // Connection management
    addConnection: (state, action: PayloadAction<Connection>) => {
      state.pipeline.connections.push(action.payload);
      state.pipeline.updatedAt = new Date().toISOString();
    },

    removeConnection: (state, action: PayloadAction<string>) => {
      state.pipeline.connections = state.pipeline.connections.filter((c) => c.id !== action.payload);
      state.pipeline.updatedAt = new Date().toISOString();
    },

    // Pipeline management
    setPipelineStatus: (state, action: PayloadAction<PipelineStatus>) => {
      state.pipeline.status = action.payload;
      state.pipeline.updatedAt = new Date().toISOString();
    },

    updatePipelineMetrics: (state, action: PayloadAction<PipelineExecutionMetrics>) => {
      // Store metrics in metadata for now
      if (!state.pipeline.metadata) {
        state.pipeline.metadata = {};
      }
      (state.pipeline.metadata as  Record<string, unknown>).metrics = action.payload;
    },

    loadPipeline: (state, action: PayloadAction<Pipeline>) => {
      state.pipeline = action.payload;
    },

    resetPipeline: (state) => {
      state.pipeline = createEmptyPipeline();
    },

    updatePipelineName: (state, action: PayloadAction<string>) => {
      state.pipeline.name = action.payload;
      state.pipeline.updatedAt = new Date().toISOString();
    },

    // Loading and error states
    setLoading: (state, action: PayloadAction<boolean>) => {
      state.isLoading = action.payload;
    },

    setError: (state, action: PayloadAction<string | null>) => {
      state.error = action.payload;
    },
  },
});

export const {
  addNode,
  removeNode,
  updateNodeConfig,
  updateNodePosition,
  addConnection,
  removeConnection,
  setPipelineStatus,
  updatePipelineMetrics,
  loadPipeline,
  resetPipeline,
  updatePipelineName,
  setLoading,
  setError,
} = pipelineSlice.actions;

export default pipelineSlice.reducer;
