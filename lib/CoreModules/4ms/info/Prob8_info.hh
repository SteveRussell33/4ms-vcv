#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct Prob8Info : ModuleInfoBase {
    static constexpr std::string_view slug{"Prob8"};
    static constexpr std::string_view description{"Probability Module"};
    static constexpr uint32_t width_hp = 8;
    static constexpr std::string_view svg_filename{"res/modules/Prob8_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Prob8.png"};

    using enum Coords;

    static constexpr std::array<Element, 12> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(32.75), to_mm<72>(47.1), Center, "1", ""}, 1.0f},
		Davies1900hBlackKnob{{to_mm<72>(84.28), to_mm<72>(47.1), Center, "2", ""}, 1.0f},
		Davies1900hBlackKnob{{to_mm<72>(32.75), to_mm<72>(104.19), Center, "3", ""}, 0.0f},
		Davies1900hBlackKnob{{to_mm<72>(84.28), to_mm<72>(104.19), Center, "4", ""}, 0.0f},
		Davies1900hBlackKnob{{to_mm<72>(32.75), to_mm<72>(163.5), Center, "5", ""}, 0.875f},
		Davies1900hBlackKnob{{to_mm<72>(84.28), to_mm<72>(163.5), Center, "6", ""}, 1.0f},
		Davies1900hBlackKnob{{to_mm<72>(32.75), to_mm<72>(222.27), Center, "7", ""}, 0.0f},
		Davies1900hBlackKnob{{to_mm<72>(84.28), to_mm<72>(222.27), Center, "8", ""}, 0.0f},
		AnalogJackInput4ms{{to_mm<72>(30.9), to_mm<72>(272.37), Center, "Clock", ""}},
		AnalogJackInput4ms{{to_mm<72>(84.57), to_mm<72>(272.37), Center, "Reset", ""}},
		AnalogJackOutput4ms{{to_mm<72>(30.9), to_mm<72>(314.05), Center, "Inv", ""}},
		AnalogJackOutput4ms{{to_mm<72>(84.57), to_mm<72>(314.05), Center, "Out", ""}},
}};

    enum class Elem {
        _1Knob,
        _2Knob,
        _3Knob,
        _4Knob,
        _5Knob,
        _6Knob,
        _7Knob,
        _8Knob,
        ClockIn,
        ResetIn,
        InvOut,
        Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        Knob_1, 
        Knob_2, 
        Knob_3, 
        Knob_4, 
        Knob_5, 
        Knob_6, 
        Knob_7, 
        Knob_8, 
        NumKnobs,
    };
    
    
    enum {
        InputClock, 
        InputReset, 
        NumInJacks,
    };
    
    enum {
        OutputInv, 
        OutputOut, 
        NumOutJacks,
    };
    
    
};
} // namespace MetaModule