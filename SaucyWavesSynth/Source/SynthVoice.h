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
    

    
    /*! \brief Getting the parameters from the AudioProcessorValueTreeState for the envelope.
    *
    *  \param attack float pointer
    *  \param decay float pointer
    *  \param sustain float pointer
    *  \param release float pointer
    */
    void getEnvelopeParam(float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(double(*attack));
        env1.setRelease(double(*release));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
    }
    
    //=========================================
    
    /*! \brief Sets the ADSR envelope.
     *  \return double
     */
    double setEnvelope()
    {
        return (env1.adsr(setOscType(),env1.trigger));
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
    /*! \brief Returns the type of filter based on the
     *         selection from the ComboBox.
     *  \return double
     */
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
    
    
    //=========================================
    
    void startNote( int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity * 0.15;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber); // Converting the keyboard note into frequency
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
    
    void initFilter()
    {
        dsp::ProcessSpec spec;
        spec.sampleRate = 44100;
        spec.maximumBlockSize = 512;
        spec.numChannels = 2;
        
        stateVariableFilter.reset();
        //    updateFilter();
        stateVariableFilter.prepare(spec);
    }
    
    //=========================================
    /*! \brief Main function for processing audio data.
     *
     *  \param outputBuffer AudioBuffer<float>
     *  \param startSample int
     *  \param numSamples int
     */
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        for(int sample = 0; sample < numSamples ; ++sample)
        {
            for(int channel = 0; channel < outputBuffer.getNumChannels();++channel)
            {
                outputBuffer.addSample(channel, startSample,setFilter() * 0.3f);
                tailOff *= 0.99;
            }
            ++startSample;
        }
//        dsp::AudioBlock<float> block (outputBuffer);
//        updateFilter();
//        stateVariableFilter.process(dsp::ProcessContextReplacing<float>(block));
        
    }
private:
    float level = 0.0;
    float frequency = 0.0;
    double tailOff = 0.0;
    
    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>,
    dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;
    
    int waveSelect;
    
    int filterChoice;
    float cutOff;
    float resonance;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
    
    
};
