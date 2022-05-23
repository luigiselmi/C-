/*
  Integration of a system of differential equations
  of the 1st order for the harmonic oscillator with
  the Euler-Cromer method.
  The Euler-Cromer's update rule for the position x
  and velocity v of the harmonic oscillator is

  x(n + 1) = x(n) + v(n + 1) * h
  v(n + 1) = v(n) - omega^2 * x(n) * h

  n is the number of steps from the initial condition
  h is the length of the step (e.g. time)
*/
#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

struct State { // state of the system in the phase space
  double x;
  double v;
};

long int readLong(char *message);
double readDouble (char *message);
struct State *initHarmonicOscillator (double x0 , double v0);
struct State *eulerCromer(double dt, double omega2, struct State *state);
double energy(double omega2 , struct State *state);
double forceOscillator (double omega2 , double x);
double potentialEnergy(double omega2, double x);

int main() {
  double x0, v0, dt, omega2, totalTime, energy0, energy1;
  long int numberOfSteps, i;
  struct State state;

  printf("# Integration of the Harmonic oscillator differential equation\n");
  totalTime = readDouble("Enter the total integration time");
  dt = readDouble(" Enter dt");
  x0 = readDouble(" Enter x0");
  v0 = readDouble(" Enter v0");
  omega2 = readDouble (" Enter omega squared ");

  numberOfSteps = (long int)( totalTime / dt);
  printf("# dt = %g total time = %g\n", dt, totalTime);
  printf("# omega2 = %g number of steps = %d\n", omega2, numberOfSteps);

  state = *initHarmonicOscillator (x0, v0);
  printf ("# Initial conditions x0 = %g v0 = %g\n", state.x, state.v);

  energy0 = energy(omega2, &state);
  printf ("# The energy at time t = %d is %g\n", 0, energy0);

  printf ("# Using the Euler-Cromer algorithm\n");
  for (i = 0; i < numberOfSteps; i++) {
    state = *eulerCromer(dt, omega2, &state);
    energy1 = energy(omega2, &state);
    printf ("%g %g %g %g\n", (double) i*dt, state.x, state.v, energy1 - energy0);
  }

  energy1 = energy(omega2, &state);
  printf ("# The energy at time t = %d is %g\n", numberOfSteps , energy1);

  return EXIT_SUCCESS;

}

long int readLong(char *message) {
  long int inputData;
  printf ("# %s\n", message);
  fflush(stdout);
  scanf ("%ld", &inputData);
  return inputData;
}

double readDouble(char *message) {
  double inputData;
  printf ("# %s\n", message);
  fflush(stdout);
  scanf ("%lg", &inputData);
  return inputData;
}
/*
  Initializes the harmonic oscillator: position x0 and velocity v0.
*/
struct State *initHarmonicOscillator(double x0 , double v0) {
  static struct State init_state;
  init_state.x = x0;
  init_state.v = v0;
  return &init_state;
}
/*
  Computes the next state of the harmonic oscillator according
  to the The Euler-Cromer's rule.
*/
struct State *eulerCromer(double dt, double omega2, struct State *state) {
  static struct State next_state;
  next_state.v = (*state).v + forceOscillator(omega2, (* state).x) * dt;
  next_state.x = state ->x + next_state.v * dt;
  return &next_state;
}
/* Computes the sum of the kinetic and the potential energy of the oscillator.
   We do not compute E but compute 2 E / m
*/
double energy(double omega2 , struct State *state) {
  double localEnergy;
  double kineticEnergy = (*state).v * (*state).v;
  localEnergy = kineticEnergy + potentialEnergy(omega2 , (*state).x);
  return localEnergy ;
}
/*
  Updates the velocity of the oscillator.
*/
double forceOscillator (double omega2 , double x) {
  return - omega2 * x;
}

double potentialEnergy(double omega2, double x) {
  return omega2 * x * x;
}
