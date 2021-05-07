package com.example.picturen;

import android.util.Log;

import androidx.annotation.NonNull;

public class FrameWriterSD implements FrameWriter {
    private static final String TAG = FrameWriterSD.class.getSimpleName();
    @Override
    public void write(@NonNull byte[] frame, @NonNull FrameWriterCallback saveCallback) {
        Log.i(TAG, "write");
        // TODO: do the implementation
        saveCallback.onSuccessSave();
    }
}
