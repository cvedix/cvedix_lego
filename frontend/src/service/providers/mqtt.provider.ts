import { PipelineStatusUpdate } from '@/models';
import { StreamingProvider } from './sse.provider';

// MQTT Provider (stub for future IoT integration)
// Note: Requires 'mqtt' package to be installed for real implementation
export class MQTTProvider implements StreamingProvider {
  // private client: mqtt.MqttClient | null = null;
  private connected = false;

  async connect(_pipelineId: string): Promise<void> {

    // Future implementation with mqtt package:
    // this.client = mqtt.connect('ws://mqtt-broker:9001', {
    //   clientId: `cvedix-${pipelineId}-${Date.now()}`,
    // });
    //
    // this.client.on('connect', () => {
    //   this.connected = true;
    //   // Subscribe to pipeline status topic
    //   this.client?.subscribe(`cvedix/pipeline/${pipelineId}/status`);
    // });
    //
    // this.client.on('message', (topic, message) => {
    //   if (this.statusCallback) {
    //     const status = JSON.parse(message.toString()) as PipelineStatusUpdate;
    //     this.statusCallback(status);
    //   }
    // });
    //
    // this.client.on('error', (error) => {
    //   console.error('MQTT error:', error);
    //   if (this.errorCallback) {
    //     this.errorCallback(error);
    //   }
    // });

    console.log('MQTT Provider: Stub implementation - not yet connected');
    this.connected = true;
  }

  disconnect(): void {
    // this.client?.end();
    // this.client = null;
    this.connected = false;
  }

  onStatusUpdate(_callback: (status: PipelineStatusUpdate) => void): void {
    // Stub implementation
  }

  onError(_callback: (error: Error) => void): void {
    // Stub implementation
  }

  isConnected(): boolean {
    return this.connected;
  }

  // MQTT-specific: Publish control commands (future implementation)
  publishCommand(command: 'start' | 'stop' | 'pause'): void {
    // this.client?.publish(
    //   `cvedix/pipeline/${this.pipelineId}/control`,
    //   JSON.stringify({ command })
    // );
    console.log(`MQTT: Would publish command: ${command}`);
  }
}
