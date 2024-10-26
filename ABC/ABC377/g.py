class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False
        self.depth = 0


class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for i, char in enumerate(word):
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
            node.depth = i + 1
        node.is_end = True

    def longest_common_prefix_length(self, target: str) -> int:
        node = self.root
        for i, char in enumerate(target):
            if char not in node.children:
                return i
            node = node.children[char]
        return node.depth


n = int(input())
words = [input() for _ in range(n)]
trie = Trie()
for word in words:
    res = trie.longest_common_prefix_length(word)
    ori_len = len(word)
    ans = min(len(word), (len(word) - res) + (ori_len - res))
    print(ans, res)
    trie.insert(word)
