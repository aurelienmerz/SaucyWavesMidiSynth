/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SaucyWavesSynthAudioProcessor::SaucyWavesSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
attackTime(0.1f),
tree(*this,nullptr, "PARAMETERS",
{    
    std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float> (0.1f, 5.0f),0.1f),
    std::make_unique<AudioParameterFloat>("release", "Release",NormalisableRange<float> (0.1f, 5.0f),0.1f),
    std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float> (0.1f, 2.0f),0.8f),
    std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float> (0.1f, 5.0f), 0.8f),
    std::make_unique<AudioParameterFloat>("wavetype", "WaveType", NormalisableRange<float> (0,2),0.0f),
    std::make_unique<AudioParameterFloat>("filterCutOff", "FilterCutOff", NormalisableRange<float> (20.0f,10000.0f),0.0f),
    std::make_unique<AudioParameterFloat>("filterRes", "FilterRes", NormalisableRange<float> (1.0f,5.0f),0.0f),
    std::make_unique<AudioParameterFloat>("filterType", "FilerType", NormalisableRange<float> (0,2),0.0f),
    std::make_unique<AudioParameterFloat>("mastergain", "MasterGain", NormalisableRange<float>(0.0f, 1.0f), 0.7f),
    std::make_unique<AudioParameterFloat>("pbup", "PBup", NormalisableRange<float>(1.0f, 12.0f), 2.0f),
    std::make_unique<AudioParameterFloat>("pbdown", "PBdown", NormalisableRange<float>(1.0f, 12.0f), 2.0f),
})
{
    tree.state = ValueTree("Synth");
    
    mySynth.clearVoices();
    
    for (auto i = 0; i < 4; ++i) 
        mySynth.addVoice (new SynthVoice());
    
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
    
}

SaucyWavesSynthAudioProcessor::~SaucyWavesSynthAudioProcessor()
{
}

//==============================================================================
const String SaucyWavesSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SaucyWavesSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SaucyWavesSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SaucyWavesSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SaucyWavesSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SaucyWavesSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SaucyWavesSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SaucyWavesSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String SaucyWavesSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SaucyWavesSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SaucyWavesSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getMainBusNumOutputChannels();
    
    stateVariableFilter.reset();
    stateVariableFilter.prepare(spec);
    updateFilter();
}

void SaucyWavesSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void SaucyWavesSynthAudioProcessor::updateFilter()
{
    int menuChoice = (*tree.getRawParameterValue("filterType"));
    int cutoff = (*tree.getRawParameterValue("filterCutOff"));
    int res = (*tree.getRawParameterValue("filterRes"));

    if (menuChoice == 0)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff,res);
    }
    if (menuChoice == 1)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff,res);
    }
    if (menuChoice == 2)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff,res);
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SaucyWavesSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SaucyWavesSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (int i=0; i < mySynth.getNumVoices();i++)
    {
        if((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->setADSRSampleRate(lastSampleRate);
            myVoice->getEnvelopeParam(tree.getRawParameterValue("attack"),
                              tree.getRawParameterValue("decay"),
                              tree.getRawParameterValue("sustain"),
                              tree.getRawParameterValue("release"));
            
            myVoice->getOscType(tree.getRawParameterValue("wavetype"));
            
            myVoice->getFilterParam(tree.getRawParameterValue("filterType"),
                                    tree.getRawParameterValue("filterCutOff"),
                                    tree.getRawParameterValue("filterRes"));
            
            myVoice->getMasterGainParams(tree.getRawParameterValue("mastergain"),
                                    tree.getRawParameterValue("pbup"),
                                    tree.getRawParameterValue("pbdown"));
            
        }
    }
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages,0,buffer.getNumSamples());
    updateFilter();
    dsp::AudioBlock<float> block (buffer);
    stateVariableFilter.process(dsp::ProcessContextReplacing<float>(block)); // Replacing the values to the output
    

    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
//        buffer.clear (i, 0, buffer.getNumSamples());
//        mySynth.renderNextBlock(buffer, midiMessages,0,buffer.getNumSamples());
    }
    

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool SaucyWavesSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SaucyWavesSynthAudioProcessor::createEditor()
{
    return new SaucyWavesSynthAudioProcessorEditor (*this);
}

//==============================================================================
void SaucyWavesSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto state = tree.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void SaucyWavesSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (tree.state.getType()))
            tree.replaceState (ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SaucyWavesSynthAudioProcessor();
}
