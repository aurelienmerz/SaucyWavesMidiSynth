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
    
    void setADSRSampleRate(double sampleRate)
    {
        adsr.setSampleRate(sampleRate);
    }
    /*! \brief Getting the parameters from the AudioProcessorValueTreeState for the envelope.
    *
    *  \param attack float pointer
    *  \param decay float pointer
    *  \param sustain float pointer
    *  \param release float pointer
    */
    void getEnvelopeParam(float* attack, float* decay, float* sustain, float* release)
    {
        adsrParams.attack = *attack;
        adsrParams.decay = *decay;
        adsrParams.sustain = *sustain;
        adsrParams.release = *release;
    }
    
    //=========================================
    /*! \brief Getting the parameters from the AudioProcessorValueTreeState for the filter.
     *
     *  \param type float pointer
     *  \param cutoff float pointer
     *  \param res float pointer
     */
    void getFilterParam(float* type, float* cutoff, float* res)
    {
        filterChoice = *type;
        cutOff = *cutoff;
        resonance = *res;
    }
        
    //=========================================
    /*! \brief Updates the state of the dsp::StateVariableFilter based
     *         selection from the ComboBox.
     *  \return void
     */
    void updateFilter()
    {
        if (filterChoice == 0)
        {
            stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
            stateVariableFilter.state->setCutOffFrequency(frequency, cutOff,resonance);
        }
        if (filterChoice == 1)
        {
            stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
            stateVariableFilter.state->setCutOffFrequency(frequency, cutOff,resonance);
        }
        if (filterChoice == 2)
        {
            stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
            stateVariableFilter.state->setCutOffFrequency(frequency, cutOff,resonance);
        }
    }
    
    //=========================================
    
    void getOscType(float* selection)
    {
        waveSelect = *selection;
    }
    
    //=========================================
    
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
    
    static double noteInHertz(int midiNoteNumber, double centOffset)
    {
        double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        hertz *= std::pow(2.0, centOffset / 1200);
        return hertz;
    }
    //=========================================
    
    void startNote( int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        adsr.noteOn();
        level = velocity * 0.15;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber); // Converting the keyboard note into frequency
    }
    //=========================================
    
    void stopNote(float velocity, bool allowTailoff)
    {
        adsr.noteOff();
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
    
    //=========================================
    /*! \brief Main function for processing audio data.
     *
     *  \param outputBuffer AudioBuffer<float>
     *  \param startSample int
     *  \param numSamples int
     */
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        adsr.setParameters(adsrParams);
        for(int sample = 0; sample < numSamples ; ++sample)
        {
            for(int channel = 0; channel < outputBuffer.getNumChannels();++channel)
            {
                outputBuffer.addSample(channel, startSample,adsr.getNextSample() * setOscType() * 0.3f);
                tailOff *= 0.99;
            }
            ++startSample;
        }
    }
    
private:
    float level = 0.0;
    float frequency = 0.0;
    double tailOff = 0.0;
    
    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>,
    dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;
    
    dsp::Oscillator<float> dspOsc1;

    int waveSelect;
    int filterChoice;
    float cutOff;
    float resonance;
    maxiOsc osc1;
    ADSR adsr;
    ADSR::Parameters adsrParams;
    
    
};
