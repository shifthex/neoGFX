// mesh_filter.hpp
/*
neogfx C++ GUI Library
Copyright (c) 2018 Leigh Johnston.  All Rights Reserved.

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
#include <neolib/uuid.hpp>
#include <neolib/string.hpp>
#include <neogfx/core/colour.hpp>
#include <neogfx/game/ecs_ids.hpp>
#include <neogfx/game/component.hpp>
#include <neogfx/game/transformation.hpp>
#include <neogfx/game/colour.hpp>
#include <neogfx/game/texture.hpp>
#include <neogfx/game/mesh.hpp>

namespace neogfx::game
{
	struct mesh_filter
	{
		shared<mesh> sharedMesh;
		std::optional<mesh> mesh;
		std::optional<mat44> transformation;
		std::optional<colour> colour;
		std::optional<texture> texture;

		struct meta : i_component_data::meta
		{
			static const neolib::uuid& id()
			{
				static const neolib::uuid sId = { 0x4dc667e1, 0x9284, 0x4834, 0xb4eb, { 0xa5, 0x9c, 0x34, 0x34, 0xe, 0xef } };
				return sId;
			}
			static const neolib::i_string& name()
			{
				static const neolib::string sName = "Mesh Filter";
				return sName;
			}
			static uint32_t field_count()
			{
				return 3;
			}
			static component_data_field_type field_type(uint32_t aFieldIndex)
			{
				switch (aFieldIndex)
				{
				case 0:
					return component_data_field_type::ComponentData | component_data_field_type::Shared;
				case 1:
					return component_data_field_type::ComponentData | component_data_field_type::Optional;
				case 2:
					return component_data_field_type::Mat44 | component_data_field_type::Optional;
				case 3:
				case 4:
					return component_data_field_type::ComponentData | component_data_field_type::Optional;
				}
			}
			static neolib::uuid field_type_id(uint32_t aFieldIndex)
			{
				switch (aFieldIndex)
				{
				case 0:
				case 1:
					return mesh::meta::id();
				case 2:
					return neolib::uuid{};
				case 3:
					return colour::meta::id();
				case 4:
					return texture::meta::id();
				}
			}
			static const neolib::i_string& field_name(uint32_t aFieldIndex)
			{
				static const neolib::string sFieldNames[] =
				{
					"Shared Mesh",
					"Mesh",
					"Transformation",
					"Colours",
					"Textures"
				};
				return sFieldNames[aFieldIndex];
			}
		};
	};
}