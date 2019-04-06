/*
  ==============================================================================

    Envelope.h
    Created: 29 Mar 2019 11:57:25pm
    Author:  Aurélien Merz

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component, public LookAndFeel_V4//,
//public Slider::Listener
{
public:
    Envelope(SaucyWavesSynthAudioProcessor& p);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    Slider attackSlider;
    Slider releaseSlider;
    Slider decaySlider;
    Slider sustainSlider;
    LookAndFeel_V4 lookAndFeel;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decayTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    
    SaucyWavesSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
