/*
  ==============================================================================

    Oscillator.h
    Created: 29 Mar 2019 10:56:50pm
    Author:  Aurélien Merz

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component,
                      private ComboBox::Listener
{
public:
    Oscillator(SaucyWavesSynthAudioProcessor& p);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox*) override;

private:
    ComboBox oscMenu;
    ScopedPointer <AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SaucyWavesSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
