'''
Monty Hall Problem Game and Simulator
Created by Andres Bravo
April 25, 2020
'''

class monty_hall():
    '''
    Monty Hall Class. It offers the posibility to create a game with user input, or 
    simulate x amount of games played.
    '''
    
    def __init__(self):
        '''
        Avoided using __init__ because of simulation, and just want to initialize the game
        when we want to start a new game and not when we create the class.
        '''
        return
    
    def initialize(self):
        '''
        Initializes the game. Sets 3 doors as a list of booleans.
        Randomly chooses 1 door as the price and obtains the information
        of what doors contain nothing. 
        '''
        import numpy as np
        self.doors = [False,False,False] #list that acts as doors.
        self.incorrect_doors = []
        self.correct_door = np.random.randint(0,3, size=1)[0] #creates a winning door (this is the index)
        self.doors[self.correct_door] = True #changes the door based on the index above
        
        for index,door in enumerate(self.doors): #finds what indexes are the doors that contain nothing.
            if door == False:
                self.incorrect_doors.append(index)
                
    def choice(self,user_input):
        '''
        Stores the choice that the user provides.
        '''
        self.user_input = user_input
        
    def open_a_door(self):
        '''
        Opens a door that must have 2 parameters:
        1) the door opened must not be chosen by the user.
        2) the door opened must not contain the price, it is a empty door (or False in the list).

        The function will randomly try a number from the incorrect doors list until it complies
        with the paramers set.
        '''
        import numpy as np
        self.open_door = np.random.choice(self.incorrect_doors)
        
        while self.open_door == self.user_input:
            self.open_door = np.random.choice(self.incorrect_doors)
            
        return self.open_door
    
    def change(self,change_choice):
        '''
        Here we give the option to the user to change doors.
        If change is desire, we change it to the remaining door.
        The parameters for the remianing doors are:
        1) Door most not have been opened.
        2) Door is different from the one chosen originally by the user.

        This is done by choosing randomly one door from the 3 until the 
        parameters are fufilled.
        '''
        import numpy as np

        if change_choice == True:
            self.final_user_choice = np.random.randint(0,3,size=1)[0]
            
            while self.final_user_choice == self.user_input or self.final_user_choice ==  self.open_door:
                self.final_user_choice = np.random.randint(0,3,size=1)[0]
                
        else:
            self.final_user_choice = self.user_input
            
    def finish(self):
        '''
        We check if the final choice (regardless of changing or not chnaging door)
        is or is not the correct door.
        The function returns a boolean depending if the user choice
        was the correct one or not.
        '''
        if self.final_user_choice == self.correct_door:
            return True
        else:
            return False
    
    def simulation(self, tries, change=True):
        '''
        The simulation is able to play the Monty Hall game several times and returns the
        amount of wins and looses that the user obtained relative to option of changing or not.
        The simulation will run for and x amount of tries (it is a parameter).
        The simulation will always choose to either change or not depending on the 
        boolean value of the parameter.
        '''

        import numpy as np
        simulation_try = 0
        wins = 0
        looses = 0
        games = []

        while tries > simulation_try:

            self.initialize()
            choice = np.random.randint(0,3,size=1)[0]
            self.choice(choice)
            door_opened = self.open_a_door()
            self.change(change)
            result = self.finish()

            if result == True:
                wins += 1
                games.append(1)
            elif result == False:
                looses += 1
                games.append(0)
            simulation_try += 1 

        return wins,looses,games

if __name__ == "__main__":
    '''
    Simulates 100 games with changing and 100 games with not changing.
    At the end it will plot the amount of wins and looses of each option.
    
    Changing will always yield more wins.

    Video I recommend to understand problem 
    by Numberphile: https://www.youtube.com/watch?v=4Lb-6rxZxx0
    '''

    game = monty_hall()
    wins_c,looses_c,x = game.simulation(100)
    wins_nc,looses_nc,x = game.simulation(100, change=False)

    import matplotlib.pyplot as plt

    fig, ax = plt.subplots()

    ax.bar([1,1.5], [wins_c,wins_nc], width=0.3, color='orange')
    ax.bar([1,1.5], [looses_c,looses_nc], width=0.3, bottom=[wins_c,wins_nc], color='grey')

    ax.set_xticks([1,1.5])
    ax.set_xticklabels(["Change","No Change"])

    ax.set_title("Monty Hole Change vs No Change (100 games each)")
    ax.legend(["Wins","Looses"],loc="upper center")
    plt.savefig("Monty.pdf")

    print("Change:")
    print("Wins:",wins_c)
    print("Looses:",looses_c)
    print("\n")
    print("No Change:")
    print("Wins:",wins_nc)
    print("Looses:",looses_nc)

    plt.axis("on")
    plt.show()
