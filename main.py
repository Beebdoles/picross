#IMPORTS
#---------------------------------------------------------------------------------------------------

import io
import numbers
import string

#CONFIG VARS
#---------------------------------------------------------------------------------------------------

board_size: int = 10

#FUNCTIONS
#---------------------------------------------------------------------------------------------------

#gets all partitions of `num` containing `count` elements, partitions are not ordered unique
def partition_generator(arr: list, acc: list, count: int, num: int, max_num: int)-> list:

    if num <= 0: return acc
    if len(acc) >= count: return []

    local_acc: list = acc.copy()

    for i in range(0, num + 1):
        acc_curr: list = local_acc.copy()
        acc_curr.append(num - i)
        acc_val: list = partition_generator(arr, acc_curr, count, i, max_num)
        arr.append(acc_val) if len(acc_val) <= count and sum(acc_val) == max_num  else arr
        
    return acc

#adds trailing 0's where necessary
def partition(count: int, num: int) -> list:
    result = []
    partition_generator(result, [], count, num, num)

    for i in result:
        if len(i) != count:
            for k in range(0, count - len(i)): i.append(0)
    
    return result

#MAIN
#---------------------------------------------------------------------------------------------------

numbers: list = []
numbers_str = input("Enter numbers: ").split(" ")
#numbers_str: list = ["9"]
#numbers_str = ["1"]

for i in range(0, len(numbers_str)):
    numbers.append(int(numbers_str[i]))

free_tiles: int = board_size - (sum(numbers) + len(numbers) - 1)
free_spaces: int = len(numbers) + 1

arr = partition(free_spaces, free_tiles)

print(arr)
print(numbers)

grid: list = [0] * 10
numbers.append(0)

if len(arr) > 0:
    for i in arr:
        index: int = 0
        for j in range(0, len(i)):

            if index == len(grid):
                break

            for k in range(index, index + i[j]):
                grid[k] += 0
            index += i[j]

            if index == len(grid):
                break

            for k in range(index, index + numbers[j]):
                grid[k] += 1
            index += numbers[j]

            if numbers[j] == 0 and j < len(i):
                grid[index] += 0
                index += 1 
else:
    index: int = 0
    for j in range(0, len(numbers)):

        for k in range(index, index + numbers[j]):
            grid[k] += 1
        index += numbers[j]

        if index == len(grid):
            break

        grid[index] += 0
        index += 1

print(grid)
print(len(arr))

# index = 0 + 9 = 9 + 1 = 10
# 0 1 2 3 4 5 6 7 8 9
# 1 2 2 2 2 2 2 2 2 1