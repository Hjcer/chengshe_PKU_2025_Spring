size = int(input())
global graph 
graph = []

for i in range(size):
    line = [0 for i in range(size)]
    graph.append(line)

def find_the_corner(size):
    corners = []
    for i in range(size):
        for j in range(size):
            if i + 1 < size and j + 1 < size and graph[i][j] == 0 and graph[i + 1][j] == 0 and graph[i][j + 1] == 0:
                corners.append((i, j))
            if i + 1 < size and j - 1 >= 0 and graph[i][j] == 0 and graph[i + 1][j] == 0 and graph[i][j - 1] == 0:
                corners.append((i, j))
            if i - 1 >= 0 and j + 1 < size and graph[i][j] == 0 and graph[i - 1][j] == 0 and graph[i][j + 1] == 0:
                corners.append((i, j))
            if i - 1 >= 0 and j - 1 >= 0 and graph[i][j] == 0 and graph[i - 1][j] == 0 and graph[i][j - 1] == 0:
                corners.append((i, j))
    return corners

for i in range(size):
    nums =  input().split()
    for j in range(size):
        graph[i][j] = int(nums[j])



corners = find_the_corner(size)


l = corners[3][0] - corners[0][0] - 1
h = corners[3][1] - corners[0][1] - 1

print(l * h)