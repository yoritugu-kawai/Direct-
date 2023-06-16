#include"WinApp.h"

//　ウィンドウプロシャージャ
LRESULT CALLBACK  WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	//　メッセージ固有処理
	switch (msg)
	{
		//　ウィンドウが破棄された
	case WM_DESTROY:
		//　OSに対してアプリが終了を伝える
		PostQuitMessage(0);
		return 0;
	}
	//　メッセージ標準処理
	return DefWindowProc(hwnd, msg, wparam, lparam);

}
WinApp::WinApp(const wchar_t* title, const int32_t kClientWidth, const int32_t kClientHeight) {
	this->title_ = title;
	this->kClientWidth_ = kClientWidth;
	this->kClientHeight_ = kClientHeight;

	this->hwnd_ = nullptr;
}

void  WinApp::Initialize() {
	DxCommen* dxCommen_ = new DxCommen;
	//ウィンドウプロシャージャ
	wc.lpfnWndProc = WindowProc;
	// ウィンドウクラス名
	wc.lpszClassName = L"%s", title_;
	//インスタンドハンドル
	wc.hInstance = GetModuleHandle(nullptr);
	//　カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//ウィンドウクラス登録
	RegisterClass(&wc);
	// クライアント領域サイズ

	//  ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc_ = { 0,0,kClientWidth_ ,kClientHeight_ };
	// クライアント領域を元に実際のサイズにwrcを変更
	AdjustWindowRect(&wrc_, WS_OVERLAPPEDWINDOW, false);
	// ウィンドウ生成
	hwnd_ = CreateWindow(
		wc.lpszClassName,//　クラス名
		title_,                //　タイトルバーの文字
		WS_OVERLAPPEDWINDOW,  //　標準的なウィンドウスタイル
		CW_USEDEFAULT,        //　標準X座標
		CW_USEDEFAULT,        //　標準Y座標
		wrc_.right - wrc_.left, //　横幅
		wrc_.bottom - wrc_.top, //　縦幅ti
		nullptr,              //　親ハンドル
		nullptr,              //　メニューハンドル
		wc.hInstance,         //　インスタンスハンドル
		nullptr               //　オプション
	);
	//ウィンドウを表示
	ShowWindow(hwnd_, SW_SHOW);
#ifdef _DEBUG
	deugController = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&deugController)))) {
		deugController->EnableDebugLayer();
		deugController->SetEnableGPUBasedValidation(TRUE);
	}

#endif // _DEBUG
}
void WinApp::Release() {
#ifdef _DEBUG
	deugController->Release();
#endif // _DEBUG
}
