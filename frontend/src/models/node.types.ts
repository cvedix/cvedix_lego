// Node categories
export enum NodeCategory {
  SOURCE = 'source',
  PROCESSING = 'processing',
  OUTPUT = 'output',
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
}
