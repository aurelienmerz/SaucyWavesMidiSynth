/*
  ==============================================================================

    Oscillator.h
    Created: 29 Mar 2019 10:56:50pm
    Author:  Aurélien Merz

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Oscillator    : public Component
{
public:
    Oscillator();
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
