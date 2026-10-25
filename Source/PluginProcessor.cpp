#include "PluginProcessor.h"
#include "PluginEditor.h"

AutoPitchProAudioProcessor::AutoPitchProAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

AutoPitchProAudioProcessor::~AutoPitchProAudioProcessor() {}

const juce::String AutoPitchProAudioProcessor::getName() const { return JucePlugin_Name; }

bool AutoPitchProAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AutoPitchProAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AutoPitchProAudioProcessor::isMidiEffect() const {
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AutoPitchProAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int AutoPitchProAudioProcessor::getNumPrograms() { return 1; }

int AutoPitchProAudioProcessor::getCurrentProgram() { return 0; }

void AutoPitchProAudioProcessor::setCurrentProgram (int index) {}

const juce::String AutoPitchProAudioProcessor::getProgramName (int index) { return {}; }

void AutoPitchProAudioProcessor::changeProgramName (int index, const juce::String& newName) {}

void AutoPitchProAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {}

void AutoPitchProAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AutoPitchProAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AutoPitchProAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
}

bool AutoPitchProAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* AutoPitchProAudioProcessor::createEditor()
{
    return new AutoPitchProAudioProcessorEditor (*this);
}

void AutoPitchProAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {}

void AutoPitchProAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AutoPitchProAudioProcessor();
}
