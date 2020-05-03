/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2020 Florian Weischer
 */

#include "stdafx_client.h"
#include "pragma/rendering/shaders/world/water/c_shader_water_surface_solve_edges.hpp"
#include <misc/compute_pipeline_create_info.h>

using namespace pragma;

ShaderWaterSurfaceSolveEdges::ShaderWaterSurfaceSolveEdges(prosper::IPrContext &context,const std::string &identifier)
	: ShaderWaterSurfaceSumEdges(context,identifier,"compute/water/cs_water_surface_solve_edges")
{}
