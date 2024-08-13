#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct PanInfo : ModuleInfoBase {
    static constexpr std::string_view slug{"Pan"};
    static constexpr std::string_view description{"Panner"};
    static constexpr uint32_t width_hp = 4;
    static constexpr std::string_view svg_filename{"res/modules/Pan_artwork.svg"};
    static constexpr std::string_view png_filename{"4ms/fp/Pan.png"};

    using enum Coords;

    static constexpr std::array<Element, 5> Elements{{
		Knob9mm{{to_mm<72>(28.8), to_mm<72>(46.77), Center, "Pan", ""}, 0.5f},
		AnalogJackInput4ms{{to_mm<72>(28.8), to_mm<72>(168.66), Center, "CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(28.8), to_mm<72>(216.85), Center, "Input", ""}},
		AnalogJackOutput4ms{{to_mm<72>(28.8), to_mm<72>(265.04), Center, "Out 1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(28.8), to_mm<72>(313.23), Center, "Out 2", ""}},
}};

    enum class Elem {
        PanKnob,
        CvIn,
        InputIn,
        Out1Out,
        Out2Out,
    };

    // Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)
    
    enum {
        KnobPan, 
        NumKnobs,
    };
    
    
    enum {
        InputCv, 
        InputInput, 
        NumInJacks,
    };
    
    enum {
        OutputOut_1, 
        OutputOut_2, 
        NumOutJacks,
    };
    
    
};
} // namespace MetaModule