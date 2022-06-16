import os
from os import listdir

answer = input("Debug or Release mode? ")
answer = answer.lower()
os.system(f"make {answer}")

testDir = listdir("test")
for c, i in enumerate(testDir):
    print(f"[TEST {c+1}/{len(testDir)}] ( {i} )")
    os.system(f"./mufi test/{i}")