#include <vector>
#include <math.h>
#include "mouvement.h"

double H = sqrt(pow(21.0, 2) - pow(A_LENGTH-P_LENGTH, 2));
double height[3] = {H,H,H};

double norm(std::vector<double> vector) {
    return sqrt(pow(vector[0],2)+pow(vector[1],2));
}

std::vector<std::vector<double>> threePoints(std::vector<double> center) {
    std::vector<std::vector<double>> points(3);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 2; j++)
            points[i].push_back(center[j]+PREHENSOR[i][j]);

    return points;
}

std::vector<std::vector<double>> vectors(std::vector<std::vector<double>> points) {
    std::vector<std::vector<double>> vectors(3);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 2; j++)
            vectors[i].push_back(POSITION[i][j]-points[i][j]);

    return vectors;
}

std::vector<double> lengths(std::vector<std::vector<double>> vectors) {
    std::vector<double> length(3);

    for(int i = 0; i < 3; i++)
        length[i] = norm(vectors[i]);

    return length;
}

std::vector<double> motions(std::vector<double> length) {
    std::vector<double> m(3);

    for(int i = 0; i < 3; i++) {
        m[i] = sqrt(pow(21.0, 2) - pow(length[i], 2)) - height[i];
        height[i] += m[i];
    }

    return m;
}

std::vector<double> computeMove(std::vector<double> center) {
    return motions(lengths(vectors(threePoints(center))));
} 

int distanceToSteps(double distance) {
    return round(distance * STEPS_PER_CENTIMETER);
}