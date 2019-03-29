/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SaucyWavesSynthAudioProcessorEditor::SaucyWavesSynthAudioProcessorEditor (SaucyWavesSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGUI(p),
keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);
    
    addAndMakeVisible(&oscGUI);
//    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
//    attackSlider.setRange(0.1f, 5000.0f);
//    attackSlider.setValue(0.1f);
//    attackSlider.addListener(this);
//    addAndMakeVisible(&attackSlider);
//
//    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
//    releaseSlider.setRange(0.1f, 5000.0f);
//    releaseSlider.setValue(0.1f);
//    releaseSlider.addListener(this);
//    addAndMakeVisible(&releaseSlider);
//
//    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
//    sustainSlider.setRange(0.1f, 5000.0f);
//    sustainSlider.setValue(0.1f);
//    sustainSlider.addListener(this);
//    addAndMakeVisible(&sustainSlider);
//
//    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
//    decaySlider.setRange(0.1f, 5000.0f);
//    decaySlider.setValue(0.1f);
//    decaySlider.addListener(this);
//    addAndMakeVisible(&decaySlider);
    
    

    addAndMakeVisible (keyboardComponent);
    keyboardState.addListener (this);
    
//    Linking the slider with the processor, on the parameter value "attack"
//    attackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"attack",attackSlider);
//    releaseTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"release",releaseSlider);
//    decayTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"decay",decaySlider);
//    sustainTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"sustain",sustainSlider);
    
}

SaucyWavesSynthAudioProcessorEditor::~SaucyWavesSynthAudioProcessorEditor()
{
    keyboardState.removeListener (this);
}

//==============================================================================
void SaucyWavesSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void SaucyWavesSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(200));
    
//    attackSlider.setBounds(10, 10, 40, 100);
//    decaySlider.setBounds(50, 10, 40, 100);
//    sustainSlider.setBounds(90, 10, 40, 100);
//    releaseSlider.setBounds(130, 10, 40, 100);
//    keyboardComponent.setBounds (area.removeFromBottom(80));
}

void SaucyWavesSynthAudioProcessorEditor::sliderValueChanged(Slider *slider)
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
