// async_task.cpp
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

#include <neogfx/neogfx.hpp>
#include <neogfx/app/i_basic_services.hpp>
#include <neogfx/core/async_task.hpp>

namespace neogfx
{
    async_task::async_task(neolib::i_thread& aThread, const std::string& aName) : 
        neolib::async_task{ aThread, aName }
    {
    }

    void async_task::run()
    {
        try
        {
            neolib::async_task::run();
        }
        catch (std::exception& e)
        {
            std::cerr << "neogfx::async_task::run: terminating with exception: " << e.what() << std::endl;
            service<i_basic_services>().display_error_dialog(name().empty() ? "Abnormal Program Termination" : "Abnormal Program Termination - " + name(), std::string("neogfx::async_task::run: terminating with exception: ") + e.what());
            throw;
        }
        catch (...)
        {
            std::cerr << "neogfx::async_task::run: terminating with unknown exception" << std::endl;
            service<i_basic_services>().display_error_dialog(name().empty() ? "Abnormal Program Termination" : "Abnormal Program Termination - " + name(), "neogfx::async_task::run: terminating with unknown exception");
            throw;
        }
    }
}