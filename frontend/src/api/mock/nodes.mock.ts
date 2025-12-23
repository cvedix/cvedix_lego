import { NodeSchema, NodeCategory, CvedixNodeType } from '@/models';

export const mockNodeSchemas: NodeSchema[] = [
  // SOURCE NODE: File Source
  {
    type: CvedixNodeType.FILE_SOURCE,
    category: NodeCategory.SOURCE,
    name: 'Video Source',
    description: 'Select or upload video file for processing',
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
        key: 'video_name',
        label: 'Video File',
        type: 'text',
        defaultValue: '',
        validation: { required: true },
        helpText: 'Selected video file name',
      },
    ],
    defaultConfig: {
      node_name: 'file_src',
      channel_index: 0,
      video_name: '',
      resize_ratio: 1.0,
      cycle: true,
      gst_decoder_name: 'avdec_h264',
      skip_interval: 0,
    },
  },

  // PROCESSING NODE: Tracker (contains tracker + analytics)
  {
    type: CvedixNodeType.TRACKER,
    category: NodeCategory.PROCESSING,
    name: 'Person Tracker',
    description: 'Track people in video stream',
    icon: '👤',
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
        id: 'tracking-output',
        type: 'output',
        dataType: 'tracking',
        label: 'Tracking Data',
        required: false,
      },
    ],
    configSchema: [],
    defaultConfig: {
      node_name: 'tracker_0',
    },
  },

  // OUTPUT NODE: RTMP Destination
  {
    type: CvedixNodeType.RTMP_DESTINATION,
    category: NodeCategory.OUTPUT,
    name: 'RTMP Stream',
    description: 'Stream output to RTMP server',
    icon: '📡',
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
    outputs: [],
    configSchema: [
      {
        key: 'rtmp_url',
        label: 'RTMP URL',
        type: 'text',
        defaultValue: 'rtmp://anhoidong.datacenter.cvedix.com:1935/live/stream',
        validation: { required: true },
        helpText: 'RTMP server URL for streaming',
      },
      {
        key: 'resolution_width',
        label: 'Width (px)',
        type: 'number',
        defaultValue: 640,
        validation: { min: 320, max: 1920 },
        helpText: 'Output video width',
      },
      {
        key: 'resolution_height',
        label: 'Height (px)',
        type: 'number',
        defaultValue: 360,
        validation: { min: 240, max: 1080 },
        helpText: 'Output video height',
      },
      {
        key: 'bitrate',
        label: 'Bitrate (kbps)',
        type: 'number',
        defaultValue: 1000,
        validation: { min: 100, max: 10000 },
        helpText: 'Video encoding bitrate',
      },
    ],
    defaultConfig: {
      node_name: 'rtmp_node',
      channel_index: 0,
      rtmp_url: 'rtmp://anhoidong.datacenter.cvedix.com:1935/live/stream',
      resolution_width: 640,
      resolution_height: 360,
      bitrate: 1000,
      osd: true,
      gst_encoder_name: 'x264enc',
    },
  },
];

// Hidden node templates (not shown in palette)
export const hiddenNodeTemplates = {
  [CvedixNodeType.FRAME_DECODER]: {
    type: CvedixNodeType.FRAME_DECODER,
    config: {
      node_name: 'decoder_0',
      channel_index: 0,
      gst_decoder_name: 'avdec_h264',
      output_format: 'BGR',
    },
  },
  [CvedixNodeType.PREPROCESS]: {
    type: CvedixNodeType.PREPROCESS,
    config: {
      node_name: 'preprocess_0',
      channel_index: 0,
      target_width: 640,
      target_height: 360,
      normalize: true,
      color_convert: 'BGR2RGB',
    },
  },
  [CvedixNodeType.ANALYTICS]: {
    type: CvedixNodeType.ANALYTICS,
    config: {
      node_name: 'analytics_0',
      rules: [
        {
          type: 'count',
          target_class: 'person',
          window_seconds: 60,
        },
        {
          type: 'crossline',
          line: [
            [100, 200],
            [500, 200],
          ],
          target_class: 'person',
        },
      ],
      emit_alerts: true,
    },
  },
};
