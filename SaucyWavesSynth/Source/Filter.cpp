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

    setSize(250, 250);
    filterMenu.addItem("Low-pass", 1);
    filterMenu.addItem("High-pass", 2);
    filterMenu.addItem("Band-pass", 3);
//    filterMenu.setItemEnabled(3, false);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);
    filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree,"filterType",filterMenu);
    
    filterCutOff.setSliderSnapsToMousePosition(false);
    filterCutOff.setSliderStyle(Slider::Rotary);
    filterCutOff.setNumDecimalPlacesToDisplay(0);
    filterCutOff.setTextValueSuffix(" Hz");
    filterCutOff.setRange(40.0, 20000.0);
    filterCutOff.setValue(20000.0f);
    filterCutOff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutOff.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterCutOff);
    filterVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterCutOff",filterCutOff);
    filterCutOff.setSkewFactorFromMidPoint(1000.0);
    
    filterRes.setSliderSnapsToMousePosition(false);
    filterRes.setSliderStyle(Slider::Rotary);
    filterRes.setRange(1, 5);
    filterRes.setValue(1);
    filterRes.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterRes.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterRes);
    
    lowFreq.setText("Cut-off", NotificationType::dontSendNotification);
    lowFont.setBold(true);
    lowFreq.setFont(lowFont);
    lowFreq.setColour(1, Colours::white);
    highFreq.setText("Resonance", NotificationType::dontSendNotification);
    highFreq.setFont(lowFont);
    highFreq.setColour(1, Colours::white);
    
    addAndMakeVisible(lowFreq);
    addAndMakeVisible(highFreq);
    
    resVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterRes",filterRes);
}

Filter::~Filter()
{
}



void Filter::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10,getWidth(),25);
    auto bckgrnd = Colour();
    g.fillAll (bckgrnd);   // clear the background
    g.setColour(Colours::white);
    g.drawText("FILTER",titleArea, Justification::centredTop);
    
    Rectangle<float> area (25,25,150,150);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void Filter::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    filterMenu.setBounds(area.removeFromTop(20));
    filterCutOff.setBounds(30, 100, 70, 70);
    filterRes.setBounds(100, 100, 70, 70);
    lowFreq.attachToComponent(&filterCutOff, false);
    highFreq.attachToComponent(&filterRes, false);
    
    

}
