import time
import random


class Array_Search:
    def __init__(self, array):
        self.array = array

    def init_array_search(self, val_array):
        self.array = Array_Search(val_array)

    def sequential_search(self, key):

        idx = 0
        for num in self.array:
            if num == key:
                return idx
            idx = idx+1
        return False

    def bsearch(self, val):

        return False

    def create_bsearchtree(self):
        self.tree = BST()
        # tree = self.tree
        # tree.init_bst(self.array[0])

        # it = 1
        for item in self.array:
            self.tree.insert(item)
            # if(it % 2 == 1):
            #     self.tree.reroot(it)
            # it += 1
        # self.tree.printTree() # Do NOT leave this in
        return False
    
    def bsearchtree(self, val):
        return self.tree.bsearch(val)


class BST_Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


class BST:
    def __init__(self):
        self.root = None

    def init_bst(self, val):
        self.root = BST_Node(val)

    def insert(self, val):
        if (self.root is None):
            self.init_bst(val)
        else:
            self.insertNode(self.root, val)

    def insertNode(self, current, val):
        # node sorting logic
        # status = False
        if val < current.val: # check against current
            if current.left == None:
                current.left = BST_Node(val)        # val <-- current --> ? 
                # print(True)
                return True
            else:
                self.insertNode(current.left, val)  # current = current.left
        else:
            if current.right == None:
                current.right = BST_Node(val)       # ? <-- current --> val
                # print(True)
                return True
            else:
                self.insertNode(current.right, val) # current = current.right
        # print(False)
        return False

    def printTree(self): #for ensuring tree is built correctly
        numTabs = 1
        it = self.root
        while it != None:
            it = it.left
            numTabs += 1
        
        it = self.root
        print('\t'*numTabs, it.val)
        print('\t'*(numTabs-2), it.left.val, "\t\t\t\t", it.right.val)
        itl = it.left
        itr = it.right
        print('\t'*(numTabs-3), itl.left.val, "\t\t", itl.right.val, "\t\t", itr.left.val, "\t\t", itr.right.val)

    # def reroot(self, numNodes):
        

    #     return False

    def bsearch(self, val):
        if val < self.root.val:         # if left of root
            if self.root.left == None:
                return False
            else:
                return self.searchNode(self.root.left, val)
        elif val == self.root.val:      # if it is root
            return True
        else:                           # if right of root
            if self.root.right == None:
                return False
            else:
                return self.searchNode(self.root.right, val)

        return False

    def searchNode(self, current, val):
        if val < current.val:
            if current.left == None:
                return False
            else:
                return self.searchNode(current.left, val)
        elif val == current.val:
            return True
        else:
            if current.right == None:
                return False
            else:
                return self.searchNode(current.right, val)

        return False

    def delete(self, val):

        return False



class RBBST_Node:
    def __init__(self, val, color):
        self.val = val
        self.left = None
        self.right = None
        self.color = color


RED = True
BLACK = False


class RBBST:
    def __init__(self):
        self.root = None

    def init_rbbst(self, val, color):
        self.root = RBBST_Node(val, color)

    def is_red(self, current):



        return False

    def rotate_left(self, current):



        return False

    def rotate_right(self, current):

        return False

    def flip_colors(self, current):

        return False

    def insert(self, val):
        if (self.root is None):
            self.init_rbbst(val, RED)
        else:
            self.insertNode(self.root, val)

    def insertNode(self, current, val):




        return False

    def bsearch(self, val):

        return False

    def searchNode(self, current, val):

        return False


if __name__ == "__main__":

    # iteration
    set_szs = [10]
    timing = [0,0,0,0]
    sequential_time = 0
    BST_time = 0
    num_numbers = int(input("How many numbers to generate? "))
    bits = 32

    # my stuff
    # Array_Search
    array = []
    random.seed(time)
    for i in range(0,num_numbers):
        array.append(random.getrandbits(bits))
    print("Last element: ", array[num_numbers-1])

    searcher = Array_Search(array)
    searcher.create_bsearchtree()
    # searcher.init_array_search(array)
    while True:
        search_for = input("Search for an 8-bit number: ")
        if search_for != "exit":
            search_for = int(search_for)
            # search calls go here
            timing[0] = time.perf_counter_ns()
            print("sequential search:", searcher.sequential_search(search_for))
            timing[1] = time.perf_counter_ns()
            sequential_time = timing[1] - timing[0]
            print("sequential time (ns):", sequential_time)

            timing[2] = time.perf_counter_ns()
            print("Binary search tree:", searcher.bsearchtree(search_for))
            timing[3] = time.perf_counter_ns()
            BST_time = timing[3] - timing[2]
            print("BST time (ns):", BST_time)
        else:
            break