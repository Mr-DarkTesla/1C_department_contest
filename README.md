# Contest to 1C department
## Якушев Георгий

## Задача 2 / Алгоритмы

___
### Что сделано?
Было реализовано два решения.
1) `lower_bound.cpp` - алгоритм на `C++` который считает три величины: число компонент связности, число мостов 
и число точек сочленения в графе. Изначально предполагалось, что этой информации достаточно, чтобы найти минимальное
число городов и восстановить ответ. Но в процессе решения был придуман контрпример, который показал, что на 
некоторых графах этой информации недостаточно, чтобы решить задачу. Но тем не менее эта программа дает некоторую
нижнюю оценку на искомое число городов. 
2) `greedy.py` - жадный алгортм на `python`, который  дает отвтет при запуске на любых корректных входных данных. 
У этого алгоритма есть 2 проблемы. Во-первых он очень долгий. Во-вторых он дает лишь верхнюю оценку на искомое число.

___
### Подробнее про реализацию:
1) `lower_bound.cpp` фактичести там присутсвуют 2.5 разных алгоритма.
Первый - система непересекающихся множеств, она позволяет найти число компонент связнсти за
O(alpha(n)), где alpha - обратная функция Аккермана.
Второй - это алгоритм поиска мостов и точек сочленения по функциям t_up и t_in при обходе в глубину.
Здесь асимптотика O(n + m), где n, m - число вершин и ребер соответственно.
2) `greedy.py` смотрит в цикле, кого можно заразить - того заражает, из оставшихся берет минимальную вершину. Также
можно в коде поднять флаг `permutation_flag`, чтобы перибирать все порядки добавления элементов в массив изначально зараженных. Это работает очень долго.
Но это точно решит поставленую задачу.
___
### Как запустить?
0) Стоит отметить, что я слегка поменял формат ввода, и теперь вместе с числом ребер программа получает число вершин.
Это было сделано для упрощения реализации ввода.
Новый формат: `N, M \n from to \n ...`. Также программа ожидает города в 1 индексации и считает, что все города до `N`
участвуют в игре, и даже если они не указаны в ребрах, то их все равно можно (и нужно заразить), как отдельну вершину. 
1) В обоих программах есть глобальная переменная  `verbose` она отвечает за подробность выходных данных. Если она `False`,
то программа выдаст минимум данных. При `True` даст дополнительную информацию о решении. Сейчас она `True`.
2) Для запуска `lower_bound.cpp` написан минискрипт на `bash`. Из консоли `$ bash run_lower_bound.sh`.
3) Для запуска `greedy.py` нужно в консоли `python greedy.py`.

___
### Небольшое послесловие
Задача очень инетересная, жаль, что я не смог найти оптимального решения, но думаю,
что мой код является неплохой попыткой. Получается, что найдены верхняя и нижняя границы решения. 