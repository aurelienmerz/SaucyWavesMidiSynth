/*
  ==============================================================================

    Oscillator.cpp
    Created: 29 Mar 2019 10:56:50pm
    Author:  Aurélien Merz

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SaucyWavesSynthAudioProcessor& p):
processor(p)
{
    setSize(200, 200);
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
    
    waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree,"wavetype", oscMenu);
    
    oscMenu.setJustificationType(Justification::centred);
    

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10, getWidth(),25);
    auto bckgrnd = Colour();
    g.fillAll (bckgrnd);   // clear the background
    g.setColour(Colours::white);
    g.drawText("OSC", titleArea, Justification::centredTop);
    
    Rectangle<float> area (25,25,150,150);
//    auto colour = Colour(84, 109, 229);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(area,20.0f, 3.0f);

}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(ComboBox * box)
{
    
}
