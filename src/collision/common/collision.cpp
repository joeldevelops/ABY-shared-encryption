#include <iostream>
#include <cmath>

using namespace std;

# define pi 3.14159265358979323846 // define pi constant

// define a struct to hold satellite parameters
struct Satellite {
    double altitude; // altitude in km
    double inclination; // inclination in degrees
    double eccentricity; // eccentricity
    double raan; // right ascension of ascending node in degrees
    double argp; // argument of perigee in degrees
    double mean_anomaly; // mean anomaly in degrees
};

// calculate collision probability between two satellites
double calculateCollisionProbability(Satellite sat1, Satellite sat2) {
    // calculate orbital periods
    double T1 = 2 * pi * sqrt(pow(sat1.altitude + 6371, 3) / 398600.4418); // in seconds
    double T2 = 2 * pi * sqrt(pow(sat2.altitude + 6371, 3) / 398600.4418); // in seconds

    // calculate relative inclination and relative longitude of ascending node
    double delta_i = abs(sat1.inclination - sat2.inclination); // in degrees
    double delta_raan = abs(sat1.raan - sat2.raan); // in degrees

    // calculate relative mean motion
    double n1 = 2 * pi / T1; // in radians per second
    double n2 = 2 * pi / T2; // in radians per second
    double delta_n = abs(n1 - n2); // in radians per second

    // calculate relative argument of perigee
    double delta_argp = abs(sat1.argp - sat2.argp); // in degrees

    // calculate relative mean anomaly
    double delta_M = abs(sat1.mean_anomaly - sat2.mean_anomaly); // in degrees

    // calculate collision probability
    double P = exp(-(pow(delta_i, 2) + pow(delta_raan, 2) + pow(delta_n, 2) 
              + pow(delta_argp, 2) + pow(delta_M, 2)) / (2 * pow(0.2, 2)));

    return P;
}

double collisionProbabilityWithMACVerification(Satellite sat1, Satellite sat2, double MAC) {
    // TODO: implement MAC verification
}

int main() {
    // create two example satellites
    Satellite sat1 = {800, 45, 0.1, 0, 0, 0};
    Satellite sat2 = {800, 55, 0.1, 0, 0, 0};

    // calculate collision probability
    double P = calculateCollisionProbability(sat1, sat2);

    // print collision probability
    cout << "Collision probability: " << P << endl;

    return 0;
}
