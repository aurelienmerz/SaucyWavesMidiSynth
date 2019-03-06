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
    
    void getParam(float* attack)
    {
        env1.setAttack(double(*attack));
    }
    
    //=========================================
    
    void startNote( int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity * 0.15;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << midiNoteNumber << std::endl;
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
        
        env1.setDecay(500);
        env1.setSustain(0.8);
        env1.setRelease(2000);
        
        for(int sample = 0; sample < numSamples ; ++sample)
        {
            double theWave = osc1.sinewave(frequency);
            double theSound = env1.adsr(theWave,env1.trigger) * level;
            double filteredSound = filter1.lores(theSound,100,0.1);
            
            for(int channel = 0; channel < outputBuffer.getNumChannels();++channel)
            {
                outputBuffer.addSample(channel, startSample,theSound);
                tailOff *= 0.99;
            }
            ++startSample;
        }
        
    }
private:
    float level = 0.0;
    float frequency = 0.0;
    double tailOff = 0.0;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
    
    
};