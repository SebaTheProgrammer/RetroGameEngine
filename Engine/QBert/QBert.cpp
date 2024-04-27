#include "QBert.h"
#include "ResourceManager.h"

QBert::QBert( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureIdle, std::shared_ptr<dae::Texture2D> textureJump,
	std::shared_ptr<dae::Texture2D> textureIdleBack, std::shared_ptr<dae::Texture2D> textureJumpBack, bool keyboardinput )
	:BaseComponent( parentGameObject )
	, m_KeyBoardInput( keyboardinput )
	, m_X( 0 )
	, m_Y( 0 )

{
	//all the textures, how can we make this more efficient?
	m_pTextureIdle = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdle, m_Scale, 1, 8, 0, m_FrameTime );
	m_pTextureJump = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureJump, m_Scale, 1, 8, 0, m_FrameTime );
	m_pTextureIdleBack = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdleBack, m_Scale, 1, 8, 0, m_FrameTime );
	m_pTextureJumpBack = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureJumpBack, m_Scale, 1, 6, 0, m_FrameTime );

	//movement
	m_pMovenment = std::make_shared<dae::MovenmentComponent>( parentGameObject, m_Speed );
	GetOwner()->AddComponent( m_pMovenment );
	m_pSingleMovenment = std::make_shared<dae::SingleMovementComponent>( parentGameObject, m_Speed, 1.f );
	GetOwner()->AddComponent( m_pSingleMovenment );

	if ( m_KeyBoardInput )
	{
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, InputTypeKeyBoard::IsPressed, dae::SingleMoveCommand{ GetOwner(), glm::vec2{-0.75f, -1.2f} } );
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_A, InputTypeKeyBoard::IsPressed, dae::SingleMoveCommand{ GetOwner(), glm::vec2{-0.75f, 1.2f} } );
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, InputTypeKeyBoard::IsPressed, dae::SingleMoveCommand{ GetOwner(), glm::vec2{0.75f, 1.2f} } );
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_D, InputTypeKeyBoard::IsPressed, dae::SingleMoveCommand{ GetOwner(), glm::vec2{0.75f, -1.2f} } );
	}
	else
	{
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsPressed, dae::MoveCommand{ GetOwner(),  glm::vec2{-0.75f, -1.2f} } );
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_LEFT, InputTypeGamePad::IsPressed, dae::MoveCommand{ GetOwner(), glm::vec2{-0.75f, 1.2f} } );
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_RIGHT, InputTypeGamePad::IsPressed, dae::MoveCommand{ GetOwner(), glm::vec2{0.75f, 1.2f} } );
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsPressed, dae::MoveCommand{ GetOwner(), glm::vec2{0.75f, -1.2f} } );
	}
	//testing mirror
	m_pTextureIdle->Mirror( true );

	////Stats
	//m_pStats = std::make_shared<PlayerStats>( parentGameObject, 3 );
	//GetOwner()->AddComponent( m_pStats );
	//AddObserver( m_pStats.get() );

	//auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 );
	//m_pHealthDisplay = std::make_shared<dae::TextComponent>( parentGameObject, "", font );
	//m_pHealthDisplay->SetText( "Health: " + std::to_string( m_pStats->GetLives() ) );
	//GetOwner()->AddComponent( m_pHealthDisplay );
}

void QBert::Update()
{
	switch ( m_CurrentState ) 
	{
	case AnimationState::Idle:
		m_pTextureIdle->Update();
		break;
	case AnimationState::Jump:
		m_pTextureJump->Update();
		break;
	case AnimationState::IdleBack:
		m_pTextureIdleBack->Update();
		break;
	case AnimationState::JumpBack:
		m_pTextureJumpBack->Update();
		break;
	}
}

void QBert::Render() const
{
	switch ( m_CurrentState ) 
	{
	case AnimationState::Idle:
		m_pTextureIdle->Render();
		break;
	case AnimationState::Jump:
		m_pTextureJump->Render();
		break;
	case AnimationState::IdleBack:
		m_pTextureIdleBack->Render();
		break;
	case AnimationState::JumpBack:
		m_pTextureJumpBack->Render();
		break;
	}
}

void QBert::GetsHit()
{
	NotifyObservers( dae::EventType::PLAYER_HIT, GetOwner() );
}
