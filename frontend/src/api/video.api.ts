import { apiClient, uploadClient } from './client';
import { ApiResponse } from '@/models';

// Backend response structure for GET /lego/getvideolist
export interface BackendVideoListResponse {
  media: Array<{
    name: string;
    size: number;
  }>;
}

// Frontend normalized structure
export interface VideoInfo {
  name: string;
  size: number;
}

export interface VideoListResponse {
  videos: VideoInfo[];
}

// Backend response structure for POST /lego/postvideo
export interface BackendUploadVideoResponse {
  status: string;
  message: string;
}

export const videoApi = {
  /**
   * Get list of uploaded videos
   * GET /lego/getvideolist
   * Backend returns: {"media": [{"name": "...", "size": ...}]}
   */
  getVideoList: async (): Promise<ApiResponse<VideoListResponse>> => {
    try {
      const response = await apiClient.get<BackendVideoListResponse>('/lego/getvideolist');

      // Transform backend response to frontend format
      return {
        success: true,
        data: {
          videos: response.data.media,
        },
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
   * Backend returns: {"status": "success", "message": "Video uploaded successfully."}
   * @param file - Video file to upload (MP4)
   * @param onProgress - Optional callback for upload progress
   */
  uploadVideo: async (
    file: File,
    onProgress?: (progress: number) => void
  ): Promise<ApiResponse<BackendUploadVideoResponse>> => {
    try {
      const formData = new FormData();
      formData.append('video', file);

      const response = await uploadClient.post<BackendUploadVideoResponse>(
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
        success: response.data.status === 'success',
        data: response.data,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Failed to upload video',
      };
    }
  },

  /**
   * Delete a video file
   * POST /lego/deletevideo
   * Backend returns: {"status": "SUCCESS/ERROR", "message": "..."}
   */
  deleteVideo: async (videoName: string): Promise<ApiResponse<{ status: string; message: string }>> => {
    try {
      const response = await apiClient.post<{ status: string; message: string }>(
        '/lego/deletevideo',
        { video_name: videoName }
      );

      return {
        success: response.data.status === 'SUCCESS',
        data: response.data,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Failed to delete video',
      };
    }
  },
};
