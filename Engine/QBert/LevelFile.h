#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

class LevelFile
{
public:
    explicit LevelFile( const std::string& path ) : m_Path( path ) {}
    ~LevelFile() = default;

    LevelFile( const LevelFile& other ) = delete;
    LevelFile( LevelFile&& other ) = delete;
    LevelFile& operator=( const LevelFile& other ) = delete;
    LevelFile& operator=( LevelFile&& other ) = delete;

    struct Level
    {
        int length = 0;
        int levelNumber = 0;
        int howManyJumpsNeeded = 0;
    };

    std::vector<Level> ReadLevelFile( const std::string& path )
    {
        std::ifstream file( path );
        std::vector<Level> levels;

        if ( file.is_open() )
        {
            std::string line;
            while ( std::getline( file, line ) )
            {
                std::istringstream iss( line );
                Level level;

                if ( iss >> level.length >> level.levelNumber >> level.howManyJumpsNeeded )
                {
                    levels.push_back( level );
                }
            }
            file.close();
        }
        else
        {
            std::cerr << "Unable to open file: " << path << std::endl;
        }

        return levels;
    }

    std::vector<Level> ReadLevelFile()
    {
        return ReadLevelFile( m_Path );
    }

private:
    std::string m_Path;
};