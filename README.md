# KoolBox (Kore Toolbox)
Experimental game-oriented toolkit for [Kore](https://github.com/Kode/Kore)

Adds some convenience, structure and basic functionality probably useful for games to the base Kore framework.

* Base implementation of a game class ("KoreGame") with convenient lifecycle callback hooks.
* Fast, flexible "opportunistic batching" drawing class (Gfx) to gather geometry into a batch and submit as one draw call only when relevant draw state changes.
* Convenient quad sprite rendering
* Support for rendering with arbitrary shaders, vertex formats, geometry (BYO triangle generation)
* Loading of [TexturePacker](https://www.codeandweb.com/texturepacker) XML atlases
* Scene structure

Currently comes with a sample scene that implements a BunnyMark style stress test.
Scores around 32,000 bunnies on an iPhone 6s using a non-optimised draw loop.


## Building
Check out source to your development machine.
Update the Kore submodules.
Use the standard Kore 'make' procedure to generate project files for your IDEs. 

Tested on MacOS and iOS.


**Highly experimental!**
Your comments and suggestions are welcome :)
