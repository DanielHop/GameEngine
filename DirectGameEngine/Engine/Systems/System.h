#pragma once
#include <bitset>
#include <vector>
#include <deque>

#include <d3d11.h>

#include "../GameObjects/Entity.h"

enum TYPE
{
	ON_TICK_UPDATE,
	RENDER_UPDATE,
	BOTH,
	EMPTY_UPDATE,
};

class System
{
public:
	System() {}
	~System() {}

	virtual void Init() {}
	virtual void EmptyUpdate() {}
	virtual void OnTickUpdate(std::vector<std::shared_ptr<Entity>> entities, float dt){}
	virtual void RenderUpdate(std::vector<std::shared_ptr<Entity>> entities, ID3D11Device* device, ID3D11DeviceContext* context) {}
	virtual void Shutdown() {}

	auto GetSignature() { return m_signature; }
	auto getType() { return m_type; }

public:
	TYPE m_type;

protected:
	std::vector<unsigned int>m_signature;
};
