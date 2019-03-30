/*
  ==============================================================================

    Filter.cpp
    Created: 30 Mar 2019 12:16:36am
    Author:  Aurélien Merz

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(SaucyWavesSynthAudioProcessor& p):
processor(p)
{
    setSize(200, 200);
    filterMenu.addItem("Low-pass", 1);
    filterMenu.addItem("High-pass", 2);
    filterMenu.addItem("Band-pass", 3);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);
    filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree,"filterType",filterMenu);
    
    filterCutOff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutOff.setRange(20.0, 20000.0);
    filterCutOff.setValue(600.0f);
    filterCutOff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutOff.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterCutOff);
    filterVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterCutOff",filterCutOff);
    filterCutOff.setSkewFactorFromMidPoint(1000.0);
    
    filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1, 5);
    filterRes.setValue(1);
    filterRes.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterRes.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterRes);
    resVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterRes",filterRes);
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10,getWidth(),20);
    g.fillAll (Colours::black);   // clear the background
    g.setColour(Colours::white);
    g.drawText("Filter",titleArea, Justification::centredTop);
    
    Rectangle<float> area (25,25,150,150);
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    filterMenu.setBounds(area.removeFromTop(20));
    filterCutOff.setBounds(30, 100, 70, 70);
    filterRes.setBounds(100, 100, 70, 70);
    
    

}
