import { apiClient, uploadClient } from './client';
import { ApiResponse } from '@/models';

export interface VideoInfo {
  video_name: string;
  file_path: string;
  file_size: number;
  upload_time: string;
  duration?: number;
  resolution?: string;
}

export interface VideoListResponse {
  videos: VideoInfo[];
  total: number;
}

export interface UploadVideoResponse {
  success: boolean;
  message: string;
  video_name: string;
  file_path: string;
}

export const videoApi = {
  /**
   * Get list of uploaded videos
   * GET /lego/getvideolist
   */
  getVideoList: async (): Promise<ApiResponse<VideoListResponse>> => {
    try {
      const response = await apiClient.get<VideoListResponse>('/lego/getvideolist');
      return {
        success: true,
        data: response.data,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Failed to fetch video list',
      };
    }
  },

  /**
   * Upload a new video file
   * POST /lego/postvideo
   * @param file - Video file to upload (MP4)
   * @param onProgress - Optional callback for upload progress
   */
  uploadVideo: async (
    file: File,
    onProgress?: (progress: number) => void
  ): Promise<ApiResponse<UploadVideoResponse>> => {
    try {
      const formData = new FormData();
      formData.append('video', file);

      const response = await uploadClient.post<UploadVideoResponse>(
        '/lego/postvideo',
        formData,
        {
          onUploadProgress: (progressEvent) => {
            if (onProgress && progressEvent.total) {
              const progress = Math.round((progressEvent.loaded * 100) / progressEvent.total);
              onProgress(progress);
            }
          },
        }
      );

      return {
        success: true,
        data: response.data,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Failed to upload video',
      };
    }
  },
};
