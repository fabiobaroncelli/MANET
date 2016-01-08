# MANET

Introduction
============

Energy-efficient broadcasting has been an attractive area of research in Mobile Ad hoc Networks (MANETs) characterized by high mobility and limited battery capacity. Probabilistic and counter-based broadcast methods are the proposed solutions suitable for high-mobility and secure MANET where the knowledge of the updated global/local topology is difficult or impossible to obtain. 

In literature, several probabilistic and deterministic MANET broadcasting methods have been proposed:
1) Probabilistic methods do not require explicit neighbour information and comprise probability-based flooding, counter-based flooding, and area-based flooding. Probability-based flooding is similar to simple flooding except that nodes rebroadcast messages with probability p

2) Counter-based flooding exploits the fact that node local density is directed proportional to the number of received packets within a given interval. During a waiting delay, a node counts the number of times it receives the same message and then it decides if the message should be rebroadcasted. In area based flooding, each node selects its farther neighbour to retransmit broadcast messages. This kind of methods are generally efficient but require the knowledge of the neighbour positions.

3) In deterministic methods, topological knowledge is obtained by periodically exchanging control messages among node's neighbours. This approach and the type of exchanged information are generally scenario-dependent. Examples are clustering methods where nodes are grouped into small clusters each one managed by a particular node called cluster-head which has the task of retransmitting broadcast messages, geographic methods where forwarding decisions exploit the availability of accurate topological information such as distance, speed and direction of the neighbours, self-pruning methods where nodes use the history of encountered nodes before delivering messages. 

MANET routing protocols based on the measure of the relative importance of a node within its cluster, named Network Centrality (NC), have been recently proposed in the literature. Although several works have explored the capacity of a node to receive and diffuse information based on different NC definition (e.g., degree, closeness, betweenness, and Eigenvector Centrality), they require complete knowledge of the network topology thus limiting the applicability of these protocols to fixed networks or to scenarios where the instant topology should be computed in a centralized fashion.

The goal of this work is to simulate a MANET in order to define an algorithm for computing NC in a distributed fashion based on the EigenVector Centrality (EVC) theory. It used the defined algorithm to propose the EVC-based Broadcast (EVCB) protocol able to efficiently disseminate critical messages in high dynamic MANETs. 

The software
============

The software simulates the spreading of a message passed among moving nodes and hubs. (Node that received a message are blue) using different transmitting mechanisms.
This project was created and maintained using QtCreator. It requires Qt5 library.
It was written by the author for personal research in the field of MANET.
It was originally written in 2011 using Qt4.3 and ported to Qt5 in November 2015.
It is totally owned by Fabio Baroncelli and released under the GPL licence.

How to use it
=============

In the MANET Settings it is possible to specify the number of nodes and of hub nodes, their degree (max simultaneous connections), the speed, the radius of their connectivity.
In the Message Setting it is possible to characterize the exchanged messages.
The output of the simulation is a report file containing the Connectivity probability (e.g., the probability of a node to receive a message) and the degree distribution (e.g., the percentage of nodes that was connected to N different nodes simultaneously).

The name of the report file is:

Nx-y-dHs-t-g-Rr-k.dat

where

x = Number of node
y = Node degree
d = Node connectivity radius
s = Number of hub
t = Hub degree
g = Hub connectivity radius
r = side square of the Area
k = Keep or no keep old neighbours
 

NB The street-walk movement is not yet implemented!

ToDo
====
Doxygen documentation 
Dedicated page on the author personal website 
Implement street walk.


Author: Fabio Baroncelli
https://uk.linkedin.com/in/fabiobaroncelli




