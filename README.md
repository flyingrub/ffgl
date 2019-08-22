This is the Resolume fork of the FFGL repository. It is up to date and has Visual Studio and Xcode projects to compile 32 bit and 64 bit plugins.

The master branch is FFGL 2.0. It is updated to be compatible with OpenGL 4.1 Core Profile. Plugins compiled with the master branch will work in Resolume 7.

To compile plugins for hosts that support FFGL 1.5 (Resolume 6, VDMX, COGE, Isadora, Magic Music Visuals), switch to the FFGL1.5 branch: https://github.com/resolume/ffgl/tree/ffgl1.5

### Plugins created
* Alea, the first plugin I realised. I tried to recreqte the animation of my website https://alea.xyz.
* Gradient, the conversion from the old plugin using the new framework.
* Polygon, allow to create repetition of polygon
* BGR, simpe plugin that inverse the Red and Blue value.
* Bloom, the more complex plugin. It allowed me to test the limit of the new framework. It is the translation from the bloom effect made by [keijiro](https://github.com/keijiro/KinoBloom) for Unity. It use multiples render passes.
* Dissolve, plugin using Perlin Noise. It allowed me to test the inclusion of code snippet in multiple plugin, so that you don't need to copy paste it each time.
* Scanline, plugin reproducing an old CRT TV screen.
* Screenshake, plugin reproducing the shaking of a camera.
* Strobobeat, stroboscope in sync with the host tempo, beat, and phase.
* Wobble, plugin that mimic the visual deformation of intoxication.
