/*
  ==============================================================================

    MasterGain.cpp
    Created: 7 Apr 2019 8:07:21pm
    Author:  Aurélien Merz

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "MasterGain.h"

//==============================================================================
MasterGain::MasterGain(SaucyWavesSynthAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    //slider initialization values
    mastergainSlider.setSliderStyle(Slider::Rotary);
    mastergainSlider.setSliderSnapsToMousePosition(false);
    mastergainSlider.setRange(0.0f, 1.0f);
    mastergainSlider.setValue(1.0f);
    mastergainSlider.setDoubleClickReturnValue(true, 1.0f);
    mastergainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    mastergainSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&mastergainSlider);
    
    pbupSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pbupSlider.setSliderSnapsToMousePosition(false);
    pbupSlider.setRange(0, 12);
    pbupSlider.setValue(12);
    pbupSlider.setTextBoxStyle(Slider::TextBoxRight, true, 35, 25);
    addAndMakeVisible(&pbupSlider);
    
    pbdownSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pbdownSlider.setSliderSnapsToMousePosition(false);
    pbdownSlider.setRange(0, 12);
    pbdownSlider.setValue(12);
    pbdownSlider.setTextBoxStyle(Slider::TextBoxRight, true, 35, 25);
    addAndMakeVisible(&pbdownSlider);
    
    
    
    //sends value of the sliders to the tree state in the processor
    mastergainVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "mastergain", mastergainSlider);
    pbupVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "pbup", pbupSlider);
    pbdownVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "pbdown", pbdownSlider);
}

MasterGain::~MasterGain()
{
}

void MasterGain::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10, getWidth(),25);
    auto bckgrnd = Colour();
    g.fillAll (bckgrnd);   // clear the background
    g.setColour(Colours::white);
    g.drawText("MASTER", titleArea, Justification::centredTop);
    
    //static positioning for now due to time, make dynamic later
//    g.drawText ("Master", 53, 40, 40, 20, Justification::centredLeft);
    g.drawText ("PB Up/Down", 53, 90, 90, 20, Justification::centred);
    
    Rectangle<float> area (25,25,150,150);
    //    auto colour = Colour(84, 109, 229);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(area,20.0f, 3.0f);
}

void MasterGain::resized()
{
    //draws the sliders...we use a rectangle object to dynamically size the UI (if we want to resize for IPad etc without needing to change ALL settings
    juce::Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderWidth = 25;
    int sliderHeight = 25;
    
    //draw sliders by reducing area from rectangle above
    
    mastergainSlider.setBounds(70, 30, 60, 60);
    pbdownSlider.setBounds (area.removeFromBottom(sliderWidth).removeFromTop(sliderHeight));
    pbupSlider.setBounds (area.removeFromBottom(sliderWidth).removeFromTop(sliderHeight));
    
}
