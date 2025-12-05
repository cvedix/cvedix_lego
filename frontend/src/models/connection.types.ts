export interface Connection {
  id: string;
  source: string; // Source node ID
  target: string; // Target node ID
  sourceHandle?: string; // Output port ID (ReactFlow)
  targetHandle?: string; // Input port ID (ReactFlow)
  type?: string; // Connection type for styling
  animated?: boolean;
  data?: {
    dataType: string; // 'video', 'detections', etc.
    label?: string;
  };
}

export interface ConnectionValidation {
  valid: boolean;
  error?: string;
}
