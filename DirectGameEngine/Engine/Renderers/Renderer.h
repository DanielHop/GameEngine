#pragma once

#include <vector>
#include <memory>
#include <d3d11.h>

#include "../GameObjects/Entity.h"
#include "../Managers/ComponentManager.h"
class Renderer
{
public:
	virtual void Init(ID3D11Device* device, ID3D11DeviceContext* context){}

	void Render(std::vector<std::shared_ptr<Entity>> entities, ID3D11DeviceContext* context);

	void Shutdown();

	auto GetSignature() { return m_signature; }
private:
	virtual void Begin(ID3D11DeviceContext* context){}
	virtual void Submit(std::shared_ptr<Entity> e, int i) = 0;
	virtual void End(ID3D11DeviceContext* context) {}
	
	virtual void Flush(ID3D11DeviceContext* context, int nSprites) = 0;

	virtual void ShutdownLocal(){}
protected:
	ID3D11Buffer* m_VB, *m_IB;
	std::vector<unsigned int>m_signature;
};