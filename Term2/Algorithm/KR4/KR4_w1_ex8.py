import time
import random
import sys

sys.setrecursionlimit(20000)


class PerformanceTracker:
    def __init__(self):
        self.comparisons = 0
        self.swaps = 0

    def reset(self):
        self.comparisons = 0
        self.swaps = 0


def heap_sort(arr, tracker):
    n = len(arr)

    def sift_down(size, root):
        largest = root
        left = 2 * root + 1
        right = 2 * root + 2

        tracker.comparisons += 1
        if left < size and arr[left] > arr[largest]:
            largest = left

        tracker.comparisons += 1
        if right < size and arr[right] > arr[largest]:
            largest = right

        if largest != root:
            arr[root], arr[largest] = arr[largest], arr[root]
            tracker.swaps += 1
            sift_down(size, largest)

    for i in range(n // 2 - 1, -1, -1):
        sift_down(n, i)

    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        tracker.swaps += 1
        sift_down(i, 0)


def bubble_sort(arr, tracker):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            tracker.comparisons += 1
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                tracker.swaps += 1
                swapped = True
        if not swapped:
            break


def insertion_sort(arr, tracker):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0:
            tracker.comparisons += 1
            if arr[j] > key:
                arr[j + 1] = arr[j]
                tracker.swaps += 1
                j -= 1
            else:
                break
        arr[j + 1] = key


def selection_sort(arr, tracker):
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            tracker.comparisons += 1
            if arr[j] < arr[min_idx]:
                min_idx = j
        if min_idx != i:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
            tracker.swaps += 1


def quick_sort(arr, tracker):
    def _quick_sort(items, low, high):
        if low < high:
            pivot_idx = partition(items, low, high)
            _quick_sort(items, low, pivot_idx - 1)
            _quick_sort(items, pivot_idx + 1, high)

    def partition(items, low, high):
        pivot = items[high]
        i = low - 1
        for j in range(low, high):
            tracker.comparisons += 1
            if items[j] < pivot:
                i += 1
                items[i], items[j] = items[j], items[i]
                tracker.swaps += 1
        items[i + 1], items[high] = items[high], items[i + 1]
        tracker.swaps += 1
        return i + 1

    _quick_sort(arr, 0, len(arr) - 1)


SMALL_SIZE = 100
LARGE_SIZE = 5000

test_cases = {
    "а) Частично отсортированный (небольшой)": sorted(random.sample(range(1, 1000), SMALL_SIZE)),
    "б) По убыванию (небольшой)": list(range(SMALL_SIZE, 0, -1)),
    "в) По возрастанию (небольшой)": list(range(1, SMALL_SIZE + 1)),
    "г) Случайный (небольшой)": random.sample(range(1, 1000), SMALL_SIZE),
    "д) Случайный (большой)": random.sample(range(1, 100000), LARGE_SIZE),
}

for _ in range(10):
    idx1, idx2 = random.randint(0, SMALL_SIZE - 1), random.randint(0, SMALL_SIZE - 1)
    test_cases["а) Частично отсортированный (небольшой)"][idx1], test_cases["а) Частично отсортированный (небольшой)"][
        idx2] = test_cases["а) Частично отсортированный (небольшой)"][idx2], \
    test_cases["а) Частично отсортированный (небольшой)"][idx1]

algorithms = {
    "Пирамидальная (Heap)": heap_sort,
    "Быстрая (Quick)": quick_sort,
    "Пузырьковая (Bubble)": bubble_sort,
    "Вставками (Insertion)": insertion_sort,
    "Выбором (Selection)": selection_sort
}

tracker = PerformanceTracker()

for case_name, base_array in test_cases.items():
    print("-" * 85)
    print(f"ТЕСТ-КЕЙС: {case_name} (Размер: {len(base_array)})")
    print(f"{'Алгоритм':<25} | {'Время (сек)':<12} | {'Сравнения':<15} | {'Перестановки':<15}")
    print("-" * 85)

    for alg_name, alg_func in algorithms.items():
        if len(base_array) == LARGE_SIZE and alg_name in ["Пузырьковая (Bubble)", "Вставками (Insertion)",
                                                          "Выбором (Selection)"]:
            print(f"{alg_name:<25} | {'пропущено':<12} | {'-':<15} | {'-':<15}")
            continue

        arr_copy = base_array.copy()
        tracker.reset()

        start_time = time.perf_counter()
        alg_func(arr_copy, tracker)
        end_time = time.perf_counter()

        execution_time = end_time - start_time

        print(f"{alg_name:<25} | {execution_time:<12.6f} | {tracker.comparisons:<15} | {tracker.swaps:<15}")

print("-" * 85)

