def printDebug(what, msg):
    # print(what)
    # print(msg)
    # print('-------')
    pass

f = open('edges.txt', 'r')

nNodes, nEdges = f.readline().split(' ')

#printDebug(nNodes)
#printDebug(nEdges)

def parseData():
    g = {}

    for l in f:
        u,v,c = [int(item) for item in l.split(' ')]
        
        if u not in g: g[u] = [(v,c)]
        else: g[u].append((v,c))

        if v not in g: g[v] = [(u,c)]
        else: g[v].append((u,c))
    
    return g

def get_cheapes(g, x):
    vertexes = [(item, g[item]) for item in x]
    printDebug('x', x)
    printDebug('vertexes', vertexes)
    

    rU, rV = vertexes[0]
    rV, rC = rV[0]

    rU, rV, rC = (0,0, 9999999999)

    for (u, adj) in vertexes:
        for (v,c) in adj:
            if rC > c and v not in x:
                rU, rV, rC = u,v,c

    ret = rU,rV,rC
    printDebug('ret', ret)
    return ret

def prims(g):
    nodes = list(g.keys())
    x = [nodes[0]]
    t = []

    while len(x) != len(nodes):
        u,v,c = get_cheapes(g,x)

        if (u,v,c) == (0,0,0): break

        t.append((u,v,c))
        x.append(v)
    
    print(t)
    print(sum([item[2] for item in t]))

g = parseData()

prims(g)
