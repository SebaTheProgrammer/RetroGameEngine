#pragma once
#include "ServiceLocator.h"

class SoundManager final
{

public:
	static SoundManager& GetInstance()
	{
		static SoundManager instance{};
		return instance;
	}

	//Player
	void PlayQbertFall( int volume = 50) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "QBertFall", "Sounds/QBertFall.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "QBertFall" ), volume );
	}
	void PlayerHit( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "QbertHit", "Sounds/QbertHit.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "QbertHit" ), volume );

		dae::ServiceLocator::GetSoundSystem().AddSound( "Swearing", "Sounds/Swearing.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "Swearing" ), volume );
	}
	void PlayerJump( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "QbertJump", "Sounds/QBertJump.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "QbertJump" ), volume );
	}
	void OnDisc( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "OnDisc", "Sounds/Disk Lift.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "OnDisc" ), volume );
	}
	void DiscLand( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "DiscLand", "Sounds/Disk Land.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "DiscLand" ), volume );
	}

	//Enemies
	void EnemyJump( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "Jump", "Sounds/Jump.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "Jump" ), volume );
	}
	void CaughtEnemy( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "CaughtEnemy", "Sounds/SlickSam Caught.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "CaughtEnemy" ), volume );
	}
	void CoilyFall( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "CoilyFall", "Sounds/Coily Fall.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "CoilyFall" ), volume );
	}

	//Level
	void StartRound( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "Start", "Sounds/Start.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "Start" ), volume );
	}
	void CompleteRound( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "CompleteRound", "Sounds/CompleteRound.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "CompleteRound" ), volume );
	}

	//Ui
	void ButtonChange( int volume = 50 ) {
		dae::ServiceLocator::GetSoundSystem().AddSound( "Change", "Sounds/Change Selection.wav" );
		dae::ServiceLocator::GetSoundSystem().Play( dae::ServiceLocator::GetSoundSystem().GetSoundId( "Change" ), volume );
	}

private:
	SoundManager() = default;
};