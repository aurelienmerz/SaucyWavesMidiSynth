/*
  ==============================================================================

    SynthSound.h
    Created: 6 Mar 2019 3:53:20pm
    Author:  Aurélien Merz

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound: public SynthesiserSound
{    
public:
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
};
