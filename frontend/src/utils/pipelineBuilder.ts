import { NodeInstance, CvedixNodeType } from '@/models';
import { BackendPipelineRequest, BackendNodeConfig } from '@/api/pipeline.api';
import { hiddenNodeTemplates } from '@/api/mock/nodes.mock';

/**
 * Build complete pipeline JSON for backend
 * Includes visible nodes + auto-generated hidden nodes in correct order
 */
export const buildBackendPipeline = (nodes: NodeInstance[]): BackendPipelineRequest => {
  const backendNodes: BackendNodeConfig[] = [];

  // Find visible nodes
  const sourceNode = nodes.find((n) => n.type === CvedixNodeType.FILE_SOURCE);
  const trackerNode = nodes.find((n) => n.type === CvedixNodeType.TRACKER);
  const destinationNode = nodes.find((n) => n.type === CvedixNodeType.RTMP_DESTINATION);

  // Build pipeline in correct order
  if (sourceNode) {
    // 1. File source node
    backendNodes.push({
      type: sourceNode.type,
      config: sourceNode.data.config,
    });

    // 2. Frame decoder (hidden)
    backendNodes.push(hiddenNodeTemplates[CvedixNodeType.FRAME_DECODER]);

    // 3. Preprocess (hidden)
    backendNodes.push(hiddenNodeTemplates[CvedixNodeType.PREPROCESS]);
  }

  if (trackerNode) {
    // 4. Tracker node
    backendNodes.push({
      type: trackerNode.type,
      config: {
        ...trackerNode.data.config,
        tracker_type: 'sort',
        max_lost: 30,
        iou_threshold: 0.3,
      },
    });

    // 5. Analytics (hidden)
    backendNodes.push(hiddenNodeTemplates[CvedixNodeType.ANALYTICS]);
  }

  if (destinationNode) {
    // 6. RTMP destination node
    backendNodes.push({
      type: destinationNode.type,
      config: destinationNode.data.config,
    });
  }

  return {
    nodes: backendNodes,
  };
};

/**
 * Validate that pipeline has required nodes
 */
export const validatePipeline = (nodes: NodeInstance[]): { valid: boolean; error?: string } => {
  const hasSource = nodes.some((n) => n.type === CvedixNodeType.FILE_SOURCE);
  const hasTracker = nodes.some((n) => n.type === CvedixNodeType.TRACKER);
  const hasDestination = nodes.some((n) => n.type === CvedixNodeType.RTMP_DESTINATION);

  if (!hasSource) {
    return { valid: false, error: 'Pipeline must have a Video Source node' };
  }

  if (!hasDestination) {
    return { valid: false, error: 'Pipeline must have an RTMP Stream node' };
  }

  // Tracker is optional but recommended
  if (!hasTracker) {
    console.warn('Pipeline has no tracker node');
  }

  // Check source node has video selected
  const sourceNode = nodes.find((n) => n.type === CvedixNodeType.FILE_SOURCE);
  if (sourceNode && !sourceNode.data.config.video_name) {
    return { valid: false, error: 'Video Source node must have a video selected' };
  }

  return { valid: true };
};

/**
 * Auto-generate connections for visual representation
 * Returns array of connection objects for ReactFlow
 */
export const generateAutoConnections = (nodes: NodeInstance[]) => {
  const connections = [];

  const sourceNode = nodes.find((n) => n.type === CvedixNodeType.FILE_SOURCE);
  const trackerNode = nodes.find((n) => n.type === CvedixNodeType.TRACKER);
  const destinationNode = nodes.find((n) => n.type === CvedixNodeType.RTMP_DESTINATION);

  // Source -> Tracker
  if (sourceNode && trackerNode) {
    connections.push({
      id: `${sourceNode.id}-${trackerNode.id}`,
      source: sourceNode.id,
      target: trackerNode.id,
      animated: true,
    });
  }

  // Tracker -> Destination
  if (trackerNode && destinationNode) {
    connections.push({
      id: `${trackerNode.id}-${destinationNode.id}`,
      source: trackerNode.id,
      target: destinationNode.id,
      animated: true,
    });
  }

  // Source -> Destination (if no tracker)
  if (sourceNode && destinationNode && !trackerNode) {
    connections.push({
      id: `${sourceNode.id}-${destinationNode.id}`,
      source: sourceNode.id,
      target: destinationNode.id,
      animated: true,
    });
  }

  return connections;
};
