#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "constants.h"

// map of our matrix
int matrix[MATRIX_HEIGHT][MATRIX_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,_,_,_,2,2,2,2,2,_,_,_,_,3,_,3,_,3,_,_,_,1},
    {1,_,_,_,_,_,2,_,_,_,2,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,_,_,_,2,_,_,_,2,_,_,_,_,3,_,_,_,3,_,_,_,1},
    {1,_,_,_,_,_,2,_,_,_,2,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,_,_,_,2,2,_,2,2,_,_,_,_,3,_,3,_,3,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1}, 
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1}, 
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,5,_,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,5,_,_,_,_,1},
    {1,4,4,4,4,4,4,4,4,_,_,_,_,_,_,_,_,_,5,_,_,_,_,1},
    {1,4,_,4,_,_,_,_,4,_,_,_,_,_,_,_,_,_,5,_,_,_,_,1},
    {1,4,_,_,_,_,5,_,4,_,_,_,_,_,_,_,_,_,5,_,_,_,_,1},
    {1,4,_,4,_,_,_,_,4,_,_,_,_,_,_,_,_,_,5,_,_,_,_,1},
    {1,4,_,4,4,4,4,4,4,_,_,_,_,_,_,_,_,_,5,_,_,_,_,1},
    {1,4,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,4,4,4,4,4,4,4,4,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// vectors for player position, the camera plane, and direction
Vector2 playerPos = {(float)SCREEN_WIDTH/4, (float)SCREEN_HEIGHT/2};
Vector2 directionV;
float playerAngle;


// rendering the 2D map
void render2DMap() {
    int i, j;
    for (i = 0; i < MATRIX_HEIGHT; i++) {
        for (j = 0; j < MATRIX_WIDTH; j++) {
            Color c;
            switch (matrix[i][j]) {
                case 0: c = BLACK; break;
                case 1: c = WHITE; break;
                case 2: c = RED; break;
                case 3: c = GREEN; break;
                case 4: c = BLUE; break;
                case 5: c = ORANGE; break;
            }

            DrawRectangle(j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE,TILE_SIZE, c);
        }
    }
}

void render2DPlayer() {

    if (IsKeyDown(KEY_D)) {
        // turn clockwise, so increase angle
        playerAngle += 2*DEG1;
        // reset angle once its too large
        if (playerAngle > 2*PI) playerAngle -= 2*PI;
        directionV.x = cos(playerAngle);
        directionV.y = sin(playerAngle);
    }

    if (IsKeyDown(KEY_A)) {
        // turn counter-clockwise, so decrease angle
        playerAngle -= 2*DEG1;
        // reset angle once its too small
        if (playerAngle < 0) playerAngle += 2*PI;
        directionV.x = cos(playerAngle);
        directionV.y = sin(playerAngle);
    }

    if (IsKeyDown(KEY_W)) {
        playerPos.x += directionV.x;
        playerPos.y += directionV.y;
    }

    if (IsKeyDown(KEY_S)) {
        playerPos.x -= directionV.x;
        playerPos.y -= directionV.y; }

    // drawing player
    DrawCircleV(playerPos, 5, YELLOW);

    // draw ray for direction player is facing
    DrawLine(
        playerPos.x, playerPos.y, 
        playerPos.x + directionV.x * 20,
        playerPos.y + directionV.y * 20,
        YELLOW
    );
}


float distance(Vector2 v1, Vector2 v2) {
    return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)));
}

// darkens a color by a certain float value
Color DarkenColor(Color baseColor, float amount) {
    baseColor.r = (unsigned char)(baseColor.r * amount);
    baseColor.g = (unsigned char)(baseColor.g * amount);
    baseColor.b = (unsigned char)(baseColor.b * amount);
    return baseColor;
}

void renderRay() {
    Vector2 rayV, offsetV;
    // depth of field for number of checks
    int dof, i, j, vIndex, hIndex, cIndex, side;
    float distanceTotal;
    Color c = RED;

    // offset the angle
    float rayAngle = playerAngle - HALFDEG * 60;
    if (rayAngle < 0) rayAngle += 2*PI;
    if (rayAngle > 2*PI) rayAngle -= 2*PI;

    // cast each angle one by one till we get a 60 degree FOV
    for (int r = 0; r < 120; r++) {

        /* CHECKING FOR HORIZONTAL LINES */

        dof = 0;
        float invTan = -1/tan(rayAngle);

        float horizontalDist = 100000000;
        Vector2 horizontalV = { playerPos.x, playerPos.y };

        // check if we're looking up
        if (rayAngle > PI) {
            rayV.y = (floor(playerPos.y/TILE_SIZE) * TILE_SIZE) - 0.0001;
            rayV.x = (playerPos.y - rayV.y) * invTan + playerPos.x;
            offsetV.y = -TILE_SIZE;
            offsetV.x = TILE_SIZE * invTan;
        }

        // check if we're looking down
        if (rayAngle < PI) {
            rayV.y = (floor(playerPos.y/TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
            rayV.x = (playerPos.y - rayV.y) * invTan + playerPos.x;
            offsetV.y = TILE_SIZE;
            offsetV.x = -TILE_SIZE * invTan;
        }

        // looking straight left or right
        if (rayAngle == 0 || FloatEquals(rayAngle, PI)) {
            rayV.x = playerPos.x;
            rayV.y = playerPos.y;
            dof = 25;
        }

        // checking for walls
        while (dof < 25) {
            i = (int)rayV.y / TILE_SIZE;
            j = (int)rayV.x / TILE_SIZE;

            // check if we hit a wall, if so, end loop
            if (i >= 0 && j >= 0 && i < MATRIX_HEIGHT && j < MATRIX_WIDTH && matrix[i][j] > 0) {
                horizontalV.x = rayV.x;
                horizontalV.y = rayV.y;
                horizontalDist = distance(playerPos, horizontalV);
                dof = 25;
                hIndex = matrix[i][j];
            } else {
                rayV.x += offsetV.x;
                rayV.y += offsetV.y;
                dof += 1;
            }

        }

        /* CHECKING FOR VERTICAL LINES */

        dof = 0;
        float nTan = -1 * tan(rayAngle);

        float verticalDist = 100000000;
        Vector2 verticalV = { playerPos.x, playerPos.y };

        // check if we're looking left
        if (rayAngle > PI/2 && rayAngle < 3*PI/2) {
            rayV.x = (floor(playerPos.x/TILE_SIZE) * TILE_SIZE) - 0.0001;
            rayV.y = (playerPos.x - rayV.x) * nTan + playerPos.y;
            offsetV.x = -TILE_SIZE;
            offsetV.y = TILE_SIZE * nTan;
        }

        // check if we're looking right
        if (rayAngle < PI/2 || rayAngle > 3*PI/2 ) {
            rayV.x = (floor(playerPos.x/TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
            rayV.y = (playerPos.x - rayV.x) * nTan + playerPos.y;
            offsetV.x = TILE_SIZE;
            offsetV.y = -TILE_SIZE * nTan;
        }

        // looking straight up or down
        if (rayAngle == 0 || FloatEquals(rayAngle, PI)) {
            rayV.x = playerPos.x;
            rayV.y = playerPos.y;
            dof = 25;
        }

        // checking for walls
        while (dof < 25) {
            i = (int)rayV.y / TILE_SIZE;
            j = (int)rayV.x / TILE_SIZE;

            // check if we hit a wall, if so, end loop
            if (i >= 0 && j >= 0 && i < MATRIX_HEIGHT && j < MATRIX_WIDTH && matrix[i][j] > 0) {
                verticalV.x = rayV.x;
                verticalV.y = rayV.y;
                verticalDist = distance(playerPos, verticalV);
                dof = 25;
                vIndex = matrix[i][j];
            } else {
                rayV.x += offsetV.x;
                rayV.y += offsetV.y;
                dof += 1;
            }
        }

        // get shortest distance between horizontal and vertical check
        if (verticalDist > horizontalDist) {
            rayV = horizontalV;
            distanceTotal = horizontalDist;
            cIndex = hIndex;
            side = 1;
        } else if (verticalDist < horizontalDist) {
            rayV = verticalV;
            distanceTotal = verticalDist;
            cIndex = vIndex;
            side = 0;
        }

        DrawLineV(playerPos, rayV, YELLOW);


        switch (cIndex) {
            case 1: c = WHITE; break;
            case 2: c = RED; break;
            case 3: c = GREEN; break;
            case 4: c = BLUE; break;
            case 5: c = ORANGE; break;
        }

        // darken side
        if (side) c = DarkenColor(c, 0.8f);


        /* RENDER 3D SPACE */

        // for fisheye fix
        float cameraAngle = playerAngle - rayAngle;
        if (cameraAngle < 0) cameraAngle += 2*PI;
        if (cameraAngle > 2*PI) cameraAngle -= 2*PI;

        distanceTotal = distanceTotal * cos(cameraAngle);

        float lineHeight = (TILE_SIZE * SCREEN_HEIGHT) / distanceTotal;
        float lineOffset = ((float)SCREEN_HEIGHT/2) - (lineHeight/2);

        Vector2 start = {r*4+((float)SCREEN_WIDTH/2), lineOffset};
        Vector2 end = {r*4+((float)SCREEN_WIDTH/2), lineHeight+lineOffset};

        DrawLineEx(start, end, 4, c);

        rayAngle += HALFDEG;
        if (rayAngle < 0) rayAngle += 2*PI;
        if (rayAngle > 2*PI) rayAngle -= 2*PI;
    }
}


int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [02] wolf3d raycasting");
    SetTargetFPS(60);

    directionV.x = cos(playerAngle);
    directionV.y = sin(playerAngle);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        render2DMap();
        renderRay();
        render2DPlayer();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
