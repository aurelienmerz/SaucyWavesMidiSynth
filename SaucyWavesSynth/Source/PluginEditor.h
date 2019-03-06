/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SaucyWavesSynthAudioProcessorEditor  : public AudioProcessorEditor,
private MidiInputCallback,
private MidiKeyboardStateListener,
public Slider::Listener
{
public:
    SaucyWavesSynthAudioProcessorEditor (SaucyWavesSynthAudioProcessor&);
    ~SaucyWavesSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SaucyWavesSynthAudioProcessor& processor;
    MidiKeyboardState keyboardState;            // [5]
    MidiKeyboardComponent keyboardComponent;    // [6]
    TextEditor midiMessagesBox;
    
    Slider attackSlider;
    AudioProcessorValueTreeState::SliderAttachment* sliderTree;

    
    void logMessage (const String& m)
    {
        midiMessagesBox.moveCaretToEnd();
        midiMessagesBox.insertTextAtCaret (m + newLine);
    }
    
    /** Starts listening to a MIDI input device, enabling it if necessary. */
    void setMidiInput (int index)
    {

    }
    
    // These methods handle callbacks from the midi device + on-screen keyboard..
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override
    {
//        const ScopedValueSetter<bool> scopedInputFlag (isAddingFromMidiInput, true);
        keyboardState.processNextMidiEvent (message);
    }
    
    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override
    {
//        if (! isAddingFromMidiInput)
//        {
//            auto m = MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity);
//            m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
//        }
    }
    
    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override
    {
//        if (! isAddingFromMidiInput)
//        {
//            auto m = MidiMessage::noteOff (midiChannel, midiNoteNumber);
//            m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
//        }
    }

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaucyWavesSynthAudioProcessorEditor)
};
