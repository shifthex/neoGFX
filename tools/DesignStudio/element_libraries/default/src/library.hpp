// library.hpp
/*
  neoGFX Design Studio
  Copyright(C) 2020 Leigh Johnston
  
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
#include <neolib/core/reference_counted.hpp>
#include <neolib/core/set.hpp>
#include <neolib/core/map.hpp>
#include <neolib/core/string.hpp>
#include <neolib/app/i_application.hpp>
#include <neolib/app/version.hpp>
#include <neogfx/tools/DesignStudio/i_element_library.hpp>

namespace neogfx::DesignStudio
{
    class default_element_library : public neolib::reference_counted<i_element_library>
    {
        // types
    public:
        typedef neolib::set<neolib::string> elements_t;
        // construction
    public:
        default_element_library(neolib::i_application& aApplication, const std::string& aPluginPath);
        // meta
    public:
        const elements_t& root_elements() const override;
        const elements_t& elements() const override;
        // factory
    public:
        void create_element(const neolib::i_string& aElementType, neolib::i_ref_ptr<i_element>& aResult) override;
        void create_element(i_element& aParent, const neolib::i_string& aElementType, neolib::i_ref_ptr<i_element>& aResult) override;
        // meta
    public:
        static const neolib::uuid& library_id() { static const neolib::uuid sId = neolib::make_uuid("9B9E93DF-DC52-406D-BDBE-07EC7758BB66"); return sId; }
        static const std::string& library_name() { static const std::string sName = "default"; return sName; }
        static const std::string& library_description() { static const std::string sDescription = "Default element library"; return sDescription; }
        static const neolib::version& library_version() { static const neolib::version sVersion = { 1, 0, 0, 0 }; return sVersion; }
        static const std::string& library_copyright() { static const std::string sCopyright = "Copyright (C) 2020 Leigh Johnston"; return sCopyright; };
        // state
    private:
        neolib::i_application& iApplication;
        std::string iPluginPath;
        elements_t iRootElements;
        elements_t iElements;
    };
}
