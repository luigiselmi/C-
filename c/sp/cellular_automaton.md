Cellular Automaton
==================
The program [cellular_automaton.c](cellular_automaton.c) implements a one-dimensional cellular automaton,
a lattice of N sites in which the state of a site at time
t + 1 depends on its own state and on the states of its
nearest neighbors at time t, according to a very simple rule.
Since the state of a site A at time t + 1 depends on the state
of three sites at time t, that is $2^3 = 8$ states, site A may
have one of $2^8 = 256$ state at time t + 1. In this example a
site may have at any time one of two possible states from the
set {0, 1}. The rules implemented in this example are rule 90 and
rule 150 in the Wolfram classification. Rule 90 is a XOR
between a site neighbors. Rule 150 is a XOR of the two nearest
neighbors, and a XOR with itself. The interesting outcome of the
cellular automaton is that even if the rules are local, that
is the state of any site depends only on its previous state
and on that of its nearest neighbors, they may produce
correlations at long distances. The initial state of
the lattice at time t = 0 has all the sites at state 0 but
the central site N/2 at state 1. The program creates a file
in which each line represents the state of the lattice at
different times. The data can be plotted using gnuplot with
the lattice in the horizontal axis and the time in the vertical
axis.
````
gnuplot> set palette defined ( 0 "white", 1 "black" )
gnuplot> set autoscale xfix
gnuplot> set autoscale yfix
gnuplot> set xlabel 'i'
gnuplot> set ylabel 't'
gnuplot> set title "Cellular Automaton"
gnuplot> plot 'automaton.dat' matrix with image

````

<p align="center">
  <img src="images/cellular_automata.png" width="640" height="486" alt="Cellular Automaton">
</p>
