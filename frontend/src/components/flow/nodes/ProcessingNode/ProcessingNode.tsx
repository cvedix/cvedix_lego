import React from 'react';
import { NodeProps } from 'reactflow';
import { BaseNode } from '../BaseNode/BaseNode';

export const ProcessingNode: React.FC<NodeProps> = (props) => {
  return <BaseNode {...props} />;
};
