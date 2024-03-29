# Project: Liquidity Protocol => Manual & Stochastic Automated Market Maker Simulator 

![alt text](https://github.com/Liquidity-protocol-CSE201-Project/Project/blob/main/LP_logo.png?raw=true)

C++ project on building liquidity pools and a stochastic market simulator to test the different automated market makers in different scenarios. We built two distinct
simulators. A manual interactive simulator and a market simulator. In the manual, one can mint tokens, initialise pools using 5 different protocols. The
simulator allows the user to trade, provide extra liquidity, withdraw liquidity and dynamically displays a graph representing the quatinities in the
pool, the invariant quantity of a protocol, divergence loss, slippage, change in money etc. The general implementation of the protocols allows the user to
create his/her own protocol and see how it performs compared to other famous protocols such as UniswapV2, UniswapV3, Curve, Balancer etc. 

Furthermore, we implemented a market simulator as well. It allows the user to see the performance of protocols in a simulated market with multiple agents (arbitrageur, liquidity provider). One can initialise any number of tokens and set their prices and choose a strategy for the trader (Naive Greedy, Linear Regression, Exponential Moving Average, Moving Average). Every step happens probabilistically and different quantities (price, volume, arbitrageur's return, liquidity provider's return) are dynamically displayed.

# Demo

https://user-images.githubusercontent.com/44528132/213862816-84bcd012-568c-4c8a-8f04-47ad25a2ec8c.mp4


## Members
| name | github username | trello username | role |
|:------------:|:---------------:|:---------------:|:------:|
| Levente Ludányi | ludlev2 | leventeludanyi | Project Leader |
| Adithya Ravichandran | Ad1thya-R | ad1thya_r | Responsible for Git |
| Fryderyk Sitnik | fryderyk-sitnik | fryderyksitnik2 | Responsible for Trello |
| Shubh Lashkery | shubhlashkery | shubhlashkery | Economics Team Leader |
| Martina Paez Berru  | Martina-Paez-Berru | martinapaezberru | Frontend Team Leader |
| Minh Pham | minhpham160603 | minhpham1606 | Playground Team Leader |
| Duc Nguyen | combi2k2 | Duc Nguyen | Protocols Team Leader |
| Kaoutar Fahraoui | Kaoutar-Fahraoui | kaoutar.fahraoui |  |
| Mia Chambat | miachambat | miachambat |  |
| Amine Roudani | amineroudani | amineroudani |  |
| Julien Girod | juliengirod | Julien Girod |  |
| Victoire Fabien | victoire-fabien | victoire-fabien |  |
| Jasmine Samson | Jasmine-Samson | jasmine samson |  |
| Tu Nguyen | ngoctu-nguyen | nguyenngoctu03 |  |
| The Nguyen | the-nguyen | thenguyen33 |  |
| Alessandro Massaad | alemassaad | alemassaad |  |
| Mathéo Le Masson | Matheo-LeMasson | matheo-lemasson |  |
| Gabriele Biroli | GabrieleBiroli | gabrielebiroli |  |



## Teams
The teams are more of a guidline, the tasks are not limited to what the team names would indicate
### Economics
- Shubh
- Gabriele
- Kaoutar
- Mia

### Protocol
- Amine
- Julien
- Duc

### Frontend
- Jasmine
- Victoire
- Martina

### Playground
- Minh
- The
- Levente
- Adithya
- Fryderyk
- Tu
- Alessandro
- Matheo

## Building guide

clone the repository
- Enter the intended location
- Run
```
git clone https://github.com/Liquidity-protocol-CSE201-Project/Project
```

Download [Qt Creator](https://www.qt.io/product/development-tools) then open the project in Qt Creator to run it.
- Open Qt Creator
- Click on `File`
- Click on `Open File or Project...`
- Follow the path where you cloned the repository
- Click on `LiquidityProtocol.pro`
- Click on Open
- Run  `Ctrl+R`

<br>


# How to use it

![alt text](https://github.com/Liquidity-protocol-CSE201-Project/Project/blob/main/Images/workflow.png?raw=true)



(It is advised to use dark mode on your computer to have the experience while running the application)

## Manual Playground

### Token creation
- Give any name
- Specify the price

### Account creation
- Given any name

### Liqudity provision
- ### New Pool
  - Choose the protocol
  - Choose the tokens and quantities
  - Specify pool fee
This will create a new liqudity pool that you are the provider of
You can see the visualisation and some metrics shown on the right
- ### Existing Pool
  - Choose the protocol
  - Specify which already existing pools you want to provide liquidity to
  - Choose the tokens and quantities
  - Specify pool fee

### Trading
- Specify the tokens
- Choose the protocol
- Specify which pool you want to trade in
- Input the desired amounts
- The dialog will show you the output quantity (computed based on the liquidity protocol)

### Withdrawing liquidty

- Specify which pool to withdraw from
- Specify percentage of provided liquidity to withdraw from pool
- The dialog will show you the output quantities 

## Market Simulator

### Set up and load initial scenario

- Add tokens and their respective quantities in the price tags list in the format “[Token-Name]”:[Token-Quantity]
- Choose Strategy of Arbitrageur from: [Naive Greedy, Linear Regression, Exponential Moving Average, Moving Average]

### Configure Options

- Select Viewing Method: View Volume or Price
- Select Pool: Select which pool to view information about

### Run Simulation

- Run a single or multiple time steps
- Toggle between the Pool, Provider and Arbitrageur graph to see how each Market Player is affected.

# Rough layout of the codebase

![alt text](https://github.com/Liquidity-protocol-CSE201-Project/Project/blob/main/Images/backend.png?raw=true)

![alt text](https://github.com/Liquidity-protocol-CSE201-Project/Project/blob/main/Images/visualisation2.png?raw=true)


## Used protocols
- [Curve](https://classic.curve.fi/files/crypto-pools-paper.pdf)
- [Balancer](https://classic.curve.fi/files/crypto-pools-paper.pdf)
- [Constant Sum](https://medium.com/bollinger-investment-group/constant-function-market-makers-defis-zero-to-one-innovation-968f77022159)
- [UniswapV2](https://uniswap.org/whitepaper.pdf)
- [UniswapV3](https://uniswap.org/whitepaper-v3.pdf)


## Definitions to know
- [Automated Market Makers](https://medium.com/pendulum-chain/what-is-an-automated-market-maker-amm-d9e8d7a6bba8)
- [Liquidity Pool](https://www.youtube.com/watch?v=cizLhxSKrAc)
- [Slippage](https://academy.shrimpy.io/post/what-is-slippage-how-to-avoid-slippage-on-defi-exchanges)
- [Divergence loss](https://medium.datadriveninvestor.com/impermanent-loss-in-defi-the-risks-involved-in-providing-liquidity-67c54fdf1cfc)



