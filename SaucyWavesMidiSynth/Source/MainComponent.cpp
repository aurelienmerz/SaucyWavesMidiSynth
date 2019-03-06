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
    
    addAndMakeVisible(attackSlider);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue ((double) 0.1f);
//  attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 20.0);
    attackSlider.addListener(this);
////    synthAudioSource.attackSlider.onValueChange = [this] { synthAudioSource.a = (float) synthAudioSource.attackSlider.getValue(); };
//    


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
//    auto cyclesPerSample = frequencySlider.getValue() / currentSampleRate;
//    angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto sliderLeft = 150;
    auto gap = 30;
    auto attackPos = 150;
    auto decayPos = attackPos - gap;
    auto sustainPos = decayPos - gap;
    auto releasePos = sustainPos - gap;

    attackSlider.setBounds(getWidth()-attackPos,sliderLeft,30,120);
//    decaySlider.setBounds(getWidth()-decayPos,sliderLeft,30,120);
//    sustainSlider.setBounds(getWidth()-sustainPos,sliderLeft,30,120);
//    releaseSlider.setBounds(getWidth()-releasePos,sliderLeft,30,120);
    
    auto area = getLocalBounds();
    
//    midiInputList    .setBounds (area.removeFromTop (36).removeFromRight (getWidth() - 150).reduced (8));
    keyboardComponent.setBounds (area.removeFromBottom(80)); //removeFromTop (80).reduced(8));
//    midiMessagesBox  .setBounds (area.reduced (8));
}


