package com.example.picturen;

public class FrameWriterFactory {
    enum Location {SD};

    public static FrameWriter create(Location location) {
        switch (location) {
            case SD:
                return new FrameWriterSD();
            default:
                return new FrameWriterSD();
        }
    }
}
