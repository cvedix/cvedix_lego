// Node categories
export enum NodeCategory {
  SOURCE = 'source',
  PROCESSING = 'processing',
  OUTPUT = 'output',
  HIDDEN = 'hidden', // For auto-generated nodes not shown in UI
}

// Specific node types for Cvedix SDK
export enum CvedixNodeType {
  // Visual nodes
  FILE_SOURCE = 'cvedix_file_src_node',
  TRACKER = 'cvedix_tracker_node',
  RTMP_DESTINATION = 'cvedix_rtmp_des_node',

  // Hidden nodes (auto-generated)
  FRAME_DECODER = 'cvedix_frame_decoder_node',
  PREPROCESS = 'cvedix_preprocess_node',
  ANALYTICS = 'cvedix_analytics_node',
}

// Base node configuration
export interface NodeConfig {
  [key: string]: string | number | boolean | object | undefined;
}

// Port definition
export interface NodePort {
  id: string;
  type: 'input' | 'output';
  dataType: string; // 'video', 'detections', 'metadata'
  label: string;
  required: boolean;
}

// Config field schema for dynamic forms
export interface ConfigFieldSchema {
  key: string;
  label: string;
  type: 'text' | 'number' | 'select' | 'toggle' | 'textarea';
  defaultValue: string | number | boolean;
  options?: Array<{ label: string; value: string | number }>;
  validation?: {
    required?: boolean;
    min?: number;
    max?: number;
    pattern?: string;
    custom?: (value:  unknown) => string | null; // Returns error message or null
  };
  helpText?: string;
}

// Node schema (defines node type capabilities)
export interface NodeSchema {
  type: string; // 'face-detection', 'rtsp-camera', etc.
  category: NodeCategory;
  name: string;
  description: string;
  icon: string; // Emoji or icon identifier
  version: string;
  inputs: NodePort[];
  outputs: NodePort[];
  configSchema: ConfigFieldSchema[]; // Defines config UI
  defaultConfig: NodeConfig;
  resourceRequirements?: {
    cpu?: number;
    gpu?: number;
    memory?: number;
  };
}

// Node instance (placed on canvas)
export interface NodeInstance {
  id: string; // Unique instance ID
  type: string; // References NodeSchema.type
  category: NodeCategory;
  position: { x: number; y: number };
  data: {
    label: string;
    config: NodeConfig;
    schema: NodeSchema;
  };
  isHidden?: boolean; // Flag for auto-generated hidden nodes
}

// Source node specific config
export interface FileSourceConfig extends NodeConfig {
  node_name: string;
  channel_index: number;
  video_name: string;
  resize_ratio: number;
  cycle: boolean;
  gst_decoder_name: string;
  skip_interval: number;
}

// RTMP destination config
export interface RtmpDestinationConfig extends NodeConfig {
  node_name: string;
  channel_index: number;
  rtmp_url: string;
  resolution_width: number;
  resolution_height: number;
  bitrate: number;
  osd: boolean;
  gst_encoder_name: string;
}
