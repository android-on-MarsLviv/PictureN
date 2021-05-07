package com.example.picturen;

import android.util.Log;

import androidx.annotation.NonNull;

public class NativeCamera implements Camera {
    private static final String TAG = NativeCamera.class.getSimpleName();

    static { System.loadLibrary("capture-lib"); }

    public native byte[] capture();

    @Override
    public void capture(@NonNull CameraCallback captureCallback) {
        Log.i(TAG, "capture");

        byte[] frame = capture();

        captureCallback.onCaptureSucceed(frame);
    }
}
