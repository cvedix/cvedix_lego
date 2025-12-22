import React, { useState, useCallback } from 'react';
import {
  Dialog,
  DialogContent,
  DialogDescription,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { Progress } from '@/components/ui/progress';
import { useQuery, useMutation, useQueryClient } from '@tanstack/react-query';
import { videoApi } from '@/api/video.api';
import { Upload, Video, Loader2, CheckCircle2 } from 'lucide-react';
import { cn } from '@/lib/utils';

interface VideoSelectionModalProps {
  open: boolean;
  onClose: () => void;
  onVideoSelected: (videoName: string) => void;
}

export const VideoSelectionModal: React.FC<VideoSelectionModalProps> = ({
  open,
  onClose,
  onVideoSelected,
}) => {
  const [selectedVideo, setSelectedVideo] = useState<string | null>(null);
  const [uploadProgress, setUploadProgress] = useState(0);
  const [isUploading, setIsUploading] = useState(false);
  const queryClient = useQueryClient();

  // Fetch video list
  const { data: videoListData, isLoading } = useQuery({
    queryKey: ['videos'],
    queryFn: async () => {
      const response = await videoApi.getVideoList();
      if (!response.success || !response.data) {
        throw new Error(response.error || 'Failed to fetch videos');
      }
      return response.data;
    },
    enabled: open,
  });

  // Upload mutation
  const uploadMutation = useMutation({
    mutationFn: (file: File) =>
      videoApi.uploadVideo(file, (progress) => setUploadProgress(progress)),
    onSuccess: (response) => {
      if (response.success && response.data) {
        queryClient.invalidateQueries({ queryKey: ['videos'] });
        setSelectedVideo(response.data.video_name);
        setIsUploading(false);
        setUploadProgress(0);
      }
    },
    onError: (error) => {
      console.error('Upload failed:', error);
      alert(`Upload failed: ${error instanceof Error ? error.message : 'Unknown error'}`);
      setIsUploading(false);
      setUploadProgress(0);
    },
  });

  const handleFileSelect = useCallback(
    (event: React.ChangeEvent<HTMLInputElement>) => {
      const file = event.target.files?.[0];
      if (!file) return;

      // Validate file type
      if (!file.name.toLowerCase().endsWith('.mp4')) {
        alert('Please select an MP4 file');
        return;
      }

      setIsUploading(true);
      uploadMutation.mutate(file);
    },
    [uploadMutation]
  );

  const handleConfirm = () => {
    if (selectedVideo) {
      onVideoSelected(selectedVideo);
      onClose();
    }
  };

  return (
    <Dialog open={open} onOpenChange={onClose}>
      <DialogContent className="max-w-2xl max-h-[80vh] overflow-hidden flex flex-col">
        <DialogHeader>
          <DialogTitle>Select Video Source</DialogTitle>
          <DialogDescription>
            Choose an existing video or upload a new one
          </DialogDescription>
        </DialogHeader>

        <div className="flex-1 overflow-y-auto space-y-6 py-4">
          {/* Upload Section */}
          <div className="space-y-3">
            <Label className="text-sm font-semibold">Upload New Video</Label>
            <div className="border-2 border-dashed border-gray-300 rounded-lg p-6 hover:border-primary transition-colors">
              <div className="flex flex-col items-center gap-3">
                {isUploading ? (
                  <>
                    <Loader2 className="w-8 h-8 text-primary animate-spin" />
                    <div className="w-full max-w-xs space-y-2">
                      <Progress value={uploadProgress} />
                      <p className="text-xs text-center text-gray-500">
                        Uploading... {uploadProgress}%
                      </p>
                    </div>
                  </>
                ) : (
                  <>
                    <Upload className="w-8 h-8 text-gray-400" />
                    <div className="text-center">
                      <Label
                        htmlFor="video-upload"
                        className="cursor-pointer text-sm font-medium text-primary hover:underline"
                      >
                        Click to upload
                      </Label>
                      <Input
                        id="video-upload"
                        type="file"
                        accept=".mp4,video/mp4"
                        onChange={handleFileSelect}
                        className="hidden"
                      />
                      <p className="text-xs text-gray-500 mt-1">MP4 files only</p>
                    </div>
                  </>
                )}
              </div>
            </div>
          </div>

          {/* Existing Videos Section */}
          <div className="space-y-3">
            <Label className="text-sm font-semibold">Or Select Existing Video</Label>
            {isLoading ? (
              <div className="flex items-center justify-center py-8">
                <Loader2 className="w-6 h-6 animate-spin text-primary" />
              </div>
            ) : (
              <div className="grid gap-2 max-h-64 overflow-y-auto">
                {videoListData?.videos.length === 0 ? (
                  <p className="text-sm text-gray-500 text-center py-4">
                    No videos uploaded yet
                  </p>
                ) : (
                  videoListData?.videos.map((video) => (
                    <button
                      key={video.video_name}
                      onClick={() => setSelectedVideo(video.video_name)}
                      className={cn(
                        'flex items-start gap-3 p-3 rounded-lg border-2 transition-all text-left',
                        selectedVideo === video.video_name
                          ? 'border-primary bg-primary/5'
                          : 'border-gray-200 hover:border-gray-300'
                      )}
                    >
                      <Video className="w-5 h-5 text-primary flex-shrink-0 mt-0.5" />
                      <div className="flex-1 min-w-0">
                        <div className="flex items-center gap-2">
                          <p className="text-sm font-medium truncate">
                            {video.video_name}
                          </p>
                          {selectedVideo === video.video_name && (
                            <CheckCircle2 className="w-4 h-4 text-primary flex-shrink-0" />
                          )}
                        </div>
                        <p className="text-xs text-gray-500">
                          {(video.file_size / (1024 * 1024)).toFixed(2)} MB
                          {video.duration && ` • ${video.duration}`}
                        </p>
                      </div>
                    </button>
                  ))
                )}
              </div>
            )}
          </div>
        </div>

        {/* Footer */}
        <div className="flex justify-end gap-2 pt-4 border-t">
          <Button variant="outline" onClick={onClose}>
            Cancel
          </Button>
          <Button onClick={handleConfirm} disabled={!selectedVideo}>
            Confirm Selection
          </Button>
        </div>
      </DialogContent>
    </Dialog>
  );
};
