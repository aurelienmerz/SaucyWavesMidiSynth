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
    void initDspOsc(dsp::ProcessSpec spec)
    {
        dspOsc1.prepare(spec);
    }
    void resetDspOsc()
    {
        dspOsc1.reset();
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
    void getMasterGainParams(float* mGain, float* pbup, float* pbdn)
    {
        masterGain = *mGain;
        pitchBendUpSemitones = *pbup;
        pitchBendDownSemitones = *pbdn;
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
        noteNumber = midiNoteNumber;
        setPitchBend(currentPitchWheelPosition);
        frequency = noteInHertz(noteNumber, pitchBendCents());
        level = velocity;
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
    void setPitchBend(int pitchWheelPos)
    {
        if (pitchWheelPos > 8192)
        {
            // shifting up
            pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
        }
        else
        {
            // shifting down
            pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
        }
    }
    
    float pitchBendCents()
    {
        if (pitchBend >= 0.0f)
        {
            // shifting up
            return pitchBend * pitchBendUpSemitones * 100;
        }
        else
        {
            // shifting down
            return pitchBend * pitchBendDownSemitones * 100;
        }
    }
    
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        setPitchBend(newPitchWheelValue);
        frequency = noteInHertz(noteNumber, pitchBendCents());
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
                outputBuffer.addSample(channel, startSample,adsr.getNextSample() * setOscType() * masterGain);
                tailOff *= 0.99;
            }
            ++startSample;
        }
    }
    
private:
    float level = 0.0;
    float frequency = 0.0;
    double tailOff = 0.0;
    
    dsp::Oscillator<float> dspOsc1;

    int waveSelect;
    int filterChoice;
    float cutOff;
    float resonance;
    maxiOsc osc1;
    ADSR adsr;
    ADSR::Parameters adsrParams;
    
    float masterGain;
    int noteNumber;
    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;
    
    
};
