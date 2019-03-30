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
        attackSlider.setRange(0.1f, 5000.0f);
        attackSlider.setValue(0.1f);
//        attackSlider.addListener(this);
        addAndMakeVisible(&attackSlider);
    
        releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        releaseSlider.setRange(0.1f, 5000.0f);
        releaseSlider.setValue(0.1f);
//        releaseSlider.addListener(this);
        addAndMakeVisible(&releaseSlider);
    
        sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        sustainSlider.setRange(0.1f, 5000.0f);
        sustainSlider.setValue(0.1f);
//        sustainSlider.addListener(this);
        addAndMakeVisible(&sustainSlider);
    
        decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        decaySlider.setRange(0.1f, 5000.0f);
        decaySlider.setValue(0.1f);
//        decaySlider.addListener(this);
        addAndMakeVisible(&decaySlider);
    
    //    Linking the slider with the processor, on the parameter value "attack"
        attackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"attack",attackSlider);
        releaseTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"release",releaseSlider);
        decayTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"decay",decaySlider);
        sustainTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"sustain",sustainSlider);

}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10,getWidth(),20);
    g.fillAll (Colours::black);   // clear the background
    g.setColour(Colours::white);
    g.drawText("Filter",titleArea, Justification::centredTop);
    
    g.drawText("A",53,150,20,20,Justification::centredTop);
    g.drawText("D",77,150,20,20,Justification::centredTop);
    g.drawText("S",103,150,20,20,Justification::centredTop);
    g.drawText("R",128,150,20,20,Justification::centredTop);
    
    Rectangle<float> area (25,25,150,150);
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
    int sliderWidth = 25;
    int sliderHeight = 175;
    
    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));

}

//void Envelope::sliderValueChanged(Slider *slider)
//{
//    if(slider == &attackSlider)
//    {
//        processor.attackTime = slider->getValue();
//    }
//    if(slider == &releaseSlider)
//    {
//        processor.releaseTime = slider->getValue();
//    }
//    if(slider == &decaySlider)
//    {
//        processor.decayTime = slider->getValue();
//    }
//    if(slider == &sustainSlider)
//    {
//        processor.sustainTime = slider->getValue();
//    }
//
//}
