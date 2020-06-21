##
## Dynamic programming to discovery the maximum-weight independent set of a path graph
##

f = open('C:/temp/mwis.txt', 'r')

n_vertices = int(f.readline())

data = [int(item) for item in f]
data = [0] + data
cache = [0] * len(data)

def calcMaxWeightIndependent(data: []):
    cache[1] = data[1]
    for i in range(2, len(data)):
        if cache[i-1] >= cache[i-2] + data[i]:
            cache[i] = cache[i-1]
        else:
            cache[i] = cache[i-2] + data[i]

calcMaxWeightIndependent(data)

def discoveryMWIPath(data):
    path = []
    i = len(data) - 1
    while i >= 0:
        if cache[i-1] >= cache[i-2] + data[i]:
            i -= 1
        else:
            path.append((i, data[i]))
            i -= 2
    return path

path = discoveryMWIPath(data)
print(path)
