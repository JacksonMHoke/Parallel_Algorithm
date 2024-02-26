## Project Description

A learning project that attempts to implement what I think a parallel algorithm is with no prior knowledge of parallel algorithms. The main idea is to compare a simple algorithm
implemented in parallel versus that algorithm implemented in series. Parallel meaning that two different parts of the algorithm are calculated on two separate exe files and series
meaning that both those two parts are calculated sequentially. The problem chosen to implement was finding the shared prime factors two numbers shared.

## Inspiration/Motivation

The main inspiration was the class CS142 Algorithm Engineering that I will be taking next quarter. In the course description for that course they mentioned parallel algorithms
and I thought it would be cool to try and implement what I thought a parallel algorithm was based on the name. Then compare and contrast what it actually is once I learn about it
in that class.

## How it works

It was implemented using 2 cpp files, core1 and core2. Core1 is the main core, while core2 is a supplemental calculator to run in parallel to core1. First you run core1, which
will wait until core2 outputs a file with "ready" in it, and then run core2. This lets both "cores" start their calculations at the same time. Once core2 finishes their calculations, they output it
to a file and core1 reads those while printing out the shared factors between their two separate calculations. Finally I ran the series computation on core1 and compared the times
taken to calculate.

## Graphs
I used mathplotlib in python to plot.
These 2 graphs compare the time taken to calculate the prime factorization of the numbers to the time saved by using parallel over series calculation.

![](https://github.com/JacksonMHoke/Parallel_Algorithm/blob/master/2dgraph.PNG)
This graph's x-axis is the shorter calculation time between the two calculations for the prime factorizations of each number, and the y-axis is the time saved by using
parallel over a series algorithm. The linear scaling makes sense in this case as the parallel algorithm scales with the longest calculation time between the two numbers,
while the series algorithm scales with the sum of the calculation times between the two numbers. This makes the difference between the parallel and the series time scale with
the shorter calculation number.

![](https://github.com/JacksonMHoke/Parallel_Algorithm/blob/master/3dgraph.PNG)
The same relation is shown by the 3D graph as the time saved is low when either the x or y axis is low. Once both the x and y values are high the time saved increases.
This follows the relation that time saved is proportional to the shorter calculation time between the two prime factorizations.

## Challenges

The greatest challenges in this project were definitely creating the data and also the graphs. It was very difficult to automate running this algorithm in masse and also save
save that data. Since this program requires you to run core1.cpp first, and then core2.cpp concurrently from a separate terminal, using system("core1.exe & core2.exe") did not work as this waits for
core1 to finish before running core2. To solve this issue I had to create a new terminal everytime I ran this program by using the start command. In order to not decrease
speed, which would affect the results, I had to limit the number of terminals open at once as opening too many would cause issues when a terminal would stall for a period of time.

Another issue I ran into was generating the random number to pass into core1 and core2 when collecting data in masse. Since I wanted the calculations to take a significant amount
of time, I had to use unsigned long long as the data type since the time difference would not be as measurable if the time was too short to factor the number. I solved this by
creating my own psuedorandom function for unsigned long long using rand() to calculate the number of digits and also the numbers that would go into every digit.

Using both the start command and also my psuedo-random function, I was able to collect the data for the execution I needed onto a csv and plot different graphs using that data
in the mathplotlib python library.


