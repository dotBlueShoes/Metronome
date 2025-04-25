***DATE** : 26.04.2025* 

- git clone https://github.com/kcat/openal-soft
- cd @
- cmake .. -G "Visual Studio 17 2022" -DLIBTYPE=STATIC
- Open created `Visual Studio Solution` and then build the `OpenAL` solution

This should produce the static library. Additionally `AL_LIBTYPE_STATIC` define is required and the following libs have to be statically linked to:

- avrt.lib   # Audio-Visual Real-Time API for WASAPI
- ole32.lib  # OLE (Object Linking and Embedding)
- imm32.lib  # Input Method Manager API
- winmm.lib  # Windows Multimedia API for audio playback
