#ifndef __C_PARTICLE_MOD_BEAM_H__
#define __C_PARTICLE_MOD_BEAM_H__

#include "pragma/clientdefinitions.h"
#include "pragma/particlesystem/c_particlemodifier.h"

namespace pragma {class CLightComponent;};
class DLLCLIENT CParticleRendererBeam
	: public CParticleRenderer
{
public:
	CParticleRendererBeam(pragma::CParticleSystemComponent &pSystem,const std::unordered_map<std::string,std::string> &values);
	virtual void Render(const std::shared_ptr<prosper::PrimaryCommandBuffer> &drawCmd,const pragma::rendering::RasterizationRenderer &renderer,bool bloom) override;
	virtual void RenderShadow(const std::shared_ptr<prosper::PrimaryCommandBuffer> &drawCmd,const pragma::rendering::RasterizationRenderer &renderer,pragma::CLightComponent &light,uint32_t layerId=0) override;
	virtual void Destroy() override;
	virtual void PostSimulate(double tDelta) override;
	virtual std::pair<Vector3,Vector3> GetRenderBounds() const override;
private:
#pragma pack(push,1)
	struct DLLCLIENT Node
	{
		Node(const Vector3 &o,const Color &c);
		Vector3 origin = {};
		Vector4 color = {};
	};
#pragma pack(pop)
	std::shared_ptr<prosper::Buffer> m_vertexBuffer = nullptr;
	std::shared_ptr<prosper::Buffer> m_indexBuffer = nullptr;
	uint32_t m_startNode = 0u;
	uint32_t m_endNode = 0u;
	uint32_t m_nodeCount = 0u;
	std::vector<Node> m_nodeOrigins;
	uint32_t m_indexCount = 0u;
	util::WeakHandle<prosper::Shader> m_shader = {};
	float m_curvature = 0.f;
	void UpdateNodes();
};

#endif