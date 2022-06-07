Random walk on a square lattice
===============================
## Single particle
The program performs a number of random walks on a 2-dimensional
square lattice. At each step the traveler can move eastward,
westward, northward or southward with equal probability 1/4.
Therefore each random walk is made up of a fixed number of random
steps. At each step t the program computes the squared absolute
value of the distance from the origin x^2(t) and its error x^4(t)
and adds them to the values computed in the preceding random walks
stored in an array.
After all the random walks (samples) are completed, the program
computes the average values of x^2 and its error for each step
and writes the values on a file. The average values of x^2 at step t,
<x^2(t)> represents the (squared) probability for the traveler to
be at position x in the square lattice.
The <x^2(t)> data can be plotted using gnuplot and the command:
```
gnuplot> plot 'rw2d_ave.dat'
````
From the plot it can be seen that <x^2(t)> is linear according to the
theory that says

<x^2(t)> = a^2 * t / D

where a is the length of the edges between two nodes of the square
lattice (in our case a = 1), t is the step (or time), and D is the
dimension (in our case D = 2). The above equation has been determined
from the probability distribution of traveler position in the square
lattice as a function of the position x = (x1, x2) and the step (time)

P(x, t) = (D / 2*Pi*t)^(D/2) * exp(-Dx^2 / 2*t*a^2 )

so that <x^2(t)> = S(x^2 * P(x, t)dx)  (S represents the integration operator)

The application also stores in another file, rw2d_prob.dat, the position
(x1, x2) at each step of any random walk (sample) that is a power of 10
between 1 and 5, that is 10, 100, 1000, 10000 and 100000. We can plot the
distribution of the positions reached by the random traveler after, for
instance 100 steps, in all the random walks. The position reached after
100 steps will be distributed around a value of (100/2)^(1/2), that is 7.07.
We can filter the data from the file to consider only the position after 100
steps
```
$ grep "T 99 " rw2d_prob.dat > rw2d_prob_100.dat
```
If we use gnuplot to plot the data we set the range for x1 and x2
```
gnuplot> set xrange [-300:300]
gnuplot> set yrange [-300:300]
```
then we plot the filtered data
```
gnuplot> plot 'rw2d_prob_100.dat' using 6:8 linecolor 'blue'
```
if we repeat the experiment filtering the data to extract the position
after, let's say, 10000 step we will see the the distribution is much
larger and the points are more dispersed.

Another experiment is to compute the number of times a certain position
in the square lattice has been reached by the random traveler after a
certain number of steps. For instance, we can count the number of times
the traveler went through the point at (0, 0) after 100 steps
```
$ grep "T 99 X1 0 X2 0" rw2d_prob.dat |wc -l
59
```
If we repeat the test for the position (10, 10)
```
$ grep "T 99 X1 10 X2 10" rw2d_prob.dat |wc -l
4
```
we see that it's much less likely. We can compute the values for all the
points in the square lattice, within the ranges we have set above, to have
the probability distribution for t = 100 or for any other value of t for
which we have the data.

## Lattice gas
Our aim is to compute the mass diffusivity, or diffusion coefficient, of a system
of N particles on a square lattice by performing some simulations using the C code.
We define the variables that will be used in the simulations.

- ρ is the probability of occupation of a lattice's node
- L is the number of nodes per lattice row (or column)
- V = $L^2$ is the total number of nodes of the lattice
- N = ρV is the total number of particles.

The occupation function η(x1, x2) assumes values in the set {0, 1} and tells us when
a node in position (x1, x2) in the lattice is occupied by a particle, so that η(x1, x2) = 1,
or when it is not and η(x1, x2) = 0. We can also define a spin function σ(x1, x2) to represent the same concept using values in the set {-1, 1} so that for an empty node σ(x1, x2) = -1 and
for an occupied node σ(x1, x2) = 1. The relation between the two representations is given by the equation

σ(x1, x2) = 2 * η(x1, x2) - 1

The total number of occupied nodes is equal to the number of particles and is assumed constant   

N = ρ * V = ∑η(x1, x2)

where the summation is made over the set of the lattice's nodes.
A particle α, of the total N particles, is located at the time t in one of the N nodes.
For each particle we have to take into account the position occupied at time t and whether
it moves at time t + 1 to an adjacent node. For the correct location of a particle
we have to take into account the boundary conditions so that

(x1, x2) = (x1 +/- L, x2) = (x1, x2 +/- L)

Each particle α can move at time t to an adjacent free node with equal probability, 1/4
for a square lattice. The quadratic distance between two adjacent nodes is

$$ ΔR_\alpha(t)^2 = (x_1(t) - x_1(0))^2 + (x_2(t) - x_2(0))^2 $$

The average distance traveled by all particles at time t is

$$ ΔR(t)^2 = \frac{1}{N} \sum_\alpha ((x_1(t) - x_1(0))^2 + (x_2(t) - x_2(0))^2) $$

In order to minimize the error we can compute the mean quadratic distance traveled by
all particles at time t by performing a certain number S of travels so that

$$ &lt;\Delta R_\alpha(t)^2&gt;= \frac{1}{S}$$
## Credits
Barone et al. - Scientific Programming, https://chimera.roma1.infn.it/SPENG/
