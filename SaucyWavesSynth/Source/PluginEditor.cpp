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
    : AudioProcessorEditor (&p), processor (p),
keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
//    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);

    addAndMakeVisible (keyboardComponent);
    keyboardState.addListener (this);
    
//    Linking the slider with the processor, on the parameter value "attack"
    sliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree,"attack",attackSlider);
    
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
    attackSlider.setBounds(10, 10, 40, 100);
    keyboardComponent.setBounds (area.removeFromBottom(80));
}

void SaucyWavesSynthAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if(slider == &attackSlider)
    {
        processor.attackTime = slider->getValue();
    }
        
}
