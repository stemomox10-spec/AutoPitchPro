#include "PluginProcessor.h"
#include "PluginEditor.h"

AutoPitchProAudioProcessorEditor::AutoPitchProAudioProcessorEditor (AutoPitchProAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setStyle(&customLookAndFeel);

    auto setupKnob = [this](juce::Slider& slider) {
        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 18);
        addAndMakeVisible(slider);
    };

    setupKnob(retuneSpeedSlider);
    setupKnob(flexTuneSlider);
    setupKnob(humanizeSlider);
    setupKnob(vibratoSlider);

    setSize (900, 560);
}

AutoPitchProAudioProcessorEditor::~AutoPitchProAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void AutoPitchProAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient bgGrad(juce::Colour(0xff22252a), 0, 0, juce::Colour(0xff0d0f12), 0, (float)getHeight(), false);
    g.setGradientFill(bgGrad);
    g.fillAll();

    g.setColour(juce::Colour(0xff16181c));
    g.fillRect(0, 0, getWidth(), 45);
    g.setColour(juce::Colour(0xff08090a));
    g.drawHorizontalLine(45, 0.0f, (float)getWidth());

    g.setColour(juce::Colours::lightgrey);
    g.setFont(13.0f);
    g.drawText("Antares", 15, 12, 60, 20, juce::Justification::left, true);
    g.setColour(juce::Colour(0xff00d4ff));
    g.setFont(juce::Font(14.0f, juce::Font::bold));
    g.drawText("AUTO-TUNE PRO", 80, 12, 140, 20, juce::Justification::left, true);

    auto centralArea = juce::Rectangle<float>(40, 60, (float)getWidth() - 80, 380);
    
    g.setColour(juce::Colours::black.withAlpha(0.6f));
    g.fillRoundedRectangle(centralArea.translated(0, 3), 8.0f);

    juce::ColourGradient panelGrad(juce::Colour(0xff1b1d22), centralArea.getX(), centralArea.getY(),
                                   juce::Colour(0xff111316), centralArea.getX(), centralArea.getBottom(), false);
    g.setGradientFill(panelGrad);
    g.fillRoundedRectangle(centralArea, 8.0f);
    g.setColour(juce::Colour(0xff2d3139));
    g.drawRoundedRectangle(centralArea, 8.0f, 1.5f);

    float cx = (float)getWidth() / 2.0f;
    float cy = 250.0f;
    float radius = 95.0f;

    g.setColour(juce::Colours::black.withAlpha(0.8f));
    g.fillEllipse(cx - radius, cy - radius + 4.0f, radius * 2.0f, radius * 2.0f);

    juce::ColourGradient dialGrad(juce::Colour(0xff0d0f12), cx, cy - radius,
                                  juce::Colour(0xff1a1d23), cx, cy + radius, false);
    g.setGradientFill(dialGrad);
    g.fillEllipse(cx - radius, cy - radius, radius * 2.0f, radius * 2.0f);

    g.setColour(juce::Colour(0xff00d4ff));
    g.drawEllipse(cx - radius, cy - radius, radius * 2.0f, radius * 2.0f, 3.0f);

    g.setColour(juce::Colour(0xff00d4ff));
    g.setFont(juce::Font(55.0f, juce::Font::bold));
    g.drawText("D", (int)(cx - radius), (int)(cy - radius), (int)(radius * 2.0f), (int)(radius * 2.0f), juce::Justification::center, true);

    float keyboardY = 450.0f;
    float keyboardH = 90.0f;
    g.setColour(juce::Colour(0xff0a0c0e));
    g.fillRect(30.0f, keyboardY, (float)getWidth() - 60.0f, keyboardH);

    float keyWidth = ((float)getWidth() - 80.0f) / 36.0f;
    for (int i = 0; i < 36; ++i)
    {
        float x = 40.0f + (i * keyWidth);
        g.setColour(juce::Colours::white);
        g.drawRect(x, keyboardY, keyWidth, keyboardH, 1);
    }
}

void AutoPitchProAudioProcessorEditor::resized()
{
    retuneSpeedSlider.setBounds(90, 140, 110, 120);
    flexTuneSlider.setBounds(90, 290, 110, 120);
    vibratoSlider.setBounds(getWidth() - 200, 140, 110, 120);
    humanizeSlider.setBounds(getWidth() - 200, 290, 110, 120);
}
