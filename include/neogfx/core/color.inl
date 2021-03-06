// color.inl
/*
  neogfx C++ App/Game Engine
  Copyright (c) 2015, 2020 Leigh Johnston.  All Rights Reserved.
  
  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <neogfx/neogfx.hpp>
#include <neolib/core/string_utils.hpp>
#include <neogfx/core/color.hpp>

namespace neogfx
{
    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::from_hsl(double aHue, double aSaturation, double aLightness, double aAlpha)
    {
        return hsl_color{ aHue, aSaturation, aLightness, aAlpha }.to_rgb<basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>>();
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::from_hsv(double aHue, double aSaturation, double aValue, double aAlpha)
    {
        return hsv_color{ aHue, aSaturation, aValue, aAlpha }.to_rgb<basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>>();
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::argb basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::as_argb() const
    {
        return (red() << RedShift) | (green() << GreenShift) | (blue() << BlueShift) | (alpha() << AlphaShift);
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline hsl_color basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::to_hsl() const
    {
        return hsl_color{ *this };
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline hsv_color basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::to_hsv() const
    {
        return hsv_color{ *this };
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline double basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::intensity() const
    {
        return (red<double>() + green<double>() + blue<double>()) / 3.0;
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline bool basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::similar_intensity(const basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>& aOther, double aThreshold)
    {
        return std::abs(intensity() - aOther.intensity()) <= aThreshold;
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::mid(const basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>& aOther) const
    {
        return typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type{
            (self_type::template red<double>() + aOther.template red<double>()) / 2.0,
            (self_type::template green<double>() + aOther.template green<double>()) / 2.0,
            (self_type::template blue<double>() + aOther.template blue<double>()) / 2.0,
            (base_type::template alpha<double>() + aOther.template alpha<double>()) / 2.0 };
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline bool basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::light(double aThreshold) const
    {
        return to_hsl().lightness() >= aThreshold;
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline bool basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::dark(double aThreshold) const
    {
        return to_hsl().lightness() < aThreshold;
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type& basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::lighten(view_component aDelta)
    {
        *this += aDelta;
        return static_cast<return_type&>(*this);
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type& basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::darken(view_component aDelta)
    {
        *this -= aDelta;
        return static_cast<return_type&>(*this);
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::lighter(view_component aDelta) const
    {
        return_type ret(*this);
        ret += aDelta;
        return ret;
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::darker(view_component aDelta) const
    {
        return_type ret(*this);
        ret -= aDelta;
        return ret;
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::shade(view_component aDelta) const
    {
        if (light())
            return darker(aDelta);
        else
            return lighter(aDelta);
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::unshade(view_component aDelta) const
    {
        if (light())
            return lighter(aDelta);
        else
            return darker(aDelta);
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::monochrome() const
    {
        view_component i = static_cast<view_component>(intensity() * 255.0);
        return basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>(i, i, i, alpha());
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::same_lightness_as(const basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>& aOther) const
    {
        hsl_color temp = to_hsl();
        temp.set_lightness(aOther.to_hsl().lightness());
        return temp.to_rgb<basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>>();
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::with_lightness(double aLightness) const
    {
        hsl_color temp = to_hsl();
        temp.set_lightness(std::min(aLightness, 1.0));
        return temp.to_rgb<basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>>();
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::inverse() const
    {
        return basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>{ static_cast<view_component>(0xFF - red()), static_cast<view_component>(0xFF - green()), static_cast<view_component>(0xFF - blue()), alpha() };
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type& basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::operator+=(view_component aDelta)
    {
        view_component newRed = std::numeric_limits<view_component>::max() - red() < aDelta ? std::numeric_limits<view_component>::max() : red() + aDelta;
        view_component newGreen = std::numeric_limits<view_component>::max() - green() < aDelta ? std::numeric_limits<view_component>::max() : green() + aDelta;
        view_component newBlue = std::numeric_limits<view_component>::max() - blue() < aDelta ? std::numeric_limits<view_component>::max() : blue() + aDelta;
        *this = basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>{ newRed, newGreen, newBlue, alpha() };
        return static_cast<return_type&>(*this);
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type& basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::operator-=(view_component aDelta)
    {
        view_component newRed = red() < aDelta ? std::numeric_limits<view_component>::min() : red() - aDelta;
        view_component newGreen = green() < aDelta ? std::numeric_limits<view_component>::min() : green() - aDelta;
        view_component newBlue = blue() < aDelta ? std::numeric_limits<view_component>::min() : blue() - aDelta;
        *this = basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>{ newRed, newGreen, newBlue, alpha() };
        return static_cast<return_type&>(*this);
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::operator~() const
    {
        return basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>{ static_cast<view_component>(~red() & 0xFF), static_cast<view_component>(~green() & 0xFF), static_cast<view_component>(~blue() & 0xFF), alpha() };
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline bool basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::operator<(const basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>& aOther) const
    {
        hsv_color left = to_hsv();
        hsv_color right = aOther.to_hsv();
        return std::make_tuple(left.hue(), left.saturation(), left.value()) < std::make_tuple(right.hue(), right.saturation(), right.value());
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline std::string basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::to_string() const
    {
        std::ostringstream result;
        result << "rgba(" << static_cast<int>(red()) << ", " << static_cast<int>(green()) << ", " << static_cast<int>(blue()) << ", " << alpha() / 255.0 << ");";
        return result.str();
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline std::string basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::to_hex_string() const
    {
        std::ostringstream result;
        result << "#" << std::uppercase << std::hex << std::setfill('0') << std::setw(6) << with_alpha(0).as_argb();
        if (alpha() != 0xFF)
            result << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(alpha());
        return result.str();
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type operator+(const basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>& aLeft, typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::view_component aRight)
    {
        typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type result{ aLeft };
        result += aRight;
        return result;
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type operator-(const basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>& aLeft, typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::view_component aRight)
    {
        typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type result{ aLeft };
        result -= aRight;
        return result;
    }

    template <color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type operator*(const basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>& aLeft, scalar aCoefficient)
    {
        typename basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>::return_type result{ aLeft };
        result *= vec4 { aCoefficient, aCoefficient, aCoefficient, aCoefficient };
        return result;
    }

    template <typename Elem, typename Traits, color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& aStream, const basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>& aColor)
    {
        aStream << std::setprecision(4) << "[" << aColor.red<double>() << ", " << aColor.green<double>() << ", " << aColor.blue<double>() << ", " << aColor.alpha<double>() << "]";
        return aStream;
    }

    template <typename Elem, typename Traits, color_space ColorSpace, typename BaseComponent, typename ViewComponent, typename Derived>
    inline std::basic_istream<Elem, Traits>& operator>>(std::basic_istream<Elem, Traits>& aStream, basic_rgb_color<ColorSpace, BaseComponent, ViewComponent, Derived>& aColor)
    {
        auto previousImbued = aStream.getloc();
        if (typeid(std::use_facet<std::ctype<char>>(previousImbued)) != typeid(neolib::comma_as_whitespace))
            aStream.imbue(std::locale{ previousImbued, new neolib::comma_as_whitespace{} });
        char ignore;
        aStream >> ignore >> aColor[0] >> aColor[1] >> aColor[2] >> aColor[3] >> ignore;
        aStream.imbue(previousImbued);
        return aStream;
    }

    template <typename Elem, typename Traits>
    inline std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& aStream, const gradient& aGradient)
    {
        aStream << std::setprecision(4) << "[";
        aStream << "(";
        for (auto const& stop : aGradient.color_stops())
            aStream << (&stop != &aGradient.color_stops()[0] ? ", " : "") << stop.first << ", " << stop.second;
        aStream << ")";
        aStream << ", (";
        for (auto const& stop : aGradient.alpha_stops())
            aStream << (&stop != &aGradient.alpha_stops()[0] ? ", " : "") << stop.first << ", " << stop.second * 1.0 / std::numeric_limits<sRGB_color::view_component>::max();
        aStream << ")";
        aStream << ", " << enum_to_string(aGradient.direction());
        if (std::holds_alternative<scalar>(aGradient.orientation()))
            aStream << ", " << std::get<scalar>(aGradient.orientation());
        else
            aStream << ", " << enum_to_string(std::get<corner>(aGradient.orientation()));
        aStream << ", " << enum_to_string(aGradient.shape());
        aStream << ", " << enum_to_string(aGradient.size());
        aStream << ", (";
        if (aGradient.exponents())
            aStream << aGradient.exponents()->x << ", " << aGradient.exponents()->y;
        aStream << ")";
        aStream << ", (";
        if (aGradient.center())
            aStream << aGradient.center()->x << ", " << aGradient.center()->y;
        aStream << ")";
        aStream << ", " << aGradient.smoothness();
        aStream << "]";
        return aStream;
    }

    template <typename Elem, typename Traits>
    inline std::basic_istream<Elem, Traits>& operator>>(std::basic_istream<Elem, Traits>& aStream, gradient& aGradient)
    {
        auto previousImbued = aStream.getloc();
        if (typeid(std::use_facet<std::ctype<char>>(previousImbued)) != typeid(neolib::comma_as_whitespace))
            aStream.imbue(std::locale{ previousImbued, new neolib::comma_as_whitespace{} });
        char ignore;
        std::string tempString;
        scalar tempScalar;
        aStream >> ignore >> ignore;
        gradient::color_stop_list colorStops;
        while (aStream)
        {
            gradient::color_stop colorStop;
            aStream >> colorStop.first >> colorStop.second;
            if (aStream)
                colorStops.push_back(colorStop);
        }
        aStream.clear();
        aStream >> ignore >> ignore;
        gradient::alpha_stop_list alphaStops;
        while (aStream)
        {
            gradient::alpha_stop alphaStop;
            aStream >> alphaStop.first >> tempScalar;
            alphaStop.second = static_cast<sRGB_color::view_component>(tempScalar * std::numeric_limits<sRGB_color::view_component>::max());
            if (aStream)
                alphaStops.push_back(alphaStop);
        }
        aStream.clear();
        aStream >> ignore;
        gradient_direction direction;
        aStream >> tempString;
        direction = neolib::string_to_enum<gradient_direction>(tempString);
        gradient::orientation_type orientation;
        if (aStream >> tempScalar)
        {
            orientation = tempScalar;
        }
        else
        {
            aStream.clear();
            aStream >> tempString;
            orientation = neolib::string_to_enum<corner>(tempString);
        }
        gradient_shape shape;
        aStream >> tempString;
        shape = neolib::string_to_enum<gradient_shape>(tempString);
        gradient_size size;
        aStream >> tempString;
        size = neolib::string_to_enum<gradient_size>(tempString);
        aStream >> ignore;
        optional_vec2 exponents;
        if (aStream >> tempScalar)
        {
            scalar y;
            aStream >> y;
            exponents.emplace(tempScalar, y);
        }
        else
            aStream.clear();
        aStream >> ignore;
        aStream >> ignore;
        optional_point center;
        if (aStream >> tempScalar)
        {
            scalar y;
            aStream >> y;
            center.emplace(tempScalar, y);
        }
        else
            aStream.clear();
        aStream >> ignore;
        scalar smoothness;
        aStream >> smoothness;
        aStream >> ignore;
        aGradient = gradient{ colorStops, alphaStops, direction };
        aGradient.set_orientation(orientation);
        aGradient.set_shape(shape);
        aGradient.set_size(size);
        aGradient.set_exponents(exponents);
        aGradient.set_center(center);
        aGradient.set_smoothness(smoothness);
        aStream.imbue(previousImbued);
        return aStream;
    }
}
