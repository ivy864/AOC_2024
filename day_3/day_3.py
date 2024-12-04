import re

regex = re.compile(
        "don't\\(\\).*?(?:do\\(\\)|$)|mul\\((\\d{1,3}),(\\d{1,3})\\)",
        re.DOTALL)

with open("input.txt") as file:
    data = file.read()

total = 0
for m in regex.finditer(data):
    if m.group(1) is not None:
        total += int(m.group(1)) * int(m.group(2))

print(total)

