# THE LAST ENGINEER
![TLELogo](https://github.com/tom-bourjala/ISEN-ALG-TLE/assets/31037693/7abe1745-4aef-4cca-bcbe-cd65b518cb3d)

### By Tom BOURJALA, Rémi HOARAU, William DER KRIKORIAN
## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Innovations](#innovations)
- [Dependencies](#dependencies)
- [Future Improvements](#future-improvements)
- [License](#license)

## Overview
The Last Engineer (TLE) is a strategy game in the sub-genre of tower defense. In this game, your mission is to defend your point "heart" from waves of enemies using towers. The game ends when the "heart" is destroyed. The game also features procedurally generated start and arrival points, making every new game a unique experience.

## Features
- **Procedurally Generated Maps**: Our maps are diverse and generated on-the-fly, providing a new experience every time you play.
- **Defensible Heart Point**: If the "heart" is destroyed, the game ends.
- **Enemy Waves**: Face off against hordes of enemies in escalating difficulties.
- **Tower Mechanics**: Different towers with varying capabilities and applications.
- **Language Selection**: All languages are stored in spreadsheet format, accessible via a specific function.
- **Dynamic Camera System**: A dynamic camera is implemented for game rendering, allowing for zoom and panning over the grid.

## Architecture
Our team is divided into three main roles:
- **Project Manager**: Tom BOURJALA
- **Software Architect & Data Manager**: Rémi HOARAU
- **Graphic Designer, Game Designer, Wave Manager**: William DER KRIKORIAN

The project's architecture and data management are handled using GitHub for version control and collaboration. We utilize a branch-based workflow for efficient and conflict-free work progress.

## Innovations
Our game introduces several innovations, including:
- **Dynamic Texture Management**: Our libraries allow for accessing a texture by its name.
- **Enemy AI**: Enemies move based on their surrounding context such as nodes, borders, and other enemies.
- **Modular Interface**: We've built a library including sliders, panels, and buttons. All elements support effects on press, hover, and hold.
- **Dynamic Asset Management**: Enemies and towers can be added or removed without recompiling the game.
- **Adaptive Sound Engine**: A complete individual track management system, non-functional in the current build.

## Dependencies
The game is developed using the following tools and libraries:
- GitHub
- Visual Studio
- Discord
- Live Share
- Valgrind
- SDL2 (and libs)

## Future Improvements
We've identified several areas for future improvement:
- Allowing players to select and sell/upgrade towers.
- Adding new maps and their associated selections.
- Implementing sound effects modification in the options menu.
- Introducing a campaign/story mode with different maps and dialogues.

## License
Our project is open-source and is available under the [MIT license](https://opensource.org/licenses/MIT).
