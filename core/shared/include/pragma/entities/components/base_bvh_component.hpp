/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan */

#ifndef __BASE_BVH_COMPONENT_HPP__
#define __BASE_BVH_COMPONENT_HPP__

#include "pragma/entities/components/base_entity_component.hpp"
#include "pragma/entities/components/util_bvh.hpp"

namespace pragma {
	namespace bvh {
		struct BvhData;
	};
	class BaseStaticBvhCacheComponent;
	class DLLNETWORK BaseBvhComponent : public BaseEntityComponent {
	  public:
		static ComponentEventId EVENT_ON_CLEAR_BVH;
		static ComponentEventId EVENT_ON_BVH_UPDATE_REQUESTED;
		static ComponentEventId EVENT_ON_BVH_REBUILT;
		static bool ShouldConsiderMesh(const ModelSubMesh &mesh);
		static void RegisterEvents(pragma::EntityComponentManager &componentManager, TRegisterComponentEvent registerEvent);

		virtual void Initialize() override;

		virtual ~BaseBvhComponent() override;
		std::optional<bvh::HitInfo> IntersectionTest(const Vector3 &origin, const Vector3 &dir, float minDist, float maxDist) const;
		virtual bool IntersectionTest(const Vector3 &origin, const Vector3 &dir, float minDist, float maxDist, bvh::HitInfo &outHitInfo) const;
		bool IntersectionTestAabb(const Vector3 &min, const Vector3 &max) const;
		bool IntersectionTestAabb(const Vector3 &min, const Vector3 &max, bvh::IntersectionInfo &outIntersectionInfo) const;
		bool IntersectionTestKDop(const std::vector<umath::Plane> &planes) const;
		bool IntersectionTestKDop(const std::vector<umath::Plane> &planes, bvh::IntersectionInfo &outIntersectionInfo) const;
		void SetStaticCache(BaseStaticBvhCacheComponent *staticCache);
		virtual bool IsStaticBvh() const { return false; }
		const bvh::MeshRange *FindPrimitiveMeshInfo(size_t primIdx) const;

		void SendBvhUpdateRequestOnInteraction();
		static bool SetVertexData(pragma::bvh::BvhData &bvhData, const std::vector<bvh::Primitive> &data);
		static void DeleteRange(pragma::bvh::BvhData &bvhData, size_t start, size_t end);
		bool SetVertexData(const std::vector<bvh::Primitive> &data);
		void GetVertexData(std::vector<bvh::Primitive> &outData) const;
		void RebuildBvh();
		void ClearBvh();
		std::optional<Vector3> GetVertex(size_t idx) const;
		size_t GetTriangleCount() const;

		// For internal use only
		struct DLLNETWORK BvhBuildInfo {
			const std::vector<umath::ScaledTransform> *poses = nullptr;
			std::function<bool()> isCancelled = nullptr;
			std::function<bool(const ModelSubMesh &, uint32_t)> shouldConsiderMesh = nullptr;
		};
		static std::shared_ptr<pragma::bvh::BvhData> RebuildBvh(const std::vector<std::shared_ptr<ModelSubMesh>> &meshes, const BvhBuildInfo *optBvhBuildInfo = nullptr, std::vector<size_t> *optOutMeshIndices = nullptr);
		std::shared_ptr<bvh::BvhData> SetBvhData(std::shared_ptr<bvh::BvhData> &bvhData);
		bool HasBvhData() const;
	  protected:
		BaseBvhComponent(BaseEntity &ent);
		virtual void DoRebuildBvh() = 0;
		const std::shared_ptr<bvh::BvhData> &GetUpdatedBvh() const;
		std::vector<bvh::MeshRange> &GetMeshRanges();
		std::shared_ptr<bvh::BvhData> m_bvhData = nullptr;
		ComponentHandle<BaseStaticBvhCacheComponent> m_staticCache;
		mutable std::mutex m_bvhDataMutex;
		bool m_sendBvhUpdateRequestOnInteraction = false;
	};
};

#endif
