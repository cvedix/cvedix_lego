import React from 'react';
import { Toolbar } from '@/components/flow/Toolbar/Toolbar';
import { NodePalette } from '@/components/flow/NodePalette/NodePalette';
import { FlowCanvas } from '@/components/flow/FlowCanvas/FlowCanvas';
import { ConfigPanel } from '@/components/flow/ConfigPanel/ConfigPanel';

export const HomePage: React.FC = () => {
  return (
    <div className="h-screen flex flex-col">
      {/* Toolbar */}
      <Toolbar />

      {/* Main content area with three panels */}
      <div className="flex-1 flex overflow-hidden">
        {/* Left sidebar - Node Palette */}
        <NodePalette />

        {/* Center - Flow Canvas */}
        <div className="flex-1 relative">
          <FlowCanvas />
        </div>

        {/* Right sidebar - Config Panel */}
        <ConfigPanel />
      </div>
    </div>
  );
};
