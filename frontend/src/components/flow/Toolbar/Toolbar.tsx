import React, { useRef } from 'react';
import { Button } from '@/components/ui/button';
import { useAppDispatch, useAppSelector } from '@/store';
import { resetPipeline, loadPipeline, setPipelineStatus, setLoading, openRtmpStreamModal, closeRtmpStreamModal } from '@/store';
import { downloadPipelineAsJson, uploadPipelineFromJson } from '@/utils/serialization';
import { buildBackendPipeline, validatePipeline } from '@/utils/pipelineBuilder';
import { pipelineApi } from '@/api/pipeline.api';
import { CvedixNodeType, PipelineStatus } from '@/models';
import { Play, Square, Save, Upload, FileText } from 'lucide-react';
import { STATUS_COLORS } from '@/utils/constants';
import { cn } from '@/lib/utils';

export const Toolbar: React.FC = () => {
  const dispatch = useAppDispatch();
  const pipeline = useAppSelector((state) => state.pipeline.pipeline);
  const isLoading = useAppSelector((state) => state.pipeline.isLoading);
  const fileInputRef = useRef<HTMLInputElement>(null);
  const isRunning = pipeline.status === PipelineStatus.RUNNING;
  const isStarting = pipeline.status === PipelineStatus.STARTING;

  const handleNew = () => {
    if (confirm('Create a new pipeline? Current pipeline will be lost.')) {
      dispatch(resetPipeline());
    }
  };

  const handleSave = () => {
    downloadPipelineAsJson(pipeline);
  };

  const handleLoad = () => {
    fileInputRef.current?.click();
  };

  const handleFileChange = async (event: React.ChangeEvent<HTMLInputElement>) => {
    const file = event.target.files?.[0];
    if (!file) return;

    try {
      const loadedPipeline = await uploadPipelineFromJson(file);
      dispatch(loadPipeline(loadedPipeline));
      alert('Pipeline loaded successfully!');
    } catch (error) {
      alert(`Failed to load pipeline: ${error instanceof Error ? error.message : 'Unknown error'}`);
    }

    // Reset file input
    event.target.value = '';
  };

  const handleRun = async () => {
    // Validate pipeline
    const validation = validatePipeline(pipeline.nodes);
    if (!validation.valid) {
      alert(validation.error);
      return;
    }

    // Build backend JSON
    const backendPipeline = buildBackendPipeline(pipeline.nodes);

    // Start pipeline
    dispatch(setLoading(true));
    dispatch(setPipelineStatus(PipelineStatus.STARTING));
    try {
      const response = await pipelineApi.start(backendPipeline);

      if (response.success) {
        dispatch(setPipelineStatus(PipelineStatus.RUNNING));

        // Get RTMP URL from destination node
        const destNode = pipeline.nodes.find((n) => n.type === CvedixNodeType.RTMP_DESTINATION);
        const rtmpUrl = (destNode?.data.config.rtmp_url as string) || import.meta.env.VITE_DEFAULT_RTMP_URL;

        // Open stream modal
        dispatch(openRtmpStreamModal(rtmpUrl));
      } else {
        dispatch(setPipelineStatus(PipelineStatus.ERROR));
        alert(`Failed to start pipeline: ${response.error}`);
      }
    } catch (error) {
      dispatch(setPipelineStatus(PipelineStatus.ERROR));
      alert(`Error starting pipeline: ${error instanceof Error ? error.message : 'Unknown error'}`);
    } finally {
      dispatch(setLoading(false));
    }
  };

  const handleStop = async () => {
    dispatch(setLoading(true));
    try {
      const response = await pipelineApi.stop();

      if (response.success) {
        dispatch(setPipelineStatus(PipelineStatus.STOPPED));
        dispatch(closeRtmpStreamModal());
      } else {
        alert(`Failed to stop pipeline: ${response.error}`);
      }
    } catch (error) {
      alert(`Error stopping pipeline: ${error instanceof Error ? error.message : 'Unknown error'}`);
    } finally {
      dispatch(setLoading(false));
    }
  };

  const metrics = (pipeline.metadata as {metrics?: {fps?: number; processedFrames?: number}})?.metrics;

  return (
    <div className="h-14 bg-white border-b-2 border-border flex items-center justify-between px-6 shadow-sm">
      {/* Left side - Logo and actions */}
      <div className="flex items-center gap-6">
        <div className="flex items-center gap-2">
          <div className="w-8 h-8 bg-gradient-to-br from-primary to-accent rounded flex items-center justify-center">
            <span className="text-white font-bold text-sm">CV</span>
          </div>
          <h1 className="text-lg font-bold text-gray-800 tracking-tight">CvedixLego</h1>
        </div>

        <div className="flex gap-1.5">
          <Button variant="outline" size="sm" onClick={handleNew}>
            <FileText className="w-3.5 h-3.5 mr-1.5" />
            New
          </Button>
          <Button variant="outline" size="sm" onClick={handleSave}>
            <Save className="w-3.5 h-3.5 mr-1.5" />
            Save
          </Button>
          <Button variant="outline" size="sm" onClick={handleLoad}>
            <Upload className="w-3.5 h-3.5 mr-1.5" />
            Load
          </Button>
          <input
            ref={fileInputRef}
            type="file"
            accept=".json"
            onChange={handleFileChange}
            className="hidden"
          />
        </div>
      </div>

      {/* Right side - Status and controls */}
      <div className="flex items-center gap-4">
        {/* Metrics */}
        {isRunning && metrics && (
          <div className="flex gap-4 text-xs bg-gray-50 px-3 py-1.5 rounded border border-gray-200">
            <div>
              <span className="text-gray-500 font-medium">FPS:</span>{' '}
              <span className="font-mono text-gray-900 font-semibold">{metrics.fps?.toFixed(1)}</span>
            </div>
            <div className="border-l border-gray-300 pl-4">
              <span className="text-gray-500 font-medium">Frames:</span>{' '}
              <span className="font-mono text-gray-900 font-semibold">{metrics.processedFrames}</span>
            </div>
          </div>
        )}

        {/* Status */}
        <div className="flex items-center gap-2 bg-gray-50 px-3 py-1.5 rounded border border-gray-200">
          <div className={cn('w-2 h-2 rounded-full', isRunning ? 'bg-green-500 animate-pulse' : 'bg-gray-400')} />
          <span className={cn('text-xs font-bold uppercase tracking-wide', STATUS_COLORS[pipeline.status])}>
            {pipeline.status}
          </span>
        </div>

        {/* Run/Stop button */}
        {isRunning ? (
          <Button
            variant="destructive"
            size="sm"
            onClick={handleStop}
            disabled={isLoading}
            className="font-semibold"
          >
            <Square className="w-3.5 h-3.5 mr-1.5" />
            {isLoading ? 'Stopping...' : 'Stop'}
          </Button>
        ) : (
          <Button
            variant="default"
            size="sm"
            onClick={handleRun}
            disabled={isStarting || isLoading || pipeline.nodes.length === 0}
            className="font-semibold"
          >
            <Play className="w-3.5 h-3.5 mr-1.5" />
            {isStarting ? 'Starting...' : 'Run'}
          </Button>
        )}
      </div>
    </div>
  );
};
