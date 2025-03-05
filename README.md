# Order book
Each order book serves one symbol.  
It is a balanced binary search tree, where each node represents a price level.  
Each node contains a priority queue of orders at that price level.  
The priority queue is ordered by the following rules, in order of precedence:  
1. Type of order (market orders have higher priority than limit orders)
2. Time of order arrival
3. Quantity of order
