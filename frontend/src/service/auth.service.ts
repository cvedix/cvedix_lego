// Auth service placeholder - to be implemented later
export const authService = {
  login: async (credentials: { username: string; password: string }) => {
    // Mock implementation
    console.log('Auth service: login called with', credentials);
    return { success: true, token: 'mock-token' };
  },

  logout: () => {
    localStorage.removeItem('auth_token');
  },

  isAuthenticated: () => {
    return !!localStorage.getItem('auth_token');
  },
};
