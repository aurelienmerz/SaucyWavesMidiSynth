/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/**
*/
class SaucyWavesSynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SaucyWavesSynthAudioProcessor();
    ~SaucyWavesSynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void updateFilter();
    
    float attackTime;
    float releaseTime;
    float decayTime;
    float sustainTime;
    AudioProcessorValueTreeState tree; // List of objects contained within the AudioProcessor

private:
    
    Synthesiser mySynth;
    SynthVoice *myVoice;
    double lastSampleRate;
    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>,
                             dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaucyWavesSynthAudioProcessor)
};
