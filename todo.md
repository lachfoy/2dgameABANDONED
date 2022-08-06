# TODO

## Features

### Visuals

- [x] basic sdl drawing code
- [ ] simple particle system - avoid any kind of physics or collisions
  - [ ] add "trail" effect for projectiles
  - [ ] smoke effect (in progress)
- [ ] add crosshair (in progress)

### Gameplay

- [x] projectiles and basic entity handling
- [x] add burning effect
- [ ] convert unit vector for velocity to floating point (in progress)
- [ ] damage can haves a "push" effect (in progress)
- [ ] Create generic "skill" system

### Controls

- [x] simple input
- [x] add mouse support

- [ ] rework player controls -- twinstick shooter style (in progress) -- make sure crosshair can be moved with arrowkeys as well

## Refactor

- [x] framerate independant update
- [x] refactor into seperate files. game class, player class, etc.
- [x] abstract projectile handling to ProjectileManager class
- [x] create base class for enemies to inherit from
- [x] abstract enemy handling to EnemyManager class
- [x] move responsibility of creating projectiles to the ProjectileManager
- [x] move responsibility of creating enemies to the EnemyManager
- [x] Player and Enemy classes to inherit from a BaseDamagable class
- [x] move responsibility of creating ui objects to the UIManager

- [ ] resource manager (in progress)
- [ ] remove Engine class and just consolodate everything into Game

## Backlog

- [ ] poison effect
- [ ] more enemy types/abilities
- [ ] gamestates - pausing, menu?
- [ ] upgrades - system for adding extra abilities to the player

- [ ] implement actual image library (SDL_image or stb_image)
- [ ] implement ttf fonts (SDL_ttf or freetype)
- [ ] implement audio (OpenAL or SDL_Mixer)
- [ ] controller support - probably will wait for native support of usb devices on WSL2
- [ ] ~~proper aabb collision response i.e. sliding response~~


# //////// ignore
## Done (or done enough)



- [x] aabb collision detection
- [x] font for ui and debugging purposes (bitmap font) (in future) refine font renderering by having different spacing per glyph
- [x] player health bar (in future) animate healthbar similar to souls games


- [x] make healthbar more general purpose (kinda still very messy)
- [x] add ability to have moving healthbars e.g. follow enemies
- [x] create base UI object and 'UI Object Manager'

- [x] think about how to handle damage and resistances
- [x] better(ish) enemy AI
- [x] add melee weapons
- [x] add dodge roll with iframes

- [x] better organised debug drawing
- [x] add shadow sprites

