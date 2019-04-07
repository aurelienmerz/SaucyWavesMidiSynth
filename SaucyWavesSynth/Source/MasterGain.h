/*
  ==============================================================================

    MasterGain.h
    Created: 7 Apr 2019 8:07:21pm
    Author:  Aurélien Merz

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class MasterGain: public Component
{
public:
    MasterGain(SaucyWavesSynthAudioProcessor&);
    ~MasterGain();
    
    void paint (Graphics&) override;
    void resized() override;
    
    
private:
    Slider mastergainSlider;
    Slider pbupSlider;
    Slider pbdownSlider;
    
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mastergainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pbupVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pbdownVal;
    
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SaucyWavesSynthAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterGain)
};
