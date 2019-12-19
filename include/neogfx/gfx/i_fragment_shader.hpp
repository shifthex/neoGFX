// i_fragment_shader.hpp
/*
  neogfx C++ GUI Library
  Copyright (c) 2019 Leigh Johnston.  All Rights Reserved.
  
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
#include <neogfx/core/colour.hpp>
#include <neogfx/gfx/primitives.hpp>
#include <neogfx/gfx/i_texture.hpp>
#include <neogfx/gfx/i_shader.hpp>

namespace neogfx
{
    class i_rendering_context;

    class i_fragment_shader : public i_shader
    {
        typedef i_fragment_shader self_type;
    public:
        typedef self_type abstract_type;
    };

    class i_gradient_shader : public i_fragment_shader
    {
        typedef i_gradient_shader self_type;
    public:
        typedef self_type abstract_type;
    public:
        virtual void clear_gradient() = 0;
        virtual void set_gradient(i_rendering_context& aContext, const gradient& aGradient, const rect& aBoundingBox) = 0; // todo: use abstract gradient and rect types when available
    };

    class i_texture_shader : public i_fragment_shader
    {
        typedef i_texture_shader self_type;
    public:
        typedef self_type abstract_type;
    public:
        virtual void clear_texture() = 0;
        virtual void set_texture(const i_texture& aTexture) = 0;
        virtual void set_effect(shader_effect aEffect) = 0;
    };
}