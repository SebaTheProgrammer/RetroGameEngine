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

    std::vector<std::pair<std::string, int>> ReadHighScores( const std::string& path )
    {
        std::ifstream file( path );
        std::vector<std::pair<std::string, int>> highScores;

        if ( !file.is_open() )
        {
            std::cerr << "Unable to open file: " << path << std::endl;
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
            std::cerr << "Error reading file: " << path << std::endl;
            highScores.clear();
        }

        file.close();

        return highScores;
    }

    void WriteHighScores( const std::string& path, const std::vector<std::pair<std::string, int>>& highScores ) 
    {
        std::ofstream file( path );
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

    void UpdateHighScores( const std::string& path, const std::string& newName, int newScore )
    {
        auto highScores = ReadHighScores( path );

        highScores.push_back( { newName, newScore } );

        std::sort( highScores.begin(), highScores.end(), []( const auto& a, const auto& b )
            {
                return b.second < a.second;
            } );

        if ( highScores.size() > 10 )
        {
            highScores.resize( 10 );
        }

        std::cout << "Updated High Scores:" << std::endl;
        for ( const auto& score : highScores )
        {
            std::cout << score.first << " " << score.second << std::endl;
        }

        WriteHighScores( path, highScores );
    }

private:
    ScoreFile() = default;
};