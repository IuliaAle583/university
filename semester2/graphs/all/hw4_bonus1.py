class Node:
    def __init__(self, x):
        self.data = x
        self.left = None
        self.right = None

#pre + post

def reconstruct_tree(pre, post, idx, l, h):
    if idx[0] >= len(pre) or l > h:
        return None
    root = Node(pre[idx[0]])    # create root node with current preorder value
    idx[0] += 1
    if l == h:
        return root # only one element left, it's a leaf
    i = -1
    # find the next node in preorder inside the postorder array
    for j in range(l, h + 1):
        if idx[0] < len(pre) and pre[idx[0]] == post[j]:
            i = j
            break
    if i != -1:
        # recursively build left and right subtrees
        root.left = reconstruct_tree(pre, post, idx, l, i)
        root.right = reconstruct_tree(pre, post, idx, i + 1, h - 1)
    return root


def final_tree(pre, post):
    idx = [0]
    return reconstruct_tree(pre, post, idx, 0, len(post) - 1)

#pre + ino

# helper to search index of value in inorder between indices l and r
def search_inorder(ino, value, l, r):
    for i in range(l, r + 1):
        if ino[i] == value:
            return i
    return -1

def build_tree_pre_ino(ino, pre, pre_index, l, r):
    if l > r:
        return None
    root_val = pre[pre_index[0]]
    pre_index[0] += 1
    root = Node(root_val)
    index = search_inorder(ino, root_val, l, r)     # find position in inorder
    # recursively build left and right subtrees
    root.left = build_tree_pre_ino(ino, pre, pre_index, l, index - 1)
    root.right = build_tree_pre_ino(ino, pre, pre_index, index + 1, r)

    return root

def build_tree_pre(ino, pre):
    pre_index = [0]
    return build_tree_pre_ino(ino, pre, pre_index, 0, len(pre) - 1)


#post + ino

# helper to search value in inorder between start and end
def search_post_inorder(v, start, end, value):
    for i in range(start, end + 1):
        if v[i] == value:
            return i
    return -1

def build(ino, post, in_start, in_end, post_index):
    if in_start > in_end:
        return None

    node = Node(post[post_index[0]])    # get current root from postorder
    post_index[0] -= 1

    if in_start == in_end:
        return node # leaf node
    # find index of current node in inorder
    in_index = search_post_inorder(ino, in_start, in_end, node.data)
    # build right subtree first ( process postorder from end)
    node.right = build(ino, post, in_index + 1, in_end, post_index)
    node.left = build(ino, post, in_start, in_index - 1, post_index)

    return node


def build_tree_post(ino, post):
    n = len(ino)
    post_index = [n - 1]    # start from end of postorder
    return build(ino, post, 0, n - 1, post_index)


