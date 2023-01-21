# CSE201-project

![alt text](https://github.com/Liquidity-protocol-CSE201-Project/Project/blob/main/LP_logo.png?raw=true)

C++ project on building liquidity pools and a stochastic market simulator to test the different automated market makers in different scenarios. We built two distinct
simulators. A manual interactive simulator and a market simulator. In the manual, one can mint tokens, initialise pools using 5 different protocols. The
simulator allows the user to trade, provide extra liquidity, withdraw liquaidity and dynamically displays a graph representing the quatinities in the
pool, the invariant quantity of a protocol, divergence loss, slipage, change in money etc. The general implementation of the protocols allows the user to
create his/her own protocol and see how it performs compared to other famous protocols such as UniswapV2, UniswapV3, Curve, Balancer etc. Furthermore, we implemented a market simulator as well. It allows the user to see the performance of protocols in a simulated market with multiple agents (arbitrageur, liquidity provider). One can initialise any number of tokens and set their prices and choose a strategy for the trader (Naive Greedy, Linear Regression, Exponential Moving Average, Moving Average). Every step happens probabilistically and different quantities (price, volume, arbitragur's return, liquidity provider's return) are dynamically displayed.


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
- Go to `src` folder
- Click on `LiquidityProtocol.pro`
- Click on Open
- Run  `Ctrl+R`

<br>


## How to use it

![alt text](https://github.com/Liquidity-protocol-CSE201-Project/Project/blob/main/workflow.png?raw=true)


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
- The program will show you the output quantity (computed based on the liquidity protocol)

### Withdrawing liquidty

- 

## Used protocols
- [Curve](https://classic.curve.fi/files/crypto-pools-paper.pdf)

- Curve
- Balancer
- Constant sum
- UniswapV2
- UniswapV3


## Definitions to know
- Divergence loss
- Impermanent loss



