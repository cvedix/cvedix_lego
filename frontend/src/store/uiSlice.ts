import { createSlice, PayloadAction } from '@reduxjs/toolkit';

interface UIState {
  selectedNodeId: string | null;
  isPanelOpen: boolean;
  isLoading: boolean;
  notification: {
    message: string;
    type: 'success' | 'error' | 'info' | 'warning';
  } | null;
}

const initialState: UIState = {
  selectedNodeId: null,
  isPanelOpen: true,
  isLoading: false,
  notification: null,
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
  },
});

export const { selectNode, togglePanel, setLoading, showNotification, hideNotification } = uiSlice.actions;

export default uiSlice.reducer;
