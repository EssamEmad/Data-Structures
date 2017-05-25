import queue
import sys
from PriorityQueue import *
class Node:
    value = None
    children = {}
    parent = None
    currentWeight = sys.maxsize
    def __init__(self,value):
        self.value = value
    def __ge__(self,node):
        return self.value >= node.value
    def __gt__(self,node):
        return self.value > node.value
class dijkstra:
    def dijkstra(self, source, destination):
        q = PriorityQueue()
        source.currentWeight = 0
        self.insertInQueue(q,source)
        destinationNode = None
        visited = {}
        while len(q):
            current = q.pop()
            if current in visited:
                continue
            visited[current] = 0
            for child in current[1].children:
                if child[0].currentWeight > current[1].currentWeight + child[1]:
                    #decrease the key
                    child[0].currentWeight = current[1].currentWeight + child[1]
                    child[0].parent = current[1]
                    if child[0].value == destination:
                        destinationNode = child[0]
                    q.reheap()
        return destinationNode
    def insertInQueue(self,q,source, shouldPrint = False):
        inserted = {}
        insertionQueue = queue.Queue()
        insertionQueue.put([source])
        while not insertionQueue.empty():
            n = insertionQueue.get()[0]
            if n in inserted:
                continue
            inserted[n] = 0
            if shouldPrint:
                print("The node:{} holds {} as distance".format(n.value, n.currentWeight))
            q.append((n.currentWeight,n))
            for child in n.children:
                insertionQueue.put(child)
    def printgraph(self, node):
        """ Recursively prints the shortest path from the destination to the source"""
        if node is None:
            return
        print("s{}".format(node.value))
        self.printgraph(node.parent)

# This is the example given in the session. The value passed in the constructor is just an identifier that
#the nodeh olds. It doesn't have anything to do with the distance.
s0 = Node(0)
s1 = Node(1)
s2 = Node(2)
s3 = Node(3)
s4 = Node(4)
s0.children = [[s1,10],[s2,5]]
s1.children = [[s3,1], [s2,2]]
s2.children = [[s1,3], [s3,9],[s4,2]]
s3.children = [[s4,4]]
s4.children = [[s3,6], [s0,7]]
# n.children = [[Node(0),2], [Node(2), 4], [Node(5),2]]
l = dijkstra()
l.printgraph(l.dijkstra(s0,4)) # 3 is the value (Not distance) of the node we are searching for
l.insertInQueue(PriorityQueue(),s0,True)
