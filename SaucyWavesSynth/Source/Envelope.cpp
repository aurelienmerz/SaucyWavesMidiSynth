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
        attackSlider.addListener(this);
        addAndMakeVisible(&attackSlider);
    
        releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        releaseSlider.setRange(0.1f, 5000.0f);
        releaseSlider.setValue(0.1f);
        releaseSlider.addListener(this);
        addAndMakeVisible(&releaseSlider);
    
        sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        sustainSlider.setRange(0.1f, 5000.0f);
        sustainSlider.setValue(0.1f);
        sustainSlider.addListener(this);
        addAndMakeVisible(&sustainSlider);
    
        decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        decaySlider.setRange(0.1f, 5000.0f);
        decaySlider.setValue(0.1f);
        decaySlider.addListener(this);
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
    g.fillAll (Colours::black);   // clear the background
}

void Envelope::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
        attackSlider.setBounds(10, 10, 40, 100);
        decaySlider.setBounds(50, 10, 40, 100);
        sustainSlider.setBounds(90, 10, 40, 100);
        releaseSlider.setBounds(130, 10, 40, 100);

}

void Envelope::sliderValueChanged(Slider *slider)
{
    if(slider == &attackSlider)
    {
        processor.attackTime = slider->getValue();
    }
    if(slider == &releaseSlider)
    {
        processor.releaseTime = slider->getValue();
    }
    if(slider == &decaySlider)
    {
        processor.decayTime = slider->getValue();
    }
    if(slider == &sustainSlider)
    {
        processor.sustainTime = slider->getValue();
    }
    
}
