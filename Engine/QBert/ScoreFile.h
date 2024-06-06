#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

class ScoreFile final
{
public:
    static ScoreFile& GetInstance()
    {
        static ScoreFile instance{};
        return instance;
    }

    ScoreFile(const ScoreFile& other) = delete;
    ScoreFile( ScoreFile&& other) = delete;
    ScoreFile& operator=(const ScoreFile& other) = delete;
    ScoreFile& operator=( ScoreFile&& other) = delete;

    std::vector<std::pair<std::string, int>> ReadHighScores()
    {
        std::ifstream file( m_Path );
        std::vector<std::pair<std::string, int>> highScores;

        if ( !file.is_open() )
        {
            std::cout << "Unable to open file: " << m_Path << std::endl;
            return highScores;
        }

        std::string name;
        int score;
        while ( file >> name >> score )
        {
            highScores.push_back( { name, score } );
        }

        if ( file.bad() )
        {
            std::cout << "Error reading file: " << m_Path << std::endl;
            highScores.clear();
        }

        file.close();

        return highScores;
    }

    void WriteHighScores(const std::vector<std::pair<std::string, int>>& highScores ) 
    {
        std::ofstream file( m_Path );
        if ( file.is_open() ) {
            for ( const auto& entry : highScores ) {
                file << entry.first << " " << entry.second << '\n';
            }
            file.close();
        }
        else {
            std::cout << "Unable to open file" << std::endl;
        }
    }

    void UpdateHighScores( int newScore )
    {
        auto highScores = ReadHighScores();

        highScores.push_back( { m_Name, newScore } );

        std::sort( highScores.begin(), highScores.end(), []( const auto& a, const auto& b )
            {
                return b.second < a.second;
            } );

        if ( highScores.size() > 10 )
        {
            highScores.resize( 10 );
        }

        WriteHighScores( highScores );
    }

    void SetName( std::string name ) { m_Name = name; };
    std::string GetName() const { return m_Name; };

private:
    ScoreFile() = default;
    std::string m_Name{"RandomPlayer"};
    std::string m_Path{"../Data/highscores.txt"};
};