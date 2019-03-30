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
class Envelope    : public Component,
public Slider::Listener
{
public:
    Envelope(SaucyWavesSynthAudioProcessor& p);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    
    Slider attackSlider;
    Slider releaseSlider;
    Slider decaySlider;
    Slider sustainSlider;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decayTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SaucyWavesSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
