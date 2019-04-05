# Saucy Waves Synth

## Getting Started
This guide assumes you have a machine equipped with XCode 10.1 or higher, Projucer from JUCE 5.4.3 or higher and the Maximilian framework https://github.com/micknoise/Maximilian.

## Installation
1.  Download repository on your machine,
2.  Open the SaucyWavesSynth.jucer file with the Projucer desktop app if not by default, 
3.  In the Projucer, add the Maximilian lib folder to the source folder under the File Explorer section. Then add the Maximilian lib path on your machine inside the "Header Search Paths" textbox under the Exporters/Debug section,  
4.  Click the save button next to the "Selected exporter" menu and your chosen IDE will open automatically.

# Overview

## What is Saucy Waves?
Saucy Waves is a polyphonic midi software synth plug-in. It has one oscillator playing at a time and can generate three different sound waves: Sine, Saw and Square. It has a filter section with two sliders controlling the cut-off and the resonance of the filter. The available filters are low-pass (default), high-pass and band-pass (disabled for now). The last section is the envelope with four sliders for the ADSR. 

## Who is it for?
Saucy Waves is designed for musicians, composers, producers, sound designers and artists looking to create new sounds to use in their compositions. 

## Plugin usage:
1.  Connect your midi controller to your computer via USB or Bluetooth (ROLI)
2.  Open your DAW of choice
3.  Open a midi track
4.  Open Saucy Waves as AU (MacOs) or VST
5.  Ready to record

## Development 
1.  IDE: Xcode 10.1
2.  Projucer
3.  Language: C++14
4.  Framework: JUCE 5.4
