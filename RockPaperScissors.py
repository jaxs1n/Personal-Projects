# My first real python project
# I don't like python but I have to learn for school...
# Also, why does python just not care what variables are what, like it's annoying:
# "Yea lowk just put it in as whatever and define it later...or don't I dont really care" - Python gods or whatever
# anyways this is a simulation of rock paper scissors
# Takes a while to run once you put the matches to like 10 million, I should've wrote this in cpp, I did I might post here
# Enjoy my weird code!

import random as rand
import time

def ComputerOneChoose(RND):
    computerOneChoice = rand.choice(RND)
    return computerOneChoice

def ComputerTwoChoose(RND):
    computerTwoChoice = rand.choice(RND)
    return computerTwoChoice

#def PlayerChoose(RND):
    #idx = int(input("1 for Rock, 2 for Paper, 3 for Scissors:"))
    #idx -= 1
    #return RND[idx]

def CheckWin(computerOneChoice, computerTwoChoice):
    if computerOneChoice == computerTwoChoice:
        return "TIE"

    if (
        (computerOneChoice == "ROCK" and computerTwoChoice == "SCISSORS") or
        (computerOneChoice == "PAPER" and computerTwoChoice == "ROCK") or 
        (computerOneChoice == "SCISSORS" and computerTwoChoice == "PAPER")
    ):
        return "ONE"
    else:
        return "TWO"

def Main():
    RND = ["ROCK", "PAPER", "SCISSORS"]
    start = time.perf_counter()

    computerOneScore = 0
    computerTwoScore = 0
    tieScore = 0

    for i in range(100000000):
        computerOneChoice = ComputerOneChoose(RND)
        computerTwoChoice = ComputerTwoChoose(RND)

        result = CheckWin(computerOneChoice, computerTwoChoice)

        if result == "ONE":
            computerOneScore += 1
        elif result == "TWO":
            computerTwoScore += 1
        else:
            tieScore += 1

    print("\nFINAL RESULTS")
    print("Computer One Wins:", computerOneScore)
    print("Computer Two Wins:", computerTwoScore)
    print("Ties:", tieScore)

    end = time.perf_counter()
    print("Simulation time:", end - start)
    
Main()
