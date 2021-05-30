/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan
 */

#include "stdafx_client.h"
#include "pragma/entities/components/c_toggle_component.hpp"
#include "pragma/lua/c_lentity_handles.hpp"

using namespace pragma;

luabind::object CToggleComponent::InitializeLuaObject(lua_State *l) {return BaseEntityComponent::InitializeLuaObject<CToggleComponentHandleWrapper>(l);}
void CToggleComponent::ReceiveData(NetPacket &packet)
{
	SetTurnedOn(packet->Read<bool>());
}
Bool CToggleComponent::ReceiveNetEvent(UInt32 eventId,NetPacket &packet)
{
	if(eventId == m_netEvToggleState)
	{
		auto bState = packet->Read<bool>();
		if(bState)
			TurnOn();
		else
			TurnOff();
		return true;
	}
	return CBaseNetComponent::ReceiveNetEvent(eventId,packet);
}

