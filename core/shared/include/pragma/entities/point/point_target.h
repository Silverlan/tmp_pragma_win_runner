/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan */

#ifndef __POINT_TARGET_H__
#define __POINT_TARGET_H__

#include "pragma/entities/components/base_entity_component.hpp"

namespace pragma
{
	class DLLNETWORK BasePointTargetComponent
		: public BaseEntityComponent
	{
	public:
		using BaseEntityComponent::BaseEntityComponent;
	};
};

#endif
