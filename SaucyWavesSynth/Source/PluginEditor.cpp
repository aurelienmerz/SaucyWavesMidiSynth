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
    : AudioProcessorEditor (&p), processor (p), oscGUI(p),envGUI(p),filterGUI(p),
keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    setSize (600, 200);
    setLookAndFeel(&filterGUI);
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::white);
    getLookAndFeel().setColour(Slider::trackColourId, Colours::white);
    
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
    addAndMakeVisible (keyboardComponent);
    keyboardState.addListener (this);
}

SaucyWavesSynthAudioProcessorEditor::~SaucyWavesSynthAudioProcessorEditor()
{
    keyboardState.removeListener (this);
    setLookAndFeel (nullptr);
}

//==============================================================================
void SaucyWavesSynthAudioProcessorEditor::paint (Graphics& g)
{
    auto colour1 = Colour(92,37,141);
    auto colour2 = Colour(67,137,162);
    auto gradient = ColourGradient(colour1, 0, 0, colour2, 600, 300, false);
    g.setGradientFill(gradient);
    g.fillAll();

}

void SaucyWavesSynthAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
}


