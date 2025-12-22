import React, { useCallback, useRef, DragEvent as ReactDragEvent } from 'react';
import ReactFlow, {
  Background,
  Controls,
  MiniMap,
  Node,
  Edge,
  Connection,
  NodeTypes,
  ReactFlowInstance,
  BackgroundVariant,
  NodeChange,
  EdgeChange,
} from 'reactflow';
import { useAppDispatch, useAppSelector } from '@/store';
import { addNode, addConnection, removeConnection, updateNodePosition, selectNode, openVideoSelectionModal } from '@/store';
import { SourceNode } from '../nodes/SourceNode/SourceNode';
import { ProcessingNode } from '../nodes/ProcessingNode/ProcessingNode';
import { OutputNode } from '../nodes/OutputNode/OutputNode';
import { useNodeRegistry } from '@/hooks/useNodeRegistry';
import { validateConnection } from '@/utils/validation';
import { generateAutoConnections } from '@/utils/pipelineBuilder';
import { CvedixNodeType } from '@/models';
import { v4 as uuidv4 } from 'uuid';

const nodeTypes: NodeTypes = {
  source: SourceNode,
  processing: ProcessingNode,
  output: OutputNode,
};

export const FlowCanvas: React.FC = () => {
  const dispatch = useAppDispatch();
  const pipeline = useAppSelector((state) => state.pipeline.pipeline);
  const { createNodeInstance } = useNodeRegistry();
  const reactFlowWrapper = useRef<HTMLDivElement>(null);
  const [reactFlowInstance, setReactFlowInstance] = React.useState<ReactFlowInstance | null>(null);

  // Convert NodeInstance to ReactFlow Node
  const nodes: Node[] = pipeline.nodes.map((node) => ({
    id: node.id,
    type: node.category,
    position: node.position,
    data: node.data,
  }));

  // Convert Connection to ReactFlow Edge
  const edges: Edge[] = pipeline.connections.map((conn) => ({
    id: conn.id,
    source: conn.source,
    target: conn.target,
    sourceHandle: conn.sourceHandle,
    targetHandle: conn.targetHandle,
    animated: conn.animated || false,
    type: 'smoothstep',
  }));

  const onNodesChange = useCallback(
    (changes: NodeChange[]) => {
      // Handle node position updates
      changes.forEach((change) => {
        if (change.type === 'position' && 'position' in change && change.position) {
          dispatch(updateNodePosition({ nodeId: change.id, position: change.position }));
        }
      });
    },
    [dispatch]
  );

  const onEdgesChange = useCallback(
    (changes: EdgeChange[]) => {
      // Handle edge removal
      changes.forEach((change) => {
        if (change.type === 'remove') {
          dispatch(removeConnection(change.id));
        }
      });
    },
    [dispatch]
  );

  const onConnect = useCallback(
    (connection: Connection) => {
      const newConnection = {
        id: `edge-${uuidv4().slice(0, 8)}`,
        source: connection.source!,
        target: connection.target!,
        sourceHandle: connection.sourceHandle || undefined,
        targetHandle: connection.targetHandle || undefined,
      };

      // Validate connection
      const validation = validateConnection(newConnection, pipeline.nodes, pipeline.connections);

      if (validation.valid) {
        dispatch(addConnection(newConnection));
      } else {
        console.error('Invalid connection:', validation.error);
        alert(`Cannot connect: ${validation.error}`);
      }
    },
    [pipeline.nodes, pipeline.connections, dispatch]
  );

  const onDragOver = useCallback((event: ReactDragEvent<HTMLDivElement>) => {
    event.preventDefault();
    event.dataTransfer.dropEffect = 'move';
  }, []);

  const onDrop = useCallback(
    (event: ReactDragEvent<HTMLDivElement>) => {
      event.preventDefault();

      if (!reactFlowInstance || !reactFlowWrapper.current) return;

      const nodeType = event.dataTransfer.getData('application/reactflow');
      if (!nodeType) return;

      const reactFlowBounds = reactFlowWrapper.current.getBoundingClientRect();
      const position = reactFlowInstance.project({
        x: event.clientX - reactFlowBounds.left,
        y: event.clientY - reactFlowBounds.top,
      });

      const newNode = createNodeInstance(nodeType, position);
      if (newNode) {
        dispatch(addNode(newNode));

        // Auto-generate connections after adding node
        setTimeout(() => {
          const updatedNodes = [...pipeline.nodes, newNode];
          const autoConnections = generateAutoConnections(updatedNodes);

          // Clear existing connections and add new ones
          pipeline.connections.forEach((conn) => {
            dispatch(removeConnection(conn.id));
          });
          autoConnections.forEach((conn) => {
            dispatch(addConnection(conn));
          });
        }, 100);

        // Open video selection modal for source nodes
        if (nodeType === CvedixNodeType.FILE_SOURCE) {
          dispatch(openVideoSelectionModal(newNode.id));
        }
      }
    },
    [reactFlowInstance, createNodeInstance, dispatch, pipeline.nodes, pipeline.connections]
  );

  const onNodeClick = useCallback(
    (_event: React.MouseEvent, node: Node) => {
      dispatch(selectNode(node.id));
    },
    [dispatch]
  );

  const onPaneClick = useCallback(() => {
    dispatch(selectNode(null));
  }, [dispatch]);

  return (
    <div ref={reactFlowWrapper} className="w-full h-full">
      <ReactFlow
        nodes={nodes}
        edges={edges}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        onConnect={onConnect}
        onInit={setReactFlowInstance}
        onDrop={onDrop}
        onDragOver={onDragOver}
        onNodeClick={onNodeClick}
        onPaneClick={onPaneClick}
        nodeTypes={nodeTypes}
        fitView
        className="bg-background"
      >
        <Background variant={BackgroundVariant.Dots} gap={16} size={1} color="#e0e7ff" />
        <Controls />
        <MiniMap
          nodeColor={(node) => {
            switch (node.type) {
              case 'source':
                return '#3b82f6';
              case 'processing':
                return '#6366f1';
              case 'output':
                return '#06b6d4';
              default:
                return '#9ca3af';
            }
          }}
          maskColor="#f8fafc"
        />
      </ReactFlow>
    </div>
  );
};
