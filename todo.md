# TODO

## Features

### Visuals

- [x] basic sdl drawing code
- [x] player health bar
- [x] add ability to have moving healthbars e.g. follow enemies
- [x] add shadow sprites
- [ ] simple particle system - avoid any kind of physics or collisions (in progress)
  - [ ] add "trail" effect for projectiles
  - [ ] smoke effect (in progress)
- [ ] add crosshair (in progress)

### Gameplay

- [x] projectiles and basic entity handling
- [x] add burning effect
- [x] add melee weapons
- [x] add dodge roll with iframes
- [x] spell cooldown with 3 charges for something interesting
- [ ] convert unit vector for velocity to floating point (in progress)
- [ ] damage can haves a "push" effect (in progress)
- [ ] Create generic "skill/spell" system
- [ ] Should enemies have iFrames at all??


### Controls

- [x] simple input
- [x] add mouse support
- [ ] rework player controls (in progress)
  - [ ] crosshair can be moved with arrowkeys as well
  - [ ] account for offset when aiming with crosshair
  - [ ] should projectiles only follow as far as the crosshair?? 

## Engine/Refactor

- [x] framerate independant update
- [x] refactor into seperate files. game class, player class, etc.
- [x] abstract projectile handling to ProjectileManager class
- [x] create base class for enemies to inherit from
- [x] abstract enemy handling to EnemyManager class
- [x] move responsibility of creating projectiles to the ProjectileManager
- [x] move responsibility of creating enemies to the EnemyManager
- [x] aabb collision detection
- [x] font for ui and debugging purposes (bitmap font)
- [x] Player and Enemy classes to inherit from a BaseDamagable class
- [x] create base UI object
- [x] move responsibility of creating ui objects to the UIManager
- [x] remove Engine class and just consolodate everything into Game
- [ ] resource manager (in progress)
  - [x] support texture loading and retrieval
- [ ] implement ttf fonts (SDL_ttf or freetype) ***PRIORITY***
- [ ] implement actual image library (SDL_image or stb_image)
- [ ] implement audio (OpenAL or SDL_Mixer)
- [ ] controller support (probably will wait for native support of usb devices on WSL2)

## Backlog

- [ ] poison effect
- [ ] more enemy types/abilities
- [ ] gamestates - pausing, menu?
- [ ] upgrades - system for adding extra abilities to the player
- ~~[ ] proper aabb collision response i.e. sliding response~~
