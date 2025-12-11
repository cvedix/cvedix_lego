import React from 'react';
import { useNavigate } from 'react-router-dom';
import { Button } from '@/components/ui/button';

export const LoginPage: React.FC = () => {
  const navigate = useNavigate();

  const handleGetStarted = () => {
    // Mock authentication - just store a token and navigate
    localStorage.setItem('auth_token', 'mock-token');
    navigate('/home');
  };

  return (
    <div className="min-h-screen flex items-center justify-center bg-gradient-to-br from-white via-blue-50 to-indigo-50">
      <div className="text-center space-y-12 p-8 max-w-5xl">
        {/* Logo */}
        <div className="space-y-6">
          <div className="flex items-center justify-center gap-3 mb-6">
            <div className="w-16 h-16 bg-gradient-to-br from-primary to-accent rounded-lg flex items-center justify-center shadow-lg">
              <span className="text-white font-bold text-2xl">CV</span>
            </div>
          </div>
          <h1 className="text-6xl font-bold bg-gradient-to-r from-blue-600 via-indigo-600 to-cyan-600 bg-clip-text text-transparent">
            CvedixLego
          </h1>
          <p className="text-xl text-gray-600 max-w-2xl mx-auto font-medium">
            Visual Flow-Based AI Video Analytics Pipeline Platform
          </p>
        </div>

        {/* Features */}
        <div className="grid grid-cols-1 md:grid-cols-3 gap-6 max-w-4xl mx-auto py-8">
          <div className="p-6 rounded-lg bg-white border-2 border-blue-200 hover:border-blue-400 transition-colors shadow-sm">
            <div className="w-12 h-12 bg-blue-100 rounded-lg flex items-center justify-center mb-3 mx-auto">
              <span className="text-2xl">🎥</span>
            </div>
            <h3 className="font-bold text-gray-900 mb-2">Video Processing</h3>
            <p className="text-sm text-gray-600">
              Process video streams with AI-powered analytics
            </p>
          </div>
          <div className="p-6 rounded-lg bg-white border-2 border-indigo-200 hover:border-indigo-400 transition-colors shadow-sm">
            <div className="w-12 h-12 bg-indigo-100 rounded-lg flex items-center justify-center mb-3 mx-auto">
              <span className="text-2xl">🔄</span>
            </div>
            <h3 className="font-bold text-gray-900 mb-2">Drag & Drop</h3>
            <p className="text-sm text-gray-600">
              Build pipelines visually with intuitive node-based interface
            </p>
          </div>
          <div className="p-6 rounded-lg bg-white border-2 border-cyan-200 hover:border-cyan-400 transition-colors shadow-sm">
            <div className="w-12 h-12 bg-cyan-100 rounded-lg flex items-center justify-center mb-3 mx-auto">
              <span className="text-2xl">⚡</span>
            </div>
            <h3 className="font-bold text-gray-900 mb-2">Real-time</h3>
            <p className="text-sm text-gray-600">
              Monitor pipeline execution with live metrics
            </p>
          </div>
        </div>

        {/* CTA Button */}
        <div>
          <Button
            size="lg"
            onClick={handleGetStarted}
            className="text-base px-10 py-6 h-auto font-semibold shadow-lg hover:shadow-xl transition-shadow"
          >
            Get Started →
          </Button>
        </div>
      </div>
    </div>
  );
};
