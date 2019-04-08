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
    : AudioProcessorEditor (&p), processor (p), oscGUI(p),envGUI(p),filterGUI(p),masterGUI(p),
keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    setSize (800, 400);
    setLookAndFeel(&filterGUI);
    setLookAndFeel(&masterGUI);
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::white);
    getLookAndFeel().setColour(Slider::trackColourId, Colours::white);
    
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
    addAndMakeVisible(&masterGUI);
    
    title.setText("SAUCY WAVES Version 1.0", NotificationType::dontSendNotification);
    font.setBold(true);
    title.setFont(font);
    title.setColour(1, Colours::white);
    addAndMakeVisible(title);
    
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
    const int componentHeight = 240;
    
    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight).withTrimmedTop(40));
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight).withTrimmedTop(40));
    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight).withTrimmedTop(40));
    masterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight).withTrimmedTop(40));
    title.setBounds(0, 0, 300, 25);
    
}


