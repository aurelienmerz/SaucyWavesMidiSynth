/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "maximilian.h"

//==============================================================================
struct SineWaveSound   : public SynthesiserSound
{
    SineWaveSound() {}
    
    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }
};

//==============================================================================
struct SineWaveVoice   : public SynthesiserVoice
{
    double m_attackTime = 0.0, m_release = 0.0, m_decay = 0.0, m_sustain = 0.0;
    
    SineWaveVoice() {}
    SineWaveVoice(double &attackTime)
    {
        m_attackTime = *(&attackTime);
    }
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        env1.trigger = 1;
        level = velocity * 0.15;
        
        frequency = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    }
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        env1.trigger = 0;
        
        allowTailOff = true;
        
        if (allowTailOff)
        {
            if (tailOff == 0)
            {
                tailOff = 1.0;
            }
            if(velocity == 0)
                clearCurrentNote();
        }
    }
    
    void pitchWheelMoved (int) override      {}
    void controllerMoved (int, int) override {}
    
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        std::cout << m_attackTime << std::endl;
        env1.setAttack(m_attackTime);
        env1.setDecay(m_decay);
        env1.setSustain(m_sustain);
        env1.setRelease(m_release);        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.saw(frequency);
            double theSound = env1.adsr(theWave,env1.trigger) * level;
//            double filteredSound = filter1.lores(theSound, 40,0.1);
            
            for(int channel = 0 ;channel < outputBuffer.getNumChannels();++channel)
            {
                outputBuffer.addSample(channel, sample, theSound);
                tailOff *= 0.99;
            }
        }
    }
    
private:
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
    double frequency = 0.0;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};

//==============================================================================
class SynthAudioSource   : public AudioSource
//                           public Slider::Listener
{
public:
    double m_attackTime;
    double &attackTime = m_attackTime;
    
    SynthAudioSource (MidiKeyboardState& keyState)
    : keyboardState (keyState)
    {
        for (auto i = 0; i < 4; ++i) // [1] We add some voices to our synthesiser. This number of voices added determines the polyphony of the synthesiser.
            synth.addVoice (new SineWaveVoice(*(&attackTime)));
        
        synth.addSound (new SineWaveSound());       // [2] We add the sound so that the synthesiser knows which sounds it can play.
    }
    
    void setUsingSineWaveSound()
    {
        synth.clearSounds();
    }
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        synth.setCurrentPlaybackSampleRate (sampleRate); // [3] The synthesiser needs to know the sample rate of the audio output.
        midiCollector.reset(sampleRate);
    }
    
    void releaseResources() override {}
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        
//        std::cout << "attackTime " << attackTime << std::endl;
        bufferToFill.clearActiveBufferRegion();
        
        MidiBuffer incomingMidi;
        midiCollector.removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples); // [11]
        keyboardState.processNextMidiBuffer (incomingMidi, bufferToFill.startSample,
                                             bufferToFill.numSamples, true);       // [4]
        
        synth.renderNextBlock (*bufferToFill.buffer, incomingMidi,
                               bufferToFill.startSample, bufferToFill.numSamples); // [5]
    }
    
    MidiMessageCollector* getMidiCollector()
    {
        return &midiCollector;
    }
    
private:
    
    MidiKeyboardState& keyboardState;
    Synthesiser synth;
    MidiMessageCollector midiCollector;
};


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Slider::Listener,
                        private MidiInputCallback,
                        private MidiKeyboardStateListener,
                        private Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override
    {
//        std::cout << attackSlider.getValue() << std::endl;
        if (slider == &attackSlider){
            synthAudioSource.m_attackTime = attackSlider.getValue();
        }
    }
    void updateAngleDelta();

private:
    //==============================================================================
    AudioDeviceManager deviceManager;           // [1]
    ComboBox midiInputList;                     // [2]
    Label midiInputListLabel;
    int lastInputIndex = 0;                     // [3]
    bool isAddingFromMidiInput = false;         // [4]
    MidiKeyboardState keyboardState;            // [5]
    MidiKeyboardComponent keyboardComponent;    // [6]
    TextEditor midiMessagesBox;
    double startTime;
    SynthAudioSource synthAudioSource;
    Random random;
        
    Slider attackSlider;
//    Slider decaySlider;
//    Slider sustainSlider;
//    Slider releaseSlider;
    
    double currentSampleRate = 0.0, currentAngle = 0.0, angleDelta = 0.0;
    double currentFrequency = 500.0, targetFrequency = 500.0;
    float currentLevel = 0.1f, targetLevel = 0.1f;

    double currentAttackTime = 0.0, currentReleaseTime = 0.0;
    
    void timerCallback() override
    {
        keyboardComponent.grabKeyboardFocus();
        stopTimer();
    }
    
    static String getMidiMessageDescription (const MidiMessage& m)
    {
        if (m.isNoteOn())           return "Note on "          + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
        if (m.isNoteOff())          return "Note off "         + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
        if (m.isProgramChange())    return "Program change "   + String (m.getProgramChangeNumber());
        if (m.isPitchWheel())       return "Pitch wheel "      + String (m.getPitchWheelValue());
        if (m.isAftertouch())       return "After touch "      + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + String (m.getAfterTouchValue());
        if (m.isChannelPressure())  return "Channel pressure " + String (m.getChannelPressureValue());
        if (m.isAllNotesOff())      return "All notes off";
        if (m.isAllSoundOff())      return "All sound off";
        if (m.isMetaEvent())        return "Meta event";
        
        if (m.isController())
        {
            String name (MidiMessage::getControllerName (m.getControllerNumber()));
            
            if (name.isEmpty())
                name = "[" + String (m.getControllerNumber()) + "]";
            
            return "Controller " + name + ": " + String (m.getControllerValue());
        }
        
        return String::toHexString (m.getRawData(), m.getRawDataSize());
    }
    
    void logMessage (const String& m)
    {
        midiMessagesBox.moveCaretToEnd();
        midiMessagesBox.insertTextAtCaret (m + newLine);
    }
    
    /** Starts listening to a MIDI input device, enabling it if necessary. */
    void setMidiInput (int index)
    {
        auto list = MidiInput::getDevices();
        
        deviceManager.removeMidiInputCallback (list[lastInputIndex], synthAudioSource.getMidiCollector());
        
        auto newInput = list[index];
        
        if (! deviceManager.isMidiInputEnabled (newInput))
            deviceManager.setMidiInputEnabled (newInput, true);
        
        deviceManager.addMidiInputCallback (newInput, synthAudioSource.getMidiCollector());
        midiInputList.setSelectedId (index + 1, dontSendNotification);
        
        lastInputIndex = index;
    }
    
    // These methods handle callbacks from the midi device + on-screen keyboard..
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override
    {
        const ScopedValueSetter<bool> scopedInputFlag (isAddingFromMidiInput, true);
        keyboardState.processNextMidiEvent (message);
        postMessageToList (message, source->getName());
    }
    
    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override
    {
        if (! isAddingFromMidiInput)
        {
            auto m = MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity);
            m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
            postMessageToList (m, "On-Screen Keyboard");
        }
    }
    
    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override
    {
        if (! isAddingFromMidiInput)
        {
            auto m = MidiMessage::noteOff (midiChannel, midiNoteNumber);
            m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
            postMessageToList (m, "On-Screen Keyboard");
        }
    }
    
    // This is used to dispach an incoming message to the message thread
    class IncomingMessageCallback   : public CallbackMessage
    {
    public:
        IncomingMessageCallback (MainComponent* o, const MidiMessage& m, const String& s)
        : owner (o), message (m), source (s)
        {}
        
        void messageCallback() override
        {
            if (owner != nullptr)
                owner->addMessageToList (message, source);
        }
        
        Component::SafePointer<MainComponent> owner;
        MidiMessage message;
        String source;
    };
    
    void postMessageToList (const MidiMessage& message, const String& source)
    {
        (new IncomingMessageCallback (this, message, source))->post();
    }
    
    void addMessageToList (const MidiMessage& message, const String& source)
    {
        auto time = message.getTimeStamp() - startTime;
        
        auto hours   = ((int) (time / 3600.0)) % 24;
        auto minutes = ((int) (time / 60.0)) % 60;
        auto seconds = ((int) time) % 60;
        auto millis  = ((int) (time * 1000.0)) % 1000;
        
        auto timecode = String::formatted ("%02d:%02d:%02d.%03d",
                                           hours,
                                           minutes,
                                           seconds,
                                           millis);
        
        auto description = getMidiMessageDescription (message);
        
        String midiMessageString (timecode + "  -  " + description + " (" + source + ")"); // [7]
        logMessage (midiMessageString);
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
