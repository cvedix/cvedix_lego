import { apiClient, uploadClient } from './client';
import { ApiResponse } from '@/models';

// Backend response structure for GET /lego/getmodellist
export interface BackendModelListResponse {
  models: Array<{
    name: string;
    size: number;
  }>;
}

// Frontend normalized structure
export interface ModelInfo {
  name: string;
  size: number;
}

export interface ModelListResponse {
  models: ModelInfo[];
}

// Backend response structure for POST /lego/postmodel
export interface BackendUploadModelResponse {
  status: string;
  message: string;
}

export const modelApi = {
  /**
   * Get list of uploaded models
   * GET /lego/getmodellist
   * Backend returns: {"models": [{"name": "...", "size": ...}]}
   */
  getModelList: async (): Promise<ApiResponse<ModelListResponse>> => {
    try {
      const response = await apiClient.get<BackendModelListResponse>('/lego/getmodellist');

      // Backend already returns in correct format, just wrap it
      return {
        success: true,
        data: {
          models: response.data.models,
        },
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Failed to fetch model list',
      };
    }
  },

  /**
   * Upload a new model file
   * POST /lego/postmodel
   * Backend returns: {"status": "success", "message": "Model uploaded successfully."}
   * @param file - Model file to upload (ONNX)
   * @param onProgress - Optional callback for upload progress
   */
  uploadModel: async (
    file: File,
    onProgress?: (progress: number) => void
  ): Promise<ApiResponse<BackendUploadModelResponse>> => {
    try {
      const formData = new FormData();
      formData.append('model', file);

      const response = await uploadClient.post<BackendUploadModelResponse>(
        '/lego/postmodel',
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
        error: error instanceof Error ? error.message : 'Failed to upload model',
      };
    }
  },

  /**
   * Delete a model file
   * POST /lego/deletemodel
   * Backend returns: {"status": "SUCCESS/ERROR", "message": "..."}
   */
  deleteModel: async (modelName: string): Promise<ApiResponse<{ status: string; message: string }>> => {
    try {
      const response = await apiClient.post<{ status: string; message: string }>(
        '/lego/deletemodel',
        { model_name: modelName }
      );

      return {
        success: response.data.status === 'SUCCESS',
        data: response.data,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Failed to delete model',
      };
    }
  },
};
