#include "SnakeState.h"
#include "Coily.h"
#include "BaseState.h"

SnakeState::SnakeState( std::shared_ptr<dae::AnimatedTextureComponent> textureCoily ) :
	CoilyState( textureCoily )
{
}

void SnakeState::OnEnter()
{
	m_pTextureCoily->SetCurrentColumn( 1 );
	m_pTextureCoily->SetMinColumns( 0 );
	m_pTextureCoily->SetMaxColumns( 4 );
	m_pTextureCoily->SetMinRows( 0 );
	m_pTextureCoily->SetMaxRows( 1 );
}

void SnakeState::OnExit()
{
}
