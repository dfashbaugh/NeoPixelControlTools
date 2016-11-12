# NeoPixel Tools

This repo contains a set of tools useful for mapping images to NeoPixel LEDs. 

## LED Video Mapper

This software uses uses OpenCV and a camera to map an arbitrary set of Neopixels into matrix. It then bins 
by a resolution chosen by the user (preserving or not preserving aspect ratio). The output is then dumped in a header
file that can be used with an Arduino to allow NeoPixel drawing with 2D mapping.

## RGB Neo Pixel Matrix Library

This library allows a system using UART or UDP to control a set of NeoPixels defined as a matrix. A microcontroller will be 
loaded with firmware based on the communication system the controller will use, and the controller will just communicate
matrices from PIL (Python Imaging Library) to draw images on the NeoPixels. 

Works great with Raspberry Pi and any laptops. 

Heavily inspired by and compatible with [hzeller's amazing Raspberry Pi RGB Matrix Library](https://github.com/hzeller/rpi-rgb-led-matrix)
