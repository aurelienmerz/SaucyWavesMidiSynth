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
class Filter    : public Component, public LookAndFeel_V4
{
public:
    Filter(SaucyWavesSynthAudioProcessor& p);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;
    
    /* Overriding the method to draw the faders new look */
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
    ComboBox filterMenu;
    LookAndFeel_V4 lookAndFeel;
    Slider filterCutOff;
    Slider filterRes;
    Label lowFreq;
    Font lowFont;
    Label highFreq;
    Font highFont;
    ScopedPointer <AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> filterVal;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> resVal;
    
    SaucyWavesSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
