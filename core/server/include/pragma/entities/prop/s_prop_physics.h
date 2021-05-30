/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan */

#ifndef __S_PROP_PHYSICS_H__
#define __S_PROP_PHYSICS_H__

#include "pragma/serverdefinitions.h"
#include <pragma/entities/prop/prop_physics.hpp>

namespace pragma
{
	class DLLSERVER SPropPhysicsComponent final
		: public BasePropPhysicsComponent
	{
	public:
		SPropPhysicsComponent(BaseEntity &ent) : BasePropPhysicsComponent(ent) {}
		virtual luabind::object InitializeLuaObject(lua_State *l) override;
	};
};

class DLLSERVER PropPhysics
	: public SBaseEntity
{
public:
	virtual void Initialize() override;
};

#endif