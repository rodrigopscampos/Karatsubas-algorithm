#each line from input file represents a 24 bit array
#the objective is to group them in clusters, such that the minimum distance between two clusters is 3


from networkx.utils.union_find import UnionFind
import time

dt_start = time.time()

num_to_bits = [0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4]
L = 24  # n digits

def computeDist1(n):
    return [n ^ (1 << i) for i in range(L)]

def computeDist2(n):
    ret = []
    for i in range(L):
        for j in range(i+1, L):
            a = 1 << i
            b = 1 << j
            c = a | b
            ret.append(n ^ c)
    return ret


def countSetBitsRec(num):
    nibble = 0
    if(0 == num):
        return num_to_bits[0]

    # Find last nibble
    nibble = num & 0xf
    return num_to_bits[nibble] + countSetBitsRec(num >> 4)


def bitArrToInt(bitArr):
    out = 0
    for bit in bitArr:
        out = (out << 1) | bit
    return out

def parseLine(line):
    return [int(item) for item in line.strip().split(' ')]


def hamming_distance(chaine1, chaine2):
    return sum(c1 != c2 for c1, c2 in zip(chaine1, chaine2))


#f = open('c:/temp/cluster.txt', 'r')
# f = open(r'C:\Temp\stanford-algs\testCases\course3\assignment2Clustering\question2\input_random_1_4_14.txt', 'r')  # 3
# f = open(r'C:\temp\stanford-algs\testCases\course3\assignment2Clustering\question2\input_random_2_4_10.txt', 'r') # 3
# f = open(r'C:\temp\stanford-algs\testCases\course3\assignment2Clustering\question2\input_random_10_16_18.txt', 'r')  # 15
# f = open(r'C:\temp\stanford-algs\testCases\course3\assignment2Clustering\question2\input_random_51_512_12.txt', 'r') #2
#f = open(r'C:\temp\stanford-algs\testCases\course3\assignment2Clustering\question2\input_random_83_262144_24.txt', 'r')  # 2549
f = open(r'C:\temp\clustering_big.txt', 'r')

nNodes, nBits = [int(item) for item in f.readline().split(' ')]

nodes = [parseLine(line) for line in f]
nodes = [bitArrToInt(item) for item in nodes]
s = set(nodes)

disjoint = {item: [] for item in nodes}
disjoint = UnionFind(disjoint)

def approach1():
    for i in range(0, len(nodes)):
        for j in range(i+1, len(nodes)):
            if countSetBitsRec(nodes[i] ^ nodes[j]) <= 2:
                disjoint.union(nodes[i], nodes[j])

def approach2():
    for item in nodes:
        for d1 in computeDist1(item):
            if d1 in s:
                disjoint.union(item, d1)

        for d2 in computeDist2(item):
            if d2 in s:
                disjoint.union(item, d2) 


approach2()
print(len(list(map(sorted, disjoint.to_sets()))))

dt_end = time.time();
print('time taken: ' + str(dt_end - dt_start))
