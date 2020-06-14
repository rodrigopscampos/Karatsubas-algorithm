import heapq
import time

class ClusterGroup:
    clusters = {}
    index = {}
    nextId = 0

    def getNextId(self):
        self.nextId += 1
        return self.nextId

    def getOrAdd(self, key: int):
        if key in self.index:
            return self.clusters[self.index[key]]

        nextId = self.getNextId()
        self.index[key] = nextId
        self.clusters[nextId] = Cluster(nextId, key)

        return self.clusters[nextId]

    def merge(self, u: int, v: int):
        uCluster = self.getOrAdd(u)  # type: Cluster
        vCluster = self.getOrAdd(v)  # type: Cluster

        if uCluster.id == vCluster.id:
            return

        if len(uCluster.keys) >= len(vCluster.keys):
            uCluster.merge(vCluster)
            del self.clusters[vCluster.id]
            for item in vCluster.keys:
                self.index[item] = uCluster.id
        else:
            vCluster.merge(uCluster)
            del self.clusters[uCluster.id]
            for item in uCluster.keys:
                self.index[item] = vCluster.id

    def printCG(self):
        print('index: {}'.format(self.index))

        for key in self.clusters:
            self.clusters[key].printC()

    def size(self):
        return len(self.clusters)

    def getMin(self):
        ret = 999999999
        for key in self.clusters:
            cluster = self.clusters[key]
            m = cluster.getMin()
            if ret > m:
                ret = m
        return ret


class Cluster:
    id: int
    keys: set()
    adjacent: {}

    def __init__(self, id: int, key: int):
        self.id = id

        self.keys = set()
        self.keys.add(key)

        self.adjacent = {}

    def merge(self, other):
        self.keys.update(other.keys)

        for item in other.keys:
            del self.adjacent[item]

        for u in other.adjacent:
            w = other.adjacent[u]

            if u not in self.keys:
                self.adjacent[u] = w

    def appendConn(self, wv: (int, int)):
        w, v = wv
        self.adjacent[v] = w

    def printC(self):
        print('{}: {} -> {}'.format(self.id, self.keys, self.adjacent))

    def getMin(self):
        ret = 999999999
        for u in self.adjacent:
            w = self.adjacent[u]
            if ret > w:
                ret = w

        return ret


begin = time.time()
f = open(r'c:/temp/data.txt', 'r')
K = 4

nEdges = int(f.readline())
nodes = []
cg = ClusterGroup()

def parseLine(line):
    item = line.split(' ')
    return int(item[2]), int(item[0]), int(item[1])

for l in f:
    w, u, v = parseLine(l)
    heapq.heappush(nodes, (w, u, v))

    cg.getOrAdd(u).appendConn((w, v))
    cg.getOrAdd(v).appendConn((w, u))

while cg.size() != K:
    w, u, v = heapq.heappop(nodes)
    cg.merge(u, v)

print('Maximum Space: ' + str(cg.getMin()))

end = time.time()
print('time taken: ' + str(end - begin))
