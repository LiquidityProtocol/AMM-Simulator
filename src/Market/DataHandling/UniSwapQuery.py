#!/usr/bin/env python3

#
# Example that prints the current virtual amounts of assets in the 0.3% USDC/ETH pool
# using liquidity data from the Uniswap v3 subgraph.
#

import json
import urllib.request
import math
import sys
import csv

# Look at the USDC/ETH 0.3% pool
POOL_ID = '0x6c6bc977e13df9b0de53b251522280bb72383700'

# if passed in command line, use an alternative pool ID
if len(sys.argv) > 1:
    POOL_ID = sys.argv[1]

URL = "https://api.thegraph.com/subgraphs/name/uniswap/uniswap-v3"
TICK_BASE = 1.0001

# GraphQL query to get the pool information
query = """{
  pool(id: "0x6c6bc977e13df9b0de53b251522280bb72383700") {
    swaps(orderBy: timestamp, orderDirection: desc, first: 1000) {
      amount0
      amount1
      timestamp
    }
    mints(orderBy: timestamp, orderDirection: desc, first: 1000) {
      amount0
      amount1
      timestamp
    }
    burns(orderBy: timestamp, orderDirection: desc, first: 1000) {
      amount0
      amount1
      timestamp
    }
    token1 {
      symbol
      volume
    }
    token0 {
      symbol
      volume
    }
  }
}"""

# Query the subgraph
req = urllib.request.Request(URL)
req.add_header('Content-Type', 'application/json; charset=utf-8')
jsondata = {"query": query, "variables": {"pool_id": POOL_ID}}
jsondataasbytes = json.dumps(jsondata).encode('utf-8')
req.add_header('Content-Length', len(jsondataasbytes))
response = urllib.request.urlopen(req, jsondataasbytes)
obj = json.load(response)
pool = obj['data']['pool']

token0_symbol, token0_amount = pool["token0"]["symbol"], pool["token0"]["volume"]
token1_symbol, token1_amount = pool["token1"]["symbol"], pool["token1"]["volume"]

transactions = []

for swap in pool["swaps"]:
    swap["type"] = "SWAP"
    transactions.append(swap)

for mint in pool["mints"]:	# Add liquidity
    mint["type"] = "MINT"
    transactions.append(mint)

for burn in pool["burns"]:	# Remove liquidity
    burn["type"] = "BURN"
    transactions.append(burn)

transactions = sorted(transactions, key = lambda x: x["timestamp"])[-1000:]
field_names = ["type", "amount0", "amount1", "timestamp"]

with open('data/sample_transactions.csv', 'w') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=field_names)
    writer.writerows(transactions)

with open('data/sample_poolconfig.txt','w') as file:
    file.write(f"{token0_symbol} {token0_amount}\n")
    file.write(f"{token1_symbol} {token1_amount}")