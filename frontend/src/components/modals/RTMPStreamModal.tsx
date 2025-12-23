import React, { useEffect, useRef } from 'react';
import {
  Dialog,
  DialogContent,
  DialogDescription,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog';
import { Button } from '@/components/ui/button';
import videojs from 'video.js';
import 'video.js/dist/video-js.css';
import type Player from 'video.js/dist/types/player';

interface RTMPStreamModalProps {
  open: boolean;
  rtmpUrl: string;
  onClose: () => void;
  onStop: () => void;
}

export const RTMPStreamModal: React.FC<RTMPStreamModalProps> = ({
  open,
  rtmpUrl,
  onClose,
  onStop,
}) => {
  const videoRef = useRef<HTMLVideoElement>(null);
  const playerRef = useRef<Player | null>(null);

  useEffect(() => {
    if (!open || !videoRef.current) return;

    // Convert RTMP to HLS for browser playback
    // Note: You may need to configure your backend to provide HLS stream
    // or use a media server that converts RTMP to HLS
    const hlsUrl = rtmpUrl.replace('rtmp://', 'http://').replace(':1935', ':8080') + '/index.m3u8';

    // Initialize Video.js player
    const player = videojs(videoRef.current, {
      controls: true,
      autoplay: true,
      preload: 'auto',
      fluid: true,
      sources: [
        {
          src: hlsUrl,
          type: 'application/x-mpegURL',
        },
      ],
    });

    playerRef.current = player;

    return () => {
      if (playerRef.current) {
        playerRef.current.dispose();
        playerRef.current = null;
      }
    };
  }, [open, rtmpUrl]);

  const handleStop = () => {
    if (playerRef.current) {
      playerRef.current.pause();
    }
    onStop();
  };

  return (
    <Dialog open={open} onOpenChange={onClose}>
      <DialogContent className="max-w-4xl">
        <DialogHeader>
          <DialogTitle>Live RTMP Stream</DialogTitle>
          <DialogDescription>
            Streaming to: {rtmpUrl}
          </DialogDescription>
        </DialogHeader>

        <div className="space-y-4">
          {/* Video Player */}
          <div className="bg-black rounded-lg overflow-hidden" data-vjs-player>
            <video
              ref={videoRef}
              className="video-js vjs-big-play-centered"
              style={{ width: '100%', height: 'auto' }}
            />
          </div>

          {/* Stream Info */}
          <div className="bg-gray-50 p-4 rounded-lg text-sm">
            <div className="grid grid-cols-2 gap-2">
              <div>
                <span className="font-medium text-gray-700">Status:</span>
                <span className="ml-2 text-green-600">● Live</span>
              </div>
              <div>
                <span className="font-medium text-gray-700">URL:</span>
                <span className="ml-2 text-gray-600 font-mono text-xs truncate block">
                  {rtmpUrl}
                </span>
              </div>
            </div>
          </div>

          {/* Controls */}
          <div className="flex justify-end gap-2">
            <Button variant="outline" onClick={onClose}>
              Minimize
            </Button>
            <Button variant="destructive" onClick={handleStop}>
              Stop Pipeline
            </Button>
          </div>
        </div>
      </DialogContent>
    </Dialog>
  );
};
