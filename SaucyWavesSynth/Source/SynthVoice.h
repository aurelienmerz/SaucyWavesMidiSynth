/*
  ==============================================================================

    SynthVoice.h
    Created: 6 Mar 2019 3:53:33pm
    Author:  Aurélien Merz

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice: public SynthesiserVoice
{
public:
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<SynthesiserSound*>(sound) != nullptr;
    }
    //=========================================
    
    void getEnvelopeParam(float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(double(*attack));
        env1.setRelease(double(*release));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
    }
    
    double setEnvelope()
    {
        return (env1.adsr(setOscType(),env1.trigger) * level);
    }
    
    void getFilterParam(float* type, float* cutoff, float* res)
    {
        filterChoice = *type;
        cutOff = *cutoff;
        resonance = *res;
    }
    
    double setFilter()
    {
        if(filterChoice == 0)
        {
            return filter1.lores(setEnvelope(), cutOff, resonance);
        }
        if(filterChoice == 1)
        {
            return filter1.hires(setEnvelope(), cutOff, resonance);
        }
        if(filterChoice == 2)
        {
            return filter1.bandpass(setEnvelope(), cutOff, resonance);
        }
        else
        {
            return filter1.lores(setEnvelope(), cutOff, resonance);
        }
        
    }
    
    //=========================================
    
    void getOscType(float* selection)
    {
        waveSelect = *selection;
    }
    
    double setOscType()
    {
        if(waveSelect == 0){
            return osc1.sinewave(frequency);
        }

        if(waveSelect == 1){
            return osc1.saw(frequency);
        }

        if(waveSelect == 2){
            return osc1.square(frequency);
        }
        else
        {
            return osc1.sinewave(frequency);
        }
    }
    
    
    //=========================================
    
    void startNote( int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity * 0.15;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    //=========================================
    
    void stopNote(float velocity, bool allowTailoff)
    {
        env1.trigger = 0;
        allowTailoff = true;
        if(allowTailoff)
        {
            if(tailOff == 0)
            {
                tailOff = 1.0;
            }
            if(velocity == 0)
                clearCurrentNote();
        }
    }
    //=========================================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    //=========================================
    
    void controllerMoved(int controllerNumber, int newControllerValue)
    {
        
    }
    
    //=========================================
    
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        for(int sample = 0; sample < numSamples ; ++sample)
        {
            for(int channel = 0; channel < outputBuffer.getNumChannels();++channel)
            {
                outputBuffer.addSample(channel, startSample,setFilter());
                tailOff *= 0.99;
            }
            ++startSample;
        }
        
    }
private:
    float level = 0.0;
    float frequency = 0.0;
    double tailOff = 0.0;
    
    int waveSelect;
    
    int filterChoice;
    float cutOff;
    float resonance;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
    
    
};
