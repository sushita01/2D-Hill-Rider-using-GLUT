# 2D Hill Rider using GLUT

## 1. Project Information

**Project Name:** 2D Hill Rider using GLUT
**Project Type:** 2D Graphics and Interactive Game
**Programming Language:** C++
**Graphics Library:** OpenGL with GLUT
**Development Environment:** Code::Blocks with MinGW
**Platform:** Windows

### Group Members

- Member 1: Sushita Roy Chowdhury (ID: 233001412) 
- Member 2: Samiha Firoze (ID: 233025212)

## 2. Introduction

2D Hill Rider using GLUT is a small 2D driving game developed as a Graphics Lab Group Project.

The main idea of the project is to control a car moving through a hilly environment. The player needs to move the car forward, collect coins, collect fuel, cross bridges, and travel as far as possible before the fuel or time runs out.

The project is made using C++ and OpenGL/GLUT. The graphics are drawn using OpenGL primitives such as polygons, quads, triangles, lines, circles, and text.

The project includes animation, keyboard interaction, moving objects, camera movement, simple vehicle physics, particle effects, fuel and coin systems, distance milestones, a progress indicator, and a game-over system.

The purpose of this project is to demonstrate the use of GLUT and OpenGL concepts through an interactive 2D application.

---

# 3. Main Objectives

The main objectives of this project are:

1. To create an interactive 2D game using GLUT.
2. To draw the game environment using OpenGL primitives.
3. To create a moving car controlled by the keyboard.
4. To implement simple car movement and physics.
5. To create hills and uneven terrain.
6. To add coins and fuel pickups.
7. To add bridges and bridge gaps.
8. To implement camera movement following the car.
9. To add particle effects such as dust and sparkles.
10. To add floating text and milestone messages.
11. To create a fuel and time based game system.
12. To display game information through a HUD.
13. To implement a game-over and restart system.

---

# 4. Tools and Technologies Used

The following tools and technologies were used:

* C++
* OpenGL
* GLUT / FreeGLUT
* Code::Blocks
* MinGW
* Windows
* OpenGL immediate mode drawing functions

The program uses the GLUT library for creating the window, receiving keyboard input, and running the main game loop.

---

# 5. Development Environment

The project was developed using Code::Blocks with the MinGW compiler.

The FreeGLUT package used for the project is the MinGW version.

The FreeGLUT package contains:

* `include` files for OpenGL/GLUT headers
* `lib` files required during compilation
* `bin` files containing the required DLL

The project uses:

```cpp
#include <GL/glut.h>
```

This header provides the GLUT and OpenGL functions used in the program.

---

# 6. FreeGLUT Setup on Windows

Before building the project, FreeGLUT needs to be configured with Code::Blocks and MinGW.

A MinGW-compatible FreeGLUT package can be used for this purpose.

After extracting the FreeGLUT package, the required folders are:

```text
bin
include
lib
```

## 6.1 Copying the Header Files

Open:

```text
freeglut\include\GL\
```

Copy the required files into the MinGW OpenGL include folder:

```text
C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\include\GL\
```

If the `GL` folder does not exist, it can be created manually.

## 6.2 Copying the Library Files

Open the x64 library folder:

```text
freeglut\lib\x64\
```

Copy the required library files into:

```text
C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\lib\
```

## 6.3 FreeGLUT DLL

The program also needs the FreeGLUT DLL when running.

The DLL can be found in:

```text
freeglut\bin\x64\
```

The required file is:

```text
libfreeglut.dll
```

The DLL can be placed in:

```text
C:\Windows\System32\
```

Alternatively, for a repository-based project, the DLL can be placed beside the generated executable so that Windows can find it when the program starts.

---

# 7. Code::Blocks Project Setup

The project was created in Code::Blocks as a C++ Console Application.

The basic project creation process is:

1. Open Code::Blocks.
2. Select `File`.
3. Select `New`.
4. Select `Project`.
5. Select `Console Application`.
6. Select `C++`.
7. Give the project name:

```text
HillRider
```

8. Create the project.
9. Open the generated `main.cpp`.
10. Replace the default code with the project source code.
11. Configure the FreeGLUT/OpenGL libraries.
12. Build and run the project.

---

# 8. Linker Settings

The required libraries are added in Code::Blocks.

Go to:

```text
Settings
    -> Compiler
        -> Linker Settings
            -> Other linker options
```

The following linker options are used:

```text
-lfreeglut
-lopengl32
-lglu32
```

These libraries provide the required GLUT, OpenGL, and GLU functionality.

---

# 9. Dependencies

The project requires:

* Windows operating system
* Code::Blocks
* MinGW compiler
* OpenGL
* FreeGLUT
* `GL/glut.h`
* FreeGLUT library files
* FreeGLUT DLL

The program will not build correctly if the required OpenGL/FreeGLUT header and library files are missing.

---

# 10. How to Build the Project

After the project is configured:

1. Open the `HillRider` project in Code::Blocks.
2. Open `main.cpp`.
3. Make sure FreeGLUT and OpenGL are configured.
4. Make sure the linker options are present.
5. Select:

```text
Build -> Build
```

or press:

```text
Ctrl + F9
```

If there are no compilation errors, the executable will be generated.

---

# 11. How to Run the Project

To run the game from Code::Blocks:

1. Open the project.
2. Build the project.
3. Press `F9` or select:

```text
Build -> Build and Run
```

The game window will open.

The title of the window is:

```text
Hill Rider
```

---

# 12. Game Overview

The player controls a red car in a 2D hilly environment.

The car starts at approximately:

```text
X = 350
```

The player can accelerate, move backward, brake, and use boost.

The terrain is not flat. The car moves over hills and slopes, and the car body changes its angle according to the terrain.

The camera follows the car as it moves forward.

The player also needs to manage:

* Fuel
* Time
* Distance
* Coins
* Milestones

The game ends when the fuel becomes empty or when the available time finishes before reaching the current target distance.

---

# 13. Game Controls

| Key         | Function                |
| ----------- | ----------------------- |
| Right Arrow | Move/accelerate forward |
| Left Arrow  | Move backward           |
| Up Arrow    | Additional acceleration |
| Down Arrow  | Slow down               |
| B           | Brake                   |
| S           | Boost                   |
| R           | Restart the game        |
| ESC         | Exit the game           |

The arrow keys are handled through GLUT special-key callbacks.

The `B` and `S` keys are handled through normal keyboard callbacks.

---

# 14. GLUT Keyboard Handling

The program uses GLUT keyboard callback functions.

The following functions are used:

```cpp
keyboard()
keyboardUp()
specialKeyDown()
specialKeyUp()
```

The arrow keys are detected using:

```cpp
GLUT_KEY_RIGHT
GLUT_KEY_LEFT
GLUT_KEY_UP
GLUT_KEY_DOWN
```

Boolean variables such as:

```cpp
rightKey
leftKey
upKey
downKey
brakeKey
boostKey
```

store the current keyboard state.

This allows the game to continuously apply movement while a key is held down.

---

# 15. Main Game Loop

The game is updated by the GLUT timer function:

```cpp
void timer(int value)
```

The timer is called repeatedly using:

```cpp
glutTimerFunc(
    16,
    timer,
    0
);
```

Approximately every 16 milliseconds, the game updates its state and redraws the screen.

The timer performs several important tasks:

* Updates time.
* Reads movement states.
* Changes car speed.
* Updates car position.
* Calculates distance.
* Decreases fuel.
* Updates animation time.
* Updates bridge physics.
* Updates coins.
* Checks coin collection.
* Updates fuel pickups.
* Checks fuel collection.
* Checks distance milestones.
* Updates sparkle particles.
* Updates floating texts.
* Checks game-over conditions.
* Updates dust particles.
* Updates wheel rotation.
* Updates camera position.
* Requests a new frame.

This timer function works as the main game update loop.

---

# 16. Car Movement Logic

The car position is mainly controlled by:

```cpp
carX
```

The car speed is controlled by:

```cpp
speed
```

When the right arrow is pressed:

```cpp
speed += 0.12f;
```

The forward speed is limited so that it does not continuously increase.

The left arrow reduces the speed and allows backward movement.

The Up Arrow provides another acceleration method.

The Down Arrow reduces the current speed.

The `B` key applies stronger braking.

The `S` key activates the boost behaviour and allows a higher maximum speed.

The normal maximum speed is lower than the boost maximum speed.

When no movement key is pressed, the program gradually reduces the speed. This creates a simple slowing-down effect instead of stopping the car immediately.

---

# 17. Car Position and Distance

The car position is updated using:

```cpp
carX += speed;
```

The car is prevented from moving too far to the left:

```cpp
if (carX < 80)
{
    carX = 80;
    speed = 0;
}
```

The travelled distance is calculated from the car position:

```cpp
distanceTravelled =
    (carX - 350.0f) * 0.05f;
```

The distance is prevented from becoming negative.

This distance value is used for:

* HUD display
* Progress bar
* Distance milestones
* Target distance
* High score

---

# 18. Fuel System

Fuel is stored in:

```cpp
fuel
```

The initial fuel value is:

```cpp
100.0f
```

Fuel decreases when the car moves.

The fuel consumption depends on speed:

```cpp
fuel -= 0.018f * speed;
```

Boost uses additional fuel:

```cpp
fuel -= 0.040f * speed;
```

Fuel is limited so that it cannot become negative.

When fuel reaches zero, the game ends.

The HUD displays the fuel level as a percentage.

---

# 19. Fuel Bar

The fuel bar is drawn inside the HUD.

The program first clamps the fuel value between:

```text
0
```

and:

```text
100
```

The width of the filled portion is calculated from the current fuel percentage.

The fuel bar changes its display when the fuel becomes low.

When fuel is at or below 25 percent, the bar blinks to warn the player.

This is implemented using:

```cpp
bool lowFuel = clampedFuel <= 25.0f;
```

and an animation-time based blinking condition.

---

# 20. Time System

The game starts with:

```text
60 seconds
```

The timer decreases the remaining time continuously.

The value is stored in:

```cpp
timeLeft
```

The game checks whether the time has reached zero.

If the player has not reached the current target distance, the game ends with a time-up message.

The HUD changes the time text colour when the remaining time becomes low.

---

# 21. Target Distance

The game uses a target distance value:

```cpp
targetDistance
```

The initial target is:

```text
300 m
```

When the player reaches the current target, the target distance increases by:

```text
300 m
```

This gives the game a continuing distance objective.

The target distance is shown in the HUD.

---

# 22. Distance Milestones

The project includes a distance milestone system.

The first distance milestone is:

```text
1000 m
```

When the player reaches a distance milestone:

* 30 seconds are added.
* Fuel is restored to 100 percent.
* Sparkle effects are created.
* A milestone message is displayed.

For example:

```text
1000m MILESTONE! +30s
```

The next milestone is increased by:

```text
1000 m
```

This system gives the player an additional reward for travelling longer distances.

---

# 23. Coin System

Coins are collected during the game.

The current number of collected coins is stored in:

```cpp
coinsCollected
```

The HUD displays the number of coins.

The project also contains a coin milestone system.

When a coin milestone is reached, the player receives:

* Additional coins
* Full fuel
* Additional time
* Sparkle effects

The current milestone logic contains special bonus messages for selected milestones such as:

```text
100 COINS BONUS!
```

and:

```text
300 COINS BONUS!
```

---

# 24. Coin Milestone Function

The function:

```cpp
checkCoinMilestones()
```

checks whether the current number of coins has reached the next milestone.

The function uses a `while` loop so that the game can process milestones correctly even if the collected coin count passes more than one threshold.

When a milestone is reached, the program:

1. Saves the reached milestone.
2. Checks whether a popup should be displayed.
3. Adds bonus coins.
4. Restores fuel.
5. Adds time.
6. Creates a golden sparkle burst.
7. Creates a bonus message.
8. Moves the next milestone forward.

---

# 25. Terrain and Hill System

The car does not move on a flat surface.

The program uses terrain height functions to find the ground level below the car.

Functions used by the car include:

```cpp
getTerrainHeight()
sampleGroundUnderWheel()
getBaseTerrainHeight()
```

The left and right wheels use separate ground values.

The program then calculates the average ground height of the two wheels.

This value is used to position the car body.

---

# 26. Car Slope Calculation

The car calculates the difference between the left and right wheel ground positions.

The slope angle is calculated using:

```cpp
atan2()
```

The result is converted from radians to degrees.

The calculated angle is used to rotate the car.

Therefore, when the car moves over a hill or slope, the car body changes its orientation according to the terrain.

---

# 27. Simple Car Physics

The project includes simple vertical physics for the car.

The following variables are used:

```cpp
carVerticalOffset
carVerticalVelocity
carInAir
carAirRotation
```

The car has a spring-like correction force that tries to bring it back to the desired ground position.

The program also applies vertical movement and damping.

The vertical velocity is reduced over time, which prevents the car from moving indefinitely.

If the car is sufficiently above the normal position, it is considered to be in the air.

When the car is in the air, the rotation is updated differently.

When the car is on the ground, the rotation gradually follows the terrain slope.

This produces a simple jumping and landing effect.

---

# 28. Wheel System

The car has two wheels.

The wheel drawing is handled by:

```cpp
drawWheel()
```

The function receives:

```cpp
x
y
radius
rotation
```

Each wheel contains several graphical parts:

* Outer tyre
* Inner wheel
* Rim
* Four spokes
* Centre hub
* Rim outline

The wheel is rotated using:

```cpp
glRotatef()
```

The wheel rotation is updated using the current speed:

```cpp
wheelRotation -= speed * 7.0f;
```

Therefore, the wheels visually rotate while the car moves.

---

# 29. Car Drawing

The complete car is drawn using:

```cpp
drawCar()
```

The car is made from OpenGL shapes including:

* Polygons
* Quads
* Lines
* Circles

The car has a red body with darker red parts and highlights.

It also contains:

* Windows
* Headlight
* Rear light
* Body details
* Wheels
* Fender outlines
* Shadows

The car is first translated to its screen position.

Then the car is rotated according to the terrain slope or air rotation.

This makes the car appear attached to the hill surface.

---

# 30. Camera System

The game uses a horizontal camera system.

The camera position is stored in:

```cpp
cameraX
```

The screen position of world objects is calculated using:

```cpp
screenX = worldX - cameraX;
```

The camera target is based on the car:

```cpp
targetCamera =
    carX - 400.0f;
```

The camera then moves gradually toward the target instead of instantly changing its position.

This produces smoother camera movement.

As the car travels forward, the world moves across the screen while the car remains near the central area.

---

# 31. Bridge System

The game includes bridges and bridge gaps.

The car checks whether a wheel is above a bridge gap using:

```cpp
isBridgeGap()
```

If the wheel is on a bridge gap, the program uses:

```cpp
getBridgeHeight()
getBridgeWheelClearance()
```

to calculate the correct wheel height.

Otherwise, the normal terrain height is used.

This allows the car to interact with both normal terrain and bridge sections.

The display function draws the following in order:

```cpp
drawBridgeGaps();
drawTerrain();
drawBridges();
```

---

# 32. Coin and Fuel Pickups

The project contains collectible objects.

The main related functions include:

```cpp
initializeCoins()
updateCoinSpawning()
checkCoins()

initializeFuel()
updateFuelSpawning()
checkFuelPickups()
```

These functions are responsible for:

* Initialising collectible objects
* Creating or spawning them
* Updating their state
* Checking whether the car collects them

The collected objects affect the player's game state.

---

# 33. Dust Particle Effect

Dust particles are generated near the wheels when the car is moving.

The timer checks:

```cpp
fabs(speed) > 1.5f
```

and also checks that the car is not in the air.

Dust is then spawned near the left and right wheel positions.

The related functions are:

```cpp
spawnDustParticle()
updateDustParticles()
drawDustParticles()
```

The dust gives a visual indication that the wheels are moving over the terrain.

---

# 34. Sparkle Particle System

The project also contains a sparkle particle system.

The main functions are:

```cpp
initializeSparkles()
spawnSparkleBurst()
updateSparkleParticles()
drawSparkleParticles()
```

Each sparkle has values such as:

* Position
* Velocity
* Colour
* Size
* Life
* Maximum life
* Active state

The particle position is updated from its velocity.

The velocity is also changed over time to create movement.

The particle life decreases gradually.

When the life reaches zero, the particle becomes inactive.

The drawing function uses alpha blending so that the particles can fade out.

Sparkles are used mainly when the player reaches rewards and milestones.

---

# 35. Floating Text System

The project contains floating text effects.

The related functions are:

```cpp
initializeFloatingTexts()
spawnFloatingText()
updateFloatingTexts()
drawFloatingTexts()
```

Floating text stores:

* Text content
* Position
* Colour
* Scale
* Life
* Maximum life
* World-space state

The text moves upward during its lifetime.

Its alpha value is calculated from the remaining life.

The text is drawn twice:

1. A darker offset version for a simple shadow.
2. The main coloured text.

This makes messages easier to see.

---

# 36. Milestone Signs

The function:

```cpp
drawMilestoneSigns()
```

draws distance signs in the game world.

The signs are placed at regular intervals.

Each sign contains:

* A wooden post
* A rectangular sign
* Distance text

The spacing used in the function is:

```text
750 units
```

The signs are skipped when they are inside a bridge gap.

The signs also use the camera position to calculate their screen position.

---

# 37. Trophy Drawing

The function:

```cpp
drawTrophy()
```

creates a small trophy icon using OpenGL shapes.

It contains:

* Trophy cup
* Handles
* Stem
* Base
* Highlight

The trophy is used in the HUD beside the best-distance value.

---

# 38. HUD

The HUD is drawn by:

```cpp
drawHUD()
```

The HUD displays important game information.

It includes:

* Fuel icon
* Fuel bar
* Fuel percentage
* Coin icon
* Coin count
* Current distance
* Progress bar
* Current time
* Target distance
* Target flag
* Best distance trophy
* Milestone messages
* Game-over information

The HUD uses screen coordinates, so it remains fixed while the world camera moves.

---

# 39. Progress Bar

The progress bar shows the player's progress toward the current target distance.

The program calculates:

```cpp
progress =
    distanceTravelled / targetDistance;
```

The value is limited between:

```text
0.0
```

and:

```text
1.0
```

A line is drawn as the progress bar and a circular marker shows the current progress.

When the target distance increases, the progress starts again toward the new target.

---

# 40. Game Over System

The project contains two main game-over conditions.

### Fuel Empty

If:

```cpp
fuel <= 0.0f
```

the game ends because the car has no fuel.

### Time Up

If:

```cpp
timeLeft <= 0.0f
```

and the current target has not been reached, the game ends because the available time has finished.

The function:

```cpp
triggerGameOver()
```

handles the final game-over state.

It also checks whether the current distance is greater than the stored high score.

---

# 41. High Score

The game stores the best distance in:

```cpp
highScore
```

When the game ends, the current distance is compared with the high score.

If the current distance is higher, the high score is updated.

The best distance is displayed in the HUD using the trophy icon.

It is also shown on the game-over screen.

---

# 42. Game Over Screen

When:

```cpp
gameOver == true
```

the HUD draws a dark transparent overlay over the game.

The screen displays:

* `GAME OVER` or `TIME UP! GAME OVER`
* Final distance
* Best distance
* Total coins
* Restart instruction

The player can press:

```text
R
```

to restart the game.

---

# 43. Restart System

The restart operation is handled inside:

```cpp
keyboard()
```

When the player presses `R`, the important game values are reset.

For example:

```cpp
carX = 350.0f;
speed = 0.0f;
cameraX = 0.0f;
fuel = 100.0f;
distanceTravelled = 0.0f;
timeLeft = 60.0f;
targetDistance = 300.0f;
gameOver = false;
```

The game systems are also reinitialised:

```cpp
initializeCoins();
initializeFuel();
initializeBridges();
initializeDust();
initializeSparkles();
initializeFloatingTexts();
```

The milestone values are reset as well.

This allows the player to start a new game without closing the program.

---

# 44. Rendering Process

The main drawing function is:

```cpp
display()
```

The screen is cleared first.

Then the game is drawn in layers.

The current drawing order is:

```cpp
drawSky();
drawBridgeGaps();
drawTerrain();
drawBridges();
drawCoins();
drawFuelPickups();
drawDustParticles();
drawCar();
drawSparkleParticles();
drawFloatingTexts();
drawHUD();
```

This order is important because it controls which objects appear in front of or behind other objects.

For example, the terrain is drawn before the car, so the car appears above the terrain.

The HUD is drawn last so that it stays visible over the game world.

---

# 45. OpenGL Transformations Used

The project uses OpenGL transformations for drawing different objects.

Important functions include:

```cpp
glPushMatrix();
glPopMatrix();
glTranslatef();
glRotatef();
glScalef();
```

For example, the car is translated to its current screen position and then rotated according to the terrain.

The wheels are separately translated and rotated.

The floating text also uses translation and scaling.

These transformations are an important part of the graphics implementation.

---

# 46. Alpha Blending

The project uses OpenGL blending for transparent effects.

The following settings are used:

```cpp
glEnable(GL_BLEND);

glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
);
```

Blending is used for:

* Particle effects
* Floating text
* Car glass
* Shadows
* Fuel display
* Game-over overlay
* Fading effects

The alpha value controls the transparency of these objects.

---

# 47. Anti-Aliasing and Smooth Drawing

The project enables several OpenGL smoothing options.

These include:

```cpp
GL_LINE_SMOOTH
GL_POLYGON_SMOOTH
GL_POINT_SMOOTH
```

The program also enables multisampling:

```cpp
glEnable(GL_MULTISAMPLE);
```

These settings are used to make lines and shapes appear smoother.

---

# 48. Projection and Window Setup

The project uses a 2D orthographic projection.

The projection is created using:

```cpp
gluOrtho2D(
    0,
    WINDOW_WIDTH,
    0,
    WINDOW_HEIGHT
);
```

This allows the program to use simple 2D coordinates for drawing.

The same projection is configured in both:

```cpp
init()
```

and:

```cpp
reshape()
```

The window size is controlled using:

```cpp
WINDOW_WIDTH
WINDOW_HEIGHT
```

---

# 49. Important Functions in the Project

The main functions can be grouped according to their purpose.

## Particle Functions

```cpp
initializeSparkles()
spawnSparkleBurst()
updateSparkleParticles()
drawSparkleParticles()

initializeFloatingTexts()
spawnFloatingText()
updateFloatingTexts()
drawFloatingTexts()

spawnDustParticle()
updateDustParticles()
drawDustParticles()
```

## Game Reward Functions

```cpp
checkCoinMilestones()
checkDistanceMilestones()
```

## Car Functions

```cpp
drawWheel()
drawCar()
```

## Environment Functions

```cpp
drawMilestoneSigns()
drawBridges()
drawBridgeGaps()
drawTerrain()
```

## HUD Functions

```cpp
drawTrophy()
drawHUD()
```

## GLUT Functions

```cpp
display()
reshape()
keyboard()
keyboardUp()
specialKeyDown()
specialKeyUp()
timer()
init()
main()
```

---

# 50. Program Structure

The project can be understood in the following simple structure:

```text
main()
 |
 +-- init()
 |
 +-- GLUT callback registration
 |
 +-- timer()
 |    |
 |    +-- keyboard state
 |    +-- car movement
 |    +-- fuel
 |    +-- distance
 |    +-- coins
 |    +-- fuel pickups
 |    +-- bridges
 |    +-- particles
 |    +-- milestones
 |    +-- game-over checks
 |    +-- camera
 |
 +-- display()
      |
      +-- sky
      +-- terrain
      +-- bridges
      +-- coins
      +-- fuel
      +-- particles
      +-- car
      +-- floating text
      +-- HUD
```

This is the basic flow of the game.

---

# 51. Graphics Used in the Project

The project does not depend on a separate 2D game engine.

The main objects are drawn manually using OpenGL primitives.

Examples include:

* `GL_QUADS`
* `GL_POLYGON`
* `GL_TRIANGLES`
* `GL_LINES`
* `GL_LINE_STRIP`
* `GL_LINE_LOOP`
* Circles created through drawing functions

This approach was used to understand how 2D objects can be created and transformed using OpenGL.

---

# 52. Game Features

The completed game includes the following features:

1. 2D hilly environment.
2. Controllable car.
3. Forward and backward movement.
4. Acceleration.
5. Braking.
6. Boost.
7. Wheel rotation.
8. Terrain-based car rotation.
9. Simple vertical car physics.
10. Air rotation.
11. Camera following the car.
12. Coins.
13. Fuel pickups.
14. Fuel consumption.
15. Fuel warning.
16. Time limit.
17. Distance tracking.
18. Target distance.
19. Distance milestones.
20. Coin milestones.
21. Bonus rewards.
22. Bridge sections.
23. Dust particles.
24. Sparkle particles.
25. Floating text.
26. Milestone signs.
27. Progress bar.
28. Best-distance tracking.
29. Game-over screen.
30. Restart system.

---

# 53. Preview of the Output

The repository should contain screenshots showing the running game.

Recommended files:

```text
screenshots/
    gameplay.png
    hud.png
    game-over.png
```

The README can display them using:

```markdown
## Gameplay Preview

![Gameplay](screenshots/gameplay.png)

## HUD Preview

![HUD](screenshots/hud.png)

## Game Over Screen

![Game Over](screenshots/game-over.png)
```

If a GIF is recorded, it can also be added:

```markdown
## Gameplay GIF

![Gameplay GIF](screenshots/gameplay.gif)
```

The screenshots should show the actual output of the submitted program.

---

# 54. Suggested Repository Structure

A simple repository structure for this project is:

```text
HillRider/
|
|-- main.cpp
|-- README.md
|
|-- screenshots/
|   |-- gameplay.png
|   |-- hud.png
|   |-- game-over.png
|   |-- gameplay.gif
|
|-- HillRider.cbp
|
```

If the Code::Blocks project file has a different name, the actual project file name should be used.

If external DLL files are included in the repository, they should also be clearly identified.

---

# 55. How to Upload the Project to GitHub

The project can be uploaded to GitHub using the following steps.

## Step 1: Create a GitHub Repository

Log in to GitHub.

Create a new repository with a suitable name such as:

```text
2D-Hill-Rider-GLUT
```

The repository can be public if required by the course submission.

## Step 2: Prepare the Project Folder

Keep the project files together in one folder.

For example:

```text
HillRider/
    main.cpp
    README.md
    screenshots/
    HillRider.cbp
```

## Step 3: Upload the Files

Open the GitHub repository.

Select:

```text
Add file
```

Then select:

```text
Upload files
```

Drag the project files and folders into the upload area.

Add a commit message such as:

```text
Add Hill Rider GLUT project
```

Then commit the files.

## Step 4: Check the Repository

After uploading, make sure the repository contains:

* `main.cpp`
* `README.md`
* Code::Blocks project file
* Screenshots
* GIF if available

Open `README.md` from GitHub and check that all images are displayed correctly.

---

# 56. How to Submit the GitHub Link

After checking the repository:

1. Open the GitHub repository.
2. Copy the repository link.
3. Open the Graphics Lab project assignment.
4. Paste the GitHub repository link into the submission field.
5. Submit the assignment.

Before submitting, the repository should be opened in a browser to make sure the link works.

---

# 57. Testing

The following parts of the game should be tested before submission:

* Program starts correctly.
* Car moves with the arrow keys.
* Brake works.
* Boost works.
* Wheels rotate.
* Car follows terrain slopes.
* Camera follows the car.
* Coins can be collected.
* Fuel pickups work.
* Fuel decreases while driving.
* Low fuel warning appears.
* Distance increases.
* Target distance updates.
* Distance milestones work.
* Coin bonuses work.
* Bridge sections work.
* Dust appears while driving.
* Sparkles appear after rewards.
* Floating messages appear.
* Game-over screen appears.
* R restarts the game.
* ESC closes the program.

---

# 58. Known Limitations

This project is a 2D OpenGL/GLUT project made for a Graphics Lab course.

Some limitations are:

* The physics are simplified rather than being a complete vehicle physics simulation.
* The game uses basic OpenGL drawing primitives.
* The terrain and game objects are generated using program logic rather than a full game engine.
* The project is designed mainly for the Windows and Code::Blocks/MinGW environment used during development.
* The game does not use a separate physics engine.

These limitations are acceptable for the scope of this Graphics Lab project.

---

# 59. Learning Outcomes

Through this project, the following topics were practiced:

* OpenGL drawing
* GLUT window creation
* Keyboard input
* Animation
* Timer callbacks
* 2D transformations
* Translation
* Rotation
* Scaling
* Alpha blending
* Orthographic projection
* Object drawing
* Basic physics
* Collision and collection logic
* Camera movement
* Particle effects
* HUD design
* Game-state management

The project also helped in understanding how different graphics and programming concepts can work together in one interactive application.

---

# 60. Conclusion

2D Hill Rider using GLUT is a small interactive 2D driving game developed using C++ and OpenGL/GLUT.

The project demonstrates more than simple object drawing. It includes keyboard interaction, animation, car movement, terrain-based rotation, simple physics, camera movement, collectibles, fuel and time management, milestone rewards, particle effects, HUD elements, and a game-over system.

The main purpose of the project is to apply the graphics programming concepts learned in the Graphics Lab in a working interactive program.

The project was developed and tested using Code::Blocks, MinGW, OpenGL, and FreeGLUT.

---

# 61. Project Submission Checklist

Before submitting the project, the following items should be checked:

* [ ] GitHub repository is created.
* [ ] Repository is accessible.
* [ ] `main.cpp` is uploaded.
* [ ] Code::Blocks project file is uploaded.
* [ ] `README.md` is uploaded.
* [ ] Setup instructions are included.
* [ ] Build instructions are included.
* [ ] Run instructions are included.
* [ ] Game controls are documented.
* [ ] Project features are documented.
* [ ] Main functions are explained.
* [ ] Physics and game logic are explained.
* [ ] Screenshots are uploaded.
* [ ] Screenshot links work in README.
* [ ] Gameplay GIF is uploaded if available.
* [ ] Group member information is filled in.
* [ ] Final GitHub link is tested before submission.

---

# 62. Final Project Statement

This project was developed as a Graphics Lab project using C++ and GLUT. The main focus was to create an interactive 2D game while applying OpenGL drawing, transformations, animation, keyboard interaction, simple physics, camera movement, and game-state logic.

The implementation was built step by step by combining individual graphics functions with the game update system. Each major part of the program, including the car, terrain, wheels, collectibles, particles, HUD, camera, milestones, and game-over system, is handled through separate functions to keep the program organised and easier to understand.
