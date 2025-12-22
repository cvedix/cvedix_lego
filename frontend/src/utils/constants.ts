// Node category colors - Industrial/Mechanical theme
export const NODE_COLORS = {
  source: {
    bg: 'bg-blue-50',
    border: 'border-blue-500',
    text: 'text-blue-700',
    accent: 'bg-blue-500',
  },
  processing: {
    bg: 'bg-indigo-50',
    border: 'border-indigo-500',
    text: 'text-indigo-700',
    accent: 'bg-indigo-500',
  },
  output: {
    bg: 'bg-cyan-50',
    border: 'border-cyan-500',
    text: 'text-cyan-700',
    accent: 'bg-cyan-500',
  },
  hidden: {
    bg: 'bg-gray-50',
    border: 'border-gray-500',
    text: 'text-gray-700',
    accent: 'bg-gray-500',
  },
};

// Pipeline status colors
export const STATUS_COLORS = {
  idle: 'text-gray-500',
  starting: 'text-yellow-600',
  running: 'text-green-600',
  paused: 'text-blue-600',
  stopping: 'text-yellow-600',
  stopped: 'text-gray-500',
  error: 'text-red-600',
};

// Default node spacing
export const NODE_SPACING = {
  width: 200,
  height: 100,
  gap: 50,
};
