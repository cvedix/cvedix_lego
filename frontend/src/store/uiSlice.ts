import { createSlice, PayloadAction } from '@reduxjs/toolkit';

interface UIState {
  selectedNodeId: string | null;
  isPanelOpen: boolean;
  isLoading: boolean;
  notification: {
    message: string;
    type: 'success' | 'error' | 'info' | 'warning';
  } | null;
  // Modal states
  modals: {
    videoSelection: {
      open: boolean;
      nodeId: string | null;
    };
    rtmpStream: {
      open: boolean;
      rtmpUrl: string | null;
    };
  };
}

const initialState: UIState = {
  selectedNodeId: null,
  isPanelOpen: true,
  isLoading: false,
  notification: null,
  modals: {
    videoSelection: {
      open: false,
      nodeId: null,
    },
    rtmpStream: {
      open: false,
      rtmpUrl: null,
    },
  },
};

const uiSlice = createSlice({
  name: 'ui',
  initialState,
  reducers: {
    selectNode: (state, action: PayloadAction<string | null>) => {
      state.selectedNodeId = action.payload;
      // Open panel when a node is selected
      if (action.payload) {
        state.isPanelOpen = true;
      }
    },

    togglePanel: (state) => {
      state.isPanelOpen = !state.isPanelOpen;
    },

    setLoading: (state, action: PayloadAction<boolean>) => {
      state.isLoading = action.payload;
    },

    showNotification: (
      state,
      action: PayloadAction<{
        message: string;
        type: 'success' | 'error' | 'info' | 'warning';
      }>
    ) => {
      state.notification = action.payload;
    },

    hideNotification: (state) => {
      state.notification = null;
    },

    // Video selection modal
    openVideoSelectionModal: (state, action: PayloadAction<string>) => {
      state.modals.videoSelection.open = true;
      state.modals.videoSelection.nodeId = action.payload;
    },

    closeVideoSelectionModal: (state) => {
      state.modals.videoSelection.open = false;
      state.modals.videoSelection.nodeId = null;
    },

    // RTMP stream modal
    openRtmpStreamModal: (state, action: PayloadAction<string>) => {
      state.modals.rtmpStream.open = true;
      state.modals.rtmpStream.rtmpUrl = action.payload;
    },

    closeRtmpStreamModal: (state) => {
      state.modals.rtmpStream.open = false;
      state.modals.rtmpStream.rtmpUrl = null;
    },
  },
});

export const {
  selectNode,
  togglePanel,
  setLoading,
  showNotification,
  hideNotification,
  openVideoSelectionModal,
  closeVideoSelectionModal,
  openRtmpStreamModal,
  closeRtmpStreamModal,
} = uiSlice.actions;

export default uiSlice.reducer;
