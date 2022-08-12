
#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

class GameStateManager
{
public:
    //GameStateManager() {}
    //~GameStateManager() {}

    enum GameState { // should be private
        GAMESTATE_GAME,
        GAMESTATE_PAUSED,
        GAMESTATE_MENU
    };

    inline GameState getGameState() const { return m_gameState; } // dont use probably lol
    void setGameState(const GameState& gameState) { m_gameState = gameState; } // also dont use probably
    
    inline bool getPaused() const { return (m_gameState == GAMESTATE_PAUSED); }
    inline bool inMenu() const { return (m_gameState == GAMESTATE_MENU); }

    void togglePaused()
    {
        if (m_gameState == GAMESTATE_GAME)
            m_gameState = GAMESTATE_PAUSED;
        else if (m_gameState == GAMESTATE_PAUSED)
            m_gameState = GAMESTATE_GAME;
    }

    void startGame()
    {
        m_gameState = GAMESTATE_GAME;
    }

private:
    GameState m_gameState;

};

#endif