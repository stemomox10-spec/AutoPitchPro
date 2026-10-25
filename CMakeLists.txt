cmake_minimum_required(VERSION 3.22)
project(AutoPitchPro VERSION 1.0.0)

find_package(JUCE CONFIG REQUIRED)

juce_add_plugin(AutoPitchPro
    COMPANY_NAME "SteMomox"
    BUNDLE_ID com.stemomox.autopitchpro
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    PLUGIN_MANUFACTURER_CODE "Stmo"
    PLUGIN_CODE_CODE "Atpr"
    FORMATS VST3 Standalone
    PRODUCT_NAME "AutoPitchPro"
)

target_sources(AutoPitchPro PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

target_compile_definitions(AutoPitchPro PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(AutoPitchPro PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_basics
    juce::juce_graphics
    juce::juce_core
    PUBLIC juce::juce_recommended_config_flags
    PUBLIC juce::juce_recommended_warning_flags
)
