#include <vector>
#include <math.h>

const double RADIUS = 15, A_LENGTH = 18.258, P_LENGTH = 6.8, COS = sqrt(3)/2, SIN = 0.5;
const double PREHENSOR[3][2] = {{0,P_LENGTH},{COS*P_LENGTH,-SIN*P_LENGTH},{-COS*P_LENGTH,-SIN*P_LENGTH}};
const double POSITION[3][2] = {{0,A_LENGTH},{COS*A_LENGTH,-SIN*A_LENGTH},{-COS*A_LENGTH,-SIN*A_LENGTH}};
const double STEPS_PER_CENTIMETER = 16;

double norm(std::vector<double> vector);

std::vector<std::vector<double>> threePoints(std::vector<double> center);

std::vector<std::vector<double>> vectors(std::vector<std::vector<double>> points);

std::vector<double> lengths(std::vector<std::vector<double>> vectors);

std::vector<double> motions(std::vector<double> length);

std::vector<double> computeMove(std::vector<double> center);

int distanceToSteps(double distance);