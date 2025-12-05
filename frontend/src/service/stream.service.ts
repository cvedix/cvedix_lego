import { useEffect, useState } from 'react';
import { useAppDispatch } from '@/store';
import { updatePipelineMetrics, setPipelineStatus } from '@/store/pipelineSlice';
import { StreamingProvider, MockSSEProvider } from './providers/sse.provider';

// Auto-select the best available provider
function selectProvider(): StreamingProvider {
  // For MVP, always use MockSSEProvider
  // In production, you would check availability:
  // if (typeof EventSource !== 'undefined') {
  //   return new SSEProvider();
  // }
  // if (typeof WebSocket !== 'undefined') {
  //   return new WebSocketProvider();
  // }

  return new MockSSEProvider();
}

export const useStreamingStatus = (pipelineId: string, enabled: boolean) => {
  const dispatch = useAppDispatch();
  const [provider, setProvider] = useState<StreamingProvider | null>(null);
  const [isConnected, setIsConnected] = useState(false);

  useEffect(() => {
    if (!enabled || !pipelineId) {
      // Cleanup if disabled
      if (provider) {
        provider.disconnect();
        setProvider(null);
        setIsConnected(false);
      }
      return;
    }

    // Create and connect provider
    const selectedProvider = selectProvider();

    selectedProvider.onStatusUpdate((status) => {
      dispatch(setPipelineStatus(status.status));
      if (status.metrics) {
        dispatch(updatePipelineMetrics(status.metrics));
      }
    });

    selectedProvider.onError((error) => {
      console.error('Streaming error:', error);
    });

    selectedProvider.connect(pipelineId).then(() => {
      setIsConnected(true);
    });

    setProvider(selectedProvider);

    return () => {
      selectedProvider.disconnect();
      setIsConnected(false);
    };
  }, [pipelineId, enabled, dispatch]);

  return { provider, isConnected };
};
