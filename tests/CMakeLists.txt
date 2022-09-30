################################################################################
#  This file is part of ccp_planner.                                           #
#                                                                              #
#  Copyright (c) 2021-2022 clounar                                             #
#                                                                              #
# ccp_planner is free software: you can redistribute it and/or modify it       #
# under the terms of the GNU General Public License as published by the Free   #
# Software Foundation, either version 3 of the License, or (at your option)    #
# any later version.                                                           #
#                                                                              #
# ccp_planner is distributed in the hope that it will be useful, but WITHOUT   #
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        #
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for     #
# more details.                                                                #
#                                                                              #
# You should have received a copy of the GNU General Public License along with #
# ccp_planner. If not, see <https://www.gnu.org/licenses/>.                    #
################################################################################

cmake_minimum_required(VERSION 3.15)
include(FetchContent)
FetchContent_Declare(doctest
	GIT_REPOSITORY    https://github.com/doctest/doctest.git
	GIT_TAG           v2.4.9)
FetchContent_MakeAvailable(doctest)

################################################################################

add_executable(ccp_planner_test_set
	experiment.cc)

target_link_libraries(ccp_planner_test_set PRIVATE
	ccp_planner
	doctest::doctest_with_main)

################################################################################

add_test (run_all_test ccp_planner_test_set)
