# 2D Hill Rider using GLUT

## 1. Project Information

**Project Name:** 2D Hill Rider using GLUT
**Project Type:** 2D Graphics Lab Game Project
**Programming Language:** C++
**Graphics Library:** OpenGL with FreeGLUT
**Development Environment:** Code::Blocks with MinGW
**Operating System:** Windows
**Window Size:** 1000 x 600 pixels

---

## 2. Group Members

- Member 1: Sushita Roy Chowdhury (ID: 233001412) 
- Member 2: Athkia Tabassum Chowdhury (ID: 233025212)

---

# 3. Project Introduction

2D Hill Rider using GLUT is a simple 2D driving game that was created as a graphics lab group project. This driving game is about the player driving a jeep over a hilly terrain. The player needs to travel as far as possible while managing fuel and time. The game includes hills, bridges, coins, fuel pickups, distance milestones, particle effects, moving camera, animated wheels, and a game over system. The project was developed using C++ with OpenGL and FreeGLUT. The majority of the objects within the game are created using basic OpenGL shapes like polygons, quads, circles, lines and triangles. The primary goal of the project is to show how 2D computer graphics concepts are applied together with animation, keyboard input, transformations, and some basic physics of the game.

---

# 4. Objectives of the Project

The main objectives of this project are:

* To create a 2D game using OpenGL and GLUT.
* To understand how a GLUT window and game loop work.
* To draw a complete vehicle using basic OpenGL shapes.
* To create a moving hilly terrain.
* To implement keyboard-based vehicle control.
* To add simple car movement and physics.
* To use rotation and translation transformations.
* To create a scrolling camera system.
* To implement coins and fuel pickups.
* To add time and fuel management.
* To create milestone rewards.
* To use particle effects for visual feedback.
* To display game information through a HUD.
* To implement a game over and restart system.

---

# 5. Development Environment

The project was developed using Code::Blocks with the MinGW C++ compiler on Windows. The project uses OpenGL and FreeGLUT for creating the game window, drawing the 2D objects, handling keyboard input, and controlling the animation. The main OpenGL or GLUT header used in the program is:

```cpp
#include <GL/glut.h>
```

The project was created as a C++ Console Application in Code::Blocks. The main source code is stored in:

```text
main.cpp
```
---

# 6. Dependencies

The following software and libraries are required to build and run the project:

* Windows operating system
* Code::Blocks
* MinGW C++ compiler
* OpenGL
* FreeGLUT
* FreeGLUT header files
* FreeGLUT library files
* FreeGLUT DLL

The source code uses the following headers:

```cpp
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
```

## 6.1 `windows.h`

This header is used for Windows-related definitions required by the OpenGL and GLUT setup.

## 6.2 `GL/glut.h`

This is the main GLUT header used by the project. It provides the GLUT and OpenGL functions used for creating the window, drawing objects, keyboard input, and the main program loop.

## 6.3 `math.h`

This header is used for mathematical functions such as:

```cpp
sin()
cos()
atan2()
fabs()
floor()
ceil()
fmod()
```

These functions are used in terrain calculations, wheel drawing, car rotation, animation, and physics.

## 6.4 `stdlib.h`

This header provides functions such as:

```cpp
rand()
srand()
exit()
```

Random number generation is used for different game elements and effects.

## 6.5 `stdio.h`

This header is used for `sprintf()`. It is used to create text displayed in the game, for example:

```text
TIME: 42s
```

and:

```text
300m
```

## 6.6 `string.h`

This header is used for `strncpy()`. It is used when copying text into fixed-size character arrays for floating messages and bonus messages.

## 6.7 `string`

The C++ `string` library provides `std::string`. It is used by the floating text system so that messages can be passed easily to:

```cpp
spawnFloatingText()
```

---

# 7. FreeGLUT Setup on Windows

FreeGLUT needs to be configured before building the project. A MinGW-compatible FreeGLUT package can be downloaded from:

https://www.songho.ca/opengl/gl_freeglut.html

The package used for this setup is:

```text
freeglut-mingw-3.8.0.zip
```

After extracting the package, the main folders are:

```text
bin
include
lib
```

## 7.1 Extract FreeGLUT

Extract the ZIP file to an easy location, for example:

```text
C:\freeglut
```

## 7.2 Copy Header Files

1. Open:

```text
C:\freeglut\include\GL\
```

2. Copy the required files to:

```text
C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\include\GL\
```

If the `GL` folder does not exist, create it.

## 7.3 Copy Library Files

1. Open:

```text
C:\freeglut\lib\x64\
```

2. Copy the required library files to:

```text
C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\lib\
```

## 7.4 Copy FreeGLUT DLL

1. Open:

```text
C:\freeglut\bin\x64\
```

2. Find:

```text
libfreeglut.dll
```

3. For the Windows setup used during development, the DLL can be copied to:

```text
C:\Windows\System32\
```

Another option is to place the DLL beside the generated `.exe` file. The DLL is required when the program starts.

---

# 8. Creating the Code::Blocks Project

The project was created in Code::Blocks using the following steps:

1. Open Code::Blocks.
2. Select `File`.
3. Select `New`.
4. Select `Project`.
5. Select `Console Application`.
6. Select `C++`.
7. Set the project name to:

```text
HillRider
```

8. Create the project.
9. Open the generated `main.cpp`.
10. Remove the default sample code.
11. Add the complete Hill Rider source code.
12. Configure the required FreeGLUT and OpenGL libraries.

---

# 9. Linker Settings

The required libraries are added in Code::Blocks. 

1. Go to:

```text
Settings
-> Compiler
-> Linker Settings
```

2. Add the following options under `Other linker options`:

```text
-lfreeglut
-lopengl32
-lglu32
```

These libraries are required for the FreeGLUT, OpenGL, and GLU functions used by the project.

---

# 10. How to Build the Project

After FreeGLUT has been configured, the project can be built from Code::Blocks.

1. Open the `HillRider` project.
2. Open `main.cpp`.
3. Make sure the complete source code is present.
4. Check the FreeGLUT setup.
5. Check the linker settings.
6. Select:

```text
Build -> Build
```

or press:

```text
Ctrl + F9
```

If there are no compilation errors, Code::Blocks will generate the executable file. The executable is normally generated inside a folder such as:

```text
bin\Debug\
```
depending on the project settings.

---

# 11. How to Run the Project

The project can be run directly from Code::Blocks. Press:

```text
F9
```

This builds and runs the program. The game window is created with the title:

```text
Hill Rider
```

The logical game window size is:

```text
1000 x 600
```

The jeep appears on the terrain and the game can start immediately. The game can also be started by opening the generated `.exe` file from the output folder. When running the `.exe` directly, `libfreeglut.dll` must be available to Windows.

---

# 12. Game Controls

The game uses both normal keyboard keys and arrow keys.

| Key         | Action                                  |
| ----------- | --------------------------------------- |
| Right Arrow | Move forward                            |
| Left Arrow  | Move backward                           |
| Up Arrow    | Increase speed                          |
| Down Arrow  | Brake                                   |
| B           | Brake                                   |
| S           | Boost                                   |
| R           | Restart the game                        |
| ESC         | Exit the game                           |

The arrow keys are handled using GLUT special key callbacks. The `B` , `R` and `S` keys are handled using the normal keyboard callbacks.

---

# 13. How the Game Works

The game starts with the jeep at approximately:

```cpp
carX = 350.0f;
```

The initial game values include:

```text
Fuel = 100
Time = 60 seconds
Target Distance = 300 meters
Speed = 0
```

The player controls the jeep using the keyboard. When the player moves forward, the car position changes:

```cpp
carX += speed;
```

The travelled distance is calculated from the car's world position:

```cpp
distanceTravelled = (carX - 350.0f) * 0.05f;
```

The game continuously updates movement, fuel, time, terrain interaction, coins, fuel pickups, bridges, particles, and the HUD. The update process is controlled by the GLUT timer function.

---

# 14. Main Game Loop

The main game loop is implemented through:

```cpp
void timer(int value)
```

This function is called repeatedly using:

```cpp
glutTimerFunc(16, timer, 0);
```

The value `16` gives an update interval of approximately 16 milliseconds. During each update, the program performs several operations. The timer function:

1. Reduces the remaining time.
2. Reads keyboard input.
3. Changes the car speed.
4. Updates the car position.
5. Calculates travelled distance.
6. Reduces fuel.
7. Updates animation time.
8. Updates bridges.
9. Updates coin spawning.
10. Checks coins.
11. Updates fuel spawning.
12. Checks fuel pickups.
13. Checks distance targets.
14. Checks distance milestones.
15. Updates sparkle particles.
16. Updates floating text.
17. Checks game over conditions.
18. Creates dust particles.
19. Updates dust.
20. Updates wheel rotation.
21. Updates the camera.
22. Requests another screen redraw.

This makes the game continuously animated.

---

# 15. Keyboard Input

The project uses GLUT keyboard callbacks.

## 15.1 Normal Keyboard

The function:
```cpp
void keyboard(unsigned char key, int x, int y)
```
handles normal keys. The following keys are used:
```text
B / b
S / s
R / r
ESC
```

1. The `B` key activates the brake.
2. The `S` key activates the boost.
3. The `R` key resets the game.
4. The `ESC` key closes the program.

## 15.2 Keyboard Release

The function:
```cpp
void keyboardUp(unsigned char key, int x, int y)
```
sets the brake and boost states to false when the keys are released.

## 15.3 Arrow Keys

The function:
```cpp
void specialKeyDown(int key, int x, int y)
```
handles the arrow keys.

The corresponding boolean variables are changed:
```text
rightKey
leftKey
upKey
downKey
```

The function:
```cpp
void specialKeyUp(int key, int x, int y)
```
sets these variables back to false when the keys are released. This allows the game to know whether a key is currently being pressed.

---

# 16. Car Speed and Movement

The car speed is changed according to the keyboard input. For the right arrow:
```cpp
speed += 0.12f;
```

The forward speed is limited to:
```text
6.0
```

For the left arrow, the speed is reduced and can become negative up to:
```text
-4.0
```

The up arrow provides another acceleration:
```cpp
speed += 0.08f;
```

The down arrow reduces the speed. The brake key applies stronger braking. The boost key increases speed by:
```cpp
speed += 0.22f;
```

and the maximum boost speed is:
```text
10.0
```

When no movement key is pressed, the car gradually slows down instead of stopping immediately. This creates simple acceleration and deceleration behavior.

---

# 17. Fuel System

Fuel is an important part of the game. The initial fuel value is:

```text
100
```

Fuel decreases when the car is moving. The amount depends on the current speed:

```cpp
fuel -= 0.018f * speed;
```

Additional fuel is consumed when boost is active:

```cpp
fuel -= 0.040f * speed;
```

Fuel is limited so that it cannot become negative. The HUD displays the fuel percentage. The fuel bar also changes when fuel becomes low. When fuel is at or below 25 percent, the fuel bar flashes. If fuel reaches zero:
```cpp
triggerGameOver(false);
```
is called and the game ends.

---

# 18. Fuel Pickups

The game also contains fuel pickup objects. The project uses functions for the fuel system such as:
```cpp
initializeFuel()
updateFuelSpawning()
checkFuelPickups()
drawFuelPickups()
```
These functions are responsible for creating fuel pickups, checking them during gameplay, and drawing them on the screen. Fuel pickups allow the player to continue travelling without depending only on the starting fuel.

---

# 19. Coin System

Coins are collected during the game. The coin system contains functions such as:

```cpp
initializeCoins()
updateCoinSpawning()
checkCoins()
drawCoins()
```

These functions manage the creation, drawing, and collection of coins. The collected coin count is shown on the HUD. The coin icon is drawn near the left side of the screen and the current number of collected coins is displayed beside it.

---

# 20. Coin Milestones

The game contains special coin milestones. The first milestone starts at:
```text
100 coins
```

The next important milestone is:
```text
300 coins
```

When a coin milestone is reached, the game:

* Adds bonus coins.
* Restores fuel to 100.
* Adds 30 seconds to the remaining time.
* Creates a sparkle effect.

For the 100 and 300 coin milestones, a bonus message is displayed.
For example:
```text
100 COINS BONUS!
```
or:
```text
300 COINS BONUS!
```

The function responsible for this is:
```cpp
checkCoinMilestones()
```

The milestone system continues to increase the next milestone after each reward.

---

# 21. Distance System

The travelled distance is calculated from the car's position. The calculation is:
```cpp
distanceTravelled = (carX - 350.0f) * 0.05f;
```
The value is prevented from becoming negative. The HUD displays the current distance. The game also has a target distance.
Initially:
```text
Target = 300m
```
When the player reaches the current target, another 300 meters is added:
```cpp
targetDistance += 300.0f;
```
Therefore, the target continues to increase as the player progresses.

---

# 22. Distance Milestones

Distance milestones are checked by:
```cpp
checkDistanceMilestones()
```
The first distance milestone is:
```text
1000m
```
After reaching a milestone, the next milestone is increased by:
```text
1000m
```
At each distance milestone:

* 30 seconds are added.
* Fuel is restored to 100.
* Sparkle effects are created.
* A milestone message is displayed.

For example:
```text
1000m MILESTONE! +30s
```
The message is displayed using the bonus popup system.

---

# 23. Terrain System

The game is based on a hilly terrain. The car does not simply move on a flat surface. Its vertical position and rotation depend on the terrain under its wheels. The project uses terrain functions such as:
```cpp
getTerrainHeight()
getBaseTerrainHeight()
sampleGroundUnderWheel()
```

These functions are used to find the terrain height at different world positions. The car uses two wheels:

```text
Left Wheel
Right Wheel
```

The terrain height under both wheels is checked separately. The average of these values is used to determine the car's vertical position.

---

# 24. Car and Terrain Interaction

Inside `drawCar()`, the ground position under each wheel is calculated. 

For the left wheel:

```cpp
leftWheelX = carX - wheelDistance;
```

For the right wheel:

```cpp
rightWheelX = carX + wheelDistance;
```

The program checks whether each wheel is over a bridge gap. If it is a bridge gap, the bridge height is used. Otherwise, the normal terrain height is used. This makes the car able to interact with both normal terrain and bridges.

---

# 25. Car Suspension and Vertical Physics

The car has simple vertical physics.

The program calculates:

```cpp
desiredY
currentY
carVerticalVelocity
carVerticalOffset
```

The desired car height is based on the average ground position:

```cpp
desiredY = averageGround + 23.0f;
```

A spring-like force is then calculated:

```cpp
springForce = (desiredY - currentY) * 0.22f;
```

The vertical velocity is updated using this force and a downward force. The velocity is also reduced using damping:

```cpp
carVerticalVelocity *= 0.84f;
```

This gives the car a small bouncing and suspension effect while moving over the terrain.

---

# 26. Car Rotation

The car rotation is calculated from the difference between the left and right wheel ground heights. The slope angle is calculated using:

```cpp
atan2(
    rightGround - leftGround,
    2.0f * wheelDistance
)
```

This value is converted from radians to degrees. When the car is on the ground, its rotation gradually moves toward the terrain slope:

```cpp
carAirRotation +=
    (slopeAngle - carAirRotation) * 0.15f;
```

This makes the car follow the hill angle.

---

# 27. Airborne Car Movement

The game also checks whether the car is in the air. If the vertical offset becomes large:

```cpp
if (carVerticalOffset > 7.0f)
    carInAir = true;
```

When the car comes close to the ground and its vertical velocity becomes small, it is considered to be on the ground again. While the car is in the air, its rotation changes according to the speed:

```cpp
carAirRotation += speed * 0.45f;
```

This gives the car a rotating movement while jumping over hills or gaps.

---

# 28. Wheel System

The wheels are drawn using the function:

```cpp
drawWheel()
```

Each wheel contains several parts:

* Outer dark tire
* Inner ring
* Light wheel surface
* Four spokes
* Center hub
* Outer rim line

The wheel is rotated using:

```cpp
glRotatef(rotation, 0, 0, 1);
```

The wheel rotation is updated in the timer:

```cpp
wheelRotation -= speed * 7.0f;
```

Therefore, the wheels rotate according to the car's movement.

---

# 29. Jeep Drawing

The complete jeep is drawn using the function:

```cpp
drawCar()
```

The jeep is made from several OpenGL shapes. The body uses polygons and quadrilaterals. The windows are drawn using dark and transparent shapes. The headlights are drawn using circles. The front and rear sections are made using lines and polygons.

The wheels are drawn using:

```cpp
drawWheel()
```

The car also has outlines to make the shape easier to see. Before drawing the car, the program uses:

```cpp
glPushMatrix();
```

Then the car is moved to its screen position using:

```cpp
glTranslatef(screenX, currentY, 0);
```

The car is rotated according to the terrain or air rotation. After drawing, the matrix is restored using:

```cpp
glPopMatrix();
```

This is an example of using OpenGL transformations in the project.

---

# 30. Camera System

The game uses a moving camera so that the player can continue travelling to the right without leaving the screen. The camera position is stored in:

```cpp
cameraX
```

The target camera position is calculated from the car position:

```cpp
targetCamera = carX - 400.0f;
```

The camera does not move instantly. Instead, it gradually moves toward the target:

```cpp
cameraX +=
    (targetCamera - cameraX) * 0.08f;
```

This gives smoother screen movement. World objects are converted to screen coordinates by subtracting `cameraX`. For example:

```cpp
screenX = worldX - cameraX;
```

---

# 31. Bridges

The game includes bridge sections. The bridge system uses functions such as:

```cpp
initializeBridges()
updateBridgePhysics()
drawBridges()
drawBridgeGaps()
isBridgeGap()
getBridgeHeight()
getBridgeWheelClearance()
```

These functions are used to create and draw bridge areas and to provide special height information for the car wheels. When a wheel is above a bridge gap, the program uses the bridge height instead of the normal terrain height. This allows the car to travel through areas where the normal terrain is interrupted.

---

# 32. Milestone Signs

The game includes distance signs placed along the terrain.

The function:

```cpp
drawMilestoneSigns()
```

creates signs at regular intervals.

The spacing is:

```cpp
const float milestoneSpacing = 750.0f;
```

The sign displays a distance value such as:

```text
750m
1500m
2250m
```

The sign is skipped if its position is inside a bridge gap. The sign contains a wooden post, a rectangular sign board, and distance text. This sign is in the code but not shown in window screen.

---

# 33. Coin and Fuel Collection Effects

The game provides visual feedback when important events happen. Sparkle particles are used for events such as:

* Coin milestone rewards
* Distance milestones
* Other reward effects

The function:

```cpp
spawnSparkleBurst()
```

creates multiple sparkle particles. These particles are updated by:

```cpp
updateSparkleParticles()
```

and drawn by:

```cpp
drawSparkleParticles()
```

---

# 34. Sparkle Particle System

The sparkle particle system uses arrays to store information about each particle. The particle system keeps values such as:

```text
X position
Y position
X velocity
Y velocity
Life
Maximum life
Size
Red value
Green value
Blue value
Active state
```

Only active particles are updated. The particle position changes according to its velocity:

```cpp
sparkleX[i] += sparkleVX[i];
sparkleY[i] += sparkleVY[i];
```

The vertical velocity is also changed:

```cpp
sparkleVY[i] -= 0.06f;
```

Velocity damping is applied:

```cpp
sparkleVX[i] *= 0.95f;
sparkleVY[i] *= 0.97f;
```

The particle life decreases over time. When the life reaches zero, the particle becomes inactive. The particle transparency depends on its remaining life.

---

# 35. Dust Particle System

Dust particles are created behind the wheels when the car is moving. The timer checks:

```cpp
fabs(speed) > 1.5f
```

and also checks that the car is not in the air. When these conditions are true, dust particles are created near both wheels. The functions used for this system include:

```cpp
initializeDust()
spawnDustParticle()
updateDustParticles()
drawDustParticles()
```

This gives a visual effect while the jeep is travelling on the terrain.

---

# 36. Floating Text System

The game has a floating text system for displaying short messages. The main functions are:

```cpp
initializeFloatingTexts()
spawnFloatingText()
updateFloatingTexts()
drawFloatingTexts()
```

Each floating text has:

* X position
* Y position
* Text
* Color
* Scale
* Life
* Maximum life
* Active state
* World-space state

The text moves upward over time:

```cpp
floatTextY[i] += 0.9f;
```

Its life decreases gradually. When the life reaches zero, the text becomes inactive. The text also becomes transparent as its life decreases.

---

# 37. Bonus Popup System

The HUD contains a larger bonus message system. The variable:

```cpp
bonusDisplayTimer
```

controls how long the message is visible. The message is shown in the center area of the screen. The popup also has:

* Scaling
* Fading
* Small movement
* Color
* Pulse animation

The pulse is calculated using:

```cpp
sin(animationTime * 14.0f)
```

This creates a small changing scale effect. The popup is used for coin and distance milestone messages.

---

# 38. HUD System

The HUD is drawn by:

```cpp
drawHUD()
```

The HUD shows the important game information while playing. It includes:

* Fuel icon
* Fuel bar
* Fuel percentage
* Coin icon
* Collected coins
* Current distance
* Progress bar
* Current time
* Target distance
* Target flag
* Best distance
* Trophy icon
* Milestone messages

The HUD is drawn using screen coordinates instead of world coordinates. This means that the HUD remains fixed while the camera moves through the game world.

---

# 39. Fuel Bar

The fuel bar is drawn using OpenGL quadrilaterals. The current fuel value is first limited between:

```text
0 and 100
```

The width of the filled part is calculated from the fuel percentage. When fuel is above 25 percent, the bar is shown normally. When fuel is 25 percent or lower, the bar flashes. The flashing is controlled using:

```cpp
fmod(animationTime * 4.0f, 2.0f)
```

This gives the player a warning that the fuel is low.

---

# 40. Distance Progress Bar

The HUD also contains a progress bar for the current target. The progress is calculated as:

```cpp
progress = distanceTravelled / targetDistance;
```

The value is limited between:

```text
0 and 1
```

A small circle is drawn on the progress line to show the current progress. The progress bar and other text are positioned around the center of the screen.

---

# 41. Time System

The game starts with:

```text
60 seconds
```

The timer decreases approximately every 16 milliseconds:

```cpp
timeLeft -= 0.016f;
```

The remaining time is displayed on the HUD. The time color changes when the remaining time becomes low. If the time is:

```text
More than 20 seconds
```

the normal HUD color is used. When the time is:

```text
20 seconds or less
```

the time becomes more noticeable. When the time reaches:

```text
10 seconds or less
```

a warning color is used. If the time reaches zero before the target distance is reached, the game ends.

---

# 42. Game Over System

The game has a separate game over state. The main variables are:

```cpp
gameOver
timeUp
```

The function:

```cpp
triggerGameOver(bool timedOut)
```

is responsible for ending the game. If the player reaches a new high score, it is stored in:

```cpp
highScore
```

The game over screen displays:

```text
GAME OVER
```

or:

```text
TIME UP! GAME OVER
```

depending on the reason for ending. It also displays:

* Final distance
* Best distance
* Total coins
* Restart instruction

The screen is darkened using a transparent black rectangle.

---

# 43. Game Over Conditions

There are two main game over conditions.

## 43.1 Fuel Empty

If:

```cpp
fuel <= 0.0f
```

the fuel is set to zero and the game ends. The game over reason is not time related.

## 43.2 Time Finished

If:

```cpp
timeLeft <= 0.0f
```

and the player has not reached the current target distance, the game ends because time has finished. The message becomes:

```text
TIME UP! GAME OVER
```

---

# 44. Restart System

The game can be restarted by pressing:

```text
R
```

The restart code resets the main game values.

For example:

```cpp
carX = 350.0f;
speed = 0.0f;
cameraX = 0.0f;
fuel = 100.0f;
distanceTravelled = 0.0f;
timeLeft = 60.0f;
targetDistance = 300.0f;
```

It also resets:

* Car vertical movement
* Car rotation
* Game over state
* Keyboard states
* Animation time
* Coins
* Fuel pickups
* Bridges
* Dust particles
* Sparkle particles
* Floating texts
* Coin milestones
* Distance milestones

The high score is not reset, so the previous best distance can still be displayed.

---

# 45. Main Functions and Their Purpose

The project contains several functions. The main functions and their purposes are listed below.

| Function                    | Purpose                                             |
| --------------------------- | --------------------------------------------------- |
| `init()`                    | Initializes OpenGL settings and game systems        |
| `main()`                    | Starts GLUT and registers callbacks                 |
| `display()`                 | Draws the complete game frame                       |
| `reshape()`                 | Sets the viewport and 2D projection                 |
| `timer()`                   | Updates the game continuously                       |
| `keyboard()`                | Handles normal keyboard keys                        |
| `keyboardUp()`              | Handles normal key release                          |
| `specialKeyDown()`          | Handles arrow key press                             |
| `specialKeyUp()`            | Handles arrow key release                           |
| `triggerGameOver()`         | Changes the game to game over state                 |
| `drawCar()`                 | Calculates car movement/rotation and draws the jeep |
| `drawWheel()`               | Draws each wheel                                    |
| `drawHUD()`                 | Draws all game information                          |
| `drawMilestoneSigns()`      | Draws distance signs                                |
| `drawTrophy()`              | Draws the trophy icon                               |
| `updateSparkleParticles()`  | Updates sparkle movement and life                   |
| `drawSparkleParticles()`    | Draws sparkle particles                             |
| `initializeFloatingTexts()` | Resets floating text objects                        |
| `spawnFloatingText()`       | Creates a floating message                          |
| `updateFloatingTexts()`     | Moves and fades floating text                       |
| `drawFloatingTexts()`       | Draws floating text                                 |
| `checkCoinMilestones()`     | Checks coin rewards                                 |
| `checkDistanceMilestones()` | Checks distance rewards                             |

There are also additional functions for terrain, bridges, coins, fuel, dust, and other game systems.

---

# 46. OpenGL Transformations Used

The project uses basic OpenGL transformations.

## Translation

The jeep is moved to its world/screen position using:

```cpp
glTranslatef()
```

## Rotation

The jeep and wheels are rotated using:

```cpp
glRotatef()
```

## Scaling

Floating text and the trophy use:

```cpp
glScalef()
```

## Matrix Management

The program uses:

```cpp
glPushMatrix()
glPopMatrix()
```

to apply transformations to individual objects without affecting other objects. These transformations are important parts of the 2D graphics implementation.

---

# 47. Blending and Transparency

The project uses OpenGL blending for transparent objects. Blending is enabled using:

```cpp
glEnable(GL_BLEND);
```

and the blending function is:

```cpp
glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
);
```

This is used for:

* Car window transparency
* Dust particles
* Sparkle particles
* Floating text
* Bonus popup
* Game over background

Alpha values are used to control transparency.

---

# 48. Anti-Aliasing

The program enables several OpenGL smoothing features:

```cpp
glEnable(GL_LINE_SMOOTH);
glEnable(GL_POLYGON_SMOOTH);
glEnable(GL_POINT_SMOOTH);
```

The project also uses:

```cpp
glEnable(GL_MULTISAMPLE);
```

These settings help make lines and shapes appear smoother.

---

# 49. Display Function

The main drawing function is:

```cpp
void display()
```

It first clears the screen:

```cpp
glClear(GL_COLOR_BUFFER_BIT);
```

Then the game objects are drawn in a specific order:

```text
Sky
Bridge gaps
Terrain
Bridges
Coins
Fuel pickups
Dust particles
Car
Sparkle particles
Floating texts
HUD
```

This drawing order is important because objects drawn later can appear in front of earlier objects. Finally, the double-buffered display is updated using:

```cpp
glutSwapBuffers();
```

---

# 50. Projection and Window Setup

The project uses a 2D orthographic projection. The projection is created using:

```cpp
gluOrtho2D(
    0,
    WINDOW_WIDTH,
    0,
    WINDOW_HEIGHT
);
```

This makes it easier to use screen-like coordinates for the 2D game. The window size is:

```text
1000 x 600
```

The `reshape()` function also resets the viewport and projection if the window is resized.

---

# 51. Main Program Setup

The `main()` function starts GLUT. It performs the following steps:

1. Initializes GLUT.
2. Sets the display mode.
3. Sets the initial window position.
4. Sets the window size.
5. Creates the window.
6. Calls `init()`.
7. Registers the display callback.
8. Registers keyboard callbacks.
9. Registers special key callbacks.
10. Registers the reshape callback.
11. Starts the timer.
12. Enters the GLUT main loop.

Important GLUT functions used include:

```cpp
glutInit()
glutInitDisplayMode()
glutInitWindowSize()
glutCreateWindow()
glutDisplayFunc()
glutKeyboardFunc()
glutKeyboardUpFunc()
glutSpecialFunc()
glutSpecialUpFunc()
glutReshapeFunc()
glutTimerFunc()
glutMainLoop()
```

---

# 52. Game Features

The main features of the game are:

1. 2D jeep driving.
2. Hilly terrain.
3. Moving camera.
4. Keyboard controls.
5. Forward and backward movement.
6. Acceleration and braking.
7. Boost system.
8. Simple suspension physics.
9. Car rotation according to terrain slope.
10. Air rotation.
11. Rotating wheels.
12. Coins.
13. Fuel pickups.
14. Fuel consumption.
15. Low fuel warning.
16. Time limit.
17. Increasing target distance.
18. Coin milestones.
19. Distance milestones.
20. Bonus time.
21. Fuel restoration at milestones.
22. Sparkle particle effects.
23. Dust particle effects.
24. Floating text.
25. Bonus popup messages.
26. Distance signs.
27. HUD.
28. Best distance tracking.
29. Game over screen.
30. Restart option.

---

# 55. Preview of the Output

The following screenshots should be added to the repository to show the final output.

## Starting Screen Screenshot

![Hill Rider Starting screen](https://github.com/sushita01/2D-Hill-Rider-using-GLUT/blob/main/starting_screen.PNG)

## Game Over Screenshot

![Hill Rider Game Over](https://github.com/sushita01/2D-Hill-Rider-using-GLUT/blob/main/gameover.PNG)

## Bridge Screen Screenshot

![Hill Rider Bridge](https://github.com/sushita01/2D-Hill-Rider-using-GLUT/blob/main/bridge_screen.PNG)

## GIF

A short GIF was also  added to show the jeep moving, collecting objects, and interacting with the terrain.

![Gameplay GIF]([screenshots/gameplay.gif](https://github.com/sushita01/2D-Hill-Rider-using-GLUT/blob/main/hillrider.gif))

---

# 56. Testing

The project was tested by running the program through Code::Blocks. The following parts were checked during testing:

* Program starts correctly.
* GLUT window opens.
* Jeep is visible.
* Arrow keys control the jeep.
* Brake works.
* Boost works.
* Wheels rotate.
* Camera follows the jeep.
* Terrain affects car rotation.
* Coins can be collected.
* Fuel decreases while driving.
* Fuel pickups work.
* Milestone rewards work.
* Sparkle effects appear.
* Dust effects appear.
* HUD updates during gameplay.
* Game over works when fuel reaches zero.
* Game over works when time finishes.
* Restart works using the `R` key.

---

# 57. Limitations

This project is a simple 2D graphics game made for a Graphics Lab project. Some limitations are:

* The graphics are created using basic OpenGL shapes.
* The physics is simplified and is not intended to be a real vehicle physics simulation.
* The game does not use a physics engine.
* The game does not contain a complex sound system.
* The game does not contain a large menu system.
* The game uses a fixed logical screen size of 1000 x 600.
* The game is designed for the Windows and Code::Blocks setup used during development.

These limitations are acceptable for the scope of this Graphics Lab project.

---

# 58. Possible Future Improvements

If the project is developed further, the following features could be added:

* More types of terrain.
* More bridge designs.
* More vehicle designs.
* Sound effects.
* Background music.
* Multiple levels.
* More types of obstacles.
* More detailed vehicle physics.
* A start menu.
* A pause menu.
* Additional game modes.
* More visual effects.
* Better texture-based graphics.
* Saveable high scores.

---

# 59. Conclusion

2D Hill Rider using GLUT is a 2D driving game developed using C++, OpenGL, and FreeGLUT. The project demonstrates several basic computer graphics concepts. It uses OpenGL primitives to draw the jeep, wheels, terrain-related objects, HUD elements, signs, particles, and other game objects. The project also includes keyboard interaction, object movement, rotation, scaling, transparency, animation, camera movement, and simple physics. The game has a fuel and time system, coins, fuel pickups, milestones, rewards, particle effects, and a game over system. The player needs to control the jeep and travel through the terrain while managing the available fuel and time. The project helped us understand how OpenGL and GLUT can be used to create an interactive 2D application with animation and user input.
