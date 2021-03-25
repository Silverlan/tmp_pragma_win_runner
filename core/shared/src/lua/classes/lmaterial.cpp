/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan
 */

#include "stdafx_shared.h"
#include "pragma/lua/classes/lmaterial.h"
#include "pragma/lua/libraries/lfile.h"
#include "luasystem.h"
#include "material.h"
#include <detail_mode.hpp>
#include <sharedutils/alpha_mode.hpp>
#include <sharedutils/util_shaderinfo.hpp>
#include <udm.hpp>

void Lua::Material::register_class(luabind::class_<::Material> &classDef)
{
	classDef.add_static_constant("ALPHA_MODE_OPAQUE",umath::to_integral(::AlphaMode::Opaque));
	classDef.add_static_constant("ALPHA_MODE_MASK",umath::to_integral(::AlphaMode::Mask));
	classDef.add_static_constant("ALPHA_MODE_BLEND",umath::to_integral(::AlphaMode::Blend));
	classDef.add_static_constant("DETAIL_BLEND_MODE_DECAL_MODULATE",umath::to_integral(msys::DetailMode::DecalModulate));
	classDef.add_static_constant("DETAIL_BLEND_MODE_ADDITIVE",umath::to_integral(msys::DetailMode::Additive));
	classDef.add_static_constant("DETAIL_BLEND_MODE_TRANSLUCENT_DETAIL",umath::to_integral(msys::DetailMode::TranslucentDetail));
	classDef.add_static_constant("DETAIL_BLEND_MODE_BLEND_FACTOR_FADE",umath::to_integral(msys::DetailMode::BlendFactorFade));
	classDef.add_static_constant("DETAIL_BLEND_MODE_TRANSLUCENT_BASE",umath::to_integral(msys::DetailMode::TranslucentBase));
	classDef.add_static_constant("DETAIL_BLEND_MODE_UNLIT_ADDITIVE",umath::to_integral(msys::DetailMode::UnlitAdditive));
	classDef.add_static_constant("DETAIL_BLEND_MODE_UNLIT_ADDITIVE_THRESHOLD_FADE",umath::to_integral(msys::DetailMode::UnlitAdditiveThresholdFade));
	classDef.add_static_constant("DETAIL_BLEND_MODE_TWO_PATTERN_DECAL_MODULATE",umath::to_integral(msys::DetailMode::TwoPatternDecalModulate));
	classDef.add_static_constant("DETAIL_BLEND_MODE_MULTIPLY",umath::to_integral(msys::DetailMode::Multiply));
	classDef.add_static_constant("DETAIL_BLEND_MODE_BASE_MASK_VIA_DETAIL_ALPHA",umath::to_integral(msys::DetailMode::BaseMaskViaDetailAlpha));
	classDef.add_static_constant("DETAIL_BLEND_MODE_SELF_SHADOWED_BUMPMAP",umath::to_integral(msys::DetailMode::SelfShadowedBumpmap));
	classDef.add_static_constant("DETAIL_BLEND_MODE_SSBUMP_ALBEDO",umath::to_integral(msys::DetailMode::SSBumpAlbedo));
	classDef.add_static_constant("DETAIL_BLEND_MODE_COUNT",umath::to_integral(msys::DetailMode::Count));
	classDef.add_static_constant("DETAIL_BLEND_MODE_INVALID",umath::to_integral(msys::DetailMode::Invalid));
	classDef.scope[luabind::def("detail_blend_mode_to_enum",static_cast<void(*)(lua_State*,const std::string&)>([](lua_State *l,const std::string &name) {
		Lua::PushInt(l,umath::to_integral(msys::to_detail_mode(name)));
	}))];
	classDef.def("IsValid",&Lua::Material::IsValid);
	classDef.def("GetShaderName",&Lua::Material::GetShaderName);
	classDef.def("GetName",&Lua::Material::GetName);
	classDef.def("IsTranslucent",&Lua::Material::IsTranslucent);
	classDef.def("GetDataBlock",&Lua::Material::GetDataBlock);
	classDef.def("Copy",static_cast<void(*)(lua_State*,::Material&)>([](lua_State *l,::Material &mat) {
		auto *matCopy = mat.Copy();
		if(matCopy == nullptr)
			return;
		Lua::Push<::Material*>(l,matCopy);
	}));
	classDef.def("UpdateTextures",static_cast<void(*)(lua_State*,::Material&)>([](lua_State *l,::Material &mat) {
		mat.UpdateTextures();
	}));
	classDef.def("Save",static_cast<void(*)(lua_State*,::Material&,udm::AssetData&)>([](lua_State *l,::Material &mat,udm::AssetData &assetData) {
		std::string err;
		auto result = mat.Save(assetData,err);
		if(result == false)
			Lua::PushString(l,err);
		else
			Lua::PushBool(l,result);
	}));
	classDef.def("Save",static_cast<void(*)(lua_State*,::Material&)>([](lua_State *l,::Material &mat) {
		std::string err;
		auto result = mat.Save(err);
		if(result == false)
			Lua::PushString(l,err);
		else
			Lua::PushBool(l,result);
	}));
	classDef.def("Save",static_cast<void(*)(lua_State*,::Material&,const std::string&)>([](lua_State *l,::Material &mat,const std::string &fname) {
		std::string err;
		auto result = mat.Save(fname,err);
		if(result == false)
			Lua::PushString(l,err);
		else
			Lua::PushBool(l,result);
	}));
	classDef.def("IsError",static_cast<void(*)(lua_State*,::Material&)>([](lua_State *l,::Material &mat) {
		Lua::PushBool(l,mat.IsError());
	}));
	classDef.def("IsLoaded",static_cast<void(*)(lua_State*,::Material&)>([](lua_State *l,::Material &mat) {
		Lua::PushBool(l,mat.IsLoaded());
	}));
	classDef.def("IsTranslucent",static_cast<void(*)(lua_State*,::Material&)>([](lua_State *l,::Material &mat) {
		Lua::PushBool(l,mat.IsTranslucent());
	}));
	classDef.def("GetAlphaMode",static_cast<AlphaMode(*)(lua_State*,::Material&)>([](lua_State *l,::Material &mat) -> AlphaMode {
		return mat.GetAlphaMode();
	}));
	classDef.def("GetAlphaCutoff",static_cast<float(*)(lua_State*,::Material&)>([](lua_State *l,::Material &mat) -> float {
		return mat.GetAlphaCutoff();
	}));
	classDef.def("Reset",static_cast<void(*)(lua_State*,::Material&)>([](lua_State *l,::Material &mat) {mat.Reset();}));
}

void Lua::Material::IsTranslucent(lua_State *l,::Material &mat)
{
	Lua::PushBool(l,mat.IsTranslucent());
}

void Lua::Material::IsValid(lua_State *l,::Material &mat)
{
	Lua::PushBool(l,mat.IsValid());
}

void Lua::Material::GetName(lua_State *l,::Material &mat)
{
	Lua::PushString(l,mat.GetName());
}

void Lua::Material::GetShaderName(lua_State *l,::Material &mat) {Lua::PushString(l,mat.GetShaderIdentifier());}

void Lua::Material::GetDataBlock(lua_State *l,::Material &mat)
{
	auto &dataBlock = mat.GetDataBlock();
	Lua::Push<std::shared_ptr<ds::Block>>(l,dataBlock);
}

