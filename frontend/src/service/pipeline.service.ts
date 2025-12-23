import { useMutation, useQueryClient } from '@tanstack/react-query';
import { pipelineApi, BackendPipelineRequest } from '@/api/pipeline.api';
import { useAppDispatch } from '@/store';
import { setPipelineStatus } from '@/store/pipelineSlice';
import { PipelineStatus } from '@/models';

export const usePipelineOperations = () => {
  const queryClient = useQueryClient();
  const dispatch = useAppDispatch();

  const startPipeline = useMutation({
    mutationFn: (pipelineJson: BackendPipelineRequest) => pipelineApi.start(pipelineJson),
    onSuccess: () => {
      dispatch(setPipelineStatus(PipelineStatus.RUNNING));
      queryClient.invalidateQueries({ queryKey: ['pipeline-status'] });
    },
    onError: (error) => {
      dispatch(setPipelineStatus(PipelineStatus.ERROR));
      console.error('Failed to start pipeline:', error);
    },
  });

  const stopPipeline = useMutation({
    mutationFn: () => pipelineApi.stop(),
    onSuccess: () => {
      dispatch(setPipelineStatus(PipelineStatus.STOPPED));
      queryClient.invalidateQueries({ queryKey: ['pipeline-status'] });
    },
    onError: (error) => {
      console.error('Failed to stop pipeline:', error);
    },
  });

  return {
    startPipeline: startPipeline.mutate,
    stopPipeline: stopPipeline.mutate,
    isStarting: startPipeline.isPending,
    isStopping: stopPipeline.isPending,
  };
};
