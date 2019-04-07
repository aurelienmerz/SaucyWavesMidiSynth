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
class MasterGain: public Component, public LookAndFeel_V4
{
public:
    MasterGain(SaucyWavesSynthAudioProcessor&);
    ~MasterGain();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::white);
        g.fillEllipse (rx, ry, rw, rw);
        
        // outline
        g.setColour (Colours::white);
        g.drawEllipse (rx, ry, rw, rw, 0.10f);
        
        Path p;
        auto pointerLength = radius * 0.5f;
        auto pointerThickness = 4.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::black);
        g.fillPath (p);
    }
    
    
private:
    Slider mastergainSlider;
    Slider pbupSlider;
    Slider pbdownSlider;
    LookAndFeel_V4 lookAndFeel;
    
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mastergainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pbupVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pbdownVal;
    
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SaucyWavesSynthAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterGain)
};
