import { NodeSchema, NodeCategory } from '@/models';

export const mockNodeSchemas: NodeSchema[] = [
  // VIDEO FILE SOURCE NODE
  {
    type: 'video-file',
    category: NodeCategory.SOURCE,
    name: 'Video File',
    description: 'Load video from disk for processing',
    icon: '🎥',
    version: '1.0.0',
    inputs: [],
    outputs: [
      {
        id: 'video-output',
        type: 'output',
        dataType: 'video',
        label: 'Video Stream',
        required: false,
      },
    ],
    configSchema: [
      {
        key: 'filePath',
        label: 'File Path',
        type: 'text',
        defaultValue: '/path/to/video.mp4',
        validation: { required: true },
        helpText: 'Path to the video file',
      },
      {
        key: 'loop',
        label: 'Loop Playback',
        type: 'toggle',
        defaultValue: false,
        helpText: 'Repeat video when it ends',
      },
      {
        key: 'startFrame',
        label: 'Start Frame',
        type: 'number',
        defaultValue: 0,
        validation: { min: 0 },
        helpText: 'Frame to start playback from',
      },
      {
        key: 'fps',
        label: 'Frames Per Second',
        type: 'number',
        defaultValue: 30,
        validation: { required: true, min: 1, max: 120 },
        helpText: 'Playback frame rate',
      },
    ],
    defaultConfig: {
      filePath: '/path/to/video.mp4',
      loop: false,
      startFrame: 0,
      fps: 30,
    },
    resourceRequirements: {
      cpu: 1,
      memory: 256,
    },
  },

  // FACE DETECTION PROCESSING NODE
  {
    type: 'face-detection',
    category: NodeCategory.PROCESSING,
    name: 'Face Detection',
    description: 'Detect and track faces in video frames using AI models',
    icon: '😊',
    version: '1.0.0',
    inputs: [
      {
        id: 'video-input',
        type: 'input',
        dataType: 'video',
        label: 'Video Stream',
        required: true,
      },
    ],
    outputs: [
      {
        id: 'detections-output',
        type: 'output',
        dataType: 'detections',
        label: 'Face Detections',
        required: false,
      },
      {
        id: 'annotated-video',
        type: 'output',
        dataType: 'video',
        label: 'Annotated Video',
        required: false,
      },
    ],
    configSchema: [
      {
        key: 'model',
        label: 'Detection Model',
        type: 'select',
        defaultValue: 'DNN',
        options: [
          { label: 'Haar Cascade (Fast)', value: 'haar' },
          { label: 'DNN (Accurate)', value: 'DNN' },
        ],
        validation: { required: true },
        helpText: 'Choose between speed (Haar) or accuracy (DNN)',
      },
      {
        key: 'threshold',
        label: 'Confidence Threshold',
        type: 'number',
        defaultValue: 0.7,
        validation: { required: true, min: 0, max: 1 },
        helpText: 'Minimum confidence score (0.0 - 1.0)',
      },
      {
        key: 'tracking',
        label: 'Enable Face Tracking',
        type: 'toggle',
        defaultValue: true,
        helpText: 'Track faces across frames for consistent IDs',
      },
      {
        key: 'minFaceSize',
        label: 'Minimum Face Size (px)',
        type: 'number',
        defaultValue: 30,
        validation: { required: true, min: 10, max: 500 },
        helpText: 'Ignore faces smaller than this size',
      },
      {
        key: 'maxFaces',
        label: 'Maximum Faces per Frame',
        type: 'number',
        defaultValue: 10,
        validation: { min: 1, max: 100 },
        helpText: 'Limit number of faces to detect',
      },
      {
        key: 'drawBoundingBoxes',
        label: 'Draw Bounding Boxes',
        type: 'toggle',
        defaultValue: true,
        helpText: 'Draw boxes around detected faces',
      },
    ],
    defaultConfig: {
      model: 'DNN',
      threshold: 0.7,
      tracking: true,
      minFaceSize: 30,
      maxFaces: 10,
      drawBoundingBoxes: true,
    },
    resourceRequirements: {
      cpu: 2,
      gpu: 0.5,
      memory: 512,
    },
  },

  // JSON OUTPUT NODE
  {
    type: 'json-output',
    category: NodeCategory.OUTPUT,
    name: 'JSON Output',
    description: 'Export detection results as JSON file',
    icon: '📄',
    version: '1.0.0',
    inputs: [
      {
        id: 'detections-input',
        type: 'input',
        dataType: 'detections',
        label: 'Detection Data',
        required: true,
      },
    ],
    outputs: [],
    configSchema: [
      {
        key: 'outputPath',
        label: 'Output Path',
        type: 'text',
        defaultValue: '/output/detections.json',
        validation: { required: true },
        helpText: 'Where to save the JSON file',
      },
      {
        key: 'format',
        label: 'Format',
        type: 'select',
        defaultValue: 'pretty',
        options: [
          { label: 'Compact', value: 'compact' },
          { label: 'Pretty', value: 'pretty' },
        ],
        helpText: 'JSON formatting style',
      },
      {
        key: 'includeMetadata',
        label: 'Include Metadata',
        type: 'toggle',
        defaultValue: true,
        helpText: 'Include timestamps and frame IDs',
      },
    ],
    defaultConfig: {
      outputPath: '/output/detections.json',
      format: 'pretty',
      includeMetadata: true,
    },
    resourceRequirements: {
      cpu: 0.5,
      memory: 128,
    },
  },
];
