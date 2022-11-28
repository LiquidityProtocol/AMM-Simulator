# Reports - The Nguyen

## Nov 21 - Nov 27
- Add type ```Token``` for representing real tokens. ```Token``` is implemented such that each real token has only one intance of type ```Token``` representing it.
- Add interface for all pools ```PoolInterface```. ```PoolInterface``` is an abstract class, which means that it cannot be used to instantiate objects and serves only as an interface.
- Add 2 basic liquidity protocols ```UniswapV2Pool``` and ```BalancerPool```. Both inherit features from ```PoolInterface```. Each protocol has its own algorithm to compute ouput quantity of swap operations, which is implemented in function ```ExecuteSwap```.
- Assist adding type ```Account```. Similar to ```Token```, ```Account``` is implemented such that each real account has only one intance of type ```Account``` representing it. Each instance of type ```Account``` can also be understood as a person. For now, accounts can interact with liquidity pools through swap operations (function ```Trade```).