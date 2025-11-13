#  Xiaolou Huang (Lor)
#  Problem 2
#   Copyright © 2018 XIAOLOU HUANG. All rights reserved.
# 
#  Assume the keyboard system matches with the notes, so whenever she press a key, it will tell which note it is.
#  Note: chord names do not change on different octave. So we only need one octave.
#  Example1 input: 1st finger: G, 3rd finger: A#, 5th finger: D
#  Example1 output: G-Bb-D
#                   G Min
#  Example2 input: 1st finger: C#, 3rd finger: E#, 5th finger: G#
# example 2 output: C#-E#-G#
#                   C# Maj
#                   Db-F-Ab
#                   Db Maj

class ChordQuality:
    # variables
    first = ""
    third = ""
    fifth = ""
    firstNotePosition = 0 # index for 'octave' array
    thirdNotePosition = 0 # index for 'octave' array
    fifthNotePosition = 0 # index for 'octave' array
    temp1 = 0; # to hold index for 'scale' array
    temp2 = 0; # to hold index for 'scale' array
    first_interval = 0 # two intervals to find out the 'chardName' (eg. Maj, Min, Aug, Dim)
    second_interval = 0
    chordName = ""
    solution1 = "" # output 1
    solution2 = "" # possible output 2
    firstNote1 = "" # chord name, eg. C# Maj, C# is firstNote1
    firstNote2 = "" # chord name
    
    # all the notes in one octave
    octave = [ [ "C", "B#" ], [ "C#", "Db" ], [ "D" ], [ "D#", "Eb" ], [ "E", "Fb" ], [ "F", "E#" ],
            [ "F#", "Gb" ], [ "G" ], [ "G#", "Ab" ], [ "A" ], [ "A#", "Bb" ], [ "B", "Cb" ] ]
    
    # add chord names into two-dimensional list
    # Maj 4, 3, Min 3, 4, Aug 4, 4, Dim 3, 3
    chords = [ [ "4", "3", "Maj" ], [ "3", "4", "Min" ], [ "4", "4", "Aug" ], [ "3", "3", "Dim" ] ]
    
    # this list is for checking if the next note is two letters away from the
    # previous note, eg. A# Cb is two letters away, but not A# B#.
    scale = [ 'A', 'B', 'C', 'D', 'E', 'F', 'G' ]

    # constructor
    def __init__(self, first, third, fifth):
        self.first = first
        self.third = third
        self.fifth = fifth
        
    # find the index in 'octave' array for notes that passed into this function.
    def findNotesPosition(self):
        for i in range(len(self.octave)):
            for j in range(len(self.octave[i])):
                if self.first == self.octave[i][j]:
                    self.firstNotePosition = i
                
                if self.third == self.octave[i][j]:
                    self.thirdNotePosition = i
                
                if self.fifth == self.octave[i][j]:
                    self.fifthNotePosition = i
                    
    # find the distance among three notes
    def findIntervals(self):
        # checking if distance is out of bound
        if self.thirdNotePosition < self.firstNotePosition:
            self.first_interval = 12 - self.firstNotePosition + self.thirdNotePosition
        else:
            self.first_interval = self.thirdNotePosition - self.firstNotePosition
             
        if self.fifthNotePosition < self.thirdNotePosition:
            self.second_interval = 12 - self.thirdNotePosition + self.fifthNotePosition
        else:
            self.second_interval = self.fifthNotePosition - self.thirdNotePosition
            
    # find out the chord name   
    def findChordName(self):
        for i in range(len(self.chords)):
            if self.first_interval == int(self.chords[i][0]) and self.second_interval == int(self.chords[i][1]):
                self.chordName = self.chords[i][2]
                
    # find out possible three notes combinations   
    def findCombinations(self):
        # first possibility
        # find the letter of first note and then find the correct third note, and then correct fifth note.
        for j in range(len(self.scale)):
            if self.octave[self.firstNotePosition][0][0] == self.scale[j]: #check first note
                self.solution1 = self.octave[self.firstNotePosition][0]
                self.firstNote1 = self.octave[self.firstNotePosition][0]
                self.temp1 = (j + 2) % 7; # Increment two letters
                for k in range(len(self.octave[self.thirdNotePosition])):
                    if self.octave[self.thirdNotePosition][k][0] == self.scale[self.temp1]: # check third note
                        self.solution1 = self.solution1 + "-" + self.octave[self.thirdNotePosition][k]
                        self.temp2 = (self.temp1 + 2) % 7; # increment two letters
                        for l in range(len(self.octave[self.fifthNotePosition])):
                            if self.octave[self.fifthNotePosition][l][0] == self.scale[self.temp2]: # check fifth note
                                self.solution1 = self.solution1 + "-" + self.octave[self.fifthNotePosition][l]

        # second possibility
        if len(self.octave[self.firstNotePosition]) == 2:
            for j in range(len(self.scale)):
                if self.octave[self.firstNotePosition][1][0] == self.scale[j]: # check first note
                    self.solution2 = self.octave[self.firstNotePosition][1]
                    self.firstNote2 = self.octave[self.firstNotePosition][1]
                    self.temp1 = (j + 2) % 7; # increment two letters
                    for k in range(len(self.octave[self.thirdNotePosition])):
                        if self.octave[self.thirdNotePosition][k][0] == self.scale[self.temp1]: # check third note
                            self.solution2 = self.solution2 + "-" + self.octave[self.thirdNotePosition][k]
                            self.temp2 = (self.temp1 + 2) % 7; # increment two letters
                            for l in range(len(self.octave[self.fifthNotePosition])):
                                if self.octave[self.fifthNotePosition][l][0] == self.scale[self.temp2]: # check fifth note
                                    self.solution2 = self.solution2 + "-" + self.octave[self.fifthNotePosition][l]
        
    def toStringOutput(self):
        self.findNotesPosition()
        self.findIntervals()
        self.findChordName()
        self.findCombinations()
        # output
        print("Output: \n{}\n{} {}\n".format(self.solution1, self.firstNote1, self.chordName))
        if self.solution2 != "":
            print("Output: \n{}\n{} {}\n".format(self.solution2, self.firstNote2, self.chordName))

def main():
    
    first = input("1st finger: ")
    third = input("3rd finger: ")
    fifth = input("5th finger: ")    
    obj = ChordQuality(first, third, fifth)  
    obj.toStringOutput()
    
main()



