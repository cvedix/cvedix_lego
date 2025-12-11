import { PipelineStatusUpdate } from '@/models';
import { StreamingProvider } from './sse.provider';

// WebSocket Provider (stub for future implementation)
export class WebSocketProvider implements StreamingProvider {
  private ws: WebSocket | null = null;
  private statusCallback: ((status: PipelineStatusUpdate) => void) | null = null;
  private errorCallback: ((error: Error) => void) | null = null;

  async connect(pipelineId: string): Promise<void> {
    const wsUrl = `ws://${window.location.host}/api/pipeline/${pipelineId}/ws`;
    this.ws = new WebSocket(wsUrl);

    this.ws.onmessage = (event) => {
      if (this.statusCallback) {
        const status = JSON.parse(event.data) as PipelineStatusUpdate;
        this.statusCallback(status);
      }
    };

    this.ws.onerror = (error) => {
      console.error('WebSocket error:', error);
      if (this.errorCallback) {
        this.errorCallback(new Error('WebSocket connection failed'));
      }
    };

    // Auto-reconnect logic
    this.ws.onclose = () => {
      console.log('WebSocket closed, attempting to reconnect...');
      setTimeout(() => this.connect(pipelineId), 3000);
    };
  }

  disconnect(): void {
    this.ws?.close();
    this.ws = null;
  }

  onStatusUpdate(callback: (status: PipelineStatusUpdate) => void): void {
    this.statusCallback = callback;
  }

  onError(callback: (error: Error) => void): void {
    this.errorCallback = callback;
  }

  isConnected(): boolean {
    return this.ws !== null && this.ws.readyState === WebSocket.OPEN;
  }
}
