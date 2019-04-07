/*
  ==============================================================================

    Envelope.cpp
    Created: 29 Mar 2019 11:57:25pm
    Author:  Aurélien Merz

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(SaucyWavesSynthAudioProcessor& p):
processor(p)
{
    setSize(200, 200);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(1.0f, 5.0f);
    attackSlider.setValue(0.1f);
    addAndMakeVisible(&attackSlider);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 2.0f);
    decaySlider.setValue(0.8f);
    addAndMakeVisible(&decaySlider);
    
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.1f, 1.0f);
    sustainSlider.setValue(0.8f);
    addAndMakeVisible(&sustainSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(1.0f, 5.0f);
    releaseSlider.setValue(0.8f);
    addAndMakeVisible(&releaseSlider);
    
    //    Linking the slider with the processor, on the parameter value "attack"
    attackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"attack",attackSlider);
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"release",releaseSlider);
    decayTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"decay",decaySlider);
    sustainTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"sustain",sustainSlider);

}

Envelope::~Envelope()
{
//    setLookAndFeel (nullptr);
}

void Envelope::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10,getWidth(),25);
    auto bckgrnd = Colour();
    g.fillAll (bckgrnd);   // clear the background

    g.setColour(Colours::white);
    g.drawText("ADSR",titleArea, Justification::centredTop);
    
    g.drawText("A",53,150,20,20,Justification::centredTop);
    g.drawText("D",77,150,20,20,Justification::centredTop);
    g.drawText("S",103,150,20,20,Justification::centredTop);
    g.drawText("R",128,150,20,20,Justification::centredTop);
    
    Rectangle<float> area (25,25,150,150);
    auto colour = Colour(84, 109, 229);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void Envelope::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
    int sliderWidth = 25;
    int sliderHeight = 175;
    
    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(5));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(5));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(5));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(5));

}
