# CvedixLego - Visual Flow-Based AI Video Analytics Pipeline Platform

A visual, drag-and-drop interface for building computer vision pipelines using React, TypeScript, and ReactFlow.

## 🚀 Features

- **Visual Pipeline Builder**: Drag-and-drop nodes to create complex CV pipelines
- **Real-time Execution**: Monitor pipeline execution with live metrics
- **Multiple Node Types**:
  - Source Nodes: Video File
  - Processing Nodes: Face Detection (AI-powered)
  - Output Nodes: JSON Output
- **Pipeline Management**: Save and load pipelines as JSON files
- **DAG Validation**: Automatic cycle detection and connection validation
- **Multiple Streaming Options**: SSE, WebSocket, and MQTT support (SSE mocked for MVP)

## 📦 Installation

```bash
npm install
```

## 🏃 Running the Application

### Development Mode

```bash
npm run dev
```

Open [http://localhost:5173](http://localhost:5173) in your browser.

### Production Build

```bash
npm run build
npm run preview
```

## 🎯 Quick Start Guide

1. **Login**: Click "Get Started" on the login page
2. **Build Pipeline**:
   - Drag **Video File** node from the left palette onto the canvas
   - Drag **Face Detection** node onto the canvas
   - Drag **JSON Output** node onto the canvas
3. **Connect Nodes**: Click and drag from the green output port to the blue input port
4. **Configure Nodes**: Click on any node to see configuration options on the right panel
5. **Save Pipeline**: Click "Save" button to export as JSON
6. **Run Pipeline**: Click "Run" button to execute (mocked with real-time metrics)

## 📁 Project Structure

```
src/
├── api/                    # API clients and mock data
│   ├── client.ts           # Axios instance with mock/real toggle
│   ├── nodes.api.ts        # Node API endpoints
│   ├── pipeline.api.ts     # Pipeline CRUD operations
│   └── mock/               # Mock data (3 node schemas)
│
├── service/                # Service layer with React Query hooks
│   ├── node.service.ts     # Node fetching service
│   ├── pipeline.service.ts # Pipeline operations (start/stop)
│   ├── stream.service.ts   # Streaming status updates
│   └── providers/          # Streaming providers (SSE, WebSocket, MQTT)
│
├── models/                 # TypeScript type definitions
│   ├── node.types.ts       # Node, NodeSchema, NodeConfig
│   ├── pipeline.types.ts   # Pipeline, PipelineStatus, Metrics
│   ├── connection.types.ts # Connection validation
│   └── api.types.ts        # API request/response types
│
├── components/
│   ├── flow/               # Flow-related components
│   │   ├── FlowCanvas/     # Main ReactFlow canvas
│   │   ├── nodes/          # Custom node components (Source, Processing, Output)
│   │   ├── NodePalette/    # Left sidebar with draggable nodes
│   │   ├── ConfigPanel/    # Right sidebar for node configuration
│   │   └── Toolbar/        # Top toolbar with pipeline operations
│   └── ui/                 # shadcn/ui components (Button, Input, Select, etc.)
│
├── pages/                  # Page components
│   ├── LoginPage/          # Landing page with "Get Started"
│   └── HomePage/           # Main app with three-panel layout
│
├── store/                  # Redux Toolkit store
│   ├── pipelineSlice.ts    # Pipeline state (nodes, connections, status)
│   └── uiSlice.ts          # UI state (selected node, panels)
│
├── hooks/                  # Custom React hooks
│   └── useNodeRegistry.ts  # Node type registry and factory
│
├── utils/                  # Utility functions
│   ├── validation.ts       # DAG validation, cycle detection
│   ├── serialization.ts    # Pipeline JSON import/export
│   └── constants.ts        # App constants (colors, spacing)
│
└── styles/                 # Global styles
    └── globals.css         # Tailwind + dark theme variables
```

## 🎨 Available Node Types

### 1. Video File (Source)

- **Purpose**: Load video from disk for processing
- **Configuration**:
  - File Path: Path to video file
  - Loop Playback: Repeat video when it ends
  - Start Frame: Frame to start from
  - FPS: Playback frame rate

### 2. Face Detection (Processing)

- **Purpose**: Detect and track faces in video frames
- **Configuration**:
  - Model: Haar Cascade (Fast) or DNN (Accurate)
  - Threshold: Confidence score (0.0 - 1.0)
  - Tracking: Enable face tracking across frames
  - Min Face Size: Ignore faces smaller than N pixels
  - Max Faces: Limit number of faces per frame
  - Draw Bounding Boxes: Visualize detections

### 3. JSON Output (Output)

- **Purpose**: Export detection results as JSON
- **Configuration**:
  - Output Path: Where to save JSON file
  - Format: Compact or Pretty
  - Include Metadata: Add timestamps and frame IDs

## 🔧 Architecture Highlights

### State Management

- **Redux Toolkit**: Pipeline data (nodes, connections, execution state)
- **React Query**: Server state (node schemas, API caching)
- **Local State**: UI interactions and form inputs

### Streaming Architecture

The application supports multiple streaming protocols:

- **SSE (Server-Sent Events)**: Primary for MVP - simple, automatic reconnection
- **WebSocket**: Future - bidirectional, low latency
- **MQTT**: Future - IoT integration, pub/sub pattern

Current implementation uses MockSSEProvider that simulates real-time updates.

### Connection Validation

- **Type Compatibility**: Validates data types match (video → video, detections → detections)
- **Cycle Detection**: Prevents cycles using DFS algorithm (DAG validation)
- **Duplicate Prevention**: Blocks duplicate connections between same ports

## 🎭 Mock API

All API calls are currently mocked with realistic delays (300-500ms). Toggle between mock and real API:

```typescript
// src/api/client.ts
export const USE_MOCK_API = true; // Set to false when backend is ready
```

## 🔌 Connecting to Real Backend

When C++ backend is ready:

1. Set `USE_MOCK_API = false` in `src/api/client.ts`
2. Configure backend URL:
   ```typescript
   baseURL: import.meta.env.VITE_API_BASE_URL || "http://localhost:8080";
   ```
3. Add `.env` file:
   ```
   VITE_API_BASE_URL=http://your-backend-url:port
   ```

## 🎨 Customization

### Adding New Node Types

1. **Define Node Schema** in `src/api/mock/nodes.mock.ts`:

   ```typescript
   {
     type: 'custom-node',
     category: NodeCategory.PROCESSING,
     name: 'Custom Node',
     icon: '🎯',
     inputs: [...],
     outputs: [...],
     configSchema: [...],
     defaultConfig: {...}
   }
   ```

2. Node will automatically appear in palette and be fully functional!

### Theme Customization

Edit `src/styles/globals.css` to modify dark theme colors:

```css
:root {
  --background: 222.2 84% 4.9%;
  --foreground: 210 40% 98%;
  /* ... more variables */
}
```

## 📊 Technologies Used

- **React 18** - UI framework
- **Vite 5** - Build tool
- **TypeScript** - Type safety
- **ReactFlow** - Node-based editor
- **Redux Toolkit** - State management
- **React Query** - Server state & caching
- **Tailwind CSS** - Styling
- **shadcn/ui** - UI components (Radix UI)
- **Axios** - HTTP client

## 🐛 Known Limitations (MVP)

- Authentication is mocked (just a "Get Started" button)
- All API calls are mocked with fake data
- Streaming uses mock intervals instead of real WebSocket/SSE
- Only 3 node types implemented (more coming soon)
- No actual video processing (backend integration needed)

## 🚧 Future Enhancements

- [ ] Additional node types (RTSP Camera, Object Detection, MQTT Publisher, etc.)
- [ ] Real backend API integration
- [ ] Actual WebSocket/SSE streaming
- [ ] Video preview in canvas
- [ ] Pipeline templates library
- [ ] Multi-user collaboration
- [ ] Pipeline debugger with execution logs
- [ ] Node search and filtering
- [ ] Undo/redo functionality
- [ ] Keyboard shortcuts

---

Built with ❤️ using React + ReactFlow
