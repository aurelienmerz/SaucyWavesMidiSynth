/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent():
keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard),
startTime (Time::getMillisecondCounterHiRes() * 0.001),
synthAudioSource(keyboardState)
{
    // Make sure you set the size of the component after
    // you add any child components.
    setOpaque (true);
    setSize (800, 600);
    setAudioChannels(0, 2); // no inputs, 2 output channels
    startTimer(400);
    
    //=========================================================================
    addAndMakeVisible (midiInputList);
    midiInputList.setTextWhenNoChoicesAvailable ("No MIDI Inputs Enabled");
    auto midiInputs = MidiInput::getDevices();
    midiInputList.addItemList (midiInputs, 1);
    midiInputList.onChange = [this] { setMidiInput (midiInputList.getSelectedItemIndex()); };
    // find the first enabled device and use that by default
    for (auto midiInput : midiInputs)
    {
        if (deviceManager.isMidiInputEnabled (midiInput))
        {
            setMidiInput (midiInputs.indexOf (midiInput));
            break;
        }
    }
    // if no enabled devices were found just use the first one in the list
    if (midiInputList.getSelectedId() == 0)
        setMidiInput (0);
    
    
    addAndMakeVisible (keyboardComponent);
    keyboardState.addListener (this);
    
//    addAndMakeVisible (midiMessagesBox);
    midiMessagesBox.setMultiLine (true);
    midiMessagesBox.setReturnKeyStartsNewLine (true);
    midiMessagesBox.setReadOnly (true);
    midiMessagesBox.setScrollbarsShown (true);
    midiMessagesBox.setCaretVisible (false);
    midiMessagesBox.setPopupMenuEnabled (true);
    midiMessagesBox.setColour (TextEditor::backgroundColourId, Colour (0x32ffffff));
    midiMessagesBox.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    midiMessagesBox.setColour (TextEditor::shadowColourId, Colour (0x16000000));
    
    //=========================================================================
////    addAndMakeVisible (frequencySlider);
//    frequencySlider.setRange (50, 5000.0);
//    frequencySlider.setSkewFactorFromMidPoint (500.0);
//    frequencySlider.setValue (currentFrequency, dontSendNotification);
//    frequencySlider.setTextValueSuffix ("Hz");
//    frequencySlider.setTextBoxStyle(Slider::TextBoxLeft, false, 160, frequencySlider.getTextBoxHeight());
//    frequencySlider.addListener(this);
//    frequencySlider.onValueChange = [this] { targetFrequency = frequencySlider.getValue(); };
//
////    addAndMakeVisible(levelSlider);
//    levelSlider.setRange(0.0, 0.125);
//    levelSlider.setValue ((double) currentLevel, dontSendNotification);
//    levelSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 160, frequencySlider.getTextBoxHeight());
//    levelSlider.addListener(this);
//    levelSlider.onValueChange = [this] { targetLevel = (float) levelSlider.getValue(); };
//
////    addAndMakeVisible (frequencyLabel);
//    frequencyLabel.setText ("Frequency", dontSendNotification);
//    frequencyLabel.attachToComponent (&frequencySlider, true);
//    addAndMakeVisible (levelLabel);
//    frequencyLabel.setText ("Level", dontSendNotification);
//    frequencyLabel.attachToComponent (&levelSlider, true);
//
    //=========================================================================
    
    addAndMakeVisible(synthAudioSource.attackSlider);
    synthAudioSource.attackSlider.setRange(0.0, 10);
    synthAudioSource.attackSlider.setValue ((double) synthAudioSource.currentAttackTime, dontSendNotification);
    synthAudioSource.attackSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 160, synthAudioSource.attackSlider.getTextBoxHeight());
    synthAudioSource.attackSlider.addListener(this);
    synthAudioSource.attackSlider.onValueChange = [this] { targetLevel = (float) synthAudioSource.attackSlider.getValue(); };
    
    addAndMakeVisible (synthAudioSource.attackLabel);
    synthAudioSource.attackLabel.setText ("Attack", dontSendNotification);
    synthAudioSource.attackLabel.attachToComponent (&synthAudioSource.attackSlider, true);
    
    addAndMakeVisible(synthAudioSource.releaseSlider);
    synthAudioSource.releaseSlider.setRange(1.0, 10);
    synthAudioSource.releaseSlider.setValue ((double) synthAudioSource.currentReleaseTime, dontSendNotification);
    synthAudioSource.releaseSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 160, synthAudioSource.releaseSlider.getTextBoxHeight());
    synthAudioSource.releaseSlider.addListener(this);
    synthAudioSource.releaseSlider.onValueChange = [this] { targetLevel = (float) synthAudioSource.releaseSlider.getValue(); };
    
    addAndMakeVisible (synthAudioSource.releaseLabel);
    synthAudioSource.releaseLabel.setText ("Release", dontSendNotification);
    synthAudioSource.releaseLabel.attachToComponent (&synthAudioSource.releaseSlider, true);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    keyboardState.removeListener (this);
    deviceManager.removeMidiInputCallback (MidiInput::getDevices()[midiInputList.getSelectedItemIndex()], this);
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    
    String message;
    currentSampleRate = sampleRate;
//    updateAngleDelta();
    synthAudioSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    message << "Preparing to play audio... " << newLine;
    message << "Sample per block expected: "<< samplesPerBlockExpected << newLine;
    message << "Sample rate: " << sampleRate << newLine;
    Logger::getCurrentLogger()->writeToLog(message);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
      synthAudioSource.getNextAudioBlock (bufferToFill);
//    auto level = (float) levelSlider.getValue();
//    auto* leftBuffer  = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
//    auto* rightBuffer = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
//    auto localTargetFrequency = targetFrequency;
//    if (localTargetFrequency != currentFrequency)                                                              // [7]
//    {
//        auto frequencyIncrement = (localTargetFrequency - currentFrequency) / bufferToFill.numSamples;         // [8]
//        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
//        {
//            auto currentSample = (float) std::sin (currentAngle);
//            currentFrequency += frequencyIncrement;                                                            // [9]
//            updateAngleDelta();                                                                                // [10]
//            currentAngle += angleDelta;
//            leftBuffer[sample]  = currentSample;
//            rightBuffer[sample] = currentSample;
//        }
//        currentFrequency = localTargetFrequency;
//    }
//    else                                                                                                       // [11]
//    {
//        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
//        {
//            auto currentSample = (float) std::sin (currentAngle);
//            currentAngle += angleDelta;
//            leftBuffer[sample]  = currentSample;
//            rightBuffer[sample] = currentSample;
//        }
//    }
    
//    auto localTargetLevel = targetLevel;
//    bufferToFill.buffer->applyGainRamp (bufferToFill.startSample, bufferToFill.numSamples, currentLevel, localTargetLevel);
//    currentLevel = localTargetLevel;

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    //bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.
    synthAudioSource.releaseResources();
    Logger::getCurrentLogger()->writeToLog ("Releasing audio resources");
    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}
void MainComponent::updateAngleDelta()
{
    auto cyclesPerSample = frequencySlider.getValue() / currentSampleRate;
    angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto sliderLeft = 120;
    synthAudioSource.attackSlider.setBounds (sliderLeft, 120, getWidth() - sliderLeft - 10, 20);
    synthAudioSource.releaseSlider.setBounds (sliderLeft, 140, getWidth() - sliderLeft - 10, 20);
    
    auto area = getLocalBounds();
    
    midiInputList    .setBounds (area.removeFromTop (36).removeFromRight (getWidth() - 150).reduced (8));
    keyboardComponent.setBounds (area.removeFromTop (80).reduced(8));
    midiMessagesBox  .setBounds (area.reduced (8));
}


