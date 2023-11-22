#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 20
#define MAX_PARTICLES (20 * 20)

int xPos[MAX_PARTICLES];
int yPos[MAX_PARTICLES];
int prevX[MAX_PARTICLES];
int prevY[MAX_PARTICLES];
int xVel[MAX_PARTICLES];
int yVel[MAX_PARTICLES];
int isActive[MAX_PARTICLES];
int totalParticles = 0;

// Load particle data from the input file
void loadData(FILE *file) {
    while (fscanf(file, "%d, %d, %d, %d", &xPos[totalParticles], &yPos[totalParticles], 
                                         &xVel[totalParticles], &yVel[totalParticles]) != EOF) {
        totalParticles++;
    }
}

// Update particle positions based on velocities
void moveParticle(int n) {
    xPos[n] += xVel[n];
    yPos[n] += yVel[n];
}

// Check particle boundaries and adjust velocities accordingly
void checkBounds(int n) {
    if (xPos[n] <= 0 || xPos[n] >= GRID_SIZE - 1) {
        xVel[n] = -xVel[n];
    }
    if (yPos[n] <= 0 || yPos[n] >= GRID_SIZE - 1) {
        yVel[n] = -yVel[n];
    }
}

// Handle collisions between particles and deactivate colliding ones
void handleCollisions() {
    for (int i = 0; i < totalParticles; i++) {
        if (!isActive[i]) continue;

        for (int j = i+1; j < totalParticles; j++) {
            if (!isActive[j]) continue;

            if (xPos[i] == xPos[j] && yPos[i] == yPos[j]) {
                isActive[i] = isActive[j] = 0;
            }
        }
    }
}

// Remove deactivated particles from the list
void refreshParticles() {
    int x = 0;
    for (int i = 0; i < totalParticles; i++) {
        if (isActive[i]) {
            xPos[x] = xPos[i];
            yPos[x] = yPos[i];
            xVel[x] = xVel[i];
            yVel[x] = yVel[i];
            isActive[x] = 1;
            x++;
        }
    }
    totalParticles = x;
}

// Simulate the movement and interaction of particles over a number of time steps
void runSimulation(int steps) {
    for (int t = 0; t < steps; t++) {
        for (int i = 0; i < totalParticles; i++) {
            moveParticle(i);
            checkBounds(i);
        }
        handleCollisions();
        refreshParticles();
    }
}

// Write the grid with particles to the output file
void saveOutput(FILE *file) {
    for (int y = GRID_SIZE; y >= 0; y--) {
        for (int x = 0; x <= GRID_SIZE; x++) {
            if (y == 0 || y == GRID_SIZE || x == 0 || x == GRID_SIZE) {
                fprintf(file, "*");
            } else {
                char particleHere = ' ';
                for (int p = 0; p < totalParticles; p++) {
                    if (xPos[p] == x && yPos[p] == y) {
                        particleHere = '+';
                        break;
                    }
                }
                fprintf(file, "%c", particleHere);
            }
        }
        fprintf(file, "\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <output_file> <num_steps>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Failed to open the input file");
        return 1;
    }

    loadData(inputFile);
    fclose(inputFile);

    for (int i = 0; i < totalParticles; i++) {
        isActive[i] = 1;
    }

    runSimulation(atoi(argv[3]));

    FILE *outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        perror("Failed to open the output file");
        return 1;
    }

    saveOutput(outputFile);
    fclose(outputFile);

    return 0;
}

