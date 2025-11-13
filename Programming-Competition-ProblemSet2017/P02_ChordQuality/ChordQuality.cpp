// Xiaolou Huang (Lor)
// Problem 2
//  Copyright © 2018 XIAOLOU HUANG. All rights reserved.
//
// Assume the keyboard system matches with the notes, so whenever she press a key, it will tell which note it is.
// Note: chord names do not change on different octave. So we only need one octave.
// Example1 input: 1st finger: G, 3rd finger: A#, 5th finger: D
// Example1 output: G-Bb-D
//                  G Min
// Example2 input: 1st finger: C#, 3rd finger: E#, 5th finger: G#
//example 2 output: C#-E#-G#
//                  C# Maj
//                  Db-F-Ab
//                  Db Maj

#include <iostream>
#include <string>
#include <vector>

class ChordQuality {
public:
    // variables
    int firstNotePosition, thirdNotePosition, fifthNotePosition; // index for 'octave' array
    int temp1, temp2; // to hold index for 'scale' array
    int first_interval, second_interval; // two intervals to find out the 'chardName' (eg. Maj, Min, Aug, Dim)
    std::string chordName;
    std::string solution1, solution2; // output strings
    std::string firstNote1, firstNote2; // chord names
    std::string first, third, fifth;
    
    // all the notes in one octave
    std::vector < std::vector<std::string> > octave = { { "C", "B#" }, { "C#", "Db" }, { "D" }, { "D#", "Eb" }, { "E", "Fb" }, { "F", "E#" },
        { "F#", "Gb" }, { "G" }, { "G#", "Ab" }, { "A" }, { "A#", "Bb" }, { "B", "Cb" } };
    
    // add chord names into two-dimensional array
    // Maj 4, 3, Min 3, 4, Aug 4, 4, Dim 3, 3
    std::vector< std::vector<std::string> > chords = { { "4", "3", "Maj" }, { "3", "4", "Min" }, { "4", "4", "Aug" }, { "3", "3", "Dim" } };
    
    // this array is for checking if the next note is two letters away from the
    // previous note, eg. A# Cb is two letters away, but not A# B#.
    std::vector<char> scale = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
    
    // constructor
    ChordQuality(std::string first, std::string third, std::string fifth) {
        this->first = first;
        this->third = third;
        this->fifth = fifth;
    }
    
    // methods
    void findNotesPosition();
    void findIntervals();
    void findChordName();
    void findCombinations();
    void print();
};

void ChordQuality::findNotesPosition() {
    // find the index in 'octave' array for notes that passed into this function.
    for (int i = 0; i < octave.size(); i++) {
        for (int j = 0; j < octave[i].size(); j++) {
            if (first.compare(octave[i][j]) == 0) {
                firstNotePosition = i;
            }
            if (third.compare(octave[i][j]) == 0) {
                thirdNotePosition = i;
            }
            if (fifth.compare(octave[i][j]) == 0) {
                fifthNotePosition = i;
            }
        }
    }
}

void ChordQuality::findIntervals() {
    // find the distance among three notes
    // checking if distance is out of bound
    if (thirdNotePosition < firstNotePosition) {
        first_interval = 12 - firstNotePosition + thirdNotePosition;
    } else {
        first_interval = thirdNotePosition - firstNotePosition;
    }
    if (fifthNotePosition < thirdNotePosition) {
        second_interval = 12 - thirdNotePosition + fifthNotePosition;
    } else {
        second_interval = fifthNotePosition - thirdNotePosition;
    }
}

void ChordQuality:: findChordName() {
    // find out the chord name
    for (int i = 0; i < chords.size(); i++) {
        if (first_interval == stoi(chords[i][0]) && second_interval == stoi(chords[i][1])) {
            chordName = chords[i][2];
        }
    }
}

void ChordQuality::findCombinations() {
    // find out possible three notes combinations
    // first possibility
    // find the letter of first note and then find the correct third note, and then correct fifth note.
    for (int j = 0; j < scale.size(); j++) {
        if (octave[firstNotePosition][0].at(0) == scale[j]) { // check first note
            solution1 = octave[firstNotePosition][0];
            firstNote1 = octave[firstNotePosition][0];
            temp1 = (j + 2) % 7; // Increment two letters
            for (int k = 0; k < octave[thirdNotePosition].size(); k++) {
                if (octave[thirdNotePosition][k].at(0) == scale[temp1]) { // check third note
                    solution1 = solution1 + "-" + octave[thirdNotePosition][k];
                    temp2 = (temp1 + 2) % 7; // increment two letters
                    for (int l = 0; l < octave[fifthNotePosition].size(); l++) {
                        if (octave[fifthNotePosition][l].at(0) == scale[temp2]) { // check fifth note
                            solution1 = solution1 + "-" + octave[fifthNotePosition][l];
                        }
                    }
                }
            }
        }
    }
    // second possibility
    if (octave[firstNotePosition].size() == 2) {
        for (int j = 0; j < scale.size(); j++) {
            if (octave[firstNotePosition][1].at(0) == scale[j]) { // check first note
                solution2 = octave[firstNotePosition][1];
                firstNote2 = octave[firstNotePosition][1];
                temp1 = (j + 2) % 7; // increment two letters
                for (int k = 0; k < octave[thirdNotePosition].size(); k++) {
                    if (octave[thirdNotePosition][k].at(0) == scale[temp1]) { // check third note
                        solution2 = solution2 + "-" + octave[thirdNotePosition][k];
                        temp2 = (temp1 + 2) % 7; // increment two letters
                        for (int l = 0; l < octave[fifthNotePosition].size(); l++) {
                            if (octave[fifthNotePosition][l].at(0) == scale[temp2]) { // check fifth note
                                solution2 = solution2 + "-" + octave[fifthNotePosition][l];
                            }
                        }
                    }
                }
            }
        }
    }
}

// call all the functions and print
void ChordQuality::print() {
    findNotesPosition();
    findIntervals();
    findChordName();
    findCombinations();
    std::cout << solution1 << std::endl << firstNote1 << " " << chordName << std::endl;
    if (solution2 != "") {
        std::cout << solution2 << std::endl << firstNote2 << " " << chordName << std::endl;
    }
}

int main() {
    
    std::string first;
    std::string third;
    std::string fifth;
    
    std::cout << "1st finger: " << std::endl;
    std::cin >> first;
    std::cout << "3rd finger: " << std::endl;
    std::cin >> third;
    std::cout << "5th finger: " << std::endl;
    std::cin >> fifth;
    
    ChordQuality obj(first, third, fifth);
    obj.print();
    
    return 0;
}
