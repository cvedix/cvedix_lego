import React from 'react';
import { Toolbar } from '@/components/flow/Toolbar/Toolbar';
import { NodePalette } from '@/components/flow/NodePalette/NodePalette';
import { FlowCanvas } from '@/components/flow/FlowCanvas/FlowCanvas';
import { ConfigPanel } from '@/components/flow/ConfigPanel/ConfigPanel';
import { VideoSelectionModal } from '@/components/modals/VideoSelectionModal';
import { RTMPStreamModal } from '@/components/modals/RTMPStreamModal';
import { useAppDispatch, useAppSelector } from '@/store';
import { closeVideoSelectionModal, closeRtmpStreamModal, updateNodeConfig, setPipelineStatus } from '@/store';
import { pipelineApi } from '@/api/pipeline.api';
import { PipelineStatus } from '@/models';

export const HomePage: React.FC = () => {
  const dispatch = useAppDispatch();
  const videoSelectionModal = useAppSelector((state) => state.ui.modals.videoSelection);
  const rtmpStreamModal = useAppSelector((state) => state.ui.modals.rtmpStream);

  const handleVideoSelected = (videoName: string) => {
    if (videoSelectionModal.nodeId) {
      dispatch(updateNodeConfig({
        nodeId: videoSelectionModal.nodeId,
        config: { video_name: videoName },
      }));
    }
    dispatch(closeVideoSelectionModal());
  };

  const handleStopFromModal = async () => {
    // Call stop pipeline API
    const response = await pipelineApi.stop();
    if (response.success) {
      dispatch(setPipelineStatus(PipelineStatus.STOPPED));
      dispatch(closeRtmpStreamModal());
    }
  };

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

      {/* Modals */}
      <VideoSelectionModal
        open={videoSelectionModal.open}
        onClose={() => dispatch(closeVideoSelectionModal())}
        onVideoSelected={handleVideoSelected}
      />

      <RTMPStreamModal
        open={rtmpStreamModal.open}
        rtmpUrl={rtmpStreamModal.rtmpUrl || ''}
        onClose={() => dispatch(closeRtmpStreamModal())}
        onStop={handleStopFromModal}
      />
    </div>
  );
};
