# Centipede Game

## Overview
This is a classic Centipede game developed using C++ and SFML (Simple and Fast Multimedia Library). The game features a player-controlled shooter, centipedes, mushrooms, and poison mushrooms, with added features for a more engaging gameplay experience.

## Features
- **Custom Fonts**: Custom fonts have been added for better visual appeal.
- **Dynamic Grid**: The game dynamically calculates grid positions for various game elements such as bullets and centipede segments.
- **Smooth Movement**: Objects in the game, including the player, bullets, and centipedes, move smoothly using SFML clock functions.
- **User Interaction**: Displays messages on the screen and waits for user input to start or proceed to the next level.
- **Different Textures**: Various textures for different game states, such as normal and poison mushrooms, and different centipede segments.

## Resources
- **Textures**: Place your textures in a folder named `Textures` within the game's root directory.
  - `player.png`: Player sprite.
  - `bullet.png`: Bullet sprite.
  - `mushroom1.png` to `mushroom4.png`: Mushroom sprites.
  - `poison1.png`, `poison2.png`: Poison mushroom sprites.
  - `walkL8.png`: Centipede segment sprite.
  - `headL3.png`, `headL4.png`: Centipede head sprites.
  - `bg1.jpg`: Background image.
- **Music**: Place your background music file `music.ogg` in a folder named `Music`.
- **Font**: Place your custom font `ARCADECLASSIC.TTF` in the game's root directory.

## Game Logic
### Initialization
- **Player**: Initialized at the center bottom of the screen.
- **Bullet**: Initialized just above the player.
- **Centipede**: Starts at the top of the screen and moves horizontally.
- **Mushrooms**: Randomly placed on the grid.
- **Poison Mushrooms**: Initialized randomly on the grid with special effects.
- **Small Segments**: Initialized off-screen and appear when needed.

### Drawing Functions
- **drawPlayer**: Draws the player sprite on the screen.
- **drawBullet**: Draws bullets fired by the player.
- **drawMushrooms**: Draws mushrooms on the screen.
- **drawPoisonMushrooms**: Draws poison mushrooms with different textures.
- **drawCentipede**: Draws the centipede and handles its movement and splitting.
- **drawSmall**: Draws small centipede segments when needed.

### Movement and Collision
- **moveBullet**: Handles bullet movement and checks for collisions.
- **moveCentipede**: Moves the centipede and handles collisions with mushrooms and bullets.
- **moveSmall**: Moves small centipede segments when they appear.
- **checkPlayerCollision**: Checks for collisions between the player and centipede or mushrooms.
- **checkBulletMushroomCollision**: Checks for collisions between bullets and mushrooms.
- **checkBulletSmallCollision**: Checks for collisions between bullets and small centipede segments.

## Game Flow
1. **Start Screen**: Displays a welcome message and waits for the player to press `S` to start.
2. **Gameplay**: The player controls the shooter, firing bullets at the centipede while avoiding or destroying mushrooms and poison mushrooms.
3. **Level Progression**: The game progresses to the next level when all centipede segments are destroyed. A message is displayed, and the game waits for the player to press `S` to start the next level.
4. **Game Over**: The game ends when the player loses all lives, displaying a game over message with the final score.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for any improvements or bug fixes.

## License
This project is licensed under the MIT License. See the LICENSE file for details.
