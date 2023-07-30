#include"../type/ImguiManager.h"
void  ImguiManager::Initialize(HWND hwnd, ID3D12Device* device, DXGI_SWAP_CHAIN_DESC1 swapChainDesc, 
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc, ID3D12DescriptorHeap* srvDescriptorHeap) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX12_Init(device,
		swapChainDesc.BufferCount,
		rtvDesc.Format,
		srvDescriptorHeap,
		srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
		srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
}

void ImguiManager::BeginFrame(ID3D12DescriptorHeap* srvDescriptorHeap, ID3D12GraphicsCommandList* commandList)
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ID3D12DescriptorHeap* descriptorHeaps[] = { srvDescriptorHeap };
	commandList->SetDescriptorHeaps(1, descriptorHeaps);
}

void ImguiManager::EndFrame(ID3D12GraphicsCommandList* commandList)
{
	//ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);
}

void ImguiManager::Release()
{
}
