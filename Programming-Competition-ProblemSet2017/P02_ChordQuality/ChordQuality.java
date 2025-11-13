// Xiaolou Huang (Lor)
// Problem 2
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

package solutions;

import java.util.Scanner;

public class ChordQuality {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("note on 1st finger: ");
        String first = input.nextLine();
        System.out.println("note on 3rd finger: ");
        String third = input.nextLine();
        System.out.println("note on 5th finger: ");
        String fifth = input.nextLine();
        chordQuality(first, third, fifth); // pass in the notes
        input.close();
    }

    public static void chordQuality(String first, String third, String fifth) {
        // variables
        int firstNotePosition = 0; // index for 'octave' array
        int thirdNotePosition = 0; // index for 'octave' array
        int fifthNotePosition = 0; // index for 'octave' array
        int temp1 = 0; // to hold index for 'scale' array
        int temp2 = 0; // to hold index for 'scale' array
        int first_interval, second_interval; // two intervals to find out the 'chardName' (eg. Maj, Min, Aug, Dim)
        String chordName = null;
        String solution1 = null; // output 1
        String solution2 = null; // possible output 2
        String firstNote1 = null; // chord name, eg. C# Maj, C# is firstNote1
        String firstNote2 = null; // chord name

        // all the notes in one octave
        String octave[][] = { { "C", "B#" }, { "C#", "Db" }, { "D" }, { "D#", "Eb" }, { "E", "Fb" }, { "F", "E#" },
                { "F#", "Gb" }, { "G" }, { "G#", "Ab" }, { "A" }, { "A#", "Bb" }, { "B", "Cb" } };

        // add chord names into two-dimensional array
        // Maj 4, 3, Min 3, 4, Aug 4, 4, Dim 3, 3
        String chords[][] = { { "4", "3", "Maj" }, { "3", "4", "Min" }, { "4", "4", "Aug" }, { "3", "3", "Dim" } };

        // this array is for checking if the next note is two letters away from the
        // previous note, eg. A# Cb is two letters away, but not A# B#.
        char scale[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };

        // find the index in 'octave' array for notes that passed into this function.
        for (int i = 0; i < octave.length; i++) {
            for (int j = 0; j < octave[i].length; j++) {
                if (first.equals(octave[i][j])) {
                    firstNotePosition = i;
                }
                if (third.equals(octave[i][j])) {
                    thirdNotePosition = i;
                }
                if (fifth.equals(octave[i][j])) {
                    fifthNotePosition = i;
                }
            }
        }

        // find the distance among three notes
        // checking if distance is out of bound
        if (thirdNotePosition < firstNotePosition) {
            first_interval = 12 - firstNotePosition + thirdNotePosition;
        } else {
            first_interval = Math.abs(firstNotePosition - thirdNotePosition);
        }
        if (fifthNotePosition < thirdNotePosition) {
            second_interval = 12 - thirdNotePosition + fifthNotePosition;
        } else {
            second_interval = Math.abs(fifthNotePosition - thirdNotePosition);
        }

        // find out the chord name
        for (int i = 0; i < chords.length; i++) {
            if (String.valueOf(first_interval).equals(chords[i][0])
                    && String.valueOf(second_interval).equals(chords[i][1])) {
                chordName = chords[i][2];
            }
        }

        // find out possible three notes combinations
        // first possibility
        // find the letter of first note and then find the correct third note, and then correct fifth note.
        for (int j = 0; j < scale.length; j++) {
            if (octave[firstNotePosition][0].charAt(0) == scale[j]) { // check first note
                solution1 = octave[firstNotePosition][0];
                firstNote1 = octave[firstNotePosition][0];
                temp1 = (j + 2) % 7; // Increment two letters
                for (int k = 0; k < octave[thirdNotePosition].length; k++) {
                    if (octave[thirdNotePosition][k].charAt(0) == scale[temp1]) { // check third note
                        solution1 = solution1 + "-" + octave[thirdNotePosition][k];
                        temp2 = (temp1 + 2) % 7; // increment two letters
                        for (int l = 0; l < octave[fifthNotePosition].length; l++) {
                            if (octave[fifthNotePosition][l].charAt(0) == scale[temp2]) { // check fifth note
                                solution1 = solution1 + "-" + octave[fifthNotePosition][l];
                            }
                        }
                    }
                }
            }
        }
        // second possibility
        if (octave[firstNotePosition].length == 2) {
            for (int j = 0; j < scale.length; j++) {
                if (octave[firstNotePosition][1].charAt(0) == scale[j]) { // check first note
                    solution2 = octave[firstNotePosition][1];
                    firstNote2 = octave[firstNotePosition][1];
                    temp1 = (j + 2) % 7; // increment two letters
                    for (int k = 0; k < octave[thirdNotePosition].length; k++) {
                        if (octave[thirdNotePosition][k].charAt(0) == scale[temp1]) { // check third note
                            solution2 = solution2 + "-" + octave[thirdNotePosition][k];
                            temp2 = (temp1 + 2) % 7; // increment two letters
                            for (int l = 0; l < octave[fifthNotePosition].length; l++) {
                                if (octave[fifthNotePosition][l].charAt(0) == scale[temp2]) { // check fifth note
                                    solution2 = solution2 + "-" + octave[fifthNotePosition][l];
                                }
                            }
                        }
                    }
                }
            }
        }
        // output
        System.out.printf("Output: \n%s\n%s %s\n\n", solution1, firstNote1, chordName);
        if (solution2 != null) {
            System.out.printf("Output: \n%s\n%s %s\n", solution2, firstNote2, chordName);

        }
    }
}
