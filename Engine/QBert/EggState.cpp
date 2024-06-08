#include "EggState.h"

EggState::EggState( std::shared_ptr<dae::AnimatedTextureComponent> textureCoily) :
	CoilyState( textureCoily )
{
}

void EggState::OnEnter()
{
	m_pTextureCoily->SetCurrentColumn( 0 );
	m_pTextureCoily->SetCurrentRow( 1 );
	m_pTextureCoily->SetMinColumns( 0 );
	m_pTextureCoily->SetMaxColumns( 4 );
	m_pTextureCoily->SetMinRows( 1 );
	m_pTextureCoily->SetMaxRows( 2 );
}

void EggState::OnExit()
{
}