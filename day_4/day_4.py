import re

with open("input.txt") as file:
    data = file.read()

total = 0
total += len(re.compile("X(?=MAS)|S(?=AMX)", re.DOTALL).findall(data))
total += len(re.compile("X(?=.{140}M.{140}A.{140}S)|S(?=.{140}A.{140}M.{140}X)", re.DOTALL).findall(data))
total += len(re.compile("X(?=.{141}M.{141}A.{141}S)|S(?=.{141}A.{141}M.{141}X)", re.DOTALL).findall(data))
total += len(re.compile("X(?=.{139}M.{139}A.{139}S)|S(?=.{139}A.{139}M.{139}X)", re.DOTALL).findall(data))

print(f"total: {total}")
