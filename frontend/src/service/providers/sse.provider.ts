import { PipelineStatusUpdate, PipelineStatus } from '@/models';

export interface StreamingProvider {
  connect(pipelineId: string): Promise<void>;
  disconnect(): void;
  onStatusUpdate(callback: (status: PipelineStatusUpdate) => void): void;
  onError(callback: (error: Error) => void): void;
  isConnected(): boolean;
}

// Mock SSE Provider for MVP (simulates SSE with intervals)
export class MockSSEProvider implements StreamingProvider {
  private interval: ReturnType<typeof setInterval> | null = null;
  private statusCallback: ((status: PipelineStatusUpdate) => void) | null = null;
  private connected = false;
  private startTime = Date.now();

  async connect(pipelineId: string): Promise<void> {
    this.connected = true;
    this.startTime = Date.now();

    this.interval = setInterval(() => {
      if (!this.statusCallback) return;

      const mockStatus: PipelineStatusUpdate = {
        pipelineId,
        status: PipelineStatus.RUNNING,
        metrics: {
          fps: 25 + Math.random() * 5,
          processedFrames: Math.floor((Date.now() - this.startTime) / 40),
          droppedFrames: Math.floor(Math.random() * 5),
          cpuUsage: 40 + Math.random() * 20,
          gpuUsage: 30 + Math.random() * 30,
          memoryUsage: 1024 + Math.random() * 512,
          uptime: Date.now() - this.startTime,
        },
        timestamp: new Date().toISOString(),
      };

      this.statusCallback(mockStatus);
    }, 1000);
  }

  disconnect(): void {
    if (this.interval) {
      clearInterval(this.interval);
      this.interval = null;
    }
    this.connected = false;
  }

  onStatusUpdate(callback: (status: PipelineStatusUpdate) => void): void {
    this.statusCallback = callback;
  }

  onError(_callback: (error: Error) => void): void {
    // Mock implementation - errors are logged to console
  }

  isConnected(): boolean {
    return this.connected;
  }
}

// Real SSE Provider (for future use)
export class SSEProvider implements StreamingProvider {
  private eventSource: EventSource | null = null;
  private statusCallback: ((status: PipelineStatusUpdate) => void) | null = null;
  private _errorCallback: ((error: Error) => void) | null = null;

  async connect(pipelineId: string): Promise<void> {
    this.eventSource = new EventSource(`/api/pipeline/${pipelineId}/status/stream`);

    this.eventSource.addEventListener('status', (event) => {
      if (this.statusCallback) {
        const status = JSON.parse(event.data) as PipelineStatusUpdate;
        this.statusCallback(status);
      }
    });

    this.eventSource.onerror = (error) => {
      console.error('SSE connection error:', error);
      if (this._errorCallback) {
        this._errorCallback(new Error('SSE connection failed'));
      }
    };
  }

  disconnect(): void {
    this.eventSource?.close();
    this.eventSource = null;
  }

  onStatusUpdate(callback: (status: PipelineStatusUpdate) => void): void {
    this.statusCallback = callback;
  }

  onError(callback: (error: Error) => void): void {
    this._errorCallback = callback;
  }

  isConnected(): boolean {
    return this.eventSource !== null && this.eventSource.readyState === EventSource.OPEN;
  }
}
