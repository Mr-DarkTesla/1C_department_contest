import numpy as np
from collections import defaultdict
from itertools import permutations

verbose = True
permutation_flag = False


def propagation(cities, new):
    new_set = set(graph[new])
    delta = len(cities)
    while delta > 0:
        start = len(cities)
        for left in cities:
            for city in new_set.intersection(set(graph[left])):
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


def solve(verices_local):
    infested = []
    initial = []

    ans = 0
    while True:
        if len(infested) >= num_of_vertices - 1:
            break
        next = min(set(verices_local).difference(set(infested)))
        initial.append(next)
        if verbose:
            print(f"Add starting: {next}")
        infested = propagation(infested, next)
        infested.append(next)
        ans += 1
    if verbose:
        print(f"Total count: {ans}")
        print(f"Infested: {initial}")
    return ans, initial


if not permutation_flag:
    print(*solve(vertices), sep='\n')
else:
    verbose = False
    anses = []
    initials = []
    for permutation in permutations(vertices):
        solution = solve(permutation)
        anses.append(solution[0])
        initials.append(solution[1])
    print(f"Total count: {min(anses)}")
    print(f"Infested: {initials[np.argmin(anses)]}")
