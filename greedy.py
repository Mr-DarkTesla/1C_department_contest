import numpy as np
from itertools import combinations
from collections import defaultdict

verbose = True

def propagation(cities):
    delta = len(cities)
    while delta > 0:
        start = len(cities)
        for (left, right) in combinations(cities, 2):
            for city in set(graph[left]).intersection(set(graph[right])):
                if city not in cities:
                    cities.append(city)
                    if verbose:
                        print(f"Infested: {city}")
        delta = len(cities) - start
    return cities


num_of_vertices, num_of_edges = map(int, input().split())
num_of_vertices += 1
vertices = np.arange(1, num_of_vertices)
edges = [tuple(map(int, input().split())) for _ in range(num_of_edges)]

graph = defaultdict(list)
for edge in edges:
    graph[edge[0]].append(edge[1])
    graph[edge[1]].append(edge[0])

infested = []
initial = []

ans = 0
while True:
    infested = propagation(infested)
    if len(infested) >= num_of_vertices - 1:
        break
    next = min(set(vertices).difference(set(infested)))
    infested.append(next)
    initial.append(next)
    if verbose:
        print(f"Add starting: {next}")
    ans += 1
if verbose:
    print(f"Total count: {ans}")
    print(f"Infested: {initial}")
else:
    print(ans)
    print(*initial)