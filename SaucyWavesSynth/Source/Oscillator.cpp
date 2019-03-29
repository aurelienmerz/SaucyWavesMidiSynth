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

}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(ComboBox * box)
{
    
}
