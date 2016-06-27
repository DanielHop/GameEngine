#include "Renderer.h"

void Renderer::Render(std::vector<std::shared_ptr<Entity>> entities, ID3D11DeviceContext* context)
{
	Begin(context);
	int i = 0;
	for (auto e : entities)
	{
		Submit(e, i);
		i++;
	}
	End(context);
	Flush(context, i);
}

void Renderer::Shutdown()
{
	m_IB->Release();
	m_VB->Release();

	ShutdownLocal();

}