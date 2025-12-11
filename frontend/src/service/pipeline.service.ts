import { useMutation, useQuery, useQueryClient } from '@tanstack/react-query';
import { pipelineApi } from '@/api';
import { useAppDispatch } from '@/store';
import { setPipelineStatus } from '@/store/pipelineSlice';
import { PipelineStatus } from '@/models';

export const usePipelineOperations = () => {
  const queryClient = useQueryClient();
  const dispatch = useAppDispatch();

  const startPipeline = useMutation({
    mutationFn: (pipelineId: string) => pipelineApi.start(pipelineId),
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
    mutationFn: (pipelineId: string) => pipelineApi.stop(pipelineId),
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

export const usePipelineStatus = (pipelineId: string, enabled: boolean = false) => {
  return useQuery({
    queryKey: ['pipeline-status', pipelineId],
    queryFn: async () => {
      const response = await pipelineApi.getStatus(pipelineId);
      if (!response.success || !response.data) {
        throw new Error(response.error || 'Failed to fetch pipeline status');
      }
      return response.data;
    },
    enabled: enabled && !!pipelineId,
    refetchInterval: enabled ? 2000 : false, // Poll every 2 seconds when enabled
  });
};
