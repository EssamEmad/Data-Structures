class PriorityQueue:
    """Heap-based priority queue implementation."""
    def __init__(self):
        """Initially empty priority queue."""
        self.queue = []

    def __len__(self):
        # Number of elements in the queue.
        return len(self.queue)

    def append(self, key):
        """Inserts an element in the priority queue."""
        if key is None:
            raise ValueError('Cannot insert None in the queue')
        self.queue.append(key)
        dummy = len(self.queue) - 1
        self.build_min_heap(dummy)


        self.min_index = None

    def min(self):
        """The smallest element in the queue."""
        # if len(self.queue) == 0:
        #     return None
        # self._find_min()
        if ( len(self.queue) == 0):
            return None
        return self.queue[0]

    def pop(self):
        """Removes the minimum element in the queue.
        Returns:
            The value of the removed element.
        """
        if len(self.queue) == 0:
            return None
        popped_key = self.queue[0]
        self.queue[0] = self.queue[-1]
        if(len(self.queue) >= 2):
            self.queue.pop(-1)
        else:
            self.queue.pop(0)
        self.min_heapify(0)
        return popped_key

    def _find_min(self):
        # Computes the index of the minimum element in the queue.
        #
        # This method may crash if called when the queue is empty. <- Lol
        return 0

    def build_min_heap(self,index):
        if(index == 0 or self.queue[index] >= self.queue[index // 2]):
            return
        else:
            temp = self.queue[index]
            self.queue[index] = self.queue[index // 2]
            self.queue[index // 2] = temp
            self.build_min_heap( index // 2)

    def min_heapify(self,index):
        if(index >= len(self.queue)):
            return
        parent = self.queue[index]
        smallerIndex = index
        if(self.heap_left_index(index) < len(self.queue) and parent > self.queue[self.heap_left_index(index)]):
            smallerIndex = self.heap_left_index(index)
        if(self.heap_left_index(index) + 1< len(self.queue) and parent > self.queue[self.heap_left_index(index) + 1]):
            smallerIndex = self.heap_left_index(index) + 1
        if(smallerIndex != index):
            temp = self.queue[index]
            self.queue[index] = self.queue[smallerIndex]
            self.queue[smallerIndex] = temp
            self.min_heapify(smallerIndex)

    def heap_left_index(self,i):
        if( i == 0):
            return 1
        else:
            return i * 21

    def reheap(self):
        self.build_min_heap(len(self.queue) - 1)
