class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False
        self.depth = 0
        self.word = None  # この位置までの単語を保存


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
            node.word = word  # 各ノードにその位置までの元の単語を保存
        node.is_end = True

    def longest_common_prefix(self, target: str) -> tuple[int, str]:
        node = self.root
        last_valid_node = node

        for i, char in enumerate(target):
            if char not in node.children:
                break
            node = node.children[char]
            last_valid_node = node

        return last_valid_node.depth, last_valid_node.word


n = int(input())
words = [input() for _ in range(n)]
trie = Trie()
for word in words:
    res, match = trie.longest_common_prefix(word)
    if match is None:
        print(len(word))
        trie.insert(word)
        continue
    ori_len = len(match)
    ans = min(len(word), (len(word) - res) + (ori_len - res))
    print(ans)
    trie.insert(word)
