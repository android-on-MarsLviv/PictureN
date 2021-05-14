package com.example.picturen;

import androidx.annotation.NonNull;

public interface FrameWriter {
    public void write(@NonNull byte[] frame, @NonNull FrameWriterCallback saveCallback);
}
