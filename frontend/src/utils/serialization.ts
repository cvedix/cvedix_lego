import { Pipeline } from '@/models';

// Serialize pipeline to JSON string
export const serializePipeline = (pipeline: Pipeline): string => {
  return JSON.stringify(pipeline, null, 2);
};

// Deserialize JSON string to pipeline
export const deserializePipeline = (json: string): Pipeline => {
  try {
    const pipeline = JSON.parse(json) as Pipeline;

    // Basic validation
    if (!pipeline.id || !pipeline.name || !Array.isArray(pipeline.nodes) || !Array.isArray(pipeline.connections)) {
      throw new Error('Invalid pipeline format');
    }

    return pipeline;
  } catch (error) {
    throw new Error(`Failed to parse pipeline: ${error instanceof Error ? error.message : 'Unknown error'}`);
  }
};

// Download pipeline as JSON file
export const downloadPipelineAsJson = (pipeline: Pipeline): void => {
  const json = serializePipeline(pipeline);
  const blob = new Blob([json], { type: 'application/json' });
  const url = URL.createObjectURL(blob);

  const link = document.createElement('a');
  link.href = url;
  link.download = `${pipeline.name.replace(/\s+/g, '_')}_${Date.now()}.json`;
  document.body.appendChild(link);
  link.click();
  document.body.removeChild(link);

  URL.revokeObjectURL(url);
};

// Upload and parse pipeline from JSON file
export const uploadPipelineFromJson = (file: File): Promise<Pipeline> => {
  return new Promise((resolve, reject) => {
    const reader = new FileReader();

    reader.onload = (event) => {
      try {
        const json = event.target?.result as string;
        const pipeline = deserializePipeline(json);
        resolve(pipeline);
      } catch (error) {
        reject(error);
      }
    };

    reader.onerror = () => {
      reject(new Error('Failed to read file'));
    };

    reader.readAsText(file);
  });
};
