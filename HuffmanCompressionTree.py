##
## Creating the Huffman compression tree
##

import heapq

class Node:
    item = None
    left = None
    right = None
    weight = None

    def __init__(self, left=None, right=None, item=None, weight=None):
        self.left = left
        self.right = right
        self.item = item
        self.weight = weight

    def __lt__(self, other):
        return self.item < other.item

f = open('c:/temp/huffman.txt', 'r')

n_symbols = int(f.readline())

data = []

for item in zip(f, range(n_symbols)):
    node = Node(item=str(item[1]), weight=int(item[0]))
    heapq.heappush(data, (node.weight, node))

for r in range(len(data) - 1):
    wa, a = heapq.heappop(data)
    wb, b = heapq.heappop(data)

    weight = wa + wb
    heapq.heappush(data, (weight, Node(left=a, right=b,
                                       item=a.item + "." + b.item,
                                       weight=weight)))

w, root = heapq.heappop(data)
