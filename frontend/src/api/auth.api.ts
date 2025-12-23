import { apiClient } from './client';
import { ApiResponse } from '@/models';

// Backend response structure for POST /lego/login and /lego/register
export interface BackendAuthResponse {
  status: 'OK' | 'ERROR';
  message: string;
}

export interface LoginRequest {
  username: string;
  password: string;
}

export interface RegisterRequest {
  username: string;
  password: string;
  email?: string;
}

export const authApi = {
  /**
   * Login user
   * POST /lego/login
   * Backend returns: {"status": "OK/ERROR", "message": "..."}
   */
  login: async (credentials: LoginRequest): Promise<ApiResponse<BackendAuthResponse>> => {
    try {
      const response = await apiClient.post<BackendAuthResponse>('/lego/login', credentials);

      return {
        success: response.data.status === 'OK',
        data: response.data,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Login failed',
      };
    }
  },

  /**
   * Register new user
   * POST /lego/register
   * Backend returns: {"status": "OK/ERROR", "message": "..."}
   */
  register: async (data: RegisterRequest): Promise<ApiResponse<BackendAuthResponse>> => {
    try {
      const response = await apiClient.post<BackendAuthResponse>('/lego/register', data);

      return {
        success: response.data.status === 'OK',
        data: response.data,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : 'Registration failed',
      };
    }
  },
};
