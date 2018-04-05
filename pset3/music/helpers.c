// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"


int to_int(char digit);



// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // Return 1 if the format of the fraction is not correct
    if(!fraction &&strlen(fraction) != 3 && fraction[1] != '/'){
        return 1;
    }

    int numerator = to_int(fraction[0]);
    int deno = to_int(fraction[2]);

    return (8/deno*numerator);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
        // TODO
    // Parse the String into its Note and Octave

    //Get the note from the string
    char note_char = note[0];
    // Get the octave from the string
    int octave = to_int(note[strlen(note) - 1]);

    // Determine Frequency of note in the given octive
    double freq = 0.0;

    // Set the frequency for this note
    switch(note_char)
    {

        case 'B' :
            freq = 440.0 * (pow(2.0, (2.0 / 12.0)));
            break;
        case 'A' :
            freq = 440.0;
            break;
        case 'G' :
            freq = 440.0 / (pow(2.0, (2.0 / 12.0)));
            break;
        case 'F' :
            freq = 440.0 / (pow(2.0, (4.0 / 12.0)));
            break;
        case 'E' :
            freq = 440.0 / (pow(2.0, (5.0 / 12.0)));
            break;
        case 'D' :
            freq = 440.0 / (pow(2.0, (7.0 / 12.0)));
            break;
        case 'C' :
            freq = 440.0 / (pow(2.0, (9.0 / 12.0)));
            break;

        default :
            return 0;
    }

    // Adjustment for flat or sharp
    if(note[1] == 'b')
    {
        freq /= (pow(2.0, (1.0 / 12.0)));
    }
    else if(note[1] == '#')
    {
        freq *= (pow(2.0, (1.0 / 12.0)));
    }

    // Adjust octave
    if(octave > 4)
    {
        int power = pow(2, octave - 4);
        freq *= power;
    }
    else if(octave < 4)
    {
        int power = pow(2, 4 - octave);
        freq /= power;
    }

    return round(freq);;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if(s && strlen(s) == 0){
        return true;
    }
    return false;
}

// Convert a char to an interger
int to_int(char digit)
{
    return digit - 48;
}