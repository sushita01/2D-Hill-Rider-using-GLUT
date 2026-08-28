#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;
const float PI = 3.14159265359f;

float getBaseTerrainHeight(float x);
bool isBridgeGap(float x);
int getBridgeIndex(float x);
float getBridgeFlexAt(float x);
float getBridgeHeight(float x);
float getTerrainHeight(float x);
float sampleGroundUnderWheel(float wheelCenterX, float wheelRadius);
float getBridgeWheelClearance(float wheelWorldX);

void updateBridgePhysics();

void drawCircle(float cx, float cy, float radius);
void drawText(float x, float y, const char* text);
void drawHudText(float x, float y, const char* text);
float textWidthBitmap(const char* text);
void drawHudTextColor(float x, float y, const char* text, float r, float g, float b);
void drawStrokeTextCentered(float centerX, float y, const char* text, float scale, float r, float g, float b);
void drawFuelCanister(float x, float y, float scale);
void drawCoinIcon(float x, float y, float scale);
void drawTrophy(float x, float y, float scale);
void drawWheel(float x, float y, float radius, float rotation);

void initializeBridges();
void initializeCoins();
void initializeFuel();
void initializeDust();

void spawnCoinGroup(float startX);
void spawnFuel(float worldX);
void spawnDustParticle(float worldX, float groundY);

void updateCoinSpawning();
void updateFuelSpawning();
void updateDustParticles();

void checkCoins();
void checkFuelPickups();

void spawnSparkleBurst(float x, float y, float r = 1.0f, float g = 0.85f, float b = 0.15f, int count = 14, float force = 1.0f, float sizeScale = 1.0f);
void spawnFloatingText(float x, float y, std::string text, float r = 1.0f, float g = 1.0f, float b = 0.2f, bool worldSpace = true, float fontScale = 1.0f);
void initializeSparkles();
void initializeFloatingTexts();
void updateSparkleParticles();
void updateFloatingTexts();
void drawSparkleParticles();
void drawFloatingTexts();

void checkCoinMilestones();
void checkDistanceMilestones();

void drawSky();
void drawTerrain();
void drawSoilCraters();
void drawBridgeGaps();
void drawBridges();
void drawCoins();
void drawFuelPickups();
void drawDustParticles();
void drawMilestoneSigns();
void drawCar();
void drawHUD();
void triggerGameOver(bool timedOut);
void reshape(int width, int height);

float carX = 350.0f;
float speed = 0.0f;
float wheelRotation = 0.0f;
const float WHEEL_OFFSET = 43.0f;
float cameraX = 0.0f;

bool rightKey = false;
bool leftKey = false;
bool upKey = false;
bool downKey = false;
bool brakeKey = false;
bool boostKey = false;

float carVerticalOffset = 0.0f;
float carVerticalVelocity = 0.0f;
float carAirRotation = 0.0f;
bool carInAir = false;

int coinsCollected = 0;
float fuel = 100.0f;
float distanceTravelled = 0.0f;
float highScore = 0.0f;
bool gameOver = false;

float timeLeft = 60.0f;
float targetDistance = 300.0f;
bool timeUp = false;

float bonusDisplayTimer = 0.0f;
char bonusDisplayText[64] = "";
float bonusDisplayR = 1.0f;
float bonusDisplayG = 0.85f;
float bonusDisplayB = 0.10f;
float nextCoinMilestone = 100.0f;
float nextDistanceMilestone = 1000.0f;
float animationTime = 0.0f;

const int MAX_COINS = 25;
float coinX[MAX_COINS];
float coinHeight[MAX_COINS];
bool coinCollected[MAX_COINS];
float nextCoinSpawnX = 700.0f;

const int MAX_FUEL = 10;
float fuelX[MAX_FUEL];
float fuelHeight[MAX_FUEL];
bool fuelCollected[MAX_FUEL];

float nextFuelAllowedX = 900.0f;
bool fuelSpawnedSinceLow = false;

const int MAX_BRIDGES = 2;
float bridgeStart[MAX_BRIDGES];
float bridgeEnd[MAX_BRIDGES];
float bridgeFlex[MAX_BRIDGES];
float bridgeFlexVelocity[MAX_BRIDGES];

const int MAX_DUST = 60;
float dustX[MAX_DUST];
float dustY[MAX_DUST];
float dustVX[MAX_DUST];
float dustVY[MAX_DUST];
float dustLife[MAX_DUST];
float dustMaxLife[MAX_DUST];
float dustSize[MAX_DUST];
bool dustActive[MAX_DUST];

const int MAX_SPARKLES = 160;
float sparkleX[MAX_SPARKLES];
float sparkleY[MAX_SPARKLES];
float sparkleVX[MAX_SPARKLES];
float sparkleVY[MAX_SPARKLES];
float sparkleLife[MAX_SPARKLES];
float sparkleMaxLife[MAX_SPARKLES];
float sparkleSize[MAX_SPARKLES];
float sparkleR[MAX_SPARKLES];
float sparkleG[MAX_SPARKLES];
float sparkleB[MAX_SPARKLES];
bool sparkleActive[MAX_SPARKLES];

const int MAX_FLOATING_TEXTS = 16;
float floatTextX[MAX_FLOATING_TEXTS];
float floatTextY[MAX_FLOATING_TEXTS];
float floatTextLife[MAX_FLOATING_TEXTS];
float floatTextMaxLife[MAX_FLOATING_TEXTS];
float floatTextR[MAX_FLOATING_TEXTS];
float floatTextG[MAX_FLOATING_TEXTS];
float floatTextB[MAX_FLOATING_TEXTS];
float floatTextScale[MAX_FLOATING_TEXTS];
bool floatTextWorldSpace[MAX_FLOATING_TEXTS];
bool floatTextActive[MAX_FLOATING_TEXTS];
char floatTextStr[MAX_FLOATING_TEXTS][32];

const float GRASS_THICKNESS = 8.0f;
const float TERRAIN_BASE_Y = 155.0f;

const float SOIL_TOP_R = 0.63f;
const float SOIL_TOP_G = 0.43f;
const float SOIL_TOP_B = 0.20f;
const float SOIL_BOTTOM_R = 0.38f;
const float SOIL_BOTTOM_G = 0.23f;
const float SOIL_BOTTOM_B = 0.11f;

const float CRATER_R = 0.34f;
const float CRATER_G = 0.205f;
const float CRATER_B = 0.095f;
const float CRATER_INNER_R = 0.30f;
const float CRATER_INNER_G = 0.175f;
const float CRATER_INNER_B = 0.075f;
const float CRATER_HIGHLIGHT_R = 0.58f;
const float CRATER_HIGHLIGHT_G = 0.39f;
const float CRATER_HIGHLIGHT_B = 0.18f;

const float GRASS_R = 0.30f;
const float GRASS_G = 0.72f;
const float GRASS_B = 0.16f;
const float GRASS_HIGHLIGHT_R = 0.46f;
const float GRASS_HIGHLIGHT_G = 0.80f;
const float GRASS_HIGHLIGHT_B = 0.24f;
float getBaseTerrainHeight(float x)
{
    float y = TERRAIN_BASE_Y;
    y += sin(x * 0.004f) * 120.0f;
    y += cos(x * 0.012f) * 45.0f;
    y += sin(x * 0.025f) * 15.0f;
    return y;
}
void drawHudText(float x, float y, const char* text)
{
    glColor3f(0.03f, 0.08f, 0.12f);
    drawText(x + 1.5f, y - 1.5f, text);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(x, y, text);
}
float textWidthBitmap(const char* text)
{
    float width = 0.0f;
    for (int i = 0; text[i] != '\0'; i++)
    {
        width += (float)glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    return width;
}
void drawHudTextColor(float x, float y, const char* text, float r, float g, float b)
{
    glColor3f(0.02f, 0.02f, 0.02f);
    drawText(x + 1.5f, y - 1.5f, text);
    glColor3f(r, g, b);
    drawText(x, y, text);
}
void drawStrokeTextCentered(float centerX, float y, const char* text, float scale, float r, float g, float b)
{
    float totalWidth = 0.0f;
    for (int i = 0; text[i] != '\0'; i++)
        totalWidth += (float)glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);

    totalWidth *= scale;

    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(centerX - totalWidth / 2.0f + 2.5f, y - 2.5f, 0.0f);
    glScalef(scale, scale, 1.0f);
    glLineWidth(3.0f);

    for (int i = 0; text[i] != '\0'; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);

    glLineWidth(1.0f);
    glPopMatrix();

    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(centerX - totalWidth / 2.0f, y, 0.0f);
    glScalef(scale, scale, 1.0f);
    glLineWidth(3.0f);

    for (int i = 0; text[i] != '\0'; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);

    glLineWidth(1.0f);
    glPopMatrix();
}

void drawFuelCanister(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.20f, 0.035f, 0.025f);
    glBegin(GL_POLYGON);
    glVertex2f(2.0f, 10.0f);
    glVertex2f(10.0f, 10.0f);
    glVertex2f(10.0f, 23.0f);
    glVertex2f(7.0f, 27.0f);
    glVertex2f(3.0f, 24.0f);
    glEnd();

    glColor3f(0.78f, 0.05f, 0.035f);
    glBegin(GL_POLYGON);
    glVertex2f(4.0f, 12.0f);
    glVertex2f(8.0f, 12.0f);
    glVertex2f(8.0f, 21.0f);
    glVertex2f(6.5f, 24.0f);
    glVertex2f(4.0f, 22.0f);
    glEnd();

    glColor3f(0.20f, 0.025f, 0.018f);
    glBegin(GL_POLYGON);
    glVertex2f(-11.0f, -15.0f);
    glVertex2f(7.0f, -15.0f);
    glVertex2f(11.0f, -11.0f);
    glVertex2f(11.0f, 10.0f);
    glVertex2f(7.0f, 16.0f);
    glVertex2f(-7.0f, 16.0f);
    glVertex2f(-11.0f, 11.0f);
    glEnd();

    glColor3f(0.86f, 0.055f, 0.035f);
    glBegin(GL_POLYGON);
    glVertex2f(-8.5f, -12.0f);
    glVertex2f(5.5f, -12.0f);
    glVertex2f(8.0f, -9.0f);
    glVertex2f(8.0f, 9.0f);
    glVertex2f(4.5f, 13.0f);
    glVertex2f(-6.0f, 13.0f);
    glVertex2f(-8.5f, 9.0f);
    glEnd();

    glColor3f(1.0f, 0.22f, 0.14f);
    glBegin(GL_QUADS);
    glVertex2f(-7.0f, -9.0f);
    glVertex2f(-4.5f, -9.0f);
    glVertex2f(-4.5f, 10.5f);
    glVertex2f(-7.0f, 10.5f);
    glEnd();

    glColor3f(0.18f, 0.025f, 0.018f);
    glBegin(GL_QUADS);
    glVertex2f(-2.5f, 14.0f);
    glVertex2f(4.0f, 14.0f);
    glVertex2f(4.0f, 18.0f);
    glVertex2f(-2.5f, 18.0f);
    glEnd();

    glColor3f(0.76f, 0.06f, 0.035f);
    glBegin(GL_QUADS);
    glVertex2f(-1.5f, 18.0f);
    glVertex2f(3.0f, 18.0f);
    glVertex2f(3.0f, 20.0f);
    glVertex2f(-1.5f, 20.0f);
    glEnd();

    glPopMatrix();
}

void drawCoinIcon(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.83f, 0.48f, 0.02f);
    drawCircle(0, 0, 14.0f);
    glColor3f(1.0f, 0.75f, 0.06f);
    drawCircle(0, 0, 11.0f);
    glColor3f(1.0f, 0.91f, 0.45f);
    drawCircle(-2.5f, 2.5f, 2.0f);
    glColor3f(0.88f, 0.52f, 0.02f);
    glLineWidth(1.4f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-6.0f, 0.0f);
    glVertex2f(-4.0f, 5.0f);
    glVertex2f(4.0f, 5.0f);
    glVertex2f(6.0f, 0.0f);
    glVertex2f(4.0f, -5.0f);
    glVertex2f(-4.0f, -5.0f);
    glEnd();

    glLineWidth(1.0f);
    glPopMatrix();
}
void initializeBridges()
{
    bridgeStart[0] = 2000.0f;
    bridgeEnd[0] = 2700.0f;

    bridgeStart[1] = 6000.0f;
    bridgeEnd[1] = 6700.0f;

    for (int i = 0; i < MAX_BRIDGES; i++)
    {
        bridgeFlex[i] = 0.0f;
        bridgeFlexVelocity[i] = 0.0f;
    }
}
bool isBridgeGap(float x)
{
    for (int i = 0; i < MAX_BRIDGES; i++)
    {
        if (x >= bridgeStart[i] && x <= bridgeEnd[i])
            return true;
    }
    return false;
}
int getBridgeIndex(float x)
{
    for (int i = 0; i < MAX_BRIDGES; i++)
    {
        if (x >= bridgeStart[i] && x <= bridgeEnd[i])
            return i;
    }
    return -1;
}
float getBridgeFlexAt(float x)
{
    int index = getBridgeIndex(x);

    if (index < 0)
        return 0.0f;

    float t =
        (x - bridgeStart[index]) /
        (bridgeEnd[index] - bridgeStart[index]);
    return bridgeFlex[index] * sin(PI * t);
}
float getBridgeHeight(float x)
{
    int index = getBridgeIndex(x);

    if (index < 0)
        return getBaseTerrainHeight(x);

    float startX = bridgeStart[index];
    float endX = bridgeEnd[index];
    float startY = getBaseTerrainHeight(startX) + 3.0f;
    float endY = getBaseTerrainHeight(endX) + 2.5f;
    float t =
        (x - startX) /
        (endX - startX);
    float baseY =
        startY +
        (endY - startY) * t;
    const float hangingSag = 75.0f;
    float sag =
        hangingSag *
        4.0f *
        t *
        (1.0f - t);
    float y =
        baseY -
        sag;
    y -= getBridgeFlexAt(x);
    return y;
}

float getTerrainHeight(float x)
{
    if (isBridgeGap(x))
        return getBridgeHeight(x);

    return getBaseTerrainHeight(x);
}

float sampleGroundUnderWheel(float wheelCenterX, float wheelRadius)
{
    const int samples = 7;
    float maxHeight = -1000000.0f;
    for (int i = 0; i < samples; i++)
    {
        float t =
            (float)i / (float)(samples - 1);
        float offset =
            (t - 0.5f) * wheelRadius * 1.4f;
        float sampleX =
            wheelCenterX + offset;
        float h =
            getTerrainHeight(sampleX);
        if (h > maxHeight)
            maxHeight = h;
    }
    return maxHeight;
}

float getBridgeWheelClearance(float wheelWorldX)
{
    const float slopeSampleDelta = 3.0f;
    const float clearanceSlopeFactor = 3.0f;
    const float clearanceMax = 4.0f;
    float heightLeft =
        getBridgeHeight(wheelWorldX - slopeSampleDelta);
    float heightRight =
        getBridgeHeight(wheelWorldX + slopeSampleDelta);
    float localSlope =
        fabs(heightRight - heightLeft) /
        (2.0f * slopeSampleDelta);
    float clearance =
        localSlope * clearanceSlopeFactor;

    if (clearance > clearanceMax)
        clearance = clearanceMax;

    return clearance;
}

void updateBridgePhysics()
{
    for (int i = 0; i < MAX_BRIDGES; i++)
    {
        float centerX =
            (bridgeStart[i] + bridgeEnd[i]) / 2.0f;

        float distanceFromCenter =
            fabs(carX - centerX);

        float halfLength =
            (bridgeEnd[i] - bridgeStart[i]) / 2.0f;

        float load = 0.0f;

        if (distanceFromCenter < halfLength + 80.0f)
        {
            float normalized =
                distanceFromCenter /
                (halfLength + 80.0f);

            if (normalized < 1.0f)
            {
                load = 1.0f - normalized;
                load *= load;
            }
        }

        float desiredFlex = load * 15.0f;

        float spring =
            (desiredFlex - bridgeFlex[i]) * 0.10f;

        bridgeFlexVelocity[i] += spring;
        bridgeFlexVelocity[i] *= 0.84f;
        bridgeFlex[i] += bridgeFlexVelocity[i];

        if (bridgeFlex[i] < 0.0f)
        {
            bridgeFlex[i] = 0.0f;
            bridgeFlexVelocity[i] = 0.0f;
        }

        if (bridgeFlex[i] > 15.0f)
            bridgeFlex[i] = 15.0f;
    }
}

void drawCircle(float cx, float cy, float radius)
{
    const int segments = 96;

    glBegin(GL_POLYGON);

    for (int i = 0; i < segments; i++)
    {
        float angle =
            2.0f * PI * i / (float)segments;

        glVertex2f(
            cx + radius * cos(angle),
            cy + radius * sin(angle)
        );
    }

    glEnd();
}

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_18,
            text[i]
        );
    }
}

void drawSky()
{
    const int strips = 100;

    float stripHeight =
        (float)WINDOW_HEIGHT / strips;

    glBegin(GL_QUADS);

    for (int i = 0; i < strips; i++)
    {
        float y1 = i * stripHeight;
        float y2 = (i + 1) * stripHeight;

        float t1 = (float)i / strips;
        float t2 = (float)(i + 1) / strips;

        float r1, g1, b1;
        float r2, g2, b2;

        if (t1 > 0.55f)
        {
            float t = (t1 - 0.55f) / 0.45f;

            r1 = 0.62f - 0.18f * t;
            g1 = 0.80f - 0.10f * t;
            b1 = 0.93f - 0.02f * t;
        }
        else if (t1 > 0.25f)
        {
            float t = (t1 - 0.25f) / 0.30f;

            r1 = 0.82f - 0.20f * t;
            g1 = 0.90f - 0.10f * t;
            b1 = 0.97f - 0.04f * t;
        }
        else
        {
            float t = t1 / 0.25f;

            r1 = 0.91f - 0.09f * t;
            g1 = 0.95f - 0.05f * t;
            b1 = 0.98f - 0.01f * t;
        }

        if (t2 > 0.55f)
        {
            float t = (t2 - 0.55f) / 0.45f;

            r2 = 0.62f - 0.18f * t;
            g2 = 0.80f - 0.10f * t;
            b2 = 0.93f - 0.02f * t;
        }
        else if (t2 > 0.25f)
        {
            float t = (t2 - 0.25f) / 0.30f;

            r2 = 0.82f - 0.20f * t;
            g2 = 0.90f - 0.10f * t;
            b2 = 0.97f - 0.04f * t;
        }
        else
        {
            float t = t2 / 0.25f;

            r2 = 0.91f - 0.09f * t;
            g2 = 0.95f - 0.05f * t;
            b2 = 0.98f - 0.01f * t;
        }

        glColor3f(r1, g1, b1);
        glVertex2f(0.0f, y1);
        glVertex2f(WINDOW_WIDTH, y1);
        glColor3f(r2, g2, b2);
        glVertex2f(WINDOW_WIDTH, y2);
        glVertex2f(0.0f, y2);
    }
    glEnd();
}

void drawTerrain()
{
    const float terrainStep = 0.5f;
    glBegin(GL_QUAD_STRIP);
    bool soilStripActive = false;

    for (float screenX = 0.0f;
         screenX <= WINDOW_WIDTH;
         screenX += terrainStep)
    {
        float worldX =
            cameraX + screenX;

        if (isBridgeGap(worldX))
        {
            if (soilStripActive)
            {
                glEnd();
                soilStripActive = false;
            }

            continue;
        }

        if (!soilStripActive)
        {
            glBegin(GL_QUAD_STRIP);
            soilStripActive = true;
        }

        float terrainY =
            getBaseTerrainHeight(worldX);

        float soilTopY =
            terrainY - GRASS_THICKNESS;

        glColor3f(
            SOIL_TOP_R,
            SOIL_TOP_G,
            SOIL_TOP_B
        );

        glVertex2f(
            screenX,
            soilTopY
        );

        glColor3f(
            SOIL_BOTTOM_R,
            SOIL_BOTTOM_G,
            SOIL_BOTTOM_B
        );

        glVertex2f(
            screenX,
            0.0f
        );
    }

    if (soilStripActive)
        glEnd();

    bool grassStripActive = false;

    for (float screenX = 0.0f;
         screenX <= WINDOW_WIDTH;
         screenX += terrainStep)
    {
        float worldX =
            cameraX + screenX;

        if (isBridgeGap(worldX))
        {
            if (grassStripActive)
            {
                glEnd();
                grassStripActive = false;
            }

            continue;
        }

        if (!grassStripActive)
        {
            glBegin(GL_QUAD_STRIP);
            grassStripActive = true;
        }

        float terrainY =
            getBaseTerrainHeight(worldX);

        float grassBottom =
            terrainY - GRASS_THICKNESS;

        glColor3f(
            GRASS_R,
            GRASS_G,
            GRASS_B
        );

        glVertex2f(
            screenX,
            grassBottom
        );

        glVertex2f(
            screenX,
            terrainY
        );
    }

    if (grassStripActive)
        glEnd();

    glColor3f(
        GRASS_HIGHLIGHT_R,
        GRASS_HIGHLIGHT_G,
        GRASS_HIGHLIGHT_B
    );

    glLineWidth(8.0f);

    bool lineActive = false;

    for (float screenX = 0.0f;
         screenX <= WINDOW_WIDTH;
         screenX += 0.5f)
    {
        float worldX =
            cameraX + screenX;

        if (isBridgeGap(worldX))
        {
            if (lineActive)
            {
                glEnd();
                lineActive = false;
            }

            continue;
        }

        if (!lineActive)
        {
            glBegin(GL_LINE_STRIP);
            lineActive = true;
        }

        float y =
            getBaseTerrainHeight(worldX);

        glVertex2f(
            screenX,
            y + 1.0f
        );
    }

    if (lineActive)
        glEnd();

    glLineWidth(1.0f);

    drawSoilCraters();
}

void drawSoilCraters()
{
    const float baseSpacing = 30.0f;

    float firstWorld =
        cameraX - 250.0f;

    float lastWorld =
        cameraX +
        WINDOW_WIDTH +
        250.0f;

    int firstIndex =
        (int)floor(firstWorld / baseSpacing) - 3;

    int lastIndex =
        (int)ceil(lastWorld / baseSpacing) + 3;

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    for (int index = firstIndex;
         index <= lastIndex;
         index++)
    {
        float seedA =
            fabs(
                sin(
                    index * 12.9898f +
                    78.233f
                ) * 43758.5453f
            );

        float randomA =
            seedA - floor(seedA);

        float seedB =
            fabs(
                cos(
                    index * 78.233f +
                    19.173f
                ) * 24634.6345f
            );

        float randomB =
            seedB - floor(seedB);

        float seedC =
            fabs(
                sin(
                    index * 37.719f +
                    11.127f
                ) * 18342.417f
            );

        float randomC =
            seedC - floor(seedC);

        float seedD =
            fabs(
                cos(
                    index * 91.173f +
                    51.719f
                ) * 31415.9265f
            );

        float randomD =
            seedD - floor(seedD);

        if (randomD < 0.16f)
            continue;

        float spacingOffset =
            (randomA - 0.5f) * 22.0f;

        float worldX =
            index * baseSpacing +
            spacingOffset;

        float radius =
            6.0f +
            randomB * 12.0f;

        float depth =
            38.0f +
            randomC * 110.0f;

        if (isBridgeGap(worldX))
            continue;

        float terrainY =
            getBaseTerrainHeight(worldX);

        float worldY =
            terrainY -
            GRASS_THICKNESS -
            depth;

        float screenX =
            worldX -
            cameraX;

        if (screenX < -100.0f ||
            screenX > WINDOW_WIDTH + 100.0f)
        {
            continue;
        }

        glColor4f(
            CRATER_R,
            CRATER_G,
            CRATER_B,
            0.045f
        );

        drawCircle(
            screenX,
            worldY,
            radius
        );

        float localOffsetX =
            (randomD - 0.5f) *
            radius *
            0.75f;

        float localOffsetY =
            (randomA - 0.5f) *
            radius *
            0.75f;

        float smallRadius =
            radius *
            (0.35f + randomC * 0.18f);

        glColor4f(
            CRATER_INNER_R,
            CRATER_INNER_G,
            CRATER_INNER_B,
            0.045f
        );

        drawCircle(
            screenX + localOffsetX,
            worldY + localOffsetY,
            smallRadius
        );

        float highlightRadius =
            radius * 0.24f;

        glColor4f(
            CRATER_HIGHLIGHT_R,
            CRATER_HIGHLIGHT_G,
            CRATER_HIGHLIGHT_B,
            0.035f
        );
        drawCircle(
            screenX - radius * 0.22f,
            worldY + radius * 0.20f,
            highlightRadius
        );
    }
    glDisable(GL_BLEND);
}

void drawBridgeGaps()
{
}

void drawBridges()
{
    const int bridgeSegments = 140;
    for (int i = 0; i < MAX_BRIDGES; i++)
    {
        float startX =
            bridgeStart[i];
        float endX =
            bridgeEnd[i];
        float screenStart =
            startX - cameraX;
        float screenEnd =
            endX - cameraX;

        if (screenEnd < -150.0f ||
            screenStart > WINDOW_WIDTH + 150.0f)
        {
            continue;
        }

        const float bridgeThickness = 8.0f;
        float startY =
            getBaseTerrainHeight(startX) + 3.0f;
        float endY =
            getBaseTerrainHeight(endX) + 2.5f;
        glBegin(GL_QUAD_STRIP);

        for (int j = 0;
             j <= bridgeSegments;
             j++)
        {
            float t =
                (float)j /
                (float)bridgeSegments;
            float wx =
                startX +
                (endX - startX) * t;
            float bridgeY;

            if (j == 0)
            {
                bridgeY = startY;
            }
            else if (j == bridgeSegments)
            {
                bridgeY = endY;
            }
            else
            {
                bridgeY =
                    getBridgeHeight(wx);
            }

            float topY =
                bridgeY;
            float bottomY =
                topY -
                bridgeThickness;
            float shade =
                0.47f -
                0.08f * t;
            float highlight =
                0.66f -
                0.05f * t;
            glColor3f(
                shade,
                0.255f -
                0.035f * t,
                0.085f -
                0.018f * t
            );
            glVertex2f(
                wx - cameraX,
                topY
            );
            glColor3f(
                highlight,
                0.38f -
                0.035f * t,
                0.13f -
                0.015f * t
            );
            glVertex2f(
                wx - cameraX,
                bottomY
            );
        }
        glEnd();
    }
}

void initializeCoins()
{
    for (int i = 0; i < MAX_COINS; i++)
    {
        coinX[i] = -100000.0f;
        coinHeight[i] = 32.0f;
        coinCollected[i] = true;
    }

    nextCoinSpawnX = 700.0f;
}

void spawnCoinGroup(float startX)
{
    int freeSlots[MAX_COINS];
    int freeCount = 0;

    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coinCollected[i])
        {
            freeSlots[freeCount] = i;
            freeCount++;
        }
    }

    if (freeCount < 2)
        return;

    int groupSize =
        2 + rand() % 4;

    if (groupSize > freeCount)
        groupSize = freeCount;

    for (int j = 0; j < groupSize; j++)
    {
        int index = freeSlots[j];

        coinX[index] =
            startX +
            j * 48.0f;

        coinHeight[index] =
            32.0f +
            (j % 3) * 10.0f;

        coinCollected[index] = false;
    }
}

void updateCoinSpawning()
{
    if (carX + 1300.0f >= nextCoinSpawnX)
    {
        spawnCoinGroup(nextCoinSpawnX);

        nextCoinSpawnX +=
            650.0f +
            (rand() % 500);
    }
}

void checkCoins()
{
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coinCollected[i])
            continue;

        float dx =
            fabs(carX - coinX[i]);

        if (dx < 55.0f)
        {
            coinCollected[i] = true;
            float groundY = getTerrainHeight(coinX[i]);
            float pickupY = groundY + coinHeight[i];
            spawnSparkleBurst(coinX[i], pickupY, 1.0f, 0.80f, 0.10f, 10, 1.0f, 1.0f);
            spawnFloatingText(coinX[i], pickupY + 6.0f, "+1", 1.0f, 0.90f, 0.10f, true, 1.0f);
            coinX[i] = -100000.0f;
            coinsCollected++;
        }
    }

    checkCoinMilestones();
}

void drawCoins()
{
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coinCollected[i])
            continue;

        float worldX =
            coinX[i];

        float groundY =
            getTerrainHeight(worldX);

        float bob =
            sin(
                animationTime * 3.0f +
                (float)i * 0.75f
            ) * 5.0f;

        float worldY =
            groundY +
            coinHeight[i] +
            bob;

        float screenX =
            worldX - cameraX;

        if (screenX < -40 ||
            screenX > WINDOW_WIDTH + 40)
        {
            continue;
        }

        float spin =
            fabs(
                cos(
                    animationTime * 4.0f +
                    (float)i * 0.55f
                )
            );

        if (spin < 0.12f)
            spin = 0.12f;

        glPushMatrix();
        glTranslatef(
            screenX,
            worldY,
            0
        );
        glScalef(
            spin,
            1.0f,
            1.0f
        );
        glColor3f(
            0.92f,
            0.60f,
            0.04f
        );
        drawCircle(
            0,
            0,
            11.0f
        );
        glColor3f(
            1.0f,
            0.82f,
            0.12f
        );
        drawCircle(
            0,
            0,
            7.0f
        );
        glColor3f(
            1.0f,
            0.94f,
            0.55f
        );
        drawCircle(
            -2.0f,
            2.0f,
            2.0f
        );
        glPopMatrix();
    }
}

void initializeFuel()
{
    for (int i = 0; i < MAX_FUEL; i++)
    {
        fuelX[i] = -100000.0f;
        fuelHeight[i] = 35.0f;
        fuelCollected[i] = true;
    }

    nextFuelAllowedX = 1100.0f;
    fuelSpawnedSinceLow = false;
}

void spawnFuel(float worldX)
{
    for (int i = 0; i < MAX_FUEL; i++)
    {
        if (fuelCollected[i])
        {
            fuelX[i] = worldX;
            fuelHeight[i] = 35.0f;
            fuelCollected[i] = false;
            return;
        }
    }
}

void updateFuelSpawning()
{
    if (fuel > 55.0f)
        fuelSpawnedSinceLow = false;

    if (fuel >= 50.0f)
        return;

    if (carX < nextFuelAllowedX)
        return;

    if (fuelSpawnedSinceLow)
        return;

    int chance = rand() % 100;

    if (chance < 60)
    {
        float spawnDistance =
            500.0f +
            rand() % 450;

        spawnFuel(
            carX + spawnDistance
        );

        fuelSpawnedSinceLow = true;

        nextFuelAllowedX =
            carX +
            spawnDistance +
            900.0f;
    }
    else
    {
        nextFuelAllowedX =
            carX + 350.0f;
    }
}

void checkFuelPickups()
{
    for (int i = 0; i < MAX_FUEL; i++)
    {
        if (fuelCollected[i])
            continue;

        float dx =
            fabs(carX - fuelX[i]);

        if (dx < 60.0f)
        {
            fuelCollected[i] = true;
            fuelX[i] = -100000.0f;
            fuel += 35.0f;

            if (fuel > 100.0f)
                fuel = 100.0f;

            nextFuelAllowedX =
                carX + 900.0f;
            fuelSpawnedSinceLow = false;
        }
    }
}

void drawFuelPickups()
{
    for (int i = 0; i < MAX_FUEL; i++)
    {
        if (fuelCollected[i])
            continue;

        float worldX =
            fuelX[i];
        float groundY =
            getTerrainHeight(worldX);
        float bob =
            sin(animationTime * 2.8f + (float)i) * 3.0f;
        float worldY =
            groundY + fuelHeight[i] + bob;
        float screenX =
            worldX - cameraX;

        if (screenX < -50 ||
            screenX > WINDOW_WIDTH + 50)
        {
            continue;
        }
        drawFuelCanister(screenX, worldY, 1.0f);
    }
}

void initializeDust()
{
    for (int i = 0; i < MAX_DUST; i++)
    {
        dustActive[i] = false;
        dustLife[i] = 0.0f;
        dustMaxLife[i] = 1.0f;
        dustSize[i] = 3.0f;
        dustX[i] = -100000.0f;
        dustY[i] = 0.0f;
        dustVX[i] = 0.0f;
        dustVY[i] = 0.0f;
    }
}

void spawnDustParticle(float worldX, float groundY)
{
    for (int i = 0; i < MAX_DUST; i++)
    {
        if (!dustActive[i])
        {
            float jitterX =
                ((rand() % 100) / 100.0f - 0.5f) * 14.0f;
            float jitterY =
                (rand() % 100) / 100.0f * 4.0f;
            dustX[i] = worldX + jitterX;
            dustY[i] = groundY + jitterY;
            float dirSign =
                (speed >= 0.0f) ? -1.0f : 1.0f;
            dustVX[i] =
                dirSign *
                (0.6f + (rand() % 100) / 100.0f * 1.2f);
            dustVY[i] =
                0.4f + (rand() % 100) / 100.0f * 0.9f;
            dustMaxLife[i] =
                0.5f + (rand() % 100) / 100.0f * 0.5f;
            dustLife[i] = dustMaxLife[i];
            dustSize[i] =
                3.0f + (rand() % 100) / 100.0f * 4.0f;
            dustActive[i] = true;
            return;
        }
    }
}

void updateDustParticles()
{
    for (int i = 0; i < MAX_DUST; i++)
    {
        if (!dustActive[i])
            continue;

        dustX[i] += dustVX[i];
        dustY[i] += dustVY[i];

        dustVY[i] -= 0.02f;
        dustVX[i] *= 0.97f;

        dustLife[i] -= 0.016f;

        if (dustLife[i] <= 0.0f)
            dustActive[i] = false;
    }
}

void drawDustParticles()
{
    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    for (int i = 0; i < MAX_DUST; i++)
    {
        if (!dustActive[i])
            continue;

        float screenX =
            dustX[i] - cameraX;

        if (screenX < -30 ||
            screenX > WINDOW_WIDTH + 30)
        {
            continue;
        }

        float alpha =
            (dustLife[i] / dustMaxLife[i]) * 0.35f;

        glColor4f(
            0.55f,
            0.42f,
            0.24f,
            alpha
        );

        drawCircle(
            screenX,
            dustY[i],
            dustSize[i]
        );
    }
    glDisable(GL_BLEND);
}

void initializeSparkles()
{
    for (int i = 0; i < MAX_SPARKLES; i++)
    {
        sparkleActive[i] = false;
        sparkleLife[i] = 0.0f;
        sparkleMaxLife[i] = 1.0f;
        sparkleX[i] = -100000.0f;
        sparkleY[i] = 0.0f;
        sparkleVX[i] = 0.0f;
        sparkleVY[i] = 0.0f;
        sparkleSize[i] = 3.0f;
        sparkleR[i] = 1.0f;
        sparkleG[i] = 1.0f;
        sparkleB[i] = 1.0f;
    }
}

void spawnSparkleBurst(float x, float y, float r, float g, float b, int count, float force, float sizeScale)
{
    int spawned = 0;

    for (int i = 0; i < MAX_SPARKLES && spawned < count; i++)
    {
        if (sparkleActive[i])
            continue;

        float angle = ((float)rand() / (float)RAND_MAX) * 2.0f * PI;

        float speedMag =
            (1.2f + ((float)rand() / (float)RAND_MAX) * 2.6f) * force;

        sparkleX[i] = x;
        sparkleY[i] = y;

        sparkleVX[i] = cos(angle) * speedMag;
        sparkleVY[i] = sin(angle) * speedMag + 0.8f;

        sparkleMaxLife[i] =
            0.55f + ((float)rand() / (float)RAND_MAX) * 0.45f;

        sparkleLife[i] = sparkleMaxLife[i];

        sparkleSize[i] =
            (2.0f + ((float)rand() / (float)RAND_MAX) * 2.5f) * sizeScale;

        sparkleR[i] = r;
        sparkleG[i] = g;
        sparkleB[i] = b;

        sparkleActive[i] = true;

        spawned++;
    }
}

void updateSparkleParticles()
{
    for (int i = 0; i < MAX_SPARKLES; i++)
    {
        if (!sparkleActive[i])
            continue;

        sparkleX[i] += sparkleVX[i];
        sparkleY[i] += sparkleVY[i];

        sparkleVY[i] -= 0.06f;
        sparkleVX[i] *= 0.95f;
        sparkleVY[i] *= 0.97f;

        sparkleLife[i] -= 0.016f;

        if (sparkleLife[i] <= 0.0f)
            sparkleActive[i] = false;
    }
}

void drawSparkleParticles()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < MAX_SPARKLES; i++)
    {
        if (!sparkleActive[i])
            continue;

        float screenX = sparkleX[i] - cameraX;

        if (screenX < -40 || screenX > WINDOW_WIDTH + 40)
            continue;

        float alpha = sparkleLife[i] / sparkleMaxLife[i];

        if (alpha < 0.0f)
            alpha = 0.0f;

        glColor4f(sparkleR[i], sparkleG[i], sparkleB[i], alpha);

        drawCircle(screenX, sparkleY[i], sparkleSize[i] * alpha + 0.5f);
    }
    glDisable(GL_BLEND);
}

void initializeFloatingTexts()
{
    for (int i = 0; i < MAX_FLOATING_TEXTS; i++)
    {
        floatTextActive[i] = false;
        floatTextLife[i] = 0.0f;
        floatTextMaxLife[i] = 1.0f;
        floatTextX[i] = 0.0f;
        floatTextY[i] = 0.0f;
        floatTextR[i] = 1.0f;
        floatTextG[i] = 1.0f;
        floatTextB[i] = 1.0f;
        floatTextScale[i] = 1.0f;
        floatTextWorldSpace[i] = true;
        floatTextStr[i][0] = '\0';
    }
}

void spawnFloatingText(float x, float y, std::string text, float r, float g, float b, bool worldSpace, float fontScale)
{
    for (int i = 0; i < MAX_FLOATING_TEXTS; i++)
    {
        if (floatTextActive[i])
            continue;

        floatTextX[i] = x;
        floatTextY[i] = y;

        floatTextMaxLife[i] = 1.0f;
        floatTextLife[i] = 1.0f;

        floatTextR[i] = r;
        floatTextG[i] = g;
        floatTextB[i] = b;

        floatTextScale[i] = fontScale;
        floatTextWorldSpace[i] = worldSpace;

        strncpy(floatTextStr[i], text.c_str(), 31);
        floatTextStr[i][31] = '\0';
        floatTextActive[i] = true;
        return;
    }
}

void updateFloatingTexts()
{
    for (int i = 0; i < MAX_FLOATING_TEXTS; i++)
    {
        if (!floatTextActive[i])
            continue;

        floatTextY[i] += 0.9f;
        floatTextLife[i] -= 0.016f;

        if (floatTextLife[i] <= 0.0f)
            floatTextActive[i] = false;
    }
}

void drawFloatingTexts()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < MAX_FLOATING_TEXTS; i++)
    {
        if (!floatTextActive[i])
            continue;

        float alpha = floatTextLife[i] / floatTextMaxLife[i];

        if (alpha < 0.0f)
            alpha = 0.0f;

        float drawX = floatTextX[i];
        float drawY = floatTextY[i];

        if (floatTextWorldSpace[i])
            drawX -= cameraX;

        if (floatTextWorldSpace[i] &&
            (drawX < -60 || drawX > WINDOW_WIDTH + 60))
        {
            continue;
        }

        glPushMatrix();
        glTranslatef(drawX, drawY, 0.0f);
        glScalef(floatTextScale[i], floatTextScale[i], 1.0f);
        glColor4f(0.0f, 0.0f, 0.0f, alpha * 0.65f);
        drawText(1.2f, -1.2f, floatTextStr[i]);
        glColor4f(floatTextR[i], floatTextG[i], floatTextB[i], alpha);
        drawText(0.0f, 0.0f, floatTextStr[i]);
        glPopMatrix();
    }
    glDisable(GL_BLEND);
}

void checkCoinMilestones()
{
    while (coinsCollected >= (int)nextCoinMilestone)
    {
        float reachedMilestone = nextCoinMilestone;

        bool showPopup =
            (reachedMilestone == 100.0f || reachedMilestone == 300.0f);

        coinsCollected += 50;
        fuel = 100.0f;
        timeLeft += 30.0f;

        float carGroundY = getTerrainHeight(carX) + 45.0f;
        spawnSparkleBurst(carX, carGroundY, 1.0f, 0.82f, 0.10f, 34, 1.6f, 1.4f);

        if (showPopup)
        {
            char msg[64];
            sprintf(msg, "%d COINS BONUS!", (int)reachedMilestone);

            strncpy(bonusDisplayText, msg, 63);
            bonusDisplayText[63] = '\0';

            bonusDisplayR = 1.0f;
            bonusDisplayG = 0.85f;
            bonusDisplayB = 0.10f;

            bonusDisplayTimer = 1.5f;
        }

        if (reachedMilestone < 300.0f)
            nextCoinMilestone = 300.0f;
        else if (reachedMilestone == 300.0f)
            nextCoinMilestone = 400.0f;
        else
            nextCoinMilestone += 100.0f;
    }
}

void checkDistanceMilestones()
{
    while (distanceTravelled >= nextDistanceMilestone)
    {
        float reachedMilestone = nextDistanceMilestone;

        timeLeft += 30.0f;
        fuel = 100.0f;

        float carGroundY = getTerrainHeight(carX) + 70.0f;

        spawnSparkleBurst(carX, carGroundY, 1.0f, 0.15f, 0.12f, 20, 1.5f, 1.3f);
        spawnSparkleBurst(carX, carGroundY, 1.0f, 1.0f, 1.0f, 16, 1.3f, 1.1f);

        char msg[64];
        sprintf(msg, "%dm MILESTONE! +30s", (int)reachedMilestone);

        strncpy(bonusDisplayText, msg, 63);
        bonusDisplayText[63] = '\0';

        bonusDisplayR = 0.20f;
        bonusDisplayG = 1.0f;
        bonusDisplayB = 0.30f;

        bonusDisplayTimer = 1.5f;

        nextDistanceMilestone += 1000.0f;
    }
}

void drawWheel(
    float x,
    float y,
    float radius,
    float rotation)
{
    glColor3f(
        0.075f,
        0.082f,
        0.090f
    );

    drawCircle(x, y, radius);

    glColor3f(
        0.15f,
        0.16f,
        0.17f
    );

    drawCircle(
        x,
        y,
        radius - 3.0f
    );

    glColor3f(
        0.78f,
        0.80f,
        0.80f
    );

    drawCircle(
        x,
        y,
        radius - 7.0f
    );

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(
        rotation,
        0,
        0,
        1
    );

    float innerRadius =
        radius - 8.0f;

    glColor3f(
        0.08f,
        0.09f,
        0.10f
    );

    for (int spoke = 0;
         spoke < 4;
         spoke++)
    {
        float angle =
            spoke *
            90.0f *
            PI /
            180.0f;

        float angleLeft =
            angle -
            8.0f *
            PI /
            180.0f;

        float angleRight =
            angle +
            8.0f *
            PI /
            180.0f;

        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(
            innerRadius * cos(angleLeft),
            innerRadius * sin(angleLeft)
        );
        glVertex2f(
            innerRadius * cos(angleRight),
            innerRadius * sin(angleRight)
        );
        glVertex2f(0, 0);
        glEnd();
    }

    glColor3f(
        0.92f,
        0.93f,
        0.92f
    );

    for (int spoke = 0;
         spoke < 4;
         spoke++)
    {
        float angle =
            spoke *
            90.0f *
            PI /
            180.0f;

        float angleLeft =
            angle -
            3.0f *
            PI /
            180.0f;

        float angleRight =
            angle +
            3.0f *
            PI /
            180.0f;

        float startRadius = 5.0f;

        glBegin(GL_QUADS);
        glVertex2f(
            startRadius * cos(angleLeft),
            startRadius * sin(angleLeft)
        );
        glVertex2f(
            innerRadius * cos(angleLeft),
            innerRadius * sin(angleLeft)
        );
        glVertex2f(
            innerRadius * cos(angleRight),
            innerRadius * sin(angleRight)
        );
        glVertex2f(
            startRadius * cos(angleRight),
            startRadius * sin(angleRight)
        );
        glEnd();
    }
    glColor3f(
        0.25f,
        0.27f,
        0.28f
    );
    drawCircle(0, 0, 5.0f);
    glColor3f(
        0.92f,
        0.93f,
        0.92f
    );
    drawCircle(0, 0, 2.7f);
    glPopMatrix();
    glColor3f(
        0.22f,
        0.23f,
        0.24f
    );
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);

    const int rimSegments = 96;

    for (int i = 0;
         i <= rimSegments;
         i++)
    {
        float angle =
            2.0f *
            PI *
            i /
            (float)rimSegments;

        glVertex2f(
            x +
            (radius - 7.0f) *
            cos(angle),

            y +
            (radius - 7.0f) *
            sin(angle)
        );
    }
    glEnd();
    glLineWidth(1.0f);
}

void drawCar()
{
    const float wheelDistance = 43.0f;
    const float wheelY = 0.0f;
    const float wheelRadius = 23.0f;

    float leftWheelX =
        carX - wheelDistance;

    float rightWheelX =
        carX + wheelDistance;

    float leftGround;

    if (isBridgeGap(leftWheelX))
    {
        leftGround =
            getBridgeHeight(leftWheelX) +
            getBridgeWheelClearance(leftWheelX);
    }
    else
    {
        leftGround =
            sampleGroundUnderWheel(leftWheelX, wheelRadius);
    }

    float rightGround;

    if (isBridgeGap(rightWheelX))
    {
        rightGround =
            getBridgeHeight(rightWheelX) +
            getBridgeWheelClearance(rightWheelX);
    }
    else
    {
        rightGround =
            sampleGroundUnderWheel(rightWheelX, wheelRadius);
    }

    float averageGround =
        (leftGround + rightGround) / 2.0f;

    float slopeAngle =
        atan2(
            rightGround - leftGround,
            2.0f * wheelDistance
        )
        *
        180.0f /
        PI;

    if (carVerticalOffset > 7.0f)
        carInAir = true;

    if (carVerticalOffset < 2.0f &&
        fabs(carVerticalVelocity) < 0.5f)
    {
        carInAir = false;
    }

    float desiredY =
        averageGround + 23.0f;

    float currentY =
        desiredY + carVerticalOffset;

    float springForce =
        (desiredY - currentY) * 0.22f;

    carVerticalVelocity += springForce;
    carVerticalVelocity -= 0.18f;
    carVerticalVelocity *= 0.84f;
    carVerticalOffset += carVerticalVelocity;

    if (carVerticalOffset < -1.0f)
    {
        carVerticalOffset = -1.0f;

        carVerticalVelocity =
            fabs(carVerticalVelocity) * 0.45f;
    }

    if (carInAir)
    {
        carAirRotation +=
            speed * 0.45f;
    }
    else
    {
        carAirRotation +=
            (slopeAngle - carAirRotation) *
            0.15f;
    }

    float screenX =
        carX - cameraX;

    glPushMatrix();

    glTranslatef(
        screenX,
        currentY,
        0
    );

    if (carInAir)
    {
        glRotatef(
            carAirRotation,
            0,
            0,
            1
        );
    }
    else
    {
        glRotatef(
            slopeAngle,
            0,
            0,
            1
        );
    }

    glColor4f(
        0.08f,
        0.07f,
        0.07f,
        0.28f
    );

    glBegin(GL_QUADS);
    glVertex2f(-67, 2);
    glVertex2f(-29, 2);
    glVertex2f(-31, -5);
    glVertex2f(-60, -5);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(29, 2);
    glVertex2f(68, 2);
    glVertex2f(61, -5);
    glVertex2f(31, -5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(
        0.478f,
        0.0f,
        0.0f
    );
    glVertex2f(-69, 8);
    glVertex2f(-31, 8);
    glColor3f(
        0.60f,
        0.0f,
        0.0f
    );
    glVertex2f(-27, 16);
    glVertex2f(-20, 21);
    glVertex2f(-10, 24);
    glVertex2f(0, 25);
    glVertex2f(10, 24);
    glVertex2f(20, 21);
    glVertex2f(27, 16);
    glColor3f(
        0.478f,
        0.0f,
        0.0f
    );
    glVertex2f(31, 8);
    glVertex2f(69, 8);
    glColor3f(
        0.815f,
        0.0f,
        0.0f
    );
    glVertex2f(66, 30);
    glVertex2f(-64, 30);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(
        0.478f,
        0.0f,
        0.0f
    );
    glVertex2f(-67, 18);
    glVertex2f(65, 18);
    glColor3f(
        0.815f,
        0.0f,
        0.0f
    );
    glVertex2f(67, 32);
    glVertex2f(55, 43);
    glColor3f(
        0.88f,
        0.035f,
        0.035f
    );
    glVertex2f(-48, 43);
    glVertex2f(-63, 34);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(
        0.68f,
        0.0f,
        0.0f
    );
    glVertex2f(19, 40);
    glVertex2f(58, 40);
    glColor3f(
        0.84f,
        0.025f,
        0.025f
    );
    glVertex2f(63, 32);
    glVertex2f(17, 32);
    glEnd();

    glColor3f(
        0.90f,
        0.08f,
        0.08f
    );

    glBegin(GL_QUADS);
    glVertex2f(22, 40);
    glVertex2f(55, 40);
    glVertex2f(51, 43);
    glVertex2f(25, 43);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(
        0.50f,
        0.0f,
        0.0f
    );
    glVertex2f(-63, 34);
    glVertex2f(-35, 35);
    glColor3f(
        0.72f,
        0.012f,
        0.018f
    );
    glVertex2f(-35, 43);
    glVertex2f(-60, 42);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(
        0.62f,
        0.0f,
        0.0f
    );
    glVertex2f(-38, 42);
    glVertex2f(30, 42);
    glColor3f(
        0.84f,
        0.025f,
        0.025f
    );
    glVertex2f(20, 70);
    glVertex2f(-25, 70);
    glEnd();

    glDisable(GL_BLEND);
    glColor3f(
        0.045f,
        0.055f,
        0.065f
    );

    glBegin(GL_QUADS);
    glVertex2f(-32, 45);
    glVertex2f(27, 45);
    glVertex2f(18, 66);
    glVertex2f(-23, 66);
    glEnd();

    glEnable(GL_BLEND);
    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glColor4f(
        0.35f,
        0.65f,
        0.95f,
        0.45f
    );

    glBegin(GL_POLYGON);
    glVertex2f(-32, 45);
    glVertex2f(27, 45);
    glVertex2f(18, 66);
    glVertex2f(-23, 66);
    glEnd();

    glColor4f(
        0.82f,
        0.95f,
        1.0f,
        0.14f
    );

    glBegin(GL_POLYGON);
    glVertex2f(-27, 48);
    glVertex2f(20, 48);
    glVertex2f(17, 57);
    glVertex2f(-23, 57);
    glEnd();

    glColor4f(
        0.04f,
        0.12f,
        0.20f,
        0.75f
    );

    glLineWidth(2.5f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-32, 45);
    glVertex2f(27, 45);
    glVertex2f(18, 66);
    glVertex2f(-23, 66);
    glEnd();

    glLineWidth(1.0f);

    glBegin(GL_QUADS);
    glColor3f(
        0.48f,
        0.0f,
        0.0f
    );
    glVertex2f(-3, 19);
    glVertex2f(38, 19);
    glColor3f(
        0.76f,
        0.012f,
        0.025f
    );
    glVertex2f(35, 39);
    glVertex2f(-3, 39);
    glEnd();

    glColor3f(
        0.38f,
        0.0f,
        0.0f
    );

    glLineWidth(2.0f);

    glBegin(GL_LINE_STRIP);
    glVertex2f(-3, 19);
    glVertex2f(-3, 39);
    glVertex2f(35, 39);
    glVertex2f(38, 19);
    glEnd();

    glLineWidth(1.0f);

    glColor3f(
        0.83f,
        0.74f,
        0.55f
    );

    glBegin(GL_QUADS);
    glVertex2f(25, 35);
    glVertex2f(34, 35);
    glVertex2f(34, 38);
    glVertex2f(25, 38);
    glEnd();

    glColor3f(
        0.92f,
        0.08f,
        0.07f
    );

    glBegin(GL_QUADS);
    glVertex2f(-55, 26);
    glVertex2f(53, 26);
    glVertex2f(51, 30);
    glVertex2f(-53, 30);
    glEnd();

    glColor3f(
        0.075f,
        0.085f,
        0.09f
    );

    glBegin(GL_QUADS);
    glVertex2f(58, 19);
    glVertex2f(68, 19);
    glVertex2f(68, 32);
    glVertex2f(58, 32);
    glEnd();

    glColor3f(
        0.25f,
        0.26f,
        0.27f
    );

    for (int i = 0; i < 3; i++)
    {
        glBegin(GL_QUADS);
        glVertex2f(
            60 + i * 3.0f,
            21
        );
        glVertex2f(
            61.5f + i * 3.0f,
            21
        );
        glVertex2f(
            61.5f + i * 3.0f,
            30
        );
        glVertex2f(
            60 + i * 3.0f,
            30
        );
        glEnd();
    }
    glColor3f(
        1.0f,
        0.86f,
        0.45f
    );
    drawCircle(
        62,
        29,
        5.5f
    );
    glColor3f(
        1.0f,
        0.98f,
        0.78f
    );
    drawCircle(
        60.5f,
        30.5f,
        2.0f
    );
    glColor3f(
        0.36f,
        0.015f,
        0.018f
    );

    glBegin(GL_QUADS);
    glVertex2f(-67, 29);
    glVertex2f(-61, 29);
    glVertex2f(-61, 37);
    glVertex2f(-67, 37);
    glEnd();

    glColor3f(
        0.95f,
        0.08f,
        0.05f
    );
    glBegin(GL_QUADS);
    glVertex2f(-66, 30);
    glVertex2f(-62, 30);
    glVertex2f(-62, 35);
    glVertex2f(-66, 35);
    glEnd();

    glColor3f(
        0.96f,
        0.12f,
        0.10f
    );
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-58, 20);
    glVertex2f(-20, 20);
    glVertex2f(20, 20);
    glVertex2f(55, 20);
    glEnd();

    glLineWidth(1.0f);
    drawWheel(
        -wheelDistance,
        wheelY,
        wheelRadius,
        wheelRotation
    );
    drawWheel(
        wheelDistance,
        wheelY,
        wheelRadius,
        wheelRotation
    );
    glColor3f(
        0.478f,
        0.0f,
        0.0f
    );
    glLineWidth(3.0f);
    const int fenderSegments = 60;
    glBegin(GL_LINE_STRIP);

    for (int i = 0;
         i <= fenderSegments;
         i++)
    {
        float a =
            PI *
            (float)i /
            (float)fenderSegments;

        float px =
            -43.0f +
            25.0f * cos(a);

        float py =
            wheelY +
            25.0f * sin(a);

        glVertex2f(px, py);
    }

    glEnd();

    glBegin(GL_LINE_STRIP);

    for (int i = 0;
         i <= fenderSegments;
         i++)
    {
        float a =
            PI *
            (float)i /
            (float)fenderSegments;

        float px =
            43.0f +
            25.0f * cos(a);

        float py =
            wheelY +
            25.0f * sin(a);

        glVertex2f(px, py);
    }

    glEnd();

    glLineWidth(1.0f);
    glColor3f(
        0.38f,
        0.0f,
        0.0f
    );
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);

    glVertex2f(-69, 8);
    glVertex2f(-67, 32);
    glVertex2f(-60, 42);
    glVertex2f(-48, 43);
    glVertex2f(-38, 43);
    glVertex2f(-25, 70);
    glVertex2f(20, 70);
    glVertex2f(30, 42);
    glVertex2f(55, 43);
    glVertex2f(67, 32);
    glVertex2f(69, 8);

    glEnd();

    glLineWidth(1.0f);

    glDisable(GL_BLEND);

    glPopMatrix();
}

void drawMilestoneSigns()
{
    const float milestoneSpacing = 750.0f;

    float firstWorld =
        floor((cameraX - 300.0f) / milestoneSpacing) *
        milestoneSpacing;

    float lastWorld =
        cameraX +
        WINDOW_WIDTH +
        300.0f;

    for (float worldX = firstWorld;
         worldX <= lastWorld;
         worldX += milestoneSpacing)
    {
        if (worldX < 1.0f)
            continue;

        if (isBridgeGap(worldX))
            continue;

        float groundY =
            getBaseTerrainHeight(worldX);

        float screenX =
            worldX - cameraX;

        if (screenX < -80.0f ||
            screenX > WINDOW_WIDTH + 80.0f)
        {
            continue;
        }

        glColor3f(
            0.20f,
            0.10f,
            0.045f
        );

        glBegin(GL_QUADS);

        glVertex2f(screenX - 3.0f, groundY);
        glVertex2f(screenX + 3.0f, groundY);
        glVertex2f(screenX + 3.0f, groundY + 48.0f);
        glVertex2f(screenX - 3.0f, groundY + 48.0f);

        glEnd();

        glColor3f(
            0.72f,
            0.55f,
            0.25f
        );

        glBegin(GL_QUADS);

        glVertex2f(screenX - 28.0f, groundY + 38.0f);
        glVertex2f(screenX + 28.0f, groundY + 38.0f);
        glVertex2f(screenX + 28.0f, groundY + 54.0f);
        glVertex2f(screenX - 28.0f, groundY + 54.0f);

        glEnd();

        char markerText[32];

        sprintf(
            markerText,
            "%dm",
            (int)worldX
        );

        glColor3f(
            0.30f,
            0.18f,
            0.07f
        );

        drawText(
            screenX - 20.0f,
            groundY + 42.0f,
            markerText
        );
    }
}
void drawTrophy(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(1.0f, 0.72f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(-10.0f, 8.0f);
    glVertex2f(10.0f, 8.0f);
    glVertex2f(8.0f, -5.0f);
    glVertex2f(5.0f, -12.0f);
    glVertex2f(-5.0f, -12.0f);
    glVertex2f(-8.0f, -5.0f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-9.0f, 4.0f);
    glVertex2f(-16.0f, 4.0f);
    glVertex2f(-16.0f, -4.0f);
    glVertex2f(-9.0f, -4.0f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(9.0f, 4.0f);
    glVertex2f(16.0f, 4.0f);
    glVertex2f(16.0f, -4.0f);
    glVertex2f(9.0f, -4.0f);
    glEnd();
    glLineWidth(1.0f);

    glColor3f(0.95f, 0.58f, 0.03f);
    glBegin(GL_QUADS);
    glVertex2f(-2.0f, -12.0f);
    glVertex2f(2.0f, -12.0f);
    glVertex2f(2.0f, -19.0f);
    glVertex2f(-2.0f, -19.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-9.0f, -19.0f);
    glVertex2f(9.0f, -19.0f);
    glVertex2f(9.0f, -23.0f);
    glVertex2f(-9.0f, -23.0f);
    glEnd();

    glColor3f(1.0f, 0.95f, 0.55f);
    drawCircle(-4.0f, 2.0f, 2.0f);
    glPopMatrix();
}

void drawHUD()
{
    const float fuelIconX = 30.0f;
    const float fuelIconY = 566.0f;
    const float fuelBarLeft = 54.0f;
    const float fuelBarRight = 205.0f;
    const float fuelBarBottom = 552.0f;
    const float fuelBarTop = 578.0f;
    const float fuelBarWidth = fuelBarRight - fuelBarLeft;

    drawFuelCanister(fuelIconX, fuelIconY, 1.05f);

    glColor4f(0.83f, 0.89f, 0.92f, 0.18f);
    glBegin(GL_QUADS);
    glVertex2f(fuelBarLeft, fuelBarBottom);
    glVertex2f(fuelBarRight, fuelBarBottom);
    glVertex2f(fuelBarRight, fuelBarTop);
    glVertex2f(fuelBarLeft, fuelBarTop);
    glEnd();

    glColor3f(0.30f, 0.42f, 0.45f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(fuelBarLeft, fuelBarBottom);
    glVertex2f(fuelBarRight, fuelBarBottom);
    glVertex2f(fuelBarRight, fuelBarTop);
    glVertex2f(fuelBarLeft, fuelBarTop);
    glEnd();
    glLineWidth(1.0f);

    float clampedFuel = fuel;
    if (clampedFuel < 0.0f)
        clampedFuel = 0.0f;
    if (clampedFuel > 100.0f)
        clampedFuel = 100.0f;

    float fillWidth =
        (fuelBarWidth - 4.0f) * (clampedFuel / 100.0f);

    bool lowFuel = clampedFuel <= 25.0f;
    bool blinkVisible =
        !lowFuel || fmod(animationTime * 4.0f, 2.0f) < 1.0f;

    if (blinkVisible && fillWidth > 0.0f)
    {
        if (lowFuel)
            glColor3f(0.95f, 0.08f, 0.06f);
        else
            glColor3f(0.16f, 0.92f, 0.18f);

        glBegin(GL_QUADS);
        glVertex2f(fuelBarLeft + 2.0f, fuelBarBottom + 2.0f);
        glVertex2f(fuelBarLeft + 2.0f + fillWidth, fuelBarBottom + 2.0f);
        glVertex2f(fuelBarLeft + 2.0f + fillWidth, fuelBarTop - 2.0f);
        glVertex2f(fuelBarLeft + 2.0f, fuelBarTop - 2.0f);
        glEnd();
    }

    char fuelText[32];
    sprintf(fuelText, "%.0f%%", clampedFuel);

    float fuelTextWidth = textWidthBitmap(fuelText);
    float fuelTextX =
        fuelBarLeft + (fuelBarWidth - fuelTextWidth) / 2.0f;

    drawHudText(fuelTextX, 558.0f, fuelText);
    drawCoinIcon(31.0f, 521.0f, 0.95f);
    char coinText[50];
    sprintf(coinText, "%d", coinsCollected);
    drawHudText(54.0f, 515.0f, coinText);

    float progress = 0.0f;
    if (targetDistance > 0.0f)
    {
        progress = distanceTravelled / targetDistance;

        if (progress < 0.0f)
            progress = 0.0f;
        if (progress > 1.0f)
            progress = 1.0f;
    }

    char distanceText[50];
    sprintf(distanceText, "%dm", (int)distanceTravelled);

    char timeText[50];
    sprintf(timeText, "TIME: %.0fs", timeLeft);

    char goalText[50];
    sprintf(goalText, "GOAL: %.0fm", targetDistance);

    const float barWidthPx = 140.0f;
    const float gapSmall = 16.0f;

    float distanceTextW = textWidthBitmap(distanceText);
    float timeTextW = textWidthBitmap(timeText);
    float goalTextW = textWidthBitmap(goalText);

    float clusterTotalWidth =
        distanceTextW + gapSmall + barWidthPx +
        gapSmall + timeTextW + gapSmall + goalTextW;

    float clusterCenterX = WINDOW_WIDTH / 2.0f;
    float clusterStartX = clusterCenterX - clusterTotalWidth / 2.0f;

    float distanceTextX = clusterStartX;
    float barLeft = distanceTextX + distanceTextW + gapSmall;
    float barRight = barLeft + barWidthPx;
    float timeTextX = barRight + gapSmall;
    float goalTextX = timeTextX + timeTextW + gapSmall;

    const float progressY = 571.0f;
    const float lineTextY = 565.0f;

    drawHudText(distanceTextX, lineTextY, distanceText);

    glColor3f(0.94f, 0.96f, 0.98f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(barLeft, progressY);
    glVertex2f(barRight, progressY);
    glEnd();
    glLineWidth(1.0f);

    float markerX = barLeft + (barRight - barLeft) * progress;

    glColor3f(1.0f, 0.62f, 0.08f);
    drawCircle(markerX, progressY, 5.0f);

    if (timeLeft <= 10.0f)
        drawHudTextColor(timeTextX, lineTextY, timeText, 1.0f, 0.20f, 0.12f);
    else if (timeLeft <= 20.0f)
        drawHudTextColor(timeTextX, lineTextY, timeText, 1.0f, 0.70f, 0.10f);
    else
        drawHudText(timeTextX, lineTextY, timeText);

    drawHudText(goalTextX, lineTextY, goalText);

    if (bonusDisplayTimer > 0.0f)
    {
        const float bonusMaxTime = 1.5f;

        float bonusProgress = bonusDisplayTimer / bonusMaxTime;

        if (bonusProgress > 1.0f)
            bonusProgress = 1.0f;

        float pulse = 0.90f + 0.10f * sin(animationTime * 14.0f);
        float rise = (1.0f - bonusProgress) * 10.0f;
        float alpha = bonusProgress;

        const float milestoneCenterX = WINDOW_WIDTH / 2.0f;
        const float milestoneCenterY = 430.0f + rise;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        drawStrokeTextCentered(
            milestoneCenterX,
            milestoneCenterY,
            bonusDisplayText,
            0.13f * pulse,
            bonusDisplayR * alpha + (1.0f - alpha) * 0.0f,
            bonusDisplayG * alpha + (1.0f - alpha) * 0.0f,
            bonusDisplayB * alpha + (1.0f - alpha) * 0.0f
        );
    }

    char flagTargetText[50];
    sprintf(flagTargetText, "%.0fm", targetDistance);

    char bestText[50];
    sprintf(bestText, "%.0fm", highScore);

    float flagTargetW = textWidthBitmap(flagTargetText);
    float bestTextW = textWidthBitmap(bestText);

    const float flagIconWidth = 40.0f;
    const float trophyIconWidth = 36.0f;
    const float rowGapSmall = 10.0f;
    const float rowGapBig = 26.0f;

    float rowTotalWidth =
        flagIconWidth + rowGapSmall + flagTargetW +
        rowGapBig +
        trophyIconWidth + rowGapSmall + bestTextW;

    const float rowRightMargin = 30.0f;
    float rowStartX = (WINDOW_WIDTH - rowRightMargin) - rowTotalWidth;

    const float rowY = 566.0f;

    glColor3f(0.30f, 0.15f, 0.07f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(rowStartX + 6.0f, rowY - 12.0f);
    glVertex2f(rowStartX + 6.0f, rowY + 14.0f);
    glEnd();
    glLineWidth(1.0f);

    glColor3f(0.84f, 0.08f, 0.05f);
    glBegin(GL_TRIANGLES);
    glVertex2f(rowStartX + 7.0f, rowY + 13.0f);
    glVertex2f(rowStartX + 34.0f, rowY + 7.0f);
    glVertex2f(rowStartX + 7.0f, rowY + 1.0f);
    glEnd();

    float flagTextX = rowStartX + flagIconWidth + rowGapSmall;
    drawHudText(flagTextX, rowY - 6.0f, flagTargetText);

    float trophyX = flagTextX + flagTargetW + rowGapBig;
    drawTrophy(trophyX + trophyIconWidth / 2.0f - 4.0f, rowY, 0.85f);

    float bestTextX = trophyX + trophyIconWidth + rowGapSmall;
    drawHudText(bestTextX, rowY - 6.0f, bestText);

    if (gameOver)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0.0f, 0.0f, 0.0f, 0.55f);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f((float)WINDOW_WIDTH, 0.0f);
        glVertex2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
        glVertex2f(0.0f, (float)WINDOW_HEIGHT);
        glEnd();

        const float goCenterX = WINDOW_WIDTH / 2.0f;
        const float titleY = 358.0f;

        if (timeUp)
            drawStrokeTextCentered(goCenterX, titleY, "TIME UP! GAME OVER", 0.145f, 1.0f, 0.14f, 0.10f);
        else
            drawStrokeTextCentered(goCenterX, titleY, "GAME OVER", 0.20f, 1.0f, 0.14f, 0.10f);

        float lineY = 305.0f;
        const float lineGap = 34.0f;
        char finalDistanceText[64];
        sprintf(finalDistanceText, "Distance: %.0fm", distanceTravelled);
        {
            float w = textWidthBitmap(finalDistanceText);
            drawHudTextColor(goCenterX - w / 2.0f, lineY, finalDistanceText, 1.0f, 1.0f, 1.0f);
        }
        lineY -= lineGap;
        char bestSummary[64];
        sprintf(bestSummary, "Best: %.0fm", highScore);
        {
            float w = textWidthBitmap(bestSummary);
            drawHudTextColor(goCenterX - w / 2.0f, lineY, bestSummary, 1.0f, 0.82f, 0.10f);
        }
        lineY -= lineGap;
        char coinSummary[64];
        sprintf(coinSummary, "+ %d Coins", coinsCollected);
        {
            float w = textWidthBitmap(coinSummary);
            drawHudTextColor(goCenterX - w / 2.0f, lineY, coinSummary, 0.20f, 1.0f, 0.30f);
        }
        lineY -= lineGap;

        const char* restartText = "PRESS R TO RESTART";
        {
            float w = textWidthBitmap(restartText);
            drawHudTextColor(goCenterX - w / 2.0f, lineY, restartText, 0.92f, 0.94f, 0.98f);
        }
    }
}

void display()
{
    glClear(
        GL_COLOR_BUFFER_BIT
    );

    glLoadIdentity();

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glEnable(GL_LINE_SMOOTH);

    glHint(
        GL_LINE_SMOOTH_HINT,
        GL_NICEST
    );

    glEnable(GL_POLYGON_SMOOTH);

    glHint(
        GL_POLYGON_SMOOTH_HINT,
        GL_NICEST
    );

    glEnable(GL_POINT_SMOOTH);

    glHint(
        GL_POINT_SMOOTH_HINT,
        GL_NICEST
    );

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

    glutSwapBuffers();
}

void reshape(
    int width,
    int height)
{
    if (height == 0)
        height = 1;

    glViewport(
        0,
        0,
        width,
        height
    );

    glMatrixMode(
        GL_PROJECTION
    );

    glLoadIdentity();

    gluOrtho2D(
        0,
        WINDOW_WIDTH,
        0,
        WINDOW_HEIGHT
    );

    glMatrixMode(
        GL_MODELVIEW
    );

    glLoadIdentity();
}

void keyboardUp(
    unsigned char key,
    int x,
    int y)
{
    if (key == 'b' || key == 'B')
        brakeKey = false;

    if (key == 's' || key == 'S')
        boostKey = false;
}

void specialKeyDown(
    int key,
    int x,
    int y)
{
    if (key == GLUT_KEY_RIGHT)
        rightKey = true;

    if (key == GLUT_KEY_LEFT)
        leftKey = true;

    if (key == GLUT_KEY_UP)
        upKey = true;

    if (key == GLUT_KEY_DOWN)
        downKey = true;
}

void specialKeyUp(
    int key,
    int x,
    int y)
{
    if (key == GLUT_KEY_RIGHT)
        rightKey = false;

    if (key == GLUT_KEY_LEFT)
        leftKey = false;

    if (key == GLUT_KEY_UP)
        upKey = false;

    if (key == GLUT_KEY_DOWN)
        downKey = false;
}

void keyboard(
    unsigned char key,
    int x,
    int y)
{
    if (key == 27)
        exit(0);

    if (key == 'b' || key == 'B')
        brakeKey = true;

    if (key == 's' || key == 'S')
        boostKey = true;

    if (key == 'r' || key == 'R')
    {
        carX = 350.0f;
        speed = 0.0f;
        cameraX = 0.0f;
        wheelRotation = 0.0f;

        carVerticalOffset = 0.0f;
        carVerticalVelocity = 0.0f;
        carAirRotation = 0.0f;
        carInAir = false;

        fuel = 100.0f;
        distanceTravelled = 0.0f;
        timeLeft = 60.0f;
        targetDistance = 300.0f;
        timeUp = false;
        bonusDisplayTimer = 0.0f;
        gameOver = false;

        rightKey = false;
        leftKey = false;
        upKey = false;
        downKey = false;
        brakeKey = false;
        boostKey = false;
        animationTime = 0.0f;

        initializeCoins();
        initializeFuel();
        initializeBridges();
        initializeDust();
        initializeSparkles();
        initializeFloatingTexts();

        nextCoinMilestone = 100.0f;
        nextDistanceMilestone = 1000.0f;
        bonusDisplayText[0] = '\0';
    }
}

void triggerGameOver(bool timedOut)
{
    if (gameOver)
        return;

    if (distanceTravelled > highScore)
        highScore = distanceTravelled;

    timeUp = timedOut;
    gameOver = true;
    speed = 0.0f;
}

void timer(int value)
{
    if (!gameOver)
    {
        timeLeft -= 0.016f;

        if (bonusDisplayTimer > 0.0f)
        {
            bonusDisplayTimer -= 0.016f;
            if (bonusDisplayTimer < 0.0f)
                bonusDisplayTimer = 0.0f;
        }

        if (timeLeft < 0.0f)
            timeLeft = 0.0f;

        if (rightKey)
        {
            speed += 0.12f;

            if (speed > 6.0f)
                speed = 6.0f;
        }

        if (leftKey)
        {
            speed -= 0.12f;

            if (speed < -4.0f)
                speed = -4.0f;
        }

        if (upKey)
        {
            speed += 0.08f;

            if (speed > 7.0f)
                speed = 7.0f;
        }

        if (downKey)
        {
            if (speed > 0)
                speed -= 0.25f;

            if (speed < 0)
                speed += 0.25f;
        }

        if (brakeKey)
        {
            if (speed > 0.0f)
            {
                speed -= 0.35f;

                if (speed < 0.0f)
                    speed = 0.0f;
            }
            else if (speed < 0.0f)
            {
                speed += 0.35f;

                if (speed > 0.0f)
                    speed = 0.0f;
            }
        }
        if (boostKey)
        {
            speed += 0.22f;

            if (speed > 10.0f)
                speed = 10.0f;
        }

        if (!rightKey &&
            !leftKey &&
            !upKey &&
            !downKey &&
            !brakeKey &&
            !boostKey)
        {
            if (speed > 0)
            {
                speed -= 0.04f;

                if (speed < 0)
                    speed = 0;
            }

            if (speed < 0)
            {
                speed += 0.04f;

                if (speed > 0)
                    speed = 0;
            }
        }

        carX += speed;

        if (carX < 80)
        {
            carX = 80;
            speed = 0;
        }

        distanceTravelled =
            (carX - 350.0f) * 0.05f;

        if (distanceTravelled < 0)
            distanceTravelled = 0;

        if (speed > 0)
            fuel -= 0.018f * speed;

        if (boostKey && speed > 0)
            fuel -= 0.040f * speed;

        if (fuel < 0)
            fuel = 0;

        animationTime += 0.016f;
        updateBridgePhysics();
        updateCoinSpawning();
        checkCoins();
        updateFuelSpawning();
        checkFuelPickups();

        if (distanceTravelled >= targetDistance)
        {
            targetDistance += 300.0f;
        }

        checkDistanceMilestones();
        updateSparkleParticles();
        updateFloatingTexts();

        if (fuel <= 0.0f)
        {
            fuel = 0.0f;
            triggerGameOver(false);
        }
        else if (timeLeft <= 0.0f &&
                 distanceTravelled < targetDistance)
        {
            timeLeft = 0.0f;
            triggerGameOver(true);
        }
        if (!gameOver && fabs(speed) > 1.5f && !carInAir)
        {
            float leftWX =
                carX - WHEEL_OFFSET;

            float rightWX =
                carX + WHEEL_OFFSET;

            spawnDustParticle(
                leftWX,
                getTerrainHeight(leftWX)
            );

            spawnDustParticle(
                rightWX,
                getTerrainHeight(rightWX)
            );
        }

        updateDustParticles();

        wheelRotation -=
            speed * 7.0f;

        float targetCamera =
            carX - 400.0f;

        cameraX +=
            (targetCamera - cameraX) *
            0.08f;
    }

    glutPostRedisplay();

    glutTimerFunc(
        16,
        timer,
        0
    );
}
void init()
{
    glClearColor(
        0.82f,
        0.90f,
        0.96f,
        1.0f
    );

    srand(1);

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_LINE_SMOOTH);

    glHint(
        GL_LINE_SMOOTH_HINT,
        GL_NICEST
    );

    glEnable(GL_POLYGON_SMOOTH);

    glHint(
        GL_POLYGON_SMOOTH_HINT,
        GL_NICEST
    );

    glEnable(GL_POINT_SMOOTH);

    glHint(
        GL_POINT_SMOOTH_HINT,
        GL_NICEST
    );

    glMatrixMode(
        GL_PROJECTION
    );

    glLoadIdentity();

    gluOrtho2D(
        0,
        WINDOW_WIDTH,
        0,
        WINDOW_HEIGHT
    );

    glMatrixMode(
        GL_MODELVIEW
    );

    glLoadIdentity();

    initializeCoins();
    initializeFuel();
    initializeBridges();
    initializeDust();
    initializeSparkles();
    initializeFloatingTexts();

    nextCoinMilestone = 100.0f;
    nextDistanceMilestone = 1000.0f;
    bonusDisplayText[0] = '\0';
}

int main(
    int argc,
    char** argv)
{
    glutInit(
        &argc,
        argv
    );
    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGBA |
        GLUT_MULTISAMPLE
    );
    glutInitWindowPosition(
        100,
        50
    );
    glutInitWindowSize(
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );
    glutCreateWindow(
        "Hill Rider"
    );
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);
    glutReshapeFunc(reshape);
    glutTimerFunc(
        0,
        timer,
        0
    );
    glutMainLoop();
    return 0;
}
