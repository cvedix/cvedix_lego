import React, { useEffect, useRef, useState } from 'react';
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
  const retryTimeoutRef = useRef<number | null>(null);
  const [streamStatus, setStreamStatus] = useState<'loading' | 'ready' | 'error'>('loading');
  const [retryCount, setRetryCount] = useState(0);
  const [playerReady, setPlayerReady] = useState(false); // Track when player is initialized

  // Initialize player once
  useEffect(() => {
    if (!open || !videoRef.current) {
      setPlayerReady(false);
      return;
    }

    console.log('Initializing Video.js player...');

    // Create player once
    const player = videojs(videoRef.current, {
      controls: true,
      autoplay: 'muted',
      muted: true,
      preload: 'auto',
      liveui: true,
      html5: {
        vhs: {
          overrideNative: true,
          enableLowInitialPlaylist: true,
        },
        nativeVideoTracks: false,
        nativeAudioTracks: false,
        nativeTextTracks: false,
      },
    });

    // Success - stream is playing
    player.on('playing', () => {
      console.log('✓ Video is now playing');
      setStreamStatus('ready');
    });

    player.on('loadeddata', () => {
      console.log('Video data loaded');
      player.play()?.catch((err) => {
        console.error('Play failed:', err);
      });
    });

    player.on('error', (err: any) => {
      const error = player.error();
      console.error('Video.js error:', err);
      if (error) {
        console.error('Error code:', error.code);
        console.error('Error message:', error.message);
      }
    });

    playerRef.current = player;

    // Signal that player is ready
    console.log('Player initialized, setting playerReady = true');
    setPlayerReady(true);

    return () => {
      console.log('Disposing player...');
      setPlayerReady(false);
      if (playerRef.current) {
        playerRef.current.dispose();
        playerRef.current = null;
      }
    };
  }, [open]);

  // Retry logic for loading stream source
  useEffect(() => {
    if (!open || !playerReady) {
      console.log('Skipping source load - open:', open, 'playerReady:', playerReady);
      return;
    }

    console.log('=== Starting source load effect (player is ready) ===');

    // Reset state
    setStreamStatus('loading');
    setRetryCount(0);

    // Clear any existing retry timeout
    if (retryTimeoutRef.current) {
      clearTimeout(retryTimeoutRef.current);
      retryTimeoutRef.current = null;
    }

    // Convert RTMP to HLS
    const hlsBaseUrl = import.meta.env.VITE_HLS_BASE_URL || 'http://media.server.cvedix.com';
    const rtmpUrl_parsed = new URL(rtmpUrl);
    const streamPath = rtmpUrl_parsed.pathname;
    const hlsUrl = `${hlsBaseUrl}${streamPath}/hls.m3u8`;

    console.log('HLS Base URL:', hlsBaseUrl);
    console.log('RTMP URL:', rtmpUrl);
    console.log('HLS URL:', hlsUrl);

    let currentAttempt = 0;
    let checkTimeout: number | null = null;
    let hasStartedPlaying = false;

    const loadSource = () => {
      if (!playerRef.current) {
        console.log('Player ref is null, aborting load');
        return;
      }

      currentAttempt++;
      console.log(`>>> Attempt ${currentAttempt} to load stream...`);
      setRetryCount(currentAttempt - 1);

      // Load the source
      playerRef.current.src({
        src: hlsUrl,
        type: 'application/x-mpegURL',
      });

      console.log('Source set, waiting for stream to start...');

      // Try to play
      playerRef.current.ready(() => {
        console.log('Player ready, attempting to play...');
        playerRef.current?.play()?.catch((err) => {
          console.error('Play attempt failed:', err);
        });
      });

      // Clear previous check timeout
      if (checkTimeout) {
        clearTimeout(checkTimeout);
      }

      // Check if stream started playing within 5 seconds
      checkTimeout = window.setTimeout(() => {
        console.log('Check timeout fired - hasStartedPlaying:', hasStartedPlaying, 'attempt:', currentAttempt);
        if (!hasStartedPlaying && currentAttempt < 15) {
          console.log(`Stream not ready after ${currentAttempt} attempts, retrying in 3s...`);
          retryTimeoutRef.current = window.setTimeout(loadSource, 3000);
        } else if (currentAttempt >= 15) {
          console.error('Max retries reached');
          setStreamStatus('error');
        }
      }, 5000);
    };

    // Listen for playing event to stop retries
    const onPlaying = () => {
      console.log('✓✓✓ PLAYING EVENT FIRED ✓✓✓');
      hasStartedPlaying = true;
      setStreamStatus('ready');
      if (checkTimeout) {
        clearTimeout(checkTimeout);
        checkTimeout = null;
      }
      if (retryTimeoutRef.current) {
        clearTimeout(retryTimeoutRef.current);
        retryTimeoutRef.current = null;
      }
    };

    if (playerRef.current) {
      playerRef.current.on('playing', onPlaying);
    }

    // Start loading
    loadSource();

    return () => {
      console.log('=== Cleaning up source load effect ===');
      if (retryTimeoutRef.current) {
        clearTimeout(retryTimeoutRef.current);
        retryTimeoutRef.current = null;
      }
      if (checkTimeout) {
        clearTimeout(checkTimeout);
      }
      if (playerRef.current) {
        playerRef.current.off('playing', onPlaying);
      }
    };
  }, [open, rtmpUrl, playerReady]);

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
          <div className="bg-black rounded-lg overflow-hidden relative" data-vjs-player>
            <video
              ref={videoRef}
              className="video-js vjs-big-play-centered"
              style={{ width: '100%', height: '500px' }}
              playsInline
              muted
            />

            {/* Loading Overlay */}
            {streamStatus === 'loading' && (
              <div className="absolute inset-0 flex flex-col items-center justify-center bg-black bg-opacity-75 z-10">
                <div className="flex flex-col items-center gap-4">
                  <div className="w-16 h-16 border-4 border-white border-t-transparent rounded-full animate-spin"></div>
                  <div className="text-white text-center">
                    <p className="text-lg font-medium">Waiting for stream...</p>
                    <p className="text-sm text-gray-300 mt-2">
                      The HLS stream is being prepared. This may take a few seconds.
                    </p>
                    {retryCount > 0 && (
                      <p className="text-xs text-gray-400 mt-2">
                        Retry attempt: {retryCount + 1}/10
                      </p>
                    )}
                  </div>
                </div>
              </div>
            )}

            {/* Error Overlay */}
            {streamStatus === 'error' && (
              <div className="absolute inset-0 flex flex-col items-center justify-center bg-black bg-opacity-75 z-10">
                <div className="text-center text-white">
                  <p className="text-lg font-medium text-red-400">Stream Unavailable</p>
                  <p className="text-sm text-gray-300 mt-2">
                    Could not connect to the HLS stream after multiple attempts.
                  </p>
                  <p className="text-xs text-gray-400 mt-2">
                    Please ensure the pipeline is running and the stream is being published.
                  </p>
                </div>
              </div>
            )}
          </div>

          {/* Stream Info */}
          <div className="bg-gray-50 p-4 rounded-lg text-sm">
            <div className="grid grid-cols-2 gap-2">
              <div>
                <span className="font-medium text-gray-700">Status:</span>
                {streamStatus === 'ready' && <span className="ml-2 text-green-600">● Live</span>}
                {streamStatus === 'loading' && <span className="ml-2 text-yellow-600">● Connecting...</span>}
                {streamStatus === 'error' && <span className="ml-2 text-red-600">● Error</span>}
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
