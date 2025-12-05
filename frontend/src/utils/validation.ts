import { NodeInstance, Connection, ConnectionValidation } from '@/models';

// Build adjacency list from connections
const buildAdjacencyList = (connections: Connection[]): Record<string, string[]> => {
  const adjacency: Record<string, string[]> = {};

  connections.forEach((conn) => {
    if (!adjacency[conn.source]) {
      adjacency[conn.source] = [];
    }
    adjacency[conn.source].push(conn.target);
  });

  return adjacency;
};

// Detect cycles using DFS
const wouldCreateCycle = (newConnection: Connection, existingConnections: Connection[]): boolean => {
  const allConnections = [...existingConnections, newConnection];
  const adjacency = buildAdjacencyList(allConnections);

  const visited = new Set<string>();
  const recStack = new Set<string>();

  const hasCycle = (nodeId: string): boolean => {
    if (recStack.has(nodeId)) return true; // Cycle detected
    if (visited.has(nodeId)) return false;

    visited.add(nodeId);
    recStack.add(nodeId);

    const neighbors = adjacency[nodeId] || [];
    for (const neighbor of neighbors) {
      if (hasCycle(neighbor)) return true;
    }

    recStack.delete(nodeId);
    return false;
  };

  // Check all nodes
  const allNodes = new Set([...Object.keys(adjacency), ...Object.values(adjacency).flat()]);
  for (const nodeId of allNodes) {
    if (hasCycle(nodeId)) return true;
  }

  return false;
};

// Validate connection before adding
export const validateConnection = (
  connection: Connection,
  nodes: NodeInstance[],
  existingConnections: Connection[]
): ConnectionValidation => {
  const sourceNode = nodes.find((n) => n.id === connection.source);
  const targetNode = nodes.find((n) => n.id === connection.target);

  if (!sourceNode || !targetNode) {
    return { valid: false, error: 'Invalid nodes' };
  }

  // Check if connection would create a cycle (DAG validation)
  if (wouldCreateCycle(connection, existingConnections)) {
    return { valid: false, error: 'Connection would create a cycle' };
  }

  // Validate data type compatibility
  const sourcePort = sourceNode.data.schema.outputs.find((p) => p.id === connection.sourceHandle);
  const targetPort = targetNode.data.schema.inputs.find((p) => p.id === connection.targetHandle);

  if (sourcePort && targetPort) {
    if (sourcePort.dataType !== targetPort.dataType) {
      return {
        valid: false,
        error: `Incompatible data types: ${sourcePort.dataType} → ${targetPort.dataType}`,
      };
    }
  }

  // Check for duplicate connections
  const isDuplicate = existingConnections.some(
    (c) =>
      c.source === connection.source &&
      c.target === connection.target &&
      c.sourceHandle === connection.sourceHandle &&
      c.targetHandle === connection.targetHandle
  );

  if (isDuplicate) {
    return { valid: false, error: 'Connection already exists' };
  }

  return { valid: true };
};

// Validate entire pipeline
export const validatePipeline = (nodes: NodeInstance[], connections: Connection[]): string[] => {
  const errors: string[] = [];

  // Check if pipeline is empty
  if (nodes.length === 0) {
    errors.push('Pipeline is empty');
    return errors;
  }

  // Check for disconnected required inputs
  nodes.forEach((node) => {
    const requiredInputs = node.data.schema.inputs.filter((input) => input.required);

    requiredInputs.forEach((input) => {
      const hasConnection = connections.some(
        (conn) => conn.target === node.id && conn.targetHandle === input.id
      );

      if (!hasConnection) {
        errors.push(`Node "${node.data.label}" is missing required input: ${input.label}`);
      }
    });
  });

  // Check for cycles
  const adjacency = buildAdjacencyList(connections);
  const visited = new Set<string>();
  const recStack = new Set<string>();

  const hasCycle = (nodeId: string): boolean => {
    if (recStack.has(nodeId)) return true;
    if (visited.has(nodeId)) return false;

    visited.add(nodeId);
    recStack.add(nodeId);

    const neighbors = adjacency[nodeId] || [];
    for (const neighbor of neighbors) {
      if (hasCycle(neighbor)) return true;
    }

    recStack.delete(nodeId);
    return false;
  };

  for (const nodeId of Object.keys(adjacency)) {
    if (hasCycle(nodeId)) {
      errors.push('Pipeline contains cycles');
      break;
    }
  }

  return errors;
};

// Topological sort for execution order
export const topologicalSort = (nodes: NodeInstance[], connections: Connection[]): string[] => {
  const adjacency = buildAdjacencyList(connections);
  const inDegree: Record<string, number> = {};

  // Calculate in-degrees
  nodes.forEach((node) => {
    inDegree[node.id] = 0;
  });

  connections.forEach((conn) => {
    inDegree[conn.target] = (inDegree[conn.target] || 0) + 1;
  });

  // Queue of nodes with no incoming edges
  const queue: string[] = [];
  Object.entries(inDegree).forEach(([nodeId, degree]) => {
    if (degree === 0) queue.push(nodeId);
  });

  const sorted: string[] = [];

  while (queue.length > 0) {
    const nodeId = queue.shift()!;
    sorted.push(nodeId);

    const neighbors = adjacency[nodeId] || [];
    neighbors.forEach((neighbor) => {
      inDegree[neighbor]--;
      if (inDegree[neighbor] === 0) {
        queue.push(neighbor);
      }
    });
  }

  // If sorted length < nodes length, there's a cycle
  if (sorted.length !== nodes.length) {
    throw new Error('Pipeline contains cycles');
  }

  return sorted;
};
