#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "../3rdParty/imgui.h"
#include "../3rdParty/imgui_impl_sdl2.h"
#include "../3rdParty/imgui_impl_opengl3.h"
#include "../3rdParty/imgui_plot.h"
#include <chrono>
#include <iostream>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init( SDL_Window* window )
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer( window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED );
	if ( m_Renderer == nullptr )
	{
		throw std::runtime_error( std::string( "SDL_CreateRenderer Error: " ) + SDL_GetError() );
	}

	InitImGui( window );
	{
	std::vector<double> values;
	std::vector<int> arr{};

	arr.resize( 1024 * 1024 * 16 );

	for ( int stepsize = 1; stepsize <= 1024; stepsize *= 2 )
	{
		double total_duration = 0.0;

		for ( int j = 0; j < 3; j++ )
		{
			auto start = std::chrono::high_resolution_clock::now();
			for ( int i = 0; i < arr.size(); i += stepsize ) {

				arr[ i ] *= 2;
				//arr[ i ].id *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			double duration_ms = std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count() / 1000.0;
			total_duration += duration_ms;
		}
		double avg_duration = total_duration / 3.0f;
		values.push_back( avg_duration );
	}
	std::vector<float> floats;
	floats.reserve( values.size() ); // Reserve memory for efficiency

	for ( const auto& d : values ) {
		floats.push_back( static_cast< float >( d ) ); // Convert and add to the float vector
	}
	m_Data1 = floats;
	}
	{
		std::vector<double> values2;
		struct transform {
			float matrix[ 16 ] = { 1,0,0,0,
							   0,1,0,0,
							   0,0,1,0,
							   0,0,0,1 };
		};
		class gameobject
		{
		public:
			transform local; //Made it a pointer
			int id;
		};

		std::vector<gameobject> arr2{};

		arr2.resize( 1024 * 1024 * 16 );

		for ( int stepsize = 1; stepsize <= 1024; stepsize *= 2 )
		{
			double total_duration = 0.0;

			for ( int j = 0; j < 3; j++ )
			{
				auto start = std::chrono::high_resolution_clock::now();
				for ( int i = 0; i < arr2.size(); i += stepsize ) {

					arr2[ i ].id *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();
				double duration_ms = std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count() / 1000.0;
				total_duration += duration_ms;
			}
			double avg_duration = total_duration / 3.0f;
			values2.push_back( avg_duration );
		}
		std::vector<float> floats2;
		floats2.reserve( values2.size() ); // Reserve memory for efficiency

		for ( const auto& d : values2 ) {
			floats2.push_back( static_cast< float >( d ) ); // Convert and add to the float vector
		}
		m_Data2 = floats2;
	}
	{
		std::vector<double> values2;
		struct transform {
			float matrix[ 16 ] = { 1,0,0,0,
							   0,1,0,0,
							   0,0,1,0,
							   0,0,0,1 };
		};
		class gameobject
		{
		public:
			transform* local; //Made it a pointer
			int id;
		};

		std::vector<gameobject> arr2{};

		arr2.resize( 1024 * 1024 * 16 );

		for ( int stepsize = 1; stepsize <= 1024; stepsize *= 2 )
		{
			double total_duration = 0.0;

			for ( int j = 0; j < 3; j++ )
			{
				auto start = std::chrono::high_resolution_clock::now();
				for ( int i = 0; i < arr2.size(); i += stepsize ) {

					arr2[ i ].id *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();
				double duration_ms = std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count() / 1000.0;
				total_duration += duration_ms;
			}
			double avg_duration = total_duration / 3.0f;
			values2.push_back( avg_duration );
		}
		std::vector<float> floats2;
		floats2.reserve( values2.size() ); // Reserve memory for efficiency

		for ( const auto& d : values2 ) {
			floats2.push_back( static_cast< float >( d ) ); // Convert and add to the float vector
		}
		m_Data3 = floats2;
	}
}


void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	SceneManager::GetInstance().Render();

	RenderImGui();
	
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::InitImGui( SDL_Window* window )
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL( window, SDL_GL_GetCurrentContext() );
	ImGui_ImplOpenGL3_Init();
}

void dae::Renderer::RenderImGui() const
{
	ImGui::ShowDemoWindow();

	ImGui::PlotLines( "", m_Data1.data(),  static_cast<int>(m_Data1.size()), 0, "Exercise1", 0.0f, 1.0f, ImVec2(0, 100));
	ImGui::PlotLines( "", m_Data2.data(), static_cast< int >( m_Data2.size() ), 0, "Exercise2", 0.0f, 1.0f, ImVec2( 0, 100 ) );
	ImGui::PlotLines( "", m_Data3.data(), static_cast< int >( m_Data3.size() ), 0, "Exercise3", 0.0f, 1.0f, ImVec2( 0, 100 ) );

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
}
