// Run service for pipeline execution operations
import { usePipelineOperations } from './pipeline.service';
import { useStreamingStatus } from './stream.service';
import { useAppSelector } from '@/store';
import { PipelineStatus } from '@/models';
import { buildBackendPipeline } from '@/utils/pipelineBuilder';

export const useRunPipeline = () => {
  const pipeline = useAppSelector((state) => state.pipeline.pipeline);
  const { startPipeline, stopPipeline, isStarting, isStopping } = usePipelineOperations();

  const isRunning = pipeline.status === PipelineStatus.RUNNING;

  // Auto-enable streaming when pipeline is running
  const { isConnected } = useStreamingStatus(pipeline.id, isRunning);

  const handleStart = () => {
    if (pipeline.nodes.length === 0) {
      console.warn('Cannot start empty pipeline');
      return;
    }
    const backendPipeline = buildBackendPipeline(pipeline.nodes);
    startPipeline(backendPipeline);
  };

  const handleStop = () => {
    stopPipeline();
  };

  return {
    start: handleStart,
    stop: handleStop,
    isRunning,
    isStarting,
    isStopping,
    isStreaming: isConnected,
    canRun: pipeline.nodes.length > 0,
  };
};
