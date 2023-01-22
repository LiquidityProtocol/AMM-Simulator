## Functionalities

  C++ project on building liquidity pools and a stochastic market simulator to test the different automated market makers in different scenarios. We built two distinct simulators. A manual interactive simulator and a market simulator. In the manual, one can mint tokens, initialise pools using 5 different protocols. The simulator allows the user to trade, provide extra liquidity, withdraw liquidity and dynamically displays a graph representing the quatinities in the pool, the invariant quantity of a protocol, divergence loss, slippage, change in money etc. The general implementation of the protocols allows the user to create his/her own protocol and see how it performs compared to other famous protocols such as UniswapV2, UniswapV3, Curve, Balancer etc.

Furthermore, we implemented a market simulator as well. It allows the user to see the performance of protocols in a simulated market with multiple agents (arbitrageur, liquidity provider). One can initialise any number of tokens and set their prices and choose a strategy for the trader (Naive Greedy, Linear Regression, Exponential Moving Average, Moving Average). Every step happens probabilistically and different quantities (price, volume, arbitrageur's return, liquidity provider's return) are dynamically displayed.

## Deadlines and deliverables
  
  Manual playground
  17/12/2022
  Stochastic Simulator
  18/01/2023

## Software Architecture

This project doesn't have any external dependencies, only QT for the Graphical Interface.

## Run the application

Written in the README.
