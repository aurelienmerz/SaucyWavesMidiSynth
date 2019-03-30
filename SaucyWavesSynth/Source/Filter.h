/*
  ==============================================================================

    Filter.h
    Created: 30 Mar 2019 12:16:36am
    Author:  Aurélien Merz

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(SaucyWavesSynthAudioProcessor& p);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
    ComboBox filterMenu;
    Slider filterCutOff;
    Slider filterRes;
    ScopedPointer <AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> filterVal;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> resVal;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SaucyWavesSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
