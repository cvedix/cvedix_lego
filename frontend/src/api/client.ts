import axios from 'axios';

export const apiClient = axios.create({
  baseURL: import.meta.env.VITE_API_BASE_URL || 'http://localhost:8090',
  timeout: 30000,
  headers: {
    'Content-Type': 'application/json',
  },
});

// Separate client for file uploads with longer timeout
export const uploadClient = axios.create({
  baseURL: import.meta.env.VITE_API_BASE_URL || 'http://localhost:8090',
  timeout: 300000, // 5 minutes for large video uploads
  headers: {
    'Content-Type': 'multipart/form-data',
  },
});

// Request interceptor for auth tokens
apiClient.interceptors.request.use((config) => {
  const token = localStorage.getItem('auth_token');
  if (token) {
    config.headers.Authorization = `Bearer ${token}`;
  }
  return config;
});

uploadClient.interceptors.request.use((config) => {
  const token = localStorage.getItem('auth_token');
  if (token) {
    config.headers.Authorization = `Bearer ${token}`;
  }
  return config;
});

// Response interceptor for error handling
const errorHandler = (error: any) => {
  console.error('API Error:', error);
  const message = error.response?.data?.message || error.message || 'An error occurred';
  return Promise.reject(new Error(message));
};

apiClient.interceptors.response.use((response) => response, errorHandler);
uploadClient.interceptors.response.use((response) => response, errorHandler);
